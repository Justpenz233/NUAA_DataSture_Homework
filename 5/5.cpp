#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <string>
#include <queue>
using namespace std;

struct Tree{
    char ch;
    int count;
    Tree *left;//左儿子
    Tree *right;//右儿子
    
    //构造函数
    Tree(char t){
        ch = t;
        count = 0;
        left = NULL;
        right = NULL;
    }
    Tree(int t){
        count = t;
        ch = '\0';
        left = NULL;
        right = NULL;
    }
    Tree(char tc, int ti) : ch(tc), count(ti), left(NULL), right(NULL){};
    Tree(){
        ch = '\0'; count = 0;
        left = NULL; right = NULL;
    };
    Tree(Tree *a,Tree *b):left(a),right(b){
        ch = '\0';
        count = a->count + b->count;
    }
};

struct comp{
    bool operator ()(const Tree *a,const Tree *b) const {
        return a->count > b->count;
    }
};

priority_queue <Tree*,vector<Tree*>,comp> pq;
//小堆，用来维护树节点

//初始化，读入文件及创建树的节点
void init(){
    int CharNum[300];
    memset(CharNum, 0, sizeof(CharNum));
    ifstream FILE;
    string s;
    printf("请输入文件绝对路径:");
    cin >> s;
    FILE.open(s, ios::in);
    if(!FILE.good()){
        printf("文件打开失败\n");
        exit(0);
    }
    while(!FILE.eof()){
        FILE >> s;
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        for (int i = 0; i < s.length();i ++)
            CharNum[s[i]]++;
    }
    for (char i = 'a'; i <= 'z';i ++){
        if(CharNum[i] != 0)
            pq.push(new Tree(i,CharNum[i]));
    }
}

//每次从堆中取出两个元素，两个元素一定是权值最小的两个
//新建立一个节点，节点权值为两个和，把一个设置为左儿子一个为右儿子，再放入堆中
Tree* work(){
    while(!pq.empty()){
        Tree* a = pq.top();
        pq.pop();
        if(pq.empty())
            return a;
        Tree* b = pq.top();
        pq.pop();
        pq.push(new Tree(a, b));
    }
}

//DFS树打印答案
//S存的是路径上的01，pos为当前所在节点的地址
void dfs(Tree* pos,string s){
    if(pos->ch != '\0'){
        printf("%c\tCount: %d\tHUFFMAN_CODE: %s\n", pos->ch,pos->count,s.c_str());
        return;
    }
    dfs(pos->left, s + '0');
    dfs(pos->right, s + '1');
}

int main()
{
    init();
    string ans = "";
    dfs(work(),ans);
}