#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#define INF 100000000
#define MAXN 100
double Graph[MAXN][MAXN];
double dis[MAXN];
bool vis[MAXN];
int n;

void dijstrka(int u){

   for (int i = 1; i <= n;i ++)
      dis[i] = INF;
   memset(vis, 0, sizeof(vis));
   int start = u;
   vis[start] = 1;
   for (int i = 1; i <= n; i++)
      dis[i] = min(dis[i], Graph[start][i]);

   for (int i = 1; i <= n - 1; i++) {
      int minn = 9999999;
      for (int j = 1; j <= n; j++){
         if (vis[j] == 0 && minn > dis[j]){
            minn = dis[j];
            start = j;
         }
      }
      vis[start] = 1;
      for (int j = 1; j <= n; j++)
         dis[j] = min(dis[j], dis[start] + Graph[start][j]);
   }
   for (int i = 1; i <= n;i ++){
      printf("%lf\t", dis[i]);
   }
   printf("\n");
}

void floyd(){
   double f[MAXN][MAXN];

   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
         f[i][j] = Graph[i][j];

   for (int k = 1; k <= n;k ++)
      for (int i = 1; i <= n;i ++)
         for (int j = 1; j <= n;j ++)
            f[i][j] = min(f[i][k] + f[k][j], f[i][j]);

   
   for (int i = 1; i <= n;i ++){
      for (int j = 1; j <= n; j++)
         printf("%lf\t", f[i][j]);
      printf("\n");
   }
   printf("\n");
}

int main()
{
   ifstream FILE;
   string FileName;
   printf("请输入文件路径: ");
   cin >> FileName;
   FILE.open(FileName, ios::in);
   if(!FILE.good()){
      printf("文件打开失败\n");
      exit(0);
   }
   FILE >> n;
   for (int i = 1; i <= n;i ++)
      for (int j = 1; j <= n;j ++)
         FILE >> Graph[i][j];
   printf("Floyd result:\n");
   floyd();
   printf("Dijstrka result:\n");
   for (int i = 1; i <= n;i ++)
      dijstrka(i);
   
}