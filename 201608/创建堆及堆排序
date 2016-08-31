//实现将无序的数组构建成堆的结构:(因为堆的结构是近乎二叉树,节点编号是从上到下,从左到右
//可以用数组下标表示)
//想法是建立空数组(不用,完全可以在原数组上操作),每次取出一个数字,放入当前尾部,
//与父节点比较(考虑存在问题)(根本不用考虑父节点问题,因为插入堆之前默认堆是有序的
//siftup本身也考虑到父节点存在问题,直接用siftup)


#include <iostream>
using namespace std;

//预处理准备函数Siftup/Siftdown
template <class T>
int Getlength(T &array){
	return (sizeof(array)/sizeof(array[0]));
}

void Siftup(int *a,int i){
	if (i==1)return ;
	int j=i/2;
	while(a[j-1] < a[i-1]&&i > 1) {
	    //交换
	    int temp=a[j-1];
	    a[j-1]=a[i-1];
	    a[i-1]=temp;
	    i=j;
	    j=i/2;
	}
}

void Siftdown(int *a,int length,int i){
	if (2*i > length)return;
	bool done=false;
	int j=2*i;
	do{
		if (j+1<=length && a[j-1]<a[j])j++;
		if (a[j-1] > a[i-1])
		{
			int temp=a[j-1];
	    	a[j-1]=a[i-1];
	    	a[i-1]=temp;
	    	i=j;
	    	j=2*i;
		}else done=true;
	}while(j <= length && !done);
}
//创建堆
//以交换为基础运算,则时间复杂度为log2+log3+log4+...+logn都是先求下限再相加
//这种方法是默认前面数字是按堆排序的,每次都是单个数字与前面数组比较,这种比较低效,可以改进
void  makeheap(int *a,int length){//a表示数组,length表示数组长度
	for (int i = 2; i <= length; ++i)
	{
		Siftup(a,i);//Siftup是从至少1个数字的堆开始的(不是空堆)
	}
}

void makeheap1(int *a,int length){
	for (int i = length/2; i >= 1; --i)//循环比第一种方法整整减半
	{
		Siftdown(a,length,i);
	}

}
//堆排序
//先将无序的数组进行堆排序,然后将a[0]与a[n-1]交换,交换后重新siftdown,继续交换,知道length为2
void heapsort(int *a,int length){
	makeheap1(a,length);
	for (int i = length; i >= 2; --i)//i的取值范围是length到2
	{
		//先交换,在siftdown
		int temp=a[0];
	    a[0]=a[i-1];
	    a[i-1]=temp;
		Siftdown(a,i-1,1);
	}
}


int main(int argc, char const *argv[])
{
	int a[]={20,17,9,10,11,4,5,3,7,5};//{4,5,3,7,5,20,17,9,10,11};
	heapsort(a,10);
	for (int i = 0; i < 10; ++i)
	{
		cout<<a[i]<<" ";
	}
	system("pause");
	return 0;
}
