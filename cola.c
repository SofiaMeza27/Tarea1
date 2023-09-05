#include "cola.h"
#include <stdio.h>
#include <string.h>

void inicializarCola(Cola *cola) {
  cola->frente = cola->final = -1;
  cola->tamaño = 0;
}

int colaVacia(Cola *cola) { return cola->tamaño == 0; }

int colaLlena(Cola *cola) { return cola->tamaño == reserMax; }

int encolar(Cola *cola, const char *estudiante) {
  if (colaLlena(cola)) {
    printf("Cola de reservas llena, no se pueden agregar más reservas.\n");
    return 0; // Indicar que no se pudo agregar
  }

  if (colaVacia(cola)) {
    cola->frente = cola->final = 0;
  } else {
    cola->final = (cola->final + 1) % reserMax;
  }

  strcpy(cola->datos[cola->final].estudiante, estudiante);
  cola->tamaño++;
  return 1; // Indicar que se agregó con éxito
}

int desencolar(Cola *cola, char *estudiante) {
  if (colaVacia(cola)) {
    printf("Cola de reservas vacía.\n");
    return 0; // Indicar que no se pudo quitar
  }

  strcpy(estudiante, cola->datos[cola->frente].estudiante);
  cola->tamaño--;

  if (cola->frente == cola->final) {
    // Último elemento en la cola
    cola->frente = cola->final = -1;
  } else {
    cola->frente = (cola->frente + 1) % reserMax;
  }

  return 1; // Indicar que se quitó con éxito
}