#include <stdlib.h>

#include "raylib/raylib.h"
#include "GameWorld.h"

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


    }

}
void DesenharVida (Bola *b){

    int raioVida = 20;
    int espaço = 5;
    int tamanhoBarraVida = 2 * raioVida + espaço;
    
    int xIni = 40;
    int yIni = 30;

    for ( int i = 0; i < b -> vidaAtual; i++){

        int xAtual = xIni + ( i * ( tamanhoBarraVida));
        DrawCircle ( xAtual, yIni, raioVida, RED);

    }


}





















