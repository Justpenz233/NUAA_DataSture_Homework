#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;
struct TEL
{
   char phone[20];//电话
   char email[50];//邮箱
   char name[20];//名字
   char sex[10];//性别
   int count = 0;//Hash次数

   TEL(string s){
      memcpy(phone, s.c_str(),sizeof(phone));
   }
   TEL(){};
   //构造函数

   void getCin(istream &INPUT){
      string see;
      INPUT >> name >> sex >> phone >> email;
   }//读入结构体

   void show(){
      printf("%s %s %s %s 散列次数:%d\n\n", name, sex, phone, email, count);
   }

   unsigned int Hash1(){
      unsigned int hash = 0;
      for (int i = 0; i < strlen(phone);i ++){
         hash = hash * 31 + phone[i];
      }
      hash %= 43;
      return abs((int)hash);
   }//BDKR哈希，可以自然溢出

   unsigned int Hash2(){
      unsigned int hash = 0;
      for (int i = 0; i < strlen(phone); i++)
         hash = hash * 10 + (phone[i] - '0');
      hash %= 43;
      return abs((int)hash);
   }//哈希2

   bool equal(TEL t){
      if(strlen(t.phone) != strlen(phone))
         return 0;
      for (int i = 0; i < strlen(phone);i ++)
         if(t.phone[i] != phone[i])
            return 0;
      return 1;
   }//判断两个信息是否相等
};

TEL* HashTable[43];
//哈希表

//查询是否存在
int serch(TEL t){
   int key = t.Hash1();//起始键值为key
   int step = t.Hash2();//步长为step
   int hash = 0;
   while (HashTable[key] != NULL && (++hash) < 43){
      if (HashTable[key]->equal(t)) {
         HashTable[key]->count = hash;
         return key;
      }
      key += step;
      key %= 43;
   }//遍历hash表
   if(hash == 43)
      return -1;//没找到
   else
      return key;
}

//查询某个电话是否存在，函数重载
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

//插入一个信息到哈希表中
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

//从文件读取信息
void init(){
   for (int i = 0; i < 43;i ++)
      HashTable[i] = NULL;
   string FILEPATH;
   printf("请输入数据文件路径：");
   cin >> FILEPATH;
   ifstream FILE;
   FILE.open(FILEPATH, ios::in);
   if(!FILE.good()){
      printf("Open FILE Failed");
      exit(0);
   }
   else
      printf("文件打开成功。\n数据导入成功");
   
   int debug = 0;
   while(!FILE.eof()){
      debug++;
      TEL *t = new TEL;
      t->getCin(FILE);
      insert(t);
   }
}

//求ASL
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
   printf("平均查找长度为: %lf\n", t);
}

int main()
{
   init();
   GetASL();
   string s = "";
   while(s != "#"){
      printf("请输入您要查找的号码:(输入#结束程序): ");
      cin >> s;
      if(s == "#")
         return 0;
      if(s.length() != 11){
         printf("请输入正确的电话号码\n\n");
         continue;
      }
      int k = serch(s);
      if(k == -1 || HashTable[k] == NULL){
         printf("您要查找的号码不存在\n\n");
      }
      else
         HashTable[k]->show();
   }
   system("pause");
}