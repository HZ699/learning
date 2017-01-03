#include <iostream>
#include <array>
using namespace std;

//查找

/*实现二分搜索
输入一组有序的数组和一个需要查找的数值
输出该数值的位置,若没有,则返回-1*/
//由于C++数组没有直接获得数组长度的函数,因此使用sizeof(array)/sizeof(array[0]),可以用模板定义
template <class T>
int GetArrayLen(T& array){
	return (sizeof(array)/sizeof(array[0]));
}


//测试
int binary_search_1(int a[],int left,int right,int input);
int binary_search_2(int a[],int n,int input);

int main(int argc, char const *argv[])
{
	int a[]={1,2,3,4,5,6,7,8,9,10,11};
	int n=GetArrayLen(a);
	int result=binary_search_1(a,0,n,10);
	// cout<<sizeof(a)<<endl;
	// cout<<sizeof(a[0])<<endl;
	cout<<result<<endl;
	system("pause");
	return 0;
}


//1.递归调用
//想法
/*将原数组均分为两组,在对符合的组查找,继续划分查找,直到组为0,结束.
比如用[0,length-1],划分后为[0,length/2]和[length/2,length-1],在对其中一组查找,直到组为0.*/
int binary_search_1(int a[],int left,int right,int input){	//注意点a[]一直是原数组,不是划分后的半数组:好处是不用每次都重构半数组,返回的下标不用复杂转换.
										//left表示当前数组的左坐标
										//right表示当前数组的右坐标
										//input表示需要查找的数值
	if (left>=right)return -1;//递归基础
	//递归主体
	int mid=(left+right)/2;
	if (a[mid]==input)return mid;//mid是下标,从0算起
	if (a[mid]<input)return binary_search_1(a,mid+1,right,input);
	return binary_search_1(a,left,mid-1,input);

}
//如果不需要这个left和right呢,非递归方式

//2.非递归调用
//想法
//循环体是找到二分点,比较数值,等于则返回坐标,大于则在上半部查找,小于则在下半部查找

int binary_search_2(int a[],int n,int input){
	int left=0;
	int right=n;
	//int right=GetArrayLen(a);//有问题,调用函数时数组a为空,则结果为1,不能在该函数中调用
	int mid=(left+right)/2;
	while(a[mid]!=input) {
	    if (a[mid]>input)right=mid-1;
	    else left=mid+1;
	    if (left>=right)return -1;
	    mid=(left+right)/2;
	}
	return mid;
}
