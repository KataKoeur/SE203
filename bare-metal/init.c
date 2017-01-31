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
   extern char _end_of_text;
   extern char _start_of_data;
   extern char _end_of_data;

   char *src = &_end_of_text;
   char *dst = &_start_of_data;
   
   while (dst < &_end_of_data) 
      *dst++ = *src++;
}
