int fibo(int n)
{
   if(n<1)                 return 0;
   else if(n==1 || n==2)   return 1;
   else                    return fibo(n-1) + fibo(n-2);
}

int main (void)
{
   int result = 0;

   while(1)
   {
      result = fibo(8);
   }
}
