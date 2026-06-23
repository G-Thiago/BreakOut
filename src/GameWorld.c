/**
 * @file GameWorld.c
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2026
 */
#include <stdio.h>
#include <stdlib.h>

#include "raylib/raylib.h"
//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

#include "GameWorld.h"
#include "Jogador.h"
#include "ResourceManager.h"

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld *createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    int largura = 150;
    int altura = 20;

    gw->jogador = (Jogador) {
        .ret = { (GetScreenWidth()/2) - largura/2, 
                  GetScreenHeight() - (3*altura), 
                  largura,  
                  altura },
        .velocidadeBase = 200,
        .velocidadeAtual = 0,
        .cor = WHITE
    };

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld( GameWorld *gw, float delta ) {

    entradaJogador ( &gw -> jogador);
    atualizarJogador ( &gw-> jogador,  delta);
}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( BLACK );

    desenharJogador( &gw->jogador );

    EndDrawing();

}