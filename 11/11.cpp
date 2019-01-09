#include <bits/stdc++.h>
#include "zkw.h"
using namespace std;

int InternetNodeNum = 0;//����ڵ�����
int ConsumerNodeNum = 0;//���ѽڵ�����
int ServerCost = 0;     //ÿ̨����������
int EdgesNum = 0;       //������
MaxFlow Basic;

int Source;
int Des;

void init()//��ȡ��������ͼ
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
   for (int i = 1; i <= EdgesNum;i ++){
      int from, to, cap, cost;
      scanf("%d%d%d%d", &from, &to, &cap, &cost);
      Basic.add(from, to, cap, cost);
      Basic.add(to, from, cap, cost);
   }

   //�����ѽڵ��
   for (int i = 1; i <= ConsumerNodeNum;i ++){
      int from, to, cap, cost;
      scanf("%d%d%d", &from, &to, &cap);
      Basic.k += cap;
      Basic.add(from + InternetNodeNum, to, cap, 0);
      Basic.add(to, from + InternetNodeNum, cap, 0);
      Basic.add(from + InternetNodeNum, Des, cap, 0);
   }
}

//������MCMF��flagΪ1ʱ����
int CalcMCMF(vector<int> &severs,string &s,bool flag){
   for (int i = 0; i < severs.size(); i++)
      MCMF->add(Source, servers[i], INF, 0);
   int ans = MCMF.zkw(s, t, ob.k);
   ans += serverCost * severs.size();
   if(flag)
      return ans;
   MCMF.search_path();
   MCMF.OutputPath(str);
   return ans;
}

void SA(int outerTimes, int interTimes, double deCold, double p, double curT) {
   int lastCost;
   int curCost;
   for(int curOuter = 0; curOuter < outerTimes; curOuter++)
	{
		for(int curInter = 0; curInter < interTimes; curInter++)
		{
         while(1){
            double ran = 1;
            while(ran == 1){
               ran = rand() / double(RAND_MAX);
            }
            double lowToMid = 0.6;
            double midToHigh = 0.8;
            if(ran < lowToMid){

               

            }//��һ����
            else if(ran < midToHigh){



            }//��һ����
            else{


            }//��һ����



            if(curCost < lastCost){

               break;
            }//���ܸ��Ž�
            metropolis = exp(-(double)(curCost - lastCost) / curT);
            
            if (metropolis >= p){
               
               break;
            }//���ܴ��Ž�
         }
      }
      curT *= deCold;
   }
}

int main(){
   init();
   SA();
   while(1)
      ;
}