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
// Funciones para el manejo de citas
void registrarCita(Cita citas[], int *total){
    Cita nuevaCita;

   printf("\nEscriba el codigo de la cita: ");
fgets(nuevaCita.codigo, sizeof(nuevaCita.codigo), stdin);

/* Verificar si el usuario escribió más de 15 caracteres */
if(strchr(nuevaCita.codigo, '\n') == NULL){
    printf("Codigo invalido. No puede tener mas de 15 caracteres.\n");
    limpiarBuffer();
    return;
}

quitarSL(nuevaCita.codigo);

if(!validarCodigo(nuevaCita.codigo)){
    printf("Codigo invalido. Debe tener entre 1 y 15 caracteres y no contener espacios en blanco.\n");
    return;
}
    if(citaExistente(citas, *total, nuevaCita.codigo)){
        printf("Codigo de cita ya existe. Ingrese un codigo diferente.\n");
        return;
    }

    printf("Paciente: ");
    fgets(nuevaCita.paciente, sizeof(nuevaCita.paciente), stdin);
    quitarSL(nuevaCita.paciente);
    if(!validarTexto(nuevaCita.paciente)){
    printf("El nombre del paciente no puede estar vacio.\n");
    return;
}

    printf("Especialidad: ");
    fgets(nuevaCita.especialidad,50,stdin);
    quitarSL(nuevaCita.especialidad);
   if(!validarTexto(nuevaCita.especialidad)){
    printf("La especialidad no puede estar vacia.\n");
    return;
}


    printf("Fecha DD/MM/AAAA: ");
    fgets(nuevaCita.fecha,11,stdin);
    quitarSL(nuevaCita.fecha);

    if(!validarFecha(nuevaCita.fecha)){
        printf("Fecha invalida. Debe estar en formato DD/MM/AAAA y ser una fecha valida.\n");
        return;
    }

    limpiarBuffer();

    printf("Ingrese la Hora HH:MM (24 horas): ");
    fgets(nuevaCita.hora,6,stdin);
    quitarSL(nuevaCita.hora);

    limpiarBuffer();

    if(!validarHora(nuevaCita.hora)){
        printf("Hora invalida. Debe estar en formato HH:MM y ser una hora valida.\n");
        return;
    }

    if(horarioOcupado(citas, *total, nuevaCita.fecha, nuevaCita.hora, -1)){
        printf("El horario ya está ocupado. Ingrese una hora diferente.\n");
        return;
    }

    printf("Medico: ");
    fgets(nuevaCita.medico,50,stdin);
    quitarSL(nuevaCita.medico);
    if(!validarTexto(nuevaCita.medico)){
    printf("El nombre del medico no puede estar vacio.\n");
    return;
}

    citas[*total] = nuevaCita;
    (*total)++;
    printf("\nCita registrada correctamente.\n");
}

void listarCitas(Cita citas[], int total){
    int i;

    printf("\n======Listado de Citas======\n");
    for (i=0; i<total; i++){
        printf("Codigo: %s\n", citas[i].codigo);
        printf("Paciente: %s\n", citas[i].paciente);
        printf("Especialidad: %s\n", citas[i].especialidad);
        printf("Fecha: %s\n", citas[i].fecha);
        printf("Hora: %s\n", citas[i].hora);
        printf("Medico: %s\n", citas[i].medico);
        printf("--------------------\n");
    }

}

void buscarCita(Cita citas[], int total){
    char dato[50];
    int i;

    printf("\nIngrese el codigo o nombre del paciente a buscar: ");
    fgets(dato,50,stdin);
    quitarSL(dato);

    for(i=0;i<total; i++){
        // Verificar si el codigo o nombre del paciente coincide con el dato ingresado
        if(strcmp(citas[i].codigo,dato)==0 || strstr(citas[i].paciente,dato)!=NULL){
            printf("\nCita encontrada:\n");
            // Mostrar los datos de la cita encontrada
            printf("\n%s | %s | %s | %s | %s | %s\n", 
            citas[i].codigo,
            citas[i].paciente,
            citas[i].especialidad,
            citas[i].fecha,
            citas[i].hora,
            citas[i].medico);
        }
    }
}

void actualizarCita(Cita citas[], int total){
    char codigo[16];
    int i;

    printf("\nIngrese el codigo de la cita a actualizar: ");
    fgets(codigo,16,stdin);
    quitarSL(codigo);

for(i=0;i<total;i++){
    if(strcmp(citas[i].codigo,codigo)==0){
        printf("Ingrese la nueva fecha DD/MM/AAAA: ");
        fgets(citas[i].fecha,11,stdin);
        quitarSL(citas[i].fecha);
        limpiarBuffer();

        if(!validarFecha(citas[i].fecha)){
            printf("Fecha invalida. Debe estar en formato DD/MM/AAAA y ser una fecha valida.\n");
            return;
        }

        printf("Ingrese la nueva hora HH:MM (24 horas): ");
        fgets(citas[i].hora,6,stdin);
        quitarSL(citas[i].hora);

        if(!validarHora(citas[i].hora)){
            printf("Hora invalida. Debe estar en formato HH:MM y ser una hora valida.\n");
            return;
        }
    if (horarioOcupado(citas, total, citas[i].fecha, citas[i].hora, i)){
        printf("El horario ya está ocupado.\n");
        return;
    }
    printf("Actualizada correctamente.\n");
    return;
    
}

}
    printf("Cita no encontrada.\n");
}

void eliminarCita(Cita citas[], int *total){
    int i,j;
    char codigo[16];
    char confirmacion;

    printf("\nIngrese el codigo de la cita a eliminar: ");
    fgets(codigo,16,stdin);
    quitarSL(codigo);

    for(i=0; i<(*total);i++){
        
        if(strcmp(citas[i].codigo,codigo)==0){
            printf("Cita encontrada:\n");
            printf("%s | %s | %s | %s | %s | %s\n", 
            citas[i].codigo,
            citas[i].paciente,
            citas[i].especialidad,
            citas[i].fecha,
            citas[i].hora,
            citas[i].medico);
            
            printf("¿Está seguro que desea eliminar esta cita? (S/N): ");
            scanf("%c",&confirmacion);
            limpiarBuffer();

            if(confirmacion=='S' || confirmacion=='s'){
                for(j=i;j<*total-1;j++){
                    citas[j]=citas[j+1];
                }
                (*total)--;
                printf("Cita eliminada correctamente.\n");
                return;
            }else{
                printf("Eliminación cancelada.\n");
                return;
            }
        }
    }
    printf("Cita no encontrada.\n");
}