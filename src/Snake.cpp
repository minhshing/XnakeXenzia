#include "Snake.h"

// Snake _________________________________________________________________________________




Snake::Snake( )
{
   // Set up Snake

    length_snake =2;
    state = None ;

    PressKey = true;
    paralyze = false;

    score =0;
    frameTime    = 0.f;
    timeParalyze = 0.f;
    timeApple    = 0.f;
    timeCollide  =0.f;


    num[0].x = 2;
    num[0].y = num[1].y = 1 ;
    num[1].x = num[0].x -1;


    key[0] = SDL_SCANCODE_W;
    key[1] = SDL_SCANCODE_S;
    key[3] = SDL_SCANCODE_A;
    key[2] = SDL_SCANCODE_D;
    key[4] = SDL_SCANCODE_SPACE ;
    key[5] = SDL_SCANCODE_UP;
    key[6] = SDL_SCANCODE_DOWN;
    key[8] = SDL_SCANCODE_LEFT;
    key[7] = SDL_SCANCODE_RIGHT;

    draw_back[0] = draw_back[1] = false;
    play_sound = true;
    collide_barrier = false;
    collide_body  = false;
    game_over = false;

    color = Red;

    mode_game[0] = true;
    mode_game[1] = false;
    mode_game[2] = false;

    num_barrier =0;

    for(int i=0; i<3 ; i++)
      highest_score[i] =0;


}

void Snake::Setup(SDL_Renderer* render) {
   if( this->LoadIMG("Image/snake/whiteb.png", render) == false )
      std::cout << "Error : Load Snake image is failed ." <<std::endl;

    rect_.w = rect_.h = Size ;
 // Load image fruit and set position

   if( fruit[0].LoadIMG("Image/icon/fruit.png", render) == false )
      std::cout << "Error : Load fruit image is failed ." <<std::endl;
   if( fruit[1].LoadIMG("Image/icon/fruit.png", render) == false )
      std::cout << "Error : Load fruit image is failed ." <<std::endl;

   int a,b ;
   SDL_QueryTexture(fruit[0].GetObject(), NULL, NULL, &a, &b);

   fruit[0].SetSize(Size,Size);
   fruit[0].x = 15;
   fruit[0].y = 2;

   fruit[0].cropRect.w =a/14;
   fruit[0].cropRect.h = b;
   fruit[0].cropRect.x = 0;
   fruit[0].cropRect.y = 0;

   fruit[1].SetRect(Size-15 ,Size-20);
   fruit[1].SetSize(Size+12,Size+12);

 // Load snake's head image

   int ret1 = head_state[0].LoadIMG("Image/snake/head_up.png", render);
   int ret2 = head_state[1].LoadIMG("Image/snake/head_down.png", render);
   int ret3 = head_state[2].LoadIMG("Image/snake/head_right.png", render);
   int ret4 = head_state[3].LoadIMG("Image/snake/head_left.png", render);
   int ret5 = head_state[4].LoadIMG("Image/snake/whiteb.png", render);

   if(!ret1 || !ret2 || !ret3 || !ret4 || !ret5)
    cout << "Error : Load image for snake's head is failed." <<endl;

   for(int i=0; i<5; i++) {
    head_state[i].rect_.w = head_state[i].rect_.h = Size;

   }
    head_state[4].rect_.x = (num[0].x+1)*Size;
    head_state[4].rect_.y = (num[0].y+3)*Size;

  // Load barrier image

   if( barrier.LoadIMG("Image/snake/barrier.png", render) == false )
     cout << "Error : load barrier image is failed." <<endl;

   barrier.SetSize(Size,Size);

 // Load effect image
   if( effect[0].LoadIMG("Image/snake/effect.png", render) == false )
     cout << "Error : load effect image is failed." <<endl;

   if( effect[1].LoadIMG("Image/snake/effect1.png", render) == false )
     cout << "Error : load effect image is failed." <<endl;

   SDL_QueryTexture(effect[0].p_object,NULL,NULL,&effect[0].frameW,&effect[0].frameH);
   effect[0].cropRect.h =  effect[0].rect_.h = effect[0].frameH/15;
   effect[0].cropRect.w =  effect[0].rect_.w = effect[0].frameW;

   effect[0].cropRect.x = effect[0].cropRect.y =0;

   SDL_QueryTexture(effect[1].p_object,NULL,NULL,&effect[1].frameW,&effect[1].frameH);

   effect[1].cropRect.h = effect[1].rect_.h  = effect[1].frameH;
   effect[1].cropRect.w =  effect[1].rect_.w = effect[1].frameW/15;

   timeEffect   = 0.f;
}



void Snake::SetFruitPos()
{
    bool checkPos = true;

    int x,y;
    while( checkPos ) {

       int counter =0;
        x = rand() % W;
        y = rand() % H;

     for(int i=0; i<length_snake ; i++ )
          if(x == num[i].x && y == num[i].y)
            counter ++;

     for(int i=0; i<num_barrier ; i++ )
          if(x == Barriers[i].x && y == Barriers[i].y)
            counter ++;


       if(counter == 0)
        checkPos = false;

    }

        fruit[0].x  = x;
        fruit[0].y  = y;

}

void Snake::SetPos_barrier()
{
    bool checkPos = true;

    int x,y;
    while( checkPos ) {

       int counter =0;
        x = rand() % W;
        y = rand() % H;

     for(int i=0; i<num_barrier ; i++ )
          if(x == Barriers[i].x && x == Barriers[i].y)
             counter ++;


     for(int i=0; i<length_snake; i++)
         if(x == num[i].x && y == num[i].y)
            counter ++;

         if(x == fruit[0].x && y== fruit[0].y)
            counter ++;


         if(counter == 0)
            checkPos = false;

    }

        Barriers[num_barrier-1].x  = x;
        Barriers[num_barrier-1].y  = y;


}

void Snake::Draw(SDL_Renderer *render, float delta)
{
  // Draw head

      rect_.x = (num[0].x +1)*Size;
      rect_.y = (num[0].y +3 )*Size;

   if(state != None)  {

     for(int i=0; i<4; i++)
       if(state == i && PressKey) {
          head_state[i].rect_ = rect_;
          head_state[i].Render(render);
      }

   } else {
       head_state[4].rect_ = rect_;
       head_state[4].Render(render);

   }





   // Draw body

     if(color == Red)
        SDL_SetTextureColorMod(p_object,255,0,0);
     else if(color == White)
        SDL_SetTextureColorMod(p_object,255,255,255);
     else if(color == Green)
         SDL_SetTextureColorMod(p_object,0,180,0);
     else if(color == Orange)
         SDL_SetTextureColorMod(p_object,255,165,0);
     else if(color == Blue)
         SDL_SetTextureColorMod(p_object,65,0,255);


   for(int i=1; i< length_snake ; i++)
   {
      rect_.x = (num[i].x +1)*Size;
      rect_.y = (num[i].y +3 )*Size;
      this->Render(render);

      rect_.x = (num[0].x +1)*Size;
      rect_.y = (num[0].y +3 )*Size;

   }

  if(timeApple <= 0.1f) fruit[0].increase_size = true;
  if(timeApple >  0.9f) fruit[0].increase_size = false;

 /// Draw fruit

    int a = (1+fruit[0].x)*Size;
    int b = (3+fruit[0].y)*Size;


  if( state != None)   {

   if( fruit[0].increase_size )
     timeApple += delta;
   else
     timeApple -= delta;

     if( timeApple<= 0.2f) {
         fruit[0].SetSize(Size+3,Size+3);
         fruit[0].Render(render,&fruit[0].cropRect);

     }
     else if(timeApple >0.2f  && timeApple <= 0.4f )
     {
         fruit[0].SetSize(Size+6,Size+6);
         fruit[0].Render(render,&fruit[0].cropRect);
         fruit[0].SetRect(a-2,b-4);
     } else if(timeApple >0.4f  && timeApple <= 0.6f )
     {
         fruit[0].SetSize(Size+9,Size+9);
         fruit[0].SetRect(a-3,b-5);
         fruit[0].Render(render,&fruit[0].cropRect);
     } else if(timeApple >0.6f  && timeApple <= 0.8f )
     {
         fruit[0].SetSize(Size+12,Size+12);
         fruit[0].SetRect(a-4,b-6);
         fruit[0].Render(render,&fruit[0].cropRect);
     } else if(timeApple >0.8f )
     {
         fruit[0].SetSize(Size+16,Size+16);
         fruit[0].SetRect(a-5,b-7);
         fruit[0].Render(render,&fruit[0].cropRect);
     }

  } else {
         fruit[0].SetSize(Size+4,Size+4);
         fruit[0].SetRect(a-2,b-2);
         fruit[0].Render(render,&fruit[0].cropRect);
  }

  fruit[1].cropRect = fruit[0].cropRect;
  fruit[1].Render(render,&fruit[1].cropRect);


  /// Draw barriers

   if(mode_game[2])
     for(int i=0; i<num_barrier; i++) {
        barrier.rect_.x = (Barriers[i].x +1)*Size;
        barrier.rect_.y = (Barriers[i].y +3)*Size;

        barrier.Render(render);
     }


}

void Snake::Update( float delta, Mix_Chunk *eat, Mix_Chunk *dead)
{
  // set mode game

    if(mode_game[0] == true)
        speed = 0.15f;
    else if(mode_game[1] == true)
        speed = 0.09f;
    else if(mode_game[2] == true) {

        speed = 0.14f;
    }

    frameTime += delta;
 if( frameTime >= speed) {

 // Get Score
   if( num[0].x == fruit[0].x && num[0].y == fruit[0].y)
   {
      SetFruitPos();
      score++;
      length_snake ++;


      if(play_sound)
          Mix_PlayChannel(1,eat, 0) ;

   // set score and highest score for each mode
      if(mode_game[0] == true) {
        if(score > highest_score[0] )
            highest_score[0] = score;

      } else if(mode_game[1] == true) {
        if(score > highest_score[1] )
            highest_score[1] = score;


     }else if(mode_game[2] == true) {            // set barrier position

          if(score == 1) {
            num_barrier = 1;
            SetPos_barrier();
         }else if(score >1 && score%2 != 0) {
            num_barrier ++;
            SetPos_barrier();
        }

        if(score > highest_score[2])
            highest_score[2] = score;

      }

   }

  // FPS
      frameTime =0.f;

  // Update snake

    for(int i=0; i<5; i++) {
        if(state == i) {
          head_state[i].rect_.x = (num[0].x+1)*Size;
          head_state[i].rect_.y = (num[0].y+3)*Size;
        }
    }

    if( state != None && !game_over)   {
      for(int i= length_snake+1; i>0  ; i--)
          num[i] = num[i-1];
    }

    if( state == Up )
        num[0].y --;
    else if( state == Down )
        num[0].y ++;
    else if( state == Right )
        num[0].x ++;
    else if( state == Left )
        num[0].x --;


 }


  /// Game over

  // Handle collide with body

   if(collide_body ) {
      if(play_sound)
         Mix_PlayChannel(0,dead,0);   // Play sound

      collide_body = false;
   }

   if(draw_back[0]) {            // draw back
     timeCollide += delta;
                                // snake's head took two space back
     if(timeCollide >= 0.3f) {
        num[0] = num[2];
        num[2] = num[3];
        num[1] = num[3];
        draw_back[0] = false;
        timeCollide = 0.f;
     }

   }


   for(int i=1; i<length_snake ; i++)
     if(num[0].x == num[i].x && num[0].y == num[i].y)
      {
           state = None;
           game_over = true;
           collide_body = true;

           num[0] = num[1];
           num[1] = num[2];
           draw_back[0] = true;
     }


  // Handle collide with barrier

   if(collide_barrier && draw_back[1]) {
     timeCollide += delta;

     if(timeCollide >= 0.3f) {
       for(int i= 0; i<length_snake  ; i++) {
         num[i] = num[i+1];                       // Snake lùi 1 ô  lần 2

      }
      draw_back[1] = false;
      timeCollide = 0.f;

     }
  }


  if(num[0].x <0 || num[0].x>=W || num[0].y <0 || num[0].y >=H ) {

           state = None;
           game_over = true;
           collide_barrier = true;
           draw_back[0] = draw_back[1] = true;
  }

  if(mode_game[2] == true)  {

     for(int i=0; i<num_barrier; i++)
        if(num[0] == Barriers[i]) {
            state = None;
            game_over = true;
            collide_barrier = true;
            draw_back[0] = draw_back[1] = true;
        }
  }

   if( collide_barrier && draw_back[0]) {
     for(int i= 0; i<=length_snake  ; i++) {
       num[i] = num[i+1];                           // Snake lùi 1 ô lần 1

     }
     draw_back[0] = false;

     if(play_sound)
        Mix_PlayChannel(0,dead,0);
   }

}

void Snake::Handle_border( int w, int h)
{

    if(num[0].x <0 && state == Left) {
       num[0].x = w-1;
       PressKey = false;
    }

    if(num[0].x >=w && state == Right) {
        num[0].x = 0;
        PressKey = false;
    }


    if(num[0].y <0 && state == Up) {
        num[0].y = h-1;
        PressKey = false;
    }


    if(num[0].y >=h && state == Down) {
        num[0].y = 0;
        PressKey = false;
    }


    if(num[0].x >=0 && num[0].x <w && num[0].y >=0 && num[0].y < h)
        PressKey = true;

}

void Snake::Move(const Uint8 *keyState , bool pause, Mix_Chunk *moving[4], bool &draw_imgControl, bool dead)
{



 if( PressKey && !pause  && !game_over  )       {

   if(( keyState[key[0]] || keyState[key[5]]) && state != Down && state != Up)           {
         state = Up;
         draw_imgControl = false;

      if(moving != NULL && play_sound)
          Mix_PlayChannel(0,moving[0], 0) ;



   }else if((keyState[key[1]] ||keyState[key[6]] )  && state != Up && state != Down && !dead)    {
          state = Down;
          draw_imgControl = false;

       if(moving != NULL && play_sound)
          Mix_PlayChannel(0,moving[1], 0) ;

   } else if((keyState[key[3]] || keyState[key[8]]) && state != Right && state != Left && !dead){
          state = Left;
          draw_imgControl = false;

        if(moving != NULL && play_sound)
          Mix_PlayChannel(0,moving[3], 0) ;

    } else if((keyState[key[2]] || keyState[key[7]]) && state != Left && state != Right && !dead) {
          state = Right;
          draw_imgControl = false;

        if(moving != NULL && play_sound)
          Mix_PlayChannel(0,moving[2], 0) ;
    }

   // for 2 player mode

    if(keyState[key[4]]  && num_mana > 0 )
        speedUp = true;
    else
        speedUp = false;

    }


}

void Snake:: Reset_game()
{
    SetFruitPos();
    length_snake =2;

    num[0].x = 2;
    num[0].y = num[1].y = 1 ;
    num[1].x = num[0].x -1;

    rect_.w = rect_.h = Size ;

    state = None ;
    PressKey = true;

    score =0;
    frameTime = 0.f;
    timeApple = 0.f;
    timeCollide =0.f;
    timeEffect   = 0.f;

    num_barrier =0;

    game_over = false;
    collide_barrier = false;

}

void Snake::Draw_effect(SDL_Renderer *render, float& delta) {

 /// When game over

     timeEffect += delta;
     effect[0].cropRect.x =  effect[1].cropRect.y=0;

    if(preState == Left || preState == Right) {

       effect[0].rect_.x = num[0].x*Size;
       effect[0].rect_.y =  (num[0].y+1)*Size;

   } else  if(preState == Up || preState == Down) {
       effect[1].rect_.x =  (num[0].x-1)*Size;
       effect[1].rect_.y =  (num[0].y+2)*Size;
   }


  if(timeEffect <= 0.3f)  {

      effect[0].cropRect.y = effect[1].cropRect.x=0;

      if(preState == Left || preState == Right)
          effect[0].Render(render,&effect[0].cropRect);
      else  if(preState == Up || preState == Down)
          effect[1].Render(render,&effect[1].cropRect) ;

  } else if(timeEffect <= 0.6f) {

      effect[0].cropRect.y =  effect[1].cropRect.x =7*189;     ///cropRect.h = 189;

      if(preState == Left || preState == Right)
          effect[0].Render(render,&effect[0].cropRect);
      else
          effect[1].Render(render,&effect[1].cropRect) ;
  }




}

Snake::~Snake()
{
    Free();
    fruit[0].Free();

    for(int i=0; i<5; i++)
       head_state[i].Free();

    barrier.Free();

}


// Snake  _________________________________________________________________________




