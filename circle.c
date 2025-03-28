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
        const float rotation_length = circle_origin.y - TOP_OFFSET;
	float circle_radius = rotation_length;	

	bool animating_f1 = false, animating_f2 = false;

	bool ball_falling = true;

	const float linear_speed = 10;
	const float rotational_speed = 2.0f * PI / 120.0f;
	float angle = 0;

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
			angle += rotational_speed;
			if (angle >= 2*PI)
				angle -= 2*PI;

			ball_vel.x = -rotational_speed * circle_radius * cosf(angle);
			ball_vel.y =  rotational_speed * circle_radius * sinf(angle);


			if (ball_falling)
				circle_radius -= 0.25f;
			else 	
				circle_radius += 0.25f;

			if (ball_falling && circle_radius <= 50)
				ball_falling = false;
			else if (circle_radius >= rotation_length)
				ball_falling = true;
		}

		ball_pos.y += ball_vel.y;
		ball_pos.x += ball_vel.x;

		BeginDrawing();
		
		ClearBackground(BLACK);
		DrawCircleV(ball_pos, 20, BLUE);
		DrawCircle(circle_origin.x, circle_origin.y, 40, YELLOW);
		
		EndDrawing();

	}

	CloseWindow();
	
	return 0;
}
