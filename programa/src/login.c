/**
 * Archivo: login.c
 * Descripcion: Implementacion de la logica de autenticacion en texto plano.
 * Autores: Ginger Rodríguez G.
 * Fecha de creación: 25/03/2026
 */

#include <stdio.h>
#include <string.h>
#include "../include/login.h"
#include "../include/archivos.h"

/**
 * Objetivo:
 * Verificar el acceso del usuario
 *
 * Entradas:
 * - Usuario ingresado por teclado
 * - Contrasena ingresada por teclado
 *
 * Salida:
 * - Retorna 1 si las credenciales son correctas
 * - Retorna 0 si las credenciales son incorrectas
 *
 * Restricciones:
 * - Deben existir credenciales de administrador guardadas.
 */
int iniciarSesion() {
    char usuario_ingresado[50];
    char clave_ingresada[50];
    char usuario_guardado[50];
    char clave_guardada[50];

    printf("\n========================================\n");
    printf("         INICIO DE SESION ADMIN         \n");
    printf("========================================\n");
    printf("Usuario: ");
    scanf("%49s", usuario_ingresado);
    printf("Contrasena: ");
    scanf("%49s", clave_ingresada);

    if (obtenerCredencialesAdmin(usuario_guardado, clave_guardada)) {
        if (strcmp(usuario_ingresado, usuario_guardado) == 0 && 
            strcmp(clave_ingresada, clave_guardada) == 0) {
            return 1; // Exito
        }
    }
    
    return 0; // Fallo
}