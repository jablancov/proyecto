#include <stdio.h>
#include "functions_and_structs.h"

int main() {

    const char *instructions_filename = "instrucciones.txt";
    cuad_func fx;
    cuad_func gx;

    print_instrucciones(instructions_filename);
    ask_func_params(&fx, &gx);

    calculate_y(&fx, 1.5);
    calculate_y(&gx, 1.5);

    printf("f(1.5) = %.2f\n", fx.y);
    printf("g(1.5) = %.2f\n", gx.y);
    return 0;
}