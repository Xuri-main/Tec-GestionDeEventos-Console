/**
 * Archivo: main.c
 * Descripcion: Contiene la funcion principal y los menus del sistema.
 * Autores: Emilio Funes R. , Ginger Rodríguez G. & Jareck Levell C.
 * Fecha: 28/03/2026
 */
#include <stdio.h>
#include <stdlib.h>
#include "include/archivos.h"
#include "include/login.h"
#include "include/sitios.h"
#include "include/eventos.h"
#include "include/facturas.h"
#include "include/cadenas.h"
#include "include/ventas.h"
#include "include/estadisticas.h"

// Menus
void menuPrincipal();
void menuAdministrativo();
void menuGeneral();

int main() {
    int opcionPrincipal;

    cargarTodosLosDatos();

    do {
        menuPrincipal();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcionPrincipal);
        limpiarBufferEntrada();

        switch(opcionPrincipal) {
            case 1:
                if (iniciarSesion()) {
                    printf("\n¡Acceso concedido!\n");
                    menuAdministrativo();
                } else {
                    printf("\nOops! Acceso denegado o archivo usuarios.txt no encontrado.\n");
                }
                break;

            case 2:
                menuGeneral();
                break;

            case 3:
                guardarTodosLosDatos();
                liberarMemoriaFacturas();
                liberarMemoriaEventos();
                liberarMemoriaSitios();
                printf("\nSaliendo del sistema...\n");
                break;

            default:
                printf("\nOops! Opcion invalida. Intente de nuevo.\n");
        }

    } while (opcionPrincipal != 3);

    return 0;
}

void menuPrincipal() {
    printf("\n========================================\n");
    printf("             MENU PRINCIPAL             \n");
    printf("========================================\n");
    printf("1. Opciones Administrativas\n");
    printf("2. Opciones Generales\n");
    printf("3. Salir\n");
    printf("========================================\n");
}

void menuAdministrativo() {
    int opcionAdmin;

    do {
        printf("\n========================================\n");
        printf("      OPCIONES ADMINISTRATIVAS          \n");
        printf("========================================\n");
        printf("1. Gestion de Sitios de Eventos\n");
        printf("2. Gestion de espacios sitio de eventos\n");
        printf("3. Gestion de Eventos\n");
        printf("4. Estado de evento\n");
        printf("5. Lista de facturas\n");
        printf("6. Estadisticas\n");
        printf("7. Volver\n");
        printf("========================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcionAdmin);
        limpiarBufferEntrada();

        switch(opcionAdmin) {
            case 1: 
                gestionSitioEventos(); 
                break;
            case 2: 
                gestionEspaciosEventos(); 
                break;
            case 3: 
                gestionEventos(); 
                break;
            case 4: 
                estadoEventos(); 
                break;
            case 5: 
                gestionListaFacturas(); 
                break;
            case 6: 
                estadisticas(); 
                break;
            case 7: 
                printf("\nRegresando al menu principal...\n"); 
                break;
            default: 
                printf("\nOpcion invalida. Intente de nuevo.\n");
        }

    } while (opcionAdmin != 7);
}

void menuGeneral() {
    int opcionGeneral;

    do {
        printf("\n========================================\n");
        printf("         OPCIONES GENERALES             \n");
        printf("========================================\n");
        printf("1. Consulta por evento\n");
        printf("2. Compra de boletos\n");
        printf("3. Salir\n");
        printf("========================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcionGeneral);
        limpiarBufferEntrada();

        switch(opcionGeneral) {
            case 1: 
                consultaPorEvento(); 
                break;
            case 2: 
                compraDeBoletos(); 
                break;
            case 3: 
                printf("\nRegresando al menu principal...\n"); 
                break;
            default: 
                printf("\nOpcion invalida. Intente de nuevo.\n");
        }

    } while (opcionGeneral != 3);
}

