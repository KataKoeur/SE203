//matrix.c

#include "matrix.h"

void matrix_init()
{
   //activation horloge port A B C et D
   SIM_SCGC5 = SIM_SCGC5 | 0x00001e00;
}
