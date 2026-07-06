#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"citas.h"
#include"utilidades.h"

// Verificar si el codigo de la cita ya existe en el arreglo de citas

int citaExistente(Cita citas[], int total,char codigo[]){
    int i=0;
    for(i=0;i<total;i++){
        if(strcmp(citas[i].codigo,codigo)==0){
            return 1;
        }
    }
    return 0;
}

int horarioOcupado(Cita citas[], int total, char fecha[], char hora[], int indiceIgnorar){
    int i=0;
    for(i=0;i<total;i++){
        if(i==indiceIgnorar)
            continue;
        // Verificar si la fecha y hora de la cita ya existen en el arreglo de citas
        if(strcmp(citas[i].fecha,fecha)==0 && strcmp(citas[i].hora,hora)==0){
            return 1;
        }
    }
    return 0;
}