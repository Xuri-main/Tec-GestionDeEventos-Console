/**
 * Archivo: archivos.c
 * Descripcion: Implementacion de la lectura y escritura de archivos planos.
 * Autores: Emilio Funes R.
 * Fecha de creación: 25/03/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/archivos.h"

void cargarTodosLosDatos() {}

void guardarTodosLosDatos() {}

int obtenerCredencialesAdmin(char *usuario, char *clave) {
    FILE *archivo = fopen(RUTA_USUARIOS, "r");
    if (archivo == NULL) return 0;

    if (fscanf(archivo, "%49[^,],%49s", usuario, clave) == 2) {
        fclose(archivo);
        return 1;
    }
    
    fclose(archivo);
    return 0;
}

// Gestion de Sitios

void cargarSitios() {}

void guardarSitios() {}
