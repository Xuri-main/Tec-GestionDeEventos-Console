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
#include "../include/cadenas.h"

static Sitio *listaSitios = NULL;
static int totalSitios = 0;

// Memoria

void inicializarMemoriaSitios(int capacidad_inicial) {
    if (capacidad_inicial > 0) {
        listaSitios = (Sitio *)malloc(capacidad_inicial * sizeof(Sitio));
    } else {
        listaSitios = NULL;
    }
    totalSitios = 0;
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
        
        resetearSectores(i); 
    }

    free(listaSitios);
    listaSitios = NULL;
    totalSitios = 0;
    printf("[INFO] Memoria dinamica de sitios liberada correctamente.\n");
}

// Getters y Busqueda

int getCantidadSitios() {
    return totalSitios;
}

Sitio* getArregloSitios() {
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

Sitio* obtenerSitioPorNombre(const char *nombre) {
    for (int i = 0; i < totalSitios; i++) {
        if (strcmp(listaSitios[i].nombre, nombre) == 0) {
            return &listaSitios[i];
        }
    }
    return NULL;
}

// Agregar y Modificar

int agregarSitio(const char *nombre, const char *ubicacion, const char *web, int cant_sectores) {
    if (existeSitio(nombre)) {
        return 0;
    }

    Sitio *temp = (Sitio *)realloc(listaSitios, (totalSitios + 1) * sizeof(Sitio));
    
    if (temp == NULL) {
        printf("Oops! Falla de memoria al agregar sitio.\n");
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

int agregarSectorASitio(int indiceSitio, const char *nombreSector, char inicial, int cantidad) {
    Sitio *sitio = &listaSitios[indiceSitio];
    
    Sector *temp = (Sector *)realloc(sitio->sectores, (sitio->cantidad_sectores + 1) * sizeof(Sector));
    
    if (temp == NULL) {
        return 0;
    }
    
    sitio->sectores = temp;

    Sector *nuevoSector = &sitio->sectores[sitio->cantidad_sectores];
    nuevoSector->nombre = asignarCadenaDinamica(nombreSector);
    nuevoSector->inicial = inicial;
    nuevoSector->cantidad_espacios = cantidad;
    nuevoSector->precio = 0.0;     
    nuevoSector->recaudado = 0.0;
    
    nuevoSector->asientos = (Asiento *)malloc(cantidad * sizeof(Asiento));
    
    for (int i = 0; i < cantidad; i++) {
        nuevoSector->asientos[i].identificador = crearIdentificadorAsiento(inicial, i + 1);
        nuevoSector->asientos[i].vendido = 0; 
    }
    
    sitio->cantidad_sectores++;
    return 1;
}

char* crearIdentificadorAsiento(char inicial, int numero) {
    char buffer[20];
    sprintf(buffer, "%c%d", inicial, numero);
    return asignarCadenaDinamica(buffer);
}

void resetearSectores(int indiceSitio) {
    Sitio *sitio = &listaSitios[indiceSitio];
    
    if (sitio->sectores == NULL) {
        return;
    }

    for (int i = 0; i < sitio->cantidad_sectores; i++) {
        Sector *sec = &sitio->sectores[i];
        
        if (sec->nombre != NULL) {
            free(sec->nombre);
        }
        
        if (sec->asientos != NULL) {
            for (int j = 0; j < sec->cantidad_espacios; j++) {
                if (sec->asientos[j].identificador != NULL) {
                    free(sec->asientos[j].identificador);
                }
            }
            free(sec->asientos);
        }
    }
    
    free(sitio->sectores);
    sitio->sectores = NULL;
    sitio->cantidad_sectores = 0;
}

// Menus y Visualizacion

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
        limpiarBufferEntrada(); 

        switch(opcion) {
            case 1:
                mostrarSitios();
                break;
            case 2:
                printf("Ingrese la ruta del archivo de lote (ej: ../data/lote_sitios.txt): ");
                fgets(ruta, sizeof(ruta), stdin);
                removerSaltoLinea(ruta); 

                int agregados = cargarLoteSitiosDesdeRuta(ruta);
                
                if (agregados >= 0) {
                    if (existeSitio(" ") == 0) {
                        printf("\nProceso finalizado. Se agregaron %d sitios nuevos correctamente.\n", agregados);
                    }
                } else {
                    printf("\nOops! No se pudo abrir el archivo en la ruta especificada.\n");
                }
                break;
            case 3:
                break;
            default:
                printf("\nOpcion invalida.\n");
        }
    } while (opcion != 3);
}

void mostrarSitios() {
    if (totalSitios == 0) {
        printf("\nNo hay sitios de eventos registrados actualmente.\n");
        return;
    }

    printf("\n--- LISTA DE SITIOS DE EVENTOS ---\n");
    for (int i = 0; i < totalSitios; i++) {
        printf("%d. %s | Ubicacion: %s | Web: %s | Sectores: %d\n", i + 1, listaSitios[i].nombre, listaSitios[i].ubicacion, listaSitios[i].sitio_web, listaSitios[i].cantidad_sectores);
    }
    printf("----------------------------------\n");
}

void gestionEspaciosEventos() {
    if (totalSitios == 0) {
        printf("\nNo hay sitios registrados en el sistema. Debe registrar sitios primero.\n");
        return;
    }

    int indice_seleccionado;
    char nombre_sec[100];
    char inicial_sec;
    int cantidad_espacios;

    do {
        printf("\n========================================\n");
        printf("    GESTION DE ESPACIOS DE SITIOS       \n");
        printf("========================================\n");
        
        for (int i = 0; i < totalSitios; i++) {
            printf("%d. %s\n", i + 1, listaSitios[i].nombre);
        }
        
        printf("0. Volver al menu administrativo\n");
        printf("========================================\n");
        printf("Seleccione el sitio que desea gestionar (numero): ");
        scanf("%d", &indice_seleccionado);
        limpiarBufferEntrada();

        if (indice_seleccionado == 0) {
            break;
        }

        if (indice_seleccionado > 0) {
            if (indice_seleccionado <= totalSitios) {
                int indiceReal = indice_seleccionado - 1; 
                int subOpcion;

                do {
                    mostrarSectoresDeSitio(indiceReal);
                    printf("\n--- ACCIONES PARA ESTE SITIO ---\n");
                    printf("1. Agregar nuevo sector\n");
                    printf("2. Hacer reset de espacios (eliminar todos)\n");
                    printf("3. Volver a la seleccion de sitios\n");
                    printf("Seleccione una accion: ");
                    scanf("%d", &subOpcion);
                    limpiarBufferEntrada();

                    switch(subOpcion) {
                        case 1:
                            printf("Nombre del sector (ej. VIP): ");
                            fgets(nombre_sec, sizeof(nombre_sec), stdin);
                            removerSaltoLinea(nombre_sec);

                            printf("Inicial para los asientos (ej. V): ");
                            scanf("%c", &inicial_sec);
                            
                            printf("Cantidad de espacios: ");
                            scanf("%d", &cantidad_espacios);
                            limpiarBufferEntrada(); 

                            if (agregarSectorASitio(indiceReal, nombre_sec, inicial_sec, cantidad_espacios)) {
                                printf("\n¡Sector creado y asientos generados exitosamente!\n");
                            } else {
                                printf("\nOops! Falla de memoria al crear el sector.\n");
                            }
                            break;
                        case 2:
                            resetearSectores(indiceReal);
                            printf("\n¡Todos los sectores y espacios del sitio han sido eliminados!\n");
                            break;
                        case 3:
                            break;
                        default:
                            printf("Opcion invalida.\n");
                    }
                } while (subOpcion != 3);
            } else {
                printf("Seleccion invalida.\n");
            }
        } else {
            printf("Seleccion invalida.\n");
        }

    } while (indice_seleccionado != 0);
}

void mostrarSectoresDeSitio(int indiceSitio) {
    Sitio *sitio = &listaSitios[indiceSitio];
    printf("\n--- ESPACIOS DEL SITIO: %s ---\n", sitio->nombre);
    
    if (sitio->cantidad_sectores == 0) {
        printf("No hay sectores definidos para este sitio.\n");
        return;
    }
    
    for (int i = 0; i < sitio->cantidad_sectores; i++) {
        Sector *sec = &sitio->sectores[i];
        printf("Sector %d: %s | Cantidad: %d | Asientos: ", i + 1, sec->nombre, sec->cantidad_espacios);
        
        for (int j = 0; j < sec->cantidad_espacios; j++) {
            printf("%s ", sec->asientos[j].identificador);
        }
        printf("\n");
    }
}