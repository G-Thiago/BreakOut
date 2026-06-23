/**
 * @file GameWorld.c
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2026
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib/raylib.h"
//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

#include "GameWorld.h"

#include "Jogador.h"
#include "Bolinha.h"

#include "ResourceManager.h"

void resolverColisaoBolinhaAlvos (Bola *b, Alvo *alvos, int quantidade);
void resolverColisaoBolinhaJogador (Bola *b, Jogador *j);
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

    gw -> bolinha = (Bola){

        .raio = 10,
        .cor = WHITE,
        .centro = {
            GetScreenWidth()/2,
            gw -> jogador.ret.y - gw -> jogador.ret.height,
        },

        .velocidade = {
            200,
            -200,
        }

    };
    
    gw -> lin = 10;
    gw -> col = 6;

    gw -> alvos = (Alvo*) malloc ( sizeof( Alvo ) * gw -> lin * gw -> col);
    
    //Baseado na coluna e linha que estou, faremos os alvos serem criados

    Color cores[10] = {

        RED, 
        BLUE, 
        RED, 
        BLUE, 
        RED, 
        BLUE, 
        RED, 
        BLUE, 
        RED, 
        BLUE,


    };

    int larguraAlvo = 80;
    int alturaAlvo = 20;
    int espaço = 5;
   
    int larguraTotal = larguraAlvo * gw -> col + espaço * (gw -> col - 1);

    int xIni = GetScreenWidth()/2 - larguraTotal/2;
    int yIni = 150;
   
    for ( int i = 0; i < gw -> lin; i++){
        for ( int j = 0; j < gw -> col; j++){

            int p = i * gw -> col + j;

            gw -> alvos[p] = (Alvo){

                .ret = {

                    .x = xIni + j * (larguraAlvo + espaço),
                    .y = yIni + i * (alturaAlvo + espaço),
                    .width = larguraAlvo,
                    .height = alturaAlvo,

                },
                .cor = cores[i],
                .hp = 1,


            };
        }
    }

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
    atualizarJogador ( &gw -> jogador,  delta);
    atualizarBola (&gw -> bolinha, delta);
    resolverColisaoBolinhaAlvos ( &gw -> bolinha, gw -> alvos, gw-> lin * gw-> col);
    resolverColisaoJ (&gw -> bolinha, &gw -> jogador);
}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( BLACK );

    desenharJogador( &gw->jogador );
    desenharBola (&gw -> bolinha);
    desenharAlvos (gw -> alvos, (gw -> lin * gw -> col));

    EndDrawing();

}

void resolverColisaoBolinhaAlvos (Bola *b, Alvo *alvos, int quantidade){

    for ( int i = 0; i < quantidade; i++){

        Alvo *alvo = &alvos[i];
        
        if (CheckCollisionCircleRec ( b -> centro, b -> raio, alvo -> ret) && alvo -> hp > 0){
         
            alvo->hp--;
            b -> centro.y = alvo -> ret.y + alvo -> ret.height + b -> raio;
            b -> velocidade.y = fabs ( b -> velocidade.y);
        }

    }
}

void resolverColisaoBolihaJogador (Bola *b, Jogador *j){


   if ( CheckCollisionCircleRec ( b -> centro, b -> raio, j -> ret)){

        b -> velocidade.y *= -1;
    
    }



}

