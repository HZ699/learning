选择排序
#include <iostream>
#include <vector>
using namespace std;

//目标是将一组无序的数组按有序输出(有多种方法,如选择排序,插入排序等等,另外需要讨论它们的效率,适用场合,空间时间复杂度等等)
//选择排序
//找出当前数组的最小值,用两个指针,一个指向待放当前放置最小值的坐标(特性是自增一),另一个指向实际当前最小值得坐标(特性是需要对比,指向较小的)
//然后相互交换,此为一轮
//如此持续下去,到最后一个为止.
//预处理
template<class T>
int GetArrayLength(T &Array){
	return sizeof(Array)/sizeof(Array[0]);
}
void  SelectionSort(int a[],int length){//输入无序数组,及它的长度(因为int数组没有直接调用出长度)
	for (int i = 0; i < length-1; ++i)//i表示要插入的次小值坐标,从0到length-2,表示有length-1次循环,不用第length次比较,因为只剩一个数不用比较
	{
		int k=i;//k表示遍历数组后找到的最小值坐标,从i开始
		for (int j = i; j < length; ++j)//j表示从第i开始遍历数组(i之前都排好序,遍历全部)
		{
			if (a[k]>a[j])k=j;//找到更小值,坐标为j,不用急着交换,先将k指向j,知道该层循环结束,可知此时的k指向就是当前数组的最小值.		
		}
		//交换(要考虑到两种情况,一是k不变,不交换,二是k变,则交换)
		if(k!=i){
			int temp=a[k];
			a[k]=a[i];
			a[i]=temp;
		}
	}
}

int main(int argc, char const *argv[])
{
	
	int a[]={1,4,3,5,7,5,3,45,67,34,18};
	int length=GetArrayLength(a);
	SelectionSort(a,length);
	for (int i = 0; i < length; ++i)
	{
		cout<<a[i]<<endl;
	}

	cout<<length<<endl;

	system("pause");
	return 0;
}
