#include "sdl.hpp"

SDLRenderer::SDLRenderer(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {
    window = NULL;
    renderer = NULL;
}

SDLRenderer::~SDLRenderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool SDLRenderer::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    return true;
}

void drawTree(Node<int>* node, int x, int y, int level, SDLRenderer& renderer) {
    if (node == nullptr) {
        return;
    }

    // Draw node
    renderer.drawRect(x, y, NODE_WIDTH, NODE_HEIGHT);

    // Draw left child
    if (node->left != nullptr) {
        int childX = x - 100 / (1 << level); // Adjust x-coordinate based on level
        int childY = y + 100; // Adjust y-coordinate for child node
        renderer.drawLine(x + NODE_WIDTH / 2, y + NODE_HEIGHT, childX + NODE_WIDTH / 2, childY);
        drawTree(node->left, childX, childY, level + 1, renderer);
    }

    // Draw right child
    if (node->right != nullptr) {
        int childX = x + 100 / (1 << level); // Adjust x-coordinate based on level
        int childY = y + 100; // Adjust y-coordinate for child node
        renderer.drawLine(x + NODE_WIDTH / 2, y + NODE_HEIGHT, childX + NODE_WIDTH / 2, childY);
        drawTree(node->right, childX, childY, level + 1, renderer);
    }
}

void SDLRenderer::clear() {
    SDL_RenderClear(renderer);
}

void SDLRenderer::present() {
    SDL_RenderPresent(renderer);
}

void SDLRenderer::drawRect(int x, int y, int width, int height) {
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderDrawRect(renderer, &rect);
}

void SDLRenderer::drawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}