
#ifndef HW3_UTILS_H
#define HW3_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define LINE_SIZE 256

int length(char* str);
// Returns the number of indexes at the array

void check_file(FILE* fp, char* path);
// End the program if the file isn't open

void check_allocate(char* ap);
// End the program if the memory allocation failed

int count_lines(FILE* f,char* path);
// Return the number of lines at the file


void copy(char *cur, char *dest);
// Copy string from char* to new one.


void strip (char* str);
// Gets char pointer to string & return it without '/n' by shifting indexes to the right

char* create_path(char* dir, char* file);
// Creating new path from two strings by dynamic memory allocation

char* get_song_name(char* path);
// Creating string by allocation dynamic memory for the first line (title) at the file

bool wc(char* path, int* nchars, int* nwords, int* nlines);
// Return True if the file opened successfully, analyzing the file by counting the parameters. Return false if the func failed to read the file.

int get_all_song_names(char* path, char*** all_song_names);
// Returns the number of files at the directory & makes an array by dynamic allocation for all the files titles.

#endif //HW3_UTILS_H
