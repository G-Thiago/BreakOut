#include <stdlib.h>

#include "raylib/raylib.h"

#include "Alvo.h"

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
void desenharPowerUp ( PowerUp *pu){
  
    DrawCircle( pu -> centro.x, pu -> centro.y, pu -> raio, pu -> cor);

}

void atualizarPowerUp (PowerUp *pu, float delta){

    pu -> centro.y += pu -> velocidadeY * delta;

    if ( pu -> centro.y >= GetScreenHeight()){

        pu -> ativo = false;

    }


}
