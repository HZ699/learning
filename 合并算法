合并算法
#include <iostream>
#include <vector>
//#include <array>
using namespace std;

//要求:合并两个有序的元素(一般升序),结果也是升序
//输入:两组有序的元素
//输出:一组有序的元素
//想法

//新建数组:
//先申请一个空间大小为a.length+b.length的数组
//3个指针分别指向3个数组,其中一个指向新数组的特点是每次自增一,另外两个每次有且只有一个增一.

//由于C++数组没有直接获得数组长度的函数,因此使用sizeof(array)/sizeof(array[0]),可以用模板定义
template <class T>
int GetArrayLen(T& array){
	return (sizeof(array)/sizeof(array[0]));
}

vector<int> merge(int *a,int *b,int alength,int blength){//约束条件是索引值必须小于数组长度
	vector<int> c(alength+blength);
	int i=0,j=0,count=0;
	while(i < alength && j < blength) {//使用while能很好解决问题
	    if (a[i] < b[j]) c[count++] = a[i++];
	    else c[count++] = b[j++];
	}
	while (j < blength)//表示a组已经索引完
	{
		c[count++]=b[j++];
	}
	while (i < alength)//表示b组已经索引完
	{
		c[count++] = a[i++];
	}

	return c;
}

int main(int argc, char const *argv[])
{
	int a[]={1,3,5,7,9,10,23,45};
	int b[]={2,4,6,8,11};
	int alength=GetArrayLen(a),blength=GetArrayLen(b);
	cout<<alength<<endl;
	cout<<blength<<endl;
	vector<int> c=merge(a,b,alength,blength);
	int clenth=alength+blength;
	//int clenth=GetArrayLen(c);成int整数位为4
	for (int i = 0; i < clenth; ++i)
	{
		cout<<c[i]<<endl;
	}
	system("pause");
	return 0;
}
