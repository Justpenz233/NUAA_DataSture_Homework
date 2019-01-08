#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
struct TEL
{
   char phone[20];
   char email[50];
   char name[20];
   char sex[10];

   TEL(string s){
      memcpy(phone, s.c_str(),szieof(phone));
   }
   TEL(){};

   void getCin(istream &INPUT){
      string see;
      INPUT >> name >> sex >> phone >> email;
   }
   void show(){
      printf("%s %s %s %s\n", name, sex, phone, email);
   }

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

   bool operator ==(const TEL &t){
      return memcmp(phone, t.phone, sizeof(phone)) == 0;
   }
};

TEL* HashTable[43];
int len[43];

int serch(TEL t){
   int key = t.Hash1();
   int step = t.Hash2();
   int hash = 0;
   while(HashTable[key] != NULL && ++hash < 43){
      key += step;
      if(*HashTable[key] == t){
         len[key] = has;
         return key;
      }
   }
   if(hash == 43)
      return -1;
}

int serch(string s){
   TEL t(s);
   int key = t.Hash1();
   int step = t.Hash2();
   int hash = 0;
   while(HashTable[key] != NULL && ++hash < 43){
      key += step;
      if(*HashTable[key] == t){
         len[key] = hash;
         return key;
      }
   }
   if(hash == 43)
      return -1;
}

bool insert(TEL *t)
{
   int k = serch(*t);
   if(k != -1)
      return 0;
   else
      HashTable[k] = t;
}

void init(){
   ifstream FILE;
   //string s;
   //cin >> s;
   FILE.open("C:\\Users\\Justpenz233\\Desktop\\DataStrure\\9\\data.txt");
   if(!FILE.good()){
      printf("Open FILE Failed");
      exit(0);
   }
   while(!FILE.eof()){
      TEL *t = new TEL;
      t->getCin(FILE);
      insert(t);
   }
}

int main()
{
   init();
   for (int i = 0; i < 43;i ++)
      HashTable[i]->show();
   system("pause");
}