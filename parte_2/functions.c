#include <stdio.h>
#include "functions_and_structs.h"
#include <math.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


/* Pregunta al usuario por los parametros de dos funciones cuadraticas y el error entre ellas
Guarda los parametros en los structs de dos funciones cuadraticas, f(x) y g(x)
Retorna la cantidad de errores (0 si todos los datos se guardaron adecuadamente)*/
int ask_func_params(cuad_func *fx, cuad_func *gx, float *threshold_error) {

    int err = 0;

    printf("Defina el valor de a (float): ");
    err += scanf("%f", &(fx->a)) - 1; 
    clean_buffer();

    printf("Defina el valor de b (float): ");
    err += scanf("%f", &(fx->c)) - 1;
    clean_buffer();

    printf("Defina el valor de c (float): ");
    err += scanf("%f", &(fx->c)) - 1;
    clean_buffer();

    printf("Ahora, para la función g(x):\n");

    printf("Defina el valor de d (float): ");
    err += scanf("%f", &(gx->a)) - 1;
    clean_buffer();

    printf("Defina el valor de e (float): ");
    err += scanf("%f", &(gx->b)) - 1;
    clean_buffer();

    printf("Defina el valor de h (float): ");
    err += scanf("%f", &(gx->c)) - 1;
    clean_buffer();

    printf("\nFinalmente, indique el porcentaje de error entre las funciones:\n");
    
    printf("Defina el valor del error porcentual maximo E (float): ");
    err += scanf("%f", threshold_error) - 1;
    clean_buffer();

    return err;
}

/*Esta funcion solo limpia el buffer del stdin para evitar bugs*/
void clean_buffer() {

    char ch;
    while (((ch = getchar()) != '\n') && ch != EOF); // Lee el stdin sin almacenar nada
}

/* Recibe un struct de funcion y calcula el valor de y.
Almacena la preimagen y la imagen de la funcion dentro del struct que recibe*/
void calculate_y(cuad_func *func, float x) {    

    func->y = func->a * x * x + func->b * x + func->c;
    func->y = round(func->y * 100) / 100;
}


/* A partir de fx, gx y calcula los puntos (x, y) desde x_min hasta x_max y los guarda en un archivo.
Tambien calcula las regiones donde la diferencia entre las funciones es menor al threshold.*/
int generate_data(cuad_func *fx, cuad_func *gx, float x_min, float x_max, region2d **region_list, float threshold_err, const char *filename) {

    FILE *data_file = fopen(filename, "w"); // Archivo para escribir los datos
    float step = 0.1;
    float x;
    float x_prev;
    float err_diff;
    int is_first_point = 1; // Indica si se va a agregar el primer punto al intervalo
    int region_index = 0; // Indica el numero de intervalo
    region2d *region = NULL;

    // Abrir archivo
    if (data_file == NULL) {
        perror("Error al abrir/crear el archivo de datos para los puntos");
        return -1;
    }
    
    fprintf(data_file, "#x f(x) g(x)\n"); // Header del archivo, para saber el orden, es un comentario

    x = x_min;

    // Empieza a calcular los puntos desde x_min a x_max
    while (x < x_max)
    {
        calculate_y(fx, x);
        calculate_y(gx, x);
        
        fprintf(data_file, "%.1f %.1f %.1f\n", x, fx->y, gx->y);

        // CALCULO DE DIFERENCIA Y COMPARACION CON ERROR
        
        // Calculo error. Evitar division por 0
        if (fx->y != 0) {

            err_diff = 100 * fabs(fx->y - gx->y) / fabs(fx->y);

        } else {

            err_diff = (gx->y == 0) ? 0 : 100;

        }


        // Comparacion error con threshold
        if (err_diff < threshold_err) {

            if (is_first_point) // Si es la primera vez que entra a un intervalo
            {
                printf("\nSe detecto un primer intervalo\n");
                region = region_list[region_index];
                region->x_min = x;
                region->y_0 = MIN(fx->y, gx->y);
                region->x_max = x;
                region->y_1 = MAX(fx->y, gx->y);
                is_first_point = 0; // El siguiente punto no es el primero del intervalo
            }
            else if (region->x_max == x_prev) // Si el punto pertenece al mismo intervalo
            {
                region->x_max = x;
                region->y_1 = MAX(fx->y, gx->y);
            }
            else if (region_index == 0) // Si hay mas de un intervalo
            {
                printf("\nSe detecto un segundo intervalo\n");
                region_index = 1;
                region = region_list[region_index]; // Se crea un nuevo intervalo
                region->x_min = x;
                region->y_0 = MIN(fx->y, gx->y);
                region->x_max = x;
                region->y_1 = MAX(fx->y, gx->y);
            }
            else 
            {
                printf("\nSe detecto mas de dos intervalos, solo se van a usar los primeros 2.\nSe detuvo la generacion de puntos\n");
                return -1;
            }
        }
        x_prev = x;
        x += step;
    }

    fclose(data_file);
    return 0;

}

/* Crea el script para poder elaborar una grafica adecuada en gnuplot. Recibe:
Nombre del script
El archivo de datos para graficarlo
struct de las funciones para escribir las leyendas
Los intervalos de interes para enmarcarlos y hacer Zoom
*/
void create_gnuplot_script(const char *script_name, const char *data_file, cuad_func *fx, cuad_func *gx, region2d **region_list) {

    //Variables
    FILE *script = fopen(script_name, "w");
    char fx_legend[50];
    char gx_legend[50];
    float plt_x0;
    float plt_x1;
    float plt_y0;
    float plt_y1;
    float int_range_x;
    float int_range_y;

    // Definir leyendas
    sprintf(fx_legend, "f(x) = %.1fx^2 + %.1fx + %.1f", fx->a, fx->b, fx->c);
    sprintf(gx_legend, "g(x) = %.1fx^2 + %.1fx + %.1f", gx->a, gx->b, gx->c);

    // Setup basico
    fprintf(script, "set xlabel 'x'\nset ylabel 'y'\nset xtics nomirror\nset ytics nomirror\n");

    // Plotear datos
    fprintf(script, "plot '%s' using 1:2 with lines title \"%s\", ", data_file, fx_legend);
    fprintf(script, "'%s' using 1:3 with lines title \"%s\"\n", data_file, gx_legend);

    // Dibujar un cuadro para los intervalos
    for (int i = 0; i < 2; i++) {
    if (region_list[i]->x_min != region_list[i]->x_max) {
        fprintf(script, "set object %d rect from %.2f,%.2f to %.2f,%.2f front fs empty lw 3\n", (i+1), region_list[i]->x_min, region_list[i]->y_0, region_list[i]->x_max, region_list[i]->y_1);
    }
    }

    // Creacion del zoom para ver mejor el intervalo

    if ((region_list[0]->x_min == region_list[0]->x_max) && (region_list[1]->x_min == region_list[1]->x_max)) // Si no hay ningun intervalo 
    {
        // No hace nada, se usa el intervalo por defecto.
    }
    else if (region_list[1]->x_min == region_list[1]->x_max) {  // Si solo hay un intervalo
    
        // Calcula el ancho del intervalo
        int_range_x = fabs(region_list[0]->x_max-region_list[0]->x_min);
        int_range_y = fabs(region_list[0]->y_1-region_list[0]->y_0);

        // Calcula los limites
        plt_x0 = region_list[0]->x_min - 1.5*int_range_x;
        plt_x1 = region_list[0]->x_max + 1.5*int_range_x;
        plt_y0 = MIN(region_list[0]->y_0, region_list[0]->y_1) - 1.5*int_range_y;
        plt_y1 = MAX(region_list[0]->y_0, region_list[0]->y_1) + 1.5*int_range_y;

        fprintf(script, "set xrange [%.2f:%.2f]\n", plt_x0, plt_x1);
        fprintf(script, "set yrange [%.2f:%.2f]\n", plt_y0, plt_y1);
    }
    else // Si hay dos intervalos, la misma idea, pero mas general.
    {
        float y0_max = MAX(region_list[0]->y_1,region_list[0]->y_0);
        float y0_min = MIN(region_list[0]->y_1,region_list[0]->y_0);
        float y1_max = MAX(region_list[1]->y_1,region_list[1]->y_0);
        float y1_min = MIN(region_list[1]->y_1,region_list[1]->y_0);

        int_range_x = fabs(region_list[1]->x_max-region_list[0]->x_min);
        int_range_y = fabs(MAX(y0_max, y1_max)-MIN(y0_min, y1_min));

        plt_x0 = region_list[0]->x_min - 0.5*int_range_x;
        plt_x1 = region_list[1]->x_max + 0.5*int_range_x;

        plt_y0 = MIN(y0_min, y1_min) - 0.5*int_range_y;
        plt_y1 = MAX(y0_max, y1_max) + 0.5*int_range_y;

        fprintf(script, "set xrange [%.2f:%.2f]\n", plt_x0, plt_x1);
        fprintf(script, "set yrange [%.2f:%.2f]\n", plt_y0, plt_y1);
    }


    // Se refresca la grafica y hace una pausa indefinida para que la ventana con la grafica se mantenga hasta que se cierre manualmente
    fprintf(script, "refresh\npause -1\n");

    fclose(script);

}

/* 
    Printea las instrucciones que estan escritas en otro archivo
    Recibe: un puntero constante que almacena el nombre del archivo.
    */
void print_instrucciones(const char *filename) {

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