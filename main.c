#include "bmp.h"
#include "command.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void applyOption(image* result, image* source, const char* opt) {
    if (strcmp(opt, "none") == 0) {
        * result = none(*source);
    } else if (strcmp(opt, "cw90") == 0) {
        * result = cw90(*source);
    } else if (strcmp(opt, "ccw90") == 0) {
        * result = ccw90(*source);
    } else if (strcmp(opt, "flipv") == 0) {
        * result = flipv(*source);
    } else if (strcmp(opt, "fliph") == 0) {
        * result = fliph(*source);
    } else {
        fprintf(stderr, "Должен быть любая из опций: none, cw90, ccw90, flipv, fliph, а не \"%s\"\n", opt);
        free(result);
        exit(2);
    }
}

void clean(FILE* file, image* image) {
    fclose(file);
    free(image);
}

int main(int argc, char** argv) {
    if (argc!= 4) {
        printf("Неправильное количество аргументов\n");
        return 1;
    }
    
    const char* sourceName = argv[1];
    const char* resultName = argv[2];
    const char* opt = argv[3];
    
    FILE* sourceFile = fopen(sourceName, "rb");
    if (!sourceFile) {
        fprintf(stderr, "Ошибка при открытии файла \"%s\"\n", sourceName);
        return 2;
    }
    FILE* resultFile = fopen(resultName, "wb");
    if (!resultFile) {
        fprintf(stderr, "Ошибка открытия файла результата \"%s\"", resultName);
        return 2;
    }

    image *source = malloc(sizeof(image));
    image *result = malloc(sizeof(image));

    read_status read_status = from_bmp(sourceFile, source);
    if (read_status != READ_OK) {
        fprintf(stderr, "Ошибка при чтении файла \"%s\" ", sourceName);
        clean(sourceFile, source);
        clean(resultFile, result);
        return read_status;
    }
    
    applyOption(result, source, opt);
 
    write_status write_status = to_bmp(resultFile, result);
    
    clean(sourceFile, source);
    clean(resultFile, result);

    if (write_status == WRITE_ERROR) {
	fprintf(stderr, "Ошибка при записи в файл \"%s\"\n", resultName);
        return write_status;
    }

    return 0;
}