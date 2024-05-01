#include "raylib.h"

int main()
{
    //setting target fps
    SetTargetFPS(60);

    //window dimension
    const int windowWidth{512};
    const int windowHeight{380};
    //initialize the window 
    InitWindow(windowWidth, windowHeight, "My Game Window");

    //acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};


    //nebula variables 
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    //scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2; 
    scarfyPos.y = windowHeight - scarfyRec.height; 

    //animation frame
    int frame{}; // starts with 0 
    //amount of time before we update the animation frame
    const float updateTime{1.0/12.0}; 
    //running Time how much time passed since last update of animation 
    float runningTime{};
    

    //boolean check if rectangle is in air
    bool isInAir = false;
    //jump velocity (pixels/s)
    const int jumpVel{-600};


    int velocity{0};
    

    while (!WindowShouldClose())
    {
        //start drawing 
        BeginDrawing();
        ClearBackground(WHITE);

        //using delta time (time since last frame)
        const float dT {GetFrameTime()};

        
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
            velocity += gravity * dT;
            isInAir = true;
        }

        //jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir) 
        {
            velocity += jumpVel;
        }


        //update Y position
        scarfyPos.y += velocity * dT;
        //update running time 
        runningTime += dT; 
        if (runningTime >= updateTime)
        {
            runningTime = 0.0;
            //update animation frame 
            scarfyRec.x = frame * scarfyRec.width; 
            frame++;
            if (frame > 5)
            {
                frame = 0;  
            }
        }

        

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE); 

        //stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    UnloadTexture(nebula);
    CloseWindow();
}