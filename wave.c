#include <math.h>
#include <stdio.h>
#include <raylib.h>
#include <string.h>
#include <stdlib.h>

const int width = 720;
const int height = 600;

const Vector2 title_pos = { 20, 20 };
const int title_size = 40;

const int dot_radius = 20;
const int wavelength = 100;

const int bottom_text_size = title_size; 
const Vector2 bottom_text_pos = { 0, height / 2 + wavelength}; 

void DrawSineTunnel(const Vector2 start, const int x_coord, const int dx)
{
	for (int x = 0; x < width; x += dx) {
		const Vector2 pos = {
			.x = start.x + x,
			.y = start.y + wavelength * sinf(x * DEG2RAD),
		};

		DrawCircleV(pos, dot_radius * 3/2, ColorAlpha(DARKGRAY, 0.25));
	}

	const Vector2 pos = {
		.x = start.x + x_coord,
		.y = start.y + wavelength * sinf(x_coord * DEG2RAD),
	};

	DrawCircleV(pos, dot_radius, RAYWHITE);

	DrawText("(sine)", bottom_text_pos.x, bottom_text_pos.y, bottom_text_size, RAYWHITE);
}

void DrawCosineTunnel(const Vector2 start, const int x_coord, const int dx)
{
	for (int x = 0; x < width; x += dx) {
		const Vector2 pos = {
			.x = start.x + x,
			.y = start.y + wavelength * cosf(x * DEG2RAD),
		};

		DrawCircleV(pos, dot_radius * 3/2, ColorAlpha(DARKGRAY, 0.25));
	}

	const Vector2 pos = {
		.x = start.x + x_coord,
		.y = start.y + wavelength * cosf(x_coord * DEG2RAD),
	};

	DrawCircleV(pos, dot_radius, RAYWHITE);

	DrawText("(cosine)", bottom_text_pos.x, bottom_text_pos.y, bottom_text_size, RAYWHITE);
}

enum wave {
	SINE,
	COSINE,
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
	const int dx = 10;
	int x_coord = 0;

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("serpent lullaby", title_pos.x, title_pos.y, title_size, SKYBLUE);

		switch (wave_type) {
		case SINE: DrawSineTunnel(start, x_coord, dx); break;
		case COSINE: DrawCosineTunnel(start, x_coord, dx); break;

		default: __builtin_unreachable();
		}

		x_coord = (x_coord + dx) % (width * 5/4);

		EndDrawing();
	}

	CloseWindow();
}
