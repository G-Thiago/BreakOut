#include <stdlib.h>


#include "raylib/raylib.h"

#include "Jogador.h"

void entradaJogador( Jogador *j ) {

    int esquerda = IsKeyDown(KEY_LEFT ) ? -1 : 0;
    int direita = IsKeyDown(KEY_RIGHT) ? 1 : 0;
    int movimento = esquerda + direita;

    
    int dashEsquerda = IsKeyPressed(KEY_A) ? -1 : 0;
    int dashDireita = IsKeyPressed (KEY_D) ? 1 : 0;
    int dash = dashEsquerda + dashDireita;
       
        if ( dash != 0 ){

            j -> dashAtivo = true;

        }

    j -> velocidadeAtual = j -> velocidadeBase * movimento;
    j -> velocidadeDashAtual = j -> velocidadeDashBase * dash;
}

void atualizarJogador( Jogador *j, float delta ) {

    j -> ret.x += j -> velocidadeAtual * delta;


    if ( j -> ret.x + j -> ret.width >= GetScreenWidth()){

        j -> ret.x = GetScreenWidth() - j -> ret.width;

    }else if ( j -> ret.x  <= 0.0f){

        j -> ret.x = 0;
    }

    if ( j -> dashAtivo == true){

        j -> ret.x += j -> velocidadeDashBase * j -> velocidadeDashAtual * delta ;
    }
}

void desenharJogador( Jogador *j ) {
    DrawRectangleRec( j->ret, j->cor );

}

