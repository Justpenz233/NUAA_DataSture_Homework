#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

bool DisplayArray = 1;

//ð������
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
      printf("\nð�����������ʱ��Ϊ%lf��\n", totaltime);
      printf("�Ƚϴ���:%d\t��������:%d\n\n", CompareTime, ChangeTime);
   }//���캯����ͬʱ��������

   void show(int flag){
      if(flag == 0)
         printf("����ǰΪ: ");
      else
         printf("�����Ϊ: ");
      for (int i = 0; i < arr.size();i ++)
         printf("%d ", arr[i]);
      printf("\n");
   }

   void work(){
      bool isLoop = true;//��¼�Ƿ�����������û�н�����ֱ��ֹͣ����
      for (int i = arr.size();isLoop && i > 0; i --){
         isLoop = false;
         for (int j = 1; j < i; j ++){
            CompareTime++;
            //ð���㷨�����̣�����һ���Ƚϴ�С
            if (arr[j] < arr[j - 1]) {
               swap(arr[j], arr[j - 1]);
               ChangeTime++;
               isLoop = true;
            }
         }
      }
   }
};

//ѡ������
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
      printf("\nѡ�����������ʱ��Ϊ%lf��\n", totaltime);
      printf("�Ƚϴ���:%d\t��������:%d\n\n", CompareTime, ChangeTime);
   } //���캯����ͬʱ��������

   void work(){
      for (int i = 0; i < arr.size(); ++i){
         int minIndex = i;
         for (int j = i + 1; j < arr.size(); ++j){
            CompareTime++;
            if (arr[j] < arr[minIndex])
               minIndex = j;//��һ����С��
         }
         if (minIndex != i){
            ChangeTime++;
            swap(arr[i], arr[minIndex]);//����С�ķŵ�ǰ��
         }
      }
   }

   void show(int flag)
   {
      if (flag == 0)
         printf("����ǰΪ: ");
      else
         printf("�����Ϊ: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }
};

//��������
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
      printf("\n�������������ʱ��Ϊ%lf��\n", totaltime);
      printf("�Ƚϴ���:%d\t��������:%d\n\n", CompareTime, ChangeTime);
   } //���캯����ͬʱ��������

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
      }//����flagС�ķŵ�����࣬��ķŵ��Ҳ�

      ChangeTime++;
      arr[i] = flag;
      work(Left, i);//�ݹ����
      work(j + 1, Right);//�ݹ��Ҳ�
   }

   void show(int flag)
   {
      if (flag == 0)
         printf("����ǰΪ: ");
      else
         printf("�����Ϊ: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }
};

//��������
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
      printf("\n�������������ʱ��Ϊ%lf��\n", totaltime);
      printf("�Ƚϴ���:%d\t��������:%d\n\n", CompareTime, ChangeTime);
   } //���캯����ͬʱ��������

   void work() {
      for (int i = 0; i < arr.size(); i++) {
         CompareTime++;
         //������ǵ�����
         if (arr[i] < arr[i - 1]) {
            int t = arr[i];
            int j = i;
            while (j > 0 && arr[j - 1] > t) {
               CompareTime++;
               arr[j] = arr[j - 1];
               j--;
            }//��Ųһλ
            ChangeTime++;
            arr[j] = t;
         }
      }
   };
   void show(int flag)
   {
      if (flag == 0)
         printf("����ǰΪ: ");
      else
         printf("�����Ϊ: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }

 
};

//�鲢����
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
      printf("\n�鲢���������ʱ��Ϊ%lf��\n", totaltime);
      printf("�Ƚϴ���:%d\t��������:%d\n\n", CompareTime, ChangeTime);
   }

   void show(int flag) {
      if (flag == 0)
         printf("����ǰΪ: ");
      else
         printf("�����Ϊ: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }

   //������temp���Һϲ�Ϊһ��
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
      CutWork(tmp, left, mid);//�ݹ����
      CutWork(tmp, mid + 1, right);
      merge(tmp, left, mid, right);//�ϲ���������
   }

   void work(){
      int len = arr.size();
      int tmp[len];
      CutWork(tmp, 0, len - 1);
   }
};

//ϣ������
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
      printf("\nϣ�����������ʱ��Ϊ%lf��\n", totaltime);
      printf("�Ƚϴ���:%d\t��������:%d\n\n", CompareTime, ChangeTime);
   }

   void show(int flag) {
      if (flag == 0)
         printf("����ǰΪ: ");
      else
         printf("�����Ϊ: ");
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

//������
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
      printf("\n�����������ʱ��Ϊ%lf��\n", totaltime);
      printf("�Ƚϴ���:%d\t��������:%d\n\n", CompareTime, ChangeTime);
   }

   void show(int flag)
   {
      if (flag == 0)
         printf("����ǰΪ: ");
      else
         printf("�����Ϊ: ");
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
         son = 2 * pos + 1; // �ӽ���λ�� = 2 * ������λ�� + 1
         // �õ��ӽ���м�ֵ�ϴ�Ľ��
         CompareTime++;
         if (son < len - 1 && arr[son + 1] > arr[son])
            son++;
         // ����ϴ���ӽ����ڸ������ô�ѽϴ���ӽ�������ƶ����滻���ĸ����
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
   //����������
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

//���ֲ�������
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
      printf("\n�۰�������������ʱ��Ϊ%lf��\n", totaltime);
      printf("�Ƚϴ���:%d\t��������:%d\n\n", CompareTime, ChangeTime);
   }

   void show(int flag)
   {
      if (flag == 0)
         printf("����ǰΪ: ");
      else
         printf("�����Ϊ: ");
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
         //���ֲ��Ҳ����λ��
         while (left <= right) {
            int mid = (left + right) / 2;
            CompareTime++;
            if (arr[mid] > temp)
               right = mid - 1;
            else
               left = mid + 1;
         }
         //���Ų��һλ
         for (j = i - 1; j >= right + 1; j--, ChangeTime++)
            arr[j + 1] = arr[j];
         arr[j + 1] = temp;
         ChangeTime++;
      }
      
   }
};

//��ʽ��������
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
      printf("\nð�����������ʱ��Ϊ%lf��\n", totaltime);
      printf("�Ƚϴ���:%d\t��������:%d\n\n", CompareTime, ChangeTime);
   }

   void show(int flag)
   {
      if (flag == 0)
         printf("����ǰΪ: ");
      else
         printf("�����Ϊ: ");
      for (int i = 0; i < arr.size(); i++)
         printf("%d ", arr[i]);
      printf("\n");
   }

   typedef struct rec //Record ��̬����Ľڵ�����
   {
      int data;
      int next; //��̬����������������д�����Ӧ�ü����ܶ��
   } Rec;
   void work() //�����
   {
      int len = arr.size();
      Rec *rec = new Rec[len + 1];
      for (int i = 0; i < len; i++) //�����ݸ�������
      {
         rec[i + 1].data = arr[i];
         rec[i + 1].next = 0;
      }
      rec[0].data = 100000000;
      rec[0].next = 1; //ͷ�ڵ�͵�һ���ڵ㹹����ѭ������
      int p, q;
      for (int i = 2; i < len + 1; i++) //�޸�next��ʹ�䰴ָ��ָ������
      {
         q = 0;
         p = rec[q].next;                   //pָ��ǰ���ȽϵĽڵ㣬qָ��ǰһ��
         while (rec[i].data >= rec[p].data) // >= ��֤��������ȶ���
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
      while (p != 0) //˳�ž�̬�����ָ��ָ�򣬻�д���ݵ�ԭ����
      {
         ChangeTime++;
         arr[i++] = rec[p].data;
         p = rec[p].next;
      }
      delete[] rec; //�ͷſռ�
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
      printf("����������Ԫ�صĸ���: ");
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