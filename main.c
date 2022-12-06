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


/// Constantes
#define MAX_LON_CADENAS    50  // Maxima longitud para las cadenas en general
#define MAX_NUM_JUGADORES  10  // Maximo numero de jugadores
#define MAX_NUM_PARTIDAS   10  // MAximo numero de partidas


// Estructura del Jugador
struct Jugador{

    char  alias[MAX_LON_CADENAS];     // Alias
    char  ci[MAX_LON_CADENAS];        // CI
    char  nombre[MAX_LON_CADENAS];    // Nombre
    char  apellido[MAX_LON_CADENAS];  // Apellido
    char  fecNac[11];                 // Fecha de Nacimiento
    int  activo;                     // Si esta activo o no
};

struct Jugador arrJugadores[MAX_NUM_JUGADORES]; // Defino el arreglo de los jugadores maximo

int gJugadoresActivos = -1; // Variable para controlar jugadores activos

// Estructura de la Partida
struct Partida{

    char  fecha[11];                 // Fecha de Partida
    char  jug_1[MAX_LON_CADENAS];    // Alias Jugador 1
    char  jug_2[MAX_LON_CADENAS];    // Alias Jugador 2
    int   ptsJug1;                   // Puntos Jugador 1
    int   ptsJug2;                   // Puntos Jugador 2
};

struct Partida arrPartidas[MAX_NUM_PARTIDAS]; // Defino el arreglo de las Partidas

int gPartidasActivas = -1; // Variable para controlar partidas activas


// Prototipo de Funciones para la segunda parte
int  fnMenuPrincipal();
void fnGestionarJugadores();
void fnConsultas();
int fnEsFecha(char* cadena);
int fnCIValido(char* ci);
int fnJugadorExiste(char *alias);
void fnJugadoresListar();
void fnJugadorAlta();
void fnJugadorBaja();
void fnJugadorCambio();

void fnJugar();
void fnPartidasListar();
void fnPartidasPorJugadorListar(const char *jugador);
void fnPartidasPorFechaListar(const char *fecha);
void fnSeleccionarPartidaDatos();

// Funciones de apoyo para parte segunda parte lab

int LongCad();
int CompCad();

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
void fnIniciarJuego();

/// Función Principal
int main(){

   int opcion=-1; // Variable para la opcion


   while (opcion!=0){ // Ciclo para controlar el Menu Principal

      opcion = fnMenuPrincipal(); // Muestra el Menu Principal

      // Verifica opcion seleccionada
      switch(opcion){

         case 1:fnGestionarJugadores();
                break;

         case 2:fnConsultas();
                break;

         case 3:fnInstruccionesDeJuego();
                break;

         case 4:fnJugar();
                break;
      }
   }
    printf("\n\n ===============================================================================\n");
    printf("\n\n                        HA SALIDO DE ARQUEROS EN EL BOSQUE                       \n"); // Mensaje final
    printf("\n ===============================================================================\n\n");
   return 0;
}

// Función para jugar
void fnJugar(){
    char opcion=' '; // Para leer la opcion
    char nivel;      // Para leer el nivel
    char usuario;    //Para leer el usuario

    // Random
    srand(time(NULL)); // Inicia la semilla para numeros aleatorios donde estos no se repitan nunca

    while (opcion !='0'){  /// Ciclo Principal del juego

        printf("\n\n");
        printf("-------------------------------------\n");
        printf("\n             MENU JUGAR          \n\n");
        printf("-------------------------------------\n\n");
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

        printf("\nElija una opcion para continuar y presione ENTER: ");
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

                case '4':// Verifica que todavia haua partidas
                         if (gPartidasActivas< MAX_NUM_PARTIDAS-2){

                             fnSeleccionarPartidaDatos();
                             fnIniciarJuego();
                         }
                         else
                            pausa("\nYa has agotado el registro de partidas.\n\n");
                         break;

                default:pausa("\n\n**************************** ERROR ****************************\n\n      Esa opcion no existe, porfavor intente nuevamente.\n\n");
                        break;
            } //fin del switch de que opcion quiere del menu el usuario
         } //fin del if
    } // Fin del while
} // Fin de la funcion principal


void fnSeleccionarPartidaDatos(){ // Función para Seleccionar Datos de la Partida

   gPartidasActivas++; // Incrementa el Contador de Partidas

   printf("\n\nEsta es la partida numero %d que se va a jugar\n",gPartidasActivas+1); // Mensaje de partidas registradas

   printf("\nAhora toca seleccionar los datos de la partida, preparense!\n\n"); // Mensaje

   while (TRUE){ // Ciclo para controlar la fecha

      printf("Ingrese la fecha en la que se esta jugando la partida (dd/mm/yyyy): "); // Solicita la Fecha
      fflush(stdin);
      scanf("%s",arrPartidas[gPartidasActivas].fecha);

      if (!fnEsFecha(arrPartidas[gPartidasActivas].fecha)){ // Verifica que sea fecha valida
         pausa("\n\n ********* La fecha indicada no es correcta. *********\n");
      }else{
         // Sale del Ciclo
         break;
      }
   }

   while (TRUE){ // Ciclo para controlar el jugador 1

      printf("\nIngrese el alias previamente registrado que va a usar el jugador 1: "); // Solicita el Alias del Jugador 1
      fflush(stdin);
      scanf("%s",arrPartidas[gPartidasActivas].jug_1);


      if (!fnJugadorExiste(arrPartidas[gPartidasActivas].jug_1)){

         pausa("\n\n***** El alias indicado no existe, fijese en las mayusculas y minusculas, intente de nuevo *****\n\n");
      }else{ // Sale del Ciclo

         break;
      }
   }


   while (TRUE){ // Ciclo para controlar el jugador 2

      printf("\nIngrese el alias previamente registrado que va a usar el jugador 2: "); // Solicita el Alias del Jugador 2
      fflush(stdin);
      scanf("%s",arrPartidas[gPartidasActivas].jug_2);


      if (CompCad(arrPartidas[gPartidasActivas].jug_1,arrPartidas[gPartidasActivas].jug_2)!=0){ // Verifica que sea distinto que el primero

         if (!fnJugadorExiste(arrPartidas[gPartidasActivas].jug_2)){

            pausa("\n\n***** El alias indicado no existe, fijese en las mayusculas y minusculas, intente de nuevo *****\n\n");
         }else{
            // Sale del Ciclo
            break;
         }
      }else
         pausa("\n\n*** No puedes usar el alias que esta usando el jugador 1, intente de nuevo ***\n\n");
   }

   printf("\n\n");
   printf("====== %s vs ",arrPartidas[gPartidasActivas].jug_1);
   printf("%s======\n",arrPartidas[gPartidasActivas].jug_2);
   pausa("\n\n====== La partida esta definida! A GUERREAR! ======\n\n");
}

void fnIniciarJuego(){

    int  enTurno;
    char ultimaJugada = ' ';
    int  roundJugandose = 1;
    int  renJugada;
    int  colJugada;

    enTurno = jugadorInicia; // Inicia el juego con el jugador seleccionado para iniciar

    char jugada; // Variable para jugada

    fnJuegoInicia(); // Inicia el juego

    arrPartidas[gPartidasActivas].ptsJug1 = 0; // Contador puntos con los que inicia el J1
    arrPartidas[gPartidasActivas].ptsJug2 = 0; // Contador puntos con los que inicia el J2

    while (arrPartidas[gPartidasActivas].ptsJug1 < 2 && arrPartidas[gPartidasActivas].ptsJug2 < 2) { /// Ciclo para controlar el Juego, mientras ninguno de los jugadores llegue a 2 ptos, sigue pasando lo de abajo

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
        printf("\nSe esta jugando el round : %d\n", roundJugandose);
        printf("Rounds ganados Jugador 1 : %d\n", arrPartidas[gPartidasActivas].ptsJug1);
        printf("Rounds ganados Jugador 2 : %d\n", arrPartidas[gPartidasActivas].ptsJug2);
        printf("\nUltima jugada            : %c\n", ultimaJugada);
        printf("\nPosicion actual de J1    : %d,%c\n", renJ1+1, fnRetornaLetraColumna(colJ1 + 1));
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

            case 'R': case 'r': // Rendirse en el JUEGO
                     if (enTurno == 1)
                     {
                        // Mensajes
                        printf("\n\n\n====== El jugador 1 *** [%s] *** se ha rendido!!! INCREIBLE!!!======\n\n",arrPartidas[gPartidasActivas].jug_1);
                        printf("\n====== El jugador 2 *** [%s] *** es el vencedor indiscutido de la partida!!! ======\n\n\n",arrPartidas[gPartidasActivas].jug_2);
                        arrPartidas[gPartidasActivas].ptsJug2 = 2;

                     }else{
                        // Mensajes
                        printf("\n\n\n====== El jugador 2 *** [%s] *** se ha rendido!!! INCREIBLE!!!======\n\n",arrPartidas[gPartidasActivas].jug_2);
                        printf("\n====== El jugador 1 *** [%s] *** es el vencedor indiscutido de la partida!!! ======\n\n\n",arrPartidas[gPartidasActivas].jug_1);
                        arrPartidas[gPartidasActivas].ptsJug1 = 2;
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

                           arrPartidas[gPartidasActivas].ptsJug1++; // Incrementa los puntos del jugador 1

                           if (arrPartidas[gPartidasActivas].ptsJug1==2){ // Verifica si ha ganado

                              pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 1\n\n*******************************************************\n\n\n"); // Mensaje de Ganar
                           }
                        }else{

                           arrPartidas[gPartidasActivas].ptsJug2++;// Incrementa los puntos del jugador 2

                           if (arrPartidas[gPartidasActivas].ptsJug2==2){ // Verifica si ha ganado

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

                           arrPartidas[gPartidasActivas].ptsJug1++;

                           if (arrPartidas[gPartidasActivas].ptsJug1==2){

                              pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 1\n\n*******************************************************\n\n\n");
                           }
                        }else{

                           arrPartidas[gPartidasActivas].ptsJug2++;

                           if (arrPartidas[gPartidasActivas].ptsJug2==2){

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

                           arrPartidas[gPartidasActivas].ptsJug1++;

                           if (arrPartidas[gPartidasActivas].ptsJug1==2){

                              pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 1\n\n*******************************************************\n\n\n");
                           }
                        }else{

                           arrPartidas[gPartidasActivas].ptsJug2++;

                           if (arrPartidas[gPartidasActivas].ptsJug2==2){

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

                           arrPartidas[gPartidasActivas].ptsJug1++;

                           if (arrPartidas[gPartidasActivas].ptsJug1==2){

                              pausa("\n\n\n*******************************************************\n\n              HA GANADO EL JUGADOR 1\n\n*******************************************************\n\n\n");
                           }
                        }else{

                           arrPartidas[gPartidasActivas].ptsJug2++;

                           if (arrPartidas[gPartidasActivas].ptsJug2==2){

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
}



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
    printf("\n\nPresione ENTER para continuar.");

    fflush(stdin);  // Libera el Buffer para que no se almacenen msjes

    getchar(); // Espera a que presione enter
    printf("\n");
}

void fnInstruccionesDeJuego(){ // Funcion que imprime las instrucciones y teclas de juego, es lo que voy a desplegar en la opcion 3 del menu principal

    printf("\n\n ===============================================================================\n");
    printf("\n                          *** INSTRUCCIONES DE JUEGO ***\n");
    printf("\n ===============================================================================\n\n\n");
    printf("         Como primer paso debes de acceder a Gestionar usuarios y al menos\n");
    printf("         registrar y dar de alta a dos jugadores distintos, para ahi poder\n");
    printf("         recien iniciar una partida, los menus de alta, baja y cambio sirven\n");
    printf("         para gestionar los usuarios de una manera eficiente, al igual que el menu\n");
    printf("         de consultas sirve para ver la lista de jugadores asi como las partidas jugadas\n");
    printf("         todos los menu son muy intuitivos, tenga cuidado a la hora de ingresar fechas\n");
    printf("         y use '/' para separar los dias, meses y anios.                              \n\n");
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
    printf("E - SALIR DEL ROUND ACTUAL PARA GENERAR UN NUEVO MAPA CON SALIDA\n");
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

// Funciones Segunda parte
// -------------------------------------------------------
int  fnMenuPrincipal(){

   int opcion; // Variable para la opción

   while (TRUE){ // Solicita una opción
      // Despliega el Menu
      printf("\n-------------------------------------\n");
      printf("         ARQUEROS EN EL BOSQUE       \n");
      printf("           by Steven Pereira         \n");
      printf("-------------------------------------\n\n");
      printf("\nRECOMENDAMOS QUE AGRANDE LA CONSOLA PARA VER EL CONTENIDO Y LOS MENSAJES DE UNA MEJOR MANERA.\n\n Antes de comenzar a jugar debe ir a la opcion 3 para leer las instrucciones! Es obligatorio!.\n\n");
      printf("1- Gestionar usuarios      \n");
      printf("2- Consultas              \n");
      printf("3- Instrucciones de Juego \n");
      printf("4- Jugar                  \n");
      printf("0- Salir                  \n\n");

      printf("Seleccione una opcion y presione ENTER: ");
      scanf("%d",&opcion); // Lee la opción

      if (opcion<0 || opcion>5){

         pausa("\n\nERROR! La opcion seleccionada no es correcta, vuelva a intentarlo.\n"); // Error
      }else{
         // Sale del Ciclo
         break;
      }
   }
   // retorna la opcion
   return opcion;
}

// Función para los Jugadores
void fnGestionarJugadores(){

    char opcion='*'; // Variable para la opcion

    printf("\n\n--------------------\n");
    printf("Gestion de jugadores\n");
    printf("--------------------\n\n");
    printf("a) Alta de jugador   \n");
    printf("b) Baja de jugador   \n");
    printf("c) Cambio de jugador \n");
    printf("s) Salir de gestion  \n\n");


    while (opcion!='s' && opcion!='S'){ // Ciclo

        printf("\nSeleccione la opcion deseada del menu de gestion de jugadores (a,b,c,s) y presione ENTER: ");

        scanf("%c",&opcion); // Lee la opcion


        switch(opcion){         // Verifica la opcion seleccionada

            // Dar de alta un jugador
            case 'a':
            case 'A':fnJugadorAlta();
                     break;

            // Dar de baja un jugador
            case 'b':
            case 'B':fnJugadorBaja();
                     break;

            // Hacer cambios a un jugador
            case 'c':
            case 'C':fnJugadorCambio();
                     break;

            case 's':
            case 'S':printf("\nRegresando al MENU PRINCIPAL.\n\n");
                     break;

        }
    }
}

/// Función para Realizar Consultas
void fnConsultas(){

    char dato[MAX_LON_CADENAS]; // Variable para el dato para consultas

    char opcion='*'; // Variable para la opcion

        printf("\n\n--------------------\n");
        printf("Consultas\n");
        printf("--------------------\n\n");
        printf("a) Lista de jugadores activos\n");
        printf("b) Lista de partidas\n");
        printf("c) Lista de partidas buscada por alias de jugador \n");
        printf("d) Lista de partidas buscada por fecha \n");
        printf("s) Salir  \n\n");


    while (opcion!='s' && opcion!='S'){ // Ciclo

        printf("\nSeleccione la opcion deseada del menu de consultas (a,b,c,d o s) y presione ENTER: ");

        // Lee la opcion
        fflush(stdin);
        scanf("%c",&opcion);
        printf("\n\n");


        // Verifica la opcion seleccionada
        switch(opcion){

            // Dar de alta un jugador
            case 'a':
            case 'A':fnJugadoresListar();
                     break;

            // Dar de baja un jugador
            case 'b':
            case 'B':fnPartidasListar();
                     break;

            case 'c':
            case 'C':// Solicita el alias
                     printf("\nIngrese el alias para buscar la partida: ");
                     fflush(stdin);
                     scanf("%s",dato);
                     fnPartidasPorJugadorListar(dato);
                     break;

            case 'd':
            case 'D':// Solicita la fecha
                     printf("\nIngrese en que fecha quiere buscar la partida (dd/mm/yyyy): ");
                     fflush(stdin);
                     scanf("%s",dato);
                     fnPartidasPorFechaListar(dato);
                     break;


            case 's':
            case 'S':printf("\n============== Regresando al menu principal ==============\n\n");
                     break;

        }
    }
}


// Función para verificar que un jugador exista
int fnJugadorExiste(char *alias){

    int indice; // Variable indice

    char activar; // Variable para activar


    int resultado =  FALSE; // Inicializa la variable de Resultado


    for (indice=0; indice<=gJugadoresActivos; indice++){ // Ciclo para verificar si existe

        if (CompCad(arrJugadores[indice].alias,alias)==0){ // Verifica si es el buscado

            if (arrJugadores[indice].activo){ // Verifica si está activo

                resultado = TRUE; // Lo encontro

                // Sale del Ciclo
                break;
            }else{
                // Mensaje
                printf("\n\n========= El Alias ya existe pero se encuentra INACTIVO =========\n\n");
                printf("\nActualmente no se puede volver a dar de alta un alias inactivo. Lo sentimos.");

                // Lee la opcion
                scanf("%c",&activar);
                fflush(stdin);
                printf("\n\n");

                // Verifica respuesta
                if (activar=='Y' || activar == 'y'){

                    arrJugadores[indice].activo = TRUE; // Cambia el Estado

                    pausa("\n\n========= El Jugador ha sido activado =========\n\n"); // Mensaje
                    resultado = TRUE;
                }

                // Cambia el Resultado
                resultado = TRUE;

                // Sale
                break;
            }
        }

    }
    // Devuelve el Resultado
    return resultado;
}

// Función para listar Jugadores
void fnJugadoresListar(){

    int indice; // Variable indice

    printf("\n====== Lista de jugadores activos ======\n\n");// Titulo del Reporte

    // Ciclo para leer el arreglo
    for (indice = 0; indice <= gJugadoresActivos; indice++){

        // Verifica que esté activo
        if (arrJugadores[indice].activo){

            // Despliega los datos del Jugador
            printf("CI       : %s \n",arrJugadores[indice].ci);
            printf("Alias    : %s \n",arrJugadores[indice].alias);
            printf("Nombre   : %s \n",arrJugadores[indice].nombre);
            printf("Apellido : %s \n",arrJugadores[indice].apellido);
            printf("Fech Nac : %s \n\n",arrJugadores[indice].fecNac);

        }
    }
    // Mensaje
    pausa("\n============= Fin del listado =============\n\n");
}

// Función para dar de alta un jugador
void fnJugadorAlta(){

    // Variable para dar de alta al jugador
    struct Jugador jugador;

    // Despliega el Numero de Jugadores Registrados
    printf("\n\n============== Alta de jugadores ==============\n\n");
    printf("Jugadores registrados: %d\n\n",gJugadoresActivos+1);

    if (gJugadoresActivos<MAX_NUM_JUGADORES-1){ // Verifica que todavia se pueda agregar un jugador

        printf("\nIngresa el alias: "); // Solicita los datos del Jugador
        fflush(stdin);// Libera el Buffer
        scanf("%s",jugador.alias);


        if (fnJugadorExiste(jugador.alias)){ // Verifica si ya existe

            pausa("\n\n ERROR! Ya existe un jugador registrado con ese alias. \n\n"); // Mensaje de que el jugador ya existe

        }else{

            while (TRUE){ // Ciclo para el CI

                printf("\nIngresa la CI del jugador sin puntos ni guiones (Ej: 9.999.999-9 = 99999999): ");
                scanf("%s",jugador.ci);

            if (!fnCIValido(jugador.ci)){ // Verifica que sea valido

                    pausa("\n\nERROR! La CI no es valida, intente de nuevo.\n\n");
                }else{
                    // Sale
                    break;
                }
            }

            printf("\nIngresa nombre: ");
            scanf("%s",jugador.nombre);

            printf("\nIngresa apellido: ");
            scanf("%s",jugador.apellido);

            // Ciclo para la fecha de nacimiento
            while (TRUE){
                printf("\nIngresa fecha de nacimiento (dd/mm/yyyy): ");
                scanf("%s",jugador.fecNac);

                // Verifica que sea valida
                if (!fnEsFecha(jugador.fecNac)){

                    pausa("\n\nERROR! La fecha de nacimiento ingresada no es valida verifique si coloco '/' para separar, intente de nuevo.\n");
                }else{
                    // Sale
                    break;
                }
            }

            jugador.activo = TRUE; // Activa el Jugador

            gJugadoresActivos++; // Incrementa el contador de Jugadores Activos

            arrJugadores[gJugadoresActivos] = jugador; // Coloca el jugador en el vector

            // Mensaje
            pausa("\n\n\n========= El jugador ha sido ingresado correctamente! =========\n\n\n");
        }
    }else{
        pausa("\n\n======== Ya no puedes agregar mas jugadores ========\n\n");
    }
}

int fnCIValido(char* ci){

    int resultado = FALSE; // resultado

    int i, s = 0, M = 0, h = 0;

    if (LongCad(ci)==8){ // Verifica la longitud /// 12345672 (Recordar borrar)

      for(i=0; ci[i] != '\0'; ++i){ // Cambia los caracteres de la cadena a numeros segun ASCII

        ci[0] = ci[0] - '0'; // Convierte caracter en entero es lo mismo que restar 48
        ci[1] = ci[1] - '0';
        ci[2] = ci[2] - '0';
        ci[3] = ci[3] - '0';
        ci[4] = ci[4] - '0';
        ci[5] = ci[5] - '0';
        ci[6] = ci[6] - '0';
        ci[7] = ci[7] - '0';

        s = 2*ci[0] + 9*ci[1] + 8*ci[2] + 7*ci[3] + 6*ci[4] + 3*ci[5] + 4*ci[6];
        M = s % 10;
        h = (10 - M) % 10;

        if (h == ci[7]){ // Verifica que el digito verificador de la CI sea igual a h

            resultado = TRUE; // Es valido
        }
      }
    }
   return resultado; // Retorna el resultado valido
}


// funcion que verifica la fecha, toma una cadena, la convierte en digito y verifica los meses, dias y anios
int fnEsFecha(char* fecha){

    int d1=fecha[0]-48; // Convierte caracter en entero es lo mismo que restar '0'
    int d2=fecha[1]-48;
    int day=d1*10+d2;

    int m1=fecha[3]-48;
    int m2=fecha[4]-48;
    int month=m1*10+m2;

    int y1=fecha[6]-48;
    int y2=fecha[7]-48;
    int y3=fecha[8]-48;
    int y4=fecha[9]-48;
    int year=y1*1000+y2*100+y3*10+y4;

    int resultado=FALSE;

    if(LongCad(fecha)==10){ // Verifica el largo de la cadena
        if(fecha[2]=='/' && fecha[5]=='/'){ // chequea que los separadores sean /
            if((d1>=0 && d1<=9) && (d2>=0 && d2<=9)){ // chequea que sean numeros entre 0-9
                if((m1>=0 && m1<=9) && (m2>=0 && m2<=9)){ // chequea que sean numeros entre 0-9
                    if((y1>=0 && y1<=9) && (y2>=0 && y2<=9) && (y3>=0 && y3<=9) && (y4>=0 && y4<=9)){ // chequea que sean numeros entre 0-9
                        if ((year >= 1919) && (year <= 2022)) {
                            if ((month >= 1) && (month <= 12)) {
                                if (((day >= 1) && (day <= 31)) && ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 9) || (month == 11))){

                                    resultado=TRUE;

                                }else if (((day >= 1) && (day <= 30)) && ((month == 4) || (month == 6) || (month == 8) || (month == 10) || (month == 12)) ){

                                    resultado=TRUE;

                                }else if (((day >= 1) && (day <= 28)) && (month == 2) ){

                                    resultado=TRUE;

                                }else if ((day == 29) && (month == 2) && ( (year%400 == 0) || ((year%4 == 0) && (year%100 != 0)) ) ){

                                    resultado=TRUE;
                                }else{

                                   resultado=FALSE;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return resultado;
}


// Función para dar de baja un Jugador
void fnJugadorBaja(){

    int indice; // Variable indice

    int encontrado = FALSE; // Variable para encontrar

    char alias[MAX_LON_CADENAS];  // Variable para solicitar el alias

	printf("\nIngresa el alias a dar de baja: "); // Solicita el alias a dar de baja
    fflush(stdin);
	scanf("%s",alias);

   for (indice=0; indice<=gJugadoresActivos; indice++){ // Ciclo para leer el vector

        if (CompCad(alias,arrJugadores[indice].alias)==0) { // Verifica si es el alias a dar de baja
            // Verifica si está activo
            if (arrJugadores[indice].activo){

                arrJugadores[indice].activo = FALSE; // Coloca inactivo

                // Mensaje
                pausa("\n\n\n========= El Jugador ha sido dado de baja =========\n\n");

                // Encontrado
                encontrado = TRUE;

                // Sale del Ciclo
                break;
            }else{
                // Mensaje de Error
                pausa("\n\nERROR! El jugador ingresado existe pero ya esta dado de baja\n");
                break;
            }
        }
    }if (!encontrado){
        // Mensaje de Error
        pausa("\n\nERROR! El jugador no existe.\n\n");
    }
}

// Funcion para realizar cambios en un Jugador
void fnJugadorCambio(){

    int encontrado=FALSE; // Variable para encontrado

    int indice; // Variable Indice


    char alias[MAX_LON_CADENAS]; // Variable para solicitar el alias

	 printf("\n\nIngresa el alias al que deseas cambiar los datos: "); // Solicita el alias a dar de baja
     fflush(stdin);
	 scanf("%s",alias);

    for (indice=0; indice<=gJugadoresActivos; indice++){ // Ciclo para leer el vector

        if (CompCad(arrJugadores[indice].alias,alias)==0){ // Verifica si es el alias a dar de baja

            if (arrJugadores[indice].activo){ // Verifica si está activo

               while (TRUE){ // Ciclo para el CI

                     printf("\nIngresa nuevamente la CI del jugador sin puntos (.) ni guiones (-) (9.999.999-9 = 99999999): ");
                     scanf("%s",arrJugadores[indice].ci);

                     // Verifica que sea valido
                     if (!fnCIValido(arrJugadores[indice].ci)){
                        pausa("\n\nLa CI ingresada no es valida, intente de nuevo.\n\n");
                     }else{
                        // Sale
                        break;
                     }
               }

                // Solicita los datos
                printf("\nIngresa nuevamente el nombre: ");
                scanf("%s",arrJugadores[indice].nombre);

                printf("\nIngresa nuevamente el apellido: ");
                scanf("%s",arrJugadores[indice].apellido);

                // Ciclo para la fecha de nacimiento
                while (TRUE){

                    printf("\nIngresa nuevamente la fecha de nacimiento (dd/mm/yyyy): ");
                    scanf("%s",arrJugadores[indice].fecNac);

                    // Verifica que sea valida
                    if (!fnEsFecha(arrJugadores[indice].fecNac)){
                        printf("\nLa fecha de nacimiento ingresada no es valida verifique si coloco '/' para separar, intente de nuevo.\n");

                    }else{
                        // Sale
                           break;
                    }
                }

                pausa("\n\n=========== El jugador ha sido actualizado ===========\n\n"); // Mensaje

                encontrado = TRUE; // Enconotrado

                // Sale del Ciclo
                break;
            }else{

                // Mensaje de Error
                pausa("\n\nERROR! El Jugador existe pero ya ha sido dado de baja. \n\n");

                // Encontrado
                encontrado = TRUE;
                break;
            }
        }
    }if (!encontrado){
        // Mensaje de Error
        pausa("ERROR! El jugador no existe. \n\n");
    }
}

// Función para listar Partidas
void fnPartidasListar(){

   int indice; // Variable indice

   printf("\n\nLista de partidas registradas: %d\n\n",gPartidasActivas+1);

   for (indice=0; indice<=gPartidasActivas;indice++){ // Ciclo para leer las partidas

      printf("\n\nFecha     : %s \n\n"  , arrPartidas[indice].fecha);
      printf("Jugador 1 : %s \n"  , arrPartidas[indice].jug_1);
      printf("Puntos    : %d \n"  , arrPartidas[indice].ptsJug1);
      printf("Jugador 2 : %s \n"  , arrPartidas[indice].jug_2);
      printf("Puntos    : %d \n", arrPartidas[indice].ptsJug2);

   }
   // Mensaje
   pausa("\n============= Fin del listado =============\n\n");
}

// Función para listar partidas por jugador
void fnPartidasPorJugadorListar(const char* jugador){

   int indice; // Variable indice

   printf("\nLista de partidas buscando por alias de jugador: %s\n",jugador); // Titulo del Reporte

   // Ciclo para leer las partidas
   for (indice=0; indice<=gPartidasActivas;indice++){

      if (CompCad(arrPartidas[indice].jug_1,jugador)==0 || CompCad(arrPartidas[indice].jug_2,jugador)==0){ // Verifica que contenga al jugador

         printf("\n\nFecha     : %s \n\n"  , arrPartidas[indice].fecha);
         printf("Jugador 1 : %s \n"  , arrPartidas[indice].jug_1);
         printf("Puntos    : %d \n"  , arrPartidas[indice].ptsJug1);
         printf("Jugador 2 : %s \n"  , arrPartidas[indice].jug_2);
         printf("Puntos    : %d \n\n", arrPartidas[indice].ptsJug2);
      }
   }

   // Mensaje
   pausa("\n============= Fin del listado =============\n\n");
}

// Función para listar Partidas por Fecha
void fnPartidasPorFechaListar(const char* fecha){

   int indice;

   printf("\nLista de partidas buscando por fecha: %s\n",fecha);

   for (indice=0; indice<=gPartidasActivas;indice++){ // Ciclo para leer las partidas

      if (CompCad(arrPartidas[indice].fecha,fecha)==0){ // Verifica que contenga la fecha

         printf("\n\nFecha     : %s \n\n"  , arrPartidas[indice].fecha);
         printf("Jugador 1 : %s \n"  , arrPartidas[indice].jug_1);
         printf("Puntos    : %d \n"  , arrPartidas[indice].ptsJug1);
         printf("Jugador 2 : %s \n"  , arrPartidas[indice].jug_2);
         printf("Puntos    : %d \n\n", arrPartidas[indice].ptsJug2);
      }
   }

   // Mensaje
   pausa("\n============= Fin del listado =============\n\n");
}


// Devuelve el largo de una cadena de caracteres
int LongCad(char *x) {

   int largo = 0;

   while (*x != '\0'){
      largo++;
      x++;
    }
   return largo;
}

// Compara dos cadenas de caracteres
int CompCad(char *Cad1, char *Cad2){

	int i = 0;
  	while(Cad1[i] == Cad2[i]){

  		if(Cad1[i] == '\0' && Cad2[i] == '\0')
	  		break;
		i++;
	}
	return Cad1[i] - Cad2[i];
}

