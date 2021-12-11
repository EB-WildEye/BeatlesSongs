#include <stdio.h>
// Created by Ein-Bar Surie 316011683 & Noam
#include "Utils.h"


int main(int argc, char *argv[])    {


    if( argc != 3 )	{
        fprintf(stderr, "ERROR: invalid number of arguments given.");
        exit(-1);
    }

    char * filenames_path = create_path(argv[1], "filenames.txt");

    // open filenames.txt for counting number of lines
    FILE * filenames = fopen(filenames_path,"r");
    check_file(filenames, filenames_path);
    int num_lines = count_lines(filenames, filenames_path);
    fclose(filenames);

    // initialize all songs to song_names
    char ** song_names = (char**)malloc(num_lines + 1);
    int num_songs = get_all_song_names(argv[1], &song_names);

    printf("%d", num_songs);
    fflush(stdout);
    // handle wc and output to output file (END!!!)
    int i, line_len, nchars = 0, nwords = 0, nlines = 0;

    char *temp_path, *temp_song_file;
    char* buf;
    size_t buf_size;

    FILE* f = fopen(filenames_path, "r");
    check_file(f, filenames_path);

    for(i = 0; i < num_songs; i++) {

        line_len = getline(&buf, &buf_size, f);

        temp_song_file = (char*)malloc(line_len + 1);
        check_allocate(temp_song_file);

        strip(buf);
        copy(buf,temp_song_file);
        printf("%s\n", buf);
        fflush(stdout);

        temp_path = create_path(argv[1], temp_song_file);
        //bool func_wc = wc(temp_path, &nchars, &nwords, &nlines);

        //printf("%s\t%d\t%d\t%d\n", *(song_names[i]), nlines, nwords, nchars);
        fflush(stdout);
    }

    free(song_names);

    return 0;
}
