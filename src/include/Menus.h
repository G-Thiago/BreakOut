#pragma once

#include "raylib/raylib.h"

#include "GameWorld.h"

typedef struct RetBotoes{

    Rectangle ret;
    Color cor;


}RetBotoes;


void DesenharGameOver (void);
void DesenharMenuInicial(void);

void InteragirMenu (EstadoJogo *estado);
