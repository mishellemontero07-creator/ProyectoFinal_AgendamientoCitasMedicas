#include<stdio.h>
#include"citas.h"
#include"utilidades.h"

int main(){


    Cita citas[MAX_CITAS];
    int total = 0;
    int opcion;

    cargarArchivo(citas,&total);

    do
    {
        //Menu principal
        printf("\n===== SISTEMA DE CITAS MEDICAS =====\n");
        printf("1. Registrar cita\n");
        printf("2. Listar citas\n");
        printf("3. Buscar cita\n");
        printf("4. Actualizar cita\n");
        printf("5. Eliminar cita\n");
        printf("6. Guardar cambios\n");
        printf("0. Salir\n");
        printf("Opcion: ");

        if(scanf("%d",&opcion) != 1)
        {
        printf("Error: Debe ingresar un numero.\n");
        limpiarBuffer();
        continue;
        }

limpiarBuffer();

if(opcion < 0 || opcion > 6)
{
    printf("Error: Debe ingresar una opcion entre 0 y 6.\n");
    continue;
}

        switch(opcion)
        {
            case 1:
                registrarCita(citas,&total);
                break;

            case 2:
                listarCitas(citas,total);
                break;

            case 3:
                buscarCita(citas,total);
                break;

            case 4:
                actualizarCita(citas,total);
                break;

            case 5:
                eliminarCita(citas,&total);
                break;

            case 6:
                guardarArchivo(citas,total);
                break;

            case 0:
                guardarArchivo(citas,total);
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while(opcion != 0);

    return 0;
}

