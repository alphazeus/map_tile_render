#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class pinClass{
    public:
        pinClass(SDL_Renderer*&);
        ~pinClass();
        void SetSrcRectParams(int, int, int, int);
        void SetDstRectParams(int, int, int, int);
        void Update(int, int, int, int, int, int);
        void Render(SDL_Renderer*&);
    private:
        SDL_Texture* m_texture;
        SDL_Rect src_rct;
        SDL_Rect dst_rct;
};


