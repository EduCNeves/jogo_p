/*bibliotecas*/
#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

/*constantes*/
#define LINHAS 35 /*tamanho maximo do labirinto*/
#define COLUNAS 80 /*tamanho maximo do labirinto*/
#define PAREDE 'H' 
#define PASTILHAS '.'
#define PASTILHA_ESP 'o'
#define FUNDO ' '
#define PACMAN 'C'
#define BLINKY 'B'
#define PINKY 'P'
#define INKY 'I'
#define CLYDE 'Y'

#define COR_PAREDE 1 /*PAREDES*/
#define COR_PACMAN 2 /*PACMAN*/
#define COR_PASTILHAS_ESP 3 /*PASTILHAS ESPECIAL*/
#define COR_PASTILHAS 4 /*PASTILHAS*/
#define COR_FUNDO 5 /*FUNDO*/
#define COR_BLINKY 6 
#define COR_PINKY 7
#define COR_INKY 8
#define COR_CLYDE 9


/*como fosse uma matriz, mas so coma as coordenas supeior e inferior*/
typedef struct coordenadas{
   int ls, /*linha supeior*/
     li,    /*linha infeior*/
     cs,    /*coluna supeior*/
     ci;    /*coluna infeior*/
}COORDENADAS;

typedef struct fantasmas{
    int linha, 
     coluna;  
    
}FANTASMAS;

/*funções para começar o jogo e para imprimir o labirinto*/
/*imprindo o tabuleiro*/
void imprimir_tabuleiro(char **labirinto, COORDENADAS pacman, FANTASMAS blinky, FANTASMAS pinky, FANTASMAS inky, FANTASMAS clyde, int pontos, int vida_pacman){
   
    int i,j;

    /*colocando o pacman no labirinto*/
    for ( i = pacman.ls; i < pacman.li+1; i++){
        for (j = pacman.cs; j < pacman.ci+1; j++){
            labirinto[i][j] = PACMAN;
        }  
    }
    /*fantasmas*/
    for ( i = blinky.linha; i < blinky.linha+3; i++){
        for (j = blinky.coluna; j < blinky.coluna+3; j++){
            labirinto[i][j] = BLINKY;
        }  
    }
    for ( i = pinky.linha; i < pinky.linha+3; i++){
        for (j = pinky.coluna; j < pinky.coluna+3; j++){
            labirinto[i][j] = PINKY;
        }  
    }for ( i = inky.linha; i < inky.linha+3; i++){
        for (j = inky.coluna; j < inky.coluna+3; j++){
            labirinto[i][j] = INKY;
        }  
    }for ( i = clyde.linha; i < clyde.linha+3; i++){
        for (j = clyde.coluna; j < clyde.coluna+3; j++){
            labirinto[i][j] = CLYDE;
        }  
    }
    /*imprimindo o labirinto*/
    move(0,0);
    refresh();
    bkgd(COLOR_PAIR(COR_FUNDO));
    printw("     pontos: %d   vidas: %d \n", pontos, vida_pacman);
    printw("\n");
    for (i=0; i < LINHAS; i++){
            for(j=0; j < COLUNAS; j++){
                if (labirinto[i][j] == PAREDE){
                    attron(COLOR_PAIR(COR_PAREDE));
                    printw("%c", labirinto[i][j]);
                    attroff(COLOR_PAIR(COR_PAREDE));
                }
                else if (labirinto[i][j] == PASTILHA_ESP){
                    attron(COLOR_PAIR(COR_PASTILHAS_ESP));
                    printw("%c", labirinto[i][j]);
                    attroff(COLOR_PAIR(COR_PASTILHAS_ESP));
                }
                else if (labirinto[i][j] == PACMAN){
                    attron(COLOR_PAIR(COR_PACMAN));
                    printw("%c", labirinto[i][j]);
                    attroff(COLOR_PAIR(COR_PACMAN));
                }
                else if (labirinto[i][j] == PASTILHAS){
                    attron(COLOR_PAIR(COR_PASTILHAS));
                    printw("%c", labirinto[i][j]);
                    attroff(COLOR_PAIR(COR_PASTILHAS));
                }
                else if (labirinto[i][j] == BLINKY){
                    attron(COLOR_PAIR(COR_BLINKY));
                    printw("%c", labirinto[i][j]);
                    attroff(COLOR_PAIR(COR_BLINKY));
                }
                else if (labirinto[i][j] == PINKY){
                    attron(COLOR_PAIR(COR_PINKY));
                    printw("%c", labirinto[i][j]);
                    attroff(COLOR_PAIR(COR_PINKY));
                }
                else if (labirinto[i][j] == INKY){
                    attron(COLOR_PAIR(COR_INKY));
                    printw("%c", labirinto[i][j]);
                    attroff(COLOR_PAIR(COR_INKY));
                }
                else if (labirinto[i][j] == CLYDE){
                    attron(COLOR_PAIR(COR_CLYDE));
                    printw("%c", labirinto[i][j]);
                    attroff(COLOR_PAIR(COR_CLYDE));
                }
                else {
                    printw("%c", labirinto[i][j]);
                }
            }
        printw("\n");
    }
}

/*criando o labirinto*/
char** comecando_labirinto(){
    int i, j;
    char **labirinto;
    labirinto = (char**) malloc(LINHAS *sizeof(char*));       
    for(i = 0; i < LINHAS; i++){
        labirinto[i] = (char*) malloc(COLUNAS *sizeof(char));  
        for(j = 0; j < COLUNAS; j++){
            /*montando o labirinto*/
            if(i == 0 || i == (LINHAS-1) || j == 0 || j == (COLUNAS-1) )
               labirinto[i][j] = PAREDE;
            else{
               labirinto[i][j] = PASTILHAS;
            }
        }
    }
       return labirinto;
}

/*contruindo as pasredes do labirinto*/
void paredes_labirinto(char **labirinto){

    int i,j;
    /*criando o lugar aonde os fantamas ficaram*/
    for (i=35; i < 44; i++){
        labirinto[16][i] = PAREDE;
        labirinto[23][i] = PAREDE;
    }
    for (j=16; j < 24; j++){
        labirinto[j][34] = PAREDE;
        labirinto[j][44] = PAREDE;
    }
    for (i=17;i < 24; i++){
        for(j=35; j < 44; j++){
            labirinto[i][j] = FUNDO;
        }
    }

    /*colocando as pastilhas especiais*/
    for (i=1;i < 3; i++){
        for (j=2; j< 4; j++){
            labirinto[i][j] = PASTILHA_ESP;
        }
    }

    for (i=33;i < 35; i++){
        for (j=1; j< 4; j++){
            labirinto[i][j] = PASTILHA_ESP;
        }
    }

    for (i=1;i < 3; i++){
        for (j=76; j< 78; j++){
            labirinto[i][j] = PASTILHA_ESP;
        }
    }

    for (i=33;i < 35; i++){
        for (j=76; j< 78; j++){
            labirinto[i][j] = PASTILHA_ESP;
        }
    }

    /*colocando as paredes*/
    for (i=4;i < 9; i++){
        for (j=4; j< 9; j++){
            labirinto[i][j] = PAREDE;
        }
    }
    /**/
    for(i=15; i < 21; i++){
        labirinto[4][i] = PAREDE;
        labirinto[8][i] = PAREDE;
    }
    /**/
    for(j=24; j < 30; j++){
        labirinto[4][j] = PAREDE;
        labirinto[8][j] = PAREDE;
    }
    /**/
    for (i=1;i < 6; i++){
        for (j=36; j< 44; j++){
            labirinto[i][j] = PAREDE;
        }
    }
    /**/
    for(i=36; i < 44; i++){
        labirinto[9][i] = PAREDE;
    }
    /**/
    for ( i=15; i < 18; i++){
        for ( j=1; j < 8; j++){
            labirinto[i][j] = PAREDE;
        }    
    }
    /**/
    for ( i=25; i < 28; i++){
        for ( j=1; j < 8; j++){
            labirinto[i][j] = PAREDE;
        }    
    }
    /**/
    for ( j=7; j < 13; j++){
        labirinto[34][j] = PAREDE;
    } 

    /**/
    for ( i=18; i < 24; i++){
        for ( j=14; j < 17; j++){
            labirinto[i][j] = PAREDE;
        }  
    }
    /**/
    for ( i=15; i < 27; i++){
        for ( j=17; j < 20; j++){
            labirinto[i][j] = PAREDE;
        }  
    }
    
    /**/
    for ( i=12; i < 15; i++){
        for ( j=26; j < 29; j++){
            labirinto[i][j] = PAREDE;
        }  
    }
    /**/
    for ( i=18; i < 21 ; i++){
        for ( j=26; j < 28; j++){
            labirinto[i][j] = PAREDE;
        }  
    }

    /**/
    for ( i=27; i < 30; i++){
        for ( j=26; j < 29; j++){
            labirinto[i][j] = PAREDE;
        }  
    }
    /**/
    for ( i=27; i < 30; i++){
        for ( j=37; j < 43; j++){
            labirinto[i][j] = PAREDE;
        }  
    }
    /**/
    for ( j=34; j < 46; j++){
        labirinto[34][j] = PAREDE;
    }

    /*outra metade do labirinto */
    for (i=4;i < 9; i++){
        for (j=71; j < 76; j++){
            labirinto[i][j] = PAREDE;
        }
    }

    for(i=59; i < 65; i++){
        labirinto[4][i] = PAREDE;
        labirinto[8][i] = PAREDE;
    }

    for(j=50; j < 56; j++){
        labirinto[4][j] = PAREDE;
        labirinto[8][j] = PAREDE;
    }

    for ( i=15; i < 18; i++){
        for ( j=72; j < 79; j++){
            labirinto[i][j] = PAREDE;
        }    
    }

    for ( i=24; i < 27; i++){
        for ( j=72; j < 79; j++){
            labirinto[i][j] = PAREDE;
        }    
    }

    for ( j=67; j < 73; j++){
        labirinto[34][j] = PAREDE;
    }  

    for ( i=18; i < 24; i++){
        for ( j=63; j < 66; j++){
            labirinto[i][j] = PAREDE;
        }  
    }

    for ( i=15; i < 27; i++){
        for ( j=60; j < 63; j++){
            labirinto[i][j] = PAREDE;
        }  
    }

    for ( i=12; i < 15; i++){
        for ( j=51; j < 54; j++){
            labirinto[i][j] = PAREDE;
        }  
    }

    for ( i=18; i < 21 ; i++){
        for ( j=52; j < 54; j++){
            labirinto[i][j] = PAREDE;
        }  
    }
    
    for ( i=27; i < 30; i++){
        for ( j=51; j < 54; j++){
            labirinto[i][j] = PAREDE;
        }  
    }
    
    for ( j=67; j < 73; j++){
        labirinto[34][j] = PAREDE;
    }  

}

/*colocando as coordenadas do pacman  no labirinto*/
void colocar_pacman(COORDENADAS *pacman){
    
    (*pacman).ls = 30;
    (*pacman).cs = 38;
    (*pacman).li = 33;
    (*pacman).ci = 40;
}

/*colocando os fantasmas*/
void colocar_fantasmas( FANTASMAS *blinky, FANTASMAS *pinky, FANTASMAS *inky, FANTASMAS *clyde){

    /*o blinky começa fora da precisao dos fantasmas*/
    (*blinky).linha = 12;
    (*blinky).coluna = 38;
    /*colocando as coordenadas pinky*/
    (*pinky).linha = 17;
    (*pinky).coluna = 38;
    /*colocando as coordenadas inky*/
    (*inky).linha = 20;
    (*inky).coluna = 36;
    /*colocando as coordenadas clyde*/
    (*clyde).linha = 20;
    (*clyde).coluna = 40;

}

/*crindo os ant_fantasmas que vai guardas o tem no labinto aonde o fantasma esta*/
char** crinado_ant_ghost(){
    int i, j;
    int tam = 3;
    char **ant_ghost;
    ant_ghost = (char**) malloc(tam *sizeof(char*));        /*Alocação de uma dimensão do ant_ghost*/
    for(i = 0; i < tam; i++){
        ant_ghost[i] = (char*) malloc(tam *sizeof(char));  /*Alocação da segunda dimensão do ant_ghost*/
        for(j = 0; j < tam; j++){
            ant_ghost[i][j] = FUNDO;
        }
    }
    return ant_ghost;
}

void crinado_ant_blinky( char **labirinto, FANTASMAS *blinky, char **ant_ghost ){

    int i,j,aux_l,aux_c;
    /*colocando oq estava no mapa aonde o fantamas andou*/
    aux_l = 0;
    for(i = (*blinky).linha ; i < (*blinky).linha +3; i++){
        aux_c = 0;
        for(j = (*blinky).coluna; j < (*blinky).coluna +3; j++){
            if ((ant_ghost[aux_l][aux_c] == PASTILHAS) || (ant_ghost[aux_l][aux_c] == FUNDO) || (ant_ghost[aux_l][aux_c] == PASTILHA_ESP)){
                labirinto[i][j] = ant_ghost[aux_l][aux_c];
            }
            else {
                labirinto[i][j] = FUNDO;
            }
            aux_c++;
        }
        aux_l++;
    }

}

/*parte de movimentação do pacman e dos fantasmas*/
/*pacman*/
/*testando o movimento para esquerda*/
int testar_movimento_esquerdo(char **labirinto, COORDENADAS pacman){

    int i = 0;
    int tem_parede = 0;
    /*testando movimento esquerda*/
    while( i < 3 || tem_parede != 1 ){
        if (labirinto[pacman.ls+i][pacman.cs-1] == PAREDE) {
            tem_parede = 1;
        }
        i++;
    }
    return tem_parede;
}

/*movimentando o pacman para a esquerda*/
void movimento_pacman_esquerdo(char **labirinto, COORDENADAS *p, int *pontos){

    /*variaveis aux*/
    int i,l,c;
    /*passando as coordenações do pacman para variaveis aux*/
    l=(*p).ls;
    c=(*p).cs;

    /*contandos os pontos */
    for (i=0; i < 3; i++){
        if (labirinto[l+i][c-1] == PASTILHAS) {
            *pontos=*pontos+10;
        }
    }

    /*tirando as pastilhas do mapa*/
    l=(*p).li;/*passando o valor para uma variavel auxiliar para poder modificar*/
    for (i=0; i < 3; i++){
        labirinto[l-i][(*p).ci] = FUNDO;
    }
    /*movimentando os pacman*/
    --(*p).cs;
    --(*p).ci;

}

int comeu_pastilha_esp_esquerdo(char **labirinto, COORDENADAS pacman, int *pontos){
    
    int i = 0;
    int comeu_esp = 0; 
    while (( i < 3) && (comeu_esp != 1)){
        if (labirinto[(pacman).ls+i][(pacman).cs-1] == PASTILHA_ESP){
                *pontos=*pontos+100;
                comeu_esp = 1;
            }
        i++;
    }

    return comeu_esp;

}

/*testando o movimento para a direita*/
int testar_movimento_direita(char **labirinto, COORDENADAS pacman){
    
    int i = 0;
    int tem_parede = 0;
    /*testando movimento direita*/
    while( i < 3 || tem_parede != 1 ){
        if (labirinto[pacman.li-i][pacman.ci+1] == PAREDE) {
            tem_parede = 1;
        }
        i++;
    }
    return tem_parede;
}

/*movimentando o pacman para a direita*/
void movimento_pacman_direita(char **labirinto, COORDENADAS *p, int *pontos){
    
    int i,l,c;

    /*pontuação do jogo*/
    l=(*p).li;
    c=(*p).ci;
    for  (i = 0; i < 3; i++){
         if (labirinto[l-i][c+1] == PAREDE) {
            *pontos=*pontos+10;
        }
    }

    /*tirando as pastilhas do mapa*/
     l=(*p).ls;
    for (i=0; i < 3; i++){
        labirinto[l+i][(*p).cs] = FUNDO;
    }
    /*movimentando para a direita*/
    ++(*p).cs;
    ++(*p).ci;

}

int comeu_pastilha_esp_direita(char **labirinto, COORDENADAS pacman, int *pontos){

    int i = 0;
    int comeu_esp = 0;
    while ((i < 3) && (comeu_esp != 1)){
        if (labirinto[(pacman).li-i][(pacman).ci+1] == PASTILHA_ESP){
            *pontos=*pontos+100;
            comeu_esp = 1;
        }
        i++;
    }

    return comeu_esp;

}

/*testando o movimento para cima*/
int testar_movimento_cima(char **labirinto, COORDENADAS pacman){

    int i = 0;
    int tem_parede = 0;
    /*testando movimento direita*/
    while( i < 3 || tem_parede != 1 ){
        if (labirinto[pacman.ls-1][pacman.cs+i] == PAREDE ) {
            tem_parede = 1;
        }
        i++;
    }
    return tem_parede;
}

/*movimentando o pacman para cima*/
void movimento_pacman_cima(char **labirinto, COORDENADAS *p, int *pontos){
    
    int i,c,l;
    /*contando os pontos*/
    l=(*p).ls;
    c=(*p).cs;
    for ( i = 0; i < 3; i++){
        if (labirinto[l-1][c+i] == PASTILHAS) {
            *pontos=*pontos+10;
        }
    }
    
    /*tirando as pastilhas do mapa*/
    c=(*p).ci;
    for (i=0; i < 3; i++){
        labirinto[(*p).li][c-i] = FUNDO;
    }
    /*movimentando para a direita*/
    --(*p).ls;
    --(*p).li;


}

int comeu_pastilha_esp_cima(char **labirinto, COORDENADAS pacman, int *pontos){

    int i = 0;
    int comeu_esp = 0;
    while ((i < 3) && (comeu_esp != 1)){
        if (labirinto[(pacman).ls-1][(pacman).cs+i] == PASTILHA_ESP){
            *pontos=*pontos+100;
            comeu_esp = 1;
        }
        i++;
    }

    return comeu_esp;

}

/*testando o movimento para baixo*/
int testar_movimento_baixo(char **labirinto, COORDENADAS pacman){

    int i = 0;
    int tem_parede = 0;
    /*testando movimento para baixo*/
    while( i < 3 || tem_parede != 1 ){
        if (labirinto[pacman.li+1][pacman.ci-i] == PAREDE) {
            tem_parede = 1;
        }
        i++;
    }
    return tem_parede;
}

/*movimentando o pacman para a baixo*/
void movimento_pacman_baixo(char **labirinto, COORDENADAS *p, int *pontos){
    
    int i,c,l;

    /*pontos*/
    l=(*p).li;
    c=(*p).ci;
    for ( i = 0; i < 3; i++){
        if (labirinto[l+1][c-i] == PASTILHAS) {
            *pontos=*pontos+10;
        }
    }

    /*tirando as pastilhas do mapa*/
    c=(*p).cs;
    for (i=0; i < 3; i++){
        labirinto[(*p).ls][c+i] = FUNDO;
    }
    /*movimentando para a baixo*/
    ++(*p).ls;
    ++(*p).li;

}

int comeu_pastilha_esp_baixo(char **labirinto, COORDENADAS pacman, int *pontos){
    
    int i = 0;
    int comeu_esp = 0;
    while ((i < 3) && (comeu_esp != 1)){
        if (labirinto[(pacman).li+1][(pacman).ci-i] == PASTILHA_ESP){
            *pontos=*pontos+100;
            comeu_esp = 1;
        }
        i++;
    }

    return comeu_esp;

}

/*fantasmas*/

int calcula_dist(int X, int Y, int x, int y){
  return sqrt(pow(X-x,2) + pow(Y-y,2));
}

void controle_blink(char **labirinto, COORDENADAS *pacman, FANTASMAS *blinky, char **ant_ghost, int *vida_pacman){

    int dist_menor  = calcula_dist((*blinky).coluna,(*blinky).linha,(*pacman).cs,(*pacman).ls);
    int ghost_c = (*blinky).coluna;
    int ghost_l = (*blinky).linha;
    int achou_pacman = 1; 
    
    /*ESQUERDA*/
    if ( (labirinto[(*blinky).linha ][(*blinky).coluna - 1] == FUNDO) && (labirinto[(*blinky).linha - 1][(*blinky).coluna - 1] == FUNDO) && (labirinto[(*blinky).linha - 2][(*blinky).coluna - 1] == FUNDO) ){
        if (calcula_dist( ( (*blinky).coluna-1),(*blinky).linha,(*pacman).cs,(*pacman).ls) < dist_menor)
            {
                ghost_c = ((*blinky).coluna-1) ;
                ghost_l = (*blinky).linha;
                achou_pacman = 0;
            }
    }

    /*DIREITA*/
    if ((labirinto[(*blinky).linha ][(*blinky).coluna +3 ] == FUNDO) && (labirinto[(*blinky).linha - 1][(*blinky).coluna + 3] == FUNDO) && (labirinto[(*blinky).linha - 2][(*blinky).coluna + 3] == FUNDO)){
        if (calcula_dist(((*blinky).coluna+1),(*blinky).linha,(*pacman).cs,(*pacman).ls) < dist_menor)
        {
            ghost_c = ((*blinky).coluna+ 3) ;
            ghost_l = (*blinky).linha;
            achou_pacman = 0;
        }
    }

    /*CIMA*/
    if ((labirinto[(*blinky).linha -1][(*blinky).coluna ] == FUNDO) && (labirinto[(*blinky).linha -1 ][(*blinky).coluna + 1] == FUNDO) && (labirinto[(*blinky).linha - 1][(*blinky).coluna + 2] == FUNDO)){
        if (calcula_dist((*blinky).coluna,((*blinky).linha-1),(*pacman).cs,(*pacman).ls) < dist_menor)
        {
            ghost_c = (*blinky).coluna;
            ghost_l = ((*blinky).linha- 1);
            achou_pacman = 0;
        }
    }

    /*BAIXO*/
    if ((labirinto[(*blinky).linha +3][(*blinky).coluna ] == FUNDO) && (labirinto[(*blinky).linha + 1][(*blinky).coluna + 3] == FUNDO) && (labirinto[(*blinky).linha +3][(*blinky).coluna + 2] == FUNDO)){
        if (calcula_dist((*blinky).coluna,((*blinky).linha+1),(*pacman).cs,(*pacman).ls) < dist_menor)
        {
            ghost_c = (*blinky).coluna;
            ghost_l = ((*blinky).linha+ 3);
            achou_pacman = 0;
        }
    }

        /*se o blinky não andar ele vai andar aleatoriamente*/
        int x;
        while (achou_pacman != 0){
            x = rand() % 4;
            if ((labirinto[(*blinky).linha -1][(*blinky).coluna ] == FUNDO) && (labirinto[(*blinky).linha -1 ][(*blinky).coluna + 1] == FUNDO) && (labirinto[(*blinky).linha - 1][(*blinky).coluna + 2] == FUNDO) && (x == 0)){/*cima*/
                ghost_c = (*blinky).coluna;
                ghost_l = ((*blinky).linha- 1);
                achou_pacman = 0;
            }
            if ((labirinto[(*blinky).linha +3][(*blinky).coluna ] == FUNDO) && (labirinto[(*blinky).linha + 3][(*blinky).coluna + 1] == FUNDO) && (labirinto[(*blinky).linha +3][(*blinky).coluna + 2] == FUNDO) && (x == 1)){/*baixo*/
                ghost_c = (*blinky).coluna;
                ghost_l = ((*blinky).linha+ 3);
                achou_pacman = 0;
            }
            if ((labirinto[(*blinky).linha ][(*blinky).coluna +3 ] == FUNDO) && (labirinto[(*blinky).linha - 1][(*blinky).coluna + 3] == FUNDO) && (labirinto[(*blinky).linha - 2][(*blinky).coluna + 3] == FUNDO) && (x == 2)){/*direita*/
                ghost_c = ((*blinky).coluna+ 3) ;
                ghost_l = (*blinky).linha;
                achou_pacman = 0;
            }
            if ((labirinto[(*blinky).linha ][(*blinky).coluna - 1] == FUNDO) && (labirinto[(*blinky).linha - 1][(*blinky).coluna - 1] == FUNDO) && (labirinto[(*blinky).linha - 2][(*blinky).coluna - 1] == FUNDO) && (x == 3)){/*esquerda*/
                ghost_c = ((*blinky).coluna-1) ;
                ghost_l = (*blinky).linha;
                achou_pacman = 0;
            }
        }

    /*APOS ENCONTRAR MELHOR POSIÇÃO PARA IR ATRAS DE PAC MAN*/
    int i,j,aux_l,aux_c;
    /*colocando oq estava no mapa aonde o fantamas andou*/
    aux_l = 0;
    for(i = (*blinky).linha ; i < (*blinky).linha +3; i++){
        aux_c = 0;
        for(j = (*blinky).coluna; j < (*blinky).coluna +3; j++){
            if ((ant_ghost[aux_l][aux_c] == PASTILHAS) || (ant_ghost[aux_l][aux_c] == FUNDO) || (ant_ghost[aux_l][aux_c] == PASTILHA_ESP)){
                labirinto[i][j] = ant_ghost[aux_l][aux_c];
            }
            else {
                labirinto[i][j] = FUNDO;
            }
            aux_c++;
        }
        aux_l++;
    } 

    (*blinky).coluna= ghost_c;
    (*blinky).linha= ghost_l;

    /*colocando o que esta no labirinto no no ant_ghost para guardar*/
    aux_l = 0;
    for(i = (*blinky).linha ; i < (*blinky).linha +3; i++){
        aux_c = 0 ;
        for(j = (*blinky).coluna; j < (*blinky).coluna +3; j++){
            ant_ghost[aux_l][aux_c] = labirinto[i][j];
            aux_c++;
        }
        aux_l++;
    }


    /*vendo em todos os lados se o fantama matou o pacman*/
    if (((*blinky).linha == (*pacman).ls && (*blinky).coluna == (*pacman).cs) && ((*blinky).linha +1 == (*pacman).ls+1 && (*blinky).coluna == (*pacman).cs) && ((*blinky).linha +2 == (*pacman).ls+2 && (*blinky).coluna == (*pacman).cs))
        --(*vida_pacman);
    else if (((*blinky).linha == (*pacman).ls && (*blinky).coluna == (*pacman).cs) && ((*blinky).linha == (*pacman).ls && (*blinky).coluna+1 == (*pacman).cs+1) && ((*blinky).linha == (*pacman).ls && (*blinky).coluna+2 == (*pacman).cs+2))
        --(*vida_pacman);
    else if (((*blinky).linha == (*pacman).li-2 && (*blinky).coluna == (*pacman).ci) && ((*blinky).linha +1 == (*pacman).li-1 && (*blinky).coluna == (*pacman).ci) && ((*blinky).linha +2 == (*pacman).li && (*blinky).coluna == (*pacman).ci))
        --(*vida_pacman);
    else if (((*blinky).linha == (*pacman).li && (*blinky).coluna == (*pacman).ci-2) && ((*blinky).linha == (*pacman).li && (*blinky).coluna+1 == (*pacman).ci-2) && ((*blinky).linha == (*pacman).li && (*blinky).coluna+2 == (*pacman).ci))
        --(*vida_pacman);
    
} 

void controle_clyde(char **labirinto, COORDENADAS *pacman, FANTASMAS *clyde, char **ant_ghost, int *vida_pacman){
    
    int achou_pacman = 1;
    int ghost_c = (*clyde).coluna;
    int ghost_l = (*clyde).linha;
    int dist_menor = calcula_dist(ghost_c,ghost_l,(*pacman).cs, (*pacman).ls);

    if (dist_menor < 15){
        /*CIMA*/
        if ((labirinto[(*clyde).linha-1][(*clyde).coluna] != PAREDE) && (labirinto[(*clyde).linha-1][(*clyde).coluna+1] != PAREDE) && (labirinto[(*clyde).linha-1][(*clyde).coluna+2] != PAREDE) ){
            if  (calcula_dist((*clyde).coluna,(*clyde).linha-1, (*pacman).cs, (*pacman).ls) < dist_menor)  {/*cima*/
                ghost_l = (*clyde).linha-1;
                ghost_c = (*clyde).coluna;
                achou_pacman = 0;
            }
        }
        /*BAIXO*/
        if ((labirinto[(*clyde).linha+3][(*clyde).coluna] != PAREDE) && (labirinto[(*clyde).linha+3][(*clyde).coluna-1] != PAREDE) && (labirinto[(*clyde).linha+3][(*clyde).coluna+2] != PAREDE) ){
            if (calcula_dist((*clyde).coluna,(*clyde).linha+3, (*pacman).cs, (*pacman).ls) < dist_menor) {/*baixo*/
                    ghost_l = (*clyde).linha+3;
                    ghost_c = (*clyde).coluna;
                    achou_pacman = 0;
                }
        }
        /*DIREITA*/
        if ((labirinto[(*clyde).linha][(*clyde).coluna+3] != PAREDE) && (labirinto[(*clyde).linha-1][(*clyde).coluna+3] != PAREDE) && (labirinto[(*clyde).linha-1][(*clyde).coluna+3] != PAREDE) ){
            if (calcula_dist((*clyde).coluna+3,(*clyde).linha, (*pacman).cs, (*pacman).ls) < dist_menor) {/*direita*/
                        ghost_l = (*clyde).linha;
                        ghost_c = (*clyde).coluna+3;
                        achou_pacman = 0;
            }
        }
            /*ESQUERDA*/
            if ((labirinto[(*clyde).linha][(*clyde).coluna-1] != PAREDE) && (labirinto[(*clyde).linha+1][(*clyde).coluna-1] != PAREDE) && (labirinto[(*clyde).linha+2][(*clyde).coluna-1] != PAREDE) ){
                if  (calcula_dist((*clyde).coluna-1,(*clyde).linha, (*pacman).cs, (*pacman).ls) < dist_menor) {/*esquerda*/
                            ghost_l = (*clyde).linha;
                            ghost_c = (*clyde).coluna-1;
                            achou_pacman = 0;
                }
            }
    }

    /*se não estiver num raio de 5 posições vai andar aleatoriamente*/
    int x;
    while (achou_pacman != 0){
        x = rand() %4;
        /*CIMA*/
        if (x == 0){
            if ((labirinto[(*clyde).linha-1][(*clyde).coluna] != PAREDE) && (labirinto[(*clyde).linha-1][(*clyde).coluna+1] != PAREDE) && (labirinto[(*clyde).linha-1][(*clyde).coluna+2] != PAREDE) ) {
                ghost_l = (*clyde).linha-1;
                ghost_c = (*clyde).coluna;
                achou_pacman = 0;
            }
        }
        /*baixo*/
        else if (x == 1){
                if ((labirinto[(*clyde).linha+3][(*clyde).coluna] != PAREDE) && (labirinto[(*clyde).linha+3][(*clyde).coluna-1] != PAREDE) && (labirinto[(*clyde).linha+3][(*clyde).coluna+2] != PAREDE) ){
                    ghost_l = (*clyde).linha+1;
                    ghost_c = (*clyde).coluna;
                    achou_pacman = 0;
                }
        }
        /*direita*/
        else if  (x == 2){
            if ((labirinto[(*clyde).linha][(*clyde).coluna+3] != PAREDE) && (labirinto[(*clyde).linha-1][(*clyde).coluna+3] != PAREDE) && (labirinto[(*clyde).linha-1][(*clyde).coluna+3] != PAREDE) ){
                ghost_l = (*clyde).linha;
                ghost_c = (*clyde).coluna+1;
                achou_pacman = 0;
            }
        }
        /*esquerda*/
        if  (x == 3){
            if ((labirinto[(*clyde).linha][(*clyde).coluna-1] != PAREDE) && (labirinto[(*clyde).linha+1][(*clyde).coluna-1] != PAREDE) && (labirinto[(*clyde).linha+2][(*clyde).coluna-1] != PAREDE) ){
                ghost_l = (*clyde).linha;
                ghost_c = (*clyde).coluna+1;
                achou_pacman = 0;
            }
        }
    }


    int i,j,aux_l,aux_c;
    aux_l = 0;
    for(i = (*clyde).linha ; i < (*clyde).linha +3; i++){
        aux_c = 0;
        for(j = (*clyde).coluna; j < (*clyde).coluna +3; j++){
            if ((ant_ghost[aux_l][aux_c] == PASTILHAS) || (ant_ghost[aux_l][aux_c] == FUNDO) || (ant_ghost[aux_l][aux_c] == PASTILHA_ESP)){
                labirinto[i][j] = ant_ghost[aux_l][aux_c];
            }
            else {
                labirinto[i][j] = FUNDO;
            }
            aux_c++;
        }
        aux_l++;
    } 

    (*clyde).coluna= ghost_c;
    (*clyde).linha= ghost_l;

    aux_l = 0;
    for(i = (*clyde).linha ; i < (*clyde).linha +3; i++){
        aux_c = 0 ;
        for(j = (*clyde).coluna; j < (*clyde).coluna +3; j++){
            ant_ghost[aux_l][aux_c] = labirinto[i][j];
            aux_c++;
        }
        aux_l++;
    }


    /*vendo em todos os lados se o fantama matou o pacman*/
    if (((*clyde).linha == (*pacman).ls && (*clyde).coluna == (*pacman).cs) && ((*clyde).linha +1 == (*pacman).ls+1 && (*clyde).coluna == (*pacman).cs) && ((*clyde).linha +2 == (*pacman).ls+2 && (*clyde).coluna == (*pacman).cs))
        --(*vida_pacman);
    else if (((*clyde).linha == (*pacman).ls && (*clyde).coluna == (*pacman).cs) && ((*clyde).linha == (*pacman).ls && (*clyde).coluna+1 == (*pacman).cs+1) && ((*clyde).linha == (*pacman).ls && (*clyde).coluna+2 == (*pacman).cs+2))
        --(*vida_pacman);
    else if (((*clyde).linha == (*pacman).li-2 && (*clyde).coluna == (*pacman).ci) && ((*clyde).linha +1 == (*pacman).li-1 && (*clyde).coluna == (*pacman).ci) && ((*clyde).linha +2 == (*pacman).li && (*clyde).coluna == (*pacman).ci))
        --(*vida_pacman);
    else if (((*clyde).linha == (*pacman).li && (*clyde).coluna == (*pacman).ci-2) && ((*clyde).linha == (*pacman).li && (*clyde).coluna+1 == (*pacman).ci-2) && ((*clyde).linha == (*pacman).li && (*clyde).coluna+2 == (*pacman).ci))
        --(*vida_pacman);


}

void controle_pinky(char **labirinto, COORDENADAS *pacman, FANTASMAS *pinky, char **ant_ghost, int *vida_pacman, char movimento){

    int dist_menor;
    int ghost_c;
    int ghost_l;
    int pacman_c, pacman_l;
    int achou_pacman = 1;

    if (movimento == 'w'){
        dist_menor = calcula_dist((*pinky).coluna,(*pinky).linha,(*pacman).ci,(*pacman).li-5);
        pacman_c= (*pacman).ci;
        pacman_l= (*pacman).li-5;
    }
    if (movimento == 's'){
        dist_menor = calcula_dist((*pinky).coluna,(*pinky).linha,(*pacman).ci,(*pacman).li+5);
        pacman_c= (*pacman).ci;
        pacman_l= (*pacman).li+5;
    }
    if (movimento == 'd'){
        dist_menor = calcula_dist((*pinky).coluna,(*pinky).linha,(*pacman).ci+5,(*pacman).li);
        pacman_c= (*pacman).ci+5;
        pacman_l= (*pacman).li;
    }
    if (movimento == 'a'){
        dist_menor = calcula_dist((*pinky).coluna,(*pinky).linha,(*pacman).ci-5,(*pacman).li);
        pacman_c= (*pacman).ci-5;
        pacman_l= (*pacman).li;
    }

    ghost_c = (*pinky).coluna ;
    ghost_l = (*pinky).linha;

    /*esquerda*/
    if ((labirinto[(*pinky).linha][(*pinky).coluna-1] != PAREDE) && (labirinto[(*pinky).linha+1][(*pinky).coluna-1] != PAREDE) && (labirinto[(*pinky).linha+2][(*pinky).coluna-1] != PAREDE)) {
        if (calcula_dist(((*pinky).coluna-1),(*pinky).linha,pacman_c,pacman_l < dist_menor)){
            ghost_c = ((*pinky).coluna - 1) ;
            ghost_l = (*pinky).linha;
            achou_pacman = 0;
        }
    }
    /*direita*/
    if ((labirinto[(*pinky).linha][(*pinky).coluna+3] != PAREDE) && (labirinto[(*pinky).linha-1][(*pinky).coluna+3] != PAREDE) && (labirinto[(*pinky).linha-1][(*pinky).coluna+3] != PAREDE) ) {
        if  (calcula_dist( ( (*pinky).coluna+3),(*pinky).linha,pacman_c,pacman_l < dist_menor)){
            ghost_c = ((*pinky).coluna + 3);
            ghost_l = (*pinky).linha;
            achou_pacman = 0;
        }
    }
    /*cima*/
    if ((labirinto[(*pinky).linha-1][(*pinky).coluna] != PAREDE) && (labirinto[(*pinky).linha-1][(*pinky).coluna+1] != PAREDE) && (labirinto[(*pinky).linha-1][(*pinky).coluna+2] != PAREDE) ) {
        if (calcula_dist((*pinky).coluna,((*pinky).linha-1),pacman_c,pacman_l ) < dist_menor){
            ghost_c = (*pinky).coluna;   
            ghost_l = ((*pinky).linha - 1);
            achou_pacman = 0;
        }
    }
    /*baixo*/
    if ((labirinto[(*pinky).linha+3][(*pinky).coluna] != PAREDE) && (labirinto[(*pinky).linha+3][(*pinky).coluna-1] != PAREDE) && (labirinto[(*pinky).linha+3][(*pinky).coluna+2] != PAREDE) ) {
        if (calcula_dist((*pinky).coluna,((*pinky).linha+3),pacman_c,pacman_l < dist_menor)){
            ghost_c = (*pinky).coluna;
            ghost_l = ((*pinky).linha + 3);
            achou_pacman = 0;
        }
    }


    /*se o fantasmas não andar ele vai andar aleatoriamente*/
    int x;
    while (achou_pacman != 0){
        x = rand() %4;
        /*CIMA*/
        if (x == 0){
            if ((labirinto[(*pinky).linha-1][(*pinky).coluna] != PAREDE) && (labirinto[(*pinky).linha-1][(*pinky).coluna+1] != PAREDE) && (labirinto[(*pinky).linha-1][(*pinky).coluna+2] != PAREDE) ) {
                ghost_l = (*pinky).linha-1;
                ghost_c = (*pinky).coluna;
                achou_pacman = 0;
            }
        }
        /*baixo*/
        else if (x == 1){
                if ((labirinto[(*pinky).linha+3][(*pinky).coluna] != PAREDE) && (labirinto[(*pinky).linha+3][(*pinky).coluna-1] != PAREDE) && (labirinto[(*pinky).linha+3][(*pinky).coluna+2] != PAREDE) ){
                    ghost_l = (*pinky).linha+1;
                    ghost_c = (*pinky).coluna;
                    achou_pacman = 0;
                }
        }
        /*direita*/
        else if  (x == 2){
            if ((labirinto[(*pinky).linha][(*pinky).coluna+3] != PAREDE) && (labirinto[(*pinky).linha-1][(*pinky).coluna+3] != PAREDE) && (labirinto[(*pinky).linha-1][(*pinky).coluna+3] != PAREDE) ){
                ghost_l = (*pinky).linha;
                ghost_c = (*pinky).coluna+1;
                achou_pacman = 0;
            }
        }
        /*esquerda*/
        if  (x == 3){
            if ((labirinto[(*pinky).linha][(*pinky).coluna-1] != PAREDE) && (labirinto[(*pinky).linha+1][(*pinky).coluna-1] != PAREDE) && (labirinto[(*pinky).linha+2][(*pinky).coluna-1] != PAREDE) ){
                ghost_l = (*pinky).linha;
                ghost_c = (*pinky).coluna+1;
                achou_pacman = 0;
            }
        }
    }


    int i,j,aux_l,aux_c;
    aux_l = 0;
    for(i = (*pinky).linha ; i < (*pinky).linha +3; i++){
        aux_c = 0;
        for(j = (*pinky).coluna; j < (*pinky).coluna +3; j++){
            if ((ant_ghost[aux_l][aux_c] == PASTILHAS) || (ant_ghost[aux_l][aux_c] == FUNDO) || (ant_ghost[aux_l][aux_c] == PASTILHA_ESP)){
                labirinto[i][j] = ant_ghost[aux_l][aux_c];
            }
            else {
                labirinto[i][j] = FUNDO;
            }
            aux_c++;
        }
        aux_l++;
    } 

    (*pinky).coluna= ghost_c;
    (*pinky).linha= ghost_l;

    aux_l = 0;
    for(i = (*pinky).linha ; i < (*pinky).linha +3; i++){
        aux_c = 0 ;
        for(j = (*pinky).coluna; j < (*pinky).coluna +3; j++){
            ant_ghost[aux_l][aux_c] = labirinto[i][j];
            aux_c++;
        }
        aux_l++;
    }


    /*vendo em todos os lados se o fantama matou o pacman*/
    if (((*pinky).linha == (*pacman).ls && (*pinky).coluna == (*pacman).cs) && ((*pinky).linha +1 == (*pacman).ls+1 && (*pinky).coluna == (*pacman).cs) && ((*pinky).linha +2 == (*pacman).ls+2 && (*pinky).coluna == (*pacman).cs))
        --(*vida_pacman);
    else if (((*pinky).linha == (*pacman).ls && (*pinky).coluna == (*pacman).cs) && ((*pinky).linha == (*pacman).ls && (*pinky).coluna+1 == (*pacman).cs+1) && ((*pinky).linha == (*pacman).ls && (*pinky).coluna+2 == (*pacman).cs+2))
        --(*vida_pacman);
    else if (((*pinky).linha == (*pacman).li-2 && (*pinky).coluna == (*pacman).ci) && ((*pinky).linha +1 == (*pacman).li-1 && (*pinky).coluna == (*pacman).ci) && ((*pinky).linha +2 == (*pacman).li && (*pinky).coluna == (*pacman).ci))
        --(*vida_pacman);
    else if (((*pinky).linha == (*pacman).li && (*pinky).coluna == (*pacman).ci-2) && ((*pinky).linha == (*pacman).li && (*pinky).coluna+1 == (*pacman).ci-2) && ((*pinky).linha == (*pacman).li && (*pinky).coluna+2 == (*pacman).ci))
        --(*vida_pacman);


}

/*função para achar a distancia do inky ate o meio do pacman e do blink*/
/*usando as equaçoes distancia de reta e ponto e achando a equação reta, e depois determina a distancia do inky*/
int distancia_inky(int x1, int y1, int x2, int y2, int x0, int y0){

    int a,b,c,dist;

    a = y1 - y2;
    b = x1 - x2;
    c = (x1*y2) - x2 - y1;

    dist = ((a*x0) + (b*y0) + c) / (sqrt( (pow(a,2)) + (pow (b,2) ) ) );
    return dist;
}

void controle_inky(char **labirinto, COORDENADAS *pacman, FANTASMAS *inky, FANTASMAS blinky, char **ant_ghost, int *vida_pacman ){

    int dist_menor;
    int ghost_c = (*inky).coluna;
    int ghost_l = (*inky).linha;
    int achou_pacman = 1;
    dist_menor = distancia_inky((*pacman).ci, (*pacman).li, blinky.coluna, blinky.linha, (*inky).coluna, (*inky).linha);

        /*ESQUERDA*/
    if ((labirinto[(*inky).linha ][(*inky).coluna - 1] == FUNDO) && (labirinto[(*inky).linha - 1][(*inky).coluna - 1] == FUNDO) && (labirinto[(*inky).linha - 2][(*inky).coluna - 1] == FUNDO)){
        if (calcula_dist(((*inky).coluna-1),(*inky).linha,(*pacman).cs,(*pacman).ls) < dist_menor)
            {
                ghost_c = ((*inky).coluna-1) ;
                ghost_l = (*inky).linha;
                achou_pacman = 0;
            }
    }

    /*DIREITA*/
    if ((labirinto[(*inky).linha ][(*inky).coluna +3 ] == FUNDO) && (labirinto[(*inky).linha - 1][(*inky).coluna + 3] == FUNDO) && (labirinto[(*inky).linha - 2][(*inky).coluna + 3] == FUNDO)){
        if (calcula_dist(((*inky).coluna+1),(*inky).linha,(*pacman).cs,(*pacman).ls) < dist_menor)
        {
            ghost_c = ((*inky).coluna+ 3) ;
            ghost_l = (*inky).linha;
            achou_pacman = 0;
        }
    }

    /*CIMA*/
    if ((labirinto[(*inky).linha -1][(*inky).coluna ] == FUNDO) && (labirinto[(*inky).linha -1 ][(*inky).coluna + 1] == FUNDO) && (labirinto[(*inky).linha - 1][(*inky).coluna + 2] == FUNDO)){
        if (calcula_dist((*inky).coluna,((*inky).linha-1),(*pacman).cs,(*pacman).ls) < dist_menor)
        {
            ghost_c = (*inky).coluna;
            ghost_l = ((*inky).linha- 1);
            achou_pacman = 0;
        }
    }

    /*BAIXO*/
    if ((labirinto[(*inky).linha +3][(*inky).coluna ] == FUNDO) && (labirinto[(*inky).linha + 1][(*inky).coluna + 3] == FUNDO) && (labirinto[(*inky).linha +3][(*inky).coluna + 2] == FUNDO)){
        if (calcula_dist((*inky).coluna,((*inky).linha+1),(*pacman).cs,(*pacman).ls) < dist_menor)
        {
            ghost_c = (*inky).coluna;
            ghost_l = ((*inky).linha+ 3);
            achou_pacman = 0;
        }
    }

        /*se o blinky não andar ele vai andar aleatoriamente*/
        int x;
        while (achou_pacman != 0){
            x = rand() % 4;
            if ((labirinto[(*inky).linha -1][(*inky).coluna ] == FUNDO) && (labirinto[(*inky).linha -1 ][(*inky).coluna + 1] == FUNDO) && (labirinto[(*inky).linha - 1][(*inky).coluna + 2] == FUNDO) && (x == 0)){/*cima*/
                ghost_c = (*inky).coluna;
                ghost_l = ((*inky).linha- 1);
                achou_pacman = 0;
            }
            if ((labirinto[(*inky).linha +3][(*inky).coluna ] == FUNDO) && (labirinto[(*inky).linha + 3][(*inky).coluna + 1] == FUNDO) && (labirinto[(*inky).linha +3][(*inky).coluna + 2] == FUNDO) && (x == 1)){/*baixo*/
                ghost_c = (*inky).coluna;
                ghost_l = ((*inky).linha+ 3);
                achou_pacman = 0;
            }
            if ((labirinto[(*inky).linha ][(*inky).coluna +3 ] == FUNDO) && (labirinto[(*inky).linha - 1][(*inky).coluna + 3] == FUNDO) && (labirinto[(*inky).linha - 2][(*inky).coluna + 3] == FUNDO) && (x == 2)){/*direita*/
                ghost_c = ((*inky).coluna+ 3) ;
                ghost_l = (*inky).linha;
                achou_pacman = 0;
            }
            if ((labirinto[(*inky).linha ][(*inky).coluna - 1] == FUNDO) && (labirinto[(*inky).linha - 1][(*inky).coluna - 1] == FUNDO) && (labirinto[(*inky).linha - 2][(*inky).coluna - 1] == FUNDO) && (x == 3)){/*esquerda*/
                ghost_c = ((*inky).coluna-1) ;
                ghost_l = (*inky).linha;
                achou_pacman = 0;
            }
        }

    /*APOS ENCONTRAR MELHOR POSIÇÃO PARA IR ATRAS DE PAC MAN*/
    int i,j,aux_l,aux_c;
    aux_l = 0;
    for(i = (*inky).linha ; i < (*inky).linha +3; i++){
        aux_c = 0;
        for(j = (*inky).coluna; j < (*inky).coluna +3; j++){
            if ((ant_ghost[aux_l][aux_c] == PASTILHAS) || (ant_ghost[aux_l][aux_c] == FUNDO) || (ant_ghost[aux_l][aux_c] == PASTILHA_ESP)){
                labirinto[i][j] = ant_ghost[aux_l][aux_c];
            }
            else {
                labirinto[i][j] = FUNDO;
            }
            aux_c++;
        }
        aux_l++;
    } 

    (*inky).coluna= ghost_c;
    (*inky).linha= ghost_l;

    aux_l = 0;
    for(i = (*inky).linha ; i < (*inky).linha +3; i++){
        aux_c = 0 ;
        for(j = (*inky).coluna; j < (*inky).coluna +3; j++){
            ant_ghost[aux_l][aux_c] = labirinto[i][j];
            aux_c++;
        }
        aux_l++;
    }


    /*vendo em todos os lados se o fantama matou o pacman*/
    if (((*inky).linha == (*pacman).ls && (*inky).coluna == (*pacman).cs) && ((*inky).linha +1 == (*pacman).ls+1 && (*inky).coluna == (*pacman).cs) && ((*inky).linha +2 == (*pacman).ls+2 && (*inky).coluna == (*pacman).cs))
        --(*vida_pacman);
    else if (((*inky).linha == (*pacman).ls && (*inky).coluna == (*pacman).cs) && ((*inky).linha == (*pacman).ls && (*inky).coluna+1 == (*pacman).cs+1) && ((*inky).linha == (*pacman).ls && (*inky).coluna+2 == (*pacman).cs+2))
        --(*vida_pacman);
    else if (((*inky).linha == (*pacman).li-2 && (*inky).coluna == (*pacman).ci) && ((*inky).linha +1 == (*pacman).li-1 && (*inky).coluna == (*pacman).ci) && ((*inky).linha +2 == (*pacman).li && (*inky).coluna == (*pacman).ci))
        --(*vida_pacman);
    else if (((*inky).linha == (*pacman).li && (*inky).coluna == (*pacman).ci-2) && ((*inky).linha == (*pacman).li && (*inky).coluna+1 == (*pacman).ci-2) && ((*inky).linha == (*pacman).li && (*inky).coluna+2 == (*pacman).ci))
        --(*vida_pacman);
   


}

int fugindo_do_pacman(char **labirinto, COORDENADAS *pacman, FANTASMAS *ghost, char **ant_ghost, int *pontos){

    
    int dist_maior;
    int ghost_c = (*ghost).coluna;
    int ghost_l = (*ghost).linha;
    int fugiu_pacman = 1;
    dist_maior  = calcula_dist((*ghost).coluna,(*ghost).linha,(*pacman).cs,(*pacman).ls);
    
    /*ESQUERDA*/
    if ((labirinto[(*ghost).linha ][(*ghost).coluna - 1] == FUNDO) && (labirinto[(*ghost).linha - 1][(*ghost).coluna - 1] == FUNDO) && (labirinto[(*ghost).linha - 2][(*ghost).coluna - 1] == FUNDO)){
        if (calcula_dist(( (*ghost).coluna-1),(*ghost).linha,(*pacman).cs,(*pacman).ls) > dist_maior)
            {
                ghost_c = ((*ghost).coluna-1) ;
                ghost_l = (*ghost).linha;
                fugiu_pacman = 0;
            }
    }

    /*DIREITA*/
    if ((labirinto[(*ghost).linha ][(*ghost).coluna +3 ] == FUNDO) && (labirinto[(*ghost).linha - 1][(*ghost).coluna + 3] == FUNDO) && (labirinto[(*ghost).linha - 2][(*ghost).coluna + 3] == FUNDO)){
        if (calcula_dist( ( (*ghost).coluna+1),(*ghost).linha,(*pacman).cs,(*pacman).ls) > dist_maior)
        {
            ghost_c = ((*ghost).coluna+ 3) ;
            ghost_l = (*ghost).linha;
            fugiu_pacman = 0;
        }
    }

    /*CIMA*/
    if ((labirinto[(*ghost).linha -1][(*ghost).coluna ] == FUNDO) && (labirinto[(*ghost).linha -1 ][(*ghost).coluna + 1] == FUNDO) && (labirinto[(*ghost).linha - 1][(*ghost).coluna + 2] == FUNDO)){
        if (calcula_dist((*ghost).coluna,((*ghost).linha-1),(*pacman).cs,(*pacman).ls) > dist_maior)
        {
            ghost_c = (*ghost).coluna;
            ghost_l = ((*ghost).linha- 1);
            fugiu_pacman = 0;
        }
    }

    /*BAIXO*/
    if ((labirinto[(*ghost).linha +3][(*ghost).coluna ] == FUNDO) && (labirinto[(*ghost).linha + 1][(*ghost).coluna + 3] == FUNDO) && (labirinto[(*ghost).linha +3][(*ghost).coluna + 2] == FUNDO)){
        if (calcula_dist((*ghost).coluna,((*ghost).linha+1),(*pacman).cs,(*pacman).ls) > dist_maior)
        {
            ghost_c = (*ghost).coluna;
            ghost_l = ((*ghost).linha+ 3);
            fugiu_pacman = 0;
        }
    }

        /*se o fantasma não achar um menor caminha ele vai andar aleatoriante*/
        int x;
        while (fugiu_pacman != 0){
            x = rand() % 4;
            if ((labirinto[(*ghost).linha -1][(*ghost).coluna ] == FUNDO) && (labirinto[(*ghost).linha -1 ][(*ghost).coluna + 1] == FUNDO) && (labirinto[(*ghost).linha - 1][(*ghost).coluna + 2] == FUNDO) && (x == 0)){/*cima*/
                ghost_c = (*ghost).coluna;
                ghost_l = ((*ghost).linha- 1);
                fugiu_pacman = 0;
            }
            if ((labirinto[(*ghost).linha +3][(*ghost).coluna ] == FUNDO) && (labirinto[(*ghost).linha + 3][(*ghost).coluna + 1] == FUNDO) && (labirinto[(*ghost).linha +3][(*ghost).coluna + 2] == FUNDO) && (x == 1)){/*baixo*/
                ghost_c = (*ghost).coluna;
                ghost_l = ((*ghost).linha+ 3);
                fugiu_pacman = 0;
            }
            if ((labirinto[(*ghost).linha ][(*ghost).coluna +3 ] == FUNDO) && (labirinto[(*ghost).linha - 1][(*ghost).coluna + 3] == FUNDO) && (labirinto[(*ghost).linha - 2][(*ghost).coluna + 3] == FUNDO) && (x == 2)){/*direita*/
                ghost_c = ((*ghost).coluna+ 3) ;
                ghost_l = (*ghost).linha;
                fugiu_pacman = 0;
            }
            if ((labirinto[(*ghost).linha ][(*ghost).coluna - 1] == FUNDO) && (labirinto[(*ghost).linha - 1][(*ghost).coluna - 1] == FUNDO) && (labirinto[(*ghost).linha - 2][(*ghost).coluna - 1] == FUNDO) && (x == 3)){/*esquerda*/
                ghost_c = ((*ghost).coluna-1) ;
                ghost_l = (*ghost).linha;
                fugiu_pacman = 0;
            }
        }

    int i,j,aux_l,aux_c;
    aux_l = 0;
    for(i = (*ghost).linha ; i < (*ghost).linha +3; i++){
        aux_c = 0;
        for(j = (*ghost).coluna; j < (*ghost).coluna +3; j++){
            if ((ant_ghost[aux_l][aux_c] == PASTILHAS) || (ant_ghost[aux_l][aux_c] == FUNDO) || (ant_ghost[aux_l][aux_c] == PASTILHA_ESP)){
                labirinto[i][j] = ant_ghost[aux_l][aux_c];
            }
            else {
                labirinto[i][j] = FUNDO;
            }
            aux_c++;
        }
        aux_l++;
    } 

    (*ghost).coluna= ghost_c;
    (*ghost).linha= ghost_l;

    aux_l = 0;
    for(i = (*ghost).linha ; i < (*ghost).linha +3; i++){
        aux_c = 0 ;
        for(j = (*ghost).coluna; j < (*ghost).coluna +3; j++){
            ant_ghost[aux_l][aux_c] = labirinto[i][j];
            aux_c++;
        }
        aux_l++;
    }


    /*vendo em todos os lados se o fantama foi morto pelo pacman*/
    int morreu = 0;
    if (((*ghost).linha == (*pacman).ls && (*ghost).coluna == (*pacman).cs) && ((*ghost).linha +1 == (*pacman).ls+1 && (*ghost).coluna == (*pacman).cs) && ((*ghost).linha +2 == (*pacman).ls+2 && (*ghost).coluna == (*pacman).cs)){
        morreu = 1;
        (*pontos)=(*pontos)+200;
    }
    else if (((*ghost).linha == (*pacman).ls && (*ghost).coluna == (*pacman).cs) && ((*ghost).linha == (*pacman).ls && (*ghost).coluna+1 == (*pacman).cs+1) && ((*ghost).linha == (*pacman).ls && (*ghost).coluna+2 == (*pacman).cs+2)){
        morreu = 1;
        (*pontos)=(*pontos)+200;
    }
    else if (((*ghost).linha == (*pacman).li-2 && (*ghost).coluna == (*pacman).ci) && ((*ghost).linha +1 == (*pacman).li-1 && (*ghost).coluna == (*pacman).ci) && ((*ghost).linha +2 == (*pacman).li && (*ghost).coluna == (*pacman).ci)){
        morreu = 1;
        (*pontos)=(*pontos)+200;
    }
    else if (((*ghost).linha == (*pacman).li && (*ghost).coluna == (*pacman).ci-2) && ((*ghost).linha == (*pacman).li && (*ghost).coluna+1 == (*pacman).ci-2) && ((*ghost).linha == (*pacman).li && (*ghost).coluna+2 == (*pacman).ci)){
        morreu = 1;
        (*pontos)=(*pontos)+200;
    }

    return morreu;
    
}

void adicionando_fantasmas( char **labirinto, FANTASMAS *ghost, char **ant_ghost){
    
    (*ghost).linha = 12;
    (*ghost).coluna = 38;

    int i,j,aux_l,aux_c;
    aux_l = 0;
    for(i = (*ghost).linha ; i < (*ghost).linha +3; i++){
        aux_c = 0 ;
        for(j = (*ghost).coluna ; j < (*ghost).coluna +3; j++){
            ant_ghost[aux_l][aux_c] = labirinto[i][j];
            aux_c++;
        }
        aux_l++;
    }

}

/*inicializando o jogo*/
void inicializando_jogo(char **labirinto){

    initscr();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    paredes_labirinto(labirinto);

}

/*testando se o jogo ja acabou*/
int proxima_fase(char **labirinto){

    int i=0;
    int j=0;
    int nao_acabou = 1;

    while ( i < LINHAS || nao_acabou != 0 ){
        while(j < COLUNAS || nao_acabou != 0){
            if (labirinto[i][j] == PASTILHAS || labirinto[i][j] == PASTILHA_ESP  ){
                    nao_acabou=0;
                }
            j++;
        }
        i++;
    }

    return nao_acabou;
}

/*comecando novamente o jogo*/
void comecar_novamente(char **labirinto){

    int i,j;
    for (i = 0; i < LINHAS; i++){
        for (j= 0; j < COLUNAS; j++){
            if (labirinto[i][j] == FUNDO){
                labirinto[i][j] = PASTILHAS;
            }
        }
    }

    for (i=17;i < 24; i++){
        for(j=35; j < 44; j++){
            labirinto[i][j] = FUNDO;
        }
    }


    /*colocando as pastilhas especiais*/
    for (i=1;i < 3; i++){
        for (j=2; j< 4; j++){
            labirinto[i][j] = PASTILHA_ESP;
        }
    }

    for (i=33;i < 35; i++){
        for (j=2; j< 4; j++){
            labirinto[i][j] = PASTILHA_ESP;
        }
    }

    for (i=1;i < 3; i++){
        for (j=77; j< 79; j++){
            labirinto[i][j] = PASTILHA_ESP;
        }
    }

    for (i=33;i < 34; i++){
        for (j=77; j< 79; j++){
            labirinto[i][j] = PASTILHA_ESP;
        }
    }
}

void refazendo_ant_ghost(char **ant_ghost){

    int i, j;
    int tam = 3;
    for(i = 0; i < tam; i++){
        for(j = 0; j < tam; j++){
            ant_ghost[i][j] = FUNDO;
        }
    }

}

int main(){

    char **labirinto;
    labirinto = comecando_labirinto();
    char movimento;
    COORDENADAS pacman;
    FANTASMAS blinky,pinky,clyde,inky;
    colocar_pacman( &pacman);

    colocar_fantasmas( &blinky, &pinky, &inky, &clyde);
    char **ant_blinky, **ant_pinky, **ant_inky, **ant_clyde;
    ant_blinky = crinado_ant_ghost();
    ant_pinky = crinado_ant_ghost();
    ant_inky = crinado_ant_ghost();
    ant_clyde = crinado_ant_ghost();
    crinado_ant_blinky( labirinto, &blinky, ant_blinky );

    int tempo_past_esp = 0;
    int pontos = 0;
    int vida_pacman = 1;
    int matou_blinky, matou_pinky, matou_inky, matou_clyde;
    int pacman_past_esp = 0;

    /*começo do jogo*/
    inicializando_jogo(labirinto);

    /*cores para o labirinto e o pacman*/
    start_color();
    init_pair(COR_PAREDE, COLOR_BLUE, COLOR_BLUE);/*PAREDES*/
    init_pair(COR_PACMAN, COLOR_YELLOW, COLOR_YELLOW);/*PACMAN*/
    init_pair(COR_PASTILHAS_ESP, COLOR_WHITE, COLOR_BLACK);/*PASTILHAS ESPECIAL*/
    init_pair(COR_PASTILHAS, COLOR_WHITE, COLOR_BLACK);/*PASTILHAS*/
    init_pair(COR_FUNDO, COLOR_BLACK, COLOR_BLACK); /*FUNDO*/
    init_pair(COR_BLINKY, COLOR_RED, COLOR_RED);
    init_pair(COR_PINKY, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(COR_INKY, COLOR_GREEN, COLOR_GREEN); 
    init_pair(COR_CLYDE, COLOR_CYAN, COLOR_CYAN); 
    

    printw("Para jogar use as teclas:\n");
    printw("     w - cima\n");
    printw("     s - baixo\n");
    printw("     a - esquerda\n");
    printw("     d - direita\n");
    printw("Aperta ' s ' para começar\n");
    printw("Ou apertar ' q ' para sair\n");

    movimento = getch(); /*esperando a tecla s */
    imprimir_tabuleiro(labirinto, pacman, blinky, pinky, inky, clyde, pontos, vida_pacman);

    while ((movimento != 's') || (vida_pacman == 0)){

        movimento = getch();
        usleep(6000);
        switch (movimento){
            /*movimento para cima*/
            case 'w':
                if (testar_movimento_cima(labirinto,pacman)){
                    pacman_past_esp = comeu_pastilha_esp_cima(labirinto, pacman, &pontos);
                    movimento_pacman_cima(labirinto,&pacman,&pontos);
                }
                break;
            /*movimento para baixo*/
            case 's':
                if (testar_movimento_direita(labirinto,pacman)){
                    pacman_past_esp = comeu_pastilha_esp_baixo(labirinto, pacman, &pontos);
                    movimento_pacman_direita(labirinto,&pacman,&pontos);
                }
                break;
            /*movimento para direita*/
            case 'd' :
                if (testar_movimento_direita(labirinto,pacman)){
                    pacman_past_esp = comeu_pastilha_esp_direita(labirinto, pacman, &pontos);
                    movimento_pacman_direita(labirinto,&pacman,&pontos);
                }
                break;
            /*movimento para esquerda*/
            case 'a':
                if (testar_movimento_esquerdo(labirinto,pacman)){
                    pacman_past_esp = comeu_pastilha_esp_esquerdo(labirinto, pacman, &pontos);
                    movimento_pacman_esquerdo(labirinto,&pacman,&pontos);
                }
                break;
                }

            /*fantasmas*/
            int add_pinky = 0;
            int add_inky = 0;
            int add_clyde = 0;
            int tempo_pinky = 0;
            int tempo_inky = 0;
            int tempo_clyde = 0;
            if (pacman_past_esp != 1){

                controle_blink(labirinto, &pacman, &blinky, ant_blinky, &vida_pacman);
                if(add_pinky != 0){
                    controle_pinky(labirinto, &pacman, &pinky, ant_pinky, &vida_pacman, movimento);
                }
                if(add_inky != 0){
                    controle_inky(labirinto, &pacman, &inky, blinky, ant_inky, &vida_pacman);
                }
                if(add_clyde != 0){
                    controle_clyde(labirinto, &pacman, &clyde, ant_clyde, &vida_pacman );
                }

                if ((tempo_pinky++) == 15){
                    adicionando_fantasmas(labirinto,&blinky,ant_pinky);
                    tempo_pinky = 16;
                    add_pinky = 1;
                }
                if ( (tempo_inky++) == 25 ){
                    adicionando_fantasmas(labirinto,&inky, ant_inky);
                    tempo_inky = 26;
                    add_inky = 1;
                }
                if ( (tempo_clyde++) == 36){
                    adicionando_fantasmas(labirinto, &clyde, ant_clyde);
                    tempo_clyde = 37;
                    add_clyde = 1;
                }
            }


        /*quando o pacman come a pastilha especial*/
        if ( pacman_past_esp != 0) {
            while (tempo_past_esp <= 40) {
            switch (movimento){
                /*movimento para cima*/
                case 'w':
                    if (testar_movimento_cima(labirinto,pacman)){
                        pacman_past_esp = comeu_pastilha_esp_cima(labirinto, pacman, &pontos);
                        movimento_pacman_cima(labirinto,&pacman,&pontos);
                    }
                    break;
                /*movimento para baixo*/
                case 's':
                    if (testar_movimento_direita(labirinto,pacman)){
                        pacman_past_esp = comeu_pastilha_esp_baixo(labirinto, pacman, &pontos);
                        movimento_pacman_direita(labirinto,&pacman,&pontos);
                    }
                    break;
                /*movimento para direita*/
                case 'd' :
                    if (testar_movimento_direita(labirinto,pacman)){
                        pacman_past_esp = comeu_pastilha_esp_direita(labirinto, pacman, &pontos);
                        movimento_pacman_direita(labirinto,&pacman,&pontos);
                    }
                    break;
                /*movimento para esquerda*/
                case 'a':
                    if (testar_movimento_esquerdo(labirinto,pacman)){
                        pacman_past_esp = comeu_pastilha_esp_esquerdo(labirinto, pacman, &pontos);
                        movimento_pacman_esquerdo(labirinto,&pacman,&pontos);
                    }
                    break;
                    }

                matou_blinky = fugindo_do_pacman(labirinto, &pacman, &blinky, ant_blinky, &pontos);
                matou_pinky = fugindo_do_pacman(labirinto, &pacman, &pinky, ant_pinky, &pontos);
                matou_inky = fugindo_do_pacman(labirinto, &pacman, &inky, ant_inky, &pontos);
                matou_clyde = fugindo_do_pacman(labirinto, &pacman, &clyde, ant_clyde, &pontos);
                tempo_past_esp++;

                if (matou_blinky){
                    blinky.linha = 12;
                    blinky.coluna = 38;
                }
                if (matou_pinky){
                    pinky.linha = 12;
                    pinky.coluna = 38;
                }
                if (matou_inky){
                    inky.linha = 12;
                    inky.coluna = 38;
                }
                if (matou_clyde){
                    clyde.linha = 12;
                    clyde.coluna = 38;
                }
                
            }
            tempo_past_esp = 0;
            pacman_past_esp = 0;
        }

        if(proxima_fase(labirinto)){
            comecar_novamente(labirinto);
            colocar_pacman(&pacman);
            colocar_fantasmas( &blinky, &pinky, &inky, &clyde);
            crinado_ant_blinky( labirinto, &blinky, ant_blinky );
            refazendo_ant_ghost( ant_pinky);
            refazendo_ant_ghost( ant_inky);
            refazendo_ant_ghost( ant_clyde);

        } 
        imprimir_tabuleiro(labirinto, pacman, blinky, pinky, inky, clyde, pontos, vida_pacman);
    }

    endwin();
    return 0;
}