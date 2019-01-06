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
    Tree *left;
    Tree *right;
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
    Tree(){
        ch = '\0'; count = 0;
        left = NULL; right = NULL;
    };
    Tree(Tree *a,Tree *b):left(a),right(b){
        ch = '\0';
        count = a->count + b->count;
    }
};

bool operator < (Tree* a,Tree *b){
    return a->count < b->count;
}

priority_queue <Tree*> pq;


void init(){
    int CharNum[300];
    memset(CharNum, 0, sizeof(CharNum));
    ifstream FILE;
    string s;
    printf("请输入文件绝对路径:");
    cin >> s;
    FILE.open("test.txt", ios::in);
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
    for (int i = 'a'; i <= 'z';i ++){
        if(CharNum[i] != 0)
            pq.push(new Tree(i));
    }
}

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

void dfs(Tree* pos,string s){
    if(pos->ch != '\0'){
        printf("%c : %s\n", pos->ch, s.c_str());
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