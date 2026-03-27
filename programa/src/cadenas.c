/**
 * Archivo: cadenas.c
 * Descripcion: Este archivo contiene las implementaciones de funciones relacionadas con el manejo de cadenas
 * Autores: Emilio Funes R. , Ginger Rodríguez G. & Jareck Levell C.
 * Fecha: 26/03/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cadenas.h"

// Memoria

char* asignarCadenaDinamica(const char *origen) {
    if (origen == NULL) {
        return NULL;
    }
    
    char *destino = (char *)malloc(strlen(origen) + 1);
    
    if (destino != NULL) {
        strcpy(destino, origen);
    }
    
    return destino;
}

// Limpieza

void removerSaltoLinea(char *cadena) {
    if (cadena != NULL) {
        cadena[strcspn(cadena, "\n")] = 0;
    }
}

void limpiarBufferEntrada() {
    int c;
    while (1) {
        c = getchar();
        if (c == '\n') {
            break;
        }
        if (c == EOF) {
            break;
        }
    }
}