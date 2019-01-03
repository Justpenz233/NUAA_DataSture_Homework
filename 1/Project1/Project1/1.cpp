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
	}
	student(char *tname) {
		memcpy(name, tname, sizeof(name));
	}
	bool operator ==(const student &b) {
		if (memcmp(b.number, number, sizeof(number)) != 0) return 0;
		if (memcmp(b.name, name, sizeof(name)) != 0) return 0;
		if (score != b.score) return 0;
		return 1;
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
	ST *p = A->next;
	while (p!= NULL && p->next != NULL && memcmp(p->name, T->name,sizeof(p->name)) <= 0) {
		p = p->next;
	}
	T->next = p->next;
	if (p->next != NULL) p->next->pre = T;
	if (p->next != NULL) p->next = T;
	T->pre = p;
	return 1;
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
	cin >> fname;
	f.open(fname);
	if (f.bad()) {
		cout << "未找到文件/文件不存在。\n";
		system("pause");
		return;
	}
	while (!f.eof()) {
		char tname[20], tid[20];
		int tscore;
		f >> tname >> tid >> tscore;
		ST *T = new student(tname, tid, tscore);
		if (T->isPass())
			insert(A, T);
		else
			insert(B, T);
	}
	f.close();
	cout << "从文件导入成功。\n";
	system("pause");
}

void showLink(ST *A,ST *B) {
	printf("及格学生信息：");
	ST *p = A->next;
	while (p->next) {
		for (int i = 1; i <= 10 && p->next != NULL; i++)
			p->show();
	}
	printf("不及格学生信息：");
	ST *p = B->next;
	while (p->next) {
		for (int i = 1; i <= 10 && p->next != NULL; i++)
			p->show();
	}

}

void workInsert(ST* A,ST *B) {
	char tname[20], tid[20];
	int tscore;
	cin >> tname >> tid >> tscore;
	ST *T = new student(tname, tid, tscore);
	ST *p, *t;
	if (T->isPass())
		t = A->next;
	else
		t = B->next;
	p = t;
	bool flag = 0;
	while (p != NULL && p->next != NULL && memcmp(p->name, tname, sizeof(p->name)) <= 0) {
		if (*p == *T) {
			printf("学生信息已经存在:\n");
			p->show();
			return;
		}
		p = p->next;
	}
	insert(t, T);
	printf("插入完成\n");
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
	T->pre->next = T->next;
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
	ST *p = A->next;
	bool flag = 0;
	int t;
	while (p != NULL && p->next != NULL && memcmp(p->name, tname, sizeof(p->name)) <= 0) {
		if (memcmp(p->name, tname, sizeof(p->name) == 0)) {
			flag = 1;
			printf("找到学生信息：\n");
			p->show();
			printf("是否要删除？(0/1): ");
			getcin(t);
			if (t) {
				ST *temp = p;
				p = p->next;
				DeleteNode(temp);
			}
			else p = p->next;
		}
	}
	p = B->next;
	while (p != NULL && p->next != NULL && memcmp(p->name, tname, sizeof(p->name)) <= 0) {
		if (memcmp(p->name, tname, sizeof(p->name) == 0)) {
			flag = 1;
			printf("找到学生信息：\n");
			p->show();
			printf("是否要删除？(0/1): ");
			getcin(t);
			if (t) {
				ST *temp = p;
				p = p->next;
				DeleteNode(temp);
			}
			else p = p->next;
		}
	}
	if (!flag)
		printf("未找到姓名为: %s的学生\n", tname);
	system("pause");
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
		case 6://********
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