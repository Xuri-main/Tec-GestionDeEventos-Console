/**
 * Archivo: facturas.c
 * Descripcion: Este archivo contiene las implementaciones de la gestion de facturas.
 * Autores: Ginger Rodríguez G.
 * Fecha: 28/03/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/facturas.h"
#include "../include/cadenas.h"

static Factura *listaFacturas = NULL;
static int totalFacturas = 0;

// Memoria

void inicializarMemoriaFacturas(int capacidad_inicial) {
    if (capacidad_inicial > 0) {
        listaFacturas = (Factura *)malloc(capacidad_inicial * sizeof(Factura));
    } else {
        listaFacturas = NULL;
    }
    
    totalFacturas = 0;
}


void liberarMemoriaFacturas() {
    if (listaFacturas == NULL) {
        return;
    }

    for (int i = 0; i < totalFacturas; i++) {
        Factura *fac = &listaFacturas[i];
        
        if (fac->fecha_compra != NULL) {
            free(fac->fecha_compra);
        }
        if (fac->cedula_cliente != NULL) {
            free(fac->cedula_cliente);
        }
        if (fac->nombre_cliente != NULL) {
            free(fac->nombre_cliente);
        }
        if (fac->nombre_evento != NULL) {
            free(fac->nombre_evento);
        }
        if (fac->productora != NULL) {
            free(fac->productora);
        }
        if (fac->sitio_evento != NULL) {
            free(fac->sitio_evento);
        }
        if (fac->fecha_evento != NULL) {
            free(fac->fecha_evento);
        }
        
        if (fac->detalles != NULL) {
            for (int j = 0; j < fac->cantidad_detalles; j++) {
                if (fac->detalles[j].identificador_asiento != NULL) {
                    free(fac->detalles[j].identificador_asiento);
                }
            }
            free(fac->detalles);
        }
    }
    free(listaFacturas);
    listaFacturas = NULL;
    totalFacturas = 0;
    
    printf("[INFO] Memoria dinamica de facturas liberada correctamente.\n");
}

// Getters
int getCantidadFacturas() {
    return totalFacturas;
}
Factura* getArregloFacturas() {
    return listaFacturas;
}

// Acciones

void agregarFactura(const char *fecha_compra, const char *cedula, const char *nombre_cliente, const char *nombre_evento, const char *productora, const char *sitio_evento, const char *fecha_evento, int cantidad_detalles, DetalleFactura *detalles, float subtotal, float costo_servicio, float total) {
    Factura *temp = (Factura *)realloc(listaFacturas, (totalFacturas + 1) * sizeof(Factura));
    
    if (temp == NULL) {
        printf("Oops! Falla de memoria al guardar factura.\n");
        return;
    }
    
    listaFacturas = temp;
    Factura *nueva = &listaFacturas[totalFacturas];
    nueva->id_factura = totalFacturas + 1; 
    nueva->fecha_compra = asignarCadenaDinamica(fecha_compra);
    nueva->cedula_cliente = asignarCadenaDinamica(cedula);
    nueva->nombre_cliente = asignarCadenaDinamica(nombre_cliente);
    nueva->nombre_evento = asignarCadenaDinamica(nombre_evento);
    nueva->productora = asignarCadenaDinamica(productora);
    nueva->sitio_evento = asignarCadenaDinamica(sitio_evento);
    nueva->fecha_evento = asignarCadenaDinamica(fecha_evento);
    

    nueva->subtotal = subtotal;
    nueva->costo_servicio = costo_servicio;
    nueva->total = total;
    
    nueva->cantidad_detalles = cantidad_detalles;
    nueva->detalles = (DetalleFactura *)malloc(cantidad_detalles * sizeof(DetalleFactura));
    
    for (int i = 0; i < cantidad_detalles; i++) {
        nueva->detalles[i].identificador_asiento = asignarCadenaDinamica(detalles[i].identificador_asiento);
        nueva->detalles[i].costo = detalles[i].costo;
    }

    totalFacturas++;
}



// Menus

void gestionListaFacturas() {
    if (totalFacturas == 0) {
        printf("\nNo hay facturas registradas en el sistema.\n");
        return;
    }
    printf("\n========================================\n");
    printf("           LISTA DE FACTURAS            \n");
    printf("========================================\n");

    for (int i = 0; i < totalFacturas; i++) {
        Factura *fac = &listaFacturas[i];  
        printf("ID Factura: %d | Evento: %s | Fecha Compra: %s | Cliente: %s | Subtotal: %.2f\n", 
               fac->id_factura, 
               fac->nombre_evento, 
               fac->fecha_compra, 
               fac->nombre_cliente, 
               fac->subtotal);
    }
    printf("========================================\n");
}


