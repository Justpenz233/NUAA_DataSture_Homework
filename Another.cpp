#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct TREE{
   string key;
   string value;//���Ϊ "key":"value"
   vector<TREE* > next; //��ŵ�ǰ�ڵ�ĺ����ǣ�ʹ�ò���������
   TREE(){};
   TREE(string s1, string s2) : key(s1), value(s2){}; //���캯��
   void push(TREE* T){
      next.push_back(T);
      //����һ���º��ӣ����ӵĵ�ַΪT
   }
};

void format(string &s) {
   for (int i = 0; i < s.size(); ++i)
      if (s[i] == '\\')
         s.erase(s.begin() + i);
}//���ַ���s��˫б��ɾ��һ������ɵ�б��

//fatherΪ��ǰ�ڵ�ĸ��׵�ַ��PattenΪ��������ַ�����preΪ���׵�keyֵ
//�ݹ鴦��������ַ���s����������Ϊ��
//���json��Ƕ�׵ģ������׵�key��Ϊpre�����׵ĵ�ַ��Ϊ������
void work(TREE* father,string &Patten, string &Pre) {
   
   string key, value;
   for (int i = 0; i != Patten.size(); ++i) {
      if (Patten[i] == '"') {
         int j = Patten.find(":", i + 1);
         key = Patten.substr(i + 1, j - i - 2);
         
         if (Pre != "")
            key = Pre + "." + key;
         //���pre��Ϊ�գ���ô�㴦��Ľڵ�keyΪ  pre.key:value
         //pre�ĵ�ַΪfather
         
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
         }//���û��ð�ţ�����������ַ�����һ������������ ��ô˵�����ڴ������Ҷ�ӽڵ�

         //����˵����ǰ�ڵ���һ��OBJECT��Ҫ�ݹ���ȥ����
         else{
            int len = 1;
            i = j + 2;
            while (len != 0)
            {
               if (Patten[i] == '{') ++len;
               else if (Patten[i] == '}') --len;
               ++i;
            }//���while�����������ź������ŵ�λ��
            //ע���м�������ŵ�Ƕ�� ����{{{{}}}}������Ҫ��������������
            //����len���ڵ������ŵ�����������������++ ����������--
            //i���մ��������������ŵ�λ��

            value = Patten.substr(j + 1, i - j - 1);
            //��{��}�м�Ķ�����ȡ����������value����

            TREE* now = new TREE(key, value);
            father->push(now);
            work(now, value, key);//�ݹ����
         }

      }
   }
}

//���Ҳ������᷵��һ���ڵ��ַ
//PattenΪ����Ҫ���ҵ��ַ���
TREE* serch(TREE *now,string Patten){
   if(now->key == Patten)
      return now;//����ҵ��� ���ص�ǰ�ĵ�ַ

   //������ǰ�ڵ����еĺ���
   for (int i = 0; i < now->next.size();i ++){
      string s = now->next[i]->key;
      //sΪ��ǰ�ڵ㺢�ӵ�key
      
      //һ����˵ Patten�ǳ�������ӵ�  s.****.*****
      //�������ǰ�Pattenǰ��λ�������s�Ա�
      if(s == Patten.substr(0,s.length())){
         TREE *t = serch(now->next[i], Patten);
         if (t != NULL)
            return t;
      }
   }
   return NULL;//û�ҵ��ͷ���NULL
}

int main()
{
   freopen("1.txt", "r", stdin);
   
   int n = 0, m = 0;
   cin >> n >> m;
   string s, Patten;
   string::iterator it;

   getline(cin, s);//����һ��
   for (int i = 0; i != n; ++i){
      getline(cin, s);
      for (int j = 0; j < s.length();j ++){
         if(!isspace(s[j]))
            Patten += s[j];
      }
   }//���for����ȥ����������Ŀո�

   TREE *root = new TREE();
   string Pre;
   work(root, Patten, Pre);//������

   for (int i = 0; i != m; ++i) {
      cin >> s;
      TREE* flag = serch(root, s);
      if(flag == NULL){
         printf("NOTEXIST\n");
         continue;
      }//û�ҵ�

      if(flag->next.size() == 0)//�ҵ��Ľڵ���һ��Ҷ��
         printf("STRING %s\n", flag->value.c_str());
      else//�ҵ��Ĳ���Ҷ��
         printf("OBJECT\n");
   }
}
