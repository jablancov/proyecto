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
struct movimiento encontrarmejormovimiento( char tabladejuego[3][3])
{
    struct movimiento mejormovimiento;
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

void ensenartabladejuego(char tabladejuego[][lado]){ 
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

void ensenarinstrucciones(){
printf("Bienvenido al juego de tres en raya o tambien conocido como juego del gato. \n");
printf("Este juego fue desarollado para el proyecto de programacion para el curso de IE0117");
}

void arrancarjuego(char tabladejuego[][lado];int movimiento3[];){
    srand(time(NULL)); 
    for (int columna = 0; columna < lado;movimiento3[]){
    for (int fila= 0; fila < lado; fila++){
            tabladejuego[columna][fila] =" "
    }
    for (int numero = 0; numero < lado * lado; numero++){
    movimiento3[numero] = i; 
    }
    }
/*PAra randomizar los movimientos*/
for (int columna = 0; columna < lado * lado; columna++) { 
        int randindex = rand() % (lado * ); 
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

int columnascruzadas(char tabladejuego[][lado]) { 
    for (int i = 0; i < lado; i++) { 
        if (tabladejuego[0][i] == tabladejuego[1][i] 
            && tabladejuego[1][i] == tabladejuego[2][i] 
            && tabladejuego[0][i] != ' ') 
            return 1; 
    } 
    return 0; 
} 
    }
}
int rowCrossed(char tabladejuego[][lado]) 
{ 
    for (int i = 0; i <lado; i++) { 
        if (tabladejuego[i][0] == board[i][1] 
            && tabladejuego[i][1] == tabladejuego[i][2] 
            && tabladejuego[i][0] != ' ') 
            return 1; 
    } 
    return 0; 
} 
int diagonalcruzadas(char tabladejuego[][lado]){
if ((tabladejuego[0][0] == tabladejuego[1][1] 
         && tabladejuego[1][1] == tabladejuego[2][2] 
         && tabladejuego[0][0] != ' ') 
        || (tabladejuego][2] == tabladejuego[1][1] 
            && tabladejuego[1][1] == tabladejuego[2][0] 
            && tabladejuego[0][2] != ' ')) 
        return 1; 
}
int gameover(char tabladejuego[][lado]){
     return (filascruzadas(tabladejuego) || columnascruzadas(tabladejuego) 
            || diagonalcruzadas(tabladejuego)); 
}
void Jugarjuegodelgato(int turno) 
{
    char tabladejuego[lado][lado]; 
    int movimientos[lado * lado]; 
    arrancarjuego(tabladejuego, turno);  
    ensenarinstrucciones(); 
  
    int movimiento4 = 0, x, y; 
  
    // Keep playing until the game is over or it is a draw 
    while (!gameOver(tabladejuego) && movimiento4 != lado * lado) { 
        if (turn == computadora) { 
            char tabladejuegotemporal[3][3]; 
            for (int i = 0; i < 3; i++) { 
                for (int j = 0; j < 3; j++) { 
                    if (tabladejuego[i][j] == 'X') { 
                        tabladejuegotemporal[i][j] = 'x'; 
                    } 
                    else if (tabladejuego[i][j] == 'O') { 
                        tabladejuegotemporal[i][j] = 'o'; 
                    } 
                    else { 
                        tabladejuegotemporal[i][j] = '_'; 
                    } 
                } 
            } 
            struct movimiento estemovimiento = encontrarmejormovimiento(tablatemporal); 
            x = estemovimiento.fila; 
            y = estemovimiento.columna; 
  
            tabladejuego[x][y] = movimientocpu; 
            printf("La computadora ha puesto  %c en la celda %d %d\n", 
                   movimientocpu, x, y); 
            showBoard(board); 
            movimiento3++; 
            turn = humano; 
        } 
        else if (turno == humano { 
            int movimiento5; 
            printf("Ingrese su movimiento: "); 
            scanf("%d", &movimiento5); 
            if (move < 1 || move > 9) { 
                printf("Entrada invalida favor ingresar un numero entre 1 y 9"); 
                continue; 
            } 
            x = (movimiento5 - 1) / lado; 
            y = (movimiento5 - 1) % lado; 
            if (tabladejuego[x][y] == ' ') { 
                tabladejuego[x][y] = jugador1; 
                showBoard(tabladejueego); 
                ind++; 
                if (gameOver(tabladejuego)) { 
                    declarar(humano); 
                    return; 
                } 
                turno = computadora; 
            } 
            else { 
                printf("La celda %d actualmente esta ocupada intente nuevamente.\n", 
                       movimiento5); 
            } 
        } 
    } 
  
    /*Si hay un empate*/
    if (!gameOver(tabladejuego) && movimiento4 == lado * lado) 
        printf("EL juego ha quedado en empate\n"); 
    else { 
        /*Verificando que usuario gano en caso de que no haya empate*/
        if (turno == computadora) 
            turno= humano; 
        else if (turno == humano) 
            turno = humano; 
  
        /*DEcir quien gano*/
        ganador(turno); 
    } 
} 
int main() 
{ /*Juega primero el humano y luego la cpu*/
   Jugarjuegodelgato(humano);
    return 0; 
}
