#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureRectangle{
    public:
        TextureRectangle(SDL_Renderer*&);
        ~TextureRectangle();
        void SetRectangleParams(int, int, int, int);
        void Update();
        void Render(SDL_Renderer*&);
    private:
        SDL_Texture* m_texture;
        SDL_Rect src_rct;
        SDL_Rect dst_rct;
};