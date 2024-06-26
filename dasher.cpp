#include "raylib.h"

struct AnimData
{
    Rectangle rec; 
    Vector2 pos;
    int frame; 
    float updateTime;
    float runningTime;
};

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

    //AnimData for nebula
    AnimData nebData
    { 
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {windowWidth, windowHeight - nebula.height/8}, // Vecto2 pos
        0, // int frame 
        1.0/12.0, // float updateTikme
        0 // float runningTime
    };

    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8}; 
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    //AnimData for nebula 2 
    AnimData neb2Data
    {
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {windowWidth + 300, windowHeight - nebula.height/8}, // Vecto2 pos
        0, // int frame 
        1.0/16.0, // float updateTikme
        0 // float runningTime
    };

    Rectangle neb2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 neb2Pos{windowWidth + 300, windowHeight - nebRec.height};

    //nebula animation variables
    int nebFrame{};
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    int neb2Frame{};
    const float neb2UpdateTime{1.0/16.0};
    float neb2RunningTime{};

    //nebula X velocity (pixels/sec)
    int nebVel{-200};

    //scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2; 
    scarfyPos.y = windowHeight - scarfyRec.height; 



    //animation frame scarfy
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


        //update nebula position
        nebPos.x += nebVel * dT;
        //update the 2nd nebula position
        neb2Pos.x += nebVel * dT; 

        //update scarfy position
        scarfyPos.y += velocity * dT;

        //update scarfy animaton frame
        if(!isInAir)
        {
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
        }

        //update nebula animation frame
        nebRunningTime += dT;
        if(nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            nebRec.x = nebFrame * nebRec.width; 
            nebFrame++; 
            if(nebFrame > 7)
            {
                nebFrame = 0; 
            }
        }

        //update nebula animation frame
        neb2RunningTime += dT;
        if(neb2RunningTime >= neb2UpdateTime)
        {
            neb2RunningTime = 0.0;
            neb2Rec.x = neb2Frame * neb2Rec.width; 
            neb2Frame++; 
            if(neb2Frame > 7)
            {
                neb2Frame = 0; 
            }
        }
        

        //draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        //draw 2nd nebula
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);
        
        //draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE); 

        //stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    UnloadTexture(nebula);
    CloseWindow();
}