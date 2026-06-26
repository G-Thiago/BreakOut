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


int largura = 150;
int altura = 20;

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld *createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

   

    gw->jogador = (Jogador) {
        .ret = { (GetScreenWidth()/2) - largura/2, 
                  GetScreenHeight() - (3*altura), 
                  largura,  
                  altura },
        .velocidadeBase = 200,
        .velocidadeAtual = 0,
        .cor = WHITE,
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
        },
        .vidaAtual = 3,

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
                .hp = i <= 5 ? 
                      (i * -1) + 6 :
                      1,
                .pontuacaoObtida = 1 <= 5 ?
                                   (i * -50) + 600:
                                   100,
                .pontuacaoAtual = 0,
            };
        }
    }

    
    gw -> estado = INICIO;

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
    
    switch ( gw -> estado ){

        case INICIO:
               
        InteragirMenu( &gw -> estado);

        break;

        case JOGANDO:

        entradaJogador ( &gw -> jogador);
        atualizarJogador ( &gw -> jogador,  delta);
        atualizarBola (&gw -> bolinha, delta);
        resolverColisaoBolinhaAlvos ( &gw -> bolinha, gw -> alvos, gw, gw-> lin * gw-> col);
        resolverColisaoBolinhaJogador (&gw -> bolinha, &gw -> jogador);
        ResetarBola_eJogo (&gw -> bolinha, &gw -> estado, &gw -> jogador);
        
        break; 

        case AGUARDANDO:

        gw -> bolinha.centro.x = GetScreenWidth()/2;
        gw -> bolinha.centro.y = gw -> jogador.ret.y - gw -> jogador.ret.height;

        if (IsKeyPressed(KEY_SPACE)){

            gw -> estado = JOGANDO;
        }

        break;

        case GAMEOVER:

        InteragirMenu( &gw -> estado);
        gw -> bolinha.vidaAtual = 3;
        gw -> pontuacaoAtual = 0;

        break;

    }   
}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    
    if ( gw -> estado == INICIO){
         
        DesenharMenuInicial( );
    }
    
    
    if ( gw -> estado == AGUARDANDO || gw -> estado == JOGANDO){
        
        ClearBackground( BLACK );

        desenharPontuacao (gw -> alvos, gw-> pontuacaoAtual, gw);
        desenharJogador( &gw->jogador );
        desenharBola (&gw -> bolinha);
        desenharAlvos (gw -> alvos, (gw -> lin * gw -> col));
        DesenharVida (&gw -> bolinha);
    
    }if ( gw -> estado == GAMEOVER){
        
        DesenharGameOver();
        

    }    


        
        EndDrawing();
    

    
}

void resolverColisaoBolinhaAlvos (Bola *b, Alvo *alvos, GameWorld *gw, int quantidade){

    for ( int i = 0; i < quantidade; i++){

        Alvo *alvo = &alvos[i];
        
        if (CheckCollisionCircleRec ( b -> centro, b -> raio, alvo -> ret) && alvo -> hp > 0){
         
            alvo->hp--;
            
            float centroAlvox = alvo -> ret.x + alvo -> ret.width / 2.0f;
            float centroAlvoy = alvo -> ret.y + alvo -> ret.height / 2.0f;

            float SobreposicaoX = ( b -> raio + alvo -> ret.width / 2.0f) - fabs ( b -> centro.x - centroAlvox);
            float SobreposicaoY = ( b -> raio + alvo -> ret.height / 2.0f) - fabs ( b -> centro.y - centroAlvoy);
            
             if ( alvo -> hp <= 0){

                gw -> pontuacaoAtual += alvo-> pontuacaoObtida;
                alvo -> pontuacaoObtida = 0;
            }

             if ( SobreposicaoX < SobreposicaoY){

                if ( b-> centro.x < centroAlvox){

                    b -> centro.x = alvo -> ret.x - b->raio;

                }else{

                    b-> centro.x = alvo-> ret.x + alvo->ret.width + b->raio;

                }
                b-> velocidade.x *= -1;

            }else{

                if ( b -> centro.y < centroAlvoy){

                    b-> centro.y = alvo-> ret.y - b-> raio;

                }else{

                    b-> centro.y = alvo -> ret.y + alvo -> ret.height + b->raio;
                }
                b-> velocidade.y *= -1;
            }   
            

    }
  }
}

void resolverColisaoBolinhaJogador (Bola *b, Jogador *j){


   if ( CheckCollisionCircleRec ( b -> centro, b -> raio, j -> ret)){
        b-> centro.y = j -> ret.y - b -> raio; 
        b -> velocidade.y *= -1;    
    }



}
void ResetarBola_eJogo (Bola *b, EstadoJogo *estado, Jogador *j){

    if ( b -> centro.y + b -> raio >= GetScreenHeight()){

        b -> vidaAtual -= 1;
        b -> centro.x = GetScreenWidth()/2;
        b -> centro.y =  j-> ret.y - j-> ret.height;
        
        b -> velocidade.y = -200;
        b -> velocidade.x = GetRandomValue(-200, 200);

        j -> ret.x = GetScreenWidth()/2 - largura/2; 
        j -> ret.y = GetScreenHeight() - (3*altura);
                
        
    if ( b -> vidaAtual > 0){
     
        *estado = AGUARDANDO;
      
    }else{     
     
        *estado = GAMEOVER;
    }


 }
}

void desenharPontuacao (Alvo *a, int PontuacaoAtual, GameWorld *gw){

    int Fonte = 50;
    int Margem = 30;
    int Fim_eixoX = GetScreenWidth();

    const char *Score = TextFormat ("%d", gw-> pontuacaoAtual);
    int larguraScore = MeasureText (Score, Fonte);

    DrawText(Score, 
             Fim_eixoX - (Margem + larguraScore),
             20, 
             Fonte, 
             WHITE);


}

