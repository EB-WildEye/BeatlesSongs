# Beatles Songs Analyzer

## Introduction
Welcome to our Beatles Songs Analyzer program! This C program scans through a collection of 211 Beatles songs and prints, for each song, the number of lines, words, and characters. The results are written to an output file named "output.txt." Enjoy exploring the Beatles' songs!

## Usage
To run the program, provide the required command-line arguments: the path to the directory containing the Beatles songs and the output file.

**./beatles_analyzer /path/to/songs /path/to/output.txt**


## Implementation Details
The program reads all the filenames from "filenames.txt" in the specified directory, analyzes each song using the utility function wc, and prints the results to "output.txt."


## Build and Run
To build the program, compile the source file along with "Utils.c" and link against the necessary standard libraries.

**gcc -o beatles_analyzer BeatlesAnalyzer.c Utils.c**

To execute the program, run the compiled binary.

**./beatles_analyzer /path/to/songs /path/to/output.txt**


## Output Format
The output file "output.txt" contains a tab-separated table with columns for the number of lines, words, characters, and the name of each Beatles song.

## Authors
Ein-Bar Surie - 316011683
Noam Ickowicz - 314766304
