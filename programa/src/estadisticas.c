/**
 * Archivo: estadisticas.c
 * Descripcion: Implementacion de funciones para la gestion de estadisticas del sistema.
 * Autores: Emilio Funes R.
 * Fecha: 28/03/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/estadisticas.h"
#include "../include/eventos.h"
#include "../include/sitios.h"
#include "../include/cadenas.h"

typedef struct {
    char mes_anio[10];
    int cantidad;
} StatMesAnio;

typedef struct {
    char productora[100];
    float recaudado;
} StatProductora;

typedef struct {
    char sitio[100];
    int cantidad_eventos;
    float recaudado;
} StatSitio;

// Calculos Auxiliares

void calcularTopMesAnio() {
    int total_eventos = getCantidadEventos();
    Evento *arreglo_eventos = getArregloEventos();

    if (total_eventos == 0) {
        printf("\n--- A. Top 3 Mes-Anio con mas eventos ---\n");
        printf("No hay eventos registrados.\n");
        return;
    }

    StatMesAnio *arreglo_stats = (StatMesAnio *)malloc(total_eventos * sizeof(StatMesAnio));
    int cantidad_stats = 0;

    for (int i = 0; i < total_eventos; i++) {
        Evento *ev = &arreglo_eventos[i];
        int dia;
        int mes;
        int anio;
        
        sscanf(ev->fecha, "%d/%d/%d", &dia, &mes, &anio);
        
        char mes_anio_temp[10];
        sprintf(mes_anio_temp, "%02d-%04d", mes, anio);

        int encontrado = 0;
        
        for (int j = 0; j < cantidad_stats; j++) {
            if (strcmp(arreglo_stats[j].mes_anio, mes_anio_temp) == 0) {
                arreglo_stats[j].cantidad = arreglo_stats[j].cantidad + 1;
                encontrado = 1;
                break;
            }
        }

        if (encontrado == 0) {
            strcpy(arreglo_stats[cantidad_stats].mes_anio, mes_anio_temp);
            arreglo_stats[cantidad_stats].cantidad = 1;
            cantidad_stats++;
        }
    }

    for (int i = 0; i < cantidad_stats - 1; i++) {
        for (int j = 0; j < cantidad_stats - i - 1; j++) {
            if (arreglo_stats[j].cantidad < arreglo_stats[j + 1].cantidad) {
                StatMesAnio temp = arreglo_stats[j];
                arreglo_stats[j] = arreglo_stats[j + 1];
                arreglo_stats[j + 1] = temp;
            }
        }
    }

    printf("\n--- A. Top 3 Mes-Anio con mas eventos ---\n");
    int limite = 3;
    
    if (cantidad_stats < 3) {
        limite = cantidad_stats;
    }

    for (int i = 0; i < limite; i++) {
        printf("%d. %s (Eventos: %d)\n", i + 1, arreglo_stats[i].mes_anio, arreglo_stats[i].cantidad);
    }

    free(arreglo_stats);
}

void calcularTopProductoras() {
    int total_eventos = getCantidadEventos();
    Evento *arreglo_eventos = getArregloEventos();

    if (total_eventos == 0) {
        printf("\n--- B. Top 3 Productoras con mas recaudacion ---\n");
        printf("No hay eventos registrados.\n");
        return;
    }

    StatProductora *arreglo_stats = (StatProductora *)malloc(total_eventos * sizeof(StatProductora));
    int cantidad_stats = 0;

    for (int i = 0; i < total_eventos; i++) {
        Evento *ev = &arreglo_eventos[i];     
        float recaudado_evento = 0.0;
        
        for (int j = 0; j < ev->cantidad_sectores_evento; j++) {
            recaudado_evento = recaudado_evento + ev->sectores_evento[j].recaudado;
        }

        int encontrado = 0;     
        for (int k = 0; k < cantidad_stats; k++) {
            if (strcmp(arreglo_stats[k].productora, ev->productora) == 0) {
                arreglo_stats[k].recaudado = arreglo_stats[k].recaudado + recaudado_evento;
                encontrado = 1;
                break;
            }
        }

        if (encontrado == 0) {
            strcpy(arreglo_stats[cantidad_stats].productora, ev->productora);
            arreglo_stats[cantidad_stats].recaudado = recaudado_evento;
            cantidad_stats++;
        }
    }
    for (int i = 0; i < cantidad_stats - 1; i++) {
        for (int j = 0; j < cantidad_stats - i - 1; j++) {
            if (arreglo_stats[j].recaudado < arreglo_stats[j + 1].recaudado) {
                StatProductora temp = arreglo_stats[j];
                arreglo_stats[j] = arreglo_stats[j + 1];
                arreglo_stats[j + 1] = temp;
            }
        }
    }

    printf("\n--- B. Top 3 Productoras con mas recaudacion ---\n");
    int limite = 3;
    
    if (cantidad_stats < 3) {
        limite = cantidad_stats;
    }
    for (int i = 0; i < limite; i++) {
        printf("%d. %s (Recaudado: %.2f)\n", i + 1, arreglo_stats[i].productora, arreglo_stats[i].recaudado);
    }
    free(arreglo_stats);
}

void calcularSitiosRecaudacion() {
    int total_sitios = getCantidadSitios();
    Sitio *arreglo_sitios = getArregloSitios();

    if (total_sitios == 0) {
        printf("\n--- C. Listado de Sitios (Monto y Cantidad de Eventos) ---\n");
        printf("No hay sitios registrados.\n");
        return;
    }

    StatSitio *arreglo_stats = (StatSitio *)malloc(total_sitios * sizeof(StatSitio));
    
    for (int i = 0; i < total_sitios; i++) {
        strcpy(arreglo_stats[i].sitio, arreglo_sitios[i].nombre);
        arreglo_stats[i].cantidad_eventos = 0;
        arreglo_stats[i].recaudado = 0.0;
    }

     int total_eventos = getCantidadEventos();
    Evento *arreglo_eventos = getArregloEventos();
    for (int i = 0; i < total_eventos; i++) {
        Evento *ev = &arreglo_eventos[i];  
        float recaudado_evento = 0.0;
        
        for (int j = 0; j < ev->cantidad_sectores_evento; j++) {
            recaudado_evento = recaudado_evento + ev->sectores_evento[j].recaudado;
        }

        for (int k = 0; k < total_sitios; k++) {
            if (strcmp(arreglo_stats[k].sitio, ev->sitio_base->nombre) == 0) {
                arreglo_stats[k].cantidad_eventos = arreglo_stats[k].cantidad_eventos + 1;
                arreglo_stats[k].recaudado = arreglo_stats[k].recaudado + recaudado_evento;
                break;
            }
        }
    }

    for (int i = 0; i < total_sitios - 1; i++) {
        for (int j = 0; j < total_sitios - i - 1; j++) {
            if (arreglo_stats[j].recaudado < arreglo_stats[j + 1].recaudado) {
                StatSitio temp = arreglo_stats[j];
                arreglo_stats[j] = arreglo_stats[j + 1];
                arreglo_stats[j + 1] = temp;
            }
        }
    }

    printf("\n--- C. Listado de Sitios (Monto y Cantidad de Eventos) ---\n");
    
    for (int i = 0; i < total_sitios; i++) {
        printf("%d. %s | Eventos: %d | Recaudado: %.2f\n", i + 1, arreglo_stats[i].sitio, arreglo_stats[i].cantidad_eventos, arreglo_stats[i].recaudado);
    }

    free(arreglo_stats);
}

// Menus

void estadisticas() {
    printf("\n========================================\n");
    printf("              ESTADISTICAS              \n");
    printf("========================================\n");
    
    calcularTopMesAnio();
    calcularTopProductoras();
    calcularSitiosRecaudacion();
    
    printf("\n========================================\n");
    printf("Presione Enter para continuar...");
    limpiarBufferEntrada();
}




