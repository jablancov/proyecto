#include <stdio.h>
#include "functions_and_structs.h"

int main() {

    const char *instructions_filename = "instrucciones.txt";
    cuad_func fx;
    cuad_func gx;

    print_instrucciones(instructions_filename);
    ask_func_params(&fx, &gx);

    fx.x = 1.5;
    gx.x = 2;

    printf("f(1.5) = %f.2", fx.y);
    return 0;
}