#ifndef OWNMATHS_H_INCLUDED
#define OWNMATHS_H_INCLUDED

class Vector2{
    public:
        int x; int y;
        Vector2(){x = 0; y = 0;}
        Vector2(int X_Component, int Y_Component){x = X_Component; y = Y_Component;}

        double len(){
            return sqrt(x*x + y*y);
                    }
};

#endif // OWNMATHS_H_INCLUDED
