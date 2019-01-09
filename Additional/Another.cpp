#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct TREE{
   string key;
   string value;//存放为 "key":"value"
   vector<TREE* > next; //存放当前节点的孩子们，使用不定长数组
   TREE(){};
   TREE(string s1, string s2) : key(s1), value(s2){}; //构造函数
   void push(TREE* T){
      next.push_back(T);
      //加入一个新孩子，孩子的地址为T
   }
};

void format(string &s) {
   for (int i = 0; i < s.size(); ++i)
      if (s[i] == '\\')
         s.erase(s.begin() + i);
}//将字符串s的双斜杠删除一个，变成单斜杠

//father为当前节点的父亲地址，Patten为待处理的字符串，pre为父亲的key值
//递归处理输入的字符串s，具体流程为：
//如果json是嵌套的，将父亲的key记为pre，父亲的地址作为参数传
void work(TREE* father,string &Patten, string &Pre) {
   
   string key, value;
   for (int i = 0; i != Patten.size(); ++i) {
      if (Patten[i] == '"') {
         int j = Patten.find(":", i + 1);
         key = Patten.substr(i + 1, j - i - 2);
         
         if (Pre != "")
            key = Pre + "." + key;
         //如果pre不为空，那么你处理的节点key为  pre.key:value
         //pre的地址为father
         
         if (Patten[j + 1] == '"') {
            if (Patten.find(",", j + 1) != string::npos)
               i = Patten.find(",", j + 1);
            else
               i = Patten.size() - 1;
            value = Patten.substr(j + 2, i - j - 3);
            format(key);
            format(value);
            TREE* now = new TREE(key, value);
            father->push(now);
         }//如果没有冒号，及待处理的字符串下一个符号是引号 那么说明现在处理的是叶子节点

         //否则说明当前节点是一个OBJECT，要递归下去操作
         else{
            int len = 1;
            i = j + 2;
            while (len != 0)
            {
               if (Patten[i] == '{') ++len;
               else if (Patten[i] == '}') --len;
               ++i;
            }//这个while是在找左括号和右括号的位置
            //注意中间会有括号的嵌套 比如{{{{}}}}，我们要找最外侧的右括号
            //所以len存在的是括号的数量，遇到左括号++ 遇到右括号--
            //i最终存的是最外侧右括号的位置

            value = Patten.substr(j + 1, i - j - 1);
            //把{和}中间的东西提取出来，存在value里面

            TREE* now = new TREE(key, value);
            father->push(now);
            work(now, value, key);//递归过程
         }

      }
   }
}

//查找操作，会返回一个节点地址
//Patten为我们要查找的字符串
TREE* serch(TREE *now,string Patten){
   if(now->key == Patten)
      return now;//如果找到了 返回当前的地址

   //遍历当前节点所有的孩子
   for (int i = 0; i < now->next.size();i ++){
      string s = now->next[i]->key;
      //s为当前节点孩子的key
      
      //一般来说 Patten是长这个样子的  s.****.*****
      //所以我们把Patten前几位提出来跟s对比
      if(s == Patten.substr(0,s.length())){
         TREE *t = serch(now->next[i], Patten);
         if (t != NULL)
            return t;
      }
   }
   return NULL;//没找到就返回NULL
}

int main()
{
   freopen("1.txt", "r", stdin);
   
   int n = 0, m = 0;
   cin >> n >> m;
   string s, Patten;
   string::iterator it;

   getline(cin, s);//读入一行
   for (int i = 0; i != n; ++i){
      getline(cin, s);
      for (int j = 0; j < s.length();j ++){
         if(!isspace(s[j]))
            Patten += s[j];
      }
   }//这个for是在去掉输入里面的空格

   TREE *root = new TREE();
   string Pre;
   work(root, Patten, Pre);//主过程

   for (int i = 0; i != m; ++i) {
      cin >> s;
      TREE* flag = serch(root, s);
      if(flag == NULL){
         printf("NOTEXIST\n");
         continue;
      }//没找到

      if(flag->next.size() == 0)//找到的节点是一个叶子
         printf("STRING %s\n", flag->value.c_str());
      else//找到的不是叶子
         printf("OBJECT\n");
   }
}
