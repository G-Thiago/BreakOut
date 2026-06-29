#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "raylib/raylib.h"
#include "Jogador.h"
typedef struct Alvo{

    Rectangle ret;
    Color cor;
    
    bool temPowerUp;
    
    int pontuacaoObtida;
    int pontuacaoAtual;
    int hp;
    int hpmax;


}Alvo;

void desenharVidaAlvo( Alvo *a);
void desenharAlvo ( Alvo *a);
void desenharAlvos ( Alvo *alvos, int quantidade);


