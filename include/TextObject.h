#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H


#include "BaseObject.h"

class TextObject : public BaseObject
{
 public:


     TextObject();
    ~TextObject();

    void setText_Color(const SDL_Color &color);
    void SetText( std::string text) { text_val =text ;};

    void CreateGameText(TTF_Font *font, SDL_Renderer *render) ;

    void DrawText(SDL_Renderer *renderTarget);


 private:
     SDL_Color text_color;
     std::string text_val;
};

#endif // TEXTOBJECT_H
