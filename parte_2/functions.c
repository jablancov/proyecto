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



int generate_data(cuad_func *fx, cuad_func *gx, float x_min, float x_max, const char *filename) {
    /*
    Recibe las funciones fx, gx y calcula los valores de x, y desde x_min hasta x_max

    */

    FILE *data_file = fopen(filename, "w");
    float step = 0.1;
    float x;

    if (data_file == NULL) {
        perror("Error al abrir/crear el archivo de datos para los puntos");
        return -1;
    }
    
    fprintf(data_file, "#x f(x) g(x)\n"); // Header del archivo, para saber el orden 

    x = x_min;
    while (x < x_max)
    {
        calculate_y(fx, x);
        calculate_y(gx, x);
        
        fprintf(data_file, "%.1f %.1f %.1f\n", x, fx->y, gx->y);

        x += step;
    }

    fclose(data_file);
    return 0;

}


void create_gnuplot_script(const char *script_name, const char *data_file, cuad_func *fx, cuad_func *gx, interval interval) {
    /* Crea el script para poder elaborar una grafica adecuada en gnuplot.*/

    //Variables
    FILE *script = fopen(script_name, "w");
    char fx_legend[30];
    char gx_legend[30];

    // Definir leyendas
    sprintf(fx_legend, "f(x) = %.1fx^2 + %.1fx + %.1f", fx->a, fx->b, fx->c);
    sprintf(gx_legend, "g(x) = %.1fx^2 + %.1fx + %.1f", gx->a, gx->b, gx->c);

    // Setup basico
    fprintf(script, "set xlabel 'x'\nset ylabel 'y'\nset xtics nomirror\nset ytics nomirror\n");

    // Plotear datos
    fprintf(script, "plot '%s' using 1:2 with lines title \"%s\", ", data_file, fx_legend);
    fprintf(script, "'%s' using 1:3 with lines title \"%s\"\n", data_file, gx_legend);

    // Hace una pausa indefinida para que la ventana con la grafica se mantenga hasta que se cierre manualmente
    fprintf(script, "pause -1");

    fclose(script);

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