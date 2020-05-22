#include "raylib.h"

// Screen size
const int screenWidth = 800;
const int screenHeight = 450;
 
// Switching between screens
bool choice = true;
bool menu = false;

// PaddleA variables
Rectangle paddleA = {0,225,20,100};
Vector2 paddleAspeed = {5,5};

// paddleB variables
Rectangle paddleB = {780,225,20,100};    
Vector2 paddleBspeed = {5,5};
    
// Pong ball using vectors
Vector2 ballposition = {400,225}; 
Vector2 ballspeed = {5,0};
const float ballradius = 10;

// scores
int playerAscore = 0;
int playerBscore = 0;

// Colours
Color select1 = RAYWHITE;
Color select2 = RAYWHITE;

float angle = 0; 
bool goal = true;
// Collision variables
bool collision1 = false;
bool collision2 = false;
 
void computer()
{
 // Computer paddle
 if ((paddleB.y+50) <= ballposition.y ) paddleB.y += paddleBspeed.y;
 if (paddleB.y >= (GetScreenHeight()-paddleA.height)) paddleB.y = (GetScreenHeight()-paddleA.height);  
 if ((paddleB.y+50) >= ballposition.y ) paddleB.y -= paddleBspeed.y;
 if (paddleB.y <= 0) paddleB.y = 0;
 
}
void multiplayer()
{
 // PaddleB movement
 if (IsKeyDown(KEY_UP)) paddleB.y -= paddleBspeed.y;
 if (paddleB.y <= 0) paddleB.y = 0;     
 if (IsKeyDown(KEY_DOWN)) paddleB.y += paddleBspeed.y;
 if (paddleB.y >= (GetScreenHeight()-paddleA.height)) paddleB.y = (GetScreenHeight()-paddleA.height);   
}
void gamedraw()
{
 // Drawing game screen
 BeginDrawing();
 ClearBackground(BLACK);
 DrawRectangleRec(paddleA, RAYWHITE);
 DrawRectangleRec(paddleB, RAYWHITE);
 for(int i = 10; i<425; i+=25)DrawRectangle(390,i,10,5,RAYWHITE);        
 DrawCircleV(ballposition, ballradius, RAYWHITE);
 DrawText(FormatText("%d   %d",playerAscore,playerBscore),280,10,100,RAYWHITE);   
 EndDrawing(); 
}
void menudraw()
{   
 // Menu controls
 if(IsKeyPressed(KEY_W))
 {
  choice = true;         
  select1 = RED;
  select2 = RAYWHITE;    
 }  
    
 if(IsKeyPressed(KEY_S))
 {
  choice = false; 
  select1 = RAYWHITE;
  select2 = RED; 
 }
 
 // Drawing menu
 BeginDrawing();
 ClearBackground(BLACK);
 DrawText("PONG 2",50,50,100,RAYWHITE);
 DrawText("Single-Player",50,200,50,select1); 
 DrawText("Multi-Player",50,350,50,select2);
 DrawText("BACKSPACE -",450,210,25,RAYWHITE);
 DrawText("RETURN \n TO \n MENU",650,210,25,RAYWHITE);      
 DrawText("W - UP",450,260,25,RAYWHITE);     
 DrawText("S - DOWN",450,310,25,RAYWHITE);
 DrawText("ENTER - SELECT",450,360,25,RAYWHITE);            
 EndDrawing();     
}
void pongdata()
{ 
if(ballspeed.x >= 18) ballspeed.x = 18;         
 // ball starts to move on spacebar
 if(!goal)
 {
     ballposition.x += ballspeed.x;
     ballposition.y += ballspeed.y;
 }
if(IsKeyPressed(KEY_SPACE)) goal = false; 

 // PaddleA controls
 if (IsKeyDown(KEY_W)) paddleA.y -= paddleAspeed.y;        
 if (paddleA.y <= 0) paddleA.y = 0;     
 if (IsKeyDown(KEY_S)) paddleA.y += paddleAspeed.y;       
 if (paddleA.y >= (GetScreenHeight()-paddleA.height)) paddleA.y = (GetScreenHeight()-paddleA.height);      


 // Scoring plus ball and wall collision on x axis
 if (ballposition.x >= (GetScreenWidth() - ballradius))
   {                    
    playerAscore += 1;               
    ballposition.x = 400;
    ballposition.y = 200;
    goal = true;
    ballspeed.x = 5;
    ballspeed.y = 0;
   }
   
 if(ballposition.x <= ballradius)
   { 
    playerBscore += 1;
    ballposition.x = 400;
    ballposition.y = 200; 
    goal = true;
    ballspeed.x = 5;
    ballspeed.y = 0;
   }
   if(goal) DrawText("Serve using Spacebar",250,425,25,RAYWHITE);
   if(IsKeyPressed(KEY_SPACE)) goal = false;
 
 //Ball collision on y axis
 if ((ballposition.y > (GetScreenHeight() - ballradius)) || (ballposition.y < ballradius)) ballspeed.y *= -1.0f;                           
        
 // Collision with ball and paddles
 collision1 = CheckCollisionCircleRec(ballposition,ballradius,paddleA);
 collision2 = CheckCollisionCircleRec(ballposition,ballradius,paddleB);

 if(collision1)
 { 
  angle = (ballposition.y-(paddleA.y+50))/50;
  ballspeed.x *= -1.05f;      
  ballspeed.y = 6*angle;
 }
 
 if(collision2)
 {
  ballspeed.x *= -1.05f;      
  angle = (ballposition.y-(paddleB.y+50))/50;
  ballspeed.y = 6*angle;
 }    
       
 // Reset game when either score reaches 10
 if (playerAscore == 10 || playerBscore == 10) 
    {
     playerAscore = 0;
     playerBscore = 0;       
    } 
}
int main(void)
{
 // Initialization
 InitWindow(screenWidth, screenHeight, "Pong 2");
 SetTargetFPS(60);

while(!WindowShouldClose())
{
    if(!menu)
 {       
  menudraw();
  if(IsKeyPressed(KEY_ENTER)) menu = true;
 }      
   if(menu && choice)
 {
  pongdata();
  gamedraw();
  computer();
  if(IsKeyPressed(KEY_BACKSPACE)) menu = false;     
 }      
    if(menu && !choice)
 {
  pongdata();
  gamedraw();
  multiplayer();
  if(IsKeyPressed(KEY_BACKSPACE)) menu = false;  
 }      
    
    
    
}



    // De-Initialization
 CloseWindow();        // Close window and OpenGL context
 return 0;
}