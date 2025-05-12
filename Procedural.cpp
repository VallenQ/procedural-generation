#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

class SDL2 {
public:
    SDL_Window* window = nullptr;
    SDL_Renderer* gRenderer = nullptr;

    SDL2() {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    }

    ~SDL2() {
        Destroy();
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void Init(int windowW, int windowH, const std::string& headerName) {
        window = SDL_CreateWindow(headerName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowW, windowH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(gRenderer);
    }

    void Destroy() {
        if (gRenderer) SDL_DestroyRenderer(gRenderer);
        if (window) SDL_DestroyWindow(window);
        gRenderer = nullptr;
        window = nullptr;
    }

    void RenderRefresh() {
        SDL_RenderPresent(gRenderer);
    }
};

// Helper functions
SDL_Rect CreateRect(int x, int y, int w, int h) {
    SDL_Rect rect = { x, y, w, h };
    return rect;
}

void RenderRectColor(SDL_Renderer* grenderer, SDL_Rect* rect, int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(grenderer, r, g, b, alpha);
    SDL_RenderFillRect(grenderer, rect);
}

// Enums for tile types
enum TileType {
    WATER,
    SAND,
    GRASS,
    DIRT
};

// Function to generate a random tile based on the transition matrix
TileType GenerateTile(TileType previous, double transitionMatrix[4][4]) {
    double randValue = (double)rand() / RAND_MAX;
    double cumulative = 0.0;

    for (int i = 0; i < 4; ++i) {
        cumulative += transitionMatrix[previous][i];
        if (randValue < cumulative) {
            return static_cast<TileType>(i);
        }
    }

    return WATER; // Default fallback
}

// Function to generate the map based on the seed and transition matrix
void GenerateMap(SDL2& sdl, int rows, int cols, int tileSize, const std::string& seed) {
    // Seed the random generator
    srand(std::hash<std::string>{}(seed));

    // Transition matrix - each row sums to 1.0
    double transitionMatrix[4][4] = {
        {0.6, 0.2, 0.1, 0.1}, // WATER -> WATER, SAND, GRASS, DIRT
        {0.3, 0.4, 0.2, 0.1}, // SAND -> WATER, SAND, GRASS, DIRT
        {0.1, 0.2, 0.5, 0.2}, // GRASS -> WATER, SAND, GRASS, DIRT
        {0.1, 0.1, 0.2, 0.6}  // DIRT -> WATER, SAND, GRASS, DIRT
    };

    // Create initial tile type (starting point)
    TileType currentTile = WATER;

    // Iterate through each cell in the grid
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Generate the next tile based on the transition matrix
            currentTile = GenerateTile(currentTile, transitionMatrix);

            // Set the color based on the tile type
            int r, g, b;
            switch (currentTile) {
                case WATER: r = 0; g = 0; b = 255; break;    // Blue for water
                case SAND:  r = 255; g = 255; b = 0; break;  // Yellow for sand
                case GRASS: r = 0; g = 255; b = 0; break;    // Green for grass
                case DIRT:  r = 139; g = 69; b = 19; break;  // Brown for dirt
            }

            // Create the rectangle for the tile
            SDL_Rect tileRect = CreateRect(j * tileSize, i * tileSize, tileSize, tileSize);
            RenderRectColor(sdl.gRenderer, &tileRect, r, g, b, 255);
        }
    }

    // Render all tiles to the screen
    sdl.RenderRefresh();
}

int main(int argc, char* argv[]) {
    // Initialize SDL and create a window
    SDL2 sdl;
    sdl.Init(800, 600, "Map");

    // Define grid size and tile size
    int rows = 30;
    int cols = 40;
    int tileSize = 20;

    // Seed value (can be changed to any string)
    std::string seed = "redstone";

    // Generate the map based on the seed
    GenerateMap(sdl, rows, cols, tileSize, seed);

    // Main loop to keep the window open
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    return 0;
}
