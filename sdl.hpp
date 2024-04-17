#ifndef SDL_HPP
#define SDL_HPP

#include <SDL.h>
#include <iostream>
#include "merkle.hpp"

const int NODE_WIDTH = 50;
const int NODE_HEIGHT = 50;

class SDLRenderer {
public:
    SDLRenderer(int screenWidth, int screenHeight);
    ~SDLRenderer();
    bool init();
    void clear();
    void present();
    void drawRect(int x, int y, int width, int height);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawTree(Node<int>* node, int x, int y, int level, SDLRenderer& renderer);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
};

#endif /* SDL_HPP */
