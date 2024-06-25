// STRUCTS


typedef struct interval
{
    float x_min;
    float x_max;
}interval;

typedef struct cuad_func
{
    float a;
    float b;
    float c;
    float x;
    float y;

}cuad_func;


// FUNCTIONS


float parabola(float a, float b, float c, float x);
int ask_func_params(cuad_func *fx, cuad_func *gx);
void calculate_y(cuad_func *func, float x);
void clean_buffer();
int generate_data(cuad_func fx, cuad_func gx, float x_min, float x_max);
void print_instrucciones(const char *filename);
