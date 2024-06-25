#include <stdio.h>
#include "functions_and_structs.h"

float parabola(float a, float b, float c, float x) {
    /*
    Recibe los parametros para crear una funcion cuadratica, y retorna la imagen de esta para el valor de x dado.
    */
    return a*x*x+b*x+c;
}



int ask_func_params(cuad_func *fx, cuad_func *gx) {
    /*Pregunta al usuario por los parametros de dos funciones cuadraticas y el error entre ellas
    Guarda los parametros en los structs de dos funciones cuadraticas, f(x) y g(x)*/

    printf("Defina el valor de a (float): ");
    scanf("%f", &(fx->a));
    clean_buffer();

    printf("Defina el valor de b (float): ");
    scanf("%f", &(fx->b));
    clean_buffer();

    printf("Defina el valor de c (float): ");
    scanf("%f", &(fx->c));
    clean_buffer();

    printf("Ahora, para la función g(x):\n");

    printf("Defina el valor de d (float): ");
    scanf("%f", &(gx->a));
    clean_buffer();

    printf("Defina el valor de e (float): ");
    scanf("%f", &(gx->b));
    clean_buffer();

    printf("Defina el valor de h (float): ");
    scanf("%f", &(gx->c));
    clean_buffer();
    
    return 0;
}


void clean_buffer() {
    /*Esta funcion solo limpia el buffer del stdin para evitar bugs*/
    char ch;
    while (((ch = getchar()) != '\n') && ch != EOF);
}


void calculate_y(cuad_func *func, float x) {
    /*Calcula y almacena la preimagen y la imagen de la funcion
     */
    func->y = func->a * x * x + func->b * x + func->c;
}



int generate_data(cuad_func fx, cuad_func gx, float x_min, float x_max) {
/*
Por definir
*/
float x;
}



void print_instrucciones(const char *filename) {
    /* 
    Printea las instrucciones que estan escritas en otro archivo
    Recibe: un puntero constante que almacena el nombre del archivo.
    */

   FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error abriendo archivo de instrucciones.\n Asegurese que instrucciones.txt esta en el directorio");
        return;
    }

    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(file);

}