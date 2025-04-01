#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define WIN_W 1028
#define WIN_H 768

#define PLAT_W 25

int player_on_ground(Rectangle* player, int offset);

Rectangle* create_platforms(size_t size);

int main () {
	SetTargetFPS(60);
	InitWindow(WIN_W,WIN_H, "DASH");

	Rectangle player = {
		WIN_W/2,
		WIN_H/2,
		25,
		25
	};

	Vector2 p_vel = {0};	

	const float gravity = 0.5;
	float angle = 0.0f;
	int dir = 0;
	
	size_t platform_count = 10;
	Rectangle* platforms = create_platforms(platform_count);

	while (!WindowShouldClose())
	{

		if (player_on_ground(&player, 0))
		{
			p_vel.y = 0;
			angle = 0;
		}
		else 
		{	
			p_vel.y += gravity;
			angle += 1.5f;
		}

		if (p_vel.x > 0)
			p_vel.x -= 0.25;
		else if (p_vel.x < 0)
		{
			p_vel.x += 0.25;
		}

		if (IsKeyPressed(KEY_SPACE) && player_on_ground(&player, 50))
		{
			p_vel.y = -15;
			if (p_vel.x > 0)
				dir = 1;
			else if (p_vel.x < 0)
				dir = -1;
		}
		if (IsKeyDown(KEY_RIGHT))
		{
			p_vel.x = 5;
		}
		else if (IsKeyDown(KEY_LEFT))
		{
			p_vel.x = -5;
		}

		player.x += p_vel.x;
		player.y += p_vel.y;
		
		BeginDrawing();
		
		ClearBackground(BLACK);
		DrawRectanglePro (
				  player, 
				  (Vector2)  {player.width/2,player.height/2}, 
				  angle * dir,
			       	  GREEN
		);
		for (int i = 0; i < platform_count; i++)
		{
			DrawRectangleRec(platforms[i], RED);
		}
		EndDrawing();
	}

	free(platforms);

	CloseWindow();
	return 0;
}

Rectangle* create_platforms(size_t size) {
	Rectangle* platforms = malloc(size * sizeof(Rectangle));

	platforms[0].x = 0;
	platforms[0].height = 500;
	platforms[0].y = WIN_H - platforms[0].height;
	platforms[0].width = PLAT_W;

	srand(time(NULL));

	float min_x, max_x , min_h = 1, max_h;
	for (int i = 1; i < size; i++)
	{
		min_x = platforms[i - 1].x + PLAT_W + 100;
		max_x = min_x + 50;
		max_h = platforms[i - 1].height + 100;

		float height = min_h + rand() % (int)(max_h - min_h + 1);
		platforms[i] = (Rectangle) {
			min_x + rand() % (int)(max_x - min_x + 1),
			WIN_H - height,
			PLAT_W,
			height
		};

		//printf("Plat no. %d CALCED X = %f, CALCED HEIGHT = %f\n", i, platforms[i].x, platforms[i].height);
	}

	return platforms;
}

int player_on_ground(Rectangle* player, int offset) {
	if ((player->y+player->height) >= WIN_H - offset)
	{
		player->y = WIN_H - player->height;
		return 1;
	}
	return 0;
}
