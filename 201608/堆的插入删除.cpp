#include <iostream>
using namespace std;

//实现将元素x插入现有堆a[]
//将元素x暂时放在a[length]位置,然后调用siftup,完成排序.关键问题在于数组a大小的变化是否需要重新建立数组b,还是用其他方法.

//从现有堆a[]删除第i个元素
//相当于将第i个元素值置为-1,调用siftdown,到最底层,然后删除.是这样吗?不是,会出现底层左边空出一个元素,不行,该方法舍弃
//重新思考,由于最终要将第i个元素放置在第n个位置上删除,所以可以将a[n-1]与a[i-1]交换,然后跟上下节点比较,决定是否siftup还是siftdown


//从现有堆a[]删除最大元素并返回max
//同上,只是将删除第i个元素固定为删除第1个元素,然后返回第一个元素值


//预处理
template <class T>
int Getlength(T &array){
	return (sizeof(array)/sizeof(array[0]));
}

void Siftup1(int *a,int i){
	if (i==1)return ;
	int j=i/2;
	while(a[j-1] < a[i-1]&&i > 1) {
	    //交换
	    int temp=a[j-1];
	    a[j-1]=a[i-1];
	    a[i-1]=temp;
	    i=j;
	    j=i/2;
	}
}
void Siftdown1(int *a,int length,int i){
	if (2*i > length)return;
	bool done=false;
	int j=2*i;
	do{
		if (j+1<=length && a[j-1]<a[j])j++;
		if (a[j-1] > a[i-1])
		{
			int temp=a[j-1];
	    	a[j-1]=a[i-1];
	    	a[i-1]=temp;
	    	i=j;
	    	j=2*i;
		}else done=true;
	}while(j <= length && !done);
}

//堆的插入
void insert(int *a ,int length,int x){//a表示数组首字母的指针,length表示数组的长度,x表示要插入的元素
	*(a+length)=x;//不安全,改写后面的数字,可能会导致程序错误
	Siftup1(a,length+1);
}

//删除堆的第i个元素
void delete1(int *a,int length,int i){//a表示数组首字母的指针,length表示数组的长度,i表示要删除的元素位置
	if (i==length)return ;//如果要删除的元素就是a[n-1],则直接删除,不用操作
	//交换元素a[i-1]和a[n-1],由于最后一位不需要,所以可以直接赋值给a[i-1]
	a[i-1]=a[length-1];
	//与上下节点比较,可以直接与上节点比较,若大于父节点,则siftup,否则siftdown.
	//等于情况下,即没有移动位置,也可以用siftup,siftdown,因为两函数都包含等于情况的处理
	if (i==1||a[i-1] <= a[i/2-1])Siftdown1(a,length,i);
	else Siftup1(a,i);
	/*if (a[i-1] >= a[i/2-1])Siftup1(a,i);//a[i/2-1]表示父节点,出现问题,在于未判断是否存在父子节点
	else Siftdown1(a,length,i);*/

}

//删除堆的最大值
int deletemax(int *a,int length){//a表示数组首字母的指针,length表示数组的长度,返回的值是max
	int max=a[0];
	delete1(a,length,1);
	return max;
}



/*int main(int argc, char const *argv[])
{
	int a[]={20,13,18,10,11,17,16,3,7,5,6,16};
	int *p=a;
	int length=Getlength(a);
	delete1(a,length,4);
	//cout<<max<<endl;
	for (int i = 0; i < length-1; ++i)
	{
		cout<<p[i]<<" ";
	}
	system("pause");
	return 0;
}
*/
