/* 
 * File:   main.c
 * Author: fabricio
 *
 * Created on July 20, 2018, 11:50 AM
 */

#include "CabeceraBatalla.h"
#include "CabeceraAleatorios.h"
#include "CabeceraTienda.h"

const char textoDarkWolf[] = "Dark Wolf";
const char textoDragon[] = "Dragon";
const char textoMightyGolem[] = "Mighty Golem";
const int HPDarkWolf = 100;
const int HPDragon = 200;
const int HPMightyGolem = 350;
const int HPPotion = 25;
const int HPHiPotion = 75;
const int MPPotion = 10;
const int p1 = 50;
const int p2 = 100;
const int p3 = 75;
const int oroDormir = 30;
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

void main(int argc, char** argv) {
    menuInicio();
}

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
            printf("5");
            break;
        case 6:
            printf("Saliendo del juego...");
            break;
        default:
            printf("\n¡Opcion no valida!\n\n");
            menuInicio();
            break;
    }
}

void verificarPuntos(){
        nivelPersonaje = obtenerNivel(experienciaPersonaje);
        HPMaxima = hpMaxima(nivelPersonaje);
        MPMaxima = mpMaxima(nivelPersonaje);
}
//Menu que inicia las acciones del menu batalla, seleccionando aleatoriamente quien inicia la batalla y el monstruo a enfrentar

void inicio() {
    printf("=============== Batalla ================\n");
    enemigo(aleatorioEntre1y3());
    printf("         Personaje vs %s\n\n", *puntero);
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
        if (HPEnemigoActual > 0) {
            turnoPersonaje();
            printf("Personaje | HP: %d / MP: %d\n\n", HPPersonaje, MPPersonaje);
        }
        if (HPPersonaje > 0 && HPEnemigoActual > 0) {
            turnoEnemigo();
        }
    }
    menuInicio();
}
//https://github.com/fabricioRG/Practica-1-Lenguajes-Formales-.git

void descansar() {
    char respuesta[1];
    printf("\n============== zzZzzZzzZ =================\n¿Deseas recuperar los puntos HP y MP al \nmaximo por %d de oro? [s/n]\n", oroDormir);
    scanf(" %s", respuesta);
    if (strcmp(respuesta, "s") == 0) {
        if (oroPersonaje >= oroDormir) {
            HPPersonaje = HPMaxima;
            MPPersonaje = MPMaxima;
            oroPersonaje -= oroDormir;
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
    printf("--------->>Turno de Personaje<<---------\n");
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
            experienciaPersonaje += recompensa(aleatorioEntre2y5(), enemigoActual);
            oroPersonaje += recompensa(aleatorioEntre5y15(), enemigoActual);
            
            printf("Enhorabuena, has vencido a %s , monstruos vencidos: %d\n", *puntero, monstruosVencidos);
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

void turnoEnemigo() {
    printf("--------->>Turno de %s<<-----------\n", *puntero);
    ataqueEnemigoActual = ataqueEnemigo(enemigoActual, nivelPersonaje, aleatorioEntre1y2());
    HPPersonaje -= ataqueEnemigoActual;
    printf("Ataque de %s con %d puntos de daño\n", *puntero, ataqueEnemigoActual);
    if (HPPersonaje <= 0) {
        reiniciarValores();
        printf("\nHP de personaje ha llegado a 0\n");
        printf("=======>>Has perdido la batalla<<========\n\n");
    } else {
        printf("Personaje | HP: %d / MP: %d\n\n", HPPersonaje, MPPersonaje);
    }
}

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

void enemigo(int aleatorio) {
    aleatorio = 1;
    if (aleatorio == 1) {
        enemigoActual = 1;
        HPEnemigoActual = HPDarkWolf;
        *puntero = textoDarkWolf;
    } else if (aleatorio == 2) {
        enemigoActual = 2;
        HPEnemigoActual = HPDragon;
        *puntero = textoDragon;
    } else if (aleatorio == 3) {
        enemigoActual = 3;
        HPEnemigoActual = HPMightyGolem;
        *puntero = textoMightyGolem;
    }
}

void tienda() {
    int opcion;
    printf("\n=============== Tienda ===================\nSelecciona el articulo que deseas comprar: \n\n");
    printf("Personaje | Oro : %d / HP: %d / MP: %d \n\n", oroPersonaje, HPPersonaje, MPPersonaje);
    printf("1. Potion: 50 oro, cura 25 HP\n"
            "2. Hi-Potion: 100 oro, cura 75 HP\n"
            "3. M-Potion: 75 oro, recupera 10 MP\n"
            "4. Regresar al menu principal\n");
    scanf("%d", &opcion);
    if (opcion == 1) {
        if (obtenerPotion(oroPersonaje) != 0) {
            Potion += 1;
            oroPersonaje -= p1;
            printf("-->Has comprado el articulo 'Potion'<--");
        } else {
            printf("No tienes suficiente oro para comprar el articulo 'Potion'");
        }
        tienda();
    } else if (opcion == 2) {
        if (obtenerHiPotion(oroPersonaje) != 0) {
            HiPotion += 1;
            oroPersonaje -= p2;
            printf("-->Has comprado el articulo 'Hi-Potion'<--");
        } else {
            printf("No tienes suficiente oro para comprar el articulo 'Hi-Potion'");
        }
        tienda();
    } else if (opcion == 3) {
        if (obtenerMPotion(oroPersonaje) != 0) {
            MPotion += 1;
            oroPersonaje -= p3;
            printf("-->Has comprado el articulo 'M-Potion'<--");
        } else {
            printf("No tienes suficiente oro para comprar el articulo 'M-Potion'");
        }
        tienda();
    } else if (opcion == 4) {
        menuInicio();
    }
}

void status() {
    char respuesta[1];
    printf("\n=============== Status ===================\n");
    printf("Nombre de jugador: Personaje\n");
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
            aumentarHP(HPPotion);
        } else {
            printf("No hay 'Potion' disponible\n");
        }
    } else if (opcion == 2) {
        if (HiPotion > 0) {
            HiPotion--;
            aumentarHP(HPHiPotion);
        } else {
            printf("No hay 'Hi-Potion' disponible\n");
        }
    } else if (opcion == 3) {
        if (MPotion > 0) {
            int manaTemporal = MPPersonaje + MPPotion;
            if (manaTemporal > MPMaxima) {
                int manaReal = MPMaxima - MPPersonaje;
                MPPersonaje = MPMaxima;
                MPotion--;
                printf("Mana de personaje se ha aumentado %d puntos MP", manaReal);
            } else {
                MPotion--;
                MPPersonaje += MPPotion;
                printf("Mana de personaje se ha aumentado %d puntos MP\n", MPPotion);
            }
        } else {
            printf("No hay 'M-Potion' disponible\n");
        }
    }
}

void aumentarHP(int curacion) {
    int vidaTemporal = HPPersonaje + curacion;
    if (HPPersonaje == HPMaxima) {
        printf(">>La salud ha llegado al maximo<<\n");
    } else if (vidaTemporal > HPMaxima) {
        int curacionReal = HPMaxima - HPPersonaje;
        HPPersonaje = HPMaxima;
        printf("Curacion de personaje con %d puntos HP\n", curacionReal);
    } else {
        HPPersonaje += curacion;
        printf("Curacion de personaje con %d puntos HP\n", curacion);
    }
}
