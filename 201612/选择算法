/**
 * -*- coding : GBK -*-
 * @Author : huangshengjiang
 * @Email : 1005542693@qq.com
 * @Date : 2016-11-09 14:50
 * @Last Modified Date : 2016-12-19 16:50
 * @FileName : 选择算法.cpp
 */

/*选择算法
	基本概念 : 从无序的数组中选出第k小的元素.(特点是不在乎数组是否有序,只要求第k小元素,再笼统点是第k小可以认为是数组的分界线.
				凡是需要对某个范围进行特殊意义的划分,要找出其分界值,都可以用到选择算法)
	应用场景 : Web分页列表点击选择,快速找出特定百分比的临界值(数据报表).
	局限性 : 如果再找出分界线之后需要统计数值,此时最好是使用快速排序算法,找出分界线的同时也保证左端都小于,右端都大于.
	具体需求 : 从无序的数组中选出第k小的元素,要求在最坏最好的时间复杂度一样,都是O(n)???(有待理解).
		输入 : 无序的数组,k值
		输出 : 第k小元素的值.

	分析 : 分析快速排序,之所以会出现最好最坏的时间复杂度不一样的原因在于每次快速排序的参考值都是取当前数组第一个元素.而不是随机选取.
		   因此会出现最坏的情况(即每次划分时数组按降序排列).
		   选择算法的最基本的理论基础是如果每次递归查找后都能舍弃1/3的数组数量,即下一次只需要在2/3中查找所求的元素.如此递归调用下,
		   其扫描的总次数是 cn(1+2/3+(2/3)^2+...) = 3-2*(2/3)^n 当n无限大时,近似3cn = O(n).
		   如何保证每次递归舍弃1/3的元素呢.书中提供的方案是每次将当前数组分为n/5组,每组5个,对n/5组分别进行排序,取出n/5个中值,再进行排序,
		   找出中值数组M的中项mm.可以用一张图描述.
		   					.........
		   					.........
		   					.........
		   					.........
		  					.........   
		  	从左到右递增,从下到上递增.所求的中项mm是位于该图的中心位置.划分为四个区域.其中左下角的元素保证能小于等于中项mm(数量A`)
		  	同理右上角保证大于等于中项mm(数量B`).假设当前数组中的严格小于mm的数量为A,明显A>=A`,A`= 3*(n/5/2)约等于0.3n,
		  	也就是说A最少也有0.3n个元素.B最多有0.7n个元素.从而保证以中项mm划分数组为3部分<,>,=.每次舍弃至少0.3n的元素.
		  	符合上述的理论基础.

			另外该图还有个特点,就是以y(y为奇数)个一组,则A>=(y/2+1)*(n/y/2)约等于(y/2+1)/2y*n = (1/4+1/2y)n,则另一方面B<=(3/4-1/2y)n
			一般而言,A(小于等于中项mm)和B(大于等于中项mm)的都是[(1/4+1/2y)n,(3/4-1/2y)n]之间.意味着每次舍弃的元素也在这个范围内.
			因此一般而言,要使该表示范围变大,且上下界限接近是最好的.分析可知,y越小越有利.

	延伸问题 : 为什么一定要3等分,不是2,4或5等分?首先需要明确的是等分数目x和总次数的关系sum = xcn.可知等分数量越少,其效率越高.
			   从另一方面讲,等分数量越少,意味着每次递归可以舍弃的元素就越多.越是能提高效率.
		   	   那为什么不直接2等分?
		   	   首先1等分很明显不对(一次递归就舍弃所有值).
		   	   其次2等分如果按上述图的划分,A>=2*(n/3/2)约等于0.33n的元素,按上述图的特点也是如此,越小越有利,那为什么不直接2等分?
	查阅书籍 : 算法导论中提示信息 : 证明分成每组3个元素(即2等分),该算法的运行时间不是线性的.
			   3个一组的话,时间复杂度是T(n)<= T(n/3)+T(n-2*n/3/2 = 2/3n) + O(n) n>=d,很明显最坏的情况下
			   不能简单的直接相加(除非已知是线性的情况下).T(n)=T(0.33n)+T(0.66n)+O(n)

	解决方案 : 1.判断当前数组数量是否小于限定值(设d,具体值后面求解),则直接进行插入排序(数量d下执行最快),直接求得值返回.
			   2.将当前数组划分n/5组,每5个一组,剩余不够分组的放在一边.不影响程序的准确性(主要求得中项mm将当前数组划分为3部分,再查找)
			   3.对n/5组分别进行排序,找出每组的中项值m1,m2,m3...,组成中项组{m1,m2,m3...}.
			   4.在对中项组递归调用,直到返回中项组中的中项mm.
			   5.以中项mm划分当前数组,<,>,=3部分.(快速排序一次)
			   6.对3部分分别比较,<,>再递归调用,=则输出.
		时间复杂度 : 设对于规模为n的时间复杂度为T(n),步骤1,2,4,5都是线性的O(n),步骤3是T(n/5),步骤6最多为T(0.7n)(导致不等号)
					 可得 T(n)<=T(n/5=0.2n)+T(0.7n)+O(n) n>=d 或 O(1) n<=d.最坏情况下是T(n)=T(0.2n)+T(0.7n)+O(n).

		空间复杂度 : 针对步骤3而言,可以开辟新的数组空间存储中项数组,也可以直接在当前数组上进行操作(复杂,大量的移位操作).
					 相比较而言,用新的数组空间更简单些.然后再撤销该数组.
					 步骤5划分当前数组为3部分,在这里最好不要重新开辟新空间.直接在原数组上进行移位操作.
					 (如果是第3种情况,则新建数组赋值,撤销当前数组,return select)

 */
#include <iostream>
#include <vector>
using namespace std;
#define  LIMIT  6	//表示限定值
//辅助函数,插入排序,划分算法
template<class T>
int Size(T &array)
{
	return sizeof(array)/sizeof(array[0]);
}

int insertLimit(vector<int> &a ,int length ,int k )//a和left表示当前数组开始位置,length表示数组长度,k值表示在当前数组的第k个元素
//小于限定值d进行直接插入排序,取k值.有k<length.
{
	int tmp = 0 ;
	int j = 0 ;
	for (int i = 1; i < length; ++i)//待排序的元素
	{
		tmp =  a[i] ;

		j = i-1 ;

		while( j >= 0 && tmp < a[j]) 
		{
		    a[j+1] = a[j] ;
			j--;
		}

		a[j+1] = tmp ; 
	}

	return a[k-1];
}

void insert5(vector<int> &a,int left)//5个一组,组内插入排序,调用前需要保证不越界.包含left本身
{
	int tmp = 0 ;
	for (int i = 1; i < 5; ++i)//待排序的元素
	{
		tmp =  a[left + i] ;

		int j = left + i - 1 ;

		while( j >= left && tmp < a[j]) 
		{
		    a[j+1] = a[j] ; 
			j-- ;
		}

		a[j+1] = tmp ; 
	}
}

void quicksort3part(vector<int> &a,int length,int mm,int& leftlength,int& midlength)//a表示数组头指针,length表示数组长度,
//mm表示划分中值mm,leftlength表示左部分的长度,midlength表示相等部分快速排序一次
{
	int i = 0, j = length -1 ; //i,j分别表示左右两端的下标.两者向中间移动,直到相遇

	int left_loc = 0 , right_loc =  length - 1 ; //left_loc表示左边等于mm要交换的位置,right_loc表示右边等于mm要交换的位置
	//重新思考如何将当前数组a依据中项mm划分为<,=,>3部分.
	/*
	解决方案1 : 类似快速排序的方法(一次排序后,mm插入的位置左边小于等于mm,右边都大于mm,问题是如何保证在每次要交换的位置都小于mm?
				
				-----------------------------------------该讨论无效-----------------------------------------------------
				关键是如何明确相遇的具体条件,是i==j(指向同一个小于mm的值),还是i+1==j(i和j相邻,且j<i,此时i指向小于mm的值).
				考虑到极端情况(即当前数组都小于mm,则此时i = length 越界)采取i==j为相遇,则对应的约束条件i<j.
				--------------------------------------------------------------------------------------------------------
				
				目标是 每次递归结束后,此时指向待交换的元素位置,其元素值的特性必须是小于等于mm.
				在约束条件i < j的多数情况下,i==j此时指向较大值,特例情况是所有值都小于mm,此时i==j==length-1指向较小值.因此在跳出
				最外围while循环后,需要判断i==length-1,是则交换a[i],否则交换a[i-1].
				但是针对本题来说,不可能所有值都小于mm,因此不会出现i==length-1的情况,则跳出while循环,i和j都指向较大值.
	 */
	int temp = 0 ;

	while(i < j) 
	{

	    while(a[i] <= mm && i < j ) {

	        if (a[i] == mm)//暂时放在左侧
	        {
	        	temp = a[i] ;

	        	a[i] = a[left_loc] ;

	        	a[left_loc ++] = temp ;
	        }
	        i++;
	    }

	    while(a[j] >= mm && i < j ) {

	        if (a[j] == mm)//暂时放在右侧
	        {
	        	temp = a[j] ;

	        	a[j] = a[right_loc] ;

	        	a[right_loc --] = temp ;
	        }
	        j--;
	    }

	    temp = a[i] ;
	    a[i] = a[j] ;
	    a[j] = temp ;
	}
	//跳出循环时,i和j都指向较大值,并且有a[i-1]<mm<a[i]的固定不等式.
	//将等于mm的值放在中间
	j = 0 ; //j此时无用,作为遍历值

	leftlength = i - left_loc ; 

	midlength = length - 1 - right_loc + left_loc ; 

	int k = leftlength ;

	//将左右两侧等于中项mm的值放在中间.
	for (; k < i  ; ++k)
	{
		temp = a[k] ;
	    a[k] = a[j] ;
	    a[j] = temp ;
	    j++;
		//a[k] =  a[j++];
	}

	j = right_loc + 1 ; 

	for (; k < leftlength + midlength  ; ++k)
	{
		temp = a[k] ;
	    a[k] = a[j] ;
	    a[j] = temp ;
	    j++;
		//a[k] =  a[j++];
	}

}

//函数
int Select(vector<int> &a,int length,int k)//length表示数组长度.下标为[0,length-1]
{
	//步骤一
	if (length <= LIMIT)
	{
		return insertLimit(a,length,k);
	}
	//步骤二,三
	int n = length/5;

	vector<int> midarray(n,0); //创建midarray数组

	for (int i = 0; i < n; ++i)
	{
		insert5( a , i*5 ) ; 

		midarray[i] = a[i*5+2] ; 
	}
	//步骤四
	int mm = Select(midarray,n,(n+1)/2);//这里要考虑奇数/还是偶数个.中项是n/2的上限,可改为(n+1)/2
	//撤销midarray数组
	midarray.clear();

	vector<int> (midarray).swap(midarray);
	

	//步骤五
	int leftlength = 0,midlength = 0;

	quicksort3part(a,length,mm,leftlength,midlength);

	//步骤六
	if (k <= leftlength )
	{
		return Select(a,leftlength,k);
	}
	if (k <= leftlength + midlength)
	{
		return a[leftlength+midlength-1];
	}
	if (k > leftlength + midlength)
	{
		int rightlength = length-leftlength-midlength;

		vector<int> rightarray(rightlength,0);//创建rightlength数组

		for (int i = 0; i < rightlength; ++i)
		{
			rightarray[i] = a[leftlength + midlength + i] ; 
		}
		//撤销当前数组a
		a.clear();

		vector<int> (a).swap(a);

		return Select(rightarray,rightlength,k-leftlength-midlength) ; 
	}
}

//测试
int main(int argc, char const *argv[])
{
	int b[] = {8,33,17,51,57,  49,35,11,25,37,  14,3,2,13,52,  12,6,29,32,54,  5,16,22,23,7};

	int length = Size(b);
	vector<int> a(length);
	for (int i = 0 ; i< length ; i++)
	{
		a[i] = b[i];
	}
	int result = Select(a,length,25);//52,54,57
	cout<< "结果为" << result <<endl;

	system("pause");
	return 0;
}
