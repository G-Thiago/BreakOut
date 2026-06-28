#include <stdlib.h>

#include "raylib/raylib.h"


#include "PowerUp.h"

void desenharPowerUp ( PowerUp *pu){
    
    if ( pu -> ativo){
        DrawCircle( pu -> centro.x, pu -> centro.y, pu -> raio, pu -> cor);

    }
}

void atualizarPowerUp ( PowerUp *pu, Jogador *j, Bola *b, float delta){
    
    if ( !pu -> ativo ) return;

    pu -> centro.y += pu -> velocidadeY * delta;

    if ( pu -> centro.y >= GetScreenHeight()){

        pu -> ativo = false;

    }

    if ( CheckCollisionCircleRec( pu -> centro, pu -> raio, j -> ret)){

        pu -> ativo = false;

        ativarPowerUp ( b, pu);

    }
        

    

}

void ativarPowerUp (Bola *b, PowerUp *pu){

    int decidirPowerUp = GetRandomValue ( 1, 3);

    switch (decidirPowerUp){

        case 1:

        if ( b -> vidaAtual < 3){

            b -> vidaAtual ++;

        }
        
        break;


        case 2:
        
        if ( b -> danoAtual <= 5){
        
            b -> danoAtual += 2;
            b -> timer = 10;
            b -> cor = RED;
        
        }
        break;

        case 3:
        
        


}
