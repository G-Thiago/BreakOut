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
int velocidadeX_Padrao = 200;
int velocidadeY_Padrao = -200; 
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
        .velocidadeBase = 200.0f,
        .velocidadeAtual = 0.0f,
        .cor = WHITE,
    };

    gw -> bolinha = (Bola){

        .raio = 10.0f,
        .cor = WHITE,
        .centro = {
            GetScreenWidth()/2,
            gw -> jogador.ret.y - gw -> jogador.ret.height,
        },

        .velocidade = {
            velocidadeX_Padrao,
            velocidadeY_Padrao,
        },
        .vidaAtual = 3,
        .danoAtual = 1,
        .danoAdcionado = false,
        .velocidadeBase = 200.0f,
    };
    gw -> powerup = (PowerUp){

        .centro = {0},
        .raio = 8,
        .velocidadeY = 200,
        .cor = YELLOW,
        .ativo = false,


    };

    gw -> ambiente = sortearCorPlanoFundo();
    gw -> lin = 10;
    gw -> col = 6;

    gw -> alvos = (Alvo*) malloc ( sizeof( Alvo ) * gw -> lin * gw -> col);
    
    //Baseado na coluna e linha que estou, faremos os alvos serem criados

    resetAlvos(gw);

    
    gw -> estado = INICIO;
    gw -> pontuacaoAtual = 0;
    gw -> proximaAceleracao = 1000;

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
        duracaoPowerUp(&gw -> bolinha, &gw -> powerup, delta);
        aceleracao ( gw);

        if ( gw -> powerup.ativo == true){
            MoverPowerUp ( &gw -> powerup, &gw -> jogador, &gw -> bolinha, delta);
        }
    
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
    
        resetAlvos(gw);

        break;

    }   
}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
   
    if ( gw -> estado == GAMEOVER || gw -> estado == INICIO){
        
        DesenharMenusIni_GameOver( &gw -> estado);
        gw -> bolinha.timer = 0;

    }    
    
    
    if ( gw -> estado == AGUARDANDO || gw -> estado == JOGANDO){
        
        ClearBackground( gw -> ambiente);
        desenharPontuacao (gw -> alvos, gw-> pontuacaoAtual, gw);
        desenharJogador( &gw->jogador );
        desenharBola (&gw -> bolinha);
        desenharAlvos (gw -> alvos, (gw -> lin * gw -> col));
        DesenharVida (&gw -> bolinha);

        if ( gw -> powerup.ativo && gw -> estado == JOGANDO){
            
                desenharPowerUp (&gw -> powerup);

        }
    
    }   


        
        EndDrawing();
    

    
}

void resolverColisaoBolinhaAlvos (Bola *b, Alvo *alvos, GameWorld *gw, int quantidade){

    for ( int i = 0; i < quantidade; i++){

        Alvo *alvo = &alvos[i];
        
        if (CheckCollisionCircleRec ( b -> centro, b -> raio, alvo -> ret) && alvo -> hp > 0){
         
            alvo->hp -= b -> danoAtual;
            
            float centroAlvox = alvo -> ret.x + alvo -> ret.width / 2.0f;
            float centroAlvoy = alvo -> ret.y + alvo -> ret.height / 2.0f;

            float SobreposicaoX = ( b -> raio + alvo -> ret.width / 2.0f) - fabs ( b -> centro.x - centroAlvox);
            float SobreposicaoY = ( b -> raio + alvo -> ret.height / 2.0f) - fabs ( b -> centro.y - centroAlvoy);
            
             if ( alvo -> hp <= 0){

                gw -> pontuacaoAtual += alvo-> pontuacaoObtida;
                alvo -> pontuacaoObtida = 0;

                if ( alvo -> temPowerUp){

                   gw->powerup.centro.x = centroAlvox;
                   gw->powerup.centro.y = centroAlvoy;
    
                   gw->powerup.ativo = true;
                   alvo->temPowerUp = false;

                }
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

void resolverColisaoBolinhaJogador(Bola *b, Jogador *j) {
   
    if (CheckCollisionCircleRec(b->centro, b->raio, j->ret)) {
        
        
        float pontoDeImpacto = (b->centro.x - j->ret.x) / j->ret.width;
        float fatorAngulo = (pontoDeImpacto - 0.5f) * 2.0f;     

        
        float vel = b -> velocidadeBase;

        b->velocidade.x = fatorAngulo * vel;
        b->velocidade.y = -vel; 

        b->centro.y = j->ret.y - b->raio;
    }
}
void ResetarBola_eJogo (Bola *b, EstadoJogo *estado, Jogador *j){

    if ( b -> centro.y + b -> raio >= GetScreenHeight()){

        b -> vidaAtual -= 1;
        b -> centro.x = GetScreenWidth()/2;
        b -> centro.y =  j-> ret.y - j-> ret.height;
        
        b -> velocidade.y = -400;
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

void resetAlvos(GameWorld *gw) {

    Color cores[10] = {
        RED, BLUE, RED, BLUE, RED,
        BLUE, RED, BLUE, RED, BLUE
    };

    int larguraAlvo = 80;
    int alturaAlvo = 20;
    int espaco = 5;

    int larguraTotal = larguraAlvo * gw->col + espaco * (gw->col - 1);
    int xIni = GetScreenWidth()/2 - larguraTotal/2;
    int yIni = 150;

    for (int i = 0; i < gw->lin; i++) {
        for (int j = 0; j < gw->col; j++) {
            
            bool sorteioPowerup = (rand() % 100 <= 15);

            int p = i * gw->col + j;
            
            gw -> alvos[p] = (Alvo){
                        
            .ret.x = xIni + j * (larguraAlvo + espaco),
            .ret.y = yIni + i * (alturaAlvo + espaco),
            .ret.width = larguraAlvo,
            .ret.height = alturaAlvo,

            .cor = sorteioPowerup ? YELLOW : cores[i],

            .hp = (i <= 5) ? ((i * -1) + 6) : 1,

            .pontuacaoObtida =
                (i <= 5) ? ((i * -50) + 600) : 100,

            .pontuacaoAtual = 0,
            .temPowerUp = sorteioPowerup,

        };

    }
  }
}

Color sortearCorPlanoFundo (){

    int sorteamento = GetRandomValue (1, 3);
    Color ambiente;
    Color corRandomica;
        
        switch ( sorteamento ){
            
            case 1:

            corRandomica = (Color) {

                    0,
                    150,
                    0,
                    200,
            };

            ambiente = corRandomica;

            break;
        
            case 2:
        
             corRandomica = (Color) {

                    0,
                    100,
                    150,
                    200,
            };

            ambiente = corRandomica;

            break;

            case 3:

             corRandomica = (Color) {

                    128,
                    0,
                    240,
                    200,
            };

            ambiente = corRandomica;

            break;

            case 4:

            ambiente = BLACK;
        
            break;

        
    }

    return ambiente;


}

void aceleracao ( GameWorld *gw){

    if (gw->pontuacaoAtual >= gw->proximaAceleracao) {
    
    float incremento = 100.0f;
    
    if (gw->bolinha.velocidade.x > 0.0f) gw->bolinha.velocidade.x += incremento;
    else gw->bolinha.velocidade.x -= incremento;
    
    if (gw->bolinha.velocidade.y > 0.0f) gw->bolinha.velocidade.y += incremento;
    else gw->bolinha.velocidade.y -= incremento;
    
    gw -> proximaAceleracao += 1000.0f;
    gw -> bolinha.velocidadeBase += 100.0f;

  }


}

