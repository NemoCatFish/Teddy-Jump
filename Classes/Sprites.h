#ifndef SPRITES_H_INCLUDED
#define SPRITES_H_INCLUDED

class Sprite{
    private:
        int CameraSpeed = 300;
    public:
        SDL_Rect Rect;
        SDL_Rect SheetRect = {0, 0, 0, 0};
        SDL_Texture* Texture;
        Sprite(Vector2 Pos, SDL_Texture* Tex, Vector2 Size){
            Rect.x = Pos.x; Rect.y = Pos.y; Rect.w = Size.x; Rect.h = Size.y;
            Texture = Tex; SheetRect.h = Size.y; SheetRect.w = Size.x;
                                                            }
        void CameraMove(double Delta){
            Rect.y += CameraSpeed * Delta;
                                }
};

#endif // SPRITES_H_INCLUDED
