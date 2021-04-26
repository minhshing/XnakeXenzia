
#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <iostream>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <time.h>
#include <stdlib.h>
#include <cmath>

using namespace std;


const int SCREEN_WIDTH = 722;
const int SCREEN_HEIGHT = 722;

const int COLOR_KEY_R = 167 ;
const int COLOR_KEY_G = 175 ;
const int COLOR_KEY_B = 180 ;

const int Size2 = 24;


const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};

bool CheckFocusWithRect(const int& x,const int &y,const SDL_Rect &rect);


#endif // COMMON_FUNC_H_
