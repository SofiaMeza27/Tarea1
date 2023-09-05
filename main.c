#include "cola.h" // Incluimos el archivo de encabezado de la cola
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONGITUD_CADENA 50
#define MAX_LIBROS 100
#define MAX_RESERVAS 10

typedef struct {
  char titulo[MAX_LONGITUD_CADENA];
  char autor[MAX_LONGITUD_CADENA];
  char genero[MAX_LONGITUD_CADENA];
  char isbn[MAX_LONGITUD_CADENA];
  char ubicacion[MAX_LONGITUD_CADENA];
  char estado[MAX_LONGITUD_CADENA];
  char reservas[MAX_RESERVAS][MAX_LONGITUD_CADENA];
  int num_reservas;
} Libro;

Libro biblioteca[MAX_LIBROS];
int num_libros = 0;

// Declaraciones de funciones
void registrarLibro();
void mostrarDatosLibro();
void mostrarTodosLosLibros();
void reservarLibro(Cola *colaReservas);
void cancelarReserva(Cola *colaReservas);
void tomarLibroPrestado(Cola *colaReservas);
void devolverLibro(Cola *colaReservas);
void mostrarLibrosPrestados(Cola *colaReservas);
void importarLibros();
void exportarLibros();

int main() {
  int opcion;

  Cola colaReservas;
  inicializarCola(&colaReservas);

  do {
    printf("\nBienvenido a la bilbioteca!\n\n");
    printf("Opcion 1 para registrar libros\n");
    printf("Opcion 2 para ver datos de libros\n");
    printf("Opcion 3 para mostrar todos los libros registrados\n");
    printf("Opcion 4 para reservar un libro\n");
    printf("Opcion 5 para cancelar una reservacion\n");
    printf("Opcion 6 para validar una reserva\n");
    printf("Opcion 7 para devolver un libro\n");
    printf("Opcion 8 para mostrar todos los libros prestados\n");
    printf("Opcion 9 importar libros desde un archivo .csv\n");
    printf("Opcion 10 para exportar los libros archivo .csv\n");
    printf("Opcion 0 para finalizar\n\n");
    printf("Ingrese una opcion: ");

    int resultado = scanf("%d", &opcion);

    if (resultado != 1) {
      printf("Opcion no valida!\n");
      break;
    }

    switch (opcion) {
    case 1:
      registrarLibro();
      break;
    case 2:
      mostrarDatosLibro();
      break;
    case 3:
      mostrarTodosLosLibros();
      break;
    case 4:
      reservarLibro(&colaReservas);
      break;
    case 5:
      cancelarReserva(&colaReservas);
      break;
    case 6:
      tomarLibroPrestado(&colaReservas);
      break;
    case 7:
      devolverLibro(&colaReservas);
      break;
    case 8:
      mostrarLibrosPrestados(&colaReservas);
      break;
    case 9:
      importarLibros();
      break;
    case 10:
      exportarLibros();
      break;
    case 0:
      printf("Vuelva pronto!\n");
      break;
    default:
      printf("\nIngrese una opcion valida.\n");
    }
  } while (opcion != 0);

  return 0;
}

void registrarLibro() {
  if (num_libros >= MAX_LIBROS) {
    printf("No es posible registrar mas libros.\n");
    return;
  }

  Libro nuevoLibro;

  while (getchar() != '\n')
    ;

  printf("\nIngrese titulo del libro: ");
  fgets(nuevoLibro.titulo, sizeof(nuevoLibro.titulo), stdin);
  nuevoLibro.titulo[strcspn(nuevoLibro.titulo, "\n")] = '\0';

  printf("Ingrese autor del libro: ");
  fgets(nuevoLibro.autor, sizeof(nuevoLibro.autor), stdin);
  nuevoLibro.autor[strcspn(nuevoLibro.autor, "\n")] = '\0';

  printf("Ingrese genero del libro: ");
  fgets(nuevoLibro.genero, sizeof(nuevoLibro.genero), stdin);
  nuevoLibro.genero[strcspn(nuevoLibro.genero, "\n")] = '\0';

  printf("Ingrese ISBN del libro: ");
  fgets(nuevoLibro.isbn, sizeof(nuevoLibro.isbn), stdin);
  nuevoLibro.isbn[strcspn(nuevoLibro.isbn, "\n")] = '\0';

  printf("Ingrese ubicacion de almacenamiento: ");
  fgets(nuevoLibro.ubicacion, sizeof(nuevoLibro.ubicacion), stdin);
  nuevoLibro.ubicacion[strcspn(nuevoLibro.ubicacion, "\n")] = '\0';

  strcpy(nuevoLibro.estado, "Disponible");
  nuevoLibro.num_reservas = 0;

  biblioteca[num_libros++] = nuevoLibro;

  printf("Libro registrado con exito\n");
}

void mostrarDatosLibro() {

  char titulo[MAX_LONGITUD_CADENA];
  char autor[MAX_LONGITUD_CADENA];

  printf("Ingrese titulo del libro: ");
  scanf(" %[^\n]", titulo);

  printf("Ingrese autor del libro: ");
  scanf(" %[^\n]", autor);

  for (int i = 0; i < num_libros; i++) {
    if (strcmp(biblioteca[i].titulo, titulo) == 0 &&
        strcmp(biblioteca[i].autor, autor) == 0) {
      printf("Titulo: %s\n", biblioteca[i].titulo);
      printf("Autor: %s\n", biblioteca[i].autor);
      printf("Genero: %s\n", biblioteca[i].genero);
      printf("ISBN: %s\n", biblioteca[i].isbn);
      printf("Ubicacion: %s\n", biblioteca[i].ubicacion);
      printf("Estado: %s\n", biblioteca[i].estado);
      if (biblioteca[i].num_reservas > 0) {
        printf("Reservas:\n");
        for (int j = 0; j < biblioteca[i].num_reservas; j++) {
          printf("  %s\n", biblioteca[i].reservas[j]);
        }
      }
      return;
    }
  }

  printf("Libro no disponible.\n");
}

void mostrarTodosLosLibros() {
  if (num_libros == 0) {
    printf("No hay libros registrados.\n");
    return;
  }

  printf("Lista de todos los libros:\n");
  for (int i = 0; i < num_libros; i++) {
    printf("%s de %s\n", biblioteca[i].titulo, biblioteca[i].autor);
  }
}

void reservarLibro(Cola *colaReservas) {
  char titulo[MAX_LONGITUD_CADENA];
  char autor[MAX_LONGITUD_CADENA];
  char estudiante[MAX_LONGITUD_CADENA];

  printf("Ingrese titulo del libro: ");
  scanf(" %[^\n]", titulo);

  while (getchar() != '\n')
    ;

  printf("Ingrese autor del libro: ");
  scanf(" %[^\n]", autor);

  printf("Nombre del estudiante que reservara: ");
  scanf(" %[^\n]", estudiante);

  for (int i = 0; i < num_libros; i++) {
    if (strcmp(biblioteca[i].titulo, titulo) == 0 &&
        strcmp(biblioteca[i].autor, autor) == 0) {
      if (strcmp(biblioteca[i].estado, "Disponible") == 0) {
        strcpy(biblioteca[i].estado, "Reservado");
        encolar(colaReservas, estudiante);
        printf("libro reservado exitosamente\n");

      } else if (strcmp(biblioteca[i].estado, "Reservado") == 0 ||
                 strcmp(biblioteca[i].estado, "Prestado") == 0) {
        encolar(colaReservas, estudiante);
        printf("libro reservado exitosamente\n");
      } else {
        printf("El libro no puede ser reservado.\n");
      }
      return;
    }
  }

  printf("Libro no disponible.\n");
}

void cancelarReserva(Cola *colaReservas) {
  char titulo[MAX_LONGITUD_CADENA];
  char autor[MAX_LONGITUD_CADENA];
  char estudiante[MAX_LONGITUD_CADENA];

  printf("Ingrese titulo del libro: ");
  scanf(" %[^\n]", titulo);
  while (getchar() != '\n')
    ;

  printf("Ingrese autor del libro: ");
  scanf(" %[^\n]", autor);

  printf("Nombre del estudiante que reservo: ");
  scanf(" %[^\n]", estudiante);

  for (int i = 0; i < num_libros; i++) {
    if (strcmp(biblioteca[i].titulo, titulo) == 0 &&
        strcmp(biblioteca[i].autor, autor) == 0) {
      if (!colaVacia(colaReservas)) {
        char estudianteReservado[MAX_LONGITUD_CADENA];
        desencolar(colaReservas, estudianteReservado);

        if (strcmp(estudianteReservado, estudiante) == 0) {
          printf("Reseva cancelada con exito\n");
        } else {

          encolar(colaReservas, estudianteReservado);
          printf("No se encontro la reservacion\n");
        }
      } else {
        printf("No se encontro la reservacion\n");
      }
      return;
    }
  }

  printf("Libro no disponible.\n");
}

void tomarLibroPrestado(Cola *colaReservas) {
  char titulo[MAX_LONGITUD_CADENA];
  char autor[MAX_LONGITUD_CADENA];
  char estudiante[MAX_LONGITUD_CADENA];

  printf("Ingrese titulo del libro: ");
  scanf(" %[^\n]", titulo);
  while (getchar() != '\n')
    ;

  printf("Ingrese autor del libro: ");
  scanf(" %[^\n]", autor);

  printf("Nombre del estudiante que reservo: ");
  scanf(" %[^\n]", estudiante);

  for (int i = 0; i < num_libros; i++) {
    if (strcmp(biblioteca[i].titulo, titulo) == 0 &&
        strcmp(biblioteca[i].autor, autor) == 0) {
      if (strcmp(biblioteca[i].estado, "Disponible") == 0) {
        strcpy(biblioteca[i].estado, "Prestado");
        printf("Libro retirado exitosamente\n");
      } else if (strcmp(biblioteca[i].estado, "Reservado") == 0) {
        char estudianteReservado[MAX_LONGITUD_CADENA];
        desencolar(colaReservas, estudianteReservado);

        if (strcmp(estudianteReservado, estudiante) == 0) {
          strcpy(biblioteca[i].estado, "Prestado");
          printf("Libro retirado exitosamente\n");
        } else {

          encolar(colaReservas, estudianteReservado);
          printf("El libro no puede ser retirado\n");
        }
      } else {
        printf("El libro no puede ser prestado.\n");
      }
      return;
    }
  }

  printf("Libro no disponible\n");
}

void devolverLibro(Cola *colaReservas) {
  char titulo[MAX_LONGITUD_CADENA];
  char autor[MAX_LONGITUD_CADENA];

  printf("Ingrese titulo del libro: ");
  scanf(" %[^\n]", titulo);

  while (getchar() != '\n')
    ;

  printf("Ingrese autor del libro: ");
  scanf(" %[^\n]", autor);

  for (int i = 0; i < num_libros; i++) {
    if (strcmp(biblioteca[i].titulo, titulo) == 0 &&
        strcmp(biblioteca[i].autor, autor) == 0) {
      if (!colaVacia(colaReservas)) {
        strcpy(biblioteca[i].estado, "Reservado");
      } else {
        strcpy(biblioteca[i].estado, "Disponible");
      }
      printf("Libro regresado exitosamente\n");
      return;
    }
  }

  printf("Libro no disponible\n");
}

void mostrarLibrosPrestados(Cola *colaReservas) {
  int contadorPrestados = 0;

  printf("Lista de libros prestados:\n");
  for (int i = 0; i < num_libros; i++) {
    if (strcmp(biblioteca[i].estado, "Prestado") == 0) {
      contadorPrestados++;
      printf("%s de %s prestado a %s\n", biblioteca[i].titulo,
             biblioteca[i].autor,
             colaReservas->datos[colaReservas->frente].estudiante);
    }
  }

  if (contadorPrestados == 0) {
    printf("No se encuentran libros prestados.\n");
  }
}

void importarLibros() {
  char nombreArchivo[MAX_LONGITUD_CADENA];
  printf("Ingrese nombre del archivo (debe inclir .CSV): ");
  scanf("%s", nombreArchivo);

  FILE *archivo = fopen(nombreArchivo, "r");
  if (archivo == NULL) {
    printf("Error al abrir el archivo.\n");
    return;
  }

  char linea[MAX_LONGITUD_CADENA * 7 + 6];
  while (fgets(linea, sizeof(linea), archivo) != NULL &&
         num_libros < MAX_LIBROS) {
    Libro nuevoLibro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", nuevoLibro.titulo,
           nuevoLibro.autor, nuevoLibro.genero, nuevoLibro.isbn,
           nuevoLibro.ubicacion, nuevoLibro.estado);

    if (strcmp(nuevoLibro.estado, "Reservado") == 0 ||
        strcmp(nuevoLibro.estado, "Prestado") == 0) {
      int num_reservas;
      sscanf(linea + strlen(nuevoLibro.titulo) + strlen(nuevoLibro.autor) +
                 strlen(nuevoLibro.genero) + strlen(nuevoLibro.isbn) +
                 strlen(nuevoLibro.ubicacion) + strlen(nuevoLibro.estado) + 6,
             ",%d", &num_reservas);
      nuevoLibro.num_reservas = num_reservas;
      for (int i = 0; i < num_reservas; i++) {
        sscanf(linea + strlen(nuevoLibro.titulo) + strlen(nuevoLibro.autor) +
                   strlen(nuevoLibro.genero) + strlen(nuevoLibro.isbn) +
                   strlen(nuevoLibro.ubicacion) + strlen(nuevoLibro.estado) +
                   7 + (i * (MAX_LONGITUD_CADENA + 1)),
               "%[^,\n]", nuevoLibro.reservas[i]);
      }
    } else {
      nuevoLibro.num_reservas = 0;
    }

    biblioteca[num_libros++] = nuevoLibro;
  }

  fclose(archivo);
  printf("Archivo importado correctamente\n");
}

void exportarLibros() {
  char nombreArchivo[MAX_LONGITUD_CADENA];
  printf("Ingrese nombre del archivo (debe inclir .CSV): ");
  scanf("%s", nombreArchivo);

  FILE *archivo = fopen(nombreArchivo, "w");
  if (archivo == NULL) {
    printf("Error al exportar el archivo\n");
    return;
  }

  for (int i = 0; i < num_libros; i++) {
    fprintf(archivo, "%s,%s,%s,%s,%s,%s", biblioteca[i].titulo,
            biblioteca[i].autor, biblioteca[i].genero, biblioteca[i].isbn,
            biblioteca[i].ubicacion, biblioteca[i].estado);

    if (strcmp(biblioteca[i].estado, "Reservado") == 0 ||
        strcmp(biblioteca[i].estado, "Prestado") == 0) {
      fprintf(archivo, ",%d", biblioteca[i].num_reservas);
      for (int j = 0; j < biblioteca[i].num_reservas; j++) {
        fprintf(archivo, ",%s", biblioteca[i].reservas[j]);
      }
    }

    fprintf(archivo, "\n");
  }

  fclose(archivo);
  printf("Archivo exportado correctamente\n");
}