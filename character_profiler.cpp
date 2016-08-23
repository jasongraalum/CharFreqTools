#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

int main( int argc, char *argv[] )
{

   int charFreq[256];
   int lineCnt = 0;
   int unprintable = 0;
   int printable = 0;
   int BS = 0;
   int HTab = 0;
   int LF = 0;
   int VTab = 0;
   int FF = 0;
   int CR = 0;
   int totalC = 0;
   int i;
   char c;
   string line;

   ifstream fpIn;
   string inFilename, dataFile; 

   cout << "Size of charFreq = " << sizeof(charFreq) << '\n';

   for(i=0; i < 256; ++i)
      charFreq[i] = 0;

   if(argc <= 2)
   {
      cout << "Usage: " << argv[0] << "<input filename> <data filename>\n";
      exit(1);
   }

   inFilename = argv[1];
   dataFile = argv[2];

   fpIn.open(inFilename, ios::in);
   if(!fpIn.is_open())
   {
      cout << "Unable to open input file: " << inFilename << '\n';
      exit(2);
   }

   //while(!fpIn.eof() )
   //while(fpIn,getline(fpIn,line))
   while(fpIn.get(c))
   {
      totalC++;
      if(c == '\n')
         lineCnt++;
      if((c > 0) && (c < 32))
      {
         unprintable++;
         if(c == 10)
            LF++;
         if(c == 11)
            VTab++;
         if(c == 12)
            FF++;
         if(c == 13)
            CR++;
         if(c == 8)
            BS++;
         if(c == 9)
            HTab++;
      }

      else
      {
         printable++;
      }
      //cout << charFreq[c];
      ++charFreq[c+128];
   }
   
   if(!fpIn.eof())
   {
      cout << "Error\n";
      if(fpIn.bad())
         cout << "Badbit set\n";
      
   }
   else
      cout << "EOF\n";
   fpIn.close();

   cout << lineCnt << '\n';
   cout << unprintable << '\n';
   cout << printable << '\n';
   cout << "Total characters:" << totalC << '\n';
   cout << "Char:(8): BS : " << BS << '\n';
   cout << "Char:(9): HTab : " << HTab << '\n';
   cout << "Char:(10): LF : " << LF << '\n';
   cout << "Char:(11): VTab : " << VTab << '\n';
   cout << "Char:(12): FF : " << FF << '\n';
   cout << "Char:(13): CR : " << CR << '\n';


   for(unsigned int i = 32; i < 128; ++i)
   {
      c = (char) i;
      cout << "Char:(" << i<< "):" << c <<": " << charFreq[i+128] << '\n';
   }

   cout << '\n';


   return(0);

}




