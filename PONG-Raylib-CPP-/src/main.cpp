// #include<iostream>
// #include<raylib.h>


// int main()
// {
//     int ballX=400;
//     int ballY=400;
//     //  Color costomGreen = (20, 160, 133, 225);


//     InitWindow(800,800,"First raylib");
//     SetTargetFPS(60);
    
//     while (WindowShouldClose() == false)
//     {
//       //1. Event handling

//       //2. Updating Positios
//         if(IsKeyDown(KEY_RIGHT))
//         {
//             ballX += 4;
//         }
//        else if (IsKeyDown(KEY_LEFT))
//        {
//         ballX -= 4;

//        }
//         else if (IsKeyDown(KEY_UP))
//        {
//         ballY -= 4;

//        }
       
//         else if (IsKeyDown(KEY_DOWN))
//        {
//         ballY += 4;

//        }

//       //3.Drawing 
//      BeginDrawing();
//      ClearBackground(BLACK);
//      DrawCircle(ballX,ballY, 20, WHITE);
//      DrawLine(800,800,0,0,WHITE);
//      DrawRectangle(0,400,20,40,WHITE);

//      EndDrawing();
//     }
    
// CloseWindow();

//     return 0;
// }

#include<iostream>
#include<raylib.h>

using namespace std;

Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int  player_score = 0;
int cpu_score = 0;


class Ball
{

public:
float x,y;
int speed_x, speed_y;
int radius;

void Draw()
{
    DrawCircle(x,y,radius,Yellow);
}

void Update()
{
    x += speed_x;
    y += speed_y;

    if(y + radius >= GetScreenHeight() || y - radius <= 0 )
    {
       speed_y *= -1;
    }

    if(x + radius >= GetScreenWidth()) //
    {
        cpu_score++;
        ResetBall();
    }
     if( x - radius <= 0 )
    {
        player_score++;
        speed_x *= -1;
        ResetBall();
    }
}
 
void ResetBall()    // return ball to the center of the screen
{
    x = GetScreenWidth()/2;
    y = GetScreenHeight()/2;

    //Random direction in both X and Y axis
    int speed_choices[2] = { -1, 1};
    speed_x *= speed_choices[GetRandomValue(0, 1)];
    speed_y *= speed_choices[GetRandomValue(0, 1)];
}

};

class Paddle
{
    protected:
    void LimitMovement()
    {
           if(y <= 0)
        {
            y = 0;
        }

        if( y + height >= GetScreenHeight() )
        {
            y =  GetScreenHeight() - height;
            
        }

    }

    public:
    float x, y;
    float width,height;
    int speed;

    void Update()
    {
        if(IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }

        if(IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }

     LimitMovement();

    }

    void Draw()
    {
        
        DrawRectangleRounded(Rectangle{x, y, width, height} , 0.8, 0, WHITE);

    }


};

class CpuPaddle : public Paddle
{
    public:
    void Update(int ball_y)
    {
        if(y + height/2 > ball_y)
        {
            y = y - speed;
        }

        if(y + height / 2 <= ball_y )
        {
            y = y + speed;
        }

        LimitMovement();

    }
};

 Ball ball;
 Paddle player;
 CpuPaddle cpu;

 
int main()
{


    int const screenwidth = 1280;
    int const screenhight = 800;
   
   InitWindow(screenwidth,screenhight,"Ping Pong Game!");
   SetTargetFPS(60);

  ball.radius = 20;
  ball.x = screenwidth / 2;
  ball.y = screenhight / 2;
  ball.speed_x = 7;
  ball.speed_y = 7;

  player.width = 25;
  player.height = 120;
  player.x = screenwidth - player.width - 10;
  player.y = screenhight / 2 - player.height / 2;
  player.speed = 7;

 cpu.width = 25;
 cpu.height = 120;
 cpu.speed = 6;
 cpu.x = 10;
 cpu.y =  screenhight / 2 - cpu.height / 2;

   while (WindowShouldClose() == false )
   {
    
    BeginDrawing();
   //Updating
    ball.Update();
    player.Update();
    cpu.Update(ball.y);

    //Checking for collisions
    if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{player.x,player.y,player.width,player.height}))
  {
    ball.speed_x *= -1;
  }

     if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{cpu.x,cpu.y,cpu.width,cpu.height}))
  {
    ball.speed_x *= -1;
  }

    //Drawing
    ClearBackground(Dark_Green);
    DrawRectangle(screenwidth/2, 0, screenwidth/2 ,screenhight,Green);
    DrawCircle(screenwidth/2, screenhight/2, 150, Light_Green );
    // DrawCircle(screenwidth/2,screenhight/2,25,WHITE);
    DrawLine(screenwidth/2,0,screenwidth/2,screenhight,WHITE);
    ball.Draw();
    // DrawRectangle(10,screenhight/2-75,25,150,WHITE);
    player.Draw();
    //DrawRectangle(screenwidth-35,screenhight/2-75,25,150,WHITE);
    cpu.Draw();

    DrawText(TextFormat("%i",cpu_score), screenwidth/4 - 20, 20, 80, WHITE);
     DrawText(TextFormat("%i",player_score),3 * screenwidth/4 - 20, 20, 80, WHITE);
    


    EndDrawing();
    
   }
   

CloseWindow();

}

