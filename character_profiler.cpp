#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

typedef struct charFreq
{
   int totalChars;
   float freq[256];
   int count[256];
   int sortedIndex[256];
} charFreq;


int main( int argc, char *argv[] )
{
   charFreq data;

   int charFreq[256];
   int totalChars;
   int i;
   char c;

   string line;

   ifstream fpIn;
   ifstream fpDataIn;
   ofstream fpDataOut;
   string inFilename, dataFilename; 

   if(argc <= 2)
   {
      cout << "Usage: " << argv[0] << "<input filename> <data filename>\n";
      exit(1);
   }
   inFilename = argv[1];
   dataFilename = argv[2];

   /*
   fpDataIn.open(dataFilename, ios::in);
   if(fpDataIn.is_open())
   {
      int value;
      while(fpDataIn >> index >> value >> percentage)
      {
         data.count[index+128] = value;
      }
      fpDataIn.close();
   }
   */

   fpIn.open(inFilename, ios::in);
   if(!fpIn.is_open())
   {
      cout << "Unable to open input file: " << inFilename << '\n';
      exit(2);
   }

   while(fpIn.get(c))
   {
      data.count[tolower(c)+128]++;
      data.totalChars++;
   }

   for(int i = 0; i < 256; ++i)
      data.freq[i] = (float)data.count[i]/data.totalChars;
   
   for(int i = 0; i < 256; ++i)
   {
      data.sortedIndex[i] = 0;
   }

   for(int i = 0; i < 256; ++i)
   {
      int j = 0, k;
      while(data.freq[i] > data.sortedIndex[j]) 
         j++;
      k = j;
      while(data.sortedIndex[j] != 0)
         j++;
      for(int m = j; m > k; m--)
         data.sortedIndex[m+1] = data.sortedIndex[m];
      
      data.sortedIndex[j] = data.freq[i]; 
   }

   fpIn.close();

   fpDataOut.open(dataFilename, ios::out);
   fpDataOut << data.totalChars << ",";
   for(int i = 0; i < 256; i++)
      fpDataOut <<  data.freq[i] << "," << data.count[i] << "," << data.sortedIndex[i];
   fpDataOut.close();

   return(0);
}
