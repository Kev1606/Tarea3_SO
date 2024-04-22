#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void buscarArchivo(char *nombreArchivo, char *rutaActual);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Uso: %s <nombre_archivo>\n", argv[0]);
		return 1;
	}
	char rutaInicial[1024];
	getcwd(rutaInicial, sizeof(rutaInicial)); // Obtener la ruta actual
	buscarArchivo(argv[1], rutaInicial);

	return 0;
}

void buscarArchivo(char *nombreArchivo, char *rutaActual) {
	DIR *directorio;
	struct dirent *entrada;
	char rutaNueva[1024];

	directorio = opendir(rutaActual); // Abrir el directorio actual

	if (directorio == NULL) {
		perror("Error al abrir el directorio");
		return;
	}

	while ((entrada = readdir(directorio)) != NULL) { // Leer las entradas del directorio
		if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0)
    	continue; // Omitir los directorios "." y ".."

		sprintf(rutaNueva, "%s/%s", rutaActual, entrada->d_name); // Construir la ruta completa

		if (strcmp(entrada->d_name, nombreArchivo) == 0) {
			printf("Archivo encontrado en: %s\n", rutaNueva); // Imprimir la ruta completa
		} else {
		  struct stat estadoArchivo;
		  if (stat(rutaNueva, &estadoArchivo) == 0 && S_ISDIR(estadoArchivo.st_mode)) {
		      buscarArchivo(nombreArchivo, rutaNueva); // Buscar recursivamente en el subdirectorio
		  }
		}
	}

	closedir(directorio); // Cerrar el directorio
}
