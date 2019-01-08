#include <iostream>
#include <cstring>
using namespace std;
#define Famale 0
#define Male 1
struct TEL
{
   bool is;
   char phone[20];
   char email[50];
   char name[20];
   int sex;
   void getCin(istream &INPUT){
      string see;
      INPUT >> name >> see >> phone >> email;
      if(see == "ÄÐ")
         sex = Male;
      else
         sex = Famale;
   }
   TEL() : is(0){};
   unsigned int Hash1(){
      unsigned int hash = 0;
      for (int i = 0; i < strlen(phone);i ++){
         hash = hash * 31 + phone[i];
      }
      hash %= 43;
      return abs(hash);
   }
   unsigned int Hash2(){
      unsigned int hash = 0;
      for (int i = 0; i < strlen(phone); i++)
         hash = hash * 10 + (phone[i] - '0');
      hash %= 43;
      return abs(hash);
   }
};

TEL* HashTable[43];


bool serch(TEL t,int i){
   int key = t.Hash1();
   int step = t.Hash2();
}

bool insert(TEL t)
{
   for (int i = 1; i * 2 <= 43; i ++){

   }
}

int main()
{
}