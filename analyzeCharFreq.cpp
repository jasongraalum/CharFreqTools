#include <iostream>
#include <ifstream>
#include <ofstream>


int main(argc, *argv[])
{
   ifstream fpDataIn;
   float charPerc[256];
   int sortedIndex[256] = {0};
   int index;


   if(argc <= 2)
   {
      cout << "Usage: " << argv[0] << "<input filename> <data filename>" << endl;
      exit(2);
   }

   inFilename = argv[1];
   dataFilename = argv[2];

   fpDataIn.open(dataFilename, ios::in);
   if(fpDataIn.is_open())
   {
      int index, value; 
      float percentage;
      while(fpDataIn >> index >> value >> percentage)
      {
         charPerc[index+128] = percentage;
         index = 0;
         while
      }
      fpDataIn.close();
   }






}




