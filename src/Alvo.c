#include <stdlib.h>

#include "raylib/raylib.h"

#include "Alvo.h"
#include <stdio.h>

void desenharAlvo ( Alvo *a){

    if ( a -> hp > 0){
    
        DrawRectangleRec ( a -> ret, a -> cor);
    
    }
    

}

void desenharAlvos ( Alvo *alvos, int quantidade){

    for ( int i = 0; i < quantidade; i++){

        desenharAlvo (&alvos[i]);
    }

}

void desenharVidaAlvo(Alvo *a){

    if (a->hp <= 0)
        return;

    if (a->hp == a->hpmax)
        return;

    float porcentagem = (float)a->hp / a->hpmax;

    DrawRectangle(
        (int)a->ret.x,
        (int)a->ret.y - 8,
        (int)a->ret.width,
        5,
        DARKGRAY
    );

    DrawRectangle(
        (int)a->ret.x,
        (int)a->ret.y - 8,
        (int)(a->ret.width * porcentagem),
        5,
        GREEN
    );


}
