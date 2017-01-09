void init_bss()
{
   int *dst = &_etext;

   for(dst = &_bstart; dst < &_bend; dst++)
   {
      *dst = 0;
   }
}
