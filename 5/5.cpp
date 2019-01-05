#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <string>
#include <queue>
using namespace std;

struct node{
    char ch;
    int count;
    node *left;
    node *right;
    node(char t){
        ch = t;
        count = 0;
    }
    node(int t){
        count = t;
        ch = '\0';
    }
    bool operator < (const node &t) const {
        return count < t.count;
    }
};

struct Tree{
    node me;
    node lch;
    node rch;
    Tree(node me);
    Tree(node l,node r){
        lch = l;
        rch = r;
        me.ch = '/0';
        me.count = l.count + r.count;
    }
    bool operator < (const Tree &t) const{
        return me < t.me;
    }
}

priority_queue <Tree> pq;


void init(){
    int CharNum[300];
    memset(CharNum, 0, sizeof(CharNum));
    ifstream FILE;
    string s;
    printf("请输入文件绝对路径:");
    cin >> s;
    FILE.open("F:\\DataStruteHomeWork\\5\\test.txt", ios::in);
    while(!FILE.eof()){
        FILE >> s;
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        for (int i = 0; i < s.length();i ++)
            CharNum[s[i]]++;
    }
    for (int i = 'a'; i <= 'z';i ++){
        if(CharNum[i] != 0)
            pq.push(*(new Tree(*(new node(i)))));
    }
}

Tree work(){
    while(!pq.empty()){
        Tree a = pq.top();
        pq.pop();
        if(pq.empty())
            return a;
        Tree b = pq.top();
        pq.pop();
        pq.push(Tree(a, b));
    }
}

void dfs(Tree pos,string s){
    if(pos.ch != '\0'){
        printf("%c : %s\n", pos.ch, s.c_str());
        return;
    }
    dfs(pos.left, s + '0');
    dfs(pos.right, s + '1');
}

int main()
{
    init();
    string ans = "";
    dfs(work(),ans);
}