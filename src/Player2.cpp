#include "Player2.h"
#include <time.h>
#include <stdlib.h>



void Player2::Load_imgItems(SDL_Renderer *render,Fruit *fruit,const std::string &s ,const int &num)
{
  for(int i=0; i<num ; i++) {

     if( fruit[i].LoadIMG(s.c_str(), render) == false )
        cout << "Error : Load  image is failed ." <<endl;

   }

}
void Player2::Initial_fruit(Fruit *item, const int &num)
{
     for(int i=0; i<num ; i++) {

       item[i].rect_.x = 60 + rand() % 50;
       item[i].rect_.y = 60 + rand() % 50;

       item[i].time_appear = 0.f;
       item[i].time_rePos = 0.f ;
       item[i].draw= false;

   }
}

Player2::Player2(SDL_Renderer *render)
{
  /// Load map and fruit

    int ret = background_p2.LoadIMG("Image/2Player/map6.png", render) ;
    int ret1 = back_ground.LoadIMG("Image/2Player/Image2.png", render) ;

    if(!ret || !ret1 )
        cout << "Error : Load image ." <<endl;

    back_ground.rect_.w = SCREEN_WIDTH;
    back_ground.rect_.h = SCREEN_WIDTH;

    num_cherry =4;
    score_level[0]= 3;
    score_level[1] =3;




  /// Load fruit's cherry

    Load_imgItems(render,cherry, "Image/2Player/cherry.png", 5) ;

    Load_imgItems(render,banana,"Image/2Player/banana.png" , 4);

    Load_imgItems(render,apple,"Image/2Player/apple.png", 3) ;

 /// Load mine
    Load_imgItems(render,stone,"Image/2Player/stone.png", 4) ;
    Load_imgItems(render,mine,"Image/2Player/boom.png", 3) ;
    Load_imgItems(render,gold, "Image/2Player/gold.png", 2);

    Load_imgItems(render,mushroom,"Image/2Player/mushroom.png",3);

    Initial_fruit(cherry,5);
    Initial_fruit(banana,4);
    Initial_fruit(apple,3);
    Initial_fruit(stone,4);
    Initial_fruit(mine,3);
    Initial_fruit(gold,2);
    Initial_fruit(mushroom,3);

    num_banana = 4 ;
    num_apple  = num_mushroom =3;
    num_cherry = 5 ;
    num_mine   = 3;
    num_stone  = 4 ;

  /// Load and set  heart image

    int a = heart[0].LoadIMG("Image/2Player/heart.png", render);
    int b = heart[1].LoadIMG("Image/2Player/heart.png", render);

    if(!a || !b)
        cout << "Load heart image is failed." <<endl;

    heart[0].rect_.x = Size2;
    heart[0].rect_.y = Size2;
    heart[0].rect_.w = heart[0].rect_.h = Size2;

    heart[1].rect_.x = Size2*25;
    heart[1].rect_.y = Size2;
    heart[1].rect_.w = heart[1].rect_.h = Size2;

    num_heart[0] = num_heart[1] =4;


 // set map

    SDL_QueryTexture(background_p2.GetObject(),NULL,NULL,
                     &background_p2.cropRect.w, &background_p2.cropRect.h) ;

    background_p2.cropRect.x = background_p2.cropRect.y =0;
    background_p2.cropRect.w /= 5;
    background_p2.cropRect.h /= 3;
    background_p2.rect_.w = background_p2.rect_.h = Size2;

 // set  snake

    s1.Setup(render);
    s2.Setup(render) ;
    s1.SetSize(Size2,Size2) ;
    s2.SetSize(Size2,Size2) ;

    for(int i=0; i<5; i++)
    {
    s1.head_state[i].SetSize(Size2,Size2);
    s2.head_state[i].SetSize(Size2,Size2);

    }

 // set  keyboard
    s2.key[0] = SDL_SCANCODE_UP;
    s2.key[1] = SDL_SCANCODE_DOWN;
    s2.key[3] = SDL_SCANCODE_LEFT;
    s2.key[2] = SDL_SCANCODE_RIGHT;
    s2.key[4] = SDL_SCANCODE_KP_0 ;


    s2.num[0].x = W_2 - 3 ;
    s2.num[1].x = W_2 -2;
    s2.num[0].y = s2.num[1].y =  H_2 -2 ;

    s2.head_state[4].rect_.x = s2.num[0].x;
    s2.head_state[4].rect_.y = s2.num[0].y;

    s1.speed = s2.speed = 0.18f;

 // set position apple
   for(int i=0; i<num_cherry ; i++)
   {
      cherry[i].draw = true;
      SetFruitPos(cherry[i]);

   }

    for(int i=0; i<3; i++)
    {
      SetFruitPos(stone[i]);
      stone[i].draw = true;

    }


 // set Text player

    text_player[0].SetRect(Size2*2, Size*1+40);
    text_player[1].SetRect(Size2*22, Size*1+40);

    text_time.setText_Color(WHITE_COLOR);
    text_time.SetRect(Size2*14, Size2*2);
    time_player =0.f;

 // Set mana
    bar_manaS1.Initial_mana(render);
    bar_manaS2.Initial_mana(render);
    s1.num_mana = s2.num_mana = 0;

}

void Player2::set_up()
{

   game_over = false;

   score_level[0]= 3;
   score_level[1] =3;

   time_player =0.f;

   num_heart[0] = num_heart[1] =4;

   dead[0] = dead[1] = false;

   s1.timeParalyze =  s2.timeParalyze = 0.f;
   s1.paralyze =false;
   s2.paralyze = false;

   s1.speedUp = s2.speedUp = false;
   s1.slowDown = s2.slowDown = false;
   s1.Reverse = s2.Reverse =false;
   s1.timeReverse = s2.timeReverse =0.f;

   s2.slow_time = s1.slow_time = 0.f;
   s1.speedUp_time = s2.speedUp_time = 0.f;

   s1.num_mana = s2.num_mana = 0;

   Initial_fruit(cherry,5);
   Initial_fruit(banana,4);
   Initial_fruit(apple,3);
   Initial_fruit(stone,4);
   Initial_fruit(mine,3);
   Initial_fruit(gold,2);

   s1.length_snake =2;
   s2.length_snake = 2;
   s2.num[0].x = W_2 - 3 ;
   s2.num[1].x = W_2 -2;
   s2.num[0].y = s2.num[1].y =  H_2 -2 ;


   s2.state = None;
   s2.score =0;

   s1.speed = s2.speed = 0.18f;

   s1.state = None;
   s1.score =0;

   s1.num[0].x = 2;
   s1.num[0].y = s1.num[1].y = 1 ;
   s1.num[1].x = s1.num[0].x -1;

    for(int i=0; i<num_cherry ; i++) {

      cherry[i].draw = true;
      SetFruitPos(cherry[i]);
    }

   for(int i=0; i< num_stone; i++) {

    SetFruitPos(stone[i]);
    stone[i].draw = true ;
   }
}

void Player2::Draw_item(SDL_Renderer *render, Fruit *f, const int & num)
{

    for(int i=0; i<num ; i++) {
       if(f[i].draw)
            f[i].Render(render);
     }

}


void Player2::Draw_player2(SDL_Renderer *render, TTF_Font *font1,  TTF_Font *font2, const float &time_val, bool &pauseP2)
{
    if( !pauseP2 ) {

      back_ground.Render(render);

      for(int i=0; i< H_2 ; i++)  {

        for(int j=0; j<W_2; j++) {

          background_p2.rect_.x = ( j+1)*Size2;
          background_p2.rect_.y = ( i+5 )*Size2;
          background_p2.Render(render, &background_p2.cropRect);

        }
    }

/// Draw player1
     // Draw snake 's head s1

    s1.rect_.x = (s1.num[0].x +1)*Size2;
    s1.rect_.y = (s1.num[0].y +5 )*Size2;

    if(!s1.paralyze) {

      for(int i=0; i<5; i++)
         if(s1.state == i  ) {
            s1.head_state[i].rect_ = s1.rect_;
            s1.head_state[i].Render(render);
          }

    } else {
        SDL_SetTextureColorMod(s1.GetObject(),255,255,255);
        s1.Render(render);
    }

   // Draw body
   for(int i=1; i< s1.length_snake ; i++)
   {

      SDL_SetTextureColorMod(s1.GetObject(),255,0,0);

      s1.rect_.x = (s1.num[i].x +1)*Size2;
      s1.rect_.y = (s1.num[i].y +5 )*Size2;
      s1.Render(render);

   // Vẽ lại đầu rắn khi đầu trùng vs thân

      s1.rect_.x = (s1.num[0].x +1)*Size2;
      s1.rect_.y = (s1.num[0].y +5 )*Size2;

      if(!s1.paralyze) {

        for(int i=0; i<5; i++)
          if(s1.state == i) {
           s1.head_state[i].rect_ = s1.rect_;
           s1.head_state[i].Render(render);
          }
      }

   }

  /// Draw heart s1,s2 ;


    for(int i=1; i<=num_heart[0]; i++) {
        heart[0].rect_.x = i*Size2;
        heart[0].Render(render);

    }

     for(int i=1; i<=num_heart[1]; i++) {
        heart[1].rect_.x = (29-i)*Size2+5;
        heart[1].Render(render);

    }



/// Draw player2
     // Draw snake 's head s2

    s2.rect_.x = (s2.num[0].x +1)*Size2;
    s2.rect_.y = (s2.num[0].y +5 )*Size2;

    if(!s2.paralyze) {

      for(int i=0; i<5; i++)
        if(s2.state == i) {
          s2.head_state[i].rect_ = s2.rect_;
          s2.head_state[i].Render(render);
         }

    } else {

        SDL_SetTextureColorMod(s2.GetObject(),255,255,255);
        s2.Render(render);
    }


   for(int i=1; i< s2.length_snake ; i++)
   {
      SDL_SetTextureColorMod(s2.GetObject(),0,128,0);
      s2.rect_.x = (s2.num[i].x +1)*Size2;
      s2.rect_.y = (s2.num[i].y +5 )*Size2;
      s2.Render(render);

    // Draw head again

      s2.rect_.x = (s2.num[0].x +1)*Size2;
      s2.rect_.y = (s2.num[0].y +5 )*Size2;

     if(!s2.paralyze) {

       for(int i=0; i<5; i++)
         if(s2.state == i) {
            s2.head_state[i].rect_ = s2.rect_;
            s2.head_state[i].Render(render);

         }
      }

   }

  // draw bar of mana

   bar_manaS1.Render_barMana(render,s1.num_mana ,1);
   bar_manaS2.Render_barMana(render,s2.num_mana, 2) ;

/// Draw Fruit and stone, mine...


    Draw_item(render,cherry,num_cherry);
    Draw_item(render, banana,num_banana) ;
    Draw_item(render, apple,num_apple) ;
    Draw_item(render, stone,4) ;
    Draw_item(render, mine,3) ;

    Draw_item(render,gold,2);
    Draw_item(render,mushroom,num_mushroom);

/// Draw  time and score text


    string str = "Score : ";
    string p1 = str + to_string(s1.score);
    string p2 = str + to_string(s2.score);

    text_player[0].SetText(p1);
    text_player[1].SetText(p2);

    for(int i=0; i<2 ;i ++) {
        text_player[i].setText_Color(YELLOW_COLOR);
        text_player[i].CreateGameText(font2,render);
        text_player[i].DrawTextA(render);
       }

   if( ! game_over)
        time_player += 1.0*time_val;

    Uint32 time = int(time_player);
    int m = time/60;
    int s = time%60;
    string str_m = to_string(m);
    string str_s = to_string(s);

    string str_time = str_m + " : " + str_s;

    text_time.SetText(str_time);
    text_time.CreateGameText(font1,render);
    text_time.DrawText(render);


    }
}

void Player2 ::Move_p2(Snake &s,const Uint8 *keyState , bool &pause, bool &dead)
{


   if( s.PressKey && !pause  && !s.game_over  )       {

   if( keyState[s.key[0]]  && s.state != Down && s.state != Up)            {
         s.state = Up;



   }else if(keyState[s.key[1]]   && s.state != Up && s.state != Down && !dead)    {
           s.state = Down;


   } else if(keyState[s.key[3]]  && s.state != Right &&  s.state != Left && !dead){
           s.state = Left;



    } else if(keyState[s.key[2]]  && s.state != Left && s.state != Right && !dead) {
           s.state = Right;

    }

    if(keyState[s.key[4]]  && s.num_mana > 0 )
        s.speedUp = true;
    else
        s.speedUp = false;

    }
}

void Player2::Snake_moving(const Uint8 *keyState , bool &pause) {

  Move_p2(s1,keyState,pause,dead[0]);
  Move_p2(s2,keyState,pause,dead[1]);


}

void Player2::Update_p2(const float &delta, bool &pauseP2)
{

 if(num_heart[0] ==0 || num_heart[1] == 0) {       // Nếu mạng = 0 thì game over

   if(num_heart[0] != 0)
      result = s1Win;
   else if(num_heart[1] != 0)
      result = s2Win;
   else {

     if(s1.score < s2.score)
        result = s2Win;
     else if(s1.score > s2.score)
        result = s1Win;
     else
        result = Tie;

   }


   game_over = true;

 }


 if( !pauseP2) {

   s1.frameTime += delta;
   s2.frameTime += delta;

   if(s1.paralyze )          // handle paralytic time
      paralyze_effect(s1,7.f,delta);




   if(s1.frameTime >=s1.speed )        // set position and time to appear of item
   {
     timeAppear_fruit(cherry,s1,0.15f , delta, 1,0,num_cherry);
     timeAppear_fruit(banana,s1,0.9f, delta ,3,0,num_banana) ;
     timeAppear_fruit(apple,s1,1.5f, delta ,5,0,num_apple) ;
     timeAppear_fruit(stone,s1, 0.8f, delta, 0,0,4);
     timeAppear_fruit(mine,s1 ,2.f, delta, 0,0,3);
     timeAppear_fruit(gold,s1,3.3f, delta, 10, 0,2);
     timeAppear_fruit(mushroom,s1,1.4f, delta, 0, 0, num_mushroom);

   }


 if( s1.frameTime >= s1.speed && !s1.paralyze) {

      s1.frameTime =0.f;

     for(int i=0; i<5; i++)
          if(s1.state == i && !s1.paralyze) {
          s1.head_state[i].rect_.x = (s1.num[0].x+1)*Size2;
          s1.head_state[i].rect_.y = (s1.num[0].y+5)*Size2;
          }


  /// Handle state s1

    if( s1.state != None)
      for(int i= s1.length_snake-1; i>0  ; i--)
        s1.num[i] = s1.num[i-1];

    if( s1.state == Up )
        s1.num[0].y --;
    else if( s1.state == Down )
        s1.num[0].y ++;
    else if( s1.state == Right )
        s1.num[0].x ++;
    else if( s1.state == Left )
        s1.num[0].x --;

   // s1 va cham s2

   for(int i=1; i<s2.length_snake ; i++) {

        if(s1.num[0] == s2.num[i] )
           handle_dead(s1);

    }


    if(s1.num[0].y < H_2)
        dead[0] = false;


  }


      if(s1.num[0] == s2.num[0]) {
           handle_dead(s1);
           handle_dead(s2);

      }


 // Handling snake 2 eat apple

     if(s2.paralyze )
        paralyze_effect(s2,7.f,delta);



    if(s2.frameTime >=s2.speed )
   {
     timeAppear_fruit(cherry,s2,0.15f , delta, 1,1, num_cherry);
     timeAppear_fruit(banana,s2,0.9f, delta ,3,1, num_banana) ;
     timeAppear_fruit(apple,s2,1.5f, delta ,5,1, num_apple) ;
     timeAppear_fruit(stone,s2, 0.8f, delta, 0, 1, 4);
     timeAppear_fruit(mine,s2 ,2.f, delta, 0, 1, 3 );
     timeAppear_fruit(gold,s2,3.3f, delta, 10, 1, 2);
     timeAppear_fruit(mushroom,s2,1.4f,delta,0,1, num_mushroom) ;

   }

   if( s2.frameTime >= s2.speed&& !s2.paralyze) {
      s2.frameTime =0;


  // Handle state s2

     for(int i=0; i<5; i++)
          if(s2.state == i ) {
          s2.head_state[i].rect_.x = (s2.num[0].x+1)*Size2;
          s2.head_state[i].rect_.y = (s2.num[0].y+5)*Size2;
          }





    if( s2.state != None)
      for(int i= s2.length_snake-1; i>0  ; i--)
        s2.num[i] = s2.num[i-1];


    if( s2.state == Up )
        s2.num[0].y --;
    else if( s2.state == Down )
        s2.num[0].y ++;
    else if( s2.state == Right )
        s2.num[0].x ++;
    else if( s2.state == Left )
        s2.num[0].x --;

  // s2 va cham s1
     for(int i=1; i<s1.length_snake ; i++) {

        if(s2.num[0] == s1.num[i] )
            handle_dead(s2);

    }



    if(s2.num[0].y < H_2)
        dead[1] = false;

   }

  /// Handle border

  if( !dead[0])
    s1.Handle_border(W_2,H_2);       // (w,h) -> with and height
  if(!dead[1])
    s2.Handle_border(W_2,H_2) ;


  } else {
   s1.state = None;
   s2.state = None;

  }



}

void Player2::timeAppear_fruit(Fruit *item, Snake &s,const float &time_appear,
                               const float &delta,const int &score, const int &index, const int &num)
{


   get_score(item, s,score,index,num);         // Increase score, length when snake eats fruit or gold

   get_effect(s, delta) ;

   for(int i=0; i<num ; i++) {

     if(item[i].draw == false) {
        item[i].time_appear += delta;
        item[i].time_rePos = 0.f    ;

     }else  {
       item[i].time_appear = 0.f   ;
       item[i].time_rePos += delta ;
     }

   }

   for(int i=0; i<num ; i++) {
       if(item[i].draw == false && item[i].time_appear >= time_appear) {

           item[i].draw  = true;
           SetFruitPos(item[i]) ;
       }else if(item[i].draw && item[i].time_rePos >= 13.f)  {   // reposition item

           SetFruitPos(item[i]) ;
           item[i].time_rePos = 0.f ;

       }

    }
}

void Player2::get_score(Fruit *item ,Snake &s, const int &score, const int &index, const int & num)
{
   if( !(item[0] == mine[0] ) && !(item[0] == mushroom[0])) {


     for(int i=0; i<num; i++)  {

        if(s.num[0].x == item[i].x && s.num[0].y == item[i].y  && item[i].draw) {

           item[i].draw = false;

           if( !(item[i] == stone[i])  ) {
               s.score = s.score +score;
               item[i].x = item[i].y = 111;




               if( s.score/ score_level[index] >=1) {    // handle increasing length
                   s.length_snake++;

               }

               if(s.score >3)
                  score_level[index] = (4*s.length_snake +3)*2;

               if(s.num_mana <19 && s.num_mana >=0)
                   s.num_mana ++;

           }else if(item[i] == stone[i]) {     // Snake  was paralyzed

               s.paralyze = true;
               item[i].x = item[i].y = 111;
               s.PressKey = false;
               s.preState = s.state;
               s.state = None ;
               item[i].draw =false;
           }

        }

      }

   }
}

void Player2::SetFruitPos(Fruit &item)
{


    int x,y;
    bool checkPos = false ;

    while(!checkPos ) {

        int counter =0;
        x = rand() % W_2;
        y = rand() % H_2;

       for(int i=0; i<s1.length_snake ; i++ )
          if(x == s1.num[i].x && y ==s1. num[i].y)
             counter ++;

       for(int i=0; i<s2.length_snake ; i++ )
          if(x == s2.num[i].x && y== s2.num[i].y )
             counter ++;

       for(int i=0; i<num_cherry; i++)
          if(x == cherry[i].x && y== cherry[i].y)
             counter++;

       for(int i=0; i<num_banana; i++)
          if(x == banana[i].x && y== banana[i].y)
             counter++;

       for(int i=0; i<num_apple; i++)
          if(x == apple[i].x && y== apple[i].y)
             counter++;

       for(int i=0; i< num_stone; i++)
          if(x == stone[i].x && y== stone[i].y)
             counter++;

       for(int i=0; i< num_mine; i++)
          if(x == mine[i].x && y== mine[i].y)
             counter++;

       for(int i=0; i< 2; i++)
          if(x == gold[i].x && y == gold[i].y)
             counter++;

       for(int i=0; i< num_mushroom; i++)
          if(x == mushroom[i].x && y== mushroom[i].y)
             counter++;

        if(counter == 0)
        {
            item.x = x;
            item.y = y;
            checkPos =true;

        }

    }

        item.rect_.x = (1+item.x)*Size2;
        item.rect_.y = (5+item.y)*Size2;
        item.rect_.w = Size2;
        item.rect_.h = Size2;

}

void Player2::paralyze_effect(Snake& s, float time_paralyze,const float &delta)
{
     s.timeParalyze += delta ;

     if(s.timeParalyze >= time_paralyze )
     {
         s.PressKey = true;
         s.state = s.preState;
         s.timeParalyze = 0.f;
         s.paralyze = false;

     }




}

void Player2::get_effect(Snake &s,const float &delta)
{



      if(!s.speedUp && !s.slowDown)     // set snake's speed
      {
           s.speed = 0.18f;

      }else if(s.slowDown && !s.speedUp) {
           s.speed  = 0.35f;
           s.slow_time -= delta;

      } else if( s.speedUp && !s.slowDown ) {
         s.speed = 0.1f;

      } else if(s.speedUp && s.slowDown)
         s.speed = 0.2f;


      if(s.slow_time <= 0.f)
      {
         s.slowDown = false;
      }

      if(s.num_mana >0 && s.speedUp && !s.paralyze) {
         s.speedUp_time += delta ;

         if(s.speedUp_time >= 0.4f) {
           s.num_mana --;
           s.speedUp_time = 0.f;
         }
      }
      if(s.num_mana == 0) s.speedUp_time = 0.f;


    //  Snake eats mine

    for(int i=0; i< num_mine ; i++) {

        if( mine[i].x == s.num[0].x && mine[i].y == s.num[0].y && mine[i].draw ) {

             mine[i].draw = false;
             if(s.length_snake >5)
                s.length_snake = s.length_snake*1/3 ;
             else
                s.length_snake = 2;

             s.score = s.score/3.5 ;
             s.slowDown = true;
             mine[i].x = mine[i].y = 133;
             s.num_mana /= 2;

          if(s.slowDown)
            s.slow_time = 3.f;
        }
    }


 // effect reverse


   for(int i=0; i< num_mushroom; i++) {

      if(mushroom[i].x == s.num[0].x && mushroom[i].y == s.num[0].y && mushroom[i].draw) {

        mushroom[i].draw = false;
        s.Reverse = true;

        if(s.Reverse)
           s.timeReverse = 6.f;
      }

   }

    if(s.Reverse) {

      if(s.timeReverse >0.f) {

         s.timeReverse -= delta;

         if(s.num[0] == s1.num[0] ) {

             s.key[0] =  SDL_SCANCODE_S;
             s.key[1] =  SDL_SCANCODE_W;
             s.key[2] =  SDL_SCANCODE_A;
             s.key[3] =  SDL_SCANCODE_D;

         }else if(s.num[0] == s2.num[0]) {

             s.key[0] =  SDL_SCANCODE_DOWN;
             s.key[1] =  SDL_SCANCODE_UP;
             s.key[2] =  SDL_SCANCODE_LEFT;
             s.key[3] =  SDL_SCANCODE_RIGHT;
         }


      } else if(s.timeReverse <=0.f)
          s.Reverse = false;

   } else {

          if(s.num[0] == s1.num[0] && s.state == s1.state) {

             s.key[0] =  SDL_SCANCODE_W;
             s.key[1] =  SDL_SCANCODE_S;
             s.key[2] =  SDL_SCANCODE_D;
             s.key[3] =  SDL_SCANCODE_A;

         }else if(s.num[0] == s2.num[0]&& s.state == s2.state) {

             s.key[0] =  SDL_SCANCODE_UP;
             s.key[1] =  SDL_SCANCODE_DOWN;
             s.key[2] =  SDL_SCANCODE_RIGHT;
             s.key[3] =  SDL_SCANCODE_LEFT;

          }
   }

}

void Player2 :: handle_dead(Snake& s) {

    s.length_snake =2;
    s.state = None;
    s.paralyze = false;
    s.Reverse  = false;
    s.slowDown = false;


   if(s1.num[0] == s.num[0] && s1.num[1]==s.num[1] ) {


            num_heart[0]--;
            dead[0] = true;
            s1.num[0].y = H_2 ;
            s1.num[0].x = 2;
            s1.num[1].x = 1;
            s1.num[1].y = H_2;



   } else if(s2.num[0] == s.num[0] && s2.num[1]==s.num[1]) {



            dead[1] = true;
            s2.num[0].y = H_2 ;
            s2.num[0].x = W_2-3;
            s2.num[1].x = W_2-2;
            s2.num[1].y = H_2;
            num_heart[1]--;
   }



}



Player2::~Player2()
{
  s1.~Snake();
  s2.~Snake();
  back_ground.Free();
  background_p2.Free();

  bar_manaS1.~Icon();
  bar_manaS2.~Icon();

  text_time.~TextObject();

  for(int i=0; i<2; i++)
    text_player[i].~TextObject();

  for(int i=0; i<num_cherry ; i++)
    cherry[i].Free();

  for(int i=0; i<num_banana; i++)
    banana[i].Free();

  for(int i=0; i<num_apple; i++)
    apple[i].Free();

  for(int i=0; i<num_mine; i++)
    mine[i].Free();
  for(int i=0; i<num_stone; i++)
    stone[i].Free();

  for(int i=0; i<2 ; i++)

    gold[i].Free();

  for(int i=0; i< num_mushroom; i++)
    mushroom[i].Free();
}
