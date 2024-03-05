#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureRectangle{
    public:
        TextureRectangle();
        TextureRectangle(SDL_Renderer*&, std::string);
        ~TextureRectangle();
        void SetSrcRectParams(int, int, int, int);
        void SetDstRectParams(int, int, int, int);
        void Update();
        void Render(SDL_Renderer*&);
        int printl();
    private:
        SDL_Texture* m_texture;
        SDL_Rect src_rct;
        SDL_Rect dst_rct;
};