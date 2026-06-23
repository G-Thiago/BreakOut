#pragma once 

#include "raylib/raylib.h"

typedef struct Bola{

    int raio;
    int velocidadeBase;
    int velocidadeAtual;
    Color cor;

}Bola;

void atualizarBola ( Bola *b, float delta);
void desenharBola (Bola *b);