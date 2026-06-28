#pragma once

#include "raylib/raylib.h"

typedef struct Jogador {
    Rectangle ret;
    
    float velocidadeBase;
    float velocidadeAtual;
    
    Color cor;

    bool dashAtivo;
    int velocidadeDashBase;
    int velocidadeDashAtual;

} Jogador;

void entradaJogador( Jogador *j );
void atualizarJogador( Jogador *j, float delta );
void desenharJogador( Jogador *j );

