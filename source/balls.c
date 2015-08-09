/*
 * This program demonstrates the glSDL Extended 2D API.
 * This code is in the public domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "glSDL.h"

static int screenw = 640;
static int screenh = 480;
static int spritesize = 96;


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
			int q = (x < size / 2) + (y < size / 2) * 2;
			int r, g, b;
			switch(q)
			{
			  case 0:
			  case 3:
				r = g = b = 256;
				break;
			  case 1:
				r = 256;
				g = b = 100;
				break;
			  case 2:
				b = 256;
				r = g = 100;
				break;
			}
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
				p[0] = v * r >> 8;
				p[1] = v * g >> 8;
				p[2] = v * b >> 8;
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


static void clear_fun(SDL_Surface *screen, double t)
{
	int y;
	for(y = 0; y < screenh; ++y)
	{
		float red, blue;
		SDL_Rect r;
		r.x = 0;
		r.w = screenw;
		r.y = y;
		r.h = 1;
		red = .25 + .25 * sin(t * 1.7 + (float)y / screenh * 2.1);
		red += .25 + .25 * sin(-t * 2.1 + (float)y / screenh * 3.3);
		blue = .25 + .25 * sin(t * 3.31 + (float)y / screenh * 4.5);
		blue += .25 + .25 * sin(-t * 1.1 + (float)y / screenh * 7.7);
		SDL_FillRect(screen, &r, SDL_MapRGB(screen->format,
					(int)64.0 * red, 0,
					(int)96.0 * blue));
	}
}


static void usage(const char *exename)
{
	fprintf(stderr, "Usage: %s [switches] <balls>\n\n", exename);
	fprintf(stderr, "Switches:  -a          Disable antialiazing\n");
	fprintf(stderr, "           -b<n>       Request <n> BitsPerPixel\n");
	fprintf(stderr, "           -c          Use colorkey instead of alpha\n");
	fprintf(stderr, "           -d          Disable double buffering\n");
	fprintf(stderr, "           -f          Fullscreen mode\n");
	fprintf(stderr, "           -g          Use flat gray background\n");
	fprintf(stderr, "           -gl         Disable OpenGL rendering\n");
	fprintf(stderr, "           -w<n>       Display width <n> pixels\n");
	fprintf(stderr, "           -h<n>       Display height <n> pixels\n\n");
	exit(1);
}


int main(int argc, char *argv[])
{
	SDL_Surface *screen;
	SDL_Surface *sprite, *temp;
	SDL_Event event;
	const SDL_version *v;
	int i, t1, t2;
	int running = 1;
	int bpp = 0;
	int flags = SDL_GLSDL | SDL_DOUBLEBUF;
	int cc = 0;
	int aa = 1;
	int trans = 0;
	int fps_start, fps_count;
	int sprite_count = 100;
	int fun = 1;
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
		else if(strncmp(argv[i], "-g", 4) == 0)
			fun = !fun;
		else if(strncmp(argv[i], "-a", 2) == 0)
			aa = !aa;
		else if(strncmp(argv[i], "-t", 2) == 0)
		{
			trans = 1;
			printf("Making sprites translucent.\n");
		}
		else if(strncmp(argv[i], "-c", 2) == 0)
		{
			cc = 1;
			printf("Using colorkeying instead of alpha.\n");
		}
		else if(strncmp(argv[i], "-b", 2) == 0)
			bpp = atoi(&argv[i][2]);
		else if(strncmp(argv[i], "-d", 2) == 0)
			flags ^= SDL_DOUBLEBUF;
		else if(strncmp(argv[i], "-f", 2) == 0)
			flags ^= SDL_FULLSCREEN;
		else if(strncmp(argv[i], "-w", 2) == 0)
			screenw = atoi(&argv[i][2]);
		else if(strncmp(argv[i], "-h", 2) == 0)
			screenh = atoi(&argv[i][2]);
		else
		{
			sprite_count = atoi(&argv[i][0]);
			if(!sprite_count)
				usage(argv[0]);
		}
	}

	if((flags & SDL_GLSDL) == SDL_GLSDL)
		printf("Requesting glSDL.\n");
	if(bpp)
		printf("Requesting %d bpp.\n", bpp);
	if((flags & SDL_DOUBLEBUF) == SDL_DOUBLEBUF)
		printf("Requesting double buffered display.\n");
	if((flags & SDL_FULLSCREEN) == SDL_FULLSCREEN)
		printf("Requesting fullscreen display.\n");
	printf("Display size: %dx%d.\n", screenw, screenh);
	printf("Sprite size: %dx%d.\n", spritesize, spritesize);
	printf("Sprite count: %d.\n", sprite_count);
	printf("Antialiasing: %s\n", aa ? "Enabled" : "Disabled");
	printf("Background fun: %s\n", fun ? "Enabled" : "Disabled");

	screen = SDL_SetVideoMode(screenw, screenh, bpp, flags);
	if(!screen)
	{
		fprintf(stderr, "Failed to open screen!\n");
		exit(-1);
	}
	screenw = screen->w;
	screenh = screen->h;

	SDL_WM_SetCaption("balls", "balls");

	temp = create_sprite(spritesize, aa, trans);
	if(!temp)
	{
		fprintf(stderr, "Failed to create sprite!\n");
		exit(-1);
	}

	if(cc)
	{
		SDL_SetColorKey(temp, SDL_SRCCOLORKEY | SDL_RLEACCEL,
				SDL_MapRGBA(temp->format, 0, 0, 0 ,0));
		sprite = SDL_DisplayFormat(temp);
	}
	else
	{
		SDL_SetAlpha(temp, SDL_SRCALPHA | SDL_RLEACCEL, 255);
		sprite = SDL_DisplayFormatAlpha(temp);
	}
	SDL_FreeSurface(temp);
	if(!sprite)
	{
		fprintf(stderr, "Failed to convert sprite!\n");
		exit(-1);
	}

	fps_start = SDL_GetTicks();
	fps_count = 0;
	t1 = t2 = fps_start;
	t = 0;
	while(running)
	{
		float dt = (float)(t2 - t1) * 0.001;

		while(SDL_PollEvent(&event))
			switch(event.type)
			{
			  case SDL_MOUSEBUTTONDOWN:
			  case SDL_KEYDOWN:
			  case SDL_QUIT:
				running = 0;
				break;
			}

		if(fun)
			clear_fun(screen, t);
		else
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,
					64, 64, 64));

		for(i = 0; i < sprite_count; ++i)
		{
			float x, y, s;
			SDL_Rect r;
			float z = i * 100.0f / sprite_count;
			x = sin(t + z * .05f) * sin(t*1.7f + z * .11f);
			y = cos(t * 1.1f + z * .06f) * cos(t * 2.3f + z * .23f);
			s = 1.0f + sin(t * 1.7f + z * .11f) * cos(t * 1.1f + z * .06f);
			x *= (screenw - spritesize) / 2;
			y *= (screenh - spritesize) / 2;
			r.x = (int)x + (screenw - spritesize) / 2;
			r.y = (int)y + (screenh - spritesize) / 2;
			glSDL_SetScale(s, s);
			glSDL_SetRotation(t * z * 5.0f);
			glSDL_SetBlendAlpha(128 + 127.0f *
					sin(t * 1.2f + z * .2f));
			glSDL_SetBlendColor(s * 127.0f, 255, s * 127.0f);
			SDL_BlitSurface(sprite, NULL, screen, &r);
		}
		glSDL_ResetState();

		SDL_Flip(screen);
		t += dt;
		t1 = t2;
		t2 = SDL_GetTicks();
		++fps_count;
	}

	printf("Average fps: %f\n",
			fps_count * 1000.0 / (SDL_GetTicks() - fps_start));

	SDL_FreeSurface(sprite);
	exit(0);
}
