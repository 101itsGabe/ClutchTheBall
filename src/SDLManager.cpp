#include <SDLManager.h>

SDLManager::SDLManager()
{
}

void SDLManager::RenderStart(SDL_Renderer* renderer, int windowWidth, int windowHeight, TTF_Font *font){
        SDL_RenderClear(renderer);
        SDL_Surface *neshaSurface = IMG_Load("./src/images/SBG.png");
            if (neshaSurface)
                {
                    SDL_Texture *shilohTexture = SDL_CreateTextureFromSurface(renderer, neshaSurface);
                    if (shilohTexture)
                    {
                        SDL_Rect rect = {0, 0, windowWidth, windowHeight};
                        SDL_RenderCopy(renderer, shilohTexture, NULL, &rect);
                        SDL_DestroyTexture(shilohTexture);
                    }
                }

        int rW = (windowWidth*0.18);
        int rH = windowHeight*0.18;
        int rX = (windowWidth/2) - rW/2;
        int rY = (windowHeight/2) - rH/2;
        SDL_Rect startRect = {rX, rY, rW, rH};
        SDL_Color color={0,0,0};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font,"Start",color);
        if(textSurface){
            SDL_Texture* tt = SDL_CreateTextureFromSurface(renderer,textSurface);
            if(tt){
                SDL_RenderCopy(renderer, tt,NULL, &startRect);
            }
            SDL_DestroyTexture(tt);
        }
        SDL_FreeSurface(textSurface);
        SDL_FreeSurface(neshaSurface);
}

bool SDLManager::InitSDL()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    // SDL_Surface* imageSurface = NULL; //Surface to load image
    TTF_Font *font = NULL;
    SDL_Surface *image = NULL;

    PlayerManager PM(6);
    GameManager GM(*PM.getPlayerList());

    // Window
    int windowWidth, windowHeight;

    vector<Tile> *tiles;

    TileManager TM;
    tiles = TM.getTileList();

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

    // Show the updated Frame
    SDL_RenderPresent(renderer);

    // Main Loop

    SDL_Event e;
    bool quit = false;
    bool clicked = false;
    bool menu = false;
    bool highlight = true;
    bool move = false;
    bool pass = false;
    Player *clickedPlayer = nullptr;
    bool StartUp = true;
    int mouseX, mouseY;
    GM.SetBallPlayer((*PM.getPlayerList())[0]);
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            SDL_GetWindowSize(window, &windowWidth, &windowHeight);
            SDL_GetMouseState(&mouseX, &mouseY);
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            if (StartUp)
            {
                RenderStart(renderer, windowWidth, windowHeight, font);
            }
            else
            {
                Tile *curTile = nullptr;
                SDL_RenderClear(renderer);
                renderBackground(renderer, backgroundTexture, windowWidth, windowHeight);
                GM.RenderScore(renderer, font, windowWidth, windowHeight);

                TM.renderTiles(renderer, windowWidth, windowHeight);
                GM.renderAllText(renderer, tiles, font);

                for (Tile &tile : *tiles)
                {
                    if (tile.getMouseCheck(mouseX, mouseY) && highlight && !menu)
                    {
                        Highlight(renderer, &tile);
                        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                        {
                            curTile = &tile;
                            break;
                        }
                    }
                }

                GM.RenderBall(renderer, tiles);
                if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                {
                    if (curTile)
                    {
                        if (clicked == false && menu == false && pass == false)
                        {
                            for (Player &p : *PM.getPlayerList())
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

                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b)
                {
                    move = true;
                }

                PM.RenderPlayers(renderer, tiles);
                GM.RenderBall(renderer, tiles);
                if (menu)
                {
                    highlight = false;
                    Menu curMenu = renderMenu(renderer, font, TM.getTileList(), windowWidth, windowHeight, clickedPlayer);
                    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (curMenu.mouseCheck(mouseX, mouseY) == 1)
                        {
                            cout << clickedPlayer->getTeam() << endl;
                            if (clickedPlayer->getTeam() == "Team1")
                            {
                                cout << "Clicked Team 1" << endl;
                                GM.AddTeamScore1(GM.madeShot(curTile, clickedPlayer, *PM.getPlayerList()));
                            }
                            else if (clickedPlayer->getTeam() == "Team2")
                            {
                                cout << "Clicked Team 2" << endl;
                                GM.AddTeamScore2(GM.madeShot(curTile, clickedPlayer, *PM.getPlayerList()));
                            }

                            clicked = false;
                            menu = false;
                            highlight = true;
                            clickedPlayer->setClicked(false);
                        }

                        else if (curMenu.mouseCheck(mouseX, mouseY) == 2)
                        {
                            cout << "MOVE" << endl;
                            clicked = true;
                            menu = false;
                            highlight = true;
                            clickedPlayer->setClicked(false);
                        }

                        else if (curMenu.mouseCheck(mouseX, mouseY) == 3 && clickedPlayer->GetTile() == GM.getBallTile())
                        {
                            cout << "Pass" << endl;
                            menu = false;
                            highlight = true;
                            pass = true;
                        }
                    }
                    if (clickedPlayer != NULL)
                        GM.RenderShotPercent(renderer, font, windowWidth, windowHeight, clickedPlayer, PM.getPlayerList());

                    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        clicked = false;
                        menu = false;
                        highlight = true;
                        clickedPlayer->setClicked(false);
                    }
                }

                else if (clicked)
                {
                    highlight = true;
                    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                    {
                        PM.SetPlayerTile(clickedPlayer, curTile->getTileId());
                        // clickedPlayer->SetTile(curTile->getTileId());
                        clickedPlayer->setClicked(false);
                        clicked = false;
                    }
                }
                else if (move)
                {
                    GM.MoveAI(PM.getPlayerList());
                    PM.RenderPlayers(renderer, TM.getTileList());
                    move = false;
                }

                else if (pass)
                {
                    clickedPlayer->setClicked(false);
                    bool playerCheck = false;
                    bool tileCheck = true;
                    menu = false;
                    if (tileCheck)
                    {
                        for (Tile &tile : *tiles)
                        {
                            if (tile.getMouseCheck(mouseX, mouseY) && !menu)
                            {
                                if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                                {
                                    curTile = &tile;
                                    playerCheck = true;
                                    tileCheck = false;
                                    break;
                                }
                            }
                        }
                    }
                    if (playerCheck)
                    {
                        for (Player &p : *PM.getPlayerList())
                        {
                            if (curTile && curTile->getTileId() == p.GetTile())
                            {
                                GM.SetBallPlayer(p);
                                pass = false;
                                clickedPlayer = nullptr;
                                playerCheck = false;
                            }
                        }
                    }
                }
            }
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return true;
}

void SDLManager::Highlight(SDL_Renderer *renderer, Tile *tile)
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

void SDLManager::renderBackground(SDL_Renderer *renderer, SDL_Texture *texture, int windowWidth, int windoHeight)
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = windowWidth;
    rect.h = windoHeight;

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

Menu SDLManager::renderMenu(SDL_Renderer *renderer, TTF_Font *font, vector<Tile> *tList, int windowWidth, int windowHeight, Player *p)
{
    SDL_Rect rect;
    Menu curMenu(windowWidth, windowHeight);
    vector<string> textList = {"Shoot", "Move", "Pass"};
    curMenu.setText(textList);
    curMenu.setData(p, tList, windowWidth);
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
