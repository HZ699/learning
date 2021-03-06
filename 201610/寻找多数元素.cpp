/**
 * -*- coding : GBK -*-
 * @Author : huangshengjiang
 * @Email : 1005542693@qq.com
 * @Date : 2016-09-21 11:15
 * @Last Modified Date :  2016-10-19 10:46
 * @FileName :   寻找多数元素.cpp
 */

/*寻找多数元素.cpp
	基本概念 : 在数组A[1...n]中,如果有个数值的数量超过[n/2]个,则认为该数值为多数元素,返回该值.否则返回-1

	观察结论 : 在数组中删除任意两个不同的数值,则原数组中的多数元素在新数组中仍然是多数元素.

	解决办法1 : 数组表示,申明一个大小为max(A中最大的数值)的动态数组B[max](需要遍历A),初始化为0.再对数组A遍历,在B[A[i]]++;
				遍历结束后,B[j]的值就是对应j=A[i]的数量.只要B[j]的值大于n/2下限,则输出j,否则输出-1
	评估1 : 时间复杂度为n*n*max,空间复杂度为max大小的数组.有一个严重的缺陷,申请了大量无用的空间max-n.如果max过大
			n偏小,极大浪费内存,也消耗cpu的功能.

	解决办法2 : 链表表示,节点结构Node包含三个成员变量,value表示数值,count表示该数值的数量,next是指针,指向下一个Node.
				遍历数组A,将A[i]与链表从头到尾进行比较,若找到相应的value值,则count++;如果没有,则new一个Node,value=A[i],count=1,next = NULL;
				然后遍历链表,如果链表中的节点this->count > n/2,则输出this->value;否则输出-1
	评估2 : 节省了大量数组表示的空间,空间复杂度为different(不同的元素数量)的节点空间.时间复杂度上(按比较次数)为1+2+...+n-1 = n(n-1)/2,
			为O(n*n),复杂度还是太大.比较排序上可以优化.

	解决办法3 : 指针的数组表示int *C[n],将申明n个大小的数组,数组中的元素是指针,初始化指向A[i]对应的地址,也就是建立A[i]元素的索引,
				对索引进行排序(自底向上排序,基数排序等等),最坏情况下的比较次数为nlogn次,然后在遍历一遍,对相同的值统计,输出结果.
	评估3 : 对索引(C[n])进行交换操作,可以节省大量的实体赋值操作,节省大量的内存资源.(但是这是对于结构大的数据而言效果好,对于int的根本没必要)

	解决办法4 : 直接对数组A进行排序,最坏比较次数为nlogn次,再遍历一遍A,统计相同的数值的数量,输出结果
	评估4 : 统计相同数值的数量,会统计到其他无用的计算,浪费资源.可以直接根据多数元素的定义,直接统计A[n/2]的值的数量

	解决办法5 : 在办法4上进行改进,直接统计A[n/2]的值的数量,两端用二分法快速找出起始位置和终点位置,相减就是数量,跟n/2比较,输出结果
	评估5 : 时间复杂度nlogn+logn,空间复杂度为n

	解决办法6 : 不进行排序,直接找出中间元素mid,然后遍历找出mid的数量
	评估6 : 时间复杂度为20n+n,更少.

	解决办法7 : 

 */
#include <iostream>
using namespace std;
template<class T>
int Size(T &array)
{
	return sizeof(array)/sizeof(array[0]);
}


//方法1,遍历数组A,找出多数元素
typedef struct Node
{
	int value;
	int count;
	Node * next;
	Node(int num):value(num),count(1),next(NULL){};
	Node():value(-1),count(-1),next(0){};
}* headnode,* lnode;

class List
{
	headnode head;
	int n;
public:
	List():n(0){head = new Node();};
	~List(){deletelist(head);};
	bool find(int num);		
	void addNode(int num);
	void increment(int num);
	int  major_return();
	void deletelist(Node *p);
};

void List::deletelist(Node *p)
{
	while (p->next)
	{
		Node *temp = p->next;
		p->next = temp->next;
		delete temp;
	}
	delete p;

}

bool List::find(int num)
{
	n++;
	lnode pre;
	pre = head;
	while(pre != NULL && pre->value != num) {
	    pre = pre->next;
	}
	if (pre == NULL)
	{
		return false;
	}
	return true;
}

void List::addNode(int num)
{
	lnode pre = head;
	lnode newnode = new Node(num);
	while(pre->next != NULL ) {
	    pre = pre->next;
	}
	pre ->next = newnode;
}

void List::increment(int num)
{
	lnode pre;
	pre = head;
	while(pre->value != num) {
	    pre = pre->next;
	}
	pre ->count ++;
}

int  List::major_return()
{
	lnode pre;
	pre = head;
	int temp = n/2;
	while(pre != NULL) {
		if (pre -> count >= temp)
		{
			return pre ->value;
		}
	    pre = pre->next;
	}
	return -1;
}

int Majority_first(int *array,int n)
{
	List headlist;
	int temp = 0;
	for (int i = 0; i < n; ++i)
	{
		temp = array[i];
		if (headlist.find(temp))
		{
			headlist.increment(temp);
		}
		else
		{
			headlist.addNode(temp);
		}
	}
	return headlist.major_return();
}

//方法2,删除数组中任意两个不同的元素,原数组的多数元素仍是新数组的多数元素
/*
	分析 : 每次递归调用,是先查找原数组中任意不相同的两个数值
		(直接与当前数组最后一位进行比较,不同,则将不同的数值与倒数第二位对调,这里不用索引,因为索引指向的类型结构小,不适合)
		递归调用函数的形参表应是数组a,数量n.放回int.递归结束标志是1.比较中没有不相同的数 2.只有一个元素(这种情况包含在1中) (默认有多数元素>n/2的情况下)
		这种情况得出的结果是候选值,还需要遍历数组,找出数量.
	看书分析 : 方法2是每次删除两个不同元素.可以进行改进.
*/
int candidate(int *array,int num)
{
	if (num == 0)return -1;
	if (num == 1)return array[0];
	int last = array[num-1];
	int i = num - 2;
	for (; i >= 0 ; i-- )
	{
		if (array[i] != last)break;
	}
	if ( i == -1)return array[0];
	last = array[num - 2];
	array[num - 2] = array [i];
	array[i] = last;
	return candidate(array,num-2);
}

//改进candidate,从头遍历,如果有一段为平衡数组(候选元素与其他元素数量相同),则从接下来再开始比较,节省递归调用的次数
int improve_candidate(int *array ,int num,int start)
{
	int j = start ;
	int temp = array[start] ;
	int count = 1;
	while (j < num && count > 0)
	{
		j++ ;
		if (array[j] == temp)
		{
			count++;
		}
		else
		{
			count--;
		}
	}
	if ( j == num)return temp;
	else return improve_candidate(array,num,j+1);

}


int Majority_second(int *array,int n)
{
	int can = improve_candidate(array,n,1);
	if (can == -1) return -1;
	int count = 0 ;
	for (int i = 0; i < n ; i++)
	{
		if (array[i] == can)
		{
			count ++;
		}
	}
	if (count > n/2)return can;
	return -1;
}

//测试
int main(int argc, char const *argv[])
{
	int a[]={1,2,3,4,5,6,7,8,9,1,1,1,1,1,1,1,1};
	int n=Size(a);
	int ret = Majority_second(a,n);
	if (ret == -1)
	{
		cout << "没有多数元素";
	}
	else
	{
		cout << "多数元素为: "<<ret<<endl;
	}
	system("pause");
	return 0;
}
