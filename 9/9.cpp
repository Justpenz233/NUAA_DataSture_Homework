#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;
struct TEL
{
   char phone[20];
   char email[50];
   char name[20];
   char sex[10];
   int count = 0;

   TEL(string s){
      memcpy(phone, s.c_str(),sizeof(phone));
   }
   TEL(){};

   void getCin(istream &INPUT){
      string see;
      INPUT >> name >> sex >> phone >> email;
   }
   void show(){
      printf("%s %s %s %s ɢ�д���:%d\n\n", name, sex, phone, email, count);
   }

   unsigned int Hash1(){
      unsigned int hash = 0;
      for (int i = 0; i < strlen(phone);i ++){
         hash = hash * 31 + phone[i];
      }
      hash %= 43;
      return abs((int)hash);
   }
   unsigned int Hash2(){
      unsigned int hash = 0;
      for (int i = 0; i < strlen(phone); i++)
         hash = hash * 10 + (phone[i] - '0');
      hash %= 43;
      return abs((int)hash);
   }

   bool equal(TEL t){
      if(strlen(t.phone) != strlen(phone))
         return 0;
      for (int i = 0; i < strlen(phone);i ++)
         if(t.phone[i] != phone[i])
            return 0;
      return 1;
   }
};

TEL* HashTable[43];

int serch(TEL t){
   int key = t.Hash1();
   int step = t.Hash2();
   int hash = 0;
   while (HashTable[key] != NULL && (++hash) < 43){
      if (HashTable[key]->equal(t)) {
         HashTable[key]->count = hash;
         return key;
      }
      key += step;
      key %= 43;
   }
   if(hash == 43)
      return -1;
   else
      return key;
}

int serch(string s){
   TEL t(s);
   int key = t.Hash1();
   int step = t.Hash2();
   int hash = 0;
   while (HashTable[key] != NULL && (++hash) < 43) {
      if(HashTable[key]->equal(t)){
         HashTable[key]->count = hash;
         return key;
      }
      key += step;
      key %= 43;
   }
   if(hash == 43)
      return -1;
   else
      return key;
}

bool insert(TEL *t)
{
   int k = serch(*t);
   if(k == -1)
      return 0;
   else{
      HashTable[k] = t;
      serch(*t);
      return 1;
   }
}

void init(){
   for (int i = 0; i < 43;i ++)
      HashTable[i] = NULL;
   string FILEPATH;
   printf("�����������ļ�·����");
   cin >> FILEPATH;
   ifstream FILE;
   FILE.open(FILEPATH, ios::in);
   if(!FILE.good()){
      printf("Open FILE Failed");
      exit(0);
   }
   else
      printf("�ļ��򿪳ɹ���\n���ݵ���ɹ�");
   
   int debug = 0;
   while(!FILE.eof()){
      debug++;
      TEL *t = new TEL;
      t->getCin(FILE);
      insert(t);
   }
}

void GetASL(){
   double NodeNum = 0;
   double HashTime = 0;
   for (int i = 0; i < 43;i ++){
      if(HashTable[i]){
         NodeNum++;
         HashTime += HashTable[i]->count;
      }
   }
   double t = HashTime / NodeNum;
   printf("ƽ�����ҳ���Ϊ: %lf\n", t);
}

int main()
{
   init();
   GetASL();
   string s = "";
   while(s != "#"){
      printf("��������Ҫ���ҵĺ���:(����#��������): ");
      cin >> s;
      if(s == "#")
         return 0;
      if(s.length() != 11){
         printf("��������ȷ�ĵ绰����\n\n");
         continue;
      }
      int k = serch(s);
      if(k == -1 || HashTable[k] == NULL){
         printf("��Ҫ���ҵĺ��벻����\n\n");
      }
      else
         HashTable[k]->show();
   }
   system("pause");
}