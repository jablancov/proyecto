/*Proyecto juego tictactoe sin interfaz en gtk*/
/*Desarollado por Carlos Nuñez c25586 y Jorge Blanco*/
/*La interfaz se encuentra afuera de esta carpeta*/
#include<stdio.h>
char tabladejuego[3][3];
void arrancartabladejuego()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tabladejuego[i][j] = ' ';
        }
    }
    int cuenta = 1;
    printf("\n\n\t  ");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printf("%d", cuenta++);
            if (j < 2)
            {
                printf("  |  ");
            }
        }
        if (i < 2)
        printf("\n\t----------------\n\t  ");
    }
    printf("\n\n\n");
}
void ensenartablero(int x, int y)
{
    printf("\n\n\t  ");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c", tabladejuego[i][j]);
            if (j < 2)
            {
                printf("  |  ");
            }
        }
        if (i < 2)
        printf("\n\t----------------\n\t  ");
    }
    printf("\n\n\n");
}
 
// Funcion para cambiar el tablero de juego
int actualizartablero(int celda, char playerSign)
{
    int fila = (celda - 1) / 3;
    int columna = (celda- 1) % 3;
    int esvalido = 1;
    if (tabladejuego[fila][columna] != ' ')
    {
        printf("\n La celda que ha seleccionado esta ocupada\n");
        esvalido = 0;
    }
    else
    {
        tabladejuego[fila][columna] = playerSign;
    }
    ensenartablero(fila, columna);
 
    return esvalido;
}
int verificar(char checkearganador)
{
    if (tabladejuego[0][0] == checkearganador && tabladejuego[0][1] == checkearganador && tabladejuego[0][2] == checkearganador ||
      tabladejuego[1][0] == checkearganador && tabladejuego[1][1] == checkearganador && tabladejuego[1][2] == checkearganador ||
      tabladejuego[2][0] == checkearganador && tabladejuego[2][1] == checkearganador && tabladejuego[2][2] == checkearganador)
    {
        return 1;
      }
    else if (tabladejuego[0][0] == checkearganador && tabladejuego[1][0] == checkearganador && tabladejuego[2][0] == tabladejuego ||
           tabladejuego[0][1] == checkearganador && tabladejuego[1][1] == checkearganador && tabladejuego[2][1] == tabladejuego ||
           tabladejuego[0][2] == checkearganador && tabladejuego[1][2] == checkearganador && tabladejuego[2][2] == checkearganador)
    {
        return 1;
    }
    else if (tabladejuego[0][0] == checkearganador && tabladejuego[1][1] == checkearganador && tabladejuego[2][2] == checkearganador ||
           tabladejuego[0][2] == checkearganador && tabladejuego[1][1] == checkearganador && tabladejuego[2][0] == checkearganador)
    {
        return 1;
    }
    return 0;
}
void Jugartictactoe()
{
    int resultadodeljuego = 0;
    int celda = 1;
    int usosdeljuego = 0;
    int cambiosenelresultado = 1;
    char Simbolo_jugador = ' ';
    while (!resultadodeljuego && usosdeljuego < 9)
    {
        if (usosdeljuego % 2 == 0)
        {
            printf("\nTurno del Jugador 1,Escoga una casila[ X ] : ");
            Simbolo_jugador = 'X';
        }
        else
        {
            printf("\nTurno del Jugador 2,escoga una casila[ X ] :");
            Simbolo_jugador = 'O';
        }
        scanf("%d", &celda);
        if (celda > 0 && celda < 10)
        {
            cambiosenelresultado = actualizartablero(celda,Simbolo_jugador);
            if (cambiosenelresultado)
            {
                resultadodeljuego = verificar(Simbolo_jugador);
                if (resultadodeljuego==1)
                {
                    printf("\t *** El Jugador %d Ha ganado el juego. ***\n", Simbolo_jugador == 'X' ? 1 : 2);
                }
                usosdeljuego++;
            }
        }
        else if (celda == -1)
        {
            printf("\n\tEl juego ha finalizado\n");
            return;
        }
        else
        {
            printf("\nFavor ingresar una celda valida\n");
        }
    }
 
    if (resultadodeljuego && usosdeljuego == 9)
    {
        printf("\n\t El resultado del juego es un empate.\n");
    }
    printf("\n\t FIn del Juego\n");
}
 
int main()
{
    printf("Bienvenido a Tic Tac Toe o tres en raya tambien conocido como el juego del gato\n\n");
    printf("\n* Instrucciones \n\n");
    printf("\tEl simbolo del Jugador 1 es: X\n");
    printf("\tEl simbolo del Jugador 2 es : O");
    printf("\n\tPara salir del Juego escriba -1\n");
 
    printf("\n\n* Cantidad de celdas en la fila:\n");
    arrancartabladejuego();
 
    char start = ' ';
    printf("\n> Presione enter para empezar");
    scanf("%c", &start);
    if (start)
    {
        int selecciondereseteo = 1;
        // restart the game
        while (selecciondereseteo)
        {
            Jugartictactoe();
            printf("\n* Menu\n");
            printf("\nPressione 1 para reiniciar el juego");
            printf("\nPresione 0 para salir del programa");
            printf("\n\nSeleccion Escogida: ");
            scanf("%d", &selecciondereseteo);
            if (selecciondereseteo)
            {
                arrancartabladejuego();
            }
            printf("\n");
        }
    }
    printf("\nGracias por jugar el juego de Tic tac toe(tres en raya) \n");
    return 0;
}