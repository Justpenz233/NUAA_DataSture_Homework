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
	vector<edge> Graph;//存边
	int Vnum;
	int fa[MAX_NODE];//并查集

	Kruskal(int k, vector<edge> t) : Vnum(k), Graph(t) {
		for (int i = 1; i <= Vnum; i++)
		  fa[i] = i;
	};//构造函数

	int find(int x){
		while (x != fa[x])
			x = fa[x] = fa[fa[x]];
		return x;
	}//寻找集合的代表元素

	void work() {
		vector<int> v[Vnum + 1];
		int cnt = 0;
		double ans = 0;
		sort(Graph.begin(), Graph.end());//按边权排序
		for (int i = 0; i < Graph.size();i ++){
			int eu = find(Graph[i].from), ev = find(Graph[i].to);
			if(eu == ev)//如果边的两个点已经在树里面 判断下一条边
				continue;
			ans += Graph[i].weight;
			fa[ev] = eu;

			//建立邻接表
			v[Graph[i].from].push_back(Graph[i].to);
			v[Graph[i].to].push_back(Graph[i].from);

			cnt++;
			if(cnt == Vnum - 1)
				break;
		}

		//打印图
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

	//构造函数
	Prim(int k,vector<edge> t):Vnum(k) {
		for (int i = 0; i < t.size();i ++){
			Graph[t[i].from].push_back(t[i]);
			Graph[t[i].to].push_back(t[i]);
		}
	}

	void work(){
		vector<int> vG[Vnum + 1];
		double dis[Vnum + 1];//dis为距离树的距离
		int belong[Vnum + 1];//belong为距离树哪个点最近
		bool vis[Vnum + 1];
		memset(vis,0,sizeof(vis));
		int cnt, tot = 0, now = 1;
		double ans = 0;
		for(int i = 2;i <= Vnum;i ++)
			dis[i] = INF;
		//初始化
		for (int i = 0;i < Graph[1].size();i ++){
			int v = Graph[1][i].to;
			double w = Graph[1][i].weight;
			if (dis[v] > w){
				dis[v] = w;
				belong[v] = 1;
			}
		}//找一个到点1最近的点

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
			//找到一个到树最近的点now

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

//Graph为图，Vnum为点的数量
//读取文件
void init(int &Vnum,vector<edge> &Graph) {
	ifstream FILE;
	printf("请输入文件路径: ");
	string Fname;
	cin >> Fname;
	FILE.open(Fname, ios::in);
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