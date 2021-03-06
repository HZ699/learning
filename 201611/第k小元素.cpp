/**
 * -*- coding : GBK -*-
 * @Author : huangshengjiang
 * @Email : 1005542693@qq.com
 * @Date : 2016-10-28 13:58
 * @Last Modified Date : 2016-11-08 14:20
 * @FileName : 第k小元素.cpp
 */

/*第k小元素
	基本概念 : 找出数组中的第k小的元素并输出.
	具体需求 : 从乱序的数组中快速找出第i小的元素并输出(重复的情况)
		输入 : 一组无序的数组A,
		输出 : 数组A中第k小的元素.

	分析 : 为了能在线性时间内快速找到第k小的元素,可以利用到二分搜索.
		时间复杂度 : O(n)
		空间复杂度 : 需要一个额外空间

	解决方案1 : 最实在的方法是先排序,在取第k值返回.这种方法的时间复杂度最少是O(nlogn)(选用自底向上合并排序)
		优缺点 : 能够确保在O(nlogn)的时间复杂度内完成,缺点是没有必要再对后面的数据进行排序.浪费大量的时间
		
	解决方案2 : 类似于快速排序(找一个参照值,i从左到右直到小于参照值,j从右到左直到大于参照值,然后交换a[i]和参照值,结束条件是i<=j),
				由于快速排序有个特性,就是每一次排序后,参照值都是放置在应有的位置上.也就是说当a[i]与参照值交换后,参照值的位置是固定的.
				即此时i就是参照值的下标.如果i==k的话,就输出当前的参照值.
				第一遍是比较是O(n),第二次大概是O(n/2),第三次是O(n/4),比较次数相加接近O(2n),交换次数最多O(2n)次,最少是O(n)次,
				平均O(1.5n)次.
				其递归的关键在于递归最后一次与参照值的交换,

	引申问题 :  可不可以不用交换呢,只通过比较来确定呢?
				如果只比较的话,还需要另外的额外空间来保存期比较的下标信息,开始以第一个数为参照值,遍历一遍知道小于和大于的个数x和y
				判断k在哪个范围内,关键在于下一步,如何确定下一个参照值,可以通过第一次比较时记录下重要的点,
				比如参照值的0.5,1.5,2倍范围的值.然后根据k/x的比例选取相应的记录点作为参照值.递归继续下去.
				这是一种概率问题,有许多无法确定因素,
				1.没有0.5,2倍这样精准地值,如何确定其范围大小?
				2.如果数据发生突越,即不在指定倍数范围内?
				3.k/x的比例要如何选取那个倍率记录点?(哪个近选哪个)
				4.最关键的是每次递归都要比较最多(2*l+1)*n次(其中l表示记录点的数量),时间复杂度最多为O(n)
				恩,这里的关键是确定记录点的个数m,倍率数组a[m]以及范围大小b[m],如果有大量数据,就可以确定这些值,快速找出第k个元素值.
				应该另起一个文档.

	方案对比 : 考虑交换和比较的代价.如果代价是h倍(h>1),则方案2复杂度是O(2+1.5h)*n,概率的复杂度是O(2*l+1)*n,
				这两个比较是1.5h+1>2*l即h>1.3l时,可用概率方案.

 */
#include <iostream>
using namespace std;
//辅助函数
template<class T>
int Size(T &array){
	return sizeof(array)/sizeof(array[0]);
}

//函数
void select(int *a,int left,int right,int k,int &out)//递归方法,a表示数组,left和right表示搜索范围[left,right],
													//k表示所求的位置,out表示输出的值
{
	int i,j ;
	int change ;
	int temp ;

	i = left ;
	j = right ;
	change = a[left] ;//这里应该随机选取数组,避免出现每次递归划分成一个大部分,一个小部分.

	while(i < j) {
	    while( a[j] > change && i < j) {
	        j--;
	    }
	    while( a[i] <= change && i < j) {
	        i++;
	    }
	    temp = a[i] ;
	    a[i] = a[j] ;
	    a[j] = temp ;
	}

	if (i == k)//递归基础(快速排序)
	{
		out = change ; 
		return ; 
	}

	a[left] = a[i] ;
	a[i] = change ;

	if (i < k)
	{
		select(a,i+1,right,k,out) ;
	}
	else 
	{
		select(a,left,i-1,k,out) ;
	}
}


void selectmain(int *a,int n,int k,int &out)
{
	out = 0 ;
	k--;  					//对应下标
	select(a,0,n-1,k,out);
}

//测试
int main(int argc, char const *argv[])
{
	int a[] = {1,2,3,7,5,6,3,6,8,9};
	int length = Size(a);
	int out = 0 ;

	selectmain(a,length,3,out);
	cout << out <<endl;

	system("pause");
	return 0;
}
