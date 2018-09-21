#include <iostream>
#include <string>
#include <fstream>

using namespace std;

typedef struct wordItem
{
   short int size;
   int count;
   string word;
} wordItem;


typedef struct wordTreeNode
{
   wordItem *item;
   wordTreeNode *right;
   wordTreeNode *left;
} wordTreeNode;

   
wordTreeNode* addItem(wordTreeNode *root, string value)
{
   wordTreeNode *newNode;
   wordItem *newItem;
   if(root->item->word == value)
   {
      root->item->count++;
      return(root);
   }
   else if(root == NULL)
   {
      cout << "Adding " << value << endl;
      newNode = new(wordTreeNode);
      newItem = new(wordItem);
      newItem->word = value;
      newItem->size = value.length();
      newNode->item = newItem;
      newNode->right = NULL;
      newNode->left = NULL;
      return(newNode);
   }
   else if(value > root->item->word)
   {
      if(root->right == NULL)
      {
         cout << "Adding to right " << value << endl;
         cout << "\tBelow " << root->item->word << endl;
         newNode = new(wordTreeNode);
         newItem = new(wordItem);
         newItem->word = value;
         newItem->size = value.length();
         newNode->item = newItem;
         newNode->right = NULL;
         newNode->left = NULL;
         root->right = newNode;
      }
      else
      {
         addItem(root->right, value);
      }
   }
   else
   {
      if(root->left == NULL)
      {
         cout << "Adding to left " << value << endl;
         cout << "\tBelow " << root->item->word << endl;
         newNode = new(wordTreeNode);
         newItem = new(wordItem);
         newItem->word = value;
         newItem->size = value.length();
         newNode->item = newItem;
         newNode->right = NULL;
         newNode->left = NULL;
         root->left = newNode;
      }
      else
      {
         addItem(root->left, value);
      }
   }
   return(root);
}

int displayWordTree(wordTreeNode *root)
{
   if(root->right != NULL)
      displayWordTree(root->right);
   if(root->left != NULL)
      displayWordTree(root->left);
   cout << "Word: " << root->item->word << endl;
   cout << "\tCount: " << root->item->count << endl;
   return(0);
}



int main(void)
{
   wordTreeNode *head;

   string testList[10] = {"bob", "apple", "cherry", "walnut", "orange", "lemon", "watermelon", "pear", "apricot", "banana"};


   for(int i = 0; i < 10; ++i)
   {
      head = addItem(head,testList[i]);
   }
   displayWordTree(head);
   cout << "Size of data " << sizeof(head) << endl;

   return(0);

}


