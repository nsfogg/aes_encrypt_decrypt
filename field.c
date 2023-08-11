/**
*/

#include "field.h"
#include <stdlib.h>

byte fieldAdd( byte a, byte b ) {
    return a ^ b;
}

byte fieldSub( byte a, byte b ) {
    return a ^ b;
}

byte fieldMul( byte a, byte b ) {
    unsigned short result = 0;
    unsigned short slot[8];

    // Determine if each slot is valid or invalid
    byte valid[8];
    for ( int i = 0; i < 8; i++ ) {
        valid[i] = ( ( ( b >> i) & 0x1 ) == 1 ) ? 1 : 0;
        // valid[i] = ( ( ( b & 0x1 ) >> i ) == 1 ) ? 1 : 0;
    }

    // Expand the multiplication
    for ( int i = 0; i < 8; i++ ) {
        // If slot is valid
        if ( valid[i] == 1 ) {
            slot[i] = a;
            // Get the corect stagger depending on digit place value
            for ( int j = 0; j < i; j++ ) {
                slot[i] *= 2;
            }
        } else {
            slot[i] = 0;
        }
    }

    // Perform the XOR
    result = slot[0] ^ slot[1];
    for ( int i = 2; i < 8; i++ ) {
        result = result ^ slot[i];
    }

    // Get the reducer
    unsigned short temp = result;
    unsigned short digits = 0;
    while ( temp > 0 ) {
        temp = temp / 2;
        digits++;
    }
    int reducer = 0x11B;

    while ( digits > BBITS ) {
        // Get digits in the reducer 
        unsigned short ddigits = 0;
        temp = reducer;
        while ( temp > 0 ) {
            temp = temp / 2;
            ddigits++;
        }
        // Shift the reducer to match result's digits
        unsigned short ddiff = digits - ddigits;
        ddigits = reducer << ddiff;
        // Perform XOR
        result = result ^ ddigits;
        // Count digits in the result
        temp = result;
        digits = 0;
        while ( temp > 0 ) {
            temp = temp / 2;
            digits++;
        }
    }

    byte final = (byte) result;
    return final;
}