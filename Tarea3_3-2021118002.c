#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char nombre[50];
	int edad;
	float salario;
} Empleado;

void guardarEmpleados(const char *nombreArchivo) {
	FILE *archivo;
	Empleado empleados[10];

	// Abrir el archivo en modo escritura
	archivo = fopen(nombreArchivo, "wb");

	// Pedir los datos de los 10 empleados y guardarlos en el archivo
	for(int i = 0; i < 10; i++) {
		printf("Ingrese el nombre del empleado %d: ", i+1);
		scanf("%s", empleados[i].nombre);
		
		printf("Ingrese la edad del empleado %d: ", i+1);
		scanf("%d", &empleados[i].edad);
		
		printf("Ingrese el salario del empleado %d: ", i+1);
		scanf("%f", &empleados[i].salario);
		
		fwrite(&empleados[i], sizeof(Empleado), 1, archivo);
	}

	// Cerrar el archivo
	fclose(archivo);
}

void imprimirEmpleadosImpares(const char *nombreArchivo) {
	FILE *archivo;
	Empleado empleado;

	// Abrir el archivo en modo lectura
	archivo = fopen(nombreArchivo, "rb");

	// Recorrer las posiciones impares del archivo usando fseek
	for(int i = 1; i < 10; i += 2) {
		fseek(archivo, i * sizeof(Empleado), SEEK_SET);
		fread(&empleado, sizeof(Empleado), 1, archivo);
		
		printf("Empleado %d:\n", i+1);
		printf("Nombre: %s\n", empleado.nombre);
		printf("Edad: %d\n", empleado.edad);
		printf("Salario: %.2f\n\n", empleado.salario);
	}

	// Cerrar el archivo
	fclose(archivo);
}

int main() {
	const char *nombreArchivo = "empleados.dat";

	// Guardar los datos de los empleados en el archivo
	guardarEmpleados(nombreArchivo);

	// Imprimir los datos de los empleados en posiciones impares
	imprimirEmpleadosImpares(nombreArchivo);

	return 0;
}
