#include "Headers/getFile.h"

char *getJsonFile(char *fileName){
    FILE *file;

    // Open file in read binary mode
    file = fopen(fileName, "rb");
    if(file == NULL){
        perror("fopen");
        return NULL;
    }

    // Set the position of curosr at the EOF to get the size
    if(fseek(file, 0, SEEK_END) != 0){
        perror("Failed to seek to EOF");
        fclose(file);
        return NULL;
    }

    // Get the size of the file by using ftell and get the amount of bytes the file is
    long fileSize = ftell(file);
    if(fileSize <= 0){
        perror("Failed to tell filesize");
        fclose(file);
        return NULL;
    }

    // Set the cursor back at the beginning
    if(fseek(file, 0, SEEK_SET) != 0){
        perror("Failed to seek to start");
        fclose(file);
        return NULL;
    }

    // Make space for the buffer to recive everything plus the '\0' indicater
    char *buffer = malloc((fileSize * sizeof(char)) + 1);

    // read everything in the file to the buffer
    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if(bytesRead < (size_t)fileSize){
        perror("Error reading the file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[bytesRead + 1] = '\0';

    fclose(file);
    return buffer;

}