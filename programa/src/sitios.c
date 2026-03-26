/**
 * Archivo: sitios.c
 * Descripcion: Implementacion de la gestion de sitios de eventos, incluyendo la memoria dinamica y la interaccion con archivos.
 * Autores: Jareck Levell C.
 * Fecha de creación: 26/03/2026
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sitios.h"
#include "../include/archivos.h"

static Sitio *listaSitios = NULL;
static int totalSitios = 0;

char* asignarCadenaDinamica(const char *origen) {
    if (origen == NULL) return NULL;

    char *destino = (char *)malloc(strlen(origen) + 1);
    if (destino != NULL) {
        strcpy(destino, origen);
    }
    return destino;
}

void inicializarMemoriaSitios(int capacidad_inicial) {
    if (capacidad_inicial > 0) {
        listaSitios = (Sitio *)malloc(capacidad_inicial * sizeof(Sitio));
    } else {
        listaSitios = NULL;
    }
    totalSitios = 0; 
}

int obtenerCantidadSitios() {
    return totalSitios;
}

Sitio* obtenerArregloSitios() {
    return listaSitios;
}

int existeSitio(const char *nombre) {
    for (int i = 0; i < totalSitios; i++) {
        if (strcmp(listaSitios[i].nombre, nombre) == 0) {
            return 1; 
        }
    }
    return 0;
}


int registrarSitioEnMemoria(const char *nombre, const char *ubicacion, const char *web, int cant_sectores) {
    if (existeSitio(nombre)) {
        return 0; // Falla por unicidad
    }

    Sitio *temp = (Sitio *)realloc(listaSitios, (totalSitios + 1) * sizeof(Sitio));
    if (temp == NULL) {
        printf("[ERROR] Falla de memoria al agregar sitio.\n");
        return 0;
    }
    listaSitios = temp;
    
    listaSitios[totalSitios].nombre = asignarCadenaDinamica(nombre);
    listaSitios[totalSitios].ubicacion = asignarCadenaDinamica(ubicacion);
    listaSitios[totalSitios].sitio_web = asignarCadenaDinamica(web);
    listaSitios[totalSitios].cantidad_sectores = cant_sectores;
    listaSitios[totalSitios].sectores = NULL;

    totalSitios++;
    return 1;
}

void mostrarSitios() {
    if (totalSitios == 0) {
        printf("\nNo hay sitios de eventos registrados actualmente.\n");
        return;
    }

    printf("\n--- LISTA DE SITIOS DE EVENTOS ---\n");
    for (int i = 0; i < totalSitios; i++) {
        printf("%d. %s | Ubicacion: %s | Web: %s | Sectores: %d\n", 
               i + 1, 
               listaSitios[i].nombre, 
               listaSitios[i].ubicacion, 
               listaSitios[i].sitio_web,
               listaSitios[i].cantidad_sectores);
    }
    printf("----------------------------------\n");
}

void gestionSitioEventos() {
    int opcion;
    char ruta[150];

    do {
        printf("\n========================================\n");
        printf("    GESTION DE SITIOS DE EVENTOS        \n");
        printf("========================================\n");
        printf("1. Ver sitios registrados\n");
        printf("2. Cargar sitios por lote (archivo .txt)\n");
        printf("3. Volver al menu administrativo\n");
        printf("========================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion) {
            case 1:
                mostrarSitios();
                break;
            case 2:
                printf("Ingrese la ruta del archivo de lote (ej: ../data/lote_sitios.txt): ");
                fgets(ruta, sizeof(ruta), stdin);
                ruta[strcspn(ruta, "\n")] = 0; // Limpiar el salto de linea

                int agregados = cargarLoteSitiosDesdeRuta(ruta);
                if (agregados >= 0 && existeSitio(" ") == 0) { // Check basico
                    printf("\nProceso finalizado. Se agregaron %d sitios nuevos correctamente.\n", agregados);
                    printf("(Los sitios duplicados fueron ignorados segun la regla de unicidad).\n");
                } else {
                    printf("\n[ERROR] No se pudo abrir el archivo en la ruta especificada.\n");
                }
                break;
            case 3:
                break;
            default:
                printf("\nOpcion invalida.\n");
        }
    } while (opcion != 3);
}

void liberarMemoriaSitios() {
    if (listaSitios == NULL) {
        return; 
    }
    for (int i = 0; i < totalSitios; i++) {
        if (listaSitios[i].nombre != NULL) {
            free(listaSitios[i].nombre);
        }
        if (listaSitios[i].ubicacion != NULL) {
            free(listaSitios[i].ubicacion);
        }
        if (listaSitios[i].sitio_web != NULL) {
            free(listaSitios[i].sitio_web);
        }
    }
    free(listaSitios);
    listaSitios = NULL;
    totalSitios = 0;

    printf("[INFO] Memoria dinamica de sitios liberada correctamente.\n");
}
