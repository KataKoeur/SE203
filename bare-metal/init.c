void init_bss()
{
   extern char _start_of_bss;   
   extern char _end_of_bss;   

   char *dst;

   for(dst = &_start_of_bss; dst < &_end_of_bss; dst++)
   {
      *dst = 0;
   }
}
