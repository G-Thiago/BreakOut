#include <stdlib.h>

#include "raylib/raylib.h"

#include "Bolinha.h"

void desenharBola (Bola *b){

    DrawCircle(b -> centro.x, b-> centro.y, b -> raio, b -> cor);



}

void atualizarBola ( Bola *b, float delta){

    b -> centro.x += b -> velocidade.x * delta;
    b -> centro.y += b -> velocidade.y * delta;

    if ( b -> centro.x - b -> raio <= 0){

        b -> centro.x = b -> raio;
        b -> velocidade.x *= -1;

    }else if ( b -> centro.x + b -> raio >= GetScreenWidth()){

        b -> centro.x = GetScreenWidth() - b-> raio;
        b -> velocidade.x *= -1;
    
    
    }if ( b -> centro.y - b -> raio <= 0){

        b -> centro.y = b -> raio;
        b -> velocidade.y *= -1;


    }else if ( b -> centro.y + b -> raio >= GetScreenHeight()){

        b -> centro.y = GetScreenHeight() - b -> raio;
        b -> velocidade.y *= -1;

    }

}

void resolverColisaoJ (Bola *b, Jogador *j){


   if ( CheckCollisionCircleRec ( b -> centro, b -> raio, j -> ret)){

        b -> centro.y = b -> centro.y - b -> raio;
        b -> velocidade.y *= -1;
    
    }



}




