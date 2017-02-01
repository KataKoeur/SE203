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
   extern char _start_of_flash_vectors_LMA;
   extern char _start_of_flash_vectors_VMA;
   extern char _end_of_flash_vectors_VMA;

   extern char _start_of_text_LMA;
   extern char _start_of_text_VMA;
   extern char _end_of_text_VMA;

   extern char _start_of_data_LMA;
   extern char _start_of_data_VMA;
   extern char _end_of_data_VMA;

   //flash_vectors vers RAM
   char *src = &_start_of_flash_vectors_LMA;
   char *dst = &_start_of_flash_vectors_VMA;
   while (dst < &_end_of_flash_vectors_VMA) *dst++ = *src++;

   //text vers RAM
   src = &_start_of_text_LMA;
   dst = &_start_of_text_VMA;
   while (dst < &_end_of_text_VMA) *dst++ = *src++;

   //data vers RAM
   src = &_start_of_data_LMA;
   dst = &_start_of_data_VMA;
   while (dst < &_end_of_data_VMA) *dst++ = *src++;
}
