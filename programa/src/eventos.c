/**
 * Archivo: eventos.c
 * Descripcion: Implementacion de funciones para la gestion de eventos.
 * Autores: Emilio Funes R.
 * Fecha: 26/03/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/eventos.h"
#include "../include/sitios.h" 
#include "../include/cadenas.h"

static Evento *listaEventos = NULL;
static int totalEventos = 0;

// Memoria

void inicializarMemoriaEventos(int capacidad_inicial) {
    if (capacidad_inicial > 0) {
        listaEventos = (Evento *)malloc(capacidad_inicial * sizeof(Evento));
    } else {
        listaEventos = NULL;
    }
    totalEventos = 0;
}

void liberarMemoriaEventos() {
    if (listaEventos == NULL) {
        return;
    }

    for (int i = 0; i < totalEventos; i++) {
        if (listaEventos[i].nombre != NULL) {
            free(listaEventos[i].nombre);
        }
        if (listaEventos[i].productora != NULL) {
            free(listaEventos[i].productora);
        }
        if (listaEventos[i].fecha != NULL) {
            free(listaEventos[i].fecha);
        }

        if (listaEventos[i].sectores_evento != NULL) {
            for (int j = 0; j < listaEventos[i].cantidad_sectores_evento; j++) {
                Sector *sec = &listaEventos[i].sectores_evento[j];
                
                if (sec->nombre != NULL) {
                    free(sec->nombre);
                }
                
                if (sec->asientos != NULL) {
                    for (int k = 0; k < sec->cantidad_espacios; k++) {
                        if (sec->asientos[k].identificador != NULL) {
                            free(sec->asientos[k].identificador);
                        }
                    }
                    free(sec->asientos);
                }
            }
            free(listaEventos[i].sectores_evento);
        }
    }

    free(listaEventos);
    listaEventos = NULL;
    totalEventos = 0;
    printf("[INFO] Memoria dinamica de eventos liberada correctamente.\n");
}

// Getters

int getCantidadEventos() { 
    return totalEventos; 
}

Evento* getArregloEventos() { 
    return listaEventos; 
}

// Agregar

Evento* agregarEvento(const char *nombre, const char *productora, const char *fecha, Sitio *sitio_base) {
    Evento *temp = (Evento *)realloc(listaEventos, (totalEventos + 1) * sizeof(Evento));
    
    if (temp == NULL) {
        return NULL;
    }
    
    listaEventos = temp;
    Evento *nuevoEvento = &listaEventos[totalEventos];

    nuevoEvento->nombre = asignarCadenaDinamica(nombre);
    nuevoEvento->productora = asignarCadenaDinamica(productora);
    nuevoEvento->fecha = asignarCadenaDinamica(fecha);
    nuevoEvento->sitio_base = sitio_base;
    nuevoEvento->cantidad_sectores_evento = sitio_base->cantidad_sectores;

    nuevoEvento->sectores_evento = (Sector *)malloc(nuevoEvento->cantidad_sectores_evento * sizeof(Sector));

    for (int i = 0; i < nuevoEvento->cantidad_sectores_evento; i++) {
        Sector *secBase = &sitio_base->sectores[i];
        Sector *secClon = &nuevoEvento->sectores_evento[i];

        secClon->nombre = asignarCadenaDinamica(secBase->nombre);
        secClon->inicial = secBase->inicial;
        secClon->cantidad_espacios = secBase->cantidad_espacios;
        secClon->precio = 0.0;
        secClon->recaudado = 0.0;

        secClon->asientos = (Asiento *)malloc(secClon->cantidad_espacios * sizeof(Asiento));
        
        for (int j = 0; j < secClon->cantidad_espacios; j++) {
            secClon->asientos[j].identificador = asignarCadenaDinamica(secBase->asientos[j].identificador);
            secClon->asientos[j].vendido = 0; 
        }
    }

    totalEventos++;
    return nuevoEvento;
}

// Menus y Visualizacion

void gestionEventos() {
    if (getCantidadSitios() == 0) {
        printf("\nNo hay sitios registrados en el sistema.\n");
        return;
    }

    char nombre[100];
    char productora[100];
    char fecha[20];
    int indice_sitio;

    printf("\n========================================\n");
    printf("           CREAR NUEVO EVENTO           \n");
    printf("========================================\n");

    printf("Nombre del evento: ");
    fgets(nombre, sizeof(nombre), stdin);
    removerSaltoLinea(nombre); 

    printf("Nombre de la productora: ");
    fgets(productora, sizeof(productora), stdin);
    removerSaltoLinea(productora);

    printf("Fecha del evento (DD/MM/AAAA): ");
    fgets(fecha, sizeof(fecha), stdin);
    removerSaltoLinea(fecha);

    printf("\n--- Seleccione el Sitio Base ---\n");
    Sitio *sitiosDisponibles = getArregloSitios();
    
    for (int i = 0; i < getCantidadSitios(); i++) {
        printf("%d. %s (Sectores: %d)\n", i + 1, sitiosDisponibles[i].nombre, sitiosDisponibles[i].cantidad_sectores);
    }
    
    printf("Seleccione: ");
    scanf("%d", &indice_sitio);
    limpiarBufferEntrada(); 

    if (indice_sitio < 1) {
        return;
    }
    if (indice_sitio > getCantidadSitios()) {
        return;
    }

    Sitio *sitio_base = &sitiosDisponibles[indice_sitio - 1];
    
    if (sitio_base->cantidad_sectores == 0) {
        printf("\nOops! El sitio '%s' no tiene sectores definidos.\n", sitio_base->nombre);
        printf("Vaya a 'Gestion de espacios sitio de eventos' y cree sectores primero.\n");
        return;
    }

    Evento *nuevoEvento = agregarEvento(nombre, productora, fecha, sitio_base);
    
    if (nuevoEvento == NULL) {
        printf("\nFalla de memoria.\n");
        return;
    }

    printf("\n--- Asignacion de precios por sector ---\n");
    for (int i = 0; i < nuevoEvento->cantidad_sectores_evento; i++) {
        Sector *secClon = &nuevoEvento->sectores_evento[i];
        
        printf("Precio para el sector '%s': ", secClon->nombre);
        scanf("%f", &secClon->precio);
        limpiarBufferEntrada();
    }

    printf("\n¡Evento '%s' configurado exitosamente!\n", nuevoEvento->nombre);
}

void estadoEventos() {
    if (getCantidadEventos() == 0) {
        printf("\nNo hay eventos registrados en el sistema.\n");
        return;
    }

    int opcion;
    printf("\n========================================\n");
    printf("           ESTADO DE EVENTO             \n");
    printf("========================================\n");
    
    for (int i = 0; i < getCantidadEventos(); i++) {
        printf("%d. %s (Fecha: %s)\n", i + 1, listaEventos[i].nombre, listaEventos[i].fecha);
    }
    
    printf("0. Volver al menu administrativo\n");
    printf("========================================\n");
    printf("Seleccione el evento que desea consultar: ");
    scanf("%d", &opcion);
    limpiarBufferEntrada();

    if (opcion == 0) {
        return;
    }

    if (opcion > 0) {
        if (opcion <= getCantidadEventos()) {
            Evento *ev = &listaEventos[opcion - 1];
            
            printf("\n--- DETALLES DEL EVENTO ---\n");
            printf("Nombre: %s\n", ev->nombre);
            printf("Productora: %s\n", ev->productora);
            printf("Sitio: %s\n", ev->sitio_base->nombre);
            printf("Fecha: %s\n", ev->fecha);
            printf("---------------------------\n");
            
            if (ev->cantidad_sectores_evento == 0) {
                printf("Este evento no tiene sectores asignados.\n");
            } else {
                for (int i = 0; i < ev->cantidad_sectores_evento; i++) {
                    Sector *sec = &ev->sectores_evento[i];
                    
                    printf("\n> Sector: %s | Precio: %.2f | Recaudado: %.2f\n", sec->nombre, sec->precio, sec->recaudado);
                    printf("  Asientos:\n  ");
                    
                    for (int j = 0; j < sec->cantidad_espacios; j++) {
                        // Imprime el ID del asiento y verifica si esta vendido (1) o disponible (0)
                        if (sec->asientos[j].vendido == 1) {
                            printf("[%s: Vendido] ", sec->asientos[j].identificador);
                        } else {
                            printf("[%s: Disponible] ", sec->asientos[j].identificador);
                        }
                    }
                    printf("\n");
                }
            }
            printf("---------------------------\n");
        } else {
            printf("\nSeleccion invalida.\n");
        }
    } else {
        printf("\nSeleccion invalida.\n");
    }
}