/*
 * This program tests blitting from huge surfaces.
 * This code is in the public domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "glSDL.h"

#define	IMAGE_W		2400
#define	IMAGE_H		2400
#define	SPRITE_SIZE	64
#define	NBALLS		(IMAGE_W*IMAGE_H / (SPRITE_SIZE*SPRITE_SIZE))
#define	SPEED		2.0

/*----------------------------------------------------------
	Render a "shaded" ball
----------------------------------------------------------*/
static SDL_Surface *create_sprite(int size, int aa, int trans)
{
	int x, y;
	SDL_Surface *s = SDL_CreateRGBSurface(SDL_SWSURFACE, size, size, 32,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
#else
			0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
#endif
	if(!s)
		return NULL;

	for(y = 0; y < size; ++y)
		for(x = 0; x < size; ++x)
		{
			unsigned char *p = s->pixels + y * s->pitch + x * 4;
			float dx = x - size * 0.5;
			float dy = y - size * 0.5;
			float d = sqrt(dx*dx + dy*dy);
			if(d > size * 0.5)
			{
				p[0] = 0;
				p[1] = 0;
				p[2] = 0;
				p[3] = 0;
			}
			else
			{
				int v = (int)(255.0 * (1.0 - d / size * 2.0));
				p[0] = v;
				p[1] = v;
				p[2] = v;
				if(aa)
				{
					if(v < 16)
						p[3] = v << 4;
					else
						p[3] = 255;
				}
				else
				{
					if(v < 8)
						p[3] = 0;
					else
						p[3] = 255;
				}
				if(trans)
					p[3] /= 3;
			}
		}
	return s;
}


/*----------------------------------------------------------
	Simple pseudo-random number generator
----------------------------------------------------------*/
static Uint32 rnd = 16576;


static void rng_reset(void)
{
	rnd = 16576;
}


static Uint32 rng_get(void)
{
	rnd *= 1566083941UL;
	rnd++;
	rnd &= 0xffffffffUL;	/* NOP on 32 bit machines */
	return rnd;
}


/*----------------------------------------------------------
	Render a big image filled with balls
----------------------------------------------------------*/
static SDL_Surface *create_image(int w, int h, int balls)
{
	int i, x, y;
	SDL_Surface *s, *tmp, *sprite;
	s = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 24,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			0x00ff0000, 0x0000ff00, 0x000000ff, 0);
#else
			0x000000ff, 0x0000ff00, 0x00ff0000, 0);
#endif
	if(!s)
		return NULL;

	sprite = create_sprite(SPRITE_SIZE, 1, 0);
	if(!sprite)
	{
		fprintf(stderr, "Failed to create ball!\n");
		SDL_FreeSurface(sprite);
		return NULL;
	}
	SDL_SetAlpha(sprite, SDL_SRCALPHA | SDL_RLEACCEL, 255);

	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 96, 32, 128));
	for(y = 0; y < 16; ++y)
		for(x = 0; x < 16; ++x)
		{
			SDL_Rect r;
			r.x = x * (w / 16) + 2;
			r.y = y * (h / 16) + 2;
			r.w = w / 16 - 4;
			r.h = h / 16 - 4;
			SDL_FillRect(s, &r, SDL_MapRGB(s->format, x*15, y*15, 0));
		}

	rng_reset();
	for(i = 0; i < balls; ++i)
	{
		SDL_Rect r;
		r.x = (rng_get() >> 16) * (w - SPRITE_SIZE) >> 16;
		r.y = (rng_get() >> 16) * (h - SPRITE_SIZE) >> 16;
		SDL_BlitSurface(sprite, NULL, s, &r);
	}

	SDL_FreeSurface(sprite);

	tmp = SDL_DisplayFormat(s);
	if(!tmp)
	{
		SDL_FreeSurface(s);
		return NULL;
	}
	SDL_FreeSurface(s);

	return tmp;
}


/*----------------------------------------------------------
	Render a hollow box
----------------------------------------------------------*/
static void box(SDL_Surface *dst, SDL_Rect *rect, Uint32 color)
{
	SDL_Rect r;
	r.x = rect->x;
	r.y = rect->y;
	r.w = rect->w;
	r.h = 1;
	SDL_FillRect(dst, &r, color);
	r.x = rect->x;
	r.y = rect->y + rect->h - 1;
	r.w = rect->w;
	r.h = 1;
	SDL_FillRect(dst, &r, color);
	r.x = rect->x;
	r.y = rect->y;
	r.w = 1;
	r.h = rect->h;
	SDL_FillRect(dst, &r, color);
	r.x = rect->x + rect->w - 1;
	r.y = rect->y;
	r.w = 1;
	r.h = rect->h;
	SDL_FillRect(dst, &r, color);
}


/*----------------------------------------------------------
	Main
----------------------------------------------------------*/

static void usage(const char *exename)
{
	fprintf(stderr, "Usage: %s [switches]\n\n", exename);
	fprintf(stderr, "Switches:  -gl         Disable OpenGL rendering\n");
	fprintf(stderr, "           -b<n>       Request <n> BitsPerPixel\n");
	fprintf(stderr, "           -d          Disable double buffering\n");
	fprintf(stderr, "           -f          Fullscreen mode\n");
	fprintf(stderr, "           -w<n>       Display width <n> pixels\n");
	fprintf(stderr, "           -h<n>       Display height <n> pixels\n\n");
	exit(1);
}


int main(int argc, char *argv[])
{
	SDL_Surface *screen;
	SDL_Surface *image;
	SDL_Event event;
	const SDL_version *v;
	int i, t1, t2;
	int running = 1;
	int bpp = 0;
	int width = 640;
	int height = 480;
	int flags = SDL_GLSDL | SDL_DOUBLEBUF;
	int fps_start, fps_count;
	double t;

	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);

	v = SDL_Linked_Version();
	printf("Using SDL version %d.%d.%d.\n",
			v->major, v->minor, v->patch);

	for(i = 1; i < argc; ++i)
	{
		if(strncmp(argv[i], "-gl", 3) == 0)
			flags ^= SDL_GLSDL;
		else if(strncmp(argv[i], "-b", 2) == 0)
			bpp = atoi(&argv[i][2]);
		else if(strncmp(argv[i], "-d", 2) == 0)
			flags ^= SDL_DOUBLEBUF;
		else if(strncmp(argv[i], "-f", 2) == 0)
			flags ^= SDL_FULLSCREEN;
		else if(strncmp(argv[i], "-w", 2) == 0)
			width = atoi(&argv[i][2]);
		else if(strncmp(argv[i], "-h", 2) == 0)
			height = atoi(&argv[i][2]);
		else
			usage(argv[0]);
	}

	if((flags & SDL_GLSDL) == SDL_GLSDL)
		printf("Requesting glSDL.\n");
	if(bpp)
		printf("Requesting %d bpp.\n", bpp);
	if((flags & SDL_DOUBLEBUF) == SDL_DOUBLEBUF)
		printf("Requesting double buffered display.\n");
	if((flags & SDL_FULLSCREEN) == SDL_FULLSCREEN)
		printf("Requesting fullscreen display.\n");
	printf("Display size: %dx%d.\n", width, height);

	screen = SDL_SetVideoMode(width, height, bpp, flags);
	if(!screen)
	{
		fprintf(stderr, "Failed to open screen!\n");
		exit(-1);
	}
	width = screen->w;
	height = screen->h;

	SDL_WM_SetCaption("bigscroll", "bigscroll");

	image = create_image(IMAGE_W, IMAGE_H, NBALLS);
	if(!image)
	{
		fprintf(stderr, "Failed to create image!\n");
		exit(-1);
	}

	/* Get the image converted, uploaded and whatnot first... */
	SDL_BlitSurface(image, NULL, screen, NULL);

	fps_start = SDL_GetTicks();
	fps_count = 0;
	t1 = t2 = fps_start;
	t = 0;
	while(running)
	{
		float x, y;
		SDL_Rect r, dr;
		float dt = (float)(t2 - t1) * .001f;

		while(SDL_PollEvent(&event))
			switch(event.type)
			{
			  case SDL_MOUSEBUTTONDOWN:
			  case SDL_KEYDOWN:
			  case SDL_QUIT:
				running = 0;
				break;
			}

		/* Background */
		SDL_FillRect(screen, NULL,
				SDL_MapRGB(screen->format, 96, 96, 96));

		/* Display target rect */
		dr.x = 20;
		dr.y = 20;
		dr.w = width - 40;
		dr.h = height - 40;
		box(screen, &dr, SDL_MapRGB(screen->format, 255, 0, 255));

		/* Test blit */
		x = sin(t*.1*SPEED) * (IMAGE_W - width) / 2;
		y = cos(t*.17*SPEED) * (IMAGE_H - height) / 2;
		r.x = (int)x + (IMAGE_W - width) / 2 + 20;
		r.y = (int)y + (IMAGE_H - height) / 2 + 20;
		r.w = width - 40;
		r.h = height - 40;
		dr.x = 20;
		dr.y = 20;
		SDL_BlitSurface(image, &r, screen, &dr);

		/* Display resulting clip rect */
		box(screen, &dr, SDL_MapRGB(screen->format, 255, 255, 0));

		SDL_Flip(screen);
		t += dt;
		t1 = t2;
		t2 = SDL_GetTicks();
		++fps_count;
	}

	printf("Average fps: %f\n",
			fps_count * 1000.0f / (SDL_GetTicks() - fps_start));

	SDL_FreeSurface(image);
	SDL_Quit();
	exit(0);
}
