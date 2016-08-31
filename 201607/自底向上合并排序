自底向上合并排序
#include <iostream>
#include <vector>
using namespace std;


//目标是将一组无序的数组按有序输出(有多种方法,如选择排序,插入排序等等,另外需要讨论它们的效率,适用场合,空间时间复杂度等等)
//自底向上合并排序
//想法是根据现有的合并算法,先两两合并,在四四合并,一直往上,直到原数组大小为止
//原数组长度length,先两个为一组,则有length/2组,4个为一组,会有length/4组,8个为一组,会有length/8组
//有可能剩余数不够一组,但单做一组算,直到为0组,结束排序
//预处理
template<class T>
int GetArrayLength(T &Array){
	return sizeof(Array)/sizeof(Array[0]);
}
//合并排序
void Merge(int a[],int p,int q,int r){//p,q分别表示第一个有序数组左右数在原数组中的坐标(从1算起)
	//r表示第二个有序数组最右数在原数组中的坐标(从1算起)
	//则实际a[p-1...q-1]表示其中一个子数组,a[q...r-1]表示另一个子数组
	//需要合并成有序的a[p..r],p,q,r分别表示第p,q,r个数,从1算起,因此对应的数的坐标要相应减一
	vector<int> b(r-p+1);//需要申请一个辅助数组,因为直接在原数组上操作会有移位产生数据覆盖
	int s=p-1,t=q,k=0;//s,t分别是指向两个子数组的指针,k为指向辅助数组的指针
	while(s < q && t < r) {//s的范围是p-1到q-1,t的范围是q到r-1
	    if (a[s] < a[t])b[k++]=a[s++];
	    else b[k++]=a[t++];
	}
	while(s < q) {
	    b[k++]=a[s++];
	}
	while(t < r) {
	    b[k++]=a[t++];
	}
	for (int i = 0; i < r-p+1; ++i)
	{
		a[p-1+i]=b[i];
	}
}

void BottomupSort1(int a[],int length){
	int b=1;//作为2的倍数除
	int num=length;
	while(num) {//num表示将a数组划分成功的组数,0组结束
		int s_num=num/2;//s_num表示能够合并的个数
	    for (int i = 0; i < s_num*2; )
	    {
	    	Merge(a,i*b+1,(i+1)*b,(i+2)*b);//关键是根据b取值(1,2,4,8...)划分成num组(下面考虑有余数的情况)
	    	//第0,1组合并,2,3组合并,4,5组合并,则i要自增2,有问题,会产生单组情况(已解决)
	    	//合并两组的坐标要确定,首先是第i组和第i+1组合并,p=i*b+1,q=(i+1)*b,r=(i+2)*b,不加一表示前一数组的最后一位下标(从1算起)
	    	i+=2;
	    }
	    //处理剩余组,要讨论是否还有个(单组和不足组),则合并,如果没有或者有不足组,则不操作
	    if ((s_num*2+2)*b > length && (s_num*2+1)*b < length)//p=s_num*2*b+1,q=(s_num*2+1)*b,r=length
	    {
	    	Merge(a,s_num*2*b+1,(s_num*2+1)*b,length);
	    }
	    b=b<<1;
	    num=num>>1;
	}
}
//总结思路
//虽然效果完美,但是代码有点难看,繁杂,不适合别人观看,有待改进,仍需努力.
//改进
void BottomupSort2(int a[],int length){
	int t=1;
	while(t < length) {
		int s=t,i=0;
		t=2*s;
		while(i + t <=length) {
		    Merge(a,i+1,i+s,i+t);
		    i=i+t;
		}
		if (i +s<length)
		{
			Merge(a,i+1,i+s,length);
		}
	}
}

int main(int argc, char const *argv[])
{
	int a[]={1,5,3,2,7,4,6,8,3};
	int length=GetArrayLength(a);
	BottomupSort2(a,length);
	for (int i = 0; i < length; ++i)
	{
		cout<<a[i]<<endl;
	}

	cout<<length<<endl;
	system("pause");
	return 0;
}
