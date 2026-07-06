#ifndef Utilidades_H
#define Utilidades_H

// Prototipos de funciones para la limpieza de buffer y quitar salto de linea
void limpiarBuffer();
void quitarSL (char cadena[]);

//Funciones de validacion
int validarCodigo(char codigo[]);
int validarFecha(char fecha[]);
int validarHora (char hora[]);
int validarTexto(char texto[]);

#endif
