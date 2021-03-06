/**
 * -*- coding: GBK-*-
 * @Author : hsj
 * @Email : 1005542693@qq.com
 * @Date  2016-08-26 14:13
 * @Last Modified time : 2016-09-19 10:12
 * @FileName : 基数排序.cpp
 */

/*基数排序
	原理 : 比较相同数位上的数值,确定排序顺序,不相等的大放前,小放后,而相等的则再比较后一数位,直到最后一位
	(暂时不考虑小数情况)
	问题 : 
		1.如果数位不一致,如何处理?(补0还是计算位数)
		答 : 想法1.计算位数,将数组先按位数分组,组内再按下述递归方法
			 想法2.计算位数,求出最大位数值,将数组的其他位数补0,形成以最大位数值的数组,再按下述递归方法
			 相比较而言,想法1比想法2更好,不用求最大位数和补0,但是想法1需要计算位数
			 (可以用struct,inline函数求位数值,用temp/10?,算法太复杂,不可) 哎,最后还是用这种方法~~~^_^~~~
			struct digit
			{
				int value;
				const int count_num;
				inline digit(int value):count_num(0)//不可,内含循环while,会自动取消内联函数,成为普通函数
				{
					this->value=value;
					while(value) //求位数的计算可以再简单点不?暂时放着
					{
						value/=10;//将10改为0x0A汇编语言的效果一样
						this->count_num++;
					}
				}
			};
			具体用法 : digit b[5]={54,345,321,4567,78905};

		延伸问题 : 能不能不用每次计算位数呢?
		答 : 比较是从数的对应位的最高位开始,如果最高位的位数不同,那根本就不用比较,位数少的自然排后.因此必须知道数的位数,不可避免.


		2.每次比较的数量问题会影响排序效率?(如果每次比较两个数值,排序效率低效且有多余重复比较)
		答 : 最好能找到能够一次性比较所有的数字,因为数值范围是[0~9],只有10种情况,(最高位开始比较)
			 可以每次比较将整个数组分为0个小组,分别为0组,1组...9组,很明显0组最小,9组最大,组间的位置是固定的,
			 而组内成员位置不是固定的,因此还需要继续划分(递归),直到出现组内出现1或0个成员或者比较的位数为个位(不考虑小数)

		3.如何分组?
		答 : 思路1 :树结构,该树的度至多为10,根节点为-1,从左到右,依次是0~9.每个节点表示数字对应位置上的值(位数不足则补0),
				   一个数的表示方式为从根节点到叶子节点的一条路径,最后形成一颗大树.
			       从左到右遍历叶子节点,就是从小到大排序出来.(要考虑相同值情况,结果显示,遍历叶子过程,添加新数)
				优点 : 再次添加新数,会简单许多.
			 	缺点 : 当出现大量位数偏小,而有几个位数偏大的值时,这棵树的无用节点过多(0)
			 	改进 : 将一棵大树分解,按位数的个数来确定树的个数.避免不必要的0节点.
			 好吧︿(￣︶￣)︿就先用这种结构.
			 
			 遍历结果显示 : 没写
			 节点所需的元素 : 1.指针数组(数组中的每个元素是指针,分别指向10个节点,初始值为NULL) 2.没写
			 总结 : 太复杂,暂不需要
*/			
/*看书感想
	看书后,了解到书中的基数排序的比较是从低位向高位,第一次按个位排序,第二次按十位排序,以此类推,直到所有数的高位都为0.
	自己的思路一直是从高位到低位比较,有考虑到从低位到高位的情况,但是被自己主观想象否决了,认为是不可能实现的.
	感想: 警惕思路狭隘,慎重对待主观想法,不可臆想相反观点的错误性,要证明相反观点的错误性,最好是按相反观点试一试,实践出真知.
		  算法方面,可以举个简单例子,证明想法.
 */
/*重新思考
	将随机数组按基数排序,例子如下: 第一次按个位排序,第二次按十位排序,第三次按百位排序...
	65231  65231  48621  65231  65231  48621
	56329  48621  75322  75322  75322  56329
	48621  75322  56329  56329  56329  56986
	56986  89654  65231  48621  56986  65231
	75322  56986  89654  89654  48621  75322
	89654  56329  56986  56986  89654  89654
	结果显示 : 方法可行,每一次将整体以某位上的数值比较,直到最高位,排序结束.(整体划分)
	反过来比较呢?例子如下 : 第一次按万位排序,第二次按千位排序,第三次按百位排序...
	65231  48621  48621
	56329  56329  56329
	48621  56986  56986
	56986  65231  65231
	75322  75322  75322
	89654  89654  89654
	结果显示 : 方法可行,每一次从高位比较,分割成至多10组,组内再次划分组,再排序,直到个位.(分组再分组,复杂)

	总结 : 很明显,用第一种方法更加便捷简单,操作不复杂.
	
	具体方法 : 先将数据按位数count_bit分组,再对每组分别依位排序(从末尾到首位),每次排列是将组内的相同数位比较排序(一个数排序,选取插入为重点)
				直到最高位,则排序结束.
			   
	引申问题 : 如何对一堆有序的个数从小到大排序,相同数字的相对位置不变?能不能将数组遍历时间缩小到O(nlogn)
	解决办法 : 最简单粗暴的方法是利用分组的思想,分为10组(0~9).将比较位置相同的数放入对应的分组中,然后迭代取出放入小组中,再重新分配

	时间复杂度 : ∑i×ni²其中∑ni的值为n,i为ni对应的位数,则如何计算呢?

	待解决问题 : 尝试精简以及从首位到尾位比较进行排序?
 */




#include <iostream>
#include <vector>
using namespace std;

#define  N  15	//能够处理的数字最大位为14位
class digit
{
	int value;
	int bit_count;
	vector<int>  bit_value;
	public :
	digit(int value):bit_count(0)
	{
		this->value=value;
		while(value) 
		{
			bit_value.push_back(value%10);
			value/=10;
			this->bit_count++;
		}
	}

	int  BitValue(int n){
		return bit_value.at(n);
	}
	int  Bitcount(){
		return bit_count;
	}
	int  Value(){
		return value;
	}

};

void  RadixSort(vector<digit> *Group,vector<digit>  *SubGroup){
	for (int i = 1; i < N; ++i)
	{
		if (Group[i].size() != 0)	//有数的组
		{
			int Length_Group = Group[i].size();
			for (int j = 0; j < i; ++j)//j表示比较的位数,某组某个数字的第j位比较,表达式为Group[i][k].Bitcount(j);
			{
				vector<digit>::iterator  it_Group=Group[i].begin();
				for (;it_Group != Group[i].end(); it_Group++)
				{
					SubGroup[it_Group->BitValue(j)].push_back(*it_Group);
				}
				it_Group=Group[i].begin();
				for (int k = 0; k < 10; ++k)
				{
					if (SubGroup[k].size() != 0)
					{
						for (vector<digit>::iterator  it_SubGroup=SubGroup[k].begin();it_SubGroup != SubGroup[k].end(); it_SubGroup++)
						{
							*it_Group = *it_SubGroup;
							it_Group++;
						}
						SubGroup[k].clear();
					}
				}
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	freopen("C:\\Users\\Administrator\\Desktop\\in.txt","r",stdin);
	int temp=-1;
	vector<digit> Data;			//暂时存放整体数组
	vector<digit> Group[N];		//按照位数的个数分组,N=15,则最多为14位,如34是两位数,则分到第3组Sort[2]去,Group[0]无用
	vector<digit> SubGroup[10];
	//读取数据,初始化
	while (scanf("%d",&temp) != EOF)
	{
		Data.push_back(temp);
	}
	
	//分组Sort
	int Length_Data = Data.size();
	for (int i = 0; i < Length_Data; ++i)
	{
		Group[Data[i].Bitcount()].push_back(Data[i]);
	}
	
	//对每组分别进行基数排序
	RadixSort(Group,SubGroup);
	
	//显示
	for (int i = 1; i < N; ++i)
	{
		if (Group[i].size() != 0)	//有数的组
		{
			cout<<i<<"位数: ";
			for (vector<digit>::iterator  it_Group=Group[i].begin(); it_Group != Group[i].end(); it_Group++)
			{
				
				cout<<it_Group->Value()<<" ";
			}
			cout<<endl;
		}
	}



	system("pause");
	return 0;
}
