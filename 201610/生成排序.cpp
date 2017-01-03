/**
 * -*- coding : GBK -*-
 * @Author : huangshengjianng
 * @Email : 1005542693@qq.com
 * @Date : 2016-09-08 16:50
 * @Last Modified Date : 2016-10-27 10:31        
 * @FileName : 生成排序.cpp
 */

/*生成排序first
	应用场景 : 计算概率,如彩票的中奖率等.作为其他算法的基础,如字典序等

	输入 : 一个正整数n
	输出 : n!个全排序(不重复),没有考虑到数字重复的情况.
	相关概念 : 全排序是1~n的每个数字有且仅有一个构成的排序.
	
	分析 : 自然思想是对数组array[0]从集合n中遍历,找出i,在对余下形成的集合继续遍历,直到集合为空.输出.
		   数学思想是递归的思想n的全排序是在n-1的全排序基础上实现的.因此有两种解决方案.
		   另外从输出的角度看,有n!个输出,那么该程序的时间复杂度至少为O(n!).	 

	解决方法1 : 构建数组array[n],对array[0]循环存放1~n中的某个值i,对余下n-1个数关于array[1~n]进行全排序.
				对于n-1的全排序也是递归的.
				关键是如何确保n-1的全排序中不出现i值呢?如何确保n-2个全排序中不出现i或j值呢?....
				首先数组按1~n有序排列.对应的数组下标为[0...n-1].每一次递归是先从剩余数组中for循环找出一个值放在
				剩余数组的头位置.递归基础是剩余数组个数为0时,输出.
				
	解决方法2 : 递归.方法类似.思想相反,方法1是从数组中拿出一个放入指定的位置,方法2是将指定的数值放入随机位置中.
				具体为每一次递归将固定值放入所有空的位置.递归基础是空的个数为0个.从n到1,还是从1到n没有区别.

	解决方法3 : 非递归方式,找出数组的替代数,替代点.交换后面大于替代数的最小值.然后将替代点后面的数组倒序.
	缺点 : 开始必须是123有序的数组.

	引申问题 : 1.n!的计算公式(简单易懂的)?
			   答 : n越大,可以用斯特林公式近似.
			   2.考虑数组中有重复数字的情况?

 */

#include <iostream>
#include <vector>
using namespace std;

static int count = 1;
void print_out(int array[],int n)
{
	cout << ::count ++ << "数组为:";
	for (int i = 0; i < n; ++i)
	{
		cout << array[i] << " ";
	}
	cout <<endl;
}

void swap_int(int &a,int &b)
{
	int temp = a;
	a = b ;
	b = temp ;
}

void perm1(int *array,int n,int m)//m表示第m个,对应的数组下标为m-1
{
	if(m == n)
	{
		print_out(array,n);
	}//递归基础
	else
	{
		for (int i = m - 1; i < n; ++i)
		{
			swap_int(array[m-1],array[i]);
			perm1(array,n,m+1);
			swap_int(array[m-1],array[i]);
			//关键是如何保证递归后还是原来的排序.(如12345当1与3交换成32145,递归后还是32145,再进行交换)
			//这两句交换的精髓就是保证递归后还是递归前的排序.
			//理由 : 从最底层就保证递归前后的排序一致性.只能举例子.
			//从1看交换无差别 1
			//从2看交换开始12,21,返回12.
			//从3看交换是123,132, 213,231, 321,312.
		}
	}
}


void perm2(int *array,int n,int m)//m表示第m个元素,下标为m-1
{
	if (m == 0)//m == n+1
	{
		print_out(array,n);
	}
	else
	{
		for (int i = 0; i < n ; i++ )
		{
			if (array[i] == 0)
			{
				array[i] = m;
				perm2(array,n,m-1);//m+1
				array[i] = 0;
			}
		}
	}
}

//非递归方式 : 每次从右往左找出第一个小于右边的替代数,坐标为替代点.同时替代点后面比替代数大的最小数,进行交换.再对后置位倒置.
//             结束的判定条件是没有找到替代数.
void exchange(int &a , int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
void perm3(int *array,int n)
{
	int loc = -1 ;  //表示替代数的下标(替代点) 范围[0...n-1]
	int min_loc = 0; //表示需要交换的比替代数的下标
	print_out(array,n);
	while (true)
	{
		loc = -1;
		for (int i = n-2 ; i >= 0; i--)
		{
			if (array[i] < array[i+1])//不用等号,理由是替代完仍然是原数组,会陷入死循环中.
			{
				loc = i ;
				int temp = array[loc+1];//要交换的数,暂时为其右边的值
				min_loc = loc+1 ; //下标
				for (int j = n-1; j > loc ; j--)
				{
					if (array[j] > array[loc])
					{
						if (array [j] < temp)
						{
							temp = array[j];
							min_loc = j;
						}
					}
				}
				//交换
				exchange(array[loc],array[min_loc]);

				//反序
				int length = n - loc -1 ; //length表示待反序的个数,loc+1..n-1有length个
				int mid = loc + length/2 ; 
				for (int k = loc + 1 ; k <= mid ; k++)//loc+1,n-1    loc+2,n-2  loc+3 ,n-3 
				{
					exchange(array[k],array[n-k+loc]);
				}
				print_out(array,n);
				break ;
			}
		}
		if (loc == -1)return ;
	}
}

//测试
int main(int argc, char const *argv[])
{
	int n = 5;
	int a[]={1,2,3,4,5};
	perm1(a,n,1);
	::count =1;

	int b[]={0,0,0,0,0};
	perm2(b,n,n);
	::count =1;

	int c[]={1,2,3,4,5};
	perm3(c,n);
	::count =1;
	
	system("pause");
	return 0;
}
