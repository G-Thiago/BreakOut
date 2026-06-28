#include <stdlib.h>
#include <math.h>
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

        b -> centro.x = GetScreenWidth() - (b-> raio );
        b -> velocidade.x *= -1;
    
    
    }if ( b -> centro.y - b -> raio <= 0){

        b -> centro.y = b -> raio;
        b -> velocidade.y *= -1;


    }
    if ( abs(b -> velocidade.x >= 350) || abs(b -> velocidade.y >= 350)){

        
            float direcaoX = ( b -> velocidade.x >= 0 ) ? 1.0f : -1.0f;
            float direcaoY = ( b -> velocidade.y >= 0 ) ? 1.0f : -1.0f; 
        
        b -> velocidade = (Vector2) {

            .x = (350 + GetRandomValue(-20,20)) * direcaoX,
            .y = (350 + GetRandomValue(-20, 20)) * direcaoY,

        };

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