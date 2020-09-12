#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char* readFile(char* filename, long* size);

int main() {
    char filename[] = "beach.png";
    long *size = malloc(sizeof(long));
    unsigned char* buffer = readFile(filename, size);

    if (buffer != NULL) {
        FILE *write_ptr;
        write_ptr = fopen("test.png","wb");
        fwrite(buffer,*size,1,write_ptr);
        fclose(write_ptr);
    
        free(buffer);
        free(size);
        return 0;
    } else {
        return -1;
    }
}

unsigned char* readFile(char* filename, long* size) {
    // Apertura del archivo en modo de lectura binaria
    FILE *pFile = fopen(filename, "rb");
    if (!pFile) {
        printf("Error al abrir el archivo\n");
        return NULL;
    }

    // Obtener dimension del archivio (tamanio)
    fseek(pFile, 0, SEEK_END); // Mueve el cursor de lectura final del archivo
    *size = ftell(pFile); // Obtiene la posicion del cursor en el archivo
    rewind(pFile); // Reinicia el cursor de lectura

    // Solicitar memoria para el buffer
    unsigned char* buffer = (char*) malloc(sizeof(unsigned char)*(*size));
    if (buffer == NULL) {
        printf("Error de memoria\n");
        return NULL;
    }

    // Reiniciar el espacio de memoria ocupado por el buffer
    memset(buffer, 0, sizeof(char)*(*size));

    // Lectura del archivo
    int result = fread(buffer, sizeof(char), *size, pFile);
    if (!result) {
        printf("Error al leer el archivo\n");
        return NULL;
    }

    fclose(pFile);
    return buffer;
}
