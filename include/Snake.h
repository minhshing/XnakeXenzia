#ifndef SNAKE_H
#define SNAKE_H


#include "BaseObject.h"


const int Size = 38 ;
const int W = 17 ;
const int H = 15 ;

class Coordinate
{
    public :
    int x, y;

  bool  operator ==(const Coordinate & f) const
  {
      if(x == f.x && y == f.y )
        return true;

     return false;
  }
};

class Fruit : public BaseObject{

 public :
  int x, y;

  // for 1 player
   bool increase_size;

  // for 2 player

  float time_appear ;
  float time_rePos ;


  bool  operator ==(const Fruit & f) const
  {
      if(x == f.x && y == f.y )
        return true;

     return false;
  }

};



enum State {Up, Down , Right , Left, None};
enum Color {Red, Green, Orange ,Blue ,White};

class Snake : public BaseObject
{
    public:
        Snake();
       ~Snake();

    void Draw(SDL_Renderer *render,  float delta) ;
    void Update( float delta, Mix_Chunk *eat, Mix_Chunk *dead) ;
    void Move(const Uint8 *keyState , bool pause ,Mix_Chunk *moving[4],bool &draw_imgControl, bool dead = false) ;

    void setState(State x) {state = x;} ;
    void SetFruitPos();
    void Reset_game() ;
    void Setup(SDL_Renderer *render);
    void Handle_border( int w,  int h) ;

    void SetPos_barrier();

    void Draw_effect(SDL_Renderer *render, float& delta);

   public :

        int score;
        int length_snake;
        float frameTime ;
        float speed ;

        SDL_Scancode key[9] ;
        Coordinate num[W*H];

        State state ;
        State preState ;
        bool PressKey;

   public :

   // for 1 player
        bool game_over;
        bool collide_barrier;
        bool collide_body ;
        bool draw_back[2];
        bool play_sound ;
        bool mode_game[3];

        Fruit fruit[2];
        BaseObject head_state[5] ;
        BaseObject barrier ;
        Coordinate Barriers[70];

        BaseObject effect[2];
        float timeEffect;

        int num_barrier;
        int highest_score[3];
        Color color;

        float timeApple ;
        float timeCollide;


    // for 2 Player
       bool speedUp, slowDown ;
       int num_mana;
       float slow_time , speedUp_time;
       bool paralyze , Reverse;
       float timeParalyze ;
       float timeReverse ;
};



#endif // SNAKE_H
