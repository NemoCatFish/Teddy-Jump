#ifndef SKYELEMENTS_H_INCLUDED
#define SKYELEMENTS_H_INCLUDED
#include <iostream>
#include <cstdlib>
using std::rand;
using std::srand;

class Cloud: public Sprite{
    private:
        int Direction = 1;
    public:
        int Speed = (rand() %30) + 100;

        void ReloadCloud(){
            Rect.x = rand() %2 * 360;
            Rect.y = (rand() %500) + 32;
            SheetRect.x = rand() %5 * 64;
            int Size =  rand() %64 + 64;
            Rect.w = Size;
            Rect.h = Size;
            Speed = (rand() %30) + 100;
            if (Rect.x > 300){
                Direction = -1;
                            }
            else{
                Direction = 1;
                }
                        }

        Cloud(SDL_Texture* Texture):Sprite(Vector2(0, 0), Texture, Vector2(64, 64)){
            ReloadCloud();
                                                                                    }

        void Loop(double Delta){
            if (Rect.x > -100 && Rect.x < 400){
                Rect.x += Speed * Direction * Delta;
                                        }
            else{
                ReloadCloud();
                }
                    }
};

#endif // SKYELEMENTS_H_INCLUDED
