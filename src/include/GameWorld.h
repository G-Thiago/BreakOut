/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2026
 */
#pragma once

#define BOLAS_MAX 4
typedef enum EstadoJogo{

    INICIO,
    JOGANDO,
    AGUARDANDO,
    GAMEOVER,
    

}EstadoJogo;

#include "Alvo.h"
#include "Jogador.h"
#include "Bolinha.h"
#include "Menus.h"
#include "PowerUp.h"
#include <time.h>

typedef struct GameWorld {
    
    EstadoJogo estado;    
    Alvo *alvos;
    Bola bolinha;
    Jogador jogador;
    PowerUp powerup;
    
    int lin;
    int col;
    int pontuacaoAtual;
    
} GameWorld;


/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld *createGameWorld( void );

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw );

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld( GameWorld *gw, float delta );

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw );

void resolverColisaoBolinhaAlvos (Bola *b, Alvo *alvos, GameWorld *gw, int quantidade);
void resolverColisaoBolinhaJogador (Bola *b, Jogador *j);
void ResetarBola_eJogo (Bola *b, EstadoJogo *estado, Jogador *j);
void desenharPontuacao (Alvo *a, int PontucaoAtual, GameWorld *gw);
void resetAlvos(GameWorld *gw);

Color sortearCorPlanoFundo (EstadoJogo *estado);
