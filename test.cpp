#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;


int main( int argc, char *argv[] )
{
   int charFreq[256];
   int i;
   char c;
   int max=0, min=0;
   ifstream fpIn;

   for(i=0; i < 256; ++i)
   {
      charFreq[i] = 0;
   }

   fpIn.open(argv[1]);


   while(!fpIn.eof())
   {
      fpIn.get(c);
      if((int)c > max) max = (int)c;
      if((int)c < min) min = (int)c;
      if((int)c > 0)
         charFreq[c]++;
   }

   cout<< "Min was: " << min << '\n';
   cout<< "Max was: " << max << '\n';

}




