/* 
 * File:   main.c
 * Author: fabricio
 *
 * Created on July 20, 2018, 11:50 AM
 */

#include "CabeceraBatalla.h"
#include "CabeceraAleatorios.h"
#include "CabeceraTienda.h"

const char TEXTO_DARK_WOLF[] = "Dark Wolf";
const char TEXTO_DRAGON[] = "Dragon";
const char TEXTO_MIGHTY_GOLEM[] = "Mighty Golem";
const int HP_DARK_WOLF = 100;
const int HP_DRAGON = 200;
const int HP_MIGHTY_GOLEM = 350;
const int HP_POTION = 25;
const int HP_HI_POTION = 75;
const int MP_POTION = 10;
const int P1 = 50;
const int P2 = 100;
const int P3 = 75;
const int ORO_DORMIR = 30;
char direccion[] = "./punteos.txt";
char argumento = 1;
char *puntero[];
int HPMaxima = 100;
int MPMaxima = 10;
int enemigoActual = 0;
int HPEnemigoActual = 0;
int ataqueEnemigoActual = 0;
int HPPersonaje = 100;
int MPPersonaje = 10;
int nivelPersonaje = 0;
int experienciaPersonaje = 0;
int oroPersonaje = 0;
int monstruosVencidos = 0;
int Potion = 0;
int HiPotion = 0;
int MPotion = 0;
char *jugador[];
char personaje[20];
FILE *fd;

/**
 * Funcion encargado de agregar texto en el archivo "punteos.txt"
 */
void agregar() {
    fflush(stdin);
    fd = fopen(direccion, "at");
    if (fd == NULL) {
        printf("No se ha podido escribir en el archivo\n");
    }
    char txt[10];
    char *texto[10];
    *texto = txt;
    sprintf(txt, "%d", monstruosVencidos);
    fprintf(fd, "\nNombre Jugador: ");
    fwrite(*jugador, 1, strlen(*jugador), fd);
    fprintf(fd, "\nMonstruos vencidos: ");
    fwrite(*texto, 1, strlen(*texto), fd);
}
/**
 * Funcion que se encarga de mostrar en pantalla los datos de todos los jugadores; muestra el nombre del jugador y su
 * punteo
 */
void visualizar(){
    int c;
    fd = fopen(direccion, "r");
    if(fd == NULL){
        printf("No se ha podido leer el archivo");
    }
    
    printf("================ Punteos ================\n");
    while((c = fgetc(fd)) != EOF) {
        if(c == '\n'){
            printf("\n");
        } else {
            putchar(c);
        }
    }
    printf("\n\n¿Regresar al menu principal? [s/n]\n");
    char respuesta[1];
    scanf(" %s", respuesta);
    if (strcmp(respuesta, "s") == 0) {
        menuInicio();
    } else {
        visualizar();
    }
}

void main(int argc, char *argv[]) {
    if (argc > 1) {
        *jugador = argv[1];
        printf("%s", *jugador);
    } else {
        datosJugdor();
    }
    menuInicio();
}
/**
 * Funcion encargada de pedir al usuario o jugador, los datos de su personaje para que estos sean debidamente guardados
 */
void datosJugdor() {
    printf("Ingrese el nombre de su jugador: \n");
    scanf(" %s", &personaje);
    *jugador = personaje;
}
/**
 * Funcion que muestra al jugador las opciones que puede realizar durante la ejecucion del juego
 */
void menuInicio() {
    int seleccion;
    verificarPuntos();
    printf("============ Menu Principal =============\n"
            "Seleccione una opcion del siguiente menu: \n"
            "1. A la carga!!!! \n"
            "2. Tienda\n"
            "3. zzZzzZzzZ\n"
            "4. Status\n"
            "5. Mejor punteo\n"
            "6. Salir\n");

    scanf("%d", &seleccion);

    switch (seleccion) {
        case 1:
            inicio();
            break;
        case 2:
            tienda();
            break;
        case 3:
            descansar();
            break;
        case 4:
            status();
            break;
        case 5:
            visualizar();
            break;
        case 6:
            printf("Saliendo del juego...\n");
            break;
        default:
            printf("\n¡Opcion no valida!\n\n");
            menuInicio();
            break;
    }
}
/**
 * Funcion que modifica el valor de la "HP maxima" del jugador, asi como la "MP maxima" basada en su experiencia
 */
void verificarPuntos() {
    nivelPersonaje = obtenerNivel(experienciaPersonaje);
    HPMaxima = hpMaxima(nivelPersonaje);
    MPMaxima = mpMaxima(nivelPersonaje);
}

//Menu que inicia las acciones del menu batalla, seleccionando aleatoriamente quien inicia la batalla y el monstruo a enfrentar
void inicio() {
    printf("=============== Batalla ================\n");
    enemigo(aleatorioEntre1y3());
    printf("         %s vs %s\n\n", *jugador, *puntero);
    printf("%s | HP: %d / MP: %d\n", *jugador, HPPersonaje, MPPersonaje);
    printf("Vida de %s:  %d\n\n", *puntero, HPEnemigoActual);
    if (aleatorioEntre1y2() == 1) {
        batalla();
    } else {
        turnoEnemigo();
        batalla();
    }
}

/**Funcion encargada de manejar los turnos del personaje y el enemigo, entrando en un ciclo que termina hasta que 
 * uno de los dos lleguen tengan puntos de vida (HP) igual a 0
 **/
void batalla() {
    argumento = 1;
    while (argumento == 1) {
        if (HPEnemigoActual > 0 && argumento == 1) {
            turnoPersonaje();
            printf("%s | HP: %d / MP: %d\n\n", *jugador, HPPersonaje, MPPersonaje);
        }
        if (HPPersonaje > 0 & HPEnemigoActual > 0 & argumento == 1) {
            turnoEnemigo();
        }
    }
    menuInicio();
}
//https://github.com/fabricioRG/Practica-1-Lenguajes-Formales-.git

void descansar() {
    char respuesta[1];
    printf("\n============== zzZzzZzzZ =================\n¿Deseas recuperar los puntos HP y MP al \nmaximo por %d de oro? [s/n]\n", ORO_DORMIR);
    scanf(" %s", respuesta);
    if (strcmp(respuesta, "s") == 0) {
        if (oroPersonaje >= ORO_DORMIR) {
            HPPersonaje = HPMaxima;
            MPPersonaje = MPMaxima;
            oroPersonaje -= ORO_DORMIR;
            printf("Personaje con puntos maximos | HP: %d / MP: %d\n\n", HPPersonaje, MPPersonaje);
        } else {
            printf("No cuentas con el oro suficiente para descansar y recuperar tus puntos HP y MP\n");
        }
    }
    printf("Regresando al menu principal...\n\n");
    menuInicio();
}

/**
 * Funcion encargada de mostrar las opciones que puede realizar el jugador en batalla, asi como mostrar mensajes informativos
 * de la salud del personaje como su ataque
 **/
void turnoPersonaje() {
    int opcion = 0;
    int ataque = 0;
    printf("--------->>Turno de %s<<---------\n", *jugador);
    printf("\nSelecciona una opcion: \n"
            "1. Atacar\n"
            "2. Curar\n"
            "3. Item\n"
            "4. Tengo Miedo\n");
    scanf("%d", &opcion);
    if (opcion == 1) {
        ataque = atacar(nivelPersonaje, aleatorioEntre10y20());
        HPEnemigoActual -= ataque;
        printf("Ataque de personaje %d puntos de daño\n", ataque);
        if (HPEnemigoActual <= 0) {
            argumento = 0;
            HPEnemigoActual = 0;
            monstruosVencidos++;
            int recompensaExpe = recompensa(aleatorioEntre2y5(), enemigoActual);
            int recompensaOro = recompensa(aleatorioEntre5y15(), enemigoActual);
            experienciaPersonaje += recompensaExpe;
            oroPersonaje += recompensaOro;
            printf("¡¡¡Enhorabuena!!!, has vencido a %s , monstruos vencidos: %d\n", *puntero, monstruosVencidos);
            printf("Has ganado %d puntos de experiencia, y %d de oro para %s\n", recompensaExpe, recompensaOro, *jugador);
        } else {
            printf("Vida de %s:  %d\n", *puntero, HPEnemigoActual);
        }
    } else if (opcion == 2) {
        if (MPPersonaje > 0) {
            MPPersonaje -= 1;
            int curacion = curar(nivelPersonaje, aleatorioEntre10y20() + 5);
            aumentarHP(curacion);
        } else {
            printf("No tienes suficientes puntos de mana\n");
        }
    } else if (opcion == 3) {
        item();
    } else if (opcion == 4) {
        tengoMiedo();
    }
}

/**
 * Funcion encargada de generar el daño que afectara al jugador en turno
 */
void turnoEnemigo() {
    printf("--------->>Turno de %s<<-----------\n", *puntero);
    ataqueEnemigoActual = ataqueEnemigo(enemigoActual, nivelPersonaje, aleatorioEntre1y2());
    HPPersonaje -= ataqueEnemigoActual;
    printf("Ataque de %s con %d puntos de daño\n", *puntero, ataqueEnemigoActual);
    if (HPPersonaje <= 0) {
        agregar();
        reiniciarValores();
        printf("\nHP de %s ha llegado a 0\n", *jugador);
        printf("=======>>Has perdido la batalla<<========\n\n");
        datosJugdor();
    } else {
        printf("%s | HP: %d / MP: %d\n\n", *jugador, HPPersonaje, MPPersonaje);
    }
}
/**
 * Funcion utilizada para llevar todos los valores a su minimo, esto se produce tras perder una partida
 */
void reiniciarValores() {
    HPPersonaje = HPMaxima;
    MPPersonaje = 10;
    nivelPersonaje = 0;
    experienciaPersonaje = 0;
    oroPersonaje = 0;
    Potion = 0;
    HiPotion = 0;
    MPotion = 0;
    monstruosVencidos = 0;
    argumento = 0;
}

void tengoMiedo() {
    int oroMin = oroParaHuir(nivelPersonaje, aleatorioEntre5y10());
    if (oroPersonaje >= oroMin) {
        oroPersonaje -= oroMin;
        argumento = 0;
        printf("Oro necesario: %d\n%s ha huido de la batalla\nRegresando al menu principal...\n\n", oroMin, *jugador);
    } else {
        printf("Oro necesario: %d\nNo cuentas con el oro necesario para huir de la batalla\n", oroMin);
    }
}
/**
 * Funcion que recibe como parametro un numero aleatorio entre 1 y 3, y dependiendo de ese numero, se asignara un enemigo
 * @param aleatorio
 */
void enemigo(int aleatorio) {
    if (aleatorio == 1) {
        enemigoActual = 1;
        HPEnemigoActual = HP_DARK_WOLF;
        *puntero = TEXTO_DARK_WOLF;
    } else if (aleatorio == 2) {
        enemigoActual = 2;
        HPEnemigoActual = HP_DRAGON;
        *puntero = TEXTO_DRAGON;
    } else if (aleatorio == 3) {
        enemigoActual = 3;
        HPEnemigoActual = HP_MIGHTY_GOLEM;
        *puntero = TEXTO_MIGHTY_GOLEM;
    }
}
/**
 * Funcion que permite comprar articulos en la tienda, para curar al personaje, asi como para recuperar sus puntos de mana
 */
void tienda() {
    int opcion;
    printf("\n=============== Tienda ===================\nSelecciona el articulo que deseas comprar: \n\n");
    printf("%s | Oro : %d / HP: %d / MP: %d \n\n", *jugador, oroPersonaje, HPPersonaje, MPPersonaje);
    printf("1. Potion: 50 oro, cura 25 HP\n"
            "2. Hi-Potion: 100 oro, cura 75 HP\n"
            "3. M-Potion: 75 oro, recupera 10 MP\n"
            "4. Regresar al menu principal\n");
    scanf("%d", &opcion);
    if (opcion == 1) {
        if (obtenerPotion(oroPersonaje) != 0) {
            Potion += 1;
            oroPersonaje -= P1;
            printf("-->Has comprado el articulo 'Potion'<--");
        } else {
            printf("No tienes suficiente oro para comprar el articulo 'Potion'");
        }
        tienda();
    } else if (opcion == 2) {
        if (obtenerHiPotion(oroPersonaje) != 0) {
            HiPotion += 1;
            oroPersonaje -= P2;
            printf("-->Has comprado el articulo 'Hi-Potion'<--");
        } else {
            printf("No tienes suficiente oro para comprar el articulo 'Hi-Potion'");
        }
        tienda();
    } else if (opcion == 3) {
        if (obtenerMPotion(oroPersonaje) != 0) {
            MPotion += 1;
            oroPersonaje -= P3;
            printf("-->Has comprado el articulo 'M-Potion'<--");
        } else {
            printf("No tienes suficiente oro para comprar el articulo 'M-Potion'");
        }
        tienda();
    } else if (opcion == 4) {
        menuInicio();
    }
}
/**
 * Funcion que muestra toda la informacion del jugador, su vida, puntos de mana, articulos comprados, monstruos vencidos, el
 * nivel del personaje, oro disponible y su experiencia
 */
void status() {
    char respuesta[1];
    printf("\n=============== Status ===================\n");
    printf("Nombre de jugador: %s\n", *jugador);
    printf("HP: %d\nMP: %d\nNivel: %d\nExperiencia: %d\nOro: %d\nMonstruos vencidos: %d\nPotion: %d\nHi-Potion: %d\nM-Potion: %d"
            "\n\nRegresar al menu principal [s/n]\n", HPPersonaje, MPPersonaje,
            nivelPersonaje, experienciaPersonaje, oroPersonaje, monstruosVencidos, Potion, HiPotion, MPotion);
    scanf(" %s", respuesta);
    if (strcmp(respuesta, "s") == 0) {
        menuInicio();
    } else {
        status();
    }
}
/**
 * Funcion utilizada en batalla, la cual permite utilizar los articulos disponible que fueron comprados en la tienda
 */
void item() {
    int opcion;
    printf("Items disponibles:\n"
            "1. Potion: %d\n"
            "2. Hi-Potion: %d\n"
            "3. M-Potion: %d\n", Potion, HiPotion, MPotion);
    scanf("%d", &opcion);
    if (opcion == 1) {
        if (Potion > 0) {
            Potion--;
            aumentarHP(HP_POTION);
        } else {
            printf("No hay 'Potion' disponible\n");
        }
    } else if (opcion == 2) {
        if (HiPotion > 0) {
            HiPotion--;
            aumentarHP(HP_HI_POTION);
        } else {
            printf("No hay 'Hi-Potion' disponible\n");
        }
    } else if (opcion == 3) {
        if (MPotion > 0) {
            int manaTemporal = MPPersonaje + MP_POTION;
            if (manaTemporal > MPMaxima) {
                int manaReal = MPMaxima - MPPersonaje;
                MPPersonaje = MPMaxima;
                MPotion--;
                printf("Mana de personaje se ha aumentado %d puntos MP", manaReal);
            } else {
                MPotion--;
                MPPersonaje += MP_POTION;
                printf("Mana de personaje se ha aumentado %d puntos MP\n", MP_POTION);
            }
        } else {
            printf("No hay 'M-Potion' disponible\n");
        }
    }
}

void aumentarHP(int curacion) {
    int vidaTemporal = HPPersonaje + curacion;
    if (HPPersonaje == HPMaxima) {
        printf(">>La salud de %s ha llegado al maximo<<\n", *jugador);
    } else if (vidaTemporal > HPMaxima) {
        int curacionReal = HPMaxima - HPPersonaje;
        HPPersonaje = HPMaxima;
        printf("Curacion de %s con %d puntos HP\n", *jugador, curacionReal);
    } else {
        HPPersonaje += curacion;
        printf("Curacion de %s con %d puntos HP\n", *jugador, curacion);
    }
}
