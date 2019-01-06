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
	struct student *next;//双向链表 下一个
	struct student *pre;//双向链表 前一个
	
	//构造函数
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
	}//重载运算符==，当两个学生信息完全相同才算相同
	bool isPass() {
		return score >= 60;
	}//判断学生是否及格
	void show() {
		printf("姓名: %s\t学号: %s\t成绩%3d\n", name, number, score);
	}//打印学生信息

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

//插入 将节点T插入到链表A中，A为链表头节点
bool insert(ST *A, ST *T) 
{
	if (A->next == NULL) {
		A->next = T;
		T->pre = A;
		return 1;
	}
	//如果链表为空直接插入并返回

	for (ST *p = A->next; p; p = p->next) {
		if (*p == *T) {
			return 0;
			//要插入的学生T已经存在，则插入失败返回0
		}
		if (memcmp(p->name, T->name, sizeof(p->name)) >= 0) {
			p->pre->next = T;
			T->pre = p->pre;
			T->next = p;
			p->pre = T;
			return 1;
		}
		//按照名字升序存储，如果找到一个比T小的，插入到他的前面

		if (!p->next) {
			p->next = T;
			T->pre = p;
			return 1;
		}
		//如果到了链表尾部 直接插入即可

	}
}

//从文件中读取学生信息， A为及格链表头，B为不及格链表头
void readFile(ST *A,ST *B){
	ifstream f;
	string fname;
	cout << "请输入文件名称/绝对路径:";
	//cin >> fname;
	f.open("01.txt");
	if (f.bad()) {
		cout << "未找到文件/文件不存在。\n";
		system("pause");
		return;
	}//读取文件失败的处理

	while (!f.eof()) {
		char tname[20], tid[20];
		int tscore;
		f >> tname >> tscore >> tid;
		ST *T = new student(tname, tid, tscore);
		if (T->isPass())
			insert(A, T);
		else
			insert(B, T);
	}//读取一个学生并选择性插入到A或B中
	f.close();
	cout << "从文件导入成功。\n";
}

//展示两个链表的学生信息，A为及格学生，B为不及格学生
void showLink(ST *A,ST *B) {
	printf("及格学生信息：\n");
	for (ST *p = A->next; p; p = p->next)
		p->show();
	printf("不及格学生信息：\n");
	for (ST *p = B->next; p; p = p->next)
		p->show();
}

//用户插入一个学生，A为及格学，B为不及格学生
void workInsert(ST* A,ST *B) {
	char tname[20], tid[20];
	int tscore;
	cout << "请输入学生姓名: ";
	cin >> tname;
	cout << "请输入学生学号: ";
	cin >> tid;
	cout << "请输入学生成绩: ";
	cin >> tscore;
	ST *T = new student(tname, tid, tscore);
	ST *t;
	//输入并创建要插入的学生

	if (T->isPass()) t = A;
	else t = B;
	if (!insert(t, T)) {
		for (ST *p = t->next; p; p = p->next) {
			if (*p == *T) {
				cout << "该学生已经存在\n";
				return;
			}
		}
	}//如果学生存在则停止插入并提示
	else printf("插入完成\n");
}

//根据学生名字进行查询操作，A为及格学生，B为不及格学生
bool Serch(ST *A,ST *B) {
	char tname[20];
	printf("请输入要查询的学生姓名: ");
	cin >> tname;
	bool flag = 0;
	int count = 0;

	for (ST *p = A->next; p; p = p->next) {
		if (memcmp(p->name, tname, strlen(p->name)) == 0) {
			p->show();
			flag = 1;
			if((++count) % 10 == 0)
				system("pause");
		}
	}//遍历链表A，找到一个立即显示

	
	for (ST *p = B->next; p; p = p->next) {
		if (memcmp(p->name, tname, strlen(p->name)) == 0) {
			p->show();
			flag = 1;
			if ((++count) % 10 == 0)
				system("pause");
		}
	} //遍历链表B，找到一个立即显示

	if (flag)
		return 1;
	if (!flag)
		printf("未找到姓名为: %s的学生\n", tname);
	return 0;
}
void DeleteNode(ST *T) {
	if(T->pre)
		T->pre->next = T->next;
	if(T->next)
		T->next->pre = T->pre;
	delete(T);
}

//输入有效性检验函数，t为输入的数字
void getcin(int &t) {
	cin >> t;
	while (t != 0 && t != 1) {
		cout << "请输入有效数字:0/1\n";
		cin >> t;
	}
}

//输入学生姓名并删除
//A为及格学生链表表头 B为不及格学生链表表头
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
	}//遍历A链表 查找学生

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
	}//遍历B链表 查找学生

	if (!flag)
		printf("未找到姓名为: %s 的学生\n", tname);
}

//补考信息录入
//A为及格学生链表表头 B为不及格学生链表表头
void BuKao(ST* A,ST *B) {
	char tname[20], tid[20];
	int tscore;
	bool flag = 0;
	cout << "请输入学生姓名: ";
	cin >> tname;
	cout << "请输入学生学号: ";
	cin >> tid;
	cout << "请输入学生成绩: ";
	cin >> tscore;
	ST *T = new student(tname, tid, tscore);
	for (ST *i = B->next; i; i = i->next) {
		if (memcmp(tname, i->name, strlen(tname)) == 0 &&
			memcmp(tid, i->number, strlen(tid)) == 0) {
			flag = 1;
			DeleteNode(i);//如果找到学生 则将其在链表中删除
			if(T->isPass()) insert(A, T);
			else insert(B, T);
			//如果学生及格了 则插入到A中 否则插入到B中
			printf("插入完成\n");
			return;
		}
	}//在链表B中查找学生是否存在
	printf("不存在名字为:%s 学号为:%s 的需要补考学生。\n", tname, tid);
	return;
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
		case 1:
			printf("调用创建链表函数\n");
			readFile(A, B);
			system("pause");
			break;
		case 2:
			printf("调用显示函数\n");
			showLink(A, B);
			system("pause");
			break;
		case 3:
			printf("调用插入函数\n");
			workInsert(A, B);
			system("pause");
			break;
		case 4:
			printf("调用删除函数 :\n");
			DeleteWork(A, B);
			system("pause");
			break;
		case 5:
			printf("调用输入补考成绩函数:\n");
			BuKao(A,B);
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