#include "./lib/user_auth.h"
#include <stdio.h>
#include <stdlib.h> // Necesario para el uso de system("clear")

// Prototipos de funciones
void clearScreen();
void menu();
void guardarResultados(double input, double result, const char *unInput,
                       const char *unResult);
void verResultados();
double celsiusToFahrenheit(double celsius);
double fahrenheitToCelsius(double fahrenheit);
double kilogramToPound(double kilogram);
double poundToKilogram(double pound);
double hoursToMinutes(double hours);
double minutesToHours(double minutes);
double metersToFeet(double meters);
double feetToMeters(double feet);

int main() {
  if (menuAuth() == 1) {

    menu();
  }

  return 0;
}

void clearScreen() {
  system("clear"); // Comando para limpiar la pantalla en sistemas UNIX
}

void menu() {
  int option;
  double input, result;
  int keepRunning = 1;

  while (keepRunning) {
    clearScreen();

    printf("Conversor de unidades:\n");
    printf("1. Celsius a Fahrenheit\n");
    printf("2. Fahrenheit a Celsius\n");
    printf("3. Kilogramos a Libras\n");
    printf("4. Libras a Kilogramos\n");
    printf("5. Horas a Minutos\n");
    printf("6. Minutos a Horas\n");
    printf("7. Metros a Pies\n");
    printf("8. Pies a Metros\n");
    printf("9. Guardar resultados en archivo\n");
    printf("10. Ver resultados desde archivo\n");
    printf("0. Salir\n");
    printf("Seleccione una opción: ");
    scanf("%d", &option);

    switch (option) {
    case 0:
      keepRunning = 0;
      printf("¡Hasta luego!\n");
      break;
    case 1:
      printf("Ingrese la temperatura en grados Celsius: ");
      scanf("%lf", &input);
      result = celsiusToFahrenheit(input);
      printf("%.2lf grados Celsius equivalen a %.2lf grados Fahrenheit.\n",
             input, result);
      guardarResultados(input, result, "°C", "°F");
      break;
    case 2:
      printf("Ingrese la temperatura en grados Fahrenheit: ");
      scanf("%lf", &input);
      result = fahrenheitToCelsius(input);
      printf("%.2lf grados Fahrenheit equivalen a %.2lf grados Celsius.\n",
             input, result);
      guardarResultados(input, result, "°F", "°C");
      break;
    case 3:
      printf("Ingrese la masa en kilogramos: ");
      scanf("%lf", &input);
      result = kilogramToPound(input);
      printf("%.2lf kilogramos equivalen a %.2lf libras.\n", input, result);
      guardarResultados(input, result, "kg", "lb");
      break;
    case 4:
      printf("Ingrese la masa en libras: ");
      scanf("%lf", &input);
      result = poundToKilogram(input);
      printf("%.2lf libras equivalen a %.2lf kilogramos.\n", input, result);
      guardarResultados(input, result, "lb", "kg");
      break;
    case 5:
      printf("Ingrese la cantidad de horas: ");
      scanf("%lf", &input);
      result = hoursToMinutes(input);
      printf("%.2lf horas equivalen a %.2lf minutos.\n", input, result);
      guardarResultados(input, result, "hrs", "min");
      break;
    case 6:
      printf("Ingrese la cantidad de minutos: ");
      scanf("%lf", &input);
      result = minutesToHours(input);
      printf("%.2lf minutos equivalen a %.2lf horas.\n", input, result);
      guardarResultados(input, result, "min", "hrs");
      break;
    case 7:
      printf("Ingrese la longitud en metros: ");
      scanf("%lf", &input);
      result = metersToFeet(input);
      printf("%.2lf metros equivalen a %.2lf pies.\n", input, result);
      guardarResultados(input, result, "m", "ft");
      break;
    case 8:
      printf("Ingrese la longitud en pies: ");
      scanf("%lf", &input);
      result = feetToMeters(input);
      printf("%.2lf pies equivalen a %.2lf metros.\n", input, result);
      guardarResultados(input, result, "ft", "m");
      break;
    case 9:
      printf("Guardando resultados en el archivo \"datos.dat\"...\n");
      guardarResultados(0, 0, "", "");
      printf("Resultados guardados correctamente.\n");
      break;
    case 10:
      printf("Mostrando resultados desde el archivo \"datos.dat\"...\n");
      verResultados();
      break;
    default:
      printf(
          "Opción no válida. Por favor, seleccione una opción del 0 al 10.\n");
      break;
    }

    printf("\nPresione Enter para continuar...");
    getchar(); // Capturar el salto de línea anterior
    getchar(); // Esperar a que el usuario presione Enter
  }
}

void guardarResultados(double input, double result, const char *unInput,
                       const char *unResult) {
  FILE *archivo;
  archivo = fopen("datos.dat", "a");

  if (archivo == NULL) {
    printf("Error al abrir el archivo.\n");
    return;
  }

  if (input == 0 && result == 0) {
    fprintf(archivo, "-----\n");
  } else {
    fprintf(archivo, "Entrada: %.2lf %s\tResultado: %.2lf %s\n", input, unInput,
            result, unResult);
  }

  fclose(archivo);
}

void verResultados() {
  FILE *archivo;
  archivo = fopen("datos.dat", "r");

  if (archivo == NULL) {
    printf("Error al abrir el archivo.\n");
    return;
  }

  char linea[100];

  printf("Resultados almacenados en el archivo \"datos.dat\":\n");

  while (fgets(linea, sizeof(linea), archivo) != NULL) {
    if (linea[0] == '-' && linea[1] == '-' && linea[2] == '-') {
      printf("\n");
    } else {
      printf("%s", linea);
    }
  }

  fclose(archivo);
}

// Resto de las funciones de conversión aquí...

double celsiusToFahrenheit(double celsius) { return (celsius * 9 / 5) + 32; }

double fahrenheitToCelsius(double fahrenheit) {
  return (fahrenheit - 32) * 5 / 9;
}

double kilogramToPound(double kilogram) { return kilogram * 2.20462; }

double poundToKilogram(double pound) { return pound / 2.20462; }

double hoursToMinutes(double hours) { return hours * 60; }

double minutesToHours(double minutes) { return minutes / 60; }

double metersToFeet(double meters) { return meters * 3.28084; }

double feetToMeters(double feet) { return feet / 3.28084; }
