#define SDL_MAIN_HANDLED

#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <random>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <menu.h>
#include "SDL_ttf.h"
#include "src/player.h"
#include "tile.h"
#include "playerManager.h"
#include "tileManager.h"
#include "gameManager.h"

// AHHHAAA INSIDE THE CPP_PROPERTIES IS WHERE YOU HAVE TO ADD THE EXTRA SDL FILES

// Try to find TTF cause its installed

using namespace std;

void renderTile(SDL_Renderer *renderer, Tile *tile, int windowWidth, int windowHeight, int tileLen)
{

    int tileSize = std::min(windowWidth, windowHeight) / 11;
    int gridWidth = 15 * tileSize; // Total width of the grid
    int gridHeight = 9 * tileSize; // Total height of the grid

    int middleX = (windowWidth - gridWidth) / 2;   // X-coordinate of the top-left corner
    int middleY = (windowHeight - gridHeight) / 2; // Y-coordinate of the top-left corner

    // cout << tile->getX() << " " << tile->getY() << endl;
    int tileX = tile->getX() * tileSize + middleX;
    int tileY = tile->getY() * tileSize + middleY;
    // This is going to calc where the exact tile will go on screen
    // This might have to be just the pixels like 64 or something

    tile->setCoords(tileX, tileY, tileSize, tileSize); // Set the color for the Tile
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect tileRect = {tileX, tileY, tileSize, tileSize};

    // Render the tile
    SDL_RenderFillRect(renderer, &tileRect);

    // Border Color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_Rect borderRect = {tileX, tileY, tileSize, tileSize};

    // Render the Border
    SDL_RenderDrawRect(renderer, &borderRect);
}

void renderText(SDL_Renderer *renderer, Tile *tile, TTF_Font *font, int check)
{

    int tileSize = tile->getTileData().tileW;
    int tileX = tile->getTileData().tileX;
    int tileY = tile->getTileData().tileY;

    string tileId;
    if (check == 3)
        tileId = "3P";
    else if (check == 2)
        tileId = "2P";
    else if (check == 1)
        tileId = "H";
    else
        tileId = to_string(tile->getTileId());
    SDL_Color textColor = {85, 85, 85};
    if (font != NULL)
    {
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, tileId.c_str(), textColor);
        if (textSurface != NULL)
        {
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture != NULL)
            {
                SDL_Rect textRect = {tileX + 16, tileY + 8, tileSize - 40, tileSize - 40};
                SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
                const char *rendererError = SDL_GetError();
                if (strlen(rendererError) > 0)
                {
                    cout << rendererError << endl;
                }
                SDL_DestroyTexture(textTexture);
            }
        }
        SDL_FreeSurface(textSurface);
    }
}

Menu renderMenu(SDL_Renderer *renderer, TTF_Font *font, Tile *t, int windowWidth, int windowHeight)
{
    SDL_Rect rect;
    Menu curMenu(windowWidth, windowHeight);
    rect.x = curMenu.getMenuData().menuX;
    rect.y = curMenu.getMenuData().menuY;
    rect.w = curMenu.getMenuData().menuW;
    rect.h = curMenu.getMenuData().menuH;
    SDL_Color color = {128, 128, 128};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 250);
    SDL_RenderFillRect(renderer, &rect);
    curMenu.RenderText(renderer, font);
    return curMenu;
}

void renderBackground(SDL_Renderer *renderer, SDL_Texture *texture, int windowWidth, int windoHeight)
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = windowWidth;
    rect.h = windoHeight;

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Highlight(SDL_Renderer *renderer, Tile *tile)
{
    SDL_Color curColor = {173, 216, 230, 255};
    SDL_SetRenderDrawColor(renderer, curColor.r, curColor.g, curColor.b, curColor.a);
    int posX = tile->getTileData().tileX;
    int posY = tile->getTileData().tileY;
    int w = tile->getTileData().tileW;
    int h = tile->getTileData().tileH;
    // cout << w << " " << h << endl;
    SDL_Rect rect = {posX, posY, w, h};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_Rect borderRect = {posX, posY, w, h};

    // Render the Tile
    SDL_RenderDrawRect(renderer, &borderRect);
}

int getRandomNumber(int min, int max)
{
    std::mt19937 gen(std::time(0));                    // Initialize with current time as seed
    std::uniform_int_distribution<int> dist(min, max); // Define a distribution

    return dist(gen); // Generate a random number
}

bool InitSDL()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    // SDL_Surface* imageSurface = NULL; //Surface to load image
    TTF_Font *font = NULL;
    SDL_Surface *image = NULL;

    PlayerManager PM(6);
    GameManager GM(PM.getPlayerList());
    for (Player &p : PM.getPlayerList())
    {
        cout << "After GM: " << p.getTeam() << endl;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Something went wrong homeslice:\n";
        cout << SDL_GetError();
        return false;
    }

    if (TTF_Init() != 0)
    {
        cout << "Something failed big dog:\n";
        cout << TTF_GetError();
        return false;
    }

    // load support for the JPG and PNG image formats
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags)
    {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    }

    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);
    int windowWidthSc = dm.w * 3 / 4;  // Set the window width to 75% of the screen width
    int windowHeightSc = dm.h * 3 / 4; // Set the window height to 75% of the screen height
    window = SDL_CreateWindow(
        "Shilos lil bigger window",
        SDL_WINDOWPOS_CENTERED, // Centered window position
        SDL_WINDOWPOS_CENTERED, // Centered window position
        windowWidthSc,
        windowHeightSc,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window == NULL)
    {
        cout << "Window is null";
        cout << SDL_GetError();
    }

    font = TTF_OpenFont("src/fonts/Roboto-Black.ttf", 45);
    if (!font)
    {
        cout << "Uhoh Spagetthi Something happened inside font: \n";
        cout << TTF_GetError();
    }
    // getting render
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Image
    image = IMG_Load("./src/images/bg3.png");
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_FreeSurface(image);

    if (image == NULL)
    {
        printf("Failed to load image. Error: %s\n", IMG_GetError());
    }
    // Window
    int windowWidth, windowHeight;

    vector<Tile> tiles;

    TileManager TM;
    tiles = TM.getTileList();

    random_device rd;
    mt19937 eng(rd());
    int min = 1;
    int max = 69;

    for (Player &p : PM.getPlayerList())
    {
        uniform_int_distribution<> distr1(min, max);
        int curN = distr1(eng);
        // cout << "First Player Tile: " << curN << endl;
        p.SetTile(curN);
    }

    // Show the updated Frame
    SDL_RenderPresent(renderer);

    // Main Loop

    SDL_Event e;
    bool quit = false;
    bool clicked = false;
    bool menu = false;
    bool highlight = true;
    Player *clickedPlayer = nullptr;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            SDL_GetWindowSize(window, &windowWidth, &windowHeight);
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            int mouseX, mouseY;
            Tile *curTile = nullptr;
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_RenderClear(renderer);
            renderBackground(renderer, backgroundTexture, windowWidth, windowHeight);
            GM.RenderScore(renderer, font, windowWidth, windowHeight);
            // cout << "Before Render Shot" << endl;
            //  GM.RenderShotPercent(renderer, font, windowWidth, windowHeight, clickedPlayer);
            for (Tile &tile : TM.getTileList())
            {
                renderTile(renderer, &tile, windowWidth, windowHeight, TM.getTileList().size());
                renderText(renderer, &tile, font, GM.check3(tile.getTileId()));
                if (tile.getMouseCheck(mouseX, mouseY) && highlight && !menu)
                {
                    Highlight(renderer, &tile);
                    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                        curTile = &tile;
                }
                for (Player &p : PM.getPlayerList())
                {
                    if (p.GetTile() == tile.getTileId())
                    {
                        p.RenderPlayer(renderer, &tile, PM);
                        break;
                    }
                }
            }

            // cout << curTile->getTileId() << endl;

            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                if (curTile)
                {
                    if (clicked == false)
                    {
                        for (Player &p : PM.getPlayerList())
                        {
                            if (p.GetTile() == curTile->getTileId() && p.getClicked() == false)
                            {
                                clickedPlayer = &p;
                                clickedPlayer->setClicked(true);
                                menu = true;
                                break;
                            }
                        }
                    }
                }
            }

            if (menu)
            {
                highlight = false;
                Menu curMenu = renderMenu(renderer, font, curTile, windowWidth, windowHeight);
                if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (curMenu.mouseCheck(mouseX, mouseY) == 1)
                    {
                        cout << clickedPlayer->getTeam() << endl;
                        if (clickedPlayer->getTeam() == "Team1")
                        {
                            cout << "Clicked Team 1" << endl;
                            GM.AddTeamScore1(GM.madeShot(curTile, clickedPlayer));
                        }
                        else if (clickedPlayer->getTeam() == "Team2")
                        {
                            cout << "Clicked Team 2" << endl;
                            GM.AddTeamScore2(GM.madeShot(curTile, clickedPlayer));
                        }

                        clicked = false;
                        menu = false;
                        highlight = true;
                        clickedPlayer->setClicked(false);
                        if (clickedPlayer != NULL)
                            GM.RenderShotPercent(renderer, font, windowWidth, windowHeight, clickedPlayer);
                    }

                    else if (curMenu.mouseCheck(mouseX, mouseY) == 2)
                    {
                        cout << "MOVE" << endl;
                        clicked = true;
                        menu = false;
                        highlight = true;
                        clickedPlayer->setClicked(false);
                    }
                }
            }

            else if (clicked == true)
            {
                highlight = true;
                if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                {
                    clickedPlayer->SetTile(curTile->getTileId());
                    clickedPlayer->setClicked(false);
                    clicked = false;
                }
            }

            GM.RenderShotPercent(renderer, font, windowWidth, windowHeight, clickedPlayer);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return true;
}

int main()
{
    if (!InitSDL())
    {
        return 1;
    }

    // Cleanup
    SDL_Quit();

    return 0;
}