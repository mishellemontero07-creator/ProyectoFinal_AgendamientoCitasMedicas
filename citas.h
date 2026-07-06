// "Include guard" sirve para verficar que si Citas_H no esta definido
// entonces lo define y si ya esta definido no lo vuelve a definir y ejecuta todo el cintenido. De esta forma evitamos errores de copilador, al intentar leer el mismo archivo dos veces.
#ifndef Citas_H
#define Citas_H //No existe Citas_H, entonces lo definelo.
#define MAX_CITAS 100
#define ARCHIVO_CSV "citas.csv" 


typedef struct{

    char codigo[16];
    char paciente[50];
    char especialidad [50];
    char fecha[11];
    char hora[6];
    char medico[50];
}Cita;

// Prototipos de funciones
//Funciones para el manejo de archivos
void cargarArchivo (Cita citas[], int *total);
void guardarArchivo (Cita citas[], int total);

//Funciones para el manejo de citas
void registrarCita (Cita citas[],int *total);
void listarCitas (Cita citas[], int total);
void buscarCita (Cita citas[], int total);
void actualizarCita(Cita citas[], int total);
void eliminarCita(Cita citas[], int *total);

int citaExistente(Cita citas[], int total, char codigo[]);
int horarioOcupado(Cita citas[], int total, char fecha[], char hora[], int indiceIgnorar);

#endif