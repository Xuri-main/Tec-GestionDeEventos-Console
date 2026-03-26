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
#include "../include/sitios.h"

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

void cargarSitios() {
    FILE *archivo = fopen(RUTA_SITIOS, "r");
    if (archivo == NULL) {
        inicializarMemoriaSitios(0);
        return;
    }

    int cantidad;
    if (fscanf(archivo, "%d\n", &cantidad) == 1) {
        inicializarMemoriaSitios(cantidad);
        
        char linea[256];
        for (int i = 0; i < cantidad; i++) {
            if (fgets(linea, sizeof(linea), archivo)) {
                linea[strcspn(linea, "\n")] = 0;
                
                char *nombre = strtok(linea, ",");
                char *ubi = strtok(NULL, ",");
                char *web = strtok(NULL, ",");
                char *cant_sec_str = strtok(NULL, ",");
                
                if(nombre && ubi && web && cant_sec_str) {
                    registrarSitioEnMemoria(nombre, ubi, web, atoi(cant_sec_str));
                }
            }
        }
    }
    fclose(archivo);
}

void guardarSitios() {
    FILE *archivo = fopen(RUTA_SITIOS, "w");
    if (archivo == NULL) return;

    int cantidad = obtenerCantidadSitios();
    Sitio *arreglo = obtenerArregloSitios();

    fprintf(archivo, "%d\n", cantidad);
    
    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%s,%s,%s,%d\n", 
                arreglo[i].nombre, 
                arreglo[i].ubicacion, 
                arreglo[i].sitio_web, 
                arreglo[i].cantidad_sectores);
    }
    fclose(archivo);
}

int cargarLoteSitiosDesdeRuta(const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL) return 0;

    char linea[256];
    int agregados = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = 0; 
    
        char *nombre = strtok(linea, ",");
        char *ubi = strtok(NULL, ",");
        char *web = strtok(NULL, ",");

        if (nombre && ubi && web) {
            if(ubi[0] == ' ') ubi++; 
            if(web[0] == ' ') web++;

            if (registrarSitioEnMemoria(nombre, ubi, web, 0)) {
                agregados++;
            }
        }
    }
    fclose(archivo);
    return agregados;
}
