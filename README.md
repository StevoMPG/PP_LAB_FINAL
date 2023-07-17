# Arqueros en el Bosque

Este repositorio contiene el código fuente de un juego llamado "Arqueros en el Bosque" implementado en lenguaje C.

## Descripción del Juego

El juego se representa como una matriz. Aquí está un ejemplo de cómo podría verse un tablero del juego:




### Elementos del Juego:

- **J1 y J2**: Son las posiciones iniciales de cada jugador.
- **X**: Representa un árbol que se genera aleatoriamente en el tablero.

### Reglas del Juego:

1. El juego tiene 3 niveles: Fácil, Normal y Difícil. La dificultad influye en el tamaño del tablero y la cantidad de árboles:
   - Fácil: Tablero de 5x5 y 5 árboles.
   - Normal: Tablero de 7x7 y 7 árboles.
   - Difícil: Tablero de 9x9 y 9 árboles.
2. El juego se juega a 3 rondas; el que gane 2 de ellas, gana el juego.
3. En cada ronda, se generan los árboles y se debe elegir qué jugador inicia.
4. El juego finaliza si los árboles generados no permiten contacto entre los jugadores.
5. Un jugador puede elegir moverse o lanzar una flecha.
6. La flecha solo puede llegar 5 posiciones en forma vertical u horizontal.
7. La flecha no puede rebasar los árboles.
8. Si en el camino de la flecha, esta alcanza la posición de un jugador, es un punto para el jugador que lanzó la flecha.
9. El juego puede finalizar cuando cualquier jugador lo indique sin que haya puntaje para nadie.
10. Cuando un jugador haya hecho 2 puntos, gana y el juego finaliza. Se debe preguntar si se desea jugar de nuevo.


## Imagenes 

![image](https://github.com/StevoMPG/PP_LAB_FINAL/assets/84050547/284c67d8-773b-4369-8cb2-cb3542e155c7)



## Instalación

Para compilar y ejecutar este programa, simplemente descargue el repositorio y ejecute los siguientes comandos en su terminal:

```bash
gcc -o juego main.c
./juego

