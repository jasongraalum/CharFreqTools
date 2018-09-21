#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>

#define START_ASCII 32
#define END_ASCII 128

using namespace std;

int main(int argc, char *argv[])
{
   ifstream fin;
   ofstream fout;
   string ifile, ofile;

   unsigned int encode[255] = {0};
   unsigned int usedCodes[255] = {0};
   unsigned int codeCnt[255] = {0};
   int code;

   char c;

   time_t t;

   srand((unsigned) time(&t));

   if(argc <= 1)
   {
      cout <<"Usage: " << argv[0] << "<filename>" << '\n';
      exit(1);
   }

   ifile = argv[1];
   fin.open(ifile, ios::in);
   if(!fin.is_open())
   {
      cout << "Unable to open input file: " << ifile << '\n';
      exit(2);
   }

   while(!fin.eof())
   {
      fin.get(c);
//      if(!usedASCII[(int)c+128])
//      {
//         cout << c << ":(" << c+128 << ") ";
//      }
      usedCodes[(int)c+128]=1;
      codeCnt[(int)c+128]++;
//      cout << ".";
   }

   for(int i = 0; i < 255; ++i)
      cout << i << ":" << usedCodes[i] << "(" << codeCnt[i] << ")\n";

   for(int i = 0; i < 255; ++i)
   {
      code = (rand() % 256);
      cout << code << '\n';
      while(usedCodes[code] == 0)
      {
         //cout << '\n';
         //cout << "Trying code: " << code << '\n';
         code = (rand() % 256);
         usedCodes[code] = 0;
      }
      encode[code] = i;
      cout << "Code: " << (char) code << "(" << code <<") encodes as: " << (char) i << "(" << i << ")\n";
   }
   exit(0);

   for(int i = START_ASCII; i < END_ASCII; ++i)
   {
     cout << i << ":" << (char) i << " -- " << encode[i] << ":" << (char)encode[i] << '\n';
   }
   exit(0);

   ofile = ifile + ".caesar";
   fout.open(ofile, ios::out);

   if(!fout.is_open())
   {
      cout << "Unable to open output file: " << ofile << '\n';
      exit(3);
   }


   while(!fin.eof())
   {
      fin.get(c);
      //cout << "Encoding: " << c << "(" << (int) c << ")\n";
      //cout << "To: " << encode[(int) c] << " == " << (int) c << '\n';

      //cout << "Debug\n";

      c = (char) encode[(int) c];
     // cout << "Debug\n";
      fout << c;
      //fout.put(c);
      //cout << "Debug\n";
   }

   fin.close();
   fout.close();
   return(0);
}







