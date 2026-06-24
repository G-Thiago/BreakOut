#include "GameWorld.h"

#include "raylib/raylib.h"
#include <stdio.h>

#define LARGURARET 250
#define ALTURARET 100

void DesenharMenuInicial(EstadoJogo *estado){
    
    ClearBackground(BLUE);

        


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

void DesenharGameOver (){

    ClearBackground(RED);


}


void InteragirMenInicial (EstadoJogo *estado){
    
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