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
		printf("����: %s\tѧ��: %s\t�ɼ�%3d\n", name, number, score);
	}
}ST;
int menu_select();


int menu_select()
{
	char i;
	do {
		system("cls");
		printf("1.������¼�����ļ����룩\n");
		printf("2.��ʾ���м�¼\n");
		printf("3.����һ����¼\n");
		printf("4.ɾ��һ����¼\n");
		printf("5.���벹���ɼ�\n");
		printf("6.��ѯ\n");
		printf("0.�˳�\n");
		printf("������ѡ�����(0-6):");
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
	cout << "�������ļ�����/����·��:";
	//cin >> fname;
	f.open("01.txt");
	if (f.bad()) {
		cout << "δ�ҵ��ļ�/�ļ������ڡ�\n";
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
	cout << "���ļ�����ɹ���\n";
}
void showLink(ST *A,ST *B) {
	printf("����ѧ����Ϣ��\n");
	for (ST *p = A->next; p; p = p->next)
		p->show();
	printf("������ѧ����Ϣ��\n");
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
				cout << "��ѧ���Ѿ�����\n";
				return;
			}
		}
	}
	else printf("�������\n");
}
void Serch(ST *A,ST *B) {
	char tname[20];
	printf("������Ҫ��ѯ��ѧ������: ");
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
		printf("δ�ҵ�����Ϊ: %s��ѧ��\n", tname);
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
		cout << "��������Ч����:0/1\n";
		cin >> t;
	}
}
void DeleteWork(ST* A,ST* B) {
	char tname[20];
	printf("������Ҫɾ����ѧ������: ");
	cin >> tname;
	int flag = 0;
	for(ST *p = A->next;p;p = p->next){
		if (memcmp(p->name, tname, strlen(tname)) == 0) {
			flag = 1;
			printf("�ҵ�ѧ����Ϣ��\n");
			p->show();
			printf("�Ƿ�Ҫɾ����(0/1): ");
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
			printf("�ҵ�ѧ����Ϣ��\n");
			p->show();
			printf("�Ƿ�Ҫɾ����(0/1): ");
			int t;
			getcin(t);
			if (t) {
				p = p->pre;
				DeleteNode(p->next);
			}
		}
	}
	if (!flag)
		printf("δ�ҵ�����Ϊ: %s ��ѧ��\n", tname);
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
			printf("���ô���������\n");
			readFile(A, B);
			system("pause");
			break;
		case 2://*******
			printf("������ʾ����\n");
			showLink(A, B);
			system("pause");
			break;
		case 3://*******
			printf("���ò��뺯��\n");
			workInsert(A, B);
			system("pause");
			break;
		case 4://*******
			printf("����ɾ������ :\n");
			DeleteWork(A, B);
			system("pause");
			break;
		case 5:
			printf("�������벹���ɼ�����:\n");
			system("pause");
			break;
		case 6:
			printf("���ò��Һ��� :\n");
			Serch(A, B);
			system("pause");
			break;
		case 0:
			printf("�ټ�\n");
			system("pause");
			exit(0);
		}
	}
}