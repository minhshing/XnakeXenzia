#include "Icon.h"

Icon::Icon()
{
}

void Icon::Load_imgIcon(SDL_Renderer* render,const string & s,BaseObject &icon)
{
    if(!icon.LoadIMG(s.c_str(), render) )
        cout << "Error : Load image is failed . " << s << endl;
    SDL_QueryTexture(icon.p_object,NULL, NULL,&icon.rect_.w, &icon.rect_.h);
}


void Icon::Initial_mana(SDL_Renderer *render)
{
  int a[20];

  a[0] = bar_mana[0].LoadIMG("Image/mana/mana0.png", render);
  a[1] = bar_mana[1].LoadIMG("Image/mana/mana1.png", render);
  a[2] = bar_mana[2].LoadIMG("Image/mana/mana2.png", render);
  a[3] = bar_mana[3].LoadIMG("Image/mana/mana3.png", render);
  a[4] = bar_mana[4].LoadIMG("Image/mana/mana4.png", render);
  a[5] = bar_mana[5].LoadIMG("Image/mana/mana5.png", render);
  a[6] = bar_mana[6].LoadIMG("Image/mana/mana6.png", render);
  a[7] = bar_mana[7].LoadIMG("Image/mana/mana7.png", render);
  a[8] = bar_mana[8].LoadIMG("Image/mana/mana8.png", render);
  a[9] = bar_mana[9].LoadIMG("Image/mana/mana9.png", render);

  a[10] = bar_mana[10].LoadIMG("Image/mana/mana10.png", render);
  a[11] = bar_mana[11].LoadIMG("Image/mana/mana11.png", render);
  a[12] = bar_mana[12].LoadIMG("Image/mana/mana12.png", render);
  a[13] = bar_mana[13].LoadIMG("Image/mana/mana13.png", render);
  a[14] = bar_mana[14].LoadIMG("Image/mana/mana14.png", render);
  a[15] = bar_mana[15].LoadIMG("Image/mana/mana15.png", render);
  a[16] = bar_mana[16].LoadIMG("Image/mana/mana16.png", render);
  a[17] = bar_mana[17].LoadIMG("Image/mana/mana17.png", render);
  a[18] = bar_mana[18].LoadIMG("Image/mana/mana18.png", render);
  a[19] = bar_mana[19].LoadIMG("Image/mana/mana19.png", render);

  for(int i=0; i<20; i++) {
    if( !a[i] )
       cout << "Load image bar mana " << i <<  "is failed" <<endl;

   bar_mana[i].SetSize(100,11);

  }
}

void Icon::Render_barMana(SDL_Renderer *render, const int &index, const int &player)
{
    if(player == 1)
       bar_mana[index].SetRect(25,60);
    else if(player == 2)
        bar_mana[index].SetRect(600,60);

    bar_mana[index].Render(render);


}

void Icon::Initial_iconP1(SDL_Renderer *render)
{

    Load_imgIcon( render,"Image/icon/iconp9.png",icon_pause) ;
    Load_imgIcon(render,"Image/icon/play3.png" , icon_play);
    Load_imgIcon(render,"Image/icon/replay3.png",icon_replay ) ;

    Load_imgIcon(render,"Image/icon/home2.png" , icon_home) ;
    Load_imgIcon(render,"Image/icon/volume_up.png", icon_volume[0]);
    Load_imgIcon(render,"Image/icon/mute.png", icon_volume[1]);

    Load_imgIcon(render,"Image/icon/shutdown.png",icon_exit);
    Load_imgIcon(render,"Image/icon/trophy_types.png", trophy) ;

    Load_imgIcon(render,"Image/snake/bkg.png", img_bkg);
    Load_imgIcon(render,"Image/snake/snake.png",imgSnake);
    Load_imgIcon(render,"Image/icon/fruit.png", imgFruit);
    SDL_QueryTexture(imgFruit.p_object,NULL,NULL,&imgFruit.cropRect.w, &imgFruit.cropRect.h);


    Load_imgIcon(render,"Image/icon/change.png", iChange);
    Load_imgIcon(render,"Image/icon/replay.png", iReplay);

}

void Icon::set_iconP1()
{
      // Set icons

    icon_pause.SetRect(15*Size,Size-18);
    SDL_SetTextureColorMod(icon_pause.p_object, 255,0,255) ;

    icon_play.SetRect(15*Size,Size-18);
    SDL_SetTextureColorMod(icon_play.p_object, 255,0,255) ;

    SDL_SetTextureColorMod(icon_replay.p_object, 255,0,255) ;

    SDL_SetTextureColorMod(icon_home.p_object, 255,0,255) ;

    icon_volume[0].SetRect(13*Size+10,Size-15);
    SDL_SetTextureColorMod(icon_volume[0].p_object, 255,0,255) ;

    icon_volume[1].SetRect(13*Size+10,Size-15);
    SDL_SetTextureColorMod(icon_volume[1].p_object, 255,0,255) ;

    icon_exit.SetRect(30,8);


    trophy.cropRect.w =  trophy.rect_.w/6  ;
    trophy.cropRect.h = trophy.rect_.h ;
    trophy.cropRect.x = trophy.cropRect.y =0;


    indexTrophy =0;
    frameX[0] = trophy.cropRect.w;

    imgSnake.rect_.y = 380;
    imgSnake.rect_.w += 20;
    indexSnake =0;

    // set img fruit

    imgFruit.SetSize(70,70);
    imgFruit.SetRect(200,140);
    imgFruit.cropRect.x = 0;
    imgFruit.cropRect.y =0;
    imgFruit.cropRect.w /= 14;

    frameX[1] = imgFruit.cropRect.w;
    indexFruit =0;

    //

    iChange.SetRect(230,550);
    iChange.SetSize(70,70);

    iReplay.SetRect(320,550);
    iReplay.SetSize(220,70);


}

void Icon::Draw_iconP1(SDL_Renderer *render,const bool &pause, const bool &sound)
{

    icon_home.SetRect(11*Size+10,Size-16);
    icon_replay.SetRect(17*Size,Size-16);

    if(pause == false)
       icon_pause.Render(render) ;
    else
       icon_play.Render(render) ;

    if( sound == true)
       icon_volume[0].Render(render);
    else
       icon_volume[1].Render(render);

    icon_replay.Render(render) ;
    icon_home.Render(render) ;


    trophy.SetRect(4*Size-20,Size-15);
    trophy.SetSize(Size+8,Size+6);

    trophy.Render(render,&trophy.cropRect);



}

void Icon::Check_iconP1(Snake &s, SDL_Event  &e, bool &pause,float &time_over,
                        bool &call_menu, bool &play1, int xMouse, int yMouse, bool &sound)
{
   // Check click icons

  if( s.game_over == false) {

    icon_play.draw  = true;
    icon_pause.draw = true;
    icon_volume[0].draw  = true;
    icon_volume[1].draw  = true;

  } else {

    icon_play.draw  = false ;
    icon_pause.draw = false ;
    icon_volume[0].draw  = false ;
    icon_volume[1].draw  = false ;


  }


      if(e.type == SDL_MOUSEBUTTONDOWN ) {
            if(CheckFocusWithRect(xMouse,yMouse,icon_pause.rect_) && !pause && icon_pause.draw ) {
                 if( s.state != None) {
                     s.setState(None) ;
                     pause = true;
                     s.PressKey = false;
                 }

            } else  if(CheckFocusWithRect(xMouse,yMouse,icon_play.rect_) && pause && icon_play.draw ) {

                 if( s.state == None) {

                     s.setState(s.preState);
                      s.PressKey = true;
                      pause = false;
                   }
            } else  if(CheckFocusWithRect(xMouse,yMouse,icon_replay.rect_)  ) {
                      s.Reset_game();
                      pause = false;
                      time_over =0.f;
            } else  if(CheckFocusWithRect(xMouse,yMouse,icon_home.rect_)  ) {
                      call_menu = true;

                      if(!s.game_over)
                         s.state = None;




           } else  if(CheckFocusWithRect(xMouse,yMouse,icon_volume[0].rect_) && sound && icon_volume[0].draw ) {
                        sound = false;

           } else  if(CheckFocusWithRect(xMouse,yMouse,icon_volume[1].rect_) && !sound && icon_volume[1].draw) {
                        sound = true;
           }


      }

  // Check icon 's position

     if(CheckFocusWithRect(xMouse,yMouse,icon_pause.rect_) ) {
         icon_pause.SetSize(Size+30,Size+30) ;
         icon_play.SetSize(Size+30,Size+30) ;

     } else {
       icon_pause.SetSize(Size+3,Size+3) ;
       icon_play.SetSize(Size+3,Size+3) ;

    }

    if(CheckFocusWithRect(xMouse,yMouse,icon_replay.rect_) )
         icon_replay.SetSize(Size+25,Size+25) ;
    else
          icon_replay.SetSize(Size,Size) ;

    if(CheckFocusWithRect(xMouse,yMouse,icon_home.rect_) ) {

           icon_home.SetSize(Size+22,Size+22) ;


    }else {
        // if(!s.game_over)
           icon_home.SetSize(Size,Size) ;

    }

    if(CheckFocusWithRect(xMouse,yMouse,icon_volume[0].rect_) ) {
         icon_volume[0].SetSize(Size+22,Size+22) ;
         icon_volume[1].SetSize(Size+22,Size+22) ;
    }else {
          icon_volume[0].SetSize(Size,Size) ;
          icon_volume[1].SetSize(Size,Size) ;
    }

    if(CheckFocusWithRect(xMouse,yMouse,icon_exit.rect_) )
        icon_exit.SetSize(2*Size+22,2*Size+22);
    else
        icon_exit.SetSize(2*Size,2*Size);


}

void Icon::Draw_textScoreP1(SDL_Renderer *render, TTF_Font *font1, TTF_Font* font2, const Snake &s , bool &draw_text_gOver)
{
    scoreP1[0].setText_Color(WHITE_COLOR);
    scoreP1[1].setText_Color(WHITE_COLOR);

    string str_score = to_string(s.score);

    string str_score1 ;
    for(int i=0; i<3; i++) {
      if(s.mode_game[i] == true)
         str_score1 = to_string(s.highest_score[i]);
    }

    if(!draw_text_gOver) {

      scoreP1[0].SetText(str_score);
      scoreP1[0].CreateGameText(font1,render) ;

      scoreP1[0].rect_.x = 2*Size +5;
      scoreP1[0].rect_.y = Size - 9;


      scoreP1[1].SetText(str_score1);
      scoreP1[1].CreateGameText(font1,render) ;
      scoreP1[1].rect_.x = 5*Size +5;
      scoreP1[1].rect_.y = Size - 9;

    } else {
      scoreP1[0].SetText(str_score);
      scoreP1[0].CreateGameText(font2,render) ;

      scoreP1[0].rect_.x = 220;
      scoreP1[0].rect_.y = 230;


      scoreP1[1].SetText(str_score1);
      scoreP1[1].CreateGameText(font2,render) ;
      scoreP1[1].rect_.x = 420;
      scoreP1[1].rect_.y = 230;


    }


    scoreP1[0].DrawText(render);
    scoreP1[1].DrawText(render);

}
// enum Color {Red, Green, Orange ,Blue ,White};
void Icon::Draw_gameOverP1(SDL_Renderer *render,const Snake &s)
{
   // Draw image snake

    if(indexSnake == 0)
       colorS  = Red;
    else if(indexSnake == 1)
        colorS = Green;
    else if(indexSnake == 2)
        colorS = Orange;
    else if(indexSnake == 3)
        colorS = Blue;
    else if(indexSnake == 4)
        colorS = White;

    if(colorS == Red)
        SDL_SetTextureColorMod(imgSnake.p_object,255,0,0);
    else if(colorS == White)
        SDL_SetTextureColorMod(imgSnake.p_object,255,255,255);
    else if(colorS == Green)
        SDL_SetTextureColorMod(imgSnake.p_object,0,180,0);
    else if(colorS == Orange)
        SDL_SetTextureColorMod(imgSnake.p_object,255,165,0);
    else if(colorS == Blue)
        SDL_SetTextureColorMod(imgSnake.p_object,65,0,255);



    img_bkg.Render(render);
    imgSnake.Render(render);

  // Draw icon
    icon_replay.SetRect(630,25);
    icon_home.SetRect(550,25);

    icon_home.Render(render);
    icon_replay.Render(render);


    icon_exit.Render(render);

  // Draw fruit and trophy
    imgFruit.Render(render,&imgFruit.cropRect);

    trophy.SetRect(400,140);
    trophy.SetSize(Size+30,Size+30);
    trophy.Render(render,&trophy.cropRect);

   //
    iChange.Render(render);
    iReplay.Render(render);

}

void Icon::Handle_GameOverP1(Snake &s, SDL_Event &e,bool &call_menu,
                           const int &xm,const int &ym, float &time_over,bool &running)
{
    if(s.game_over) {
        imgSnake.draw = true;
        imgFruit.draw = true;
        iReplay.draw  = true;
        iChange.draw  = true;

    } else {
        imgSnake.draw = false;
        imgFruit.draw = false;
        iReplay.draw  = false;
        iChange.draw  = false;
    }

   s.color = colorS;




   if(e.type == SDL_MOUSEBUTTONDOWN ) {

        if(CheckFocusWithRect(xm,ym,imgSnake.rect_) && imgSnake.draw) {

            if(indexSnake >=0 && indexSnake <4)
                indexSnake ++;
            else if(indexSnake ==4)
                indexSnake =0;

        }else  if(CheckFocusWithRect(xm,ym,icon_home.rect_)  ) {
                      call_menu = true;
                      s.Reset_game();
                      time_over =0.f;

        }else  if(CheckFocusWithRect(xm,ym,imgFruit.rect_) && imgFruit.draw ) {
                    if(indexFruit >=0 && indexFruit<13)
                        indexFruit ++;
                    else if(indexFruit == 13)
                        indexFruit =0;



        }else  if(CheckFocusWithRect(xm,ym,trophy.rect_) && s.game_over ) {

                 if(indexTrophy == 0)
                      indexTrophy ++;
                 else if(indexTrophy ==1)
                      indexTrophy = 4 ;
                 else if(indexTrophy ==4)
                      indexTrophy = 0 ;




         }  else if(CheckFocusWithRect(xm,ym,icon_exit.rect_)  ) {
                   running = false;

         } else if(CheckFocusWithRect(xm,ym,iReplay.rect_) &&iReplay.draw ) {
                      s.Reset_game();

                      time_over =0.f;

         } else if(CheckFocusWithRect(xm,ym,iChange.rect_) &&iChange.draw ) {

               indexFruit = rand() % 14;
               indexSnake = rand() % 5;

               int a = rand() % 3;

               if(a == 0)
                  indexTrophy = 0;
               else if(a == 1)
                   indexTrophy =1;
               else if(a == 2)
                   indexTrophy = 4;


         }

   }



    if(CheckFocusWithRect(xm,ym,iReplay.rect_) &&iReplay.draw )
        iReplay.SetSize(260,80);
    else
        iReplay.SetSize(220,70);

    if(CheckFocusWithRect(xm,ym,iChange.rect_) &&iChange.draw )
        iChange.SetSize(80,80);
    else
        iChange.SetSize(70,70);


 // Set mode 1 Player

     imgFruit.cropRect.x = indexFruit*frameX[1];
     s.fruit[0].cropRect.x  = indexFruit*frameX[1];

       if(indexTrophy == 0) {
        s.mode_game[0] = true;
        s.mode_game[1] = s.mode_game[2] =false;

     } else  if(indexTrophy == 1) {

        s.mode_game[1] = true;
        s.mode_game[0] = s.mode_game[2] =false;

     }  if(indexTrophy == 4) {

        s.mode_game[2] = true;
        s.mode_game[1] = s.mode_game[0] =false;
     }

    trophy.cropRect.x = indexTrophy*frameX[0];


}

Icon::~Icon()
{
   for(int i=0; i<20; i++)
       bar_mana[i].Free();

   for(int i=0; i<2; i++) {
      icon_volume[i].Free();
      scoreP1[i].~TextObject();

   }

   icon_home.Free();
   icon_pause.Free();
   icon_replay.Free();

   trophy.Free();
   imgSnake.Free();
   imgFruit.Free();
   img_bkg.Free();
   iChange.Free();
   iReplay.Free();



}
