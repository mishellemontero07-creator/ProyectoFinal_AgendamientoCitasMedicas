#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include "utilidades.h"

// Funciones de utilidad

void limpiarBuffer(){
    while(getchar() != '\n');
}

void quitarSL (char cadena[]){
    cadena[strcspn (cadena, "\n")] = '\0';
}

// Validacion de codigo, fecha y hora
int validarCodigo(char codigo[]){

// Validar que el codigo no este vacio, que no tenga mas de 15 caracteres y que no tenga espacios en blanco
    int i;
    if(strlen(codigo) ==0 || strlen(codigo)>15)
    return 0;

    for(i = 0; codigo[i] != '\0'; i++){
    if(!isalnum(codigo[i]))
        return 0;
    }
    return 1;
}

int validarFecha(char fecha[]){

    int d, m, a;
    if (sscanf(fecha, "%d/%d/%d", &d, &m, &a) !=3)
        return 0;

    if (d<1 || d>31)
        return 0;
    if (m<1 || m>12)
        return 0;
    if (a<2025 || a>2028)
        return 0;
    return 1;   
}

int validarHora(char hora[]){
    int h, m;
    if (sscanf(hora, "%d:%d", &h, &m)!=2)
        return 0;
    if (h<0 || h>23)
        return 0;
    if(m<0 || m>59)
        return 0;
    return 1;
}