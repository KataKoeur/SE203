#include <stdio.h>

__attribute__((naked)) void f()
{
  uint32_t a; // global variable

  for (uint8_t i=0; i<=a; i++)
  {
    g();
  }
}
