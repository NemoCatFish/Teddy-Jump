#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED
#include <vector>
using std::vector;
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <emscripten.h>
#include "OwnMaths.h"
#include "Sprites.h"
#include "GroundElements.h"
#include "SkyElements.h"
#include "Player.h"

class App{
    private:
        double LastTick = 0;
        SDL_Window* Window;
        SDL_Renderer* Renderer;
        SDL_Event InputEvent;
    public:
        char* CurrentScreen = "Main";
        bool Running = true;
        App(char* Title, Vector2 Size){
            IMG_Init(IMG_INIT_PNG);
            TTF_Init();
            Window = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Size.x, Size.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                                    }
        void kill(){
            Running = false;
            SDL_DestroyRenderer(Renderer);
            SDL_DestroyWindow(Window);
            IMG_Quit();
            SDL_Quit();
            emscripten_cancel_main_loop();
                    }

        void InputCheck(){
            while (SDL_PollEvent(&InputEvent)){
                if (InputEvent.type == SDL_QUIT){
                    kill();
                    return;
                                                }
                else if (InputEvent.type == SDL_KEYDOWN){
                    if (CurrentScreen == "Died" | CurrentScreen == "Main"){
                        CurrentScreen = "Game";
                                                                        }
                                                        }
                                            }
                        }
        void UpdateWindow(Player p, vector<Ground> Grounds, vector<Cloud> Clouds, vector<Sprite> Texts, Sprite Score){
            SDL_RenderClear(Renderer);
            SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);

            for (Cloud &c: Clouds){
                SDL_RenderCopy(Renderer, c.Texture, &c.SheetRect, &c.Rect);
                                }

            if (CurrentScreen == "Game"){
                for (Ground &g: Grounds){
                    SDL_RenderCopy(Renderer, g.Texture, NULL, &g.Rect);
                                        }
                SDL_RenderCopy(Renderer, p.Texture, &p.SheetRect, &p.Rect);

                                        }
            else{
                for (Sprite &T: Texts){
                    SDL_RenderCopy(Renderer, T.Texture, NULL, &T.Rect);
                                            }
                }

            SDL_RenderCopy(Renderer, Score.Texture, NULL, &Score.Rect);
            SDL_SetRenderDrawColor(Renderer, 135, 206, 235, 0);
            SDL_RenderPresent(Renderer);
                            }

        double GetDelta(){
            double Delta = (SDL_GetTicks() - LastTick) / 1000.f;
            LastTick = SDL_GetTicks();
            return Delta;
                          }

        void Loop(Player p, vector<Ground> Grounds, vector<Cloud> Clouds, vector<Sprite> Texts, Sprite Score){
            InputCheck();
            UpdateWindow(p, Grounds, Clouds, Texts, Score);
                                                                        }

        SDL_Texture* Get_texture(char* path){
            SDL_Surface* surface = IMG_Load(path);
            SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, surface);
            SDL_FreeSurface(surface);
            return Texture;
                                            }

        SDL_Texture* Get_Text(char* FontPath, const char* Text){
            TTF_Font* Font = TTF_OpenFont(FontPath, 24);
            SDL_Color White = {0, 0, 0};
            SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, Text, White);
            SDL_Texture* TextTex = SDL_CreateTextureFromSurface(Renderer, TextSurface);
            return TextTex;
                                                        }

};

#endif // APP_H_INCLUDED
