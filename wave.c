#define _DEFAULT_SOURCE
#include <math.h>
#include <stdio.h>
#include <raylib.h>
#include <string.h>
#include <stdlib.h>

static inline float secf(const float r)
{
	return 1.0 / sinf(r);
}
static inline float cosecf(const float r)
{
	return 1.0 / cosf(r);
}
static inline float cotanf(const float r)
{
	return 1.0 / tanf(r);
}

typedef float(*WaveFunction)(float);

const int width = 720;
const int height = 600;

const Vector2 title_pos = { 20, 20 };
const int title_size = 40;

const int dot_radius = 20;
const int wavelength = 100;

const int bottom_text_size = title_size; 
const Vector2 bottom_text_pos = { 0, height / 2 + wavelength}; 

void DrawTunnel(const Vector2 start, const int x_coord, const int dx, WaveFunction wave_func, const char *wave_name)
{
	for (int x = 0; x < width; x += dx) {
		const Vector2 pos = {
			.x = start.x + x,
			.y = start.y + wavelength * wave_func(x * DEG2RAD),
		};

		DrawCircleV(pos, dot_radius * 3/2, ColorAlpha(DARKGRAY, 0.25));
	}

	const Vector2 pos = {
		.x = start.x + x_coord,
		.y = start.y + wavelength * wave_func(x_coord * DEG2RAD),
	};

	DrawCircleV(pos, dot_radius, RAYWHITE);

	DrawText(wave_name, bottom_text_pos.x, bottom_text_pos.y, bottom_text_size, RAYWHITE);
}

enum wave {
	SINE,
	COSINE,
	TANGENT,

	SECANT,
	COSECANT,
	COTANGENT,

	INVALID,
};

enum wave parse_wave_type(const int argc, char **argv)
{
	if (argc == 1)
		return SINE;

	if (argc > 2)
		return INVALID;
	
	if (!strcmp(argv[1], "sine"))
		return SINE;
	if (!strcmp(argv[1], "cosine"))
		return COSINE;
	if (!strcmp(argv[1], "tangent"))
		return TANGENT;

	if (!strcmp(argv[1], "secant"))
		return SECANT;
	if (!strcmp(argv[1], "cosecant"))
		return COSECANT;
	if (!strcmp(argv[1], "cotangent"))
		return COTANGENT;

	return INVALID;
}

__attribute((noreturn)) void usage(void)
{
	fprintf(stderr, "usage: ./wave sine|cosine\n");
	exit(1);
}

int main(const int argc, char **argv)
{
	const enum wave wave_type = parse_wave_type(argc, argv); 

	if (wave_type == INVALID)
		usage();

	const Vector2 screen_pos = { GetScreenWidth() / 4, GetScreenHeight() / 4 };

	InitWindow(width, height, "sine wave");
	SetWindowPosition(screen_pos.x, screen_pos.y);

	const Vector2 start = { 0, (height - wavelength) / 2 };
	const int dx = 5;
	int x_coord = 0;

	const char *wave_name;
	WaveFunction wave_func;

	switch (wave_type) {
	case SINE:	wave_name = "(sine)"; wave_func = sinf; break;
	case COSINE:	wave_name = "(cosine)"; wave_func = cosf; break;
	case TANGENT:	wave_name = "(tangent)"; wave_func = tanf; break;

	case SECANT:	wave_name = "(secant)"; wave_func = secf; break;
	case COSECANT:	wave_name = "(cosecant)"; wave_func = cosecf; break;
	case COTANGENT:	wave_name = "(cotangent)"; wave_func = cotanf; break;

	default: __builtin_unreachable();
	}


	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("serpent lullaby", title_pos.x, title_pos.y, title_size, SKYBLUE);

		DrawTunnel(start, x_coord, dx, wave_func, wave_name);

		x_coord = (x_coord + dx) % (width * 5/4);

		EndDrawing();
	}

	CloseWindow();
}
