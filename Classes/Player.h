#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player: public Sprite{
    private:
        Vector2 Velocity = Vector2(0,-1);
        double FrameTime = 0;
        int CurrentFrame = 1;
        int Direction = 0;
        int Speed = 300;
        int Gravity = 60;
        int JumpForce = 30;
        bool JumpPressed = false;
        bool JumpReleased = true;

    public:
        Player(Vector2 pos, SDL_Texture* Tex):Sprite(pos, Tex, Vector2(46, 64)){}

        void CheckInput(){
            const Uint8* Key = SDL_GetKeyboardState( NULL );
            Direction = Key[SDL_SCANCODE_RIGHT] - Key[SDL_SCANCODE_LEFT];
            if (!Direction){
                Direction = Key[SDL_SCANCODE_D] - Key[SDL_SCANCODE_A];
                                }

            if (Key[SDL_SCANCODE_SPACE]){
                if (JumpReleased){
                    JumpPressed = true;
                                }
                                        }
            else{
                JumpReleased = true;
                }
                        }

        int Colliding(SDL_Rect* TempRect, vector<Ground> Plats){
            for (Ground &p: Plats){
                if (SDL_HasIntersection(TempRect, &p.Rect)){
                    return p.Rect.y;
                                                            }
                                    }
            return 0;
                        }

        void Move(double Delta, vector<Ground> Plats){
            Velocity.x = Direction * Speed * Delta;
            Velocity.y += Gravity * Delta;
            SDL_Rect TempRect = Rect;
            TempRect.y += Velocity.y;
            int PlatHeight = Colliding(&TempRect, Plats);
            if (PlatHeight){
                if (JumpPressed){
                    JumpReleased = false;
                    Velocity.y = -JumpForce;
                                }
                else if (Velocity.y > 0 && PlatHeight > Rect.y + 63){
                    Velocity.y = 0;
                                        }
                else{
                    Rect.y += Velocity.y;
                    }
                                            }
            else{
                Rect.y += Velocity.y;
                }

            if (Rect.x > 360){
                Rect.x = -64;
                            }
            else if (Rect.x < -64){
                Rect.x = 360;
                                }

            Rect.x += Velocity.x;
            JumpPressed = false;
                                                    }

        void Animate(double Delta){
            if (Velocity.y != 0){
                if (Velocity.y > 0){
                    SheetRect.x = 322;
                                    }
                else{
                    SheetRect.x = 276;
                    }
                                }
            else if (Velocity.x != 0){
                if (CurrentFrame > 2){
                    CurrentFrame = 1;
                                    }
                SheetRect.x = 138 + (46 * CurrentFrame);
                FrameTime += Delta;
                                    }

            else{
                SheetRect.x = 46 * (CurrentFrame - 1);
                FrameTime += Delta;
                }

            if (FrameTime > 0.2){
                if (CurrentFrame < 4){
                    CurrentFrame += 1;
                                    }
                else{
                    CurrentFrame = 1;
                    }
                FrameTime = 0;
                                }
                        }

        void Loop(double Delta, vector<Ground> Plats){
            CheckInput();
            Animate(Delta);
            Move(Delta, Plats);
                    }
};

#endif // PLAYER_H_INCLUDED
