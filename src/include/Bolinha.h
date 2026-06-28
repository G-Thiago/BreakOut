#pragma once 

#include "raylib/raylib.h"

typedef struct Bola{

    float vidaAtual;

    float raio;
    
    Color cor;
    
    Vector2 centro;
    Vector2 velocidade;

    float danoAtual;
    bool danoAdcionado;
    float timer;
    
}Bola;



void atualizarBola ( Bola *b, float delta);
void desenharBola (Bola *b);
void DesenharVida (Bola *b);


