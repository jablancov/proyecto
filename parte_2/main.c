#include <stdio.h>
#include <stdlib.h>
#include "functions_and_structs.h"

int main() {

    const char *instructions_filename = "instrucciones.txt";
    const char *data_file = "functions_plot.dat";
    const char *script_gp = "plot_script.gp";
    char polt_command[30];
    cuad_func fx;
    cuad_func gx;
    interval set_1;

    print_instrucciones(instructions_filename);

    ask_func_params(&fx, &gx);

    generate_data(&fx, &gx, -100000, 100000, data_file);

    /*Preguntar por la diferencia maxima*/
    /*Calcular intervalo*/

    /*Plotear*/
    create_gnuplot_script(script_gp, data_file, &fx, &gx, set_1);
    sprintf(polt_command, "gnuplot %s", script_gp);
    system(polt_command);

    return 0;
}