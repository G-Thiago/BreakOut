#pragma once

#include "raylib/raylib.h"


typedef struct RetBotoes{

    Rectangle ret;
    Color cor;


}RetBotoes;


void DesenharVitoria (void);

void DesenharMenusIni_GameOver (EstadoJogo *estado);
void InteragirMenu (EstadoJogo *estado);
