/**
 * -*- coding : GBK -*-
 * @Author : huangshengjiang
 * @Email : 1005542693@qq.com
 * @Date : 2016-10-28 13:59
 * @Last Modified Date : 2016-11-10 18:46
 * @FileName : 自顶向下合并排序.cpp
 */

/*自顶向下合并排序
	基本概念 : 从上往下递归调用的排序,与自底向上合并排序相反
	应用场景 : 分解思想,将大问题分解成小问题,主要是分析程序代码.
	局限性 : 与自底向上排序比较,两者时间复杂度一样,另外前者比后者需要额外的空间,但是自顶向下有利于分析理解.
	具体需求 : 将无序的数组A排序成从小到大的数组
		输入 : 一组无序的数组A
		输出 : 有序的数组

	分析 : 自顶向下实际上是将数组划分成多个小数组,并对每个小数组按相同方法递归调用.
		   这里使用的是二分法(每次讲数组划分为2个部分),其递归基础是小组个数为1.
		时间复杂度 : O(nlogn)
		空间复杂度 : O(1)
 */
#include <iostream>
#include <vector>
using namespace std;
//辅助函数
template<class T>
int Size(T &array)
{
	return sizeof(array)/sizeof(array[0]);
}
vector<int> buffer;
void merge(int *a,int left,int mid,int right)//合并数组a的两个部分,
									//left表示最左边位置,mid表示左边最后位置,right表示最右边位置,下标都在[0...n-1]范围内
									//由于每次需要额外的空间暂时存放数据,因此建议在外面直接申请一个数组
{
	int i,j;
	int t;

	i = left ; 
	j = mid + 1 ;
	t = 0 ; 

	while(i <= mid && j <= right) {//i,j都在合理范围内,没有过界,当某个达到边界,则跳出循环
	    if (a[i] <= a[j])
	    {
	    	buffer[t++] = a[i++];
	    }
	    else{
	    	buffer[t++] = a[j++];
	    }
	}

	//右边已经遍历完
	while(i <= mid) {
	    buffer[t++] = a[i++] ;
	}

	//左边已经遍历完
	while(j <= right) {
	    buffer[t++] = a[j++] ;
	}

	//赋值
	i = left ;
	for (int k = 0; k < t; ++k)
	{
		a[i++] = buffer[k];
	}
}

//函数
void mergesort(int *a,int left,int right)
{
	if( left == right) return ; 
	int mid = (left + right) / 2 ; //由于/的特性,两个临近值相加/2,是左边的值.因此merge的参数mid是指左边的最后位置
	mergesort(a,left,mid) ;
	mergesort(a,mid+1,right) ;
	merge(a,left,mid,right) ;//后序遍历,先左再右最后根
}

void sort(int *a,int n)
{
	mergesort(a,0,n-1);
}

//测试
int main(int argc, char const *argv[])
{
	int a[] = {3,5,8,5,45,4,6,8,9};
	int n = Size(a);
	buffer.resize(n);
	
	sort(a,n);

	for (int i = 0; i < n; ++i)
	{
		cout << a[i] <<" ";
	}
	cout<<endl;

	system("pause");
	return 0;
}
