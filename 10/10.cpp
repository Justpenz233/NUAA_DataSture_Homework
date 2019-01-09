#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

bool DisplayArray = 1;

//冒泡排序
struct BubbleSort
{
   int CompareTime = 0;
   int ChangeTime = 0;
   vector<int> arr;

   BubbleSort(vector<int> t):arr(t){
      double totaltime;
      clock_t start, finish;
      if(DisplayArray) show(0);
      start = clock();
      work();
      finish = clock();
      if (DisplayArray) show(1);
      totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
      printf("\n冒泡排序的运行时间为%lf秒\n", totaltime);
      printf("比较次数:%d\t交换次数:%d\n\n", CompareTime, ChangeTime);
   }//构造函数，同时是主过程

   void show(int flag){
      if(flag == 0)
         printf("排序前为: ");
      else
         printf("排序后为: ");
      for (int i = 0; i < arr.size();i ++)
         printf("%d ", arr[i]);
      printf("\n");
   }

   void work(){
      bool isLoop = true;//记录是否发生过交换，没有交换则直接停止过程
      for (int i = arr.size();isLoop && i > 0; i --){
         isLoop = false;
         for (int j = 1; j < i; j ++){
            CompareTime++;
            //冒泡算法主过程，和上一个比较大小
            if (arr[j] < arr[j - 1]) {
               swap(arr[j], arr[j - 1]);
               ChangeTime++;
               isLoop = true;
            }
         }
      }
   }
};

//选择排序
struct SelectSort
{
   int CompareTime = 0;
   int ChangeTime = 0;
   vector<int> arr;

   SelectSort(vector<int> t) : arr(t)
   {
      double totaltime;
      clock_t start, finish;
      if (DisplayArray)
         show(0);
      start = clock();
      work();
      finish = clock();
      if (DisplayArray) show(1);
      totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
      printf("\n选择排序的运行时间为%lf秒\n", totaltime);
      printf("比较次数:%d\t交换次数:%d\n\n", CompareTime, ChangeTime);
   } //构造函数，同时是主过程

   void work(){
      for (int i = 0; i < arr.size(); ++i){
         int minIndex = i;
         for (int j = i + 1; j < arr.size(); ++j){
            CompareTime++;
            if (arr[j] < arr[minIndex])
               minIndex = j;//找一个最小的
         }
         if (minIndex != i){
            ChangeTime++;
            swap(arr[i], arr[minIndex]);//将最小的放到前面
         }
      }
   }

   void show(int flag)
   {
      if (flag == 0)
         printf("排序前为: ");
      else
         printf("排序后为: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }
};

//快速排序
struct QuickSort
{
   int CompareTime = 0;
   int ChangeTime = 0;
   vector<int> arr;

   QuickSort(vector<int> t) : arr(t)
   {
      double totaltime;
      clock_t start, finish;
      if (DisplayArray)
         show(0);
      start = clock();
      work(0,arr.size());
      finish = clock();
      if (DisplayArray)
         show(1);
      totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
      printf("\n快速排序的运行时间为%lf秒\n", totaltime);
      printf("比较次数:%d\t交换次数:%d\n\n", CompareTime, ChangeTime);
   } //构造函数，同时是主过程

   void work(int Left, int Right) {
      if (Left >= Right - 1)
         return;
      int i = Left;
      int j = Right - 1;
      int flag = arr[i];
      while (i < j){
         while (i < j){
            CompareTime++;
            if (arr[j] < flag){
               ChangeTime++;
               arr[i++] = arr[j];
               break;
            }
            --j;
         }

         while (i < j){
            CompareTime++;
            if (arr[i] >= flag){
               ChangeTime++;
               arr[j--] = arr[i];
               break;
            }
            ++i;
         }
      }//将比flag小的放到其左侧，大的放到右侧

      ChangeTime++;
      arr[i] = flag;
      work(Left, i);//递归左侧
      work(j + 1, Right);//递归右侧
   }

   void show(int flag)
   {
      if (flag == 0)
         printf("排序前为: ");
      else
         printf("排序后为: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }
};

//插入排序
struct InsertSort
{
   int CompareTime = 0;
   int ChangeTime = 0;
   vector<int> arr;

   InsertSort(vector<int> t) : arr(t)
   {
      double totaltime;
      clock_t start, finish;
      if (DisplayArray)
         show(0);
      start = clock();
      work();
      finish = clock();
      if (DisplayArray)
         show(1);
      totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
      printf("\n插入排序的运行时间为%lf秒\n", totaltime);
      printf("比较次数:%d\t交换次数:%d\n\n", CompareTime, ChangeTime);
   } //构造函数，同时是主过程

   void work() {
      for (int i = 0; i < arr.size(); i++) {
         CompareTime++;
         //如果不是递增的
         if (arr[i] < arr[i - 1]) {
            int t = arr[i];
            int j = i;
            while (j > 0 && arr[j - 1] > t) {
               CompareTime++;
               arr[j] = arr[j - 1];
               j--;
            }//后挪一位
            ChangeTime++;
            arr[j] = t;
         }
      }
   };
   void show(int flag)
   {
      if (flag == 0)
         printf("排序前为: ");
      else
         printf("排序后为: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }

 
};

//归并排序
struct MergeSort
{
   int CompareTime = 0;
   int ChangeTime = 0;
   vector<int> arr;

   MergeSort(vector<int> t) : arr(t)
   {
      double totaltime;
      clock_t start, finish;
      if (DisplayArray)
         show(0);
      start = clock();
      work();
      finish = clock();
      if (DisplayArray)
         show(1);
      totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
      printf("\n归并排序的运行时间为%lf秒\n", totaltime);
      printf("比较次数:%d\t交换次数:%d\n\n", CompareTime, ChangeTime);
   }

   void show(int flag) {
      if (flag == 0)
         printf("排序前为: ");
      else
         printf("排序后为: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }

   //将数组temp左右合并为一个
   void merge(int tmp[], int left, int mid, int right) {
      int i = left;
      int j = mid + 1;
      int k = left;
      while (i <= mid && j <= right){
         CompareTime++;
         if (arr[i] < arr[j])
            tmp[k++] = arr[i++];
         else
            tmp[k++] = arr[j++];
      }
      while (i <= mid)
         tmp[k++] = arr[i++];
      
      while (j <= right)
         tmp[k++] = arr[j++];
      
      for (i = left; i <= right; i++){
         ChangeTime++;
         arr[i] = tmp[i];
      }
   }

   void CutWork(int tmp[], int left, int right) {
      if (left >= right)
         return;
      int mid = left + (right - left) / 2;
      CutWork(tmp, left, mid);//递归操作
      CutWork(tmp, mid + 1, right);
      merge(tmp, left, mid, right);//合并左右序列
   }

   void work(){
      int len = arr.size();
      int tmp[len];
      CutWork(tmp, 0, len - 1);
   }
};

//希尔排序
struct ShellSort
{
   int CompareTime = 0;
   int ChangeTime = 0;
   vector<int> arr;

   ShellSort(vector<int> t) : arr(t) {
      double totaltime;
      clock_t start, finish;
      if (DisplayArray)
         show(0);
      start = clock();
      work();
      finish = clock();
      if (DisplayArray)
         show(1);
      totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
      printf("\n希尔排序的运行时间为%lf秒\n", totaltime);
      printf("比较次数:%d\t交换次数:%d\n\n", CompareTime, ChangeTime);
   }

   void show(int flag) {
      if (flag == 0)
         printf("排序前为: ");
      else
         printf("排序后为: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }

   void work()
   {
      int len = arr.size();
      for (int gap = len / 2; gap > 0; gap /= 2)
         for (int i = gap; i < len; i++)
            for (int j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap,CompareTime ++){
               ChangeTime++;
               swap(arr[j], arr[j + gap]);   
            }
   }
};

//堆排序
struct HeapSort
{
   int CompareTime = 0;
   int ChangeTime = 0;
   vector<int> arr;

   HeapSort(vector<int> t) : arr(t)
   {
      double totaltime;
      clock_t start, finish;
      if (DisplayArray)
         show(0);
      start = clock();
      work();
      finish = clock();
      if (DisplayArray)
         show(1);
      totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
      printf("\n堆排序的运行时间为%lf秒\n", totaltime);
      printf("比较次数:%d\t交换次数:%d\n\n", CompareTime, ChangeTime);
   }

   void show(int flag)
   {
      if (flag == 0)
         printf("排序前为: ");
      else
         printf("排序后为: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }
   void heap_adjust(int pos, int len)
   {
      int son;
      int temp;
      for (; 2 * pos + 1 < len; pos = son)
      {
         son = 2 * pos + 1; // 子结点的位置 = 2 * 父结点的位置 + 1
         // 得到子结点中键值较大的结点
         CompareTime++;
         if (son < len - 1 && arr[son + 1] > arr[son])
            son++;
         // 如果较大的子结点大于父结点那么把较大的子结点往上移动，替换它的父结点
         CompareTime++;
         if (arr[pos] < arr[son])
         {
            ChangeTime++;
            temp = arr[pos];
            arr[pos] = arr[son];
            arr[son] = temp;
         }
         else
            break;
      }
   }
   //排序主过程
   void work()
   {
      int len = arr.size();
      for (int i = len / 2 - 1; i >= 0; i--)
         heap_adjust(i, len);
      for (int i = len - 1; i > 0; i--) {
         int temp = arr[0];
         arr[0] = arr[i];
         arr[i] = temp;
         ChangeTime++;
         heap_adjust(0, i);
      }
   }
};

//二分插入排序
struct BinaryInsertSort
{
   int CompareTime = 0;
   int ChangeTime = 0;
   vector<int> arr;

   BinaryInsertSort(vector<int> t) : arr(t)
   {
      double totaltime;
      clock_t start, finish;
      if (DisplayArray)
         show(0);
      start = clock();
      work();
      finish = clock();
      if (DisplayArray)
         show(1);
      totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
      printf("\n折半插入排序的运行时间为%lf秒\n", totaltime);
      printf("比较次数:%d\t交换次数:%d\n\n", CompareTime, ChangeTime);
   }

   void show(int flag)
   {
      if (flag == 0)
         printf("排序前为: ");
      else
         printf("排序后为: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }

   void work(){
      int len = arr.size();
      int i,temp,j,left,right;
      for (i = 1; i < len; i++) {
         temp = arr[i];
         left = 0;
         right = i - 1;
         //二分查找插入的位置
         while (left <= right) {
            int mid = (left + right) / 2;
            CompareTime++;
            if (arr[mid] > temp)
               right = mid - 1;
            else
               left = mid + 1;
         }
         //向后挪动一位
         for (j = i - 1; j >= right + 1; j--, ChangeTime++)
            arr[j + 1] = arr[j];
         arr[j + 1] = temp;
         ChangeTime++;
      }
      
   }
};

//链式插入排序
struct LinkInsertSort
{
   int CompareTime = 0;
   int ChangeTime = 0;
   vector<int> arr;
   LinkInsertSort(vector<int> t) : arr(t)
   {
      double totaltime;
      clock_t start, finish;
      if (DisplayArray)
         show(0);
      start = clock();
      work();
      finish = clock();
      if (DisplayArray)
         show(1);
      totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
      printf("\n冒泡排序的运行时间为%lf秒\n", totaltime);
      printf("比较次数:%d\t交换次数:%d\n\n", CompareTime, ChangeTime);
   }

   void show(int flag)
   {
      if (flag == 0)
         printf("排序前为: ");
      else
         printf("排序后为: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }

   typedef struct rec //Record 静态链表的节点类型
   {
      int data;
      int next; //静态链表的链域可以这样写，大家应该见过很多次
   } Rec;
   void work() //表插入
   {
      int len = arr.size();
      Rec *rec = new Rec[len + 1];
      for (int i = 0; i < len; i++) //把数据赋给链表
      {
         rec[i + 1].data = arr[i];
         rec[i + 1].next = 0;
      }
      rec[0].data = 100000000;
      rec[0].next = 1; //头节点和第一个节点构成了循环链表
      int p, q;
      for (int i = 2; i < len + 1; i++) //修改next域，使其按指针指向有序
      {
         q = 0;
         p = rec[q].next;                   //p指向当前待比较的节点，q指向前一个
         while (rec[i].data >= rec[p].data) // >= 保证了排序的稳定性
         {
            CompareTime++;
            q = p;
            p = rec[q].next;
         }
         rec[i].next = p;
         rec[q].next = i;
         ChangeTime++;
      }
      p = rec[0].next;
      int i = 0;
      while (p != 0) //顺着静态链表的指针指向，回写数据到原数组
      {
         ChangeTime++;
         arr[i++] = rec[p].data;
         p = rec[p].next;
      }
      delete[] rec; //释放空间
   }
};

void GetArray(int n,vector<int>&arr){
   for (int i = 1; i <= n;i ++)
      arr.push_back(rand());
}

int main()
{
   while(1){
      int n;
      vector<int> arr;
      printf("请输入数列元素的个数: ");
      cin >> n;
      GetArray(n, arr);
      new BubbleSort(arr);
      new SelectSort(arr);
      new QuickSort(arr);
      new InsertSort(arr);
      new MergeSort(arr);
      new ShellSort(arr);
      new HeapSort(arr);
      new BinaryInsertSort(arr);
      new LinkInsertSort(arr);
      system("pause");
   }
}