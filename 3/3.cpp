#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int GetSeg(int l,int r,string s){
    int t = 0;
    for (int i = l; i <= r;i ++)
        t = t * 10 + s[i] - '0';
    return t;
}

int deta = -1;
int last = 0;
bool dfs(int pre,int pos,int PreLen,string s){
    int a = -1, b = -1;
    if(s[pos] == '0')
        return 0;
    if(pos == s.length()){
        last = pre;
        return 1;
    }
    if(pos + PreLen - 1 < s.length())
        a = GetSeg(pos, pos + PreLen - 1, s);
    if(pos + PreLen < s.length())
        b = GetSeg(pos, pos + PreLen, s);
    
    if(a == pre + 1) {
        if(dfs(a, pos + PreLen, PreLen, s))
            return 1;
    }
    if(b == pre + 1){
        if(dfs(b, pos + PreLen + 1, PreLen + 1, s))
            return 1;
    }
    
    if(a == pre + 2){
        if(deta != -1)
            return 0;
        deta = pre + 1;
        if(dfs(a, pos + PreLen, PreLen, s))
            return 1;
    }
    
    if(b == pre + 2){
        if(deta != -1)
            return 0;
        deta = pre + 1;
        if(dfs(b, pos + PreLen + 1, PreLen + 1, s))
            return 1;
    }
    
    return 0;
}
void printAns(int begin,int last){
    for (int i = begin; i <= last;i ++){
        if(i != deta)
            printf("%d,", i);
    }
    printf("\n");
    if(deta != -1){
        printf("The Jump Number is: %d\n", deta);
    }
}
bool work(string s){
    for (int i = 0; i < s.length();i ++)
        if(s[i] < '0' || s[i] > '9')
            return 0;
    for (int i = 1; i * 2 <= s.length(); i++) {
        deta = -1;
		int begin = GetSeg(0, 0 + i - 1, s);
		if (dfs(begin, i, i, s)) {
            printAns(begin, last);
            return 1;
		}
    }
    return 0;
}
int main()
{
    string s;
    while(cin >> s){
        if(s == "#"){
            printf("Exit\n");
            exit(0);
        }
        if(!work(s))
            printf("Invalid Input,Please try agagin\n");
    }
}