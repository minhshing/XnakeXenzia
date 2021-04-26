#include "BaseObject.h"

BaseObject::BaseObject()
{
   rect_.x = rect_.y =0;
   rect_.w = rect_.h =0;

   p_object = NULL;


}

BaseObject::~BaseObject()
{
    Free();
}


bool BaseObject :: LoadIMG(std::string filePath, SDL_Renderer *renderTarger)
{
    SDL_Texture *new_texture = NULL;
    SDL_Surface *load_surface = IMG_Load(filePath.c_str());

   if( load_surface != NULL) {
    // SDL_SetColorKey(load_surface,SDL_TRUE ,
                     //SDL_MapRGB(load_surface->format, COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B)) ;

        new_texture = SDL_CreateTextureFromSurface(renderTarger,load_surface);

        if(new_texture == NULL) {
            std::cout << "Error : Failed Texture ." <<std::endl;
        }
        else {
           rect_.w = load_surface->w;
           rect_.h = load_surface->h;

           p_object = new_texture;
        }
    }

    SDL_FreeSurface(load_surface);

    return p_object != NULL ;
}

void BaseObject ::Render(SDL_Renderer *des, SDL_Rect *cropRect )
{
    SDL_Rect rectPos = {rect_.x, rect_.y, rect_.w , rect_.h} ;
    SDL_RenderCopy(des, p_object, cropRect, &rectPos);

}

void BaseObject ::Free()
{
    if( p_object != NULL)
    {
        SDL_DestroyTexture(p_object);
        p_object = NULL;
        rect_.w = rect_.h =0;

    }
}
