#include <stdio.h>

uint32_t *a; // global variable
uint32_t *b; // global variable
uint32_t *c; // global variable

__attribute__((naked)) void f()
{
  *a += *c ;
  *b += *c ;
}
