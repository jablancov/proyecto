#include <stdbool.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#define computadora 1 
#define humano 2 
#define lado 3 
#define jugador1 'O' 
#define movimientocpu 'X'
//Movimientos de la computadora(CPU)//
struct movimiento{ /* Estructura que registra el movimiento*/
int fila,columna;
};
char Jugador = 'O', Oponente = 'X'; 
bool movimientosrestantes(char tabladejuego[3][3]){
    for (int fila = 0; fila < 3; fila++)
        for (int columna = 0; columna < 3; columna++)
            if (tabladejuego[fila][columna]="_")
                return true;
    return false;
}
//Viendo si hay un ganador ya sea de jugador 1 o de la cpu//
int evaluar(char tablallena[3][3]){ 
    for (int fila = 0;fila < 3;fila++){
     if (tablallena[fila][0] == tablallena[fila][1]&&tablallena[fila][1] == tablallena[fila][2]){
        if (tablallena[fila][0]=Jugador){
            return 1;
        }
        if 
     }
    }
}
