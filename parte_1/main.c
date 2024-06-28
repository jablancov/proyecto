#include <gtk/gtk.h>

#define SIZE 3

typedef enum { EMPTY, X, O } player_mark; //La marca que deja cada jugador en la casilla

player_mark grid[SIZE][SIZE]; //Array de casillas
player_mark current_player = X; // Empieza el jugador con la X


GtkWidget *buttons[SIZE][SIZE];


/* Funcion que muestra el resultado de la partida creando un mensaje de dialogo. Recibe:
La ventana padre (la de la rejilla para jugar) para destruirse juntas
El mensaje a mostrar empantalla (Jugador X/O gana o empate)*/
void show_result(GtkWindow *parent, const char *result_messg) {

    GtkWidget *dialog;
    
    dialog = gtk_message_dialog_new(parent,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "%s", result_messg);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


/*Función para verificar si hay un ganador o empate. Si hay un resultado final (ganador o empate)
muestra una ventana de dialogo que indica al usuario y cierra el juego*/ 
void check_winner(GtkWindow *parent) {

    // Compruebar filas y columnas
    
    for (int i = 0; i < SIZE; i++) {

        // Checkeo de líneas horizontales
        // Si los botones que estan en fila tienen la misma player_mark y es distinta de vacio.
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != EMPTY) {

            char result_messg[20];
            sprintf(result_messg, "Jugador %c ganó", grid[i][0] == X ? 'X' : 'O');
            show_result(parent, result_messg);
            gtk_widget_destroy(GTK_WIDGET(parent));
            return;
        }
        // Checkeo de líneas verticales
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != EMPTY) {

            char result_messg[20];
            sprintf(result_messg, "Jugador %c ganó", grid[0][i] == X ? 'X' : 'O');
            show_result(parent, result_messg);
            gtk_widget_destroy(GTK_WIDGET(parent));
            return;
        }
    }
    
    // Checkeo de diagonales
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != EMPTY) {

        char result_messg[20];
        sprintf(result_messg, "Jugador %c ganó", grid[1][1] == X ? 'X' : 'O');
        show_result(parent, result_messg);
        gtk_widget_destroy(GTK_WIDGET(parent));
        return;
    }
    // Diagonal opuesta
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != EMPTY) {

        char result_messg[20];
        sprintf(result_messg, "Jugador %c ganó", grid[1][1] == X ? 'X' : 'O');
        show_result(parent, result_messg);
        gtk_widget_destroy(GTK_WIDGET(parent));
        return;
    }

    // Comprueba si hay empate
    int draw = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (grid[i][j] == EMPTY) {

                draw = 0;
                break;
            }
        }
    }
    
    if (draw) {  // Si empataron

        show_result(parent, "Empate");
        gtk_widget_destroy(GTK_WIDGET(parent));
    }
}



/* Funcion que realiza los cambios cuando el usuario da clic en un boton del juego
   Si el usuario hace click en una casilla que no esta ocupada no hace nada.
   Si la casilla esta ocupada pone la marca del usuario.
   Al final de la funcion cambia la marca del jugador
*/
void clicked_button(GtkButton *button, gpointer user_data) {
    int row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "row"));
    int col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "col"));

    // Verificar si la casilla está vacía
    if (grid[row][col] == EMPTY) {
        grid[row][col] = current_player;
        gtk_button_set_label(button, current_player == X ? "X" : "O");

        // Verificar si hay un ganador o empate después de cada movimiento
        check_winner(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))));

        // Alternar jugador
        current_player = (current_player == X) ? O : X;
    }
}




/* Le da la funcionalidad a la aplicacion
   Inicializa la aplicacion a partir del archivo creado con glade
   Inicializa todos los botones indicando su posicion, nombre,
   les pone una etiqueta vacia y los linkea a la funcion clicked_button
*/
void activate(GtkApplication *app, gpointer user_data) {

    // Obtener la rejilla y diseno de glade. Construye la ventana a partir de este
    GtkBuilder *builder = gtk_builder_new_from_file("parte_1/grid_template.glade"); 
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_builder_connect_signals(builder, NULL);

    // Inicializar botones
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            // Nombre de boton
            char button_name[12];
            snprintf(button_name, 12, "button_%d_%d", i, j);

            // 
            buttons[i][j] = GTK_WIDGET(gtk_builder_get_object(builder, button_name));
            g_object_set_data(G_OBJECT(buttons[i][j]), "row", GINT_TO_POINTER(i));
            g_object_set_data(G_OBJECT(buttons[i][j]), "col", GINT_TO_POINTER(j));

            // Darle funcionalidad al boton conectandolo a la funcion clicked button
            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(clicked_button), NULL);

            // Botones vacios al inicio
            gtk_button_set_label(GTK_BUTTON(buttons[i][j]), "");
            grid[i][j] = EMPTY;

        }
    }

    // Asignar aplicacion a la ventana y mostrarla al usuario
    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_widget_show_all(window);
    g_object_unref(builder);
}

/* Función principal
Crea la aplicacion y la configura acorde a activate

*/
int main(int argc, char **argv) {
    
    // Se crea la aplicacion
    GtkApplication *app = gtk_application_new("gtk.gato", G_APPLICATION_FLAGS_NONE);

    // Le da funcionalidad a la aplicacion
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Ejecuta la aplicacion y guarda su estatus.
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
