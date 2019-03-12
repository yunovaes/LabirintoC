#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int x;
    int y;
}Coordenada;

typedef struct{
    Coordenada *coordenadas;
    int i;
    int f;
}TFila;

int **matrix;
int linha, coluna;

// funcoes para o TAD Fila
TFila * InitFila(int N);
void insereFila( TFila *F, Coordenada coord);
Coordenada removerFila(TFila *F);
void liberaFila(TFila *F);

//funcoes para a matrix
void printaMatrix();
void preencheMatrixArquivo(FILE * fp);

//funcoes para inserir as coordenadas e verificar se estao corretas
Coordenada pegarCoordenadaInicio(TFila * fila);
Coordenada pegarCoordenadaFinal();

//funcoes para preencher a matrix a partir das coordenadas inseridas
void chamarPreencheLabirinto(TFila *, int N);
void preencheLabirinto (TFila *F, Coordenada coord);

//funcao para a achar o menor caminho entre as coordenadas inseridas
Coordenada * leCaminho(Coordenada coordInicio, Coordenada coordAtual, int tamanho);

//funcao para printar o caminho percorrido pelo labirinto
void printarCaminho(Coordenada* caminho, int tamanho);

int main () {

    //Abrir arquivo
    FILE *fp = fopen("matrix.txt","r");
    TFila * fila;

    //preenchendo a matrix e printando em seguida
    preencheMatrixArquivo(fp);
    printaMatrix();

    //inicializando fila
    fila = InitFila(linha*coluna);

    //pegar as coordenadas de inicio e final
    Coordenada CoordInicio, CoordFim;
    CoordInicio = pegarCoordenadaInicio(fila);
    CoordFim = pegarCoordenadaFinal();

    //preenche a matrix a partir das coordenadas inseridas
    chamarPreencheLabirinto(fila, linha*coluna);
    matrix[CoordInicio.x][CoordInicio.y] = 0;

    printaMatrix();
    int tamanhoCaminho = matrix[CoordFim.x][CoordFim.y];

    //inicializa o vetor de caminho e atribui o caminho percorrido pela funcao leCaminho
    //e printa o caminho logo em seguida
    Coordenada * caminho;
    caminho = (Coordenada *) calloc (tamanhoCaminho, sizeof(Coordenada) );
    caminho = leCaminho(CoordInicio,CoordFim, tamanhoCaminho);
    printarCaminho(caminho, tamanhoCaminho);

    return 1;
}

void printaMatrix(){
    int k, l;
    for(k = 0; k < linha; k++){
        for(l = 0; l < coluna; l++){
            printf("%d ", matrix[k][l]);
        }
        printf("\n");
    }
}

void preencheMatrixArquivo(FILE * fp){

    //Pega número de linha e coluna
    fscanf(fp, "%d %d", &linha, &coluna);

    int k, l;
    //alocando matriz
    matrix = (int **) calloc ( linha + 1, sizeof(int) );
    for (k = 0; k < linha; k++){
        matrix[k] = (int *) calloc ( coluna + 1, sizeof(int) );
    }

    //preenchendo a matriz a partir do arquivo texto
    for(k = 0; k < linha; k++){
        for(l = 0; l < coluna; l++){
            fscanf(fp, "%d", &matrix[k][l]);
        }
    }
}

Coordenada pegarCoordenadaInicio(TFila * fila){

    int ok = 0, bloqueio = 0;
    Coordenada CoordInicio;

    while ( !ok ){
        //lendo as coordenadas de inicio e final
        printf("Digite a coordenada de inicio do Labirinto: \n");
        scanf("%d", &CoordInicio.x);
        scanf("%d", &CoordInicio.y);
        if(CoordInicio.x >= 0 && CoordInicio.x < linha){
            if(CoordInicio.y >= 0 && CoordInicio.y < coluna) {
                if(matrix[CoordInicio.x][CoordInicio.y] != -1){
                    ok = 1;
                    insereFila(fila, CoordInicio);
                } else {
                    printf("Bloqueio! \n");
                }
            }else {
                 printf("Coordenada errada! \n");
            }
        } else {
            printf("Coordenada errada! \n");
        }
    }

    return CoordInicio;
}

Coordenada pegarCoordenadaFinal(){
    int ok = 0;
    Coordenada CoordFim;
    while ( !ok ){
        //lendo as coordenadas de inicio e final
        printf("Digite a coordenada final do Labirinto: \n");
        scanf("%d", &CoordFim.x);
        scanf("%d", &CoordFim.y);
        if(CoordFim.x >= 0 && CoordFim.x < linha){
            if(CoordFim.y >= 0 && CoordFim.y < coluna) {
                if(matrix[CoordFim.x][CoordFim.y] != -1){
                    ok = 1;
                } else {
                    printf("Bloqueio! \n");
                }
            }else {
                 printf("Coordenada errada! \n");
            }
        } else {
            printf("Coordenada errada! \n");
        }
    }
    return CoordFim;
}

TFila * InitFila( int N ){

    TFila *T;

    T = (TFila *) calloc (N, sizeof(TFila));

    if(!T){
        printf("Deu ruim ao alocar a fila");
        exit(1);
    }

    T->i = 0;
    T->f = 0;
    T->coordenadas = (Coordenada *) calloc (N, sizeof(Coordenada) );

    return T;

}

void insereFila( TFila *F, Coordenada coord){
    F->coordenadas[F->f++] = coord;
}

void chamarPreencheLabirinto(TFila *F, int N){

    int i = 0;
    while (i != N) {
        Coordenada coordAuxiliar = removerFila(F);
        preencheLabirinto(F, coordAuxiliar);
        i++;
      }
}


void preencheLabirinto(TFila *F, Coordenada coord){

    Coordenada coordAux;

    //preencher em cima
    if ( coord.x >= 0 && coord.x < linha && coord.y - 1 >= 0 && coord.y - 1 < coluna ){
        if ( matrix[coord.x][coord.y - 1] != -1 ) {
            if(matrix[coord.x][coord.y - 1] == 0){
                matrix[coord.x][coord.y - 1] = matrix[coord.x][coord.y] + 1;
                coordAux.x = coord.x;
                coordAux.y = coord.y-1;
                insereFila(F, coordAux);
            }
        }
    }

    //preencher na direita
    if ( coord.x + 1 >= 0 && coord.x + 1 < linha && coord.y >= 0 && coord.y < coluna ){
        if ( matrix[coord.x + 1][coord.y] != -1 ) {
            if(matrix[coord.x + 1][coord.y] == 0){
                matrix[coord.x + 1][coord.y] = matrix[coord.x][coord.y] + 1;
                coordAux.x = coord.x + 1;
                coordAux.y = coord.y;
                insereFila(F, coordAux);
            }
        }
    }

    //preencher em baixo
    if ( coord.x >= 0 && coord.x < linha && coord.y + 1 >= 0 && coord.y + 1 < coluna ){
        if ( matrix[coord.x][coord.y + 1] != -1 ) {
            if(matrix[coord.x][coord.y + 1] == 0){
                matrix[coord.x][coord.y + 1] = matrix[coord.x][coord.y] + 1;
                coordAux.x = coord.x;
                coordAux.y = coord.y + 1;
                insereFila(F, coordAux);
            }
        }
    }

    //preencher na esquerda
    if ( coord.x - 1 >= 0 && coord.x - 1 < linha && coord.y >= 0 && coord.y < coluna ){
        if ( matrix[coord.x - 1][coord.y] != -1 ) {
            if(matrix[coord.x - 1][coord.y] == 0){
                matrix[coord.x - 1][coord.y] = matrix[coord.x][coord.y] + 1;
                coordAux.x = coord.x - 1;
                coordAux.y = coord.y;
                insereFila(F, coordAux);
            }
        }
    }
}

Coordenada removerFila(TFila *F){
    return F->coordenadas[F->i++];
}

Coordenada * leCaminho(Coordenada coordInicio, Coordenada coordAtual, int tamanho){

    Coordenada *caminho;
    caminho = (Coordenada *) calloc (tamanho, sizeof(Coordenada));
    Coordenada coordAuxiliar;
    int i = 0;

    while( ! (coordAtual.x == coordInicio.x && coordAtual.y == coordInicio.y) ){

        coordAuxiliar.x = coordAtual.x;
        coordAuxiliar.y = coordAtual.y;

        //acima
        if ( coordAtual.x >= 0 && coordAtual.x < linha && coordAtual.y - 1 >= 0 && coordAtual.y - 1 < coluna ){
            if ( matrix[coordAtual.x][coordAtual.y - 1] != -1 ) {
                if(matrix[coordAtual.x][coordAtual.y - 1] < matrix[coordAtual.x][coordAtual.y] &&
                   matrix[coordAtual.x][coordAtual.y - 1] < matrix[coordAuxiliar.x][coordAuxiliar.y]){
                    coordAuxiliar.x = coordAtual.x;
                    coordAuxiliar.y = coordAtual.y-1;
                }
            }
        }

        //direita
        if ( coordAtual.x + 1 >= 0 && coordAtual.x + 1 < linha && coordAtual.y >= 0 && coordAtual.y < coluna ){
            if ( matrix[coordAtual.x + 1][coordAtual.y] != -1 ) {
                if(matrix[coordAtual.x + 1][coordAtual.y] < matrix[coordAtual.x][coordAtual.y] &&
                   matrix[coordAtual.x + 1][coordAtual.y] < matrix[coordAuxiliar.x][coordAuxiliar.y]){
                    coordAuxiliar.x = coordAtual.x + 1;
                    coordAuxiliar.y = coordAtual.y;
                }
            }
        }

        //baixo
        if ( coordAtual.x >= 0 && coordAtual.x < linha && coordAtual.y + 1 >= 0 && coordAtual.y + 1 < coluna ){
            if ( matrix[coordAtual.x][coordAtual.y + 1] != -1 ) {
                if(matrix[coordAtual.x][coordAtual.y + 1] < matrix[coordAtual.x][coordAtual.y] &&
                   matrix[coordAtual.x][coordAtual.y + 1] < matrix[coordAuxiliar.x][coordAuxiliar.y]){
                    coordAuxiliar.x = coordAtual.x;
                    coordAuxiliar.y = coordAtual.y+1;
                }
            }
        }

        //esquerda
        if ( coordAtual.x - 1 >= 0 && coordAtual.x - 1 < linha && coordAtual.y >= 0 && coordAtual.y < coluna ){
            if ( matrix[coordAtual.x - 1][coordAtual.y] != -1 ) {
                if(matrix[coordAtual.x - 1][coordAtual.y] < matrix[coordAtual.x][coordAtual.y] &&
                   matrix[coordAtual.x - 1][coordAtual.y] < matrix[coordAuxiliar.x][coordAuxiliar.y]){
                    coordAuxiliar.x = coordAtual.x - 1;
                    coordAuxiliar.y = coordAtual.y;
                }
            }
        }
        caminho[i].x = coordAuxiliar.x;
        caminho[i].y = coordAuxiliar.y;
        i++;

        coordAtual.x = coordAuxiliar.x;
        coordAtual.y = coordAuxiliar.y;
    }

    return caminho;
}

void printarCaminho(Coordenada * caminho, int tamanho){

    printf("\n");
    int i;
    for(i = tamanho-1; i >= 0; i--){
        printf("%d - %d\n", caminho[i].x, caminho[i].y);
    }
}
