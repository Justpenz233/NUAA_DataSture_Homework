#include "zkw.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#define MAXN 1000
using namespace std;

int InternetNodeNum = 0; //����ڵ�����
int ConsumerNodeNum = 0; //���ѽڵ�����
int ServerCost = 0;      //ÿ̨����������
int EdgesNum = 0;        //������
MaxFlow Basic;

int Source;
int Des;

struct node
{
   int pos;
   int need;
   node(){};
   void init(int Tpos, int Nneed)
   {
      pos = Tpos;
      need = Nneed;
   }
   bool operator<(const node &t)
   {
      return need > t.need;
   }
};

node ConsumeNode[MAXN];

void init() //��ȡ��������ͼ
{
   freopen("F:\\DataStruteHomeWork\\11\\00.txt", "r", stdin);
   cin >> InternetNodeNum >> EdgesNum >> ConsumerNodeNum;

   cin >> ServerCost;
   Basic.ConsumerNodeNum = ConsumerNodeNum;
   Basic.InternetNodeNum = InternetNodeNum;
   Basic.ServerCost = ServerCost;

   Source = ConsumerNodeNum + InternetNodeNum;
   Des = Source + 1;
   Basic.init(Des + 1);

   //������ڵ�ı�
   for (int i = 1; i <= EdgesNum; i++)
   {
      int from, to, cap, cost;
      scanf("%d%d%d%d", &from, &to, &cap, &cost);
      Basic.add(from, to, cap, cost);
      Basic.add(to, from, cap, cost);
   }

   Basic.k = 0;
   //�����ѽڵ��
   for (int i = 1; i <= ConsumerNodeNum; i++)
   {
      int from, to, cap;
      scanf("%d%d%d", &from, &to, &cap);
      Basic.k += cap;
      Basic.add(from + InternetNodeNum, to, cap, 0);
      Basic.add(to, from + InternetNodeNum, cap, 0);
      Basic.add(from + InternetNodeNum, Des, cap, 0);
      ConsumeNode[i].init(to, cap);
   }
}

//������MCMF��flagΪ1ʱ����
int CalcMCMF(vector<int> &severs, bool flag)
{
   MaxFlow MCMF = Basic;
   for (int i = 0; i < severs.size(); i++)
      MCMF.add(Source, severs[i], INF, 0);
   int ans = MCMF.zkw(Source, Des, Basic.k);
   if (ans == -1)
      return -1;
   ans += ServerCost * severs.size();
   if (flag)
      return ans;
   MCMF.search_path();
   string s;
   MCMF.OutputPath(s);
   return ans;
}

//���������ѽڵ㰴�����С��������
//������ֱ�������ѽڵ��Ϸŷ�����
//���������Ŀ�ʼ�ţ������е�ʱ����ֹ
//�ٴ�������С�Ľڵ㿪ʼ��һ�ַ�������ֻҪ������У������ܳɱ��ܽ��ͣ��ͼ���
//����ٴ�����������һ�֡�
void Greedy()
{
   set<int> SConsume;
   vector<int> SeverPos;
   sort(ConsumeNode + 1, ConsumeNode + ConsumerNodeNum + 1);
   int ans = 0;
   for (int i = 1; i <= ConsumerNodeNum; i++) {
      SConsume.insert(ConsumeNode[i].pos);
      SeverPos.push_back(ConsumeNode[i].pos);
      ans = CalcMCMF(SeverPos, 1);
      if(ans != -1){
         break;
      }
   }

   vector<int> temp(SeverPos);
   for (auto i = SeverPos.end(); i != SeverPos.begin(); i--) {
      vector<int> t(temp);
      for (auto j = t.begin(); j != t.end(); j++) {
         if (*j == *i) {
            t.erase(j);
            break;
         }
      }
      int now = CalcMCMF(t, 1);
      if (now != -1 && now < ans) {
         ans = now;
         temp = t;
         SConsume.erase(*i);
      }
   }
   SeverPos = temp;

   for (int i = 1; i <= ConsumerNodeNum; i++){
      if (SConsume.find(ConsumeNode[i].pos) != SConsume.end()) {
         SeverPos.push_back(ConsumeNode[i].pos);
         int now = CalcMCMF(SeverPos, 1);
         if(now < ans)
            ans = now;
         else
            SeverPos.erase(SeverPos.end() - 1);
      }
   }
   cout << CalcMCMF(SeverPos, 0) << endl;
}

int main()
{
   init();
   //SA();
   Greedy();
   system("pause");
}