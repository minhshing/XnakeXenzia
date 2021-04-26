#ifndef PLAYER2_H
#define PLAYER2_H

#include "Snake.h"
#include "TextObject.h"
#include "Icon.h"

const int W_2 =28 ;
const int H_2 = 24 ;


///  2 Player Mode game

enum Result{s1Win,s2Win,Tie,none};

class Player2
{
    public:

       Player2(SDL_Renderer *render);
       void Draw_player2(SDL_Renderer *render, TTF_Font *font1,  TTF_Font *font2,const float &time_val, bool &pauseP2) ;
       void Move_p2(Snake &s,const Uint8 *keyState , bool &pause, bool &dead) ;
       void Snake_moving(const Uint8 *keyState , bool &pause);

       void Update_p2(const float &delta, bool &pauseP2) ;

       ~Player2();

       void set_up();
       void Game_Over();

   private :
       void Load_imgItems(SDL_Renderer *render,Fruit *fruit, const std::string &s ,const int &num);
       void Draw_item(SDL_Renderer *render,Fruit *f, const int & num);

       void SetFruitPos(Fruit &Cherry);
       void timeAppear_fruit(Fruit *item, Snake &s,const float &time_appear,
                            const float &delta,const int &score, const int &index,const int &num);

       void get_score(Fruit *item ,Snake &s, const int &score, const int &index, const int & num) ;
       void get_effect(Snake &s, const float &delta) ;

       void Initial_fruit(Fruit* item, const int & num);

       void paralyze_effect(Snake& s, float time_paralyze,const float &delta);
       void handle_dead(Snake& s);

    private:



        Fruit cherry[5] ;
        Fruit banana[4];
        Fruit apple[3] ;
        Fruit mushroom[3] ;

        BaseObject heart[2];
        int num_heart[2] ;

        int num_cherry , num_banana ;
        int num_apple , num_mushroom ;
        int num_mine, num_stone ;

        int score_level[2];
        float time_player ;

        bool dead[2];

        TextObject text_player[2] ;
        TextObject text_time ;


        Snake s1,s2 ;

        Fruit mine[3] ;
        Fruit stone[4];
        Fruit gold[2];

        Icon bar_manaS1, bar_manaS2;

    public :
        BaseObject back_ground;
        bool game_over;
        BaseObject background_p2 ;
        Result result;

};



#endif // PLAYER2_H
