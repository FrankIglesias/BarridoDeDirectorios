/*
 * prueba.c
 *
 *  Created on: 13/10/2016
 *      Author: utnso
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
void recorrerDirectorios(char *ruta, void (*funcionCarpeta(char * ruta)),
		void (*funcionArchivo(char *ruta))) {
	DIR *dip;
	struct dirent *dit;
	if ((dip = opendir(ruta)) == NULL) {
		perror("opendir");
	}
	while ((dit = readdir(dip)) != NULL) {

		if (!(strcmp(dit->d_name, "..") == 0 || strcmp(dit->d_name, ".") == 0)) {
			char * aux = malloc(strlen(ruta) + 1 + strlen(dit->d_name));
			strcpy(aux, ruta);
			strcat(aux, dit->d_name);
			if (dit->d_type == 4) {
				strcat(aux, "/");
				funcionCarpeta(aux);
				recorrerDirectorios(aux, funcionCarpeta, funcionArchivo);

			} else if (dit->d_type == 8) {
				funcionArchivo(aux);
			}
			free(aux);
		}

	}
	if (closedir(dip) == -1) {
		perror("closedir");
	}
}
void funcionCarpeta(char *ruta) {
	printf("Carpeta: %s\n", ruta);
}
void funcionArchivo(char * ruta) {
	printf("Archivo: %s\n", ruta);
}
int main(int argc, char *argv[]) {
	recorrerDirectorios("/home/utnso/workspace/",
			funcionCarpeta, funcionArchivo);
	return 0;
}
