/**
 * Archivo: ventas.c
 * Descripcion: Implementacion de funciones para la gestion de ventas y consultas.
 * Autores: Emilio Funes R. , Ginger Rodríguez G. & Jareck Levell C.
 * Fecha: 27/03/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/ventas.h"
#include "../include/eventos.h"
#include "../include/sitios.h"
#include "../include/cadenas.h"


int compararFechas(const char *fecha_evento, const char *fecha_inicial) {
    struct tm tm_evento = {0};
    struct tm tm_inicial = {0};
    int dia;
    int mes;
    int anio;

    sscanf(fecha_evento, "%d/%d/%d", &dia, &mes, &anio);
    tm_evento.tm_mday = dia;
    tm_evento.tm_mon = mes - 1;
    tm_evento.tm_year = anio - 1900;
    tm_evento.tm_isdst = -1;

    sscanf(fecha_inicial, "%d/%d/%d", &dia, &mes, &anio);
    tm_inicial.tm_mday = dia;
    tm_inicial.tm_mon = mes - 1;
    tm_inicial.tm_year = anio - 1900;
    tm_inicial.tm_isdst = -1;

    time_t t_evento = mktime(&tm_evento);
    time_t t_inicial = mktime(&tm_inicial);

    if (difftime(t_evento, t_inicial) >= 0) {
        return 1;
    }

    return 0;
}

// Menus

void consultaPorEvento() {
    if (getCantidadEventos() == 0) {
        printf("\nNo hay eventos registrados en el sistema.\n");
        return;
    }

    char fecha_inicial[20];
    
    printf("\n========================================\n");
    printf("         CONSULTA POR EVENTO            \n");
    printf("========================================\n");
    
    printf("Ingrese la fecha inicial (DD/MM/AAAA): ");
    fgets(fecha_inicial, sizeof(fecha_inicial), stdin);
    removerSaltoLinea(fecha_inicial);

    int total_eventos = getCantidadEventos();
    Evento *arreglo_eventos = getArregloEventos();
    
    int *indices_validos = (int *)malloc(total_eventos * sizeof(int));
    int cantidad_validos = 0;

    for (int i = 0; i < total_eventos; i++) {
        if (compararFechas(arreglo_eventos[i].fecha, fecha_inicial)) {
            indices_validos[cantidad_validos] = i;
            cantidad_validos++;
        }
    }

    if (cantidad_validos == 0) {
        printf("\nNo se encontraron eventos programados para esa fecha o posteriores.\n");
        free(indices_validos);
        return;
    }

    printf("\n--- EVENTOS FUTUROS ---\n");
    
    for (int i = 0; i < cantidad_validos; i++) {
        Evento *ev = &arreglo_eventos[indices_validos[i]];
        
        printf("%d. %s - %s\n", i + 1, ev->nombre, ev->fecha);
    }

    int opcion;
    
    printf("0. Volver al menu general\n");
    printf("========================================\n");
    printf("Seleccione un evento para ver detalles: ");
    scanf("%d", &opcion);
    limpiarBufferEntrada();

    if (opcion > 0) {
        if (opcion <= cantidad_validos) {
            int indice_real = indices_validos[opcion - 1];
            Evento *ev_seleccionado = &arreglo_eventos[indice_real];
            
            printf("\n--- DETALLES DEL EVENTO ---\n");
            printf("Nombre: %s\n", ev_seleccionado->nombre);
            printf("Productora: %s\n", ev_seleccionado->productora);
            printf("Sitio: %s\n", ev_seleccionado->sitio_base->nombre);
            printf("Fecha: %s\n", ev_seleccionado->fecha);
            printf("---------------------------\n");
            
            if (ev_seleccionado->cantidad_sectores_evento == 0) {
                printf("Este evento no tiene sectores definidos.\n");
            } else {
                for (int i = 0; i < ev_seleccionado->cantidad_sectores_evento; i++) {
                    Sector *sec = &ev_seleccionado->sectores_evento[i];
                    int asientos_disponibles = 0;
                    
                    for (int j = 0; j < sec->cantidad_espacios; j++) {
                        if (sec->asientos[j].vendido == 0) {
                            asientos_disponibles++;
                        }
                    }
                    
                    printf("> Sector: %s | Monto por asiento: %.2f | Asientos disponibles: %d\n", sec->nombre, sec->precio, asientos_disponibles);
                }
            }
            printf("---------------------------\n");
        } else {
            printf("\nSeleccion invalida.\n");
        }
    } else {
        if (opcion != 0) {
            printf("\nSeleccion invalida.\n");
        }
    }

    free(indices_validos);
}

void compraDeBoletos() {}