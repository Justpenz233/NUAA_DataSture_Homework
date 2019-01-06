#include <windows.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <map>
using namespace std;
#define MAX_EDGE 1000
#define MAX_NODE 1000
#define INF 100000000

struct edge{
	int to;
	int from;
	double weight;
	bool operator < (const edge & b) {
		return weight < b.weight;
	}
};

struct Kruskal
{
	vector<edge> Graph;
	int Vnum;
	int fa[MAX_NODE];

	Kruskal(int k, vector<edge> t) : Vnum(k), Graph(t) {
		for (int i = 1; i <= Vnum; i++)
		  fa[i] = i;
	};

	int find(int x){
		while (x != fa[x])
			x = fa[x] = fa[fa[x]];
		return x;
	}

	void work() {
		vector<int> v[Vnum + 1];
		int cnt = 0;
		double ans = 0;
		sort(Graph.begin(), Graph.end());
		for (int i = 0; i < Graph.size();i ++){
			int eu = find(Graph[i].from), ev = find(Graph[i].to);
			if(eu == ev)
				continue;
			ans += Graph[i].weight;
			fa[ev] = eu;
			v[Graph[i].from].push_back(Graph[i].to);
			v[Graph[i].to].push_back(Graph[i].from);
			cnt++;
			if(cnt == Vnum - 1)
				break;
		}

		printf("Kruskal生成的最小生成树权值和为: %lf\n", ans);
		for (int i = 1; i <= Vnum; i++){
			printf("%d: ", i);
			for (int j = 0; j < v[i].size();j ++){
				printf("%d ", v[i][j]);
			}
			printf("\n");
		}
	}
};

struct Prim{
	int Vnum;
	vector<edge> Graph[MAX_NODE];

	Prim(int k,vector<edge> t):Vnum(k) {
		for (int i = 0; i < t.size();i ++){
			Graph[t[i].from].push_back(t[i]);
			Graph[t[i].to].push_back(t[i]);
		}
	}

	void work(){
		vector<int> vG[Vnum + 1];
		double dis[Vnum + 1];
		int belong[Vnum + 1];
		bool vis[Vnum + 1];
		memset(vis,0,sizeof(vis));
		int cnt, tot = 0, now = 1;
		double ans = 0;
		for(int i = 2;i <= Vnum;i ++)
			dis[i] = INF;
		for (int i = 0;i < Graph[1].size();i ++){
			int v = Graph[1][i].to;
			double w = Graph[1][i].weight;
			if (dis[v] > w){
				dis[v] = w;
				belong[v] = 1;
			}
		}

		while (++tot < Vnum)
		{
			double minn = INF;
			vis[now] = 1;
			for (int i = 1; i <= Vnum; ++i) {
				if (!vis[i] && minn > dis[i]) {
					minn = dis[i];
					now = i;
				}
			}
			ans += minn;

			vG[now].push_back(belong[now]);
			vG[belong[now]].push_back(now);

			//枚举now的所有连边，更新dis数组
			for (int i = 0; i < Graph[now].size(); i ++) {
				int v = Graph[now][i].to;
				double w = Graph[now][i].weight;
				if (dis[v] > w && !vis[v]){
					dis[v] = w;
					belong[v] = i;
				}
			}
		}

		printf("Prime生成的最小生成树权值和为: %lf\n", ans);
		for (int i = 1; i <= Vnum; i++)
		{
			printf("%d: ", i);
			for (int j = 0; j < vG[i].size(); j++)
				printf("%d ", vG[i][j]);
			printf("\n");
		}

	}
};

void init(int &Vnum,vector<edge> &Graph) {
	ifstream FILE;
	FILE.open("F:\\DataStruteHomeWork\\6\\6.txt", ios::in);
	if(!FILE.good()) {
		printf("文件打开失败，请检查文件是否存在。");
		exit(0);
	}
	FILE >> Vnum;
	for (int i = 1; i <= Vnum; i++) {
		string t;
		FILE >> t;
	}
	while (!FILE.eof()) {
		edge t;
		FILE >> t.from >> t.to >> t.weight;
		Graph.push_back(t);
	}
}


int main()
{
	int Vunm;
	vector<edge> Graph;
	init(Vunm,Graph);
	Kruskal Kwork(Vunm,Graph);
	clock_t start_time = clock();
	Kwork.work();
	clock_t end_time = clock();
	cout << "Kruskal runing time is:" << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	Prim Pwork(Vunm, Graph);
	start_time = clock();
	Pwork.work();
	end_time = clock();
	cout << "Prim runing time is:" << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}