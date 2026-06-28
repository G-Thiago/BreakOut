#include "GameWorld.h"

#include "raylib/raylib.h"
#include <stdio.h>

#define LARGURARET 250
#define ALTURARET 100

void DesenharMenusIni_GameOver (EstadoJogo *estado){

    if ( *estado == GAMEOVER){

    ClearBackground(RED);

        const char *reiniciar = "Reiniciar";
        const char *sair = "SAIR";
        const char *GameOver = "GAME OVER";

        int Fonte = 50;

        int larguraReiniciar = MeasureText(reiniciar, Fonte);
        int larguraSair = MeasureText(sair, Fonte);
        int larguraGameOver = MeasureText (GameOver, Fonte);

           RetBotoes  retReiniciar = {

        .ret = {
            .x = ( GetScreenWidth()/2.0f ) - ( LARGURARET / 2.0f),
            .y = (GetScreenHeight()/2.0f),
            .width = LARGURARET,
            .height = ALTURARET,
        },
        
        .cor = WHITE,

        


    };

    int espacoEntreSairEjogar = 20;

    RetBotoes retSair = {

        .ret = {
            .x = retReiniciar.ret.x,
            .y = retReiniciar.ret.y + retReiniciar.ret.height + espacoEntreSairEjogar,
            .width = LARGURARET,
            .height = ALTURARET,
    
        },
        .cor = WHITE,

    };

    DrawRectangleRec ( retReiniciar.ret, retReiniciar.cor);
    DrawRectangleRec ( retSair.ret, retSair.cor);

    DrawText ( reiniciar, 
               retReiniciar.ret.x/2 + (larguraReiniciar/2),
               retReiniciar.ret.y,
                Fonte,
                 BLACK );

    DrawText (sair,
              2*retSair.ret.x - larguraSair,
              retSair.ret.y,
              Fonte,
              BLACK);
    
    DrawText ( GameOver,
              GetScreenWidth()/2 - larguraGameOver/2,
              50,
              Fonte,
              BLACK);


    }if ( *estado == INICIO ){

    ClearBackground (BLUE);

        const char *jogar = "JOGAR";
        const char *sair = "SAIR";
        const char *titulo = "BREAK OUT";
        const char *autores = "THIAGO E FABIO";

        int Fonte = 50;

        int larguraJogar = MeasureText(sair, Fonte);
        int larguraSair = MeasureText(sair, Fonte);
        int larguraTitulo = MeasureText (titulo, Fonte);
        int larguraAutores = MeasureText (autores, Fonte);

         RetBotoes  retJogar = {

        .ret = {
            .x = ( GetScreenWidth()/2.0f ) - ( LARGURARET / 2.0f),
            .y = (GetScreenHeight()/2.0f),
            .width = LARGURARET,
            .height = ALTURARET,
        },
        
        .cor = WHITE,


    };

    int espacoEntreSairEjogar = 20;

    RetBotoes retSair = {

        .ret = {
            .x = retJogar.ret.x,
            .y = retJogar.ret.y + retJogar.ret.height + espacoEntreSairEjogar,
            .width = LARGURARET,
            .height = ALTURARET,
    
        },
        .cor = WHITE,

    };

    

    DrawRectangleRec ( retJogar.ret, retJogar.cor);
    DrawRectangleRec ( retSair.ret, retSair.cor);


    DrawText ( jogar, 
               2*retJogar.ret.x - (larguraJogar + 10),
               retJogar.ret.y,
                Fonte,
                 BLACK );

    DrawText (sair,
              2*retSair.ret.x - larguraSair,
              retSair.ret.y,
              Fonte,
              BLACK);
    
    DrawText (titulo,
              GetScreenWidth()/2 - larguraTitulo/2,
              50,
              Fonte,
              BLACK);

    DrawText (autores,
              GetScreenWidth() - larguraAutores/2,
              GetScreenHeight() - 20,
              20,
              BLACK);

    }

 
    
}


void InteragirMenu (EstadoJogo *estado){

 
    Vector2 posMouse = GetMousePosition();

    int xposJogarInicial = ( GetScreenWidth()/2.0f ) - ( LARGURARET / 2.0f);
    int yposJogarInicial = (GetScreenHeight()/2.0f);
    
    int xposSairInicial = xposJogarInicial;
    int yPosSairInicial = yposJogarInicial + ALTURARET + 20;

    Rectangle retJogar = {
        xposJogarInicial,
        yposJogarInicial,
        LARGURARET,
        ALTURARET,
    };

    Rectangle retSair = {
        
        .x = xposSairInicial,
        .y = yPosSairInicial,
        .width = LARGURARET,
        .height = ALTURARET,


    };
    

    if ( IsMouseButtonPressed (MOUSE_BUTTON_LEFT)){


        if ( CheckCollisionPointRec( posMouse, retJogar)){

            *estado = AGUARDANDO;

            
        }

    if (CheckCollisionPointRec(posMouse, retSair)){

        CloseWindow();

      
    }
 }

} 
