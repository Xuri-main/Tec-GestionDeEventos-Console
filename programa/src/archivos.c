/**
 * Archivo: archivos.c
 * Descripcion: Implementacion de la lectura y escritura de archivos planos.
 * Autores: Emilio Funes R , Ginger Rodríguez G. & Jareck Levell C.
 * Fecha: 28/03/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/archivos.h"
#include "../include/sitios.h" 
#include "../include/eventos.h"
#include "../include/cadenas.h"
#include "../include/facturas.h"

// Generales

void cargarTodosLosDatos() {
    printf("[INFO] Cargando datos desde archivos...\n");
    cargarSitios();
    cargarEventos();
    cargarFacturas();
}

void guardarTodosLosDatos() {
    printf("[INFO] Guardando todos los datos...\n");
    guardarSitios();
    guardarEventos();
    guardarFacturas();
}

int obtenerCredencialesAdmin(char *usuario, char *clave) {
    FILE *archivo = fopen(RUTA_USUARIOS, "r");
    
    if (archivo == NULL) {
        return 0;
    }

    if (fscanf(archivo, "%49[^,],%49s", usuario, clave) == 2) {
        fclose(archivo);
        return 1;
    }
    
    fclose(archivo);
    return 0;
}

// Sitios

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
                removerSaltoLinea(linea);
                
                char *nombre = strtok(linea, ",");
                char *ubi = strtok(NULL, ",");
                char *web = strtok(NULL, ",");
                char *cant_sec_str = strtok(NULL, ",");
                
                if (nombre != NULL) {
                    if (ubi != NULL) {
                        if (web != NULL) {
                            if (cant_sec_str != NULL) {
                                if (agregarSitio(nombre, ubi, web, 0)) {
                                    int indiceNuevoSitio = getCantidadSitios() - 1;
                                    int cant_sectores_guardados = atoi(cant_sec_str);

                                    for (int j = 0; j < cant_sectores_guardados; j++) {
                                        if (fgets(linea, sizeof(linea), archivo)) {
                                            removerSaltoLinea(linea);
                                            char *nom_sec = strtok(linea, ",");
                                            char *ini_sec_str = strtok(NULL, ",");
                                            char *cant_esp_str = strtok(NULL, ",");
                                            
                                            if (nom_sec != NULL) {
                                                if (ini_sec_str != NULL) {
                                                    if (cant_esp_str != NULL) {
                                                        agregarSectorASitio(indiceNuevoSitio, nom_sec, ini_sec_str[0], atoi(cant_esp_str));
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    fclose(archivo);
}

void guardarSitios() {
    FILE *archivo = fopen(RUTA_SITIOS, "w");
    
    if (archivo == NULL) {
        return;
    }

    int cantidad = getCantidadSitios();
    Sitio *arreglo = getArregloSitios();

    fprintf(archivo, "%d\n", cantidad);
    
    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%s,%s,%s,%d\n", arreglo[i].nombre, arreglo[i].ubicacion, arreglo[i].sitio_web, arreglo[i].cantidad_sectores);
        
        for (int j = 0; j < arreglo[i].cantidad_sectores; j++) {
            Sector *sec = &arreglo[i].sectores[j];
            fprintf(archivo, "%s,%c,%d\n", sec->nombre, sec->inicial, sec->cantidad_espacios);
        }
    }
    
    fclose(archivo);
}

int cargarLoteSitiosDesdeRuta(const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    
    if (archivo == NULL) {
        return 0; 
    }

    char linea[256];
    int agregados = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        removerSaltoLinea(linea);
        
        char *nombre = strtok(linea, ",");
        char *ubi = strtok(NULL, ",");
        char *web = strtok(NULL, ",");

        if (nombre != NULL) {
            if (ubi != NULL) {
                if (web != NULL) {
                    if (ubi[0] == ' ') {
                        ubi++; 
                    }
                    if (web[0] == ' ') {
                        web++;
                    }
                    
                    if (agregarSitio(nombre, ubi, web, 0)) {
                        agregados++;
                    }
                }
            }
        }
    }
    
    fclose(archivo);
    return agregados;
}

// Eventos

void cargarEventos() {
    FILE *archivo = fopen(RUTA_EVENTOS, "r");
    
    if (archivo == NULL) {
        inicializarMemoriaEventos(0);
        return;
    }

    int cantidad_eventos;
    if (fscanf(archivo, "%d\n", &cantidad_eventos) == 1) {
        inicializarMemoriaEventos(0); 

        char linea[512];
        for (int i = 0; i < cantidad_eventos; i++) {
            if (fgets(linea, sizeof(linea), archivo)) {
                removerSaltoLinea(linea);
                
                char *nombre = strtok(linea, ",");
                char *prod = strtok(NULL, ",");
                char *fecha = strtok(NULL, ",");
                char *nombre_sitio = strtok(NULL, ",");

                if (nombre != NULL) {
                    if (prod != NULL) {
                        if (fecha != NULL) {
                            if (nombre_sitio != NULL) {
                                Sitio *sitio_base = obtenerSitioPorNombre(nombre_sitio);
                                
                                if (sitio_base != NULL) {
                                    Evento *nuevoEv = agregarEvento(nombre, prod, fecha, sitio_base);
                                    
                                    if (nuevoEv != NULL) {
                                        for (int j = 0; j < nuevoEv->cantidad_sectores_evento; j++) {
                                            Sector *sec = &nuevoEv->sectores_evento[j];
                                            
                                            if (fgets(linea, sizeof(linea), archivo)) {
                                                removerSaltoLinea(linea);
                                                char *precio_str = strtok(linea, ",");
                                                char *recau_str = strtok(NULL, ",");
                                                
                                                if (precio_str != NULL) {
                                                    if (recau_str != NULL) {
                                                        sec->precio = atof(precio_str);
                                                        sec->recaudado = atof(recau_str);
                                                    }
                                                }
                                            }

                                            if (fgets(linea, sizeof(linea), archivo)) {
                                                removerSaltoLinea(linea);
                                                for (int k = 0; k < sec->cantidad_espacios; k++) {
                                                    if (linea[k] != '\0') {
                                                        sec->asientos[k].vendido = linea[k] - '0';
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    fclose(archivo);
}

void guardarEventos() {
    FILE *archivo = fopen(RUTA_EVENTOS, "w");
    
    if (archivo == NULL) {
        return;
    }

    int cantidad = getCantidadEventos();
    Evento *arreglo = getArregloEventos();

    fprintf(archivo, "%d\n", cantidad);
    
    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%s,%s,%s,%s\n", arreglo[i].nombre, arreglo[i].productora, arreglo[i].fecha, arreglo[i].sitio_base->nombre); 
        
        for (int j = 0; j < arreglo[i].cantidad_sectores_evento; j++) {
            Sector *sec = &arreglo[i].sectores_evento[j];
            
            fprintf(archivo, "%.2f,%.2f\n", sec->precio, sec->recaudado);
            
            for (int k = 0; k < sec->cantidad_espacios; k++) {
                fprintf(archivo, "%d", sec->asientos[k].vendido);
            }
            fprintf(archivo, "\n");
        }
    }
    
    fclose(archivo);
}

// Facturas

void cargarFacturas() {
    FILE *archivo = fopen(RUTA_FACTURAS, "r");
    
    if (archivo == NULL) {
        inicializarMemoriaFacturas(0);
        return;
    }

    int cantidad;
    if (fscanf(archivo, "%d\n", &cantidad) == 1) {
        inicializarMemoriaFacturas(0);
        
        // Leer cada factura. Linea estatica.
        char linea[512];
        for (int i = 0; i < cantidad; i++) {
            if (fgets(linea, sizeof(linea), archivo)) {
                removerSaltoLinea(linea);
                
                char *f_compra = strtok(linea, ",");
                char *cedula = strtok(NULL, ",");
                char *nom_cli = strtok(NULL, ",");
                char *nom_ev = strtok(NULL, ",");
                char *prod = strtok(NULL, ",");
                char *sitio = strtok(NULL, ",");
                char *f_ev = strtok(NULL, ",");
                
                char *sub_str = strtok(NULL, ",");
                char *serv_str = strtok(NULL, ",");
                char *tot_str = strtok(NULL, ",");
                char *cant_det_str = strtok(NULL, ",");

                int valido = 1;
                if (f_compra == NULL) valido = 0;
                if (cedula == NULL) valido = 0;
                if (nom_cli == NULL) valido = 0;
                if (nom_ev == NULL) valido = 0;
                if (prod == NULL) valido = 0;
                if (sitio == NULL) valido = 0;
                if (f_ev == NULL) valido = 0;
                if (sub_str == NULL) valido = 0;
                if (serv_str == NULL) valido = 0;
                if (tot_str == NULL) valido = 0;
                if (cant_det_str == NULL) valido = 0;

                if (valido == 1) {
                    int cant_detalles = atoi(cant_det_str);
                    DetalleFactura *detalles_temp = (DetalleFactura *)malloc(cant_detalles * sizeof(DetalleFactura));
                    
                    for (int j = 0; j < cant_detalles; j++) {
                        if (fgets(linea, sizeof(linea), archivo)) {
                            removerSaltoLinea(linea);
                            char *id_asiento = strtok(linea, ",");
                            char *costo_str = strtok(NULL, ",");
                            
                            if (id_asiento != NULL) {
                                if (costo_str != NULL) {
                                    detalles_temp[j].identificador_asiento = asignarCadenaDinamica(id_asiento);
                                    detalles_temp[j].costo = atof(costo_str);
                                }
                            }
                        }
                    }
                    

                    agregarFactura(f_compra, cedula, nom_cli, nom_ev, prod, sitio, f_ev, cant_detalles, detalles_temp, atof(sub_str), atof(serv_str), atof(tot_str));
                    
                    for (int j = 0; j < cant_detalles; j++) {
                        if (detalles_temp[j].identificador_asiento != NULL) {
                            free(detalles_temp[j].identificador_asiento);
                        }
                    }
                    free(detalles_temp);
                }
            }
        }
    }
    

    fclose(archivo);
}

void guardarFacturas() {
   
    FILE *archivo = fopen(RUTA_FACTURAS, "w");
    if (archivo == NULL) {
        return;
    }
    int cantidad = getCantidadFacturas();
    Factura *arreglo = getArregloFacturas();

    fprintf(archivo, "%d\n", cantidad);
    for (int i = 0; i < cantidad; i++) {
        Factura *fac = &arreglo[i]; 
        fprintf(archivo, "%s,%s,%s,%s,%s,%s,%s,%.2f,%.2f,%.2f,%d\n", 
                fac->fecha_compra, 
                fac->cedula_cliente, 
                fac->nombre_cliente, 
                fac->nombre_evento, 
                fac->productora, 
                fac->sitio_evento, 
                fac->fecha_evento, 
                fac->subtotal, 
                fac->costo_servicio, 
                fac->total, 
                fac->cantidad_detalles);
    


        for (int j = 0; j < fac->cantidad_detalles; j++) {
            fprintf(archivo, "%s,%.2f\n", fac->detalles[j].identificador_asiento, fac->detalles[j].costo);
        }
    }

    fclose(archivo);
}


