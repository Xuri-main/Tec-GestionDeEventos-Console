/**
 * Archivo: ventas.c
 * Descripcion: Implementacion de funciones para la gestion de ventas y consultas.
 * Autores: Emilio Funes R. , Ginger Rodríguez G. & Jareck Levell C.
 * Fecha: 28/03/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/ventas.h"
#include "../include/eventos.h"
#include "../include/sitios.h"
#include "../include/cadenas.h"
#include "../include/facturas.h"


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

void compraDeBoletos() {
    if (getCantidadEventos() == 0) {
        printf("\nNo hay eventos registrados en el sistema.\n");
        return;
    }

    time_t tiempo_actual;
    struct tm *info_tiempo;
    char fecha_hoy[20];

    time(&tiempo_actual);
    info_tiempo = localtime(&tiempo_actual);
    sprintf(fecha_hoy, "%02d/%02d/%04d", info_tiempo->tm_mday, info_tiempo->tm_mon + 1, info_tiempo->tm_year + 1900);

    int total_eventos = getCantidadEventos();
    Evento *arreglo_eventos = getArregloEventos();
    
    int *indices_validos = (int *)malloc(total_eventos * sizeof(int));
    int cantidad_validos = 0;

    for (int i = 0; i < total_eventos; i++) {
        if (compararFechas(arreglo_eventos[i].fecha, fecha_hoy)) {
            indices_validos[cantidad_validos] = i;
            cantidad_validos++;
        }
    }

    if (cantidad_validos == 0) {
        printf("\nNo hay eventos futuros disponibles para compra.\n");
        free(indices_validos);
        return;
    }

    printf("\n========================================\n");
    printf("         COMPRA DE BOLETOS              \n");
    printf("========================================\n");
    
    for (int i = 0; i < cantidad_validos; i++) {
        Evento *ev = &arreglo_eventos[indices_validos[i]];
        printf("%d. %s - %s\n", i + 1, ev->nombre, ev->fecha);
    }
    
    int seleccion_evento;
    printf("0. Cancelar compra\n");
    printf("========================================\n");
    printf("Seleccione el evento al que desea asistir: ");
    scanf("%d", &seleccion_evento);
    limpiarBufferEntrada();

    if (seleccion_evento == 0) {
        free(indices_validos);
        return;
    }

    if (seleccion_evento < 1) {
        printf("Seleccion invalida.\n");
        free(indices_validos);
        return;
    }

    if (seleccion_evento > cantidad_validos) {
        printf("Seleccion invalida.\n");
        free(indices_validos);
        return;
    }

    Evento *ev_seleccionado = &arreglo_eventos[indices_validos[seleccion_evento - 1]];
    
    printf("\n--- ASIENTOS DISPONIBLES ---\n");
    
    for (int i = 0; i < ev_seleccionado->cantidad_sectores_evento; i++) {
        Sector *sec = &ev_seleccionado->sectores_evento[i];
        printf("> Sector %s (Precio: %.2f)\n  Disponibles: ", sec->nombre, sec->precio);
        
        for (int j = 0; j < sec->cantidad_espacios; j++) {
            if (sec->asientos[j].vendido == 0) {
                printf("%s ", sec->asientos[j].identificador);
            }
        }
        printf("\n\n");
    }
    int cantidad_comprar;
    printf("Ingrese la cantidad de asientos que desea comprar: ");
    scanf("%d", &cantidad_comprar);
    limpiarBufferEntrada();

    if (cantidad_comprar <= 0) {
        printf("Cantidad invalida.\n");
        free(indices_validos);
        return;
    }

    DetalleFactura *detalles_temp = (DetalleFactura *)malloc(cantidad_comprar * sizeof(DetalleFactura));
    float subtotal = 0.0;
    char asiento_ingresado[20];

    for (int i = 0; i < cantidad_comprar; i++) {
        printf("Ingrese el identificador del asiento %d (Ej: V1): ", i + 1);
        fgets(asiento_ingresado, sizeof(asiento_ingresado), stdin);
        removerSaltoLinea(asiento_ingresado);

        int estado_busqueda = 0; 
        
        for (int j = 0; j < ev_seleccionado->cantidad_sectores_evento; j++) {
            Sector *sec = &ev_seleccionado->sectores_evento[j];
            
            for (int k = 0; k < sec->cantidad_espacios; k++) {
                if (strcmp(sec->asientos[k].identificador, asiento_ingresado) == 0) {
                    if (sec->asientos[k].vendido == 0) {
                        sec->asientos[k].vendido = 1;
                        sec->recaudado = sec->recaudado + sec->precio;
                        
                        detalles_temp[i].identificador_asiento = asignarCadenaDinamica(asiento_ingresado);
                        detalles_temp[i].costo = sec->precio;
                        subtotal = subtotal + sec->precio;
                        
                        estado_busqueda = 1; 
                    } else {
                        estado_busqueda = 2; 
                    }
                    break;
                }
            }
            if (estado_busqueda > 0) {
                break;
            }
        }

        if (estado_busqueda == 0) {
            printf("[ERROR] El asiento no existe. Intente de nuevo.\n");
            i--; 
        } else {
            if (estado_busqueda == 2) {
                printf("[ERROR] El asiento ya esta vendido. Elija otro.\n");
                i--; 
            }
        }
    }

    char cedula[50];
    char nombre_cliente[100];

    printf("\n--- DATOS DEL COMPRADOR ---\n");
    printf("Ingrese su cedula: ");
    fgets(cedula, sizeof(cedula), stdin);
    removerSaltoLinea(cedula);

    printf("Ingrese su nombre completo: ");
    fgets(nombre_cliente, sizeof(nombre_cliente), stdin);
    removerSaltoLinea(nombre_cliente);

    float costo_servicio = subtotal * 0.05;
    float total_final = subtotal + costo_servicio;

    agregarFactura(fecha_hoy, cedula, nombre_cliente, ev_seleccionado->nombre, ev_seleccionado->productora, ev_seleccionado->sitio_base->nombre, ev_seleccionado->fecha, cantidad_comprar, detalles_temp, subtotal, costo_servicio, total_final);

    int ultimo_id = getCantidadFacturas();

    printf("\n========================================\n");
    printf("              FACTURA #%d               \n", ultimo_id);
    printf("========================================\n");
    printf("Fecha de Compra: %s\n", fecha_hoy);
    printf("Cliente: %s | Cedula: %s\n", nombre_cliente, cedula);
    printf("Evento: %s | Productora: %s\n", ev_seleccionado->nombre, ev_seleccionado->productora);
    printf("Sitio: %s | Fecha Evento: %s\n", ev_seleccionado->sitio_base->nombre, ev_seleccionado->fecha);
    printf("----------------------------------------\n");
    printf("DETALLE DE ASIENTOS:\n");
 
    for (int i = 0; i < cantidad_comprar; i++) {
        printf(" - Asiento %s : %.2f\n", detalles_temp[i].identificador_asiento, detalles_temp[i].costo);
    } 
    printf("----------------------------------------\n");
    printf("Subtotal:       %.2f\n", subtotal);
    printf("Costo Servicio: %.2f (5%%)\n", costo_servicio);
    printf("TOTAL:          %.2f\n", total_final);
    printf("========================================\n");
    printf("Compra realizada con exito!\n");

    for (int i = 0; i < cantidad_comprar; i++) {
        free(detalles_temp[i].identificador_asiento);
    }
    free(detalles_temp);
    free(indices_validos);
}