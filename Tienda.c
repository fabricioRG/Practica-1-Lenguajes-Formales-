const int oroPotion = 50;
const int oroHiPotion = 100;
const int oroMPotion = 75;

int obtenerPotion(int oro){
    if(oro >= oroPotion){
        return 1;
    } else {
        return 0;
    }
}

int obtenerHiPotion(int oro){
    if(oro >= oroHiPotion){
        return 1;
    } else {
        return 0;
    }
}

int obtenerMPotion(int oro){
    if(oro >= oroMPotion){
        return 1;
    } else {
        return 0;
    }
}

