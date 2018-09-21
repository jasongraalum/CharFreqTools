#include <iostream>
#include <fstream>
#include <vector>

#define START_LETTER 'a'
#define END_LETTER 'z'
#define TERM_CHAR '{'

using namespace std;

char toLower(char c)
{
   if(c >= 'A' && c <= 'Z')
      return c-('Z'-'z');
   else
      return c;
}

int getIndex(char c)
{
   if(c == TERM_CHAR)
      return(26);
   else
      return(START_LETTER - c);
}


class charTreeNode {
   private:
      char c;
      charTreeNode *letterPtr[(END_LETTER - START_LETTER) + 2];
   public:
      charTreeNode()
      {
         //cout << "New Node" << endl;
         c = '_';
         for(int i = 0; i < (END_LETTER-START_LETTER)+2; ++i)
         {
            this->letterPtr[i] = NULL;
         }
      }
      char getLetter()
      {
         return this->c;
      }
      charTreeNode* getLetterPtr(int index)
      {
         return this->letterPtr[index];
      }
      void addLetter(char letter)
      {
         int index;
         charTreeNode *newNode;

         //cout << "Debug #1 " << c << " " << i << endl;
         //
         index = letter - START_LETTER;
         if(letter == TERM_CHAR)
         {
            index = 26;
         }

         //cout << "Debug #2" << endl;
         if(this->letterPtr[index] == NULL)
         {
         cout << "Adding letter " << letter << " below " << this->getLetter() << endl;
            //cout << "New letter " << c << " " << i << endl;
            newNode = new(charTreeNode);
            this->letterPtr[index] = newNode;
            this->c = letter;
         }
         else
         {
         cout << letter << " already exists below " << this->getLetter() << endl;
         }
         return;
      }
      charTreeNode* getCharNode(char letter)
      {
         if(letter == TERM_CHAR)
            return letterPtr[26];
         else
            return letterPtr[letter - START_LETTER];
      }
};

class charTree {
   private:
      charTreeNode *top;
      int totalWords;
   public:
      charTree()
      {
         //cout << "New Tree" << endl;
         top = new(charTreeNode);
         totalWords = 0;
      }
      void addWord(string word)
      {
         char letter;
         charTreeNode *current;

         current = top;
         while(word.length() > 0)
         {
            letter = toLower(word[0]);
            if(((letter >= START_LETTER) && (letter <= END_LETTER)) || (letter == TERM_CHAR))
            {
               cout << "Adding " << letter << endl;
               cout << "1 " << &current << endl;
               current->addLetter(letter);
               current = current->getLetterPtr(getIndex(letter));
               cout << "2 " << current->getLetterPtr(getIndex(letter)) << endl;
               cout << "3 " << &current << endl;
            }
            word.erase(0,1);
         }
         current->addLetter(TERM_CHAR);
         totalWords++;
         return;
      }
      void dumpTree()
      {
         //cout << "Debug #0" << endl;
         dumpTree(this->top,"");
      }
      void dumpTree(charTreeNode *head, string space)
      {
         charTreeNode *nextLetter;
         //cout << "Debug #2" << endl;
         //if(head == NULL)
         //   head = this->top;

         nextLetter = head->getLetterPtr(26);

         if(nextLetter)
         {
            cout << space << nextLetter->getLetter() << endl;
         }

         for(int i = 0; i <= (END_LETTER - START_LETTER); ++i)
         {
            char c = START_LETTER + i; 
            if(i == 26) c = TERM_CHAR;

            //cout << "Checking " << c << endl; 
            nextLetter = head->getLetterPtr(i);
            if(nextLetter)
            {
               cout << space << nextLetter->getLetter() <<  endl;
               dumpTree(nextLetter, space + " ");
            }
         }

      }
      void dumpTreeFlat()
      {
         dumpTreeFlat(this->top, NULL,0);
      }
      void dumpTreeFlat(string dataFileName)
      {
         ofstream *outDataFile;
         outDataFile = new ofstream(dataFileName, std::ios::out);
         dumpTreeFlat(this->top, outDataFile,0);
         outDataFile->close();
      }
      void dumpTreeFlat(charTreeNode *head, ofstream *dataFile, int level)
      {
         charTreeNode *letterPtr;
         level++;

         if(dataFile)
            *dataFile << head->getLetter() << "-> ";
         else
            cout << head->getLetter() << "-> ";

         for(int index = 0; index < (END_LETTER - START_LETTER)+2; ++index)
         {
            char c = START_LETTER + index;
            letterPtr = head->getLetterPtr(index);
            if(letterPtr != NULL)
               if(dataFile)
                  *dataFile << "1 ";
               else
                  cout << c << " 1 ";
            else
               if(dataFile)
                  *dataFile << "0 ";
               else
                  cout << c << " 0 ";
         }
         if(dataFile)
            *dataFile << endl;
         else
            cout << endl;

         for(int index = 0; index < (END_LETTER - START_LETTER)+2; ++index) { 

            char c = index + START_LETTER; 

            if(index == 26) 
               c = TERM_CHAR; 

            letterPtr = head->getLetterPtr(index);

            if(letterPtr != NULL)
            {
               cout << "Looking at: " << head->getLetter() << endl;
               dumpTreeFlat(head->getLetterPtr(index), dataFile, level);
            }

         }

      }
      void loadTreeFlat(string dataFileName)
      {
         ifstream *inDataFile;
         inDataFile = new ifstream(dataFileName, std::ios::in);
         cout << "Loading " << dataFileName << endl;
         loadTreeFlat(this->top, inDataFile);
         inDataFile->close();

      }
      void loadTreeFlat(charTreeNode *head, ifstream *dataFile)
      {
         charTreeNode *letterPtr;
         char line_char;
         
         cout << "Loading letter: " << line_char << endl;
         for(int index = 0; index < (END_LETTER - START_LETTER)+2; ++index)
         {
            long int n;
            char c = START_LETTER + index;
            if(index == 26)
               c = TERM_CHAR;

            *dataFile >> n;
            if(n == 1)
            {
               //cout << "Adding " << n << " " << c << endl;
               head->addLetter(c);
            }
         }

         for(int index = 0; index < (END_LETTER - START_LETTER)+2; ++index)
         {
            letterPtr = head->getLetterPtr(index);
            if(letterPtr != NULL)
            {
               loadTreeFlat(head->getLetterPtr(index), dataFile);
            }
         }

      }

      vector<string> findWord(int length)
      {
         return(findWords(this->top,"",length));
      }
      vector<string> findWord(string prefix, int length)
      {
         vector<string> foundwords;
         vector<string> words;
         string fullword;
         charTreeNode *current;

         current = this->top;
         for(int i = 0; i < prefix.length(); ++i)
         {
            if(current->getLetterPtr(prefix[i] - START_LETTER) == NULL)
               return vector<string>();
            current = current->getLetterPtr(prefix[i] - START_LETTER);
         }
         foundwords = findWords(current,"",length-prefix.length());
         for(vector<string>::iterator it = foundwords.begin(); it != foundwords.end(); ++it)
         {
            fullword = prefix + *it;
            //cout << "Adding prefix " << prefix << " to " << *it << endl;
            words.push_back(fullword);
         }
         return(words);

            

      }
      vector<string> findWords(charTreeNode *head, string prefix, int length)
      {
         vector<string> words;
         charTreeNode *current;
         current = head;
         if(length == 0) 
         {
            if(current->getLetterPtr(26) != NULL)
            {
               //cout << "Found word " << prefix << endl;
               words.push_back(prefix);
               return(words);
            }
            else 
            {
               //cout << "No word" << endl;
               return vector<string>();
            }
         }
         else
         {
            for(int i = 0; i < (END_LETTER - START_LETTER); ++i)
            {
               charTreeNode *nextLetter;
               nextLetter = current->getLetterPtr(i);
               char c = START_LETTER + i;
               if(nextLetter != NULL)
               {
                  //cout << "Looking at " << c << " for size " << length << endl;
                  vector<string> newwords;
                  string newprefix = prefix + c;
                  newwords = findWords(nextLetter, newprefix, length-1);
                  if(newwords.size() > 0)
                  {
                     //cout << "Merging words" << endl;
                     //cout << "New words size = " << newwords.size() << endl;
                     //cout << "\tNew word[1] = " << newwords.front() << endl;
                     //cout << "Existing words size = " << words.size() << endl;
                     words.insert(words.end(), newwords.begin(), newwords.end());
                     //cout << "Words size = " << words.size() << endl;
                  }
               }
            }
            return(words);
         }
      }
      charTreeNode *getCharNode()
      {
         return(top);
      }


};

int main(int argc, char* argv[])
{

   charTree *root, *root2, *root3, *root4;
   ifstream inFile;
   string word;
   vector<string> foundWords;

   ofstream *outDataFile;
   ifstream *inDataFile;

   root = new(charTree);
   root2 = new(charTree);
   root3 = new(charTree);
   root4 = new(charTree);

   inFile.open(argv[1],ios::in);
   while(inFile >> word)
   {
      root->addWord(word);
   }
   inFile.close();
   //root->dumpTreeFlat("dumpData.out");
   //root->dumpTreeFlat();

   /*
   inFile.open(argv[2],ios::in);
   while(inFile >> word)
   {
      root2->addWord(word);
   }
   inFile.close();

   root->dumpTreeFlat("dumpData.out");
   root2->dumpTreeFlat("dumpData2.out");
   //return(0);


   root->loadTreeFlat("dumpData.out");
   root->loadTreeFlat("dumpData2.out");

   root->dumpTreeFlat("dumpDataF.out");
   //root2->dumpTreeFlat("dumpDataF2.out");

   return(0);



   
   
   foundWords = root->findWord("ab", 4);
   cout << foundWords.size() << " words found" << endl;
   for(vector<string>::iterator it = foundWords.begin(); it != foundWords.end(); ++it)
      cout << *it << endl;
   foundWords = root->findWord("ab", 3);
   cout << foundWords.size() << " words found" << endl;
   for(vector<string>::iterator it = foundWords.begin(); it != foundWords.end(); ++it)
      cout << *it << endl;
   */



}

