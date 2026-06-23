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

void desenharPontuacao (Alvo *a){

    int Fonte = 50;
    int Margem = 30;
    int Fim_eixoX = GetScreenWidth();

    const char *Score = TextFormat ("%d", a -> pontuacaoAtual);
    int larguraScore = MeasureText (Score, Fonte);

    DrawText(Score, 
             Fim_eixoX - (Margem + larguraScore),
             20, 
             Fonte, 
             WHITE);


}