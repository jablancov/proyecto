/*Proyecto juego tictactoe sin interfaz en gtk*/
/*Desarollado por Carlos Nuñez c25586 y Jorge Blanco*/
#include <stdbool.h> /*Requerido para el bool*/ 
#include <stdio.h>  /*REquerido para el print*/
#include <stdlib.h>  /*Liberrias*/
#include <time.h>  /*Para sacar tiempos*/
/*Definicion de las macros*/
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
    /*VIendo si hay ganador por filas*/
    for (int fila = 0;fila < 3;fila++){
     if (tablallena[fila][0] == tablallena[fila][1]&&tablallena[fila][1] == tablallena[fila][2]){ /*Verifica que haya un ganador por fila si no no entra*/
        if (tablallena[fila][0]=Jugador){
            return 1; /*Si el que gana es la O esta funcion retorna 1*/
        }
        if (tablallena[fila][0]=Oponente){ /*Si el que gana es la X esta funcion retorna 2*/
            return 2;
        }
     }
    }
    if (tablallena[0][0]= tablallena[1][1]&& tablallena[2][2]){
        if (tablallena[0][0]=Jugador){
            return 1;
        }
        if (tablallena[0][0]=Oponente){
            return 2;
        }
    }
    if (tablallena[0][2]= tablallena[1][1]&& tablallena[2][0]){
        if (tablallena[0][2]=Jugador){/*Si el que gana es la O esta funcion retorna 1*/
            return 1;
        }
        if (tablallena[0][2]=Oponente){ /*Si el que gana es la O esta funcion retorna 2*/
            return 2;
        }
    }
    return 0; /*Retorna este si ninguno gana*/
}

/*La siguiente funcion saca las posibilidades que el juego puede tomar*/
int minimax(char tabladejuego[3][3], int profundidad, bool maximacantidadposibilidades){
int resultado = evaluar(tabladejuego); /*Saca el valor del resultado si jugador gana o el oponente gana*/
    if (resultado == 1){
        return resultado;
    }
    if (resultado == 2){
        return resultado;
    }
    if (movimientosrestantes(tabladejuego)==false)
    {
        return 0;
    }
    if (maximacantidadposibilidades){
        int maxima = 100;
        //Moverse por todas las celdas de la matriz//
        for (int celda = 0; celda <3;celda++){

        }
    }
    
}
