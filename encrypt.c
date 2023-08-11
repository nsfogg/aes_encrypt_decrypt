#include "io.h"
#include "aes.h"
#include "field.h"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
    if ( argc != WORD_SIZE ) {
        fprintf(stderr, "usage: encrypt <key-file> <input-file> <output-file>\n");
        exit( 1 );
    }
    int keySize = 0;
    int fileSize = 0;
    char *keyName = argv[1];
    char *filename = argv[2];
    char *outputName = argv[argc - 1];

    byte *key = readBinaryFile( keyName, &keySize );
    if ( keySize != BLOCK_SIZE ) {
        fprintf(stderr, "Bad key file: %s\n", keyName);
        exit( 1 );
    }
    byte *input = readBinaryFile( filename, &fileSize );
    if ( fileSize % BLOCK_SIZE != 0 ) {
        fprintf(stderr, "Bad plaintext file length: %s\n", filename);
    }
    byte data[BLOCK_SIZE];
    byte final[fileSize];
    int finalSize = fileSize;
    int iteration = 0;
    while ( fileSize >= BLOCK_SIZE ) {
        for (int i = 0; i < BLOCK_SIZE; i++ ) {
            data[i] = input[i + iteration];
        }
        encryptBlock( data, key );
        for (int i = 0; i < BLOCK_SIZE; i++ ) {
            final[i + iteration] = data[i];
        }
        iteration += BLOCK_SIZE;
        fileSize -= BLOCK_SIZE;
    }
    writeBinaryFile( outputName, final, finalSize );

    return 0;
}