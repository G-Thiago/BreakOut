#pragma once

#include "raylib/raylib.h"

typedef struct Jogador {
    Rectangle ret;
    float velocidade;
    Color cor;
} Jogador;

void entradaJogador( Jogador *j );
void atualizarJogador( Jogador *j, float delta );
void desenharJogador( Jogador *j );
