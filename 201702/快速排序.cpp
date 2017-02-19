/**
 * -*- coding : GBK -*-
 * @Author : huangshengjiang
 * @Email : 1005542693@qq.com
 * @Date : 2016-12-26 11:18
 * @Last Modified Date : 2017-02-19 23:25
 * @FileName : 快速排序.cpp
 */

/*快速排序
	基本概念 : 以数组的某个值(一般为首尾,此处为首)为标准值,i,j从左到右遍历(i指向最近的大于A[0]的值,
			   j指向出现小于A[0]的值,如果i和j不相同,则交换),j遍历结束后,此时i指向A[0]需要交换的位置.
	具体需求 : 将数组A有序化
		输入 : 无序数组A
		输出 : 将A有序化
	解决方案 : 基于上述的每次将一定范围的数组首位放在合适的位置.(特点是该位置上的元素
			   对于整体还是局部都是固定不变的.)
			   第一种方法是二分法,不管每次执行交换的位置.统一二分递归调用.(实现简单,但是有多余计算,
			   比如4,3,5,7,6,此时5是上一次的执行结果,一旦j大于5后,比较就没有意义了)
			   第二种方法是根据上一次的递归结果,将当前数组划分两部分,递归调用.
 */
#include <iostream>
using namespace std;
//辅助函数
template<class T>
int Size(T &data)
{
	return sizeof(data)/sizeof(data[0]);
}


//确保A[left]在[left,right]区间的准确位置(左边<X,右边>X),返回值是X的精准坐标.
//如果返回值是-1,则表示区间错误
int partition(int *a,int left,int right)
{
	if (left < right)//由于大多数情况是left<right,就先判断先
	{
		int i = left,j = left + 1 ;
		int x = a[left];
		//保证[left+1,i]都小于A[left],[i+1,right]大于等于A[left].
		while( j <= right )
		{
			if (a[j] < x)
			{
				i++;
				//if(i!=j){交换},不妥,该判断只有在j=left+1并且a[left+1]<x时有效,其余时刻多余,浪费资源
				int tmp = a[i];
				a[i] = a[j];
				a[j] = tmp; 
			}
			j ++ ;
		}
		//最后交换
		a[left] = a[i] ; 
		a[i] = x ;
		return i ; 
	}
	else if (left > right) return -1;
	else return left;
}

void quicksort(int *a,int left,int right)
{
	if (left >= right)return;
	int s = partition(a,left,right);//前一个语句,保证执行到该步时left < right.
	quicksort(a,left,s-1);//左递归
	quicksort(a,s+1,right);//右递归
}

//测试
int main(int argc, char const *argv[])
{
	int a[]={1,3,5,7,9,2,4,6,8,0};
	int length = Size(a);
	quicksort(a,0,length-1);
	for (int i = 0;i<length;i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}
