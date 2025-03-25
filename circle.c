#include "raylib.h"
#include "stdio.h"
#include "math.h"

#define WIN_W 1024
#define WIN_H 768

#define TOP_OFFSET 50

int main() {
	InitWindow(WIN_W, WIN_H, "Circle");

	Vector2 ball_pos = { WIN_W/2, WIN_H/2 };
	Vector2 ball_vel = {0,0};

	const Vector2 circle_origin = { WIN_W/2, WIN_H/2 };
        float circle_radius = circle_origin.y - TOP_OFFSET;	

	bool animating_f1 = false, animating_f2 = false;

	const float linear_speed = 10;
	float angle;

	SetTargetFPS(60);	

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			if (!animating_f2)
				animating_f1 = true;
		}

		if (animating_f1) 
		{
			ball_vel.y = -linear_speed;
			if (ball_pos.y <= TOP_OFFSET)
			{
				ball_vel.y = 0;
				animating_f1 = false;
				animating_f2 = true;
			}
		}
		else if (animating_f2)
		{
			angle += 3.14f * GetFrameTime();

			ball_vel.x = linear_speed * cosf(angle);
			ball_vel.y = linear_speed * sinf(angle);
		}

		ball_pos.y += ball_vel.y;
		ball_pos.x += ball_vel.x;

		BeginDrawing();
		
		ClearBackground(BLACK);
		DrawCircleV(ball_pos, 10, RED);
		
		EndDrawing();

	}

	CloseWindow();
	
	return 0;
}
