#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#define INF 1000000000
using namespace std;
vector<int> fm[4];
double Center[4][5]; // Center
double NodeSet[160][5];
int BelongTo[160];

double GetInstance(int x,int y){
    double Sum = 0;
    for (int i = 1; i <= 4;i ++)
        Sum += pow(NodeSet[x][i] - Center[y][i], 2);
    return Sum;
}

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

void Divide(){
    for (int i = 1; i <= 150;i ++){
        double Result[4];
        for (int j = 1; j <= 3;j ++)
            Result[j] = GetInstance(i, j);
        BelongTo[i] = GetBelongTo(Result);
        fm[BelongTo[i]].push_back(i);
    }
}
void init(){
    ifstream FILE;
    FILE.open("C:\\Users\\Justpenz233\\Desktop\\DataStrure\\4\\Iris.txt");
    if(!FILE.good()){
        cout << "文件打开失败";
        exit(0);
    }
    for (int i = 1; i <= 150;i ++)
        for (int j = 1; j <= 4;j ++)
                FILE >> NodeSet[i][j];
    for (int i = 1; i <= 3;i ++)
        for (int j = 1; j <= 4;j ++)
            Center[i][j] = NodeSet[i][j];
    FILE.close();
}



int work(){
    int count = 0;
    bool flag = 0;
    do{
        flag = 0;
        Divide();//分类
        for (int i = 1; i <= 3;i ++){
            for (int j = 1; j <= 4;j ++){
                double t = 0;
                for (int k = 0; k < fm[i].size();k ++)
                    t += NodeSet[fm[i][k]][j];
                t /= (double) fm[i].size();
                if(t != Center[i][j])
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