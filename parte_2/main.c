//Creado por Jorge Blanco
/*
Este programa genera dos funciones cuadráticas a partir del input del usuario:
f(x)= ax^2 + bx + c.
g(x)= dx^2 + ex + h

Luego, el usuario tambien debe especificar un error porcentual entre ambas funciones E.
Se va a encontrar as regiones en las que la diferencia entre las funciones sea menor a E, es decir:

E > 100 * (f(x)-g(x))/(f(x))

Finalmente, en una grafica se va a mostrar las funciones f(x), g(x) y se van a enmarcar las regiones
cuya diferencia es menor a la especificada por el usuario.
El programa automaticamente hace un zoom a estas regiones.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions_and_structs.h"

int main() {

    const char *instructions_filename = "instrucciones.txt";
    const char *data_file = "functions_plot.dat";
    const char *script_gp = "plot_script.gp";
    char polt_command[30];
    float threshold_error;
    int err_args = 0;
    cuad_func fx;
    cuad_func gx;
    region2d *region_list[2];

    print_instrucciones(instructions_filename);

    do
    {
        err_args =  ask_func_params(&fx, &gx, &threshold_error);
        if (err_args != 0) {
            printf("Error al guardar los argumentos, vuelva a intentar\n");
        }
    } while (err_args != 0);
    
    

    for (int i = 0; i < 2; i++) {
        region_list[i] = malloc(sizeof(region2d));
        if (region_list[i] == NULL) {
            perror("Failed to allocate memory for region");
            return -1;
        }
        region_list[i]->x_min = 0.0;
        region_list[i]->x_max = 0.0;
        region_list[i]->y_0 = 0.0;
        region_list[i]->y_1 = 0.0;
    }


    generate_data(&fx, &gx, -100000, 100000, region_list, threshold_error, data_file);


    create_gnuplot_script(script_gp, data_file, &fx, &gx, region_list);

    printf("Intervalos\n");

    for (int i = 0; i < 2; i++) {
        printf("x_min: %.2f, x_max: %.2f, y_0: %.2f, y_1: %.2f\n", region_list[i]->x_min,region_list[i]->x_max,region_list[i]->y_0,region_list[i]->y_1);
        free(region_list[i]);
    }

    sprintf(polt_command, "gnuplot %s", script_gp); // Crear un comando para realizar la grafica
    system(polt_command); // Mostrar la grafica



    return 0;
}