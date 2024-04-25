#include "raylib.h"

int main()
{
    // setting target fps
    SetTargetFPS(60);

    //window dimension
    const int windowWidth{512};
    const int windowHeight{380};
    //initialize the window 
    InitWindow(windowWidth, windowHeight, "My Game Window");

    //acceleration due to gravity (pixels/frame)/frame
    const int gravity{1};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2; 
    scarfyPos.y = windowHeight - scarfyRec.height; 

    //boolean check if rectangle is in air
    bool isInAir = false;
    //jump velocity
    const int jumpVel{-22};


    int velocity{0};
    

    while (!WindowShouldClose())
    {
        //start drawing 
        BeginDrawing();
        ClearBackground(WHITE);

        
        //perform ground check
        if(scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            //rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else 
        {
            //rectangle in in the air 
            //apply gravity
            velocity += gravity;
            isInAir = true;
        }

        //jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir) 
        {
            velocity += jumpVel;
        }


        //update Y position
        scarfyPos.y += velocity;

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE); 

        //stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    CloseWindow();
}