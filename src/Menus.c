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
                retReiniciar.ret.x + (retReiniciar.ret.width - larguraReiniciar)/2,
                retReiniciar.ret.y + (retReiniciar.ret.height - Fonte)/2,
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

void DesenharVitoria(void){

    ClearBackground(GREEN);

    const char *jogar = "Reiniciar";
    const char *sair = "SAIR";
    const char *titulo = "VOCE VENCEU!";

    int Fonte = 50;

    int larguraJogar = MeasureText(jogar, Fonte);
    int larguraSair = MeasureText(sair, Fonte);
    int larguraTitulo = MeasureText(titulo, Fonte);

    RetBotoes retReiniciar = {

        .ret = {
            .x = (GetScreenWidth()/2.0f) - (LARGURARET/2.0f),
            .y = (GetScreenHeight()/2.0f),
            .width = LARGURARET,
            .height = ALTURARET,
        },

        .cor = WHITE,

    };

    int espacoEntreBotoes = 20;

    RetBotoes retSair = {

        .ret = {
            .x = retReiniciar.ret.x,
            .y = retReiniciar.ret.y + retReiniciar.ret.height + espacoEntreBotoes,
            .width = LARGURARET,
            .height = ALTURARET,
        },

        .cor = WHITE,

    };

    DrawRectangleRec(retReiniciar.ret, retReiniciar.cor);
    DrawRectangleRec(retSair.ret, retSair.cor);

    DrawText(jogar,
             retReiniciar.ret.x + (LARGURARET - larguraJogar)/2,
             retReiniciar.ret.y + (ALTURARET - Fonte)/2,
             Fonte,
             BLACK);

    DrawText(sair,
             retSair.ret.x + (LARGURARET - larguraSair)/2,
             retSair.ret.y + (ALTURARET - Fonte)/2,
             Fonte,
             BLACK);

    DrawText(titulo,
             GetScreenWidth()/2 - larguraTitulo/2,
             50,
             Fonte,
             BLACK);
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

    if ( gw -> estado == AGUARDANDO){
        
         int yIni = 150;
         int altura_Alvos = 20;
         int espaco = 5;
         
         int FonteContinua = 15;

         const char *continua = "PRESS SPACE TO CONTINUE";
         int larguraContinua = MeasureText (continua, Fonte);

         int yContinua = yIni + (gw -> lin * (altura_Alvos + espaco)) + 5;
         int xContinua = (GetScreenWidth()) - (larguraContinua/2) - 10;

        DrawText (  continua,
                    xContinua,
                    yContinua,
                    FonteContinua, 
                    BLACK);

    }
}


Color sortearCorPlanoFundo ( void ){

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

bool VerificarVitoria(GameWorld *gw){

    int quantidade = gw->lin * gw->col;

    for(int i = 0; i < quantidade; i++){

        if(gw->alvos[i].hp > 0){
            return false;
        }

    }

    return true;

}
