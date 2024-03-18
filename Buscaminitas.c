#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define B 10
#define TAM 10

void creartabla(char tablero[TAM][TAM], char tablerobombastic[TAM][TAM]);
void colocarbombita(char tablero[TAM][TAM]);
void mostrartablero(char tablero[TAM][TAM], char tablerobombastic[TAM][TAM]);
void coordenadas(char tablero[TAM][TAM], char tablerobombastic[TAM][TAM]);
void destapados(char tablero[TAM][TAM], char tablerobombastic[TAM][TAM], int, int);
void actualizartablero(char tablerobombastic[TAM][TAM], int, int);
void explosion(char tablerobombastic[TAM][TAM], char tablero[TAM][TAM]);
int comprobacion(char tablero[TAM][TAM]);

int main()
{
    srand(time(NULL)); 

    char tablerobombastic[TAM][TAM];
    char tablero[TAM][TAM];

    creartabla(tablero, tablerobombastic);

    colocarbombita(tablerobombastic);

    coordenadas(tablero, tablerobombastic);

    while(getchar() != '\n');
    while(getchar() != '\n');

    return 0;
}

// Crear las tablas, una con todo '-' que es la que se va amostrar y otra con '0' que es la escondida
void creartabla(char tablero[TAM][TAM], char tablerobombastic[TAM][TAM])
{
    // Bucle para recorrer todo el array
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
        {
            tablero[i][j] = '-';
            tablerobombastic[i][j] = '0';
        }
}

// Coloca todas las bombar por todo el tablero aleatoriamente
void colocarbombita(char tablerobombastic[TAM][TAM])
{
    int fila;
    int columna;
    
    for (int i = 0; i < B; i++)
    {
        fila = rand() % B;
        columna = rand() % B;
        while(tablerobombastic[fila][columna] == 'B')
        {
            fila = rand() % B;
            columna = rand() % B;
        }

        tablerobombastic[fila][columna] = 'B'; 
        actualizartablero(tablerobombastic, fila, columna);
    }
}
 
void actualizartablero(char tablerobombastic[TAM][TAM], int fila, int columna)
{
    for(int i = fila - 1; i <= fila + 1; i++)
    {
        if(i >= TAM || i < 0) continue;
        for(int j = columna - 1; j <= columna + 1; j++)
        {
            if(j >= TAM || j < 0) continue;
                if(tablerobombastic[i][j] != 'B')
                    tablerobombastic[i][j] = (int) tablerobombastic[i][j] + 1;
        }
    }
}

// Introduccion de coordenadas
void coordenadas(char tablero[TAM][TAM], char tablerobombastic[TAM][TAM])
{
    int x, y;
    int win = 0;
    do
    {    
        printf("\nIntroduce una coordenada pls (rango de 0 a 9): ");
        scanf("%d %d", &x, &y);

        if((x < 0 || x > 9) || (y < 0 || y > 9))
        {
            printf("Rango no permitido, prueba otra vez");
        }
        else
        {
            if(tablerobombastic[x][y] == 'B')
            {
                explosion(tablerobombastic, tablero);
                printf("Vaya matao, has perdido\n");
            }
            else if(tablero[x][y] == ' ')
            {
                printf("Ya se ha jugado esa casilla imbecil\n");
            }
            else
            {
                destapados(tablero, tablerobombastic, x, y);
                mostrartablero(tablero, tablerobombastic);
            }
        }
        win = comprobacion(tablero);
    }while(tablerobombastic[x][y] != 'B' && !win);

    if(win)
    {
        printf("\nGanaste de chorra maricon");
    }
}

void mostrartablero(char tablero[TAM][TAM], char tablerobombastic[TAM][TAM])
{
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            printf("%c ", tablero[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            printf("%c ", tablerobombastic[i][j]);
        }
        printf("\n");
    }
}

void explosion(char tablerobombastic[TAM][TAM], char tablero[TAM][TAM])
{
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            if(tablerobombastic[i][j] == 'B')
            {
                tablero[i][j] = 'X';
            }
            else
            {
                tablero[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            printf("%c ", tablero[i][j]);
        }
        printf("\n");
    }
}

void destapados(char tablero[TAM][TAM], char tablerobombastic[TAM][TAM], int x, int y)
{
    // Verificar que la casilla seleccionada no contiene una bomba
    if (tablerobombastic[x][y] != '0') {
        tablero[x][y] = tablerobombastic[x][y];
        return;
    }

    // Descubrir la casilla seleccionada
    tablero[x][y] = ' ';

    // Verificar las casillas adyacentes en todas las direcciones
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            // Verificar que las coordenadas estén dentro del tablero
            if (i >= 0 && i < TAM && j >= 0 && j < TAM) {
                // Si la casilla no ha sido destapada aún, llamar a la función destapados
                if (tablero[i][j] == '-') {
                    destapados(tablero, tablerobombastic, i, j);
                }
            }
        }
    }
}

int comprobacion(char tablero[TAM][TAM])
{
    int cont = 0;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if(tablero[i][j] == '-')
            {
                cont++;
            }
        }
    }

    return cont == B;
}
