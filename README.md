# Proyecto del curso Programación bajo Plataformas Abiertas (IE0117)

Este proyecto está dividido en dos partes

## Parte 1


### Requerimientos

El usuario debe tener instalado gcc, GTK-3 y glade. Que se puede realizar con los siguientes comandos en terminal

- sudo apt install gcc
- sudo apt-get install libgtk-3-dev
- sudo apt-get install glade

- El programa ocupa del archivos .glade presente en la carpeta parte1.

## Parte 2

Realizada por Jorge Blanco

Este programa genera dos funciones cuadráticas a partir del input del usuario:

$$f(x)= ax^2 + bx + c$$

$$g(x)= dx^2 + ex + h$$

Luego, el usuario tambien debe especificar un error porcentual entre ambas funciones E.
Se va a encontrar as regiones en las que la diferencia entre las funciones sea menor a E, es decir:

$$E \geq 100 * \frac{f(x)-g(x)}{f(x)}$$

Finalmente, en una grafica se va a mostrar las funciones f(x), g(x) y se van a enmarcar las regiones
cuya diferencia es menor a la especificada por el usuario.

El programa automaticamente hace un zoom a estas regiones.

### Requerimientos

El usuario debe tener instalado gcc y gnuplot. Que se puede realizar con los siguientes comandos en terminal

- sudo apt install gcc
- sudo apt install gnuplot
