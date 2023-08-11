#include "io.h"
#include "field.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * This function reads the contents of the binary file with the given name. 
 * It returns a pointer to a dynamically allocated array of bytes containing 
 * the entire file contents. The size parameter is an integer that’s passed by 
 * reference to the function. The function fills in this integer with the total
 *  size of the file (i.e., how many bytes are in the returned array).
*/
byte *readBinaryFile( char const *filename, int *size )
{
    FILE *reader = fopen(filename, "rb");

    if ( reader == NULL ) {
        fprintf(stderr, "Can't open file: %s\n", filename);
        exit( 1 );
    }

    int capacity = 1;
    int len = 0;
    byte *contents = malloc( capacity * sizeof( byte ) );

    // int elements = fread( contents, sizeof( byte ), elements, reader );
    int ch;
    while ( ( ch = fgetc( reader ) ) != EOF ) {
        if ( len >= capacity ) {
            capacity *= 2;
            contents = realloc( contents, capacity * sizeof( byte ) );
        }
        contents[ len++ ] = (byte) ch;
    }

    *size = len;
    fclose(reader);
    return contents;
}

/**
 * This function writes the contents of the given data array (in binary) to the 
 * file with the given name. The size parameter says how many bytes are contained in the data array.
*/
void writeBinaryFile( char const *filename, byte *data, int size )
{
    FILE *writer = fopen(filename, "w");

    fwrite( data, sizeof( byte ), size, writer );
}