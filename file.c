#include <stdio.h>
#include <stdlib.h>

char* read_file(char *filename) {
    FILE* f;
    int file_length;
    unsigned int last_size = 0, contents_size = 0, buffer_length = 0, buffer_size = 1024;
    char *contents = (char *) malloc(sizeof(char));
    char buffer[buffer_size];

    f = fopen(filename, "rb");

    if (f == NULL) {
        printf("Could not open file %s\n", filename);
        contents[0] = '\0';
        return contents;
    }

    fseek(f, 0, SEEK_END);
    file_length = ftell(f);
    fseek(f, 0, SEEK_SET);

    while (file_length > 0) {
        last_size = contents_size;
        buffer_length = file_length > buffer_size ? buffer_size : file_length;
        fread(buffer, buffer_length, 1, f);
        contents_size += buffer_length;
        contents = (char*) realloc(contents, sizeof(char) * (contents_size + 1));
        strncpy(&contents[last_size], &buffer, buffer_length);
        contents[contents_size] = '\0';
        file_length -= buffer_length;
    }

    fclose(f);
    return contents;
}

void create_file(char *filename, char *contents) {
    FILE *f;

    f = fopen(filename, "wb");
    if (f == NULL) {
        printf("Could not open file %s for writing\n", filename);
    }

    fprintf(f, "%s", contents);
    fclose(f);
}

int copy_file(char *filename, char *dest_path) {
    FILE *f, *dest_f;
    int file_size = 0, buffer_size = 128;
    char buffer[buffer_size];

    f = fopen(filename, "rb");
    if (f == NULL) {
        return 0;
    }

    dest_f = fopen(dest_path, "wb");
    if (dest_f == NULL) {
        return 0;
    }

    fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    for (;file_size > 0;) {
        fread(buffer, sizeof(buffer), 1, f);
        fwrite(buffer, sizeof(buffer), 1, dest_f);
        file_size -= buffer_size;
    }

    fclose(dest_f);
    fclose(f);

    return 1;
}

char* get_filename_from_path(char *filepath) {
    unsigned short length = strlen(filepath), iterator, cut_length;
    char *result, c;

    iterator = length - 1;
    // Lets find the most-right slash in the string
    while (1) {
        c = filepath[iterator];
        if (c == '/') {
            ++iterator;
            break;
        } else if (iterator == 0) {
            break;
        }
        --iterator;
    }

    cut_length = length - iterator;
    result = (char*) malloc(sizeof(char) * (cut_length + 1));
    strncpy(result, &filepath[iterator], cut_length);
    result[cut_length] = '\0';

    return result;
}