//init.c

void init_bss()
{
   extern char _start_of_bss;   
   extern char _end_of_bss;   

   char *dst = &_start_of_bss;

   for(dst = &_start_of_bss; dst < &_end_of_bss; dst++)
   {
      *dst = 0;
   }
}

void init_memory()
{
   extern char _start_of_flash_vectors;
   extern void *vector_table[];

   _start_of_flash_vectors = (int) vector_table;
}
