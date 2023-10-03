#define SDL_MAIN_HANDLED

#include <SDLManager.h>

// AHHHAAA INSIDE THE CPP_PROPERTIES IS WHERE YOU HAVE TO ADD THE EXTRA SDL FILES

// Try to find TTF cause its installed

using namespace std;

int main()
{
    SDLManager manager;
    if (!manager.InitSDL())
    {
        return 1;
    }

    // Cleanup
    SDL_Quit();

    return 0;
}