#pragma once

#include "raylib/raylib.h"

#include "Bolinha.h"
#include "Jogador.h"

typedef struct PowerUp{

    float velocidadeY;
    Vector2 centro;

    float raio;
    
    Color cor;

    bool ativo;

}PowerUp;

void desenharPowerUp ( PowerUp *pu);
void atualizarPowerUp ( PowerUp *pu, Jogador *j, Bola *b, float delta);
void ativarPowerUp (Bola *b, PowerUp *pu);