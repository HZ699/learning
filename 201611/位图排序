/**
 * -*- coding : GBK -*-
 * @Author : huangshengjiang
 * @Email : 1005542693@qq.com
 * @Date : 2016-10-28 14:21
 * @Last Modified Date : 2016-11-02 16:33      
 * @FileName : 位图排序.cpp
 */

/*位图排序
	基本概念 : 按照计算机存储数据的特性(二进制),用一系列的二进制串表示数据,如果第i位的值为1,则表示存在数据i.为0则表示不存在这个数值.
				例如 0100 0010 0000 0001 从左向右(低位到高位) ,表示数据{1,6,15}.
				特性出发,二进制串的每个值只有0或1两种状态,表示相反的状态(可以为有无,正面反面),该值的位置表示其位置信息(一维位置信息)
	应用场景 :  稠密数据(数据之间没有关联)的极简表示.(稀疏的就没有必要).在内存空间不足的情况下,可以用位图表示大量稠密的数据
	局限性 : 只能表示没有关联的稠密数据.
	具体需求 : 用极小的空间进行排序.
		输入 : 一个最多包含n个正整数的文件,每个数都小于n,其中n=10的7次方,没有重复出现的数字.
		输出 : 按升序排列输出列表.(用位图排序)

	分析 : c++等语言没有直接对位Bit操作,最小的操作数是字符char.因此对位的操作只能通过&或|某个数来间接操作位字符.
		   想.总体思路是对数据文件遍历,将每个数据所对应的位置置1,然后从低往高遍历,遇到1的则输出位置信息.
		   很明显,最耗费时间的是依据数据快速到对应的位置.根据位置快速计算出其数据.
		   这里有几个问题,如何对位操作(set,read)?如何快速找出位置信息.
	解决方案 : 需要设置一个类,私有成员时1MB的内存空间,有成员函数set(int location),作用是将对应位置的0置为1.
			   以及read(),输出已经排好序的数组信息.

 */
#include <iostream>
using namespace std;
char data_type[8] = {(char)0x01,(char)0x02,(char)0x04,(char)0x08,(char)0x10,(char)0x20,(char)0x40,(char)0x80};
//函数
#define  N  1024*993 //这里有个问题,如果N为1024*1009就会因为后面的变量声明而导致堆栈溢出,
					//因此要为程序后续的声明变量提供足够的堆空间,N值应为1024*993
class Bit
{
	char data[N];  //1MB~1024*1024*8bit = 8388608bit   char是8位,则需要1024*1024个char表示1MB内存
				   //但是只能最多申请1024*1009*8bit = 8265728bit字节,也可满足条件.最多表示在[0~8265728)内的8265728个数字.
public:
	Bit()
	{memset(data,0,sizeof(data));};
	~Bit(){};
	void set(int location); //int是4个字节,总共有32bit,最大可表示2^32-1的值,远远大于8265728值,完全满足需求.实际上用3个字节表示最省空间.
	void read();
};

void Bit::set(int location)//先将location转换为对应的第i块字节第j为.i是字节号[0~N-1],j是字节内的位号[0~7].
{						   //location/8是商,location%8是余数.一般情况下,i就是商,j就是余数-1.
						   //特殊的是刚好整除即余数为0的情况,此时i是商-1,j是7.
	int  i ;
	char j ;
	i = location/8 ;
	j = location%8 ;
	if (j == 0){ i--; j = 7; }
	else{ j--; }
	//确定对应的字节号i,和字节内位号j
	data[i] = data[i]|data_type[j];//|的作用是将1对应位 置1,0对应位 保留.
	/*switch(j)//用数组的方法更好
	{
		case 0:
			data[i] = data[i]|0x01; //字节内最后一位置为1,其余位保留
			break;
		case 1:
			data[i] = data[i]|0x02;//第二位
			break;
		case 2:
			data[i] = data[i]|0x04;//第三位
			break;
		case 3:
			data[i] = data[i]|0x08;//第四位
			break;
		case 4:
			data[i] = data[i]|0x10;//第五位
			break;
		case 5:
			data[i] = data[i]|0x20;//第六位
			break;
		case 6:
			data[i] = data[i]|0x40;//第七位
			break;
		case 7:
			data[i] = data[i]|0x80;//第八位
			break;
	}*/
}
void Bit::read()//有公式i*8+j+1=location;其中i和j分别是data的字节号[0~N-1],字节内位号[0~7].
{				//data[i]如何得知0~7位上哪一位置为1,有没有可能一次性求得所有j值.
	int location ;
	int n= N;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			char temp=data[i]&data_type[j];
			if(temp == data_type[j])//&的作用是将只保留1对应的位置保留,其余位去除.
			{
 				location = i * 8 + j+1;
				cout<<location<<endl;
			}
		}
	}
}

//测试
int main(int argc, char const *argv[])
{
	Bit temp;
	int a[6] ={32,34,45,23,44,24};
	for (int i = 0; i < 6; ++i)
	{
		temp.set(a[i]);
	}
	temp.read();
	
	system("pause");
	return 0;
}
