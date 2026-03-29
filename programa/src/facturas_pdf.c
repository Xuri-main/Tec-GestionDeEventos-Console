/**
 * Archivo: facturas_pdf.c
 * Descripcion: Este archivo contiene las implementaciones para generación de archivos PDF, para las facturas.
 * Autores: Jareck Levell C.
 * Fecha: 28/03/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/facturas_pdf.h"
#include "../include/pdfgen.h"

void generarFacturaPDF(Factura *fac) {
    if (fac == NULL) {
        return;
    }

    char ruta_pdf[150];
    sprintf(ruta_pdf, "../output/Factura_%d.pdf", fac->id_factura);

    struct pdf_info info = {
        .creator = "Sistema de Gestion de Eventos",
        .producer = "TEC - Proyecto 1",
        .title = "Factura de Compra",
        .author = "Equipo de Desarrollo",
        .subject = "Comprobante de Boletos",
        .date = "Hoy"
    };

    struct pdf_doc *pdf = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, &info);
    
    if (pdf == NULL) {
        printf("\n[ERROR] No se pudo inicializar el generador PDF.\n");
        return;
    }

    pdf_set_font(pdf, "Helvetica");
    pdf_append_page(pdf);

    int pos_y = 800;

    pdf_add_text(pdf, NULL, "SISTEMA DE GESTION DE EVENTOS TEC", 18, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 30;

    char buffer[200];
    
    sprintf(buffer, "Factura #%d", fac->id_factura);
    pdf_add_text(pdf, NULL, buffer, 14, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 30;

    sprintf(buffer, "Fecha de Compra: %s", fac->fecha_compra);
    pdf_add_text(pdf, NULL, buffer, 12, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 20;

    sprintf(buffer, "Cliente: %s", fac->nombre_cliente);
    pdf_add_text(pdf, NULL, buffer, 12, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 20;

    sprintf(buffer, "Cedula: %s", fac->cedula_cliente);
    pdf_add_text(pdf, NULL, buffer, 12, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 40;

    pdf_add_text(pdf, NULL, "DETALLES DEL EVENTO", 14, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 20;

    sprintf(buffer, "Evento: %s", fac->nombre_evento);
    pdf_add_text(pdf, NULL, buffer, 12, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 20;

    sprintf(buffer, "Productora: %s", fac->productora);
    pdf_add_text(pdf, NULL, buffer, 12, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 20;

    sprintf(buffer, "Sitio: %s", fac->sitio_evento);
    pdf_add_text(pdf, NULL, buffer, 12, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 20;

    sprintf(buffer, "Fecha del Evento: %s", fac->fecha_evento);
    pdf_add_text(pdf, NULL, buffer, 12, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 40;

    pdf_add_text(pdf, NULL, "ASIENTOS ADQUIRIDOS", 14, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 20;

    for (int i = 0; i < fac->cantidad_detalles; i++) {
        sprintf(buffer, "- Asiento %s : %.2f", fac->detalles[i].identificador_asiento, fac->detalles[i].costo);
        pdf_add_text(pdf, NULL, buffer, 12, 50, pos_y, PDF_BLACK);
        pos_y = pos_y - 15;
        
        if (pos_y < 100) {
            pdf_append_page(pdf);
            pos_y = 800;
        }
    }

    pos_y = pos_y - 30;
    
    if (pos_y < 150) {
        pdf_append_page(pdf);
        pos_y = 800;
    }

    sprintf(buffer, "Subtotal: %.2f", fac->subtotal);
    pdf_add_text(pdf, NULL, buffer, 12, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 15;

    sprintf(buffer, "Costo por Servicio (5%%): %.2f", fac->costo_servicio);
    pdf_add_text(pdf, NULL, buffer, 12, 50, pos_y, PDF_BLACK);
    pos_y = pos_y - 15;

    sprintf(buffer, "TOTAL FINAL: %.2f", fac->total);
    pdf_add_text(pdf, NULL, buffer, 14, 50, pos_y, PDF_BLACK);

    pdf_save(pdf, ruta_pdf);
    pdf_destroy(pdf);

    printf("[INFO] Se ha generado una copia en PDF: %s\n", ruta_pdf);
}

