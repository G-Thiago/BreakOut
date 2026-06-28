#pragma once

#include "raylib/raylib.h"

#include "GameWorld.h"

typedef struct RetBotoes{

    Rectangle ret;
    Color cor;


}RetBotoes;


void DesenharMenusIni_GameOver (EstadoJogo *estado);
void InteragirMenu (EstadoJogo *estado);
