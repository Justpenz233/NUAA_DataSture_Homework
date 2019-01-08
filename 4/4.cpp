#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#define INF 1000000000
using namespace std;
vector<int> fm[4];
double Center[4][5];//数据中心
double NodeSet[160][5];//点集
int BelongTo[160];//点归到第几个类

//计算(x,y)的欧式距离，第x个点和第y个点
double GetInstance(int x,int y){
    double Sum = 0;
    for (int i = 1; i <= 4;i ++)
        Sum += pow(NodeSet[x][i] - Center[y][i], 2);
    return Sum;
}

//点到三个中心的欧式距离，寻找一个最小的并返回是哪一个
int GetBelongTo(double Result[4]){
    double temp = INF;
    double No;
    for (int i = 1; i <= 3;i ++){
        if(temp > Result[i]){
            temp = Result[i];
            No = i;
        }
    }
    return No;
}

//寻找每个点的归属类
void Divide(){
    for (int i = 1; i <= 150;i ++){
        double Result[4];
        for (int j = 1; j <= 3;j ++)
            Result[j] = GetInstance(i, j);
        BelongTo[i] = GetBelongTo(Result);
        fm[BelongTo[i]].push_back(i);
    }
}

//打开文件
void init(){
    string s;
    ifstream FILE;
    printf("请输入文件路径: ");
    cin >> s;
    FILE.open(s, ios::in);
    if(!FILE.good()){
        cout << "文件打开失败";
        exit(0);
    }
    for (int i = 1; i <= 150;i ++)
        for (int j = 1; j <= 4;j ++)
                FILE >> NodeSet[i][j];
    //将前三个点作为聚类中心
    for (int i = 1; i <= 3;i ++)
        for (int j = 1; j <= 4;j ++)
            Center[i][j] = NodeSet[i][j];
    FILE.close();
}



int work(){
    int count = 0;//迭代次数
    bool flag = 0;
    do{
        flag = 0;//记录聚类中心是否被修改过
        Divide();//分类
        for (int i = 1; i <= 3;i ++){
            for (int j = 1; j <= 4;j ++){
                double t = 0;

                //计算每个聚类的平均向量
                for (int k = 0; k < fm[i].size();k ++)
                    t += NodeSet[fm[i][k]][j];
                t /= (double) fm[i].size();
                
                if(t != Center[i][j])//if 聚类中心被修改过
                    flag = 1;
                Center[i][j] = t;
            }
        }
        if(!flag)
            return ++count;
        for (int i = 1; i <= 3;i ++)
            fm[i].clear();
        count++;
    } while (flag);
    return count;
}

//打印答案情况，参数为迭代次数
void showAns(int count){
    printf("共迭代%d次\n", count);
    for (int i = 1; i <= 3;i ++){
        printf("第%d类: \n", i);
        for (int j = 0; j < fm[i].size();j ++)
            printf("%d ", fm[i][j]);
        printf("\n");
    }
}
int main()
{
    init();
    showAns(work());
    system("pause");
}