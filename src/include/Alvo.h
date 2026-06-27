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

typedef struct PowerUp{

    float velocidadeY;
    Vector2 centro;

    float raio;
    
    Color cor;

    bool ativo;

}PowerUp;

void desenharAlvo ( Alvo *a);
void desenharAlvos ( Alvo *alvos, int quantidade);

void desenharPowerUp ( PowerUp *pu);
void atualizarPowerUp (PowerUp *pu, float delta);
