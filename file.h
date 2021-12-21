#ifndef C_UTILS_FILE_H_INCLUDED
#define C_UTILS_FILE_H_INCLUDED

char* read_file(char *filename);
void create_file(char *filename, char *contents);
int copy_file(char *filename, char *dest_path);
char* get_filename_from_path(char *filepath);

#endif // C_UTILS_FILE_H_INCLUDED