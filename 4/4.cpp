#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#define INF 1000000000
using namespace std;
vector<int> fm[4];
double Center[4][5];//��������
double NodeSet[160][5];//�㼯
int BelongTo[160];//��鵽�ڼ�����

//����(x,y)��ŷʽ���룬��x����͵�y����
double GetInstance(int x,int y){
    double Sum = 0;
    for (int i = 1; i <= 4;i ++)
        Sum += pow(NodeSet[x][i] - Center[y][i], 2);
    return Sum;
}

//�㵽�������ĵ�ŷʽ���룬Ѱ��һ����С�Ĳ���������һ��
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

//Ѱ��ÿ����Ĺ�����
void Divide(){
    for (int i = 1; i <= 150;i ++){
        double Result[4];
        for (int j = 1; j <= 3;j ++)
            Result[j] = GetInstance(i, j);
        BelongTo[i] = GetBelongTo(Result);
        fm[BelongTo[i]].push_back(i);
    }
}

//���ļ�
void init(){
    string s;
    ifstream FILE;
    printf("�������ļ�·��: ");
    cin >> s;
    FILE.open(s, ios::in);
    if(!FILE.good()){
        cout << "�ļ���ʧ��";
        exit(0);
    }
    for (int i = 1; i <= 150;i ++)
        for (int j = 1; j <= 4;j ++)
                FILE >> NodeSet[i][j];
    //��ǰ��������Ϊ��������
    for (int i = 1; i <= 3;i ++)
        for (int j = 1; j <= 4;j ++)
            Center[i][j] = NodeSet[i][j];
    FILE.close();
}



int work(){
    int count = 0;//��������
    bool flag = 0;
    do{
        flag = 0;//��¼���������Ƿ��޸Ĺ�
        Divide();//����
        for (int i = 1; i <= 3;i ++){
            for (int j = 1; j <= 4;j ++){
                double t = 0;

                //����ÿ�������ƽ������
                for (int k = 0; k < fm[i].size();k ++)
                    t += NodeSet[fm[i][k]][j];
                t /= (double) fm[i].size();
                
                if(t != Center[i][j])//if �������ı��޸Ĺ�
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

//��ӡ�����������Ϊ��������
void showAns(int count){
    printf("������%d��\n", count);
    for (int i = 1; i <= 3;i ++){
        printf("��%d��: \n", i);
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