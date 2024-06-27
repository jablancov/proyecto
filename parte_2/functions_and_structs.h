e// STRUCTS

/* Struct para definir una region de interes para visualizar en la grafica
Funciona tambien para guardar los intervalos*/
typedef struct region2d
{
    float x_min;
    float x_max;
    float y_0;
    float y_1;
}region2d;

/* Struct para guardar los parametros de una funcion y calcular los puntos*/
typedef struct cuad_func
{
    float a;
    float b;
    float c;
    float x;
    float y;

}cuad_func;


// FUNCIONES

float parabola(float a, float b, float c, float x);
int ask_func_params(cuad_func *fx, cuad_func *gx, float *threshold_error);
void calculate_y(cuad_func *func, float x);
void clean_buffer();
int generate_data(cuad_func *fx, cuad_func *gx, float x_min, float x_max, region2d **region_list, float threshold_err, const char *filename);
void create_gnuplot_script(const char *script_name, const char *data_file, cuad_func *fx, cuad_func *gx, region2d **region_list);
void print_instrucciones(const char *filename);

