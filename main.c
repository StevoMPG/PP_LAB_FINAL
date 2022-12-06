/// Profesor, comentarios que debo hacerle respecto al trabajo:

/// 1. Hay que leer las instrucciones del menu principal para jugarlo obligatoriamente, para que se entienda el funcionamiento del juego y los controles.

/// 2. Los disparos funcionan bien en la mayoria de los casos, avisando cuando el disparo se estrella con un arbol o cuando sale del mapa.
///    Pero e detectado que hay casos que el tiro da igual en el rival, por lo general pasa con los tiros hacia la izquierda o derecha. No pude encontrar el error en las funciones que realice.
///    Por lo que me gustaria que me comente cual es el error para mejorarlo, esto seguro que es algo sencillo lo cual no me estoy dando cuenta.

/// 3. Por ultimo, algo que no afecta el funcionamiento del juego, pero si molesta visualmente en la consola, es que cuando realizas una jugada te muestra el tablero 2 veces, una donde juega el turno el otro jugador y una vacia mostrando la ultima jugada.

/// Sin mas que decir espero que disfrute el juego. Saludos, Steven Pereira.


/// Librerias utilizadas en el juego.
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

/// Valores booleanos (valor de tipo binario verdadero o falso)
#define FALSE 0
#define TRUE  1

/// Valor maximo que puede alcanzar el tablero y el avance de la flecha
#define MAX_TABLERO   9
#define AVANCE_FLECHA 5

/// Niveles de juego 5x5, 7x7 y 9x9 respectivamente
char facil[]   = "Facil";
char normal[]  = "Normal";
char dificil[] = "Dificil";

/// Respuestas validas cuando vas a realizar un movimiento o un disparo
#define SALIR              'E'  // Salir del round
#define RENDIRSE           'R'  // Jugador se rinde del round

#define MOVER_ARRIBA       '8'  // Moverse hacia arriba
#define MOVER_DERECHA      '6'  // Moverse hacia derecha
#define MOVER_ABAJO        '2'  // Moverse hacia abajo
#define MOVER_IZQUIERDA    '4'  // Moverse hacia izquierda

#define DISPARAR_ARRIBA    'W'  // Disparar hacia arriba
#define DISPARAR_DERECHA   'D'  // Disparar hacia derecha
#define DISPARAR_ABAJO     'S'  // Disparar hacia abajo
#define DISPARAR_IZQUIERDA 'A'  // Disparar hacia izquierda

char tablero[MAX_TABLERO][MAX_TABLERO]; /// Matriz del tablero
char busqueda[MAX_TABLERO][MAX_TABLERO]; /// Matriz de busqueda

/// Variable para el nivel de juego
int nivelJuego = 5; // 5x5 Es el default

/// Variable para saber que jugador esta en que turno
int jugadorInicia = 1; // J1 inicia por default

/// Variables para la posicion de los jugadores
int renJ1; // Fila J1
int colJ1; // Columna J1
int renJ2; // Fila J2
int colJ2; // Columna J2

/// Toda las funciones que fueron creadas para utilizarse dentro la principal y la funcion que inicia el juego.
void fnTableroInicia();
void fnJugadoresInicia();
void fnMarcadoresInicia();
void fnJuegoInicia();
int  fnGeneraNumeroAleatorio();
int  fnHayArbol(int ren, int col);
int  fnHayJugador(int ren, int col);
int  fnPosicionLibre(int ren, int col);
void fnColocaArbol(int ren, int col);
void fnMueveJugador(int jugador,char movimiento);
void fnTableroDespliega();
void fnArbolesGenera();
int  fnVerificaContacto(int ren, int col);
void pausa(const char *mensaje);
void fnInstruccionesDeJuego();
char fnRetornaLetraColumna(int columna);
int  fnDispararArriba(int  renglon,int  columna);
int  fnDispararDerecha(int  renglon,int  columna);
int  fnDispararAbajo(int  renglon,int  columna);
int  fnDispararIzquierda(int  renglon,int  columna);
int  fnDispararFlecha(char direccion, int jugador);

void fnIniciarJuego(){ /// Función que inicia el juego

    int  enTurno;
    char ultimaJugada = ' ';
    int  roundJugandose = 1;
    int  renJugada;
    int  colJugada;
    int  puntosJ1;
    int  puntosJ2;

    enTurno = jugadorInicia; // Inicia el juego con el jugador seleccionado para iniciar

    char jugada; // Variable para jugada

    fnJuegoInicia(); // Inicia el juego

    puntosJ1 = 0; // Contador puntos con los que inicia el J1
    puntosJ2 = 0; // Contador puntos con los que inicia el J2

    while (puntosJ1 < 2 && puntosJ2 < 2){ /// Ciclo para controlar el Juego, mientras ninguno de los jugadores llegue a 2 ptos, sigue pasando lo de abajo

        fnTableroDespliega(); // Despliega el tablero

        printf("\nNivel de juego actual    : "); // Desplegando informacion básica en pantalla

        switch(nivelJuego){ /// Verifica y cambia el nivel de juego por el elegido

            case 5:printf("%s\n", facil);
                   break;
            case 7:printf("%s\n", normal);
                   break;
            case 9:printf("%s\n", dificil);
                   break;
        }
        // Imprime en pantalla los datos de la partida en cada turno
        printf("Se esta jugando el round : %d\n", roundJugandose);
        printf("Rounds ganados Jugador 1 : %d\n", puntosJ1);
        printf("Rounds ganados Jugador 2 : %d\n", puntosJ2);
        printf("Ultima jugada            : %c\n", ultimaJugada);
        printf("Posicion actual de J1    : %d,%c\n", renJ1+1, fnRetornaLetraColumna(colJ1 + 1));
        printf("Posicion actual de J2    : %d,%c\n", renJ2+1, fnRetornaLetraColumna(colJ2 + 1));

        // Solicitud de movimiento e imprime de quien es el turno del jugador
        printf("\nEste turno le pertenece al jugador: %d\n\n",enTurno);
        printf("INDIQUE ACCION: ");
        fflush(stdin); //Limpia buffer para no tomar valores viejos
        jugada = getchar();


        switch (jugada){
            case 'E': case 'e': // E para salir del round de 'Exit'

                     fnJuegoInicia(); // Se inicia el juego nuevamente

                     enTurno = jugadorInicia; // Se actualiza la variable enTurno

                     ultimaJugada = jugada; // Se actualiza la utlima jugada
                     break;

            case 'R': case 'r': // Rendirse en el round
                     if (enTurno == 1){ // Verifica si el jugador en turno es el 1

                        puntosJ2++; // Incrementa puntaje al J2 porque se rindio el J1

                        if (puntosJ2 == 2) // Verifica si el J2 ha ganado al llegar a 2 ptos


                           pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 2\n\n*******************************************************\n\n\n");
                        else // Si aun no llego a 2 ptos muestra en pantalla esto

                           pausa("\n\n\n*******************************************************\n\n              Se ha aumentado un punto al J2\n\n*******************************************************\n\n\n");
                     }
                     else{ // Si no es el jugador 1 en el turno va a ser el 2...

                        puntosJ1++; // Incrementa puntaje al J1 porque se rindio el J2

                        if (puntosJ1 == 2) // Verifica si el J1 ha ganado al llegar a 2 ptos

                           pausa("\n\n\n*******************************************************\n\n               HA GANADO EL JUGADOR 1\n\n*******************************************************\n\n\n");
                        else

                           pausa("\n\n\n*******************************************************\n\n              Se ha aumentado un punto al J1\n\n*******************************************************\n\n\n");
                     }

                     ultimaJugada=jugada; // Actualiza utlima jugada
                     break;

            case '8': // Moverse para arriba

                     if (enTurno==1){ // Verifica si el jugador en turno es el 1

                        renJugada = renJ1-1; // Le resta un renglon, en el caso de nuestro tablero sube un movimiento hacia arriba
                        colJugada = colJ1;
                     }else{ // Si no es el 1 es el 2...

                        renJugada = renJ2-1;
                        colJugada = colJ2;
                     }

                     if (renJugada < 0){ // Verifica que no salga del tablero, si sale del tablero da un error.

                        pausa ("**************************** ERROR ****************************\n\n       Ese movimiento hacia ARRIBA te lleva fuera del tablero.\n\n\n");
                     }else{

                        if (!fnPosicionLibre(renJugada,colJugada)){ //Si anteriormente no salio del tablero, verifica si hay un obstaculo, si lo hay tira error, sino...

                           pausa ("**************************** ERROR ****************************\n\n      Ese movimiento hacia ARRIBA te lleva a un obstaculo.\n\n\n");
                        }else{ // ... Si no hace esto

                           fnMueveJugador(enTurno,MOVER_ARRIBA); // Mueve al jugador que este jugando su turno hacia arriba

                           if (enTurno==1){ // Cambia de turno

                              enTurno=2;
                           }else{
                              enTurno=1;
                           }
                           ultimaJugada=jugada; // Actualiza ultima jugada
                         }
                     }
                     break;

            case '6':// Moverse para la derecha

                     if (enTurno==1){

                        colJugada=colJ1+1;
                        renJugada=renJ1;
                     }else{

                        colJugada=colJ2+1;
                        renJugada=renJ2;
                     }

                     if (colJugada == nivelJuego){

                        pausa ("**************************** ERROR ****************************\n\n       Ese movimiento hacia la DERECHA te lleva fuera del tablero.\n\n\n");
                     }else{

                        if (!fnPosicionLibre(renJugada,colJugada)){

                           pausa ("**************************** ERROR ****************************\n\n      Ese movimiento hacia la DERECHA te lleva a un obstaculo.\n\n\n");
                        }else{

                           fnMueveJugador(enTurno,MOVER_DERECHA);

                           if (enTurno==1){
                              enTurno=2;
                           }else{
                              enTurno=1;
                           }
                           ultimaJugada=jugada;
                        }
                     }
                     break;

            case '2': // Moverse hacia abajo

                     if (enTurno==1){

                        renJugada=renJ1+1;
                        colJugada=colJ1;
                     }else{

                        renJugada=renJ2+1;
                        colJugada=colJ2;
                     }

                     if (renJugada == nivelJuego){

                        pausa ("**************************** ERROR ****************************\n\n       Ese movimiento hacia ABAJO te lleva fuera del tablero.\n\n\n");
                     }else{

                        if (!fnPosicionLibre(renJugada,colJugada)){

                           pausa ("**************************** ERROR ****************************\n\n      Ese movimiento hacia ABAJO te lleva a un obstaculo.\n\n\n");
                        }else{

                           fnMueveJugador(enTurno,MOVER_ABAJO);

                           if (enTurno==1){
                              enTurno=2;
                           }else{
                              enTurno=1;
                           }
                           ultimaJugada=jugada;
                        }
                     }
                     break;

            case '4':// Moverse para la izquierda

                     if (enTurno==1){

                        colJugada=colJ1-1;
                        renJugada=renJ1;
                     }else{

                        colJugada=colJ2-1;
                        renJugada=renJ2;
                     }

                     if (colJugada < 0){

                        pausa ("**************************** ERROR ****************************\n\n       Ese movimiento hacia la IZQUIERDA te lleva fuera del tablero.\n\n\n");
                     }else{

                        if (!fnPosicionLibre(renJugada,colJugada)){

                           pausa ("**************************** ERROR ****************************\n\n      Ese movimiento hacia la IZQUIERDA te lleva a un obstaculo.\n\n\n");
                        }else{

                           fnMueveJugador(enTurno,MOVER_IZQUIERDA);

                           if (enTurno==1){
                              enTurno=2;
                           }else{
                              enTurno=1;
                           }
                           ultimaJugada=jugada;
                        }
                     }
                     break;

            case 'W':
            case 'w': // Disparar para arriba

                     if (fnDispararFlecha(DISPARAR_ARRIBA, enTurno)){  // Si dio en el jugador contrario
                        if (enTurno==1){

                           puntosJ1++; // Incrementa los puntos del jugador 1

                           if (puntosJ1==2){ // Verifica si ha ganado

                              pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 1\n\n*******************************************************\n\n\n"); // Mensaje de Ganar
                           }
                        }else{

                           puntosJ2++;// Incrementa los puntos del jugador 2

                           if (puntosJ2==2){ // Verifica si ha ganado

                              pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 2\n\n*******************************************************\n\n\n");// Mensaje de Ganar
                           }
                        }

                        fnJuegoInicia(); // Se inicia el Juego

                        ultimaJugada=' '; // Actualiza utlima jugada

                        roundJugandose++; // Se incrementa el Round

                        enTurno = jugadorInicia; // Se actualiza enTurno
                     }else{
                        if (enTurno==1){

                           enTurno=2;
                        }else{

                           enTurno=1;
                        }
                     }
                     break;

            case 'D':
            case 'd': // Disparar a la derecha

                     if (fnDispararFlecha(DISPARAR_DERECHA, enTurno)){
                        if (enTurno==1){

                           puntosJ1++;

                           if (puntosJ1==2){

                              pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 1\n\n*******************************************************\n\n\n");
                           }
                        }else{

                           puntosJ2++;

                           if (puntosJ2==2){

                              pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 2\n\n*******************************************************\n\n\n");
                           }
                        }

                        fnJuegoInicia(); // Se inicia el Juego

                        ultimaJugada=' '; // Actualiza utlima jugada

                        roundJugandose++; // Se incrementa el Round

                        enTurno = jugadorInicia; // Se actualiza enTurno
                     }else{
                        if (enTurno==1){

                           enTurno=2;
                        }else{

                           enTurno=1;
                        }
                     }
                     break;

            case 'S':
            case 's': // Disparar para abajo

                     if (fnDispararFlecha(DISPARAR_ABAJO, enTurno)){
                        if (enTurno==1){

                           puntosJ1++;

                           if (puntosJ1==2){

                              pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 1\n\n*******************************************************\n\n\n");
                           }
                        }else{

                           puntosJ2++;

                           if (puntosJ2==2){

                              pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 2\n\n*******************************************************\n\n\n");
                           }
                        }

                        fnJuegoInicia(); // Se inicia el Juego

                        ultimaJugada=' '; // Actualiza utlima jugada

                        roundJugandose++; // Se incrementa el Round

                        enTurno = jugadorInicia; // Se actualiza enTurno
                     }else{
                        if (enTurno==1){

                           enTurno=2;
                        }else{

                           enTurno=1;
                        }
                     }
                     break;

            case 'A':
            case 'a':// Disparar a la izquierda

                     if (fnDispararFlecha(DISPARAR_IZQUIERDA, enTurno)){
                        if (enTurno==1){

                           puntosJ1++;

                           if (puntosJ1==2){

                              pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 1\n\n*******************************************************\n\n\n");
                           }
                        }else{

                           puntosJ2++;

                           if (puntosJ2==2){

                              pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 2\n\n*******************************************************\n\n\n");
                           }
                        }

                        fnJuegoInicia(); // Se inicia el Juego

                        ultimaJugada=' '; // Actualiza utlima jugada

                        roundJugandose++; // Se incrementa el Round

                        enTurno = jugadorInicia; // Se actualiza enTurno
                     }else{
                        if (enTurno==1){

                           enTurno=2;
                        }else{

                           enTurno=1;
                        }
                     }
                     break;
        } // FIn del switch
    } // Fin del while
} // Fin del void FnIniciarJuego

int main(){ /// Función Principal

    char opcion=' '; // Para leer la opcion
    char nivel; // Para leer el nivel
    char usuario; //Para leer el usuario

    srand(time(NULL)); // Inicia la semilla para numeros aleatorios donde estos no se repitan nunca

    while (opcion !='0'){  /// Ciclo Principal del juego

        printf("\n\n");
        printf("-------------------------------------\n");
        printf("         ARQUEROS EN EL BOSQUE       \n\n");
        printf("           by Steven Pereira         \n"); // Menu Principal
        printf("-------------------------------------\n\n");
        printf("\n\n MENU PRINCIPAL \n\n");
        printf("1- Nivel de Juego (Activo: ");

        switch (nivelJuego){

            case 5:printf("%s)\n",facil);
                   break;
            case 7:printf("%s)\n",normal);
                   break;
            case 9:printf("%s)\n",dificil);
                   break;
        }
        printf("2- Quien inicia la partida (Activo: Jugador %d)\n", jugadorInicia);
        printf("3- Instrucciones de juego (IMPORTANTE LEER antes de iniciar)\n");
        printf("4- INICIAR PARTIDA \n");
        printf("0- SALIR\n");

        fflush(stdin); // Limpiar el buffer

        printf("\n\nElija una opcion para continuar y presione ENTER: ");
        opcion = getchar(); // Lee la opcion elegida, si llega a ser el 0, se termina el bucle del while

        if(getchar()=='\n'){

            switch (opcion){ // Evalua que opcion quiere el usuario

                case '0': // Sale del Juego
                        break;

                case '1':
                        printf("\n\nSeleccione nivel de juego (F)-Facil (N)-Normal (D)-Dificil y presione ENTER: ");

                        fflush(stdin);// Limpiar el Buffer

                        nivel = getchar(); // Lee si elegiste F o N o D o algun otro caracter

                        if(getchar()=='\n'){

                            switch (nivel){ // Evalua opcion

                                case 'F':
                                case 'f':// Asigna Nivel 5
                                        nivelJuego = 5;
                                        break;

                                case 'N':
                                case 'n':// Asigna Nivel 7
                                        nivelJuego = 7;
                                        break;

                                case 'D':
                                case 'd':// Asigna Nivel 9
                                        nivelJuego = 9;
                                        break;

                                default:pausa("Error en nivel elegido");
                                        break;
                            } //Fin del switch nivel
                        } //Fin del if si le das al enter
                        break;

                case '2':
                        printf("\n\nSeleccione que jugador inicia (1 o 2) y presione ENTER: ");

                        fflush(stdin); // Limpiar el Buffer

                        usuario = getchar(); // Lee si ingresaste 1 o 2 o algun otro caracter

                        if(getchar()=='\n'){

                            switch (usuario){ // Evalua opcion

                                case '1':// Asigna inicio al J1
                                    jugadorInicia = 1;
                                    break;

                                case '2':// Asigna inicio al J2
                                    jugadorInicia = 2;
                                    break;

                            default:pausa("Error en jugador elegido");
                                  break;
                            } //Fin del switch usuario
                        } //Fin del if si le das al enter
                        break;

                case '3':fnInstruccionesDeJuego();
                        break;

                case '4':fnIniciarJuego();
                        break;

                default:pausa("\n\n**************************** ERROR ****************************\n\n      Esa opcion no existe, porfavor intente nuevamente.\n\n");
                        break;
            } //fin del switch de que opcion quiere del menu el usuario
        } // Fin del if si le das al enter despues de elegir la opcion del usuario
    } // Fin del while
    printf("\n\n ===============================================================================\n");
    printf("\n\n                        HA SALIDO DE ARQUEROS EN EL BOSQUE                       \n"); // Mensaje final
    printf("\n ===============================================================================\n\n");
} // Fin de la funcion principal

void fnTableroInicia(){ // Funcion para iniciar el tablero

    for (int ren = 0; ren < nivelJuego; ren++){ // Ciclo para iniciar el Tablero
        for (int col = 0; col < nivelJuego; col++){

            tablero[ren][col] ='.'; // Inicia tablero de juego

            busqueda[ren][col]=' '; // Inicia tablero de busqueda
        }
    }
    printf("\n\n ===============================================================================\n");
    printf("\n\n                El Tablero esta siendo desplegado, PREPARENSE! \n\n"); // Mensaje en pantalla
}

void fnJugadoresInicia(){ // Funcion para posicionar a los jugadores

    // Coloca los jugadores en su posición inicial
    renJ1 = nivelJuego-1;
    colJ1 = 0;
    renJ2 = 0;
    colJ2 = nivelJuego-1;

    // Coloca los jugadores en tablero
    tablero[renJ1][colJ1]='1';
    tablero[renJ2][colJ2]='2';
}

void fnJuegoInicia(){

    fnTableroInicia(); // Inicia tablero

    fnJugadoresInicia(); // Inicia jugadores

    fnArbolesGenera(); // Genera los Arboles
}

int fnGeneraNumeroAleatorio(){ // Genera un numero aleatorio

    int resultado; // Variable de resultado

    resultado = rand() % nivelJuego; // Genera el numero aleatorio dependiendo del nivel de juego

    return resultado; // Devuelve el Numero
}

int fnHayArbol(int ren, int col){ // Funcion que verifica si hay un arbol en la posición

    if (tablero[ren][col]=='X') // Verifica si hay arbol buscando el caracter X, si lo hay devuelve el valor booleano (TRUE) indicando que si hay
       return TRUE;
    else // Si no hay devuelve 0 (FALSE)
       return FALSE;
}

int fnPosicionLibre(int ren, int col){ // Funcion que verifica si el camino eta libre de arboles

    if (tablero[ren][col]=='.') // Verifica si esta libre buscando los puntos, si lo hay devuelve el valor booleano (TRUE) indicando que si hay
       return TRUE;
    else // Si no hay devuelve 0 (FALSE)
       return FALSE;
}

int fnHayJugador(int ren, int col){ // Funcion que verifica si hay un jugador

    if (tablero[ren][col] == '1' || tablero[ren][col] == '2') // Verifica si en esa fila y columna esta el jugador 1 o el jugador 2 comprobando el caracter
       return TRUE;
    else
       return FALSE;
}

void fnColocaArbol(int ren, int col){ // Funcion que coloca un arbol en la posición

    tablero[ren][col]='X'; // Coloca un Arbol (X)
}

void fnMueveJugador(int jugador, char movimiento){ // Función que mueve el Jugador

    if (jugador == 1){ // Verifica si es el jugador 1

       tablero[renJ1][colJ1]='.'; // Quita al jugador 1 de su posicion actual

       switch(movimiento){ // Verifica hacia donde mover segun lo que el jugador elige

            case MOVER_ARRIBA:

                 renJ1--; // Decrementa un renglon (fila)
                 break;
            case MOVER_DERECHA:

                 colJ1++; // Incrementa la columna
                 break;
            case MOVER_ABAJO:

                 renJ1++; // Incrementa el renglon (fila)
                 break;
            case MOVER_IZQUIERDA:

                 colJ1--; // Decrementa la columna
                 break;
       }
       tablero[renJ1][colJ1]='1'; // Coloca al Jugador en la nueva posición
    }else{

       tablero[renJ2][colJ2]='.'; // Quita al jugador 2 de su posicion actual

       switch(movimiento){ // Verifica hacia donde mover segun lo que el jugador elige

            case MOVER_ARRIBA:

                 renJ2--;
                 break;
            case MOVER_DERECHA:

                 colJ2++;
                 break;
            case MOVER_ABAJO:

                 renJ2++;
                 break;
            case MOVER_IZQUIERDA:

                 colJ2--;
                 break;
       }
       tablero[renJ2][colJ2]='2';
    } // FIn del else que continuaba el anterior if
} // FIn de la funcion

void fnTableroDespliega(){ // Funciòn para desplegar el tablero en pantalla

    printf("\n\n *******************************************************************************\n");
    printf("\n                                TABLERO DE JUEGO \n"); // Mensaje del tabler
    printf("\n *******************************************************************************\n\n");

    if (nivelJuego == 5){ // Imprime los encabezados del tablero para el nivel de 5x5

       printf("   A B C D E  \n");
       printf("   ---------- \n");
    }else if (nivelJuego==7){ // Imprime los encabezados del tablero para el nivel de 7x7

       printf("   A B C D E F G  \n");
       printf("   -------------- \n");
    }else{ // Imprime los encabezados del tablero para el nivel de 9x9

       printf("   A B C D E F G H I  \n");
       printf("   ------------------ \n");
    }

    for (int ren=0; ren < nivelJuego; ren++){ // Ciclo

        printf("%d |",ren+1); // Imprime la fila

        for (int col=0; col < nivelJuego; col++){

            printf("%c ",tablero[ren][col]); //Imprime los elementos que contiene el tablero por columna
        }
        printf("|\n"); // Cambia de Linea despues que cierra una columna
    }
    // Imprime los encabezados
    if (nivelJuego==5)
       printf("   ---------- \n");
    else
    if (nivelJuego==7)
       printf("   -------------- \n");
    else
       printf("   ------------------ \n");
} // Fin de la funcion

void fnArbolesGenera(){ // Función que genera los arboles

    int arbolesGenerados=0; // Contador de arboles que se han ido generaando
    int renglon;
    int columna;

    while (arbolesGenerados<nivelJuego){ // Inicio un ciclo while donde se generan los arboles hata alcanzar el nivel de juego

        renglon = fnGeneraNumeroAleatorio(); // Genera una fila aleatoria con la funcion fnGeneraNumeroAleatorio
        columna = fnGeneraNumeroAleatorio(); // Genera una columna aleatoria con la funcion fnGeneraNumeroAleatorio

        if (fnPosicionLibre(renglon,columna)){ // Verifica si esa posicion esta libre utilizando la funcion, si esta libre coloca un arbol

            fnColocaArbol(renglon,columna); // Coloca arbol en la posicion con la funcion de colocar arbol

            arbolesGenerados++; // Incrementa el contador de arboles generados para que complete los necesarios para el nivel, y se cierre el while
        } // Fin del if
    } // Fin del while

    printf("                   ***  ARBOLES CARGADOS CORRECTAMENTE ***\n\n"); // Mensaje en pantalla (Este mensaje no es necesario, pero le da mas 'vida' al juego jaja espero le guste profe)
}

void pausa(const char *mensaje){ // Funcion para poner un mensaje y pausar

    printf("%s\n",mensaje); // Despliega el Mensaje
    printf("\n\nPresione ENTER para continuar");

    fflush(stdin);  // Libera el Buffer para que no se almacenen msjes

    getchar(); // Espera a que presione enter
    printf("\n");
}

void fnInstruccionesDeJuego(){ // Funcion que imprime las instrucciones y teclas de juego, es lo que voy a desplegar en la opcion 3 del menu principal

    printf("\n\n ===============================================================================\n");
    printf("\n                          *** INSTRUCCIONES DE JUEGO ***\n");
    printf("\n ===============================================================================\n\n");
    printf("         El juego consiste en intentar matar a tu rival de un flechazo\n");
    printf("         las  flechas  no  atraviesan  arboles y  tampoco  llegan a una\n");
    printf("         distancia que sea superior a 5 metros (casillas del tablero). \n");
    printf("         Asi que le recomendamos acercarse al enemigo para disparar.\n");
    printf("         No intente disparar si no tiene al otro jugador a tiro!!! \n\n");
    printf("\n\n       *** Piensa bien tus movimientos y no quedes a tiro de tu rival ***\n\n");
    printf("          El jugador que consiga ganar 2 rounds, ganara la partida...\n");
    printf("\n          En el MENU PRINCIPAL podras elegir dificultad y quien empieza.\n");
    printf("\n -------------------------------------------------------------------------------\n\n");
    printf("                              *** IMPORTANTE ***\n\n");
    printf("          Si se te genera un bosque donde los arboles no permitan el paso,\n");
    printf("          donde dice INDIQUE ACCION debes de darle a E y ENTER para salir\n");
    printf("          del mapa actual y que se vuelva a generar uno nuevo sin rendirte.\n");
    printf("\n\n          Si ingresas un movimiento fuera del tablero o hacia un arbol");
    printf("\n          se te avisara de que hay un error y deberas ingresar ");
    printf("\n          nuevamente el movimiento.\n");
    printf("\n -------------------------------------------------------------------------------\n\n");

    printf("                            *** TECLAS DE JUEGO ***\n\n");
    printf("E - SALIR DEL ROUND\n");
    printf("R - RENDIRSE\n");
    printf("8 - MOVER_ARRIBA\n");
    printf("6 - MOVER_DERECHA\n");
    printf("2 - MOVER_ABAJO\n");
    printf("4 - MOVER_IZQUIERDA\n");
    printf("W - DISPARAR_ARRIBA\n");
    printf("D - DISPARAR_DERECHA\n");
    printf("S - DISPARAR_ABAJO\n");
    printf("A - DISPARAR_IZQUIERDA\n");
    printf("\n -------------------------------------------------------------------------------\n\n");
    pausa("");
}

char fnRetornaLetraColumna(int columna){ // Funcion que retorna la letra de la Columna en la que se esta

   char resultado=' '; // Variable de Resultado

   switch (columna){

      case 1:resultado ='A';
             break;
      case 2:resultado ='B';
             break;
      case 3:resultado ='C';
             break;
      case 4:resultado ='D';
             break;
      case 5:resultado ='E';
             break;
      case 6:resultado ='F';
             break;
      case 7:resultado ='G';
             break;
      case 8:resultado ='H';
             break;
      case 9:resultado ='I';
             break;
   }
   return resultado;
}

int fnDispararArriba(int renglon, int  columna){ // función para disparar flecha hacia arriba

    int resultado = TRUE; // Resultado

    int flechaSalioDelTablero = FALSE; // No salio del tablero

    int avanceFlecha = 0; // Contador avance de la flecha

    while (avanceFlecha < AVANCE_FLECHA){ // Ciclo para buscar hacia arriba siendo definido AVANCE_FLECHA como 5

        avanceFlecha++; // Incrementa el Avance de la Flecha

        renglon--; // Decremanta el renglon

        if (renglon < 0){ // Verifica que no haya salido del tablero

           flechaSalioDelTablero = TRUE; // Salio del Tablero

           resultado = FALSE; // Cambia el Resultado

           break; // Sale del Ciclo
        }

        if (fnHayArbol(renglon,columna)){ // Verifica si hay un árbol

           resultado = FALSE; // Cambia el Resultado

           pausa("\n****************************** UPS!!! ******************************\n\n            La Flecha se ha impactado con un arbol\n\n********************************************************************\n\n\n"); // Mensaje

           break; // Sale
        }else if (fnHayJugador(renglon,columna)){
            break;
        }
    }

    if (resultado){// Verifica si ha alcanzado oponente
       pausa("\n****************************** EXITO!!! ******************************\n\n              La Flecha ha herido al oponente\n\n**********************************************************************\n\n\n");

    }else if (flechaSalioDelTablero){ // Verifica si la flecha sale del tablero
       pausa("\n**********************************************************************\n\n              La Flecha salio del Tablero sin encontrar oponente\n\n**********************************************************************\n\n\n");

    }else if (avanceFlecha == AVANCE_FLECHA){ // Verifica el avance de la flecha
       pausa("\n**********************************************************************                  La Flecha alcanzo su distancia sin encontrar oponente\n\n**********************************************************************\n\n\n");

    }
    return resultado;  // Devuelve el resultado
}

int fnDispararDerecha(int  renglon,int  columna){ // función dispara flecha hacia Derecha

    int resultado = TRUE;

    int flechaSalioDelTablero = FALSE;

    int avanceFlecha = 0;

    while (avanceFlecha < AVANCE_FLECHA){

        avanceFlecha++;

        columna++;

        if (renglon == nivelJuego){

           flechaSalioDelTablero = TRUE;

           resultado = FALSE;

           break;
        }

        if (fnHayArbol(renglon,columna)){

            resultado = FALSE;

            pausa("\n****************************** UPS!!! ******************************\n\n            La Flecha se ha impactado con un arbol\n\n********************************************************************\n\n\n"); // Mensaje

           break;
        } else if (fnHayJugador(renglon,columna)){
            // Sale
            break;
        }
    }

    if (resultado){
       pausa("\n****************************** EXITO!!! ******************************\n\n              La Flecha ha herido al oponente\n\n**********************************************************************\n\n\n");

    }else if (flechaSalioDelTablero){
       pausa("\n**********************************************************************\n\n              La Flecha salio del Tablero sin encontrar oponente\n\n**********************************************************************\n\n\n");

    }else if (avanceFlecha == AVANCE_FLECHA){
       pausa("\n**********************************************************************                  La Flecha alcanzo su distancia sin encontrar oponente\n\n**********************************************************************\n\n\n");

    }
    return resultado;
}

int fnDispararAbajo(int  renglon, int  columna){ // función para disparar flecha abajo

    int resultado = TRUE;

    int flechaSalioDelTablero = FALSE;

    int avanceFlecha = 0;

    while (avanceFlecha < AVANCE_FLECHA){

        avanceFlecha++;

        renglon++;

        if (renglon == nivelJuego){

           flechaSalioDelTablero = TRUE;

           resultado = FALSE;

           break;
        }

        if (fnHayArbol(renglon,columna)){

           resultado = FALSE;

           pausa("\n****************************** UPS!!! ******************************\n\n            La Flecha se ha impactado con un arbol\n\n********************************************************************\n\n\n"); // Mensaje

           break;
        }
        else if (fnHayJugador(renglon,columna)){
            break;
        }
    }

    if (resultado){
       pausa("\n****************************** EXITO!!! ******************************\n\n              La Flecha ha herido al oponente\n\n**********************************************************************\n\n\n");

    }else if (flechaSalioDelTablero){
       pausa("\n**********************************************************************\n\n              La Flecha salio del Tablero sin encontrar oponente\n\n**********************************************************************\n\n\n");

    }else if (avanceFlecha == AVANCE_FLECHA){
       pausa("\n**********************************************************************                  La Flecha alcanzo su distancia sin encontrar oponente\n\n**********************************************************************\n\n\n");

    }
    return resultado;
}

int fnDispararIzquierda(int  renglon,int  columna){ // función dispara flecha hacia Izquierda

    int resultado = TRUE;

    int flechaSalioDelTablero = FALSE;

    int avanceFlecha = 0;

    while (avanceFlecha < AVANCE_FLECHA){

        avanceFlecha++;

        columna--;

        if (renglon == nivelJuego){

           flechaSalioDelTablero = TRUE;

           resultado = FALSE;

           break;
        }

        if (fnHayArbol(renglon,columna)){

           resultado = FALSE;

           pausa("\n****************************** UPS!!! ******************************\n\n            La Flecha se ha impactado con un arbol\n\n********************************************************************\n\n\n"); // Mensaje

           break;
        }else if (fnHayJugador(renglon,columna)){

            break;
        }
    }

    if (resultado){
       pausa("\n****************************** EXITO!!! ******************************\n\n              La Flecha ha herido al oponente\n\n**********************************************************************\n\n\n");

    }else if (flechaSalioDelTablero){
       pausa("\n**********************************************************************\n\n              La Flecha salio del Tablero sin encontrar oponente\n\n**********************************************************************\n\n\n");

    }else if (avanceFlecha == AVANCE_FLECHA){
       pausa("\n**********************************************************************                  La Flecha alcanzo su distancia sin encontrar oponente\n\n**********************************************************************\n\n\n");

    }
    return resultado;
}

int fnDispararFlecha(char direccion, int jugador){ // Funcion para Disparar Flecha

    int resultado = FALSE;  // Variable de Resultado
    // Posición Inicial del Disparo
    int renDisparo;
    int colDisparo;

    if (jugador==1){
       // Obtiene la posición inicial del disparo del J1
       renDisparo = renJ1;
       colDisparo = colJ1;
    }else{
      // Obtiene la posición inicial del disparo del J2
      renDisparo = renJ2;
      colDisparo = colJ2;
    }

   switch (direccion){ //Evalua en que direccion

         case DISPARAR_ARRIBA:

                if (fnDispararArriba(renDisparo,colDisparo)){ // Verifica disparo

                    resultado = TRUE; // Resultado
                }
                break;

         case DISPARAR_DERECHA:

                if (fnDispararDerecha(renDisparo,colDisparo)){

                    resultado = TRUE;
                }
                break;

         case DISPARAR_ABAJO:

                if (fnDispararAbajo(renDisparo,colDisparo)){

                    resultado = TRUE;
                }
                break;

         case DISPARAR_IZQUIERDA:

                if (fnDispararIzquierda(renDisparo,colDisparo)){

                    resultado = TRUE;
                }
                break;
    }
    return resultado;
}
