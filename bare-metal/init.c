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
   extern char _end_of_flash_vectors;

   extern char _start_of_text;
   extern char _end_of_text;

   extern char _start_of_data;
   extern char _end_of_data;

   extern char _end_of_bss;   

   char *src = &_start_of_flash_vectors;
   char *dst = &_end_of_bss;

   //flash_vectors vers RAM
   while (src < &_end_of_flash_vectors) *dst++ = *src++;

   //text vers RAM
   src = &_start_of_text;
   while (src < &_end_of_text) *dst++ = *src++;

   //data vers RAM
   src = &_start_of_data;
   while (src < &_end_of_data) *dst++ = *src++;
}
