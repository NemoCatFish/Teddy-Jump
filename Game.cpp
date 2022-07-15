#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "Classes/App.h"
using std::string;
using std::to_string;

App Game = App("BearJump", Vector2(360, 640));
Player PlayerBear = Player(Vector2(200, 400), Game.Get_texture("Assets/Bear/Bear.png"));
SDL_Texture* GroundTex = Game.Get_texture("Assets/Ground/Grass Ground.png");
SDL_Texture* CloudTex = Game.Get_texture("Assets/Sky Elements/Clouds.png");

vector<Ground> Grounds = {Ground(Vector2(0, 400), GroundTex, 1), Ground(Vector2(150, 500), GroundTex, 2),
                          Ground(Vector2(250, 200), GroundTex, 3), Ground(Vector2(50, 120), GroundTex, 4)};

vector<Cloud> Clouds = {Cloud(CloudTex), Cloud(CloudTex), Cloud(CloudTex), Cloud(CloudTex)};

string ScoreText = "Score: ";
int ScoreNumber = 0;
char* FontPath = "Assets/Fonts/Cartoon3D.ttf";
char* LatoFontPath = "Assets/Fonts/Lato-Regular.ttf";
Sprite ScoreSprite = Sprite(Vector2(5, 5), Game.Get_Text(LatoFontPath, "Score: 0"),  Vector2(64, 32));

vector<Sprite> Texts = {Sprite(Vector2(50, 50), Game.Get_Text(FontPath, "Bear Game"), Vector2(256, 128)),
                        Sprite(Vector2(150, 150), Game.Get_Text(FontPath, "By Nour"), Vector2(192, 64)),
                        Sprite(Vector2(50, 500), Game.Get_Text(FontPath, "Press Any Button To Begin"), Vector2(256, 64))};

void Reload(){
    PlayerBear = Player(Vector2(200, 400), Game.Get_texture("Assets/Bear/Bear.png"));
    Grounds = {Ground(Vector2(0, 400), GroundTex, 1), Ground(Vector2(150, 500), GroundTex, 2),
                Ground(Vector2(250, 200), GroundTex, 3), Ground(Vector2(50, 120), GroundTex, 4)};
}

void main_loop(){
//    while (Game.Running){
        double Delta = Game.GetDelta();
        bool CameraUP = false;

        if (PlayerBear.Rect.y < 640 /3){
            CameraUP = true;
            PlayerBear.CameraMove(Delta);
                                        }
        else if (PlayerBear.Rect.y > 640){
            Reload();
            Game.CurrentScreen = "Died";
                                        }

        for (Cloud &c: Clouds){
            c.Loop(Delta);
                            }

        for (Ground &g: Grounds){
            if (CameraUP){
                g.CameraMove(Delta);
                if (g.Rect.y > 640 + 48){
                    g.Reload(Grounds);
                    ScoreNumber += 5;
                    ScoreSprite = Sprite(Vector2(5, 5), Game.Get_Text(LatoFontPath, (ScoreText + to_string(ScoreNumber)).c_str()),  Vector2(64, 32));
                                        }
                        }
                                }
        PlayerBear.Loop(Delta, Grounds);
        Game.Loop(PlayerBear, Grounds, Clouds, Texts, ScoreSprite);
//                        }
}

int main(){
    srand(time(0));
    SDL_Init( SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_OGG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 8192);
    Mix_Music* ThemeSong = Mix_LoadMUS("Assets/Sounds/GameTheme.ogg");
    Mix_PlayMusic(ThemeSong, -1);
    emscripten_set_main_loop(main_loop, 0, false);
}


