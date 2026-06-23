#pragma once 

#include "raylib/raylib.h"
#include "Jogador.h"
#include "Alvo.h"

typedef struct Bola{

    float raio;
    
    Color cor;
    
    Vector2 centro;
    Vector2 velocidade;

}Bola;

void atualizarBola ( Bola *b, float delta);
void desenharBola (Bola *b);
void resolverColisaoJ (Bola *b, Jogador *j);
void resolverColisaoObs (Bola *b);
