#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


typedef struct student
{
	char name[20];
	char number[20];
	int score;
	struct student *next;
	struct student *pre;
	student(char *tname,char *tnumber,int tscore) {
		memcpy(name, tname, sizeof(name));
		memcpy(number, tnumber, sizeof(number));
		score = tscore;
		next = NULL;
		pre = NULL;
	}
	student(char *tname) {
		memcpy(name, tname, sizeof(name));
		next = NULL;
		pre = NULL;
	}
	bool operator ==(const student &b){
		if (memcmp(b.number, number, strlen(number)) != 0) return false;
		if (memcmp(b.name, name, strlen(name)) != 0) return false;
		if (score != b.score) return false;
		return true;
	}
	bool isPass() {
		return score >= 60;
	}
	void show() {
		printf("姓名: %s\t学号: %s\t成绩%3d\n", name, number, score);
	}
}ST;
int menu_select();


int menu_select()
{
	char i;
	do {
		system("cls");
		printf("1.创建纪录（从文件读入）\n");
		printf("2.显示所有记录\n");
		printf("3.插入一条记录\n");
		printf("4.删除一条记录\n");
		printf("5.输入补考成绩\n");
		printf("6.查询\n");
		printf("0.退出\n");
		printf("请输入选择序号(0-6):");
		i = getchar();
	} while (i<'0' || i>'6');
	return (i - '0');
}
bool insert(ST *A, ST *T) {
	if (A->next == NULL) {
		A->next = T;
		T->pre = A;
		return 1;
	}
	for (ST *p = A->next; p; p = p->next) {
		if (*p == *T) {
			return 0;
		}
		if (memcmp(p->name, T->name, sizeof(p->name)) >= 0) {
			p->pre->next = T;
			T->pre = p->pre;
			T->next = p;
			p->pre = T;
			return 1;
		}
		if (!p->next) {
			p->next = T;
			T->pre = p;
			return 1;
		}
	}
}
bool isVaild(ST* T) {
	for (int i = 0; i < strlen(T->number); i++) {
		if (T->number[i] < '0' || T->number[i] > '9')
			return 0;
	}
}
void readFile(ST *A,ST *B) {
	ifstream f;
	string fname;
	cout << "请输入文件名称/绝对路径:";
	//cin >> fname;
	f.open("01.txt");
	if (f.bad()) {
		cout << "未找到文件/文件不存在。\n";
		system("pause");
		return;
	}
	while (!f.eof()) {
		char tname[20], tid[20];
		int tscore;
		f >> tname >> tscore >> tid;
		ST *T = new student(tname, tid, tscore);
		if (T->isPass())
			insert(A, T);
		else
			insert(B, T);
	}
	f.close();
	cout << "从文件导入成功。\n";
}
void showLink(ST *A,ST *B) {
	printf("及格学生信息：\n");
	for (ST *p = A->next; p; p = p->next)
		p->show();
	printf("不及格学生信息：\n");
	for (ST *p = B->next; p; p = p->next)
		p->show();
}
void workInsert(ST* A,ST *B) {
	char tname[20], tid[20];
	int tscore;
	A->next->show();
	cin >> tname >> tscore >> tid;
	ST *T = new student(tname, tid, tscore);
	ST *t;
	if (T->isPass()) t = A;
	else t = B;
	if (!insert(t, T)) {
		for (ST *p = t->next; p; p = p->next) {
			if (*p == *T) {
				cout << "该学生已经存在\n";
				return;
			}
		}
	}
	else printf("插入完成\n");
}
void Serch(ST *A,ST *B) {
	char tname[20];
	printf("请输入要查询的学生姓名: ");
	cin >> tname;
	ST *p = A->next;
	bool flag = 0;
	while (p != NULL && p->next != NULL && memcmp(p->name,tname, sizeof(p->name)) <= 0) {
		if (memcmp(p->name, tname, sizeof(p->name) == 0)) {
			p->show();
			flag = 1;
		}
	}
	p = B->next;
	while (p != NULL && p->next != NULL && memcmp(p->name, tname, sizeof(p->name)) <= 0) {
		if (memcmp(p->name, tname, sizeof(p->name) == 0)) {
			p->show();
			flag = 1;
		}
	}
	if (!flag)
		printf("未找到姓名为: %s的学生\n", tname);
	system("pause");
}
void DeleteNode(ST *T) {
	if(T->pre)
		T->pre->next = T->next;
	if(T->next)
		T->next->pre = T->pre;
	delete(T);
}
void getcin(int &t) {
	cin >> t;
	while (t != 0 && t != 1) {
		cout << "请输入有效数字:0/1\n";
		cin >> t;
	}
}
void DeleteWork(ST* A,ST* B) {
	char tname[20];
	printf("请输入要删除的学生姓名: ");
	cin >> tname;
	int flag = 0;
	for(ST *p = A->next;p;p = p->next){
		if (memcmp(p->name, tname, strlen(tname)) == 0) {
			flag = 1;
			printf("找到学生信息：\n");
			p->show();
			printf("是否要删除？(0/1): ");
			int t;
			getcin(t);
			if (t) {
				p = p->pre;
				DeleteNode(p->next);
			}
		}
	}
	for (ST *p = B->next; p; p = p->next) {
		if (memcmp(p->name, tname, strlen(tname)) == 0) {
			flag = 1;
			printf("找到学生信息：\n");
			p->show();
			printf("是否要删除？(0/1): ");
			int t;
			getcin(t);
			if (t) {
				p = p->pre;
				DeleteNode(p->next);
			}
		}
	}
	if (!flag)
		printf("未找到姓名为: %s 的学生\n", tname);
}

int main()
{
	ST *A, *B;
	A = (ST *)malloc(sizeof(ST));
	B = (ST *)malloc(sizeof(ST));
	A->next = B->next = NULL;
	for (;;)
	{
		switch (menu_select())
		{
		case 1://*******
			printf("调用创建链表函数\n");
			readFile(A, B);
			system("pause");
			break;
		case 2://*******
			printf("调用显示函数\n");
			showLink(A, B);
			system("pause");
			break;
		case 3://*******
			printf("调用插入函数\n");
			workInsert(A, B);
			system("pause");
			break;
		case 4://*******
			printf("调用删除函数 :\n");
			DeleteWork(A, B);
			system("pause");
			break;
		case 5:
			printf("调用输入补考成绩函数:\n");
			system("pause");
			break;
		case 6:
			printf("调用查找函数 :\n");
			Serch(A, B);
			system("pause");
			break;
		case 0:
			printf("再见\n");
			system("pause");
			exit(0);
		}
	}
}