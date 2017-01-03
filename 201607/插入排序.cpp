插入排序
#include <iostream>
#include <vector>
using namespace std;

//目标是将一组无序的数组按有序输出(有多种方法,如选择排序,插入排序等等,另外需要讨论它们的效率,适用场合,空间时间复杂度等等)
//插入排序
//每一次默认在i之前的数字为有序的,将第i个数放入合适的位置,成为i个有序的数组,持续到最后,i从2到length(第一个默认有序,不用比较)
//(重点是思考过程,记录下来)想法:1.先申请一个大小为length的空数组,将第1个数放入第1个,之后依次从原数组取一个数与新数组比较(从头比到尾)
//找到合适位置k,将后位数依次后移(从后到前),空出坐标k,放置该数.
//想法2.(改进1),不用申请新数组,可以在原数组上操作,默认第1个为有序,依次从数组中取出一个数与前面有序的数组比较,从后向前比较,比较不成功则进行移位
//成功则放入当前空出来的位置,需要两个指针,一个为需要插入的数坐标(自增一),i范围是1到length,另一个指向有序数组从后向前对比的坐标(自减一),j范围是i-1到0
//预处理
template<class T>
int GetArrayLength(T &Array){
	return sizeof(Array)/sizeof(Array[0]);
}

//设函数
void InsertionSort1(int a[],int length){//输入无序数组,及它的长度(因为int数组没有直接调用出长度)
	for (int i = 1; i < length; ++i)//i表示需要插入数组的数的坐标,要将该数放在temp中,因为后续会产生移位
	{
		int temp=a[i];
		for (int j = i-1; j >= 0; j--)//j表示比较当前数字的坐标,同时要插入的坐标是j+1
		{
			if (a[j] > temp)//待会再讨论等号情况
			{
				a[j+1]=a[j];
			}
			else {
				a[j+1]=temp;//需要跳出该层循环
				break;//还是有隐患,可以改进
			}
		}   
		
	}
}

void InsertionSort2(int a[],int length){//输入无序数组,及它的长度(因为int数组没有直接调用出长度)
	for (int i = 1; i < length; ++i)//i表示需要插入数组的数的坐标,要将该数放在temp中,因为后续会产生移位
	{
		int temp=a[i];
		//改进为
		int j=i-1;
		while(j >=0 &&(a[j] > temp)) {
		    a[j+1]=a[j];
		    j--;
		}
		a[j+1]=temp;
	}
}

int main(int argc, char const *argv[])
{
	int a[]={1,4,3,5,7,5,5,3,45,67,34,18};
	int length=GetArrayLength(a);
	InsertionSort2(a,length);
	for (int i = 0; i < length; ++i)
	{
		cout<<a[i]<<endl;
	}

	cout<<length<<endl;
	system("pause");
	return 0;
}
