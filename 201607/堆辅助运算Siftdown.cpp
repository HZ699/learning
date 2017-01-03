//Siftdown是在2i或2i+1<n的情况下有H[i]<H[2i]或者H[i]<H[2i+1]时,需要将父节点下移
//分析首先要满足2i或2i+1存在,即存在左/右节点,因此要满足2i<n或2i+1<n,
//其次,i范围在1~n/2(从1开始),取i,2i,4i,8i..直到i*2^(k+1)>n,k表示至多需要比较的次数
//子节点存在有2种情况,一是存在左节点,二是存在左和右节点,需要进行判断,一般来说除最后一层,都是有左右节点
//一是左节点的情况下,只要比较,如果小于左节点,则交换,否则停止
//二是左右节点的情况下,又分为3种情况,1是小于左节点,2是小于右节点,3是都小于.
//    情况1/2和上面的情况一相同,同样操作
//    关键是情况3,需要左右字节相互比较,取较大者交换


#include <iostream>
using namespace std;

//预处理
template <class T>
int Getlength(T &a){
	return (sizeof(a)/sizeof(a[0]));
}


void Siftdown(int a[],int length ,int i){//a数组表示对应的堆,堆得第i个节点在a数组中的位置是i-1

	if (2*i > length)return;//表示没有左节点,更不可能有右节点
	int j=2*i;//表示左节点的位置
	while(j+1 <= length ){//表示左右节点存在
		/*if ((a[i-1]<a[2*i-1]&&a[i-1]>a[2*i])||((a[i-1]>a[2*i-1]&&a[i-1]<a[2*i])))//表示二种情况,一是左节点小,二是右节点小
		{
			int temp=a[j-1];
	    	a[j-1]=a[i-1];
	    	a[i-1]=temp;
		}*///表示太繁杂,舍弃
	    if (a[i-1]<a[j-1]&&a[i-1]>=a[j])//仅小于左节点,等号要加进去,否则会漏掉左节点等于父节点,右节点大于父节点的情况
	    {
	    	int temp=a[j-1];
	    	a[j-1]=a[i-1];
	    	a[i-1]=temp;
	    	i=j;
	    	j=2*i;
	    }
	    else if (a[i-1]>=a[j-1]&&a[i-1]<a[j])//仅小于右节点
	    {
	    	int temp=a[j];
	    	a[j]=a[i-1];
	    	a[i-1]=temp;
	    	i=j+1;//加1的理由是右节点与父节点交换,那么i应该重新指向右节点的位置,而不是左节点的位置
	    	j=2*i;
	    }
	    else if (a[i-1]<a[j-1]&&a[i-1]<a[j])//都小于左右节点
	    {
	    	if (a[j-1]<a[j])
	    	{
	    		int temp=a[j];
	    		a[j]=a[i-1];
	    		a[i-1]=temp;
	    		i=j+1;
	    		j=2*i;
	    	}
	    	else{
	    		int temp=a[j-1];
	    		a[j-1]=a[i-1];
	    		a[i-1]=temp;
	    		i=j;
	    		j=2*i;
	    	}
	    }else {
	    	return;
	    }
	}
	if (j==length&&a[i-1]<a[j-1])//表示左节点存在并且小于左节点,交换
	{
		int temp=a[j-1];
	    a[j-1]=a[i-1];
	    a[i-1]=temp;
	}
}


//改进方法
void Siftdown2(int a[],int length,int i){//由于除最后一次比较外,其他次比较都与左右节点比较
	//因此只要在左右节点先比较,找到最大值,再跟父节点比较
	if (2*i > length)return;
	bool done=false;
	int j=2*i;
	do{
		if (j+1<=length && a[j-1]<a[j])j++;//表示存在左右节点,并且右节点大于左节点,j指向左右节点中最大的节点位置
		if (a[j-1] > a[i-1])//父节点比子节点小,交换,否则跳出
		{
			int temp=a[j-1];
	    	a[j-1]=a[i-1];
	    	a[i-1]=temp;
	    	i=j;
	    	j=2*i;
		}else done=true;
	}while(j <= length && !done);
}

int main(int argc, char const *argv[])
{
	int a[]={20,3,9,12,11,4,5,3,7,5};
	int length=Getlength(a);
	Siftdown2(a,length,2);
	for (int i = 0; i < length; ++i)
	{
		cout<<a[i]<<" ";
	}



	system("pause");
	return 0;
}
