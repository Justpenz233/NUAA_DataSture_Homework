#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#define MAXN 1000
using namespace std;
vector<int> v[MAXN];//��ߵ���һ����
vector<int> w[MAXN];//��ߵı�Ȩ
vector<int> C[MAXN];//��ߵı��

vector<int> ans1;//��ؼ��
vector<int> ans2;//��ؼ�·��

int ve[MAXN], vl[MAXN];
int indegree[MAXN];
int n, m;
void FindInDegree(){
   //����ÿ��������
   memset(indegree, 0, sizeof(indegree));
   for (int i = 1; i <= n;i ++){
      for (int j = 0; j < v[i].size();i ++){
         indegree[v[i][j]]++;
      }
   }
}

//������������ �������T��
bool TopSort(stack<int> &T){
   int count = 0, k;
   FindInDegree();
   stack<int> s;
   for (int i = 1; i <= n; i ++)
      if (indegree[i] == 0)
         s.push(i);
   count = 0;
   for (int i = 1; i <= n; i ++)
      ve[i] = 0;
   while (!s.empty()) {
      int j = s.top();
      s.pop();
      T.push(j);
      ++count;
      for (int i = 0; i < v[j].size();i ++) {
         int k = v[j][i];
         if (--indegree[k] == 0)
            s.push(k);
         if (ve[j] + w[j][i] > ve[k])
            ve[k] = ve[j] + w[j][i];
      }
   }
   if (count < n)
      return 0; // ���������л�·
   else
      return 1;
}

void POP(stack<int> &T,int &j)
{
   j = T.top();
   T.pop();
}

bool CriticalPath()
{
   // GΪ�����������G�ĸ���ؼ����
   stack<int> T;
   int j, k, el, ee, dut;
   char tag;
   if (!TopSort(T))
      return 0;
   for (int i = 1; i <= n; i ++)
      vl[i] = ve[n]; // ��ʼ�������¼�����ٷ���ʱ��

   while (!T.empty()){
      POP(T, j);
      for (int i = 0; i < v[j].size(); i++) {
         k = v[j][i];
         dut = w[j][i]; //dut<j,k>
         if (vl[k] - dut < vl[j])
            vl[j] = vl[k] - dut;
            //����VL
      }
   }

   //�������� ��ؼ��
   for (j = 1; j <= n;j ++) // ��ee,el�͹ؼ��
      for (int i = 0; i < v[j].size(); i++) {
         k = v[j][i];
         dut = w[j][i];
         ee = ve[j];
         el = vl[k] - dut;
         if(ee == el)
            ans1.push_back(C[j][i]);
      }

   for (int i = 1; i <= n;i ++)
      if(vl[i] == ve[i])
         ans2.push_back(i);

   return 1;
}

int main()
{
   freopen("F:\\DataStruteHomeWork\\7\\7.txt", "r", stdin);
   cin >> n >> m;
   for (int i = 1; i <= m;i ++){
      int x, y, c;
      scanf("%d%d%d", &x, &y, &c);
      v[x].push_back(y);
      w[x].push_back(c);
      C[x].push_back(i);
   }
   if (!CriticalPath()){
      printf("ͼ�л�\n");
      exit(0);
   }
   printf("�ؼ�����Ϊ: ");
   for (int i = 0; i < ans1.size();i ++) {
      printf("%d ", ans1[i]);
   }
   printf("\n�ؼ�·�����Ϊ: ");
   for (int i = 0; i < ans2.size(); i++) {
      printf("%d ", ans2[i]);
   }
}