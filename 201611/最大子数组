/**
 * -*- coding : GBK -*-
 * @Author : huangshengjiang
 * @Email : 1005542693@qq.com
 * @Date : 2016-11-09 14:42
 * @Last Modified Date : 2016-11-21 14:43     
 * @FileName : 最大子数组.cpp
 */

/*最大子数组
	基本概念 : 在数组A中(有正有负),存在一段连续的子数组,其元素之和是最大的.例如有A[5] = {2,-7,4,-2,5},
			   其中最大子数组为A[2..4],特性是(一般情况下)数据有正有负.
			   
	应用场景 : 股票的应用(寻找最佳的买入和买出时间,已知后面的股票起伏).
	具体需求 : 找出数组中的某个子数组,其元素之和是最大的.
		输入 : 一组有正有负的数组
		输出 : 最大子数组的左右坐标[1...n]范围内,最大子数组最小值为0,即(都是为负,不选择)

	分析 : 以几何图为例,数据在图像上表现为上下起伏(如股票),要求出向上(not向下)的最高幅度(这样只要求出最小值最大值,
		   并且最小值的位置小于最大值的位置,概率为一半),如果最小值locmin在最大值locmax后面则需重新计算,概率为一半.
		   那么重新计算如何使用最大值,最小值的信息简化时间复杂度呢?
	重新分析 : 这种有正有负的数据有两种表示方式后一个相对前一个的变化,大于为正,小于为负.
			   1.是以第一个数字为基础,对前一个的变化都计算出来,形成折线图.
			   所求的最大子数组在图像上的显示是某两点的差距(正向)是最大的.
			   2.是以0为基准,正在上,负在下的柱状图.
			   最大子数组在该图中的表现是两点之间的所有面积之和是最大的.


	解决方案1/2 : 最直接最易懂的方法是一一尝试,求出所有可能的子数组,比较找出最大值的子数组输出.
		优缺点 : 时间复杂度为O(n^3),太大不适合.可以改进,直接从a[i..j]的基础上计算a[i..j+1]的值,时间复杂度为O(n^2).
				 还可以改进.
				 方案1/2的思想都是遍历所有可能的排列数组,并相互比较,可不可以通过一些有效的判断,删去不需要的计算排列数组

	解决方案3 : 分治思想,每次将当前数组等分为两部分,分别求出两部分的最大子数组,但这不一定是当前数组的最大子数组,
				因为最大子数组有可能存在于跨越两部分.这里的关键性问题是如何确定中间部分的最大数组,其范围是在
				左右最大子数组范围内.比较得出当前数组的最大子数组信息.
				当前数组的中间最大子数组的可能范围是在[low,high]左右最大子数组范围内.但是有个特性是必然包含中间元素.
				左右两端的数组可以不断的递归下去,直到递归基础left==right指向一个值,有logn次递归.
				中间元素的求解从中间向两边各自扫描,找出其左右最大部分,相加就是中间最大子数组
		优缺点 : 重复计算中间的扫描过程,但易于理解.

	解决方案4 : 扫描思想,从结果找规律,
				规律1 : 很明显无论怎样的数组(有正有负),其最大子数组的左右两端的值必定为正.两端外侧的值必然是负.

				------------------------以下讨论有些价值---------------------------
				规律2 : 反推法,已知[k,m]是数组中的最大子数组.则可以看成+-+-[k,m]-+-+.
						其左右两端的负值绝对值总和一定大于正值.
						规律2否决,本身就存在问题,一旦和为负值,舍弃(有可能是最大子数组),
						因此舍弃的时候需要与当前最大值判断后,再舍弃

				更根本的原因是非最大子数组也有这样的情况,而不是最大子数组独有的.因此规律2完全否决,以下的讨论否决
				
				因此可根据这个结果规律,快速求出最大数组.
				具体方法是从数组两端往中间扫描,两边都找到正值的位置i,j,可以明确的是最大子数组必然在[i,j]里.
				关键是内部如何继续处理??
				思考过程 : 内部如果都是正的,则当前i,j就是最大子数组.
				如果内部有一个负的,则划分为左右两个正部分和中间一个负部分.最大值呢?极端点,如果负值过大,只能取正大的部分.
				如果为-1的话,则最大就为这3部分之和.用数学方法来描述,则左部分值为sum_more,右部分为sum_less,中间负值为x.
				有如下关系 : sum_more + sum_less - x  与 sum_more 的比较决定那部分为当前最大子数组.
				也就是说x值要比其中较小的部分和大,则需要舍弃这较小正部分.
				如果内部有2个负的,则将数组划分为3个正部分和2个负部分.
				太麻烦!!
				重新思考 : 基础是从数组两端往中间扫描,两边都找到首个正值的位置i,j.最大子数组在[i,j]里
				如何继续处理 ? 
				根据规律2的说明是两端从左右正值向内扫描,
				首先是左端开始同时累加,记录开始点,一旦出现和为负值,则舍弃该部分置和为0,继续扫描.
				直到右端相遇.记录前一个开始扫描点i
				然后是右端扫描同时累加,记录开始点,一旦和为负值,则舍弃该部分,开始点为下一个扫描点同时和置0,
				直到和左端的扫描点相遇.记录前一个开始扫描点.j
				因此此时[i,j]就是最大子数组.有问题,如果+-+,中间的负值远远大于另外正值.则根据上述方法得到的结果一直是右边的+.
				不可,需要改正.
				问题出在和出现负值的情况下舍弃之前的累加计算.(有可能舍弃了最大子数组)
				---------------------------------------------------

				继续重新思考 : 
				规律1 : 很明显无论怎样的数组(有正有负),其最大子数组(后选子数组)的左右两端的值必定为正.两端外侧的值必然是负.
				从方案2的思考点出发,考虑较少不必要的计算.首先从左右两端往中间遍历,找到第一个正值i,j.然后从i开始正值遍历,直到遇到
				负值.比较sum;等等,这种方法不是将[i,j]分割成多个正负相间的部分,并计算所有的可能性.如果正部分有n/2(最多),
				负部分n/2-1个.则可能的组合有O(n^2)个,那能不能再减少组合次数呢?
				
				结论 : 从左边正值开始遍历,累加正部分,并与当前的最大子数组比较,然后累加负部分,如果小于0,则从下一个正值开始累加;
				如果大于0,则继续累加完正部分,在于当前最大子数组比较;直到遍历结束.

				数学基础 : 找出+-+-+-+的顺序子数组和最大,最基础的+-+三部分,暂存首个+部分,计算+-,小于0,
				则舍弃(可能是最大子数组保留下来),没有扩展的价值,从下一个+开始,大于0则表示有扩展的价值,此时+-+累加再比较.
				则存储下+-+当前的最大子数组和保留有效的延展性.

 		优缺点 : 快速,时间复杂度为O(n).这是运用观察规律得到的结果

	有4种解决方案,分别是立方,平方,分治,扫描两种.

 */
#include <iostream>
using namespace std;
template<class T>
int Size(T &array)
{
	return sizeof(array)/sizeof(array[0]);
}

//函数
int Maxsum_simple(int *a,int n,int &left,int &right)//a表示指向数组的指针,n表示数组个数
//left,right是最大子数组的左右下标.范围在[0...n-1],返回值类型是int,表示最大子数组之和.
{
	int sum = 0 ;
	int tmp = 0 ;
	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			tmp = 0 ;
			for (int k = i; k <= j ; ++k)
			{
				tmp += a[k] ;
			}
			if (tmp > sum )
			{
				left = i ;
				right = j ;
				sum  = tmp ;
			}
		}
	}
	//这种方法是最简单的,时间复杂度为O(n^3),可以改进
	return sum ;
}

int Maxsum_impsimple(int *a,int n,int &left,int &right)//a表示指向数组的指针,n表示数组个数
//left,right是最大子数组的左右下标.范围在[0...n-1],返回值类型是int,表示最大子数组之和.
{
	int sum = 0 ;

	int tmp = 0 ;
	for (int i = 0; i < n; ++i)
	{
		tmp = 0 ;
		for (int j = i; j < n; ++j)
		{
			tmp += a[j] ;
			if (tmp > sum )
			{
				left = i ;
				right = j ;
				sum  = tmp ;
			}
		}
	}
	//这种方法是最简单的,时间复杂度为O(n^2),还可以改进
	return sum ;
}

/*int abs_test(int x)
{
	return x > 0 ? x : -x ;
}*/

int Maxsum_scan(int *a,int n,int &left,int &right)//a表示指向数组的指针,n表示数组个数
//left,right是最大子数组的左右下标.范围在[0...n-1],返回值类型是int,表示最大子数组之和.
{
	//关键是如何控制+-+之间的正负变化控制.功能是能够知道+-,-+的变化.abs(a)+abs(b) 与 abs(a+b) 比较,不同则产生变化
	//相同则没有变化.除头尾两个abs一次,其余都需要abs两次.总共需要abs 3n次.可以用某个值替代abs(b),减少计算.
	
	//返回值
	int sum = 0 ;

	// a和b暂存abs的数据
	int a_tmp = abs(a[0]);
	int b = 0 ; 

	//暂存某个子数组相关数据,			注意点是遍历的开始和结束处理.
	int tmp_sum = a[0] > 0 ? a[0] : 0 ;
	int tmp_left = -1 ;	//指向左边正值的前一个负值下标

	for (int i = 1; i < n; ++i)
	{
		b = abs(a[i]) ; 

		if (a_tmp+b != abs(a[i-1]+a[i]) && a[i] < 0)//发生符号变化,+到-,需要比较保留,或-到+需要继续
		{
			//与当前子数组比较
			if (tmp_sum > sum)
			{
				sum = tmp_sum ;
				left = tmp_left + 1 ;
				right = i-1 ;
			}
		}
		
		tmp_sum += a[i] ;
		
		if (tmp_sum < 0)//和小于0,舍弃
		{
			tmp_sum = 0 ;
			tmp_left = i ;
		}

		a_tmp = b ; 
	}

	//遍历截止,若为正则需比较.        注意点是遍历的开始和结束处理.
	if (tmp_sum > sum)
	{
		sum = tmp_sum ;
		left = tmp_left + 1 ;
		right = n-1 ;
	}

	return sum ; 
}

//设置数据结构,存放当前数组的相关信息
struct array_messege
{
	int sum ;    //最大子数组和
	int left ;	 //最大子数组左下标
	int right ;	 //最大子数组右下标
	array_messege(int left_,int right_) : left(left_),right(right_),sum(0){}
};


int Maxsum_div_detail(int *a,int n,int left_org,int right_org,int &left,int &right)//a表示指向数组的指针,n表示数组个数
//left_org,right_org表示当前数组的划分,left,right是求得的最大子数组的左右下标.范围在[left_org...right_org],
//返回值类型是int,表示当前最大子数组之和.
{
	if (left_org == right_org )//递归基础 : left == right ,此时当前数组只有一个元素,其值为正,取该值,否则为负取0.
	{
		return a[left_org] > 0 ? a[left_org] : 0 ;
	}
	
	int mid = (left_org + right_org) / 2 ; 

	array_messege  l(left_org , mid ) ;  //表示左边数组的最大子数组的信息 
	array_messege  r(mid+1 ,right_org ) ;//表示右边数组的最大子数组的信息 

	l.sum = Maxsum_div_detail(a,n,left_org,mid,l.left,l.right);//求出左边最大子数组信息

	r.sum = Maxsum_div_detail(a,n,mid+1,right_org,r.left,r.right);//求出右边最大子数组信息

	//重点求出中间的最大子数组信息.其特点是一定跨越其中间边界,其实用到扫描的思想
	int lmax , rmax , temp ,left_m = mid, right_m = mid + 1 ; //lmax,rmax左/右最大值,temp暂存结果用于比较.
	//最后存储lmax+rmax;left_m,right_m为中间的左右边界
	lmax = temp = 0 ;
	for (int i = mid ; i >= left_org ; i--)
	{
		temp += a[i] ;
		if (temp > lmax)//不能有等号,如果出现极端现象,都是负值
		{
			lmax = temp ;
			left_m = i ;
		}
	}

	rmax = temp = 0 ;
	for (int i = mid + 1; i <= right_org ; ++i)
	{
		temp += a[i] ;
		if (temp > rmax)
		{
			rmax = temp ;
			right_m = i ;
		}
	}
	array_messege m(left_m,right_m) ;
	m.sum = lmax + rmax ;

	//比较三者的大小
	array_messege tmp(left_org,right_org) ; 
	tmp = l.sum > r.sum ?  l : r ; // 此时temp作为存放最大值的变量(容器)
	tmp = tmp.sum > m.sum ? tmp : m ; //三者的比较不能有等号,否则会引起歧义(如 left有两个值),最好设置数据结构.消除二义性

	left = tmp.left ; 
	right = tmp.right ; 
	
	return tmp.sum ;
}

int Maxsum_div(int *a,int n,int &left,int &right) 
{
	return Maxsum_div_detail(a,n,0,n-1,left,right) ;
}

//测试
int main(int argc, char const *argv[])
{
	int a[] = {31,-41,58,97,-53,59,26,-93,-23,84};//{31,-41,59,26,-53,58,97,-93,-23,84};
	int n = Size(a);
	int left,right;
	int result = Maxsum_div(a,n,left,right);
	cout << "左下标为" << left << "右下标为" << right << endl;
	cout << "和为" << result <<endl;
	system("pause");
	return 0;
}
