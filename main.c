/* Welcome to our program !
   The program scanning the Beatles songs ( 211 songs!! ) and print for each one the
   number of lines, words and characters by this order to an output file. Enjoy !! :)

   Created by Ein-Bar Surie 316011683  &&  Noam Ickowicz 314766304*/
#include <stdio.h>
#include "Utils.h"

int main(int argc, char *argv[])    {
    // Checking if our program have all the arguments
    if( argc != 3 )	{
        fprintf(stderr, "ERROR: invalid number of arguments given.");
        exit(-1);
    }

    // Creating path for the songs names file
    char * filenames_path = create_path(argv[1], "filenames.txt");

    // Open filenames.txt for counting number of lines & open output.txt in writing mode
    FILE * filenames = fopen(filenames_path,"r");
    FILE * output_file = fopen("output.txt", "w");
    check_file(filenames, filenames_path);
    int num_lines = count_lines(filenames, filenames_path);

    // Allocated dynamic memory for the songs names array & get the number of all songs
    char** song_names = (char**)malloc((num_lines + 1)*(sizeof(char*)));
    int num_songs = get_all_song_names(argv[1], &song_names);

    // Initialized all the counting variables
    int line_len, nchars = 0, nwords = 0, nlines = 0;

    char *temp_path, *temp_song_file;
    size_t buf_size;
    char* buf;

    // Print the data of the song for each song at the directory
    for(int i = 0; i < num_songs; i++) {
        line_len = (int)getline(&buf, &buf_size, filenames);
        temp_song_file = (char*)malloc(line_len + 1);
        check_allocate(temp_song_file);

        // Preparing the song file & creating its path
        strip(buf);
        copy(buf,temp_song_file);
        temp_path = create_path(argv[1], temp_song_file);

        // If our song doesn't open successfully, continue for the next song ( condition for the filenames file )
        if(!wc(temp_path, &nchars, &nwords, &nlines)){
            continue;
        }

        // Printing the data of the song to the output file
        char* song = *song_names++;
        fprintf(output_file, "%d\t\t%d\t\t%d\t\t%s\n", nlines, nwords, nchars, song);
    }

    // Releasing the allocated memory & closing the file
    fclose(filenames);
    free(temp_song_file);
    free(song_names);

    return 0;
}