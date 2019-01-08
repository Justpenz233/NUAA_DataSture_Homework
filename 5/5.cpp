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
    Tree *left;//�����
    Tree *right;//�Ҷ���
    
    //���캯��
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
//С�ѣ�����ά�����ڵ�

//��ʼ���������ļ����������Ľڵ�
void init(){
    int CharNum[300];
    memset(CharNum, 0, sizeof(CharNum));
    ifstream FILE;
    string s;
    printf("�������ļ�����·��:");
    cin >> s;
    FILE.open(s, ios::in);
    if(!FILE.good()){
        printf("�ļ���ʧ��\n");
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

//ÿ�δӶ���ȡ������Ԫ�أ�����Ԫ��һ����Ȩֵ��С������
//�½���һ���ڵ㣬�ڵ�ȨֵΪ�����ͣ���һ������Ϊ�����һ��Ϊ�Ҷ��ӣ��ٷ������
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

//DFS����ӡ��
//S�����·���ϵ�01��posΪ��ǰ���ڽڵ�ĵ�ַ
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