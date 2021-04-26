#ifndef ICON_H
#define ICON_H

#include "Snake.h"
#include "TextObject.h"

class Icon
{
    public:
         Icon();
        ~Icon();

    void Initial_mana(SDL_Renderer *render) ;
    void Render_barMana(SDL_Renderer *render, const int &index,const int &player);
    void Initial_iconP1(SDL_Renderer *render);
    void Load_imgIcon(SDL_Renderer* render,const string & s, BaseObject &icon);

    void set_iconP1();
    void Draw_iconP1(SDL_Renderer *render,const bool &pause, const bool &sound) ;
    void Check_iconP1(Snake &s, SDL_Event  &e,bool &pause,float &time_over,
                      bool &call_menu, bool &play1 ,int xMouse, int yMouse, bool &sound);

   void Draw_textScoreP1(SDL_Renderer *render, TTF_Font *font,TTF_Font* font2,const Snake &s,bool& draw_text_gOver);
   void Draw_gameOverP1(SDL_Renderer *render,const Snake &s);

   void Handle_GameOverP1(Snake& s, SDL_Event &e, bool &call_menu,
                        const int &xm,const int &ym, float &time_over,bool &running);

    private :
       BaseObject bar_mana[20];

       BaseObject icon_play  ;
       BaseObject icon_replay ;
       BaseObject icon_home ;
       BaseObject icon_pause;
       BaseObject icon_volume[2];
       BaseObject icon_exit;

       BaseObject trophy;
       TextObject scoreP1[2];

       BaseObject imgSnake;
       BaseObject img_bkg ;
       BaseObject imgFruit ;

       BaseObject iChange,iReplay;

       Color colorS;
       int indexSnake;
       int indexFruit,frameX[2];
       int indexTrophy;

};

#endif // ICON_H
