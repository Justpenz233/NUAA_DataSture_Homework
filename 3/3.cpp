#include <iostream>
#include <string>
#include <cstring>
using namespace std;

//将字符串s[l....r]转换为int型
int GetSeg(int l,int r,string s){
    int t = 0;
    for (int i = l; i <= r;i ++)
        t = t * 10 + s[i] - '0';
    return t;
}

int deta = -1;
int last = 0;

//进行搜索
//pre为生成数列的上一个数字
//pos为处理到原字符串的第pos位
//Prelen记录上个数字的位数
//s为输入的原字符串
bool dfs(int pre,int pos,int PreLen,string s){
    int a = -1, b = -1;
    if(s[pos] == '0')
        return 0;
    if(pos == s.length()){
        last = pre;
        return 1;
    }

    //长度要么和上一个数字相同，要么比上一个数字多一位
    if(pos + PreLen - 1 < s.length())
        a = GetSeg(pos, pos + PreLen - 1, s);
    if(pos + PreLen < s.length())
        b = GetSeg(pos, pos + PreLen, s);
    
    //没跳过数字
    if(a == pre + 1) {
        if(dfs(a, pos + PreLen, PreLen, s))
            return 1;
    }//和上一个数字位数相同
    if(b == pre + 1){
        if(dfs(b, pos + PreLen + 1, PreLen + 1, s))
            return 1;
    }//比上一个数字位数多一
    
    //跳过数字并记录
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

//打印答案
//答案是[begin,end]，中间只可能跳过数字deta
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

//主过程
//枚举第一个数字的位数并进行dfs搜索
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