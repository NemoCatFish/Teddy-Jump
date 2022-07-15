#ifndef GROUNDELEMENTS_H_INCLUDED
#define GROUNDELEMENTS_H_INCLUDED
#include <cstdlib>

class Ground: public Sprite{
    private:
        int Index = 0;
    public:
        Ground(Vector2 Pos, SDL_Texture* Tex, int index): Sprite(Pos, Tex, Vector2(144, 48)){
            Index = index;
                                                                                        }

        void Reload(vector<Ground> Grounds){
            Rect.x = rand() %(360 - 144);
            Rect.y = rand() %(320 - 48) + 48;
            Rect.w = (rand() %144) + 72;
            int ID = 1;
            for (Ground &g: Grounds){
                if (ID != Index){
                    if (abs(Rect.y - g.Rect.y) < 96){
                        Reload(Grounds);
                                                    }
                                }
            ID += 1;
                                    }
                    }
};

#endif // GROUNDELEMENTS_H_INCLUDED
