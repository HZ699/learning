/**
 * -*- coding : GBK -*-
 * @Author : huangshengjianng
 * @Email : 1005542693@qq.com
 * @Date : 2016-08-30 15:56
 * @Last Modified Date : 2016-08-30 19:29
 * @FileName : 整数幂.cpp
 */

/*需求分析 : 
	输入 : 整数x和非负数n
	输出 : 计算x^n的值
	想法1 : 递归计算,将x^n化为x^(n/2)*x^(n/2),在对x^(n/2)再次递归,直到n/k=0(此时x^0=1)为止
	分析 : 要考虑到n是奇数还是偶数,若为偶数,则x^(n/2)*x^(n/2),否则再乘以x
	想法2 : 将n化为二进制计算
	分析 : 从左向右遍历,如果当前二进制数字为0,则对y平方,为1,则对y平方再乘上x.(二进制思想牢记)
 */

#include <iostream>
#include <vector>
using namespace std;


int power(int x,int n){//x表示底数,n表示幂值,返回的是x^n的值
	if (n==0)return 1;//递归基础
	int y=power(x,n/2);//按递归求出x^(n/2)
	y=y*y;
	if (n%2==1)y=x*y;
	return y;
}

//由于n要转换为二进制数字,而计算机表示的最小访问单位为1个字节(8bit),不可再进一步访问bit位.
//需要求解n转换为二进制的大小k和binary[k]
#define BRYSIZE  16
void T2B(int n,int &k,int* binary){//binary数组存放着n的二进制,k是二进制的个数.
	//例如n=5=101B,k=3,则binary[2][1][0]分别为101
	while(n) {
	    binary[k++] = n&0x01;
	    n=n>>1;
	}
}


int exp(int x,int n){//x表示底数,n表示幂值(需要转换为二进制),返回的是x^n的值
	int y=1;
	int k=0;
	int binary[BRYSIZE];
	T2B(n,k,binary);
	for (int i = k-1; i >=0 ; --i)//n=5=1* 2^2 +0* 2^1 +1* 2^0=1+2*(0+2*1)
		//x^5=x^1 * x^(2*(0+2*1))
		//x^(2*(0+2*1))=x^(0+2*1) * x^(0+2*1)
		//x^(0+2*1)=x^0 * x^(2*1)
		//x^(2*1) = x^1 * x^1
	{
		y=y*y;
		if (binary[i]==1)y=x*y;
	}
	return y;
}
//总体而言 : 第一种方法比第二种方法好.

int main(int argc, char const *argv[])
{
	int x=2;
	int n=8;
	cout<<exp(x,n)<<endl;
	cout<<exp(2,3)<<endl;
	cout<<exp(2,4)<<endl;
	cout<<exp(2,5)<<endl;
	cout<<exp(2,6)<<endl;
	cout<<exp(2,7)<<endl;
	cout<<exp(2,8)<<endl;
	system("pause");
	return 0;

}
