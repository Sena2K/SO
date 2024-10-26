#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char *argv[]) {
 
    int file = open(argv[2], O_RDONLY);
    if (file == -1) {
        perror("erro ao abrir arquivo");
        return;
    }

    char buffer[1024];
    char buffer_linha[2048] = {0};
    ssize_t bytesRead;
    const char *termo_busca = argv[1];

    while ((bytesRead = read(file, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';
        
        char *linha = buffer;
        char *nova_linha;

        while ((nova_linha = strchr(linha, '\n')) != NULL) {
            *nova_linha = '\0';
            strcat(buffer_linha, linha);

            if (strstr(buffer_linha, termo_busca) != NULL) {
                write(1, buffer_linha, strlen(buffer_linha));
                write(1, "\n", 1);
            }

            buffer_linha[0] = '\0';
            linha = nova_linha + 1;
        }

        strcat(buffer_linha, linha);
    }

    if (buffer_linha[0] != '\0' && strstr(buffer_linha, termo_busca) != NULL) {
        write(1, buffer_linha, strlen(buffer_linha));
        write(1, "\n", 1);
    }

    close(file);
}

