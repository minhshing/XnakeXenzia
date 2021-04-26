
#include "Player2.h"
#include "Menu_Game.h"
#include "Icon.h"

SDL_Window* g_window =NULL;
SDL_Renderer *g_screen = NULL ;
SDL_Event g_event;


BaseObject g_background;
BaseObject g_background_menu;
BaseObject bkground_menuP2 ;
BaseObject img_control ;

Mix_Chunk *moving_sound[4] ;
Mix_Chunk *dead_sound  ;
Mix_Chunk *eating_sound;
Mix_Music *Music_1Player;



using namespace std;


bool Init(){

 bool success = true;

 SDL_Init(SDL_INIT_EVERYTHING);
 SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) ;
 if(TTF_Init() < 0)
        cout << "Error : " << TTF_GetError() <<endl;

 SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY , "1") ;

 g_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED ,
                                           SDL_WINDOWPOS_UNDEFINED ,
                                           SCREEN_WIDTH , SCREEN_HEIGHT,
                                           SDL_WINDOW_SHOWN             );
 if( g_window == NULL ) {
    success = false;
    cout << "Error : Window is NULL . " << endl;

 } else {


    g_screen = SDL_CreateRenderer(g_window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ;

    if(g_screen == NULL)

        success = false;
     else
      {
        SDL_SetRenderDrawColor(g_screen, 255, 255, 255 , 255) ;

        int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG ;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
          {
              cout << "SDL could not initialize ! SDL_image Error :" << endl;
              success = false;
          }
      }

    }

   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2,9000 ) < 0) {
     cout << "Error : " << Mix_GetError() <<endl;
     success = false;

   }


   return success;

}

bool Load_background()
{
    // Load background
    int ret = g_background.LoadIMG("Image/snake/ground.png" , g_screen );
    int ret1 = g_background_menu.LoadIMG("Image/snake/2.png", g_screen) ;
    int ret2 = bkground_menuP2.LoadIMG("Image/2Player/bkg3.jpg", g_screen);
    int ret3 = img_control.LoadIMG("Image/snake/control.png", g_screen);
    // Load Icon



    if( !ret || !ret1 || !ret2 || !ret3 )
    {
        cout << "Error : Load image background is failed ." <<endl;
        return false;
    }

  // Set width, height background
   g_background.SetSize(SCREEN_WIDTH,SCREEN_HEIGHT);
   g_background_menu.SetSize(SCREEN_WIDTH,SCREEN_HEIGHT) ;
   bkground_menuP2.SetSize(SCREEN_WIDTH,SCREEN_HEIGHT) ;

   SDL_QueryTexture(img_control.GetObject(),NULL,NULL,
                    &img_control.rect_.w, &img_control.rect_.h) ;
   img_control.SetRect(300,250);

  // Load music
   moving_sound[0] = Mix_LoadWAV("Sound/up.wav");
   moving_sound[1] = Mix_LoadWAV("Sound/down.wav") ;
   moving_sound[2] = Mix_LoadWAV("Sound/right.wav" );
   moving_sound[3] = Mix_LoadWAV("Sound/left.wav") ;

   dead_sound      = Mix_LoadWAV("Sound/dead.wav");
   eating_sound    = Mix_LoadWAV("Sound/eat.wav");
   Music_1Player   = Mix_LoadMUS("Sound/wholesome.mp3");


   for(int i=0; i<4; i++)
     if(moving_sound[i] == NULL)
       cout << "Error : Loading sound " << i << " is failed" <<endl;

   if(dead_sound == NULL || eating_sound == NULL || Music_1Player == NULL)
      cout << "Error : Loading sound is failed" <<endl;

    return true;
}

void close()
{
    g_background.Free();
    g_background_menu.Free();
    img_control.Free();
    bkground_menuP2.Free();

    SDL_DestroyRenderer(g_screen) ;

    g_screen = NULL;

    SDL_DestroyWindow(g_window) ;
    g_window = NULL;

    for(int i=0; i<4 ; i++) {
      Mix_FreeChunk(moving_sound[i]);
      moving_sound[i] = NULL;
    }
    Mix_FreeChunk(eating_sound);
    Mix_FreeChunk(dead_sound);
    Mix_FreeMusic(Music_1Player);

    eating_sound = NULL;
    dead_sound   = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

int main(int argc, char *argv[])
{
  // Initial SDL2 and background
    srand(time(NULL));

    if( Init() == false)
       return -1;
    if( Load_background() == false)
        return -1;
    bool running = true;
    bool pauseP1 = false ;
    bool pauseP2  = false;

    bool play1   = false ;
    bool draw_imgControl = true;
    bool sound   = true;
    bool draw_textG_overP1 = false;
    bool playMusicP2 = true;


  // Set up Keyboard

   Snake snake ;
   snake.Setup(g_screen);

   const Uint8 *keyState = nullptr;

 // Set up FPS
   float delta ;
   Uint32 preTime , currentTime =0;
   float time_over = 0.f;

  // Create Font and Text
   TTF_Font* font_score = TTF_OpenFont("font/VNI-Souvir.TTF",27) ;
   TTF_Font* font_menu = TTF_OpenFont("font/File-Bold.ttf", 60) ;
   TTF_Font* font_G_over = TTF_OpenFont("font/File-Bold.ttf", 75) ;
   TTF_Font* font_p2_score = TTF_OpenFont("font/starcraft.ttf", 20);
   TTF_Font* font_time = TTF_OpenFont("font/starcraft.ttf", 20);
   TTF_Font* font_     = TTF_OpenFont("font/File-Bold.ttf", 35);

   if( font_score == NULL )
        cout << "Error : Null font ." <<endl;
   TextObject text;
   text.setText_Color(WHITE_COLOR);

    bool Call_menu = true;
    bool Play_2 = false;

     Menu_Game menu(g_screen);
     Player2 player_2(g_screen);

     Icon icon;
     icon.Initial_iconP1(g_screen);
     icon.set_iconP1();

     float effect_time = 0.f;


 // Loop
  while( running ) {

       // delta time
          preTime = currentTime;
          currentTime = SDL_GetTicks() ;
          delta = (currentTime - preTime)/1000.f;



    while( SDL_PollEvent(&g_event))
    {
        // Handling icon menu

      menu.Handle_event(g_event,running, Call_menu, play1, snake,Play_2, player_2, time_over,pauseP1) ;
        // Handling icon play, replay
      if(play1) {
        icon.Check_iconP1(snake,g_event,pauseP1,time_over, Call_menu, play1, menu.xMouse,menu.yMouse,sound);

        if(snake.game_over)
         icon.Handle_GameOverP1(snake,g_event,Call_menu, menu.xMouse,menu.yMouse,time_over, running);
      }
      if(Play_2)
        menu.Check_menuP2(player_2,g_event,pauseP2,running,Call_menu,Play_2,play1,playMusicP2);



    }
      keyState = SDL_GetKeyboardState(NULL);

      // Draw menu game

      if(Call_menu  == true )               // Menu chính, chọn chế độ chơi
      {


        SDL_RenderClear(g_screen);
        g_background_menu.Render(g_screen);
        menu.Draw_Menu(g_screen, font_menu,play1);

        SDL_RenderPresent(g_screen) ;


          Mix_PauseMusic();
          Mix_HaltMusic();

      } else if( Play_2 == true && !Call_menu ) {

        if(!Mix_PlayingMusic() && playMusicP2)
         Mix_PlayMusic(Music_1Player,-1);


        if(player_2.game_over == false) {

           SDL_RenderClear(g_screen);

           if(pauseP2 == false) {    // Đang trong chế độ 2 người

              player_2.Draw_player2(g_screen,font_time,font_p2_score,delta,pauseP2);
              player_2.Snake_moving(keyState,pauseP2) ;
              player_2.Update_p2(delta,pauseP2);
              menu.Draw_iconP2(g_screen);


            } else {                                // Gọi menu mode 2 người
              bkground_menuP2.Render(g_screen);
              menu.Draw_menuP2(g_screen,pauseP2) ;

           }

        } else {

          SDL_RenderClear(g_screen);
          player_2.Draw_player2(g_screen,font_time,font_p2_score,delta,pauseP2);

          menu.DrawGame_OverP2(player_2,g_screen,font_G_over,font_);


        }


         SDL_RenderPresent(g_screen);
     } else if(play1 == true ) {             // Mode 1 người chơi
        // get previous state

          Mix_PauseMusic();
          Mix_HaltMusic();

          if( snake.state != None) snake.preState = snake.state;

          snake.play_sound = sound;


          // Set text score
          string str_score = to_string(snake.score);



          SDL_RenderClear(g_screen);

          if( snake.game_over == false) {
             g_background.Render(g_screen);

            //  menu.Draw_icon(g_screen, pause) ;
             icon.Draw_iconP1(g_screen, pauseP1, sound);
             snake.Draw(g_screen,delta);
             snake.Move(keyState, pauseP1,moving_sound,draw_imgControl) ;
             snake.Update(delta ,eating_sound, dead_sound);

             draw_textG_overP1 = false;
             icon.Draw_textScoreP1(g_screen,font_score,font_G_over,snake,draw_textG_overP1);



          } else {
              time_over += delta;
              if(time_over <= 2.f) {

                g_background.Render(g_screen);
                icon.Draw_iconP1(g_screen, pauseP1, sound);
                snake.Draw(g_screen,delta);

                snake.Update(delta ,eating_sound, dead_sound);
                icon.Draw_textScoreP1(g_screen,font_score,font_G_over,snake,draw_textG_overP1);
                snake.Draw_effect(g_screen,delta);

             }else {
               icon.Draw_gameOverP1(g_screen,snake);       // Khi game over

               draw_textG_overP1 = true;
               icon.Draw_textScoreP1(g_screen,font_score,font_G_over,snake, draw_textG_overP1);
            }
         }


         if(draw_imgControl)
            img_control.Render(g_screen);


         SDL_RenderPresent(g_screen) ;
     }

  }



    close() ;
    snake.~Snake();
    menu.~Menu_Game();
    player_2.~Player2();
    icon.~Icon();

    return 0;
}



