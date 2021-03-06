/**
 * -*- coding : GBK -*-
 * @Author : huangshengjianng
 * @Email : 1005542693@qq.com
 * @Date : 2016-08-31 13:27
 * @Last Modified Date : 2016-08-31 14:21
 * @FileName : 多项式求值.cpp
 */

/*需求分析 : 
	输入 : n+1个实数a0,a1,...,an,和x的序列
	输出 : an*x^n +an-1 *x^(n-1) + ...+a0的值
	想法 : (anx+an-1)x...  按这种方式直到 ...x+a0 最后得到值
	结果 : 想法成立,可行.
	引申问题 : 如何自动设置a0,a1,...,an(不是手动设置)?
		输入 : 公式
		输出 : 对应指数的系数构成的数组a,数组长度=最高指数+1;
		想法 : 将数组看成字符串遍历,先整合相同指数的系数,求出最高指数Max,建立a(Max+1)={0}(+1原因是a0*x^0=a0);
			   再将指数i对应的系数bi赋值给a[Max-i].
		结果 : 暂时不了解数字公式在程序中如何表示,无法下手.
		结论 : 没有实现.
 */
#include <iostream>
#include <vector>
using namespace std;

//辅助工具
template < class T >
int GetLen(T & a){
	return (sizeof(a)/sizeof(a[0]));
}

//Horner函数
void Horner(const int *a,const int n,const int x,int &result){//a数组(按an...a0的顺序),n数组长度,x变量,result存储结果
	result=a[0];
	for (int i = 0; i < n-1; ++i)
	{
		result=x*result+a[i+1];//注意点 : 最后的运算时...*x + a[n-1],则此时i为n-2.
	}
}

//测试
int main(int argc, char const *argv[])
{
	int a[]={1,2,1};//x^2 +2*x+1
	int n=GetLen(a);
	int result=0;

	Horner(a,n,1,result);//result=4
	cout<<result<<endl;
	Horner(a,n,2,result);//result=9
	cout<<result<<endl;
	Horner(a,n,3,result);//result=16
	cout<<result<<endl;
	Horner(a,n,4,result);//result=25
	cout<<result<<endl;
	Horner(a,n,5,result);//result=36
	cout<<result<<endl;
	system("pause");
	return 0;

}
