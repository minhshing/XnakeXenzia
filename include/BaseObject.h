#include "CommonFunc.h"

#ifndef BASEOBJECT_H
#define BASEOBJECT_H

// for 1 Player




//
class BaseObject
{
    public:
       BaseObject();
      ~BaseObject();

    void SetRect(const int &x, const int &y) { rect_.x =x; rect_.y = y ;};
    void SetSize(const int &x, const int &y) {rect_.w = x; rect_.h = y ;} ;
    SDL_Rect GetRect() const {return rect_; };


    SDL_Texture *GetObject() const { return p_object;}

    bool LoadIMG(std::string filePath, SDL_Renderer *renderTarger);
    void Render(SDL_Renderer *des, SDL_Rect* cropRect = NULL) ;
    void Free();
    bool draw;

    public:
      SDL_Texture *p_object;
      SDL_Rect rect_;
      SDL_Rect cropRect;
      int frameX,frameY;
      int frameH,frameW;

};

#endif // BASEOBJECT_H
