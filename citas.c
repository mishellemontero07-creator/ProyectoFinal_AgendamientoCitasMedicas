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
// Funciones para el manejo de archivos
void cargarArchivo(Cita citas[], int *total){
    FILE *archivo;
    char linea[300];

    archivo=fopen(ARCHIVO_CSV,"r");

    if(archivo==NULL)
    return;
    // Leer cada linea del archivo y cargarla en el arreglo de citas
    fgets(linea,sizeof(linea),archivo);


    while(fgets(linea,sizeof(linea),archivo)){
        sscanf(linea, "%15[^,],%49[^,],%49[^,],%10[^,],%5[^,],%49[^\n]",
        citas[*total].codigo,
        citas[*total].paciente,
        citas[*total].especialidad,
        citas[*total].fecha,
        citas[*total].hora,
        citas[*total].medico); 
        (*total)++;

    }
    fclose(archivo);

}

void guardarArchivo(Cita citas[], int total){
    FILE *archivo;
    int i;
// Abrir el archivo en modo escritura y guardar los datos del arreglo de citas en el archivo
    archivo=fopen(ARCHIVO_CSV,"w");
    fprintf(archivo,"codigo_cita,nombre_paciente,especialidad,fecha,hora,medico\n");

    for (i=0; i<total; i++){
        fprintf(archivo, "%s,%s,%s,%s,%s,%s\n",
            citas[i].codigo,
            citas[i].paciente,
            citas[i].especialidad,
            citas[i].fecha,
            citas[i].hora,
            citas[i].medico);
    }
    fclose(archivo);
    printf("Archivo guardado correctamente.\n");
}
