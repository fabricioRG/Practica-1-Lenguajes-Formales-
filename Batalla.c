
const int ataqueDarkWolf = 10;
const int ataqueDragon = 15;
const int ataqueMightyGolem = 25;

int atacar(int nivel, int aleatorio) {
    int ataque = ((nivel + 1)*10) + aleatorio;
    return ataque;
}

int curar(int nivel, int aleatorio, int MP) {
    int curacion = ((nivel + 1)*5) + aleatorio;
    return curacion;
}

void tengoMiedo() {
    printf("Teniendo miedo");
}

int ataqueEnemigo(int enemigo, int nivel, int aleatorio) {
    int ataqueFinal = 0;
    int ataqueEnemigo = 0;
    if (enemigo == 1) {
        ataqueEnemigo = ataqueDarkWolf;
    } else if (enemigo == 2) {
        ataqueEnemigo = ataqueDragon;
    } else if (enemigo == 3) {
        ataqueEnemigo = ataqueMightyGolem;
    }
    if (aleatorio == 1) {
        ataqueFinal = ataqueEnemigo + nivel;
        return (ataqueFinal);
    } else {
        ataqueFinal = ataqueEnemigo + nivel + 10;
        return (ataqueFinal);
    }
}

int recompensa(int aleatorio, int enemigo) {
    int recompensa = 0;
    if (enemigo == 1) {
        recompensa = aleatorio*ataqueDarkWolf;
    } else if (enemigo == 2) {
        recompensa = aleatorio*ataqueDragon;
    } else if (enemigo == 3) {
        recompensa = aleatorio*ataqueMightyGolem;
    }
    return recompensa;
}

int obtenerNivel(int experiencia) {
    if (experiencia > 100) {
        return experiencia / 100;
    }
}

int hpMaxima(int nivel) {
    return 100 * (nivel + 1);
}

int mpMaxima(int nivel) {
    return 10 * (nivel + 1);
}