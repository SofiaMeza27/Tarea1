#ifndef COLA_H
#define COLA_H

#define reserMax 10
#define maxStr 50

typedef struct {
  char estudiante[maxStr];
} Reserva;

typedef struct {
  Reserva datos[reserMax];
  int frente, final, tamaño;
} Cola;

void inicializarCola(Cola *cola);
int colaVacia(Cola *cola);
int colaLlena(Cola *cola);
int encolar(Cola *cola, const char *estudiante);
int desencolar(Cola *cola, char *estudiante);

#endif