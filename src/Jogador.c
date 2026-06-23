#include <stdlib.h>

#include "raylib/raylib.h"

#include "Jogador.h"

void entradaJogador( Jogador *j ) {

    if (IsKeyDown(KEY_LEFT)){

        j -> velocidadeAtual = -j -> velocidadeBase;

    }else if (IsKeyDown(KEY_RIGHT)){

        j -> velocidadeAtual = j -> velocidadeBase;

    }else{
        j -> velocidadeAtual = 0;
    }
}

void atualizarJogador( Jogador *j, float delta ) {

    j -> ret.x += j -> velocidadeAtual * delta;

    if ( j -> ret.x + j -> ret.width >= GetScreenWidth()){

        j -> ret.x = GetScreenWidth() - j -> ret.width;

    }else if ( j -> ret.x  <= 0.0f){

        j -> ret.x = 0;
    }
}

void desenharJogador( Jogador *j ) {
    DrawRectangleRec( j->ret, j->cor );

}