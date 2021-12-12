// Created by Ein-Bar Surie 316011683  &&  Noam Ickowicz 314766304
#include "Utils.h"

int length(const char* str) {
    int i = 0;
    // Loop for counting the indexes
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

void check_file(FILE* fp, char* path) {

    if(!fp){
        printf( "Failed to read file %s", path);
        exit(-1);
    }
}

void check_allocate(const char* ap) {

    if(!ap) {
        printf("Allocation Failed\n");
        exit(-1);
    }
}

int count_lines(FILE* f,char* path) {

    int i = 0;
    char * buffer = NULL;
    size_t buff_size;
    f = fopen(path, "r");
    check_file(f, path);

    while( !feof(f) ) {
        getline(&buffer, &buff_size, f);
        i++;
    }
    fclose(f);

    return i;
}

void copy(char *cur, char *dest) {
    // assuming that dest is pre allocated to cur size.

    int i = 0;

    for(i = 0 ; i < length(cur); i++) {
        dest[i] = cur[i];
    }

    dest[i]='\0';
}

void strip (char* str) {

    int index = 0;

    while(str[index] != '\0') {
        // First loop for running from first to the last char of the string
        if(str[index] == '\n') {
            // Search the char we want to remove
            int next_index = index; // New variable to hold the value of current index

            while(str[next_index] != '\0') {
                // The second loop for shift indexes over from left to the right
                str[next_index] = str[next_index+1];
                next_index++;
            }
        }
        else index++; // Increase the current indexes
    }
}

char* create_path(char* dir, char* file) {

    int i = length(dir), j = length(file), x = 0;
    x += i + j + 2; // extend the array for the strings & the '\' char.
    char* path_file =(char*)malloc(x+1); // dynamic memory allocation for the path string
    check_allocate(path_file);

    int index;
    for (index = 0; index <= x; index++) {
        if (index < i) {
            path_file[index] = dir[index];
        }
        if (index == i) {
            path_file[index] = '\\';
        }
        if (index > i) {
            path_file[index] = file[index -1 - i];
        }
        if(index == x)
        {
            path_file[index] = '\0';
        }
    }
    return path_file;
}

char* get_song_name(char* path) {
    FILE* fp = fopen(path, "r");
    check_file(fp, path);

    // Use getline to extract song name from file ( first line ).
    char * buffer = NULL;
    size_t buff_size;
    int line_len;
    line_len = getline(&buffer, &buff_size, fp);

    char * song_name = (char*)malloc(line_len+1); // Allocated memory for the song name
    check_allocate(song_name);
    copy(buffer, song_name);
    strip(song_name); // Cutting the last char - '\n'

    fclose(fp);

    return song_name;
}

bool wc(const char* path, int* nchars, int* nwords, int* nlines) {

    FILE* fp = fopen(path, "r");
    if(!fp) {
        printf( "Failed to read file %s\n", path);
        return false;
    }

    int lines = -2, words = 0 , chars = 0; // Creating int objects for the counting
    char buf[LINE_SIZE];

    while(fgets(buf,sizeof(buf),fp) != NULL)   {
        // Counting the lines for each loop without the two first lines
        int i = 0; // Creating i variable for the buffer indexes
        lines++;

        if ( lines > 0 ) {
            while(buf[i] != '\0'){
                chars++;
                i++;
                if(buf[i] == 32) { // Count the words by all the spaces at line ( count it without the last word )
                    words ++;
                }
            }
        }
    }
    words += lines; // Adding the last word for each line

    // Setting the pointers to result of the function
    *nwords = words;
    *nlines = lines;
    *nchars = chars;

    fclose(fp);

    return true;
}

int get_all_song_names(char* path, char*** all_song_names) {
    // Creat the path file & opened it
    char * filenames = create_path(path, "filenames.txt");
    FILE * songs = fopen(filenames, "r");
    check_file(songs, filenames);

    // Initialized the temporary variables for each song
    char *buffer = NULL, *tmp_song_path, *tmp_song_name, *tmp_song_file;
    size_t buff_size;
    int line_len, i = 0;

    line_len = (int)getline(&buffer, &buff_size, songs); // Get the first line

    while( !feof(songs) )   { // Loop until we get EOF

        tmp_song_file = (char*)malloc(line_len+1); // Allocated memory for the file name
        check_allocate(tmp_song_file);

        copy(buffer, tmp_song_file); // Preparing the path song
        strip(tmp_song_file);
        tmp_song_path = create_path(path, tmp_song_file);
        tmp_song_name = get_song_name(tmp_song_path);

        (*all_song_names)[i++] = get_song_name(tmp_song_path); // Saves the name of the current song and moves on to the next index

        // Realising all pointers
        free(tmp_song_file);
        free(tmp_song_path);

        line_len = getline(&buffer, &buff_size, songs); // Get the next line
    }

    fclose(songs);

    return i; // Returns the numbers of songs
}
