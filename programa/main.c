#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>

void menuPrincipal();
void menuAdministrativo();
void menuGeneral();
int verificarLogin();

void gestionSitioEventos();
void gestionEspaciosEventos();
void gestionEventos();
void estadoEventos();
void listaFacturas();
void estadisticas();

void consultaPorEvento();
void compraDeBoletos();



int main()
{
    int opcionPrincipal;

    do
    {
        menuPrincipal();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcionPrincipal);

        switch(opcionPrincipal)
        {
            case 1:
                if(verificarLogin())
                {
                    menuAdministrativo();
                }
                else
                {
                    printf("\nOops! Acceso denegado.\n");
                }
                break;

            case 2:
                menuGeneral();
                break;

            case 3:
                printf("\nSaliendo del sistema...\n");
                break;

            default:
                printf("\nOops! Opcion invalida. Intente de nuevo.\n");
        }

    } while(opcionPrincipal != 3);

    return 0;
}

void menuPrincipal()
{
    printf("\n========================================\n");
    printf("             MENU PRINCIPAL             \n");
    printf("========================================\n");
    printf("1. Opciones Administrativas\n");
    printf("2. Opciones Generales\n");
    printf("3. Salir\n");
    printf("========================================\n");
}

int verificarLogin()
{

    printf("\n===== LOGIN EN PROCESO =====\n");
    
}

void menuAdministrativo()
{
    int opcionAdmin;

    do
    {
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

        switch(opcionAdmin)
        {
            case 1:
                gestionSitioEventos();
                break;

            case 2:
                gestionEspaciosEventos();
                break;

            case 3:
                gestionSitioEventos();
                break;

            case 4:
                estadoEventos();
                break;

            case 5:
                listaFacturas();
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

    } while(opcionAdmin != 7);
}

void menuGeneral()
{
    int opcionGeneral;

    do
    {
        printf("\n========================================\n");
        printf("         OPCIONES GENERALES             \n");
        printf("========================================\n");
        printf("1. Consulta por evento\n");
        printf("2. Compra de boletos\n");
        printf("3. Salir\n");
        printf("========================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcionGeneral);

        switch(opcionGeneral)
        {
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

    } while(opcionGeneral != 3);
}

/* lOGICA PARA DESPUES */

void gestionarSitiosEventos()
{}

void gestionEspaciosEventos()
{}

void gestionSitioEventos()
{}

void estadoEventos()
{}

void listaFacturas()
{}

void estadisticas()
{}

void consultaPorEvento()
{}

void compraDeBoletos()
{}