#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_EMPLEADOS 10

struct Empleado {
    int id;
    char nombre[50];
    int edad;
};

void escritor() {
	int fd;
	struct flock lock;
	struct Empleado empleado;

	// Abrir el archivo en modo append
	fd = open("empleados.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1) {
		perror("Error al abrir el archivo");
		exit(1);
	}

	for (int i = 1; i <= MAX_EMPLEADOS; i++) {
		// Bloquear el archivo antes de escribir
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		fcntl(fd, F_SETLKW, &lock);

		// Llenar la información del empleado
		empleado.id = i;
		sprintf(empleado.nombre, "Empleado %d", i);
		empleado.edad = 25 + i;

		// Escribir la información del empleado en el archivo
		write(fd, &empleado, sizeof(empleado));

		// Desbloquear el archivo después de escribir
		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		printf("Empleado %d agregado\n", i);

		// Esperar 2 segundos antes de agregar el siguiente empleado
		sleep(2);
	}

	close(fd);
}

void lector() {
  int fd;
  struct flock lock;
  struct Empleado empleado;

  while (1) {
    // Abrir el archivo en modo lectura
    fd = open("empleados.txt", O_RDONLY);
    if (fd == -1) {
		  perror("Error al abrir el archivo");
		  exit(1);
    }

    // Bloquear el archivo antes de leer
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    fcntl(fd, F_SETLKW, &lock);

    // Leer e imprimir la información de los empleados
    printf("Información de empleados:\n");
    while (read(fd, &empleado, sizeof(empleado)) == sizeof(empleado)) {
    	printf("ID: %d, Nombre: %s, Edad: %d\n", empleado.id, empleado.nombre, empleado.edad);
    }

    // Desbloquear el archivo después de leer
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);

    // Esperar 2 segundos antes de volver a leer
    sleep(2);
  }
}

int main() {
	pid_t pid;

	// Crear un proceso hijo para el lector
	pid = fork();

	if (pid == -1) {
		perror("Error al crear el proceso hijo");
		exit(1);
	} else if (pid == 0) {
		// Proceso hijo (lector)
		lector();
	} else {
		// Proceso padre (escritor)
		escritor();

		// Esperar a que el proceso hijo termine
		wait(NULL);
	}

	return 0;
	}
