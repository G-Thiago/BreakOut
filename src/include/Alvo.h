#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "raylib/raylib.h"

typedef struct Alvo{

    Rectangle ret;
    Color cor;
    
    bool temPowerUp;
    
    int pontuacaoObtida;
    int pontuacaoAtual;
    int hp;


}Alvo;

void desenharAlvo ( Alvo *a);
void desenharAlvos ( Alvo *alvos, int quantidade);
