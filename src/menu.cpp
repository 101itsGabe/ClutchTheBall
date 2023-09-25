#include "menu.h"
#include "SDL.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

Menu::Menu() {}

Menu::Menu(int windowWidth, int windowHeight)
{
    menuData.menuX = windowWidth / 2.5;
    menuData.menuY = windowHeight / 6;
    menuData.menuW = windowWidth * 0.25;
    menuData.menuH = windowHeight * 0.40;
}

int Menu::mouseCheck(int mX, int mY)
{
    for (TextData &md : textData)
    {
        if (md.menuX < mX && md.menuY < mY && (md.menuW + md.menuX) > mX && (md.menuH + md.menuY) > mY)
        {
            if (md.name == "Shoot")
                return 1;
            else if (md.name == "Move")
                return 2;
        }
    }
    return 0;
}

MenuData Menu::getMenuData()
{
    return menuData;
}

void Menu::RenderText(SDL_Renderer *renderer, TTF_Font *font)
{
    vector<string> textList = {"Shoot", "Move", "Dribble"};
    int numItems = textList.size();
    int offsetConst = (menuData.menuH * 0.4) / numItems;
    SDL_Color color = {0, 0, 0};
    for (string &text : textList)
    {
        if (font != NULL)
        {
            SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
            if (textSurface != NULL)
            {
                SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture != NULL)
                {
                    SDL_Rect textRect;
                    if (textList[0] == text)
                        textRect = {menuData.menuX, menuData.menuY, menuData.menuW / 2, (int)((menuData.menuH / 2) / textList.size())};
                    else
                        textRect = {menuData.menuX, menuData.menuY + offsetConst, menuData.menuW / 2, (int)((menuData.menuH / 2) / textList.size())};

                    TextData curText = {text, textRect.x, textRect.y, textRect.w, textRect.h};
                    textData.emplace_back(curText);
                    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
                    const char *rendererError = SDL_GetError();
                    if (strlen(rendererError) > 0)
                    {
                        cout << rendererError << endl;
                    }
                    SDL_FreeSurface(textSurface);
                    SDL_DestroyTexture(textTexture);
                    offsetConst += offsetConst;
                }
            }
        }
    }
}

vector<TextData> &Menu::getTextData()
{
    return textData;
}