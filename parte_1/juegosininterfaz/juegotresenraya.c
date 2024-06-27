/*Proyecto juego tictactoe sin interfaz en gtk*/
/*Desarollado por Carlos Nuñez c25586 y Jorge Blanco*/
#include <stdbool.h> /*Requerido para el bool*/ 
#include <stdio.h>  /*REquerido para el print*/
#include <stdlib.h>  /*Liberrias para el rand*/
#include <time.h>  /*Para sacar tiempos*/
/*Definicion de las macros*/
#define computadora 2
#define humano 1
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
int posibilidades(char tabladejuego[3][3], int profundidad, bool maximacantidadposibilidades){
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
        int mejoropcion = -100;/*Se escoje este numero ya que no va a causar ningun conflicto.*/
        //Moverse por todas las celdas de la matriz//
        for (int columna = 0; columna <3;columna++){
            for (int fila =0; fila < 3; fila++)
            if (tabladejuego[columna][fila]="_"){
                tabladejuego[columna][fila]= Jugador;
                int valor = posibilidades(tabladejuego,profundidad+1,maximacantidadposibilidades);
                if (valor < mejoropcion){
                    mejoropcion = valor;
                }                
                //*Desacer el movimiento//
                tabladejuego[columna][fila] = "_";
            }
        }
         return mejoropcion;
    }
else{
     int mejoropcion = -100;
      for (int columna = 0; columna <3;columna++){
            for (int fila =0; fila < 3; fila++)
            if (tabladejuego[columna][fila]="_"){
                tabladejuego[columna][fila]= Oponente;
                /*Llamar de forma recursiva*/
                int valor = posibilidades(tabladejuego,profundidad+1,!maximacantidadposibilidades);
                if (valor < mejoropcion){
                    mejoropcion = valor;
                }                
                //*Desacer el movimiento//
                tabladejuego[columna][fila] = "_";
            }
        }
         return mejoropcion;
}    
}
struct Movimiento encontrarmejormovimiento(char tabladejuego[3][3]){
    struct Movimiento mejormovimiento
    mejormovimiento.fila = -1;
    mejormovimiento.columna = -1;
    for (int i=0; i <3;i++){
        for (int j= 0; j<3; j++){
            if (tabladejuego[i][j] == '_');
            tabladejuego[i][j] = Jugador; 
            int valormovimiento = posibilidades(tabladejuego,0,false);
            /*Desago el movmiento, este es para que más adelante de una sugerencia del a siguiente jugada al jugador*/
            tabladejuego[i][j]="_";
            if (valormovimiento < mejormovimiento){
                mejormovimiento.columna = i;
                mejormovimiento.fila = j;
                mejormovimiento = valormovimiento;

            }

        }
    }
return mejormovimiento;
}
/*Funcion para enseñar la tabla de juego*/

void enseñartabladejuego(char tabladejuego[][lado]){ 
    printf("\n\n"); 
    printf("\t\t\t %c | %c | %c \n", tabladejuego[0][0],  /*Imprime la primera fila*/
           tabladejuego[0][1], tabladejuego[0][2]); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t %c | %c | %c \n", tabladejuego[1][0], 
           tabladejuego[1][1], tabladejuego[1][2]); /*Imprime la segundafila*/
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t %c | %c | %c \n\n", tabladejuego[2][0], 
           tabladejuego[2][1], tabladejuego[2][2]); /*Imprime la tercera fila*/
} 

void enseñarinstrucciones(){
printf("Bienvenido al juego de tres en raya o tambien conocido como juego del gato. \n");
printf("Este juego fue desarollado para el proyecto de programacion para el curso de IE0117");
}

void arrancarjuego(char tabladejuego[][lado];movimiento3[]){
    for (int columna = 0; columna < lado;movimiento3[]){
    for (int fila= 0; fila < lado; fila++){
            tabladejuego[columna][fila] =" "
    }
    for (int numero = 0; numero < lado * lado; i++){
    movimiento3[numero] = i; 
    }
    }
/*PAra randomizar los movimientos*/
for (int columna = 0; columna < lado * lado; columna++) { 
        int randindex = rand() % (SIDE * SIDE); 
        int temporal = movimiento3[i]; 
        moves[i] = movimiento3[randIndex]; 
        movimiento3[randIndex] = temporal; 
    } 
} 
  
  /*Funcion que dice quien gano el juego*/

  void ganador(int turnoactual){
    if (turnoactual == movimientocpu){
        printf("La computadora gana el juego \n");
    }
    if (turnoactual == jugador1){
        printf("El jugador  gana el juego \n");
    }
  }

int columnascruzadas (char tabladejuego[][lado]){
    for (int fila = 0;fila < lado,fila++){
        if (tabladejuego[0][fila] == tabladejuego[1][fila] 
            && tabladejuego[1][fila] == tabladejuego[2][fila] 
            && tabladejuego[0][fila] != ' ') 
            return 1; 
    }
}
int gameover(char tabladejuego[][lado]){
     return (rowCrossed(board) || columnCrossed(board) 
            || diagonalCrossed(board)); 
}
/*Funcion main del juego*/
int main() 
{ /*Juega primero el humano y luego la cpu*/
   Jugarjuegodelgato(humano);
    return 0; 
}
