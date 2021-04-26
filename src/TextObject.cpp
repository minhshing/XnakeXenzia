#include "TextObject.h"

TextObject::TextObject()
{

}

TextObject::~TextObject()
{
  Free();

}

void TextObject::setText_Color(const SDL_Color &color )
{
  text_color = color;

}

void TextObject::CreateGameText(TTF_Font *font, SDL_Renderer *render)
{
    this->Free();  /// Important

     SDL_Surface *textSurface = TTF_RenderText_Solid(font, text_val.c_str() ,text_color ) ;
     p_object = SDL_CreateTextureFromSurface(render, textSurface);



     SDL_QueryTexture(p_object,NULL,NULL, &rect_.w, &rect_.h);

     SDL_FreeSurface(textSurface);
     textSurface = NULL;

}

void TextObject::DrawText(SDL_Renderer *renderTarget)
{
    this->Render(renderTarget);

}
