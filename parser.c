#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

void LinearEquation(float Slope, float Ypoint);

char equation[100];
int win_width  = 1280;
int win_height =  960;

struct Coordinate{
    float x;
    float y;
} center;

int main(){ 
    center.x = win_width / 2;
    center.y = win_height / 2;

    printf("write your mathmatical equation here: ");
    fgets(equation, 100, stdin);

    for (int i = 0; equation[i] != 0; i++){
        printf("%c", equation[i]);
    }

    // get math expression and pitch
    float x_pitch = 100.0;
    float y_pitch = 100.0;
    
    Vector2 start = (Vector2){center.x - (win_width + (1.0 * x_pitch)), center.y + (win_height)};
    
    Vector2 end = (Vector2){center.x + (win_width), center.y - (win_height + (1.0 * y_pitch))};

    InitWindow(win_width, win_height, "math parser");

    Camera2D cam = { 0 };
	cam.zoom = 1;

        // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // translate based on right click
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f / cam.zoom);

			cam.target = Vector2Add(cam.target, delta);
		}

        // zoom based on wheel
		float wheel = GetMouseWheelMove();
		if (wheel != 0)
		{
			// get the world point that is under the mouse
			Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam);
			
			// set the offset to where the mouse is
			cam.offset = GetMousePosition();

			// set the target to match, so that the camera maps the world space point under the cursor to the screen space point under the cursor at any zoom
			cam.target = mouseWorldPos;

			// zoom
			cam.zoom += wheel * 0.125f;
			if (cam.zoom < 0.125f)
				cam.zoom = 0.125f;
		}
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            BeginMode2D(cam);
            // draw the 3d grid, rotated 90 degrees and centered around 0,0 just so we have something in the XY plane
            rlPushMatrix();
            rlTranslatef(0, 25 * 50, 0);
            rlRotatef(90, 1, 0, 0);
            DrawGrid(100, 50);
            rlPopMatrix();


            LinearEquation(2, 1);

            DrawCircle(0, 0, 50, RED);
            DrawText("center", -33, -10, 20, GRAY);

            DrawText(equation, 190, 200, 20, GRAY);
            //DrawLineV(start, end, GRAY);

            // draw y coordinate line
            DrawLine(win_width / 2, 0, win_width / 2, win_height, GRAY);
            DrawText("y", (win_width / 2) + 6, 4, 20, GRAY);
            // draw x coordinate line
            DrawLine(0, win_height / 2, win_width, win_height / 2, GRAY);
            DrawText("x", 10, (win_height / 2) + 6, 20, GRAY);

            EndMode2D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;

}

// default linear equation: y = Slope * x + Ypoint (y=mx+t)
void LinearEquation(float Slope, float Ypoint){

    // TODO switch to scale Vector
    float x_start_point = 0;
    float y_start_point = center.y + ((Slope * ((win_width / 2) * 1.0)) - Ypoint * 100.0);
    float x_end_point = win_width;
    float y_end_point = center.y + ((Slope * ((win_width / 2) * -1.0)) - Ypoint * 100.0);

    DrawLine(x_start_point, y_start_point, x_end_point, y_end_point, GRAY);
}