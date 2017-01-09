void init_bss()
{
   int *dst = &_end_of_text;

   for(dst = &_start_of_bss; dst < &_end_of_bss; dst++)
   {
      *dst = 0;
   }
}
