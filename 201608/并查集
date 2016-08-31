//UNION(x,y)是将x,y分属的集合合并成一个集合,集合名字为两个集合名称的其中一个(按秩合并)
//FIND(x)是寻找x所属的集合名称(路径压缩)
//其中的关键是要快速找到根节点(集合名称)
//使用条件:不需要考虑集合内部情况,只要快速知道集合名称(根节点),并以此判断
//具体用处:1.任意两个人是否有亲属关系;2.互不相通的集合数;3.网络连接判断;4.变量名等同性(类似于指针的概念)

//数据结构有两种
//1.数组表示法:下标j表示节点j,A[j]表示j的父节点,例如9的父节点是4,则有A[9]=4(数组型适用于连续元素)
//2.树表示法: 3个成员变量,rank表示该节点的秩,value表示该节点的值,father表示指向父节点的指针(普遍使用,如果是连续数据则数组表示法更好)



#include <iostream>
using namespace std;

#define N 50

//树表示法(至于数组表示法,则使用性不是很强,不写)
typedef struct NODE
{
	int rank;
	int value;
	NODE * father;
	NODE(int value):father(NULL){
		this->rank=0;
		this->value=value;
		//this->father =NULL;
	}
}Node;
void  union1(Node *a,Node *b);
Node*  find1(Node *a);
Node*  find2(Node *a);

void  union1(Node *a,Node *b){
	//``a,b为两个集合,比较两者的rank,相等则a指向b同时b的rank+1,不等则低的指向高的``
	//有问题,这里的a,b的定义不是两个集合的根节点,而是两个集合的任意两个节点,因此要先找到a,b所属的根节点,在进行合并操作
	//a,b所属的根节点
	Node *pa=find2(a);
	Node *pb=find2(b);
	if (pa->rank <= pb->rank)
	{
		pa->father=pb;
		if (pa->rank == pb->rank)
		{
			pb->rank++;
		}
	}
	else 
	{
		pb->father=pa;
	}
}

Node*  find1(Node *a){//返回a节点所属的根节点(同时压缩路径)
	Node *root=a;
	while(root->father!=NULL) {//寻找根节点,直到father为NULL
	    root =root->father;
	}
	//跳出循环,此时root指向的就是根节点
	//压缩路径,理由是只有先找到根节点,才能压缩路径
	while(a!=root) {//a此时为移动指针,root此时为根节点指针,如果不相等,则将a指向root,同时a指针指向father
		Node *temp=a;
		a=a->father;
		temp->father=root;
	}//可以在优化,理由是a遍历的时候,最后一次是多余的,可以省去
	//不可行,最后一次不是多余,如果find的节点本身就是根节点,则会产生错误,如下的注释,因此不可优化
	return root;
}

Node*  find2(Node *a){
	//代码清晰易懂
	Node *y=a;
	while(y->father!=NULL) {
	    y=y->father;
	}
	Node *root=y;
	y=a;
	while(y->father!=NULL) {//未考虑到当y本身就是root时,y->father为NULL,应该为y!=root或者y->father!=NULL
	    Node *temp=y->father;
	    y->father=root;
	    y=temp;
	}
	return root;
}

int main(){
	//初始化数据
	
	Node* p1=new Node(1);
	Node* p2=new Node(2);
	Node* p3=new Node(3);
	Node* p4=new Node(4);
	Node* p5=new Node(5);
	Node* p6=new Node(6);
	Node* p7=new Node(7);
	union1(p1,p2);
	union1(p2,p3);
	union1(p4,p5);
	union1(p1,p4);
	Node *root=find2(p1);

	system("pause");
	return 0;

}
