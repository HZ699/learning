/**
 * -*- coding : GBK -*-
 * @Author : huangshengjiang
 * @Email : 1005542693@qq.com
 * @Date : 2016-10-28 14:00
 * @Last Modified Date : 2016-12-22 15:11
 * @FileName : 三个水桶等分8升水.cpp
 */

/*三个水桶等分8升水

	应用场景 : 有3个容器,分别是3升/5升/8升的水桶(没有刻度),其中容器8升的水桶装满水,3升和5升的水桶空的.要求将8升的水等分成两份,每份是4升水
			   约束条件是只能用这3个容器,不能借用其他辅助容器. 要求列出所有等分成功的过程.

	具体需求 : 仅使用3/5/8升的容器,将开始装满8升的水等分成两份,每份是4升水.要求列出所有等分成功的过程
		输入 : 3个容器的容量和开始水量.对应输入为(3,5,8)和8
		输出 : 初始水量等分两份成功的所有过程. 

	分析 : 首先必须明确的是计算机实现的是模拟人脑中的思考过程.思考过程中用自然语言描述的每一步是由计算机实现的.因此在解决问题前,
		   应先描述好自然的解决方案,再由计算机实现或者简化升华.
		   从自然的角度来实现 : 
		   1.初始,3升容器0升水,5升容器0升水,8升容器8升水.(A,a)(B,b)(C,c),大写表示该容器的容量,小写表示容器此刻的水量.(capacity,size)
		   需输入n个容器的初始容量和水量.输入形式暂时简单化.在内部要构成形式 id(capacity,size) ; 
		   可以用
		   struct container{
				int capacity ; 
				int size ; 
		   	}
		   	vector<container>  con; 每次输入则push_back(new container) ; 
		   	prinf("请输入桶的数量 n ");
			scanf("%d",&n);
			vector<container>  con(n);
			for (int i = 0; i < 输入的桶数量n; ++i)
			{
				prinf("请输入%d号桶的容量",i+1);
				scanf("%d",&con[i].capacity);
				prinf("请输入%d号桶的当前水量",i+1);
				scanf("%d",&con[i].size);
			}


		   	添加结束后,在创建一个Init表示初始化的状态.con为变化的状态.

		   2.由于有3个容器,因此每次有6种倒水动作,分别是3->5,3->8,5->8,5->3,8->3,8->5.很明显由于3/5升的容器水为空.则只有8->3或8->5的倒水动作
		   需要两个函数,一是求倒水动作的种类(包括src->des的信息).特点是该函数只需执行一次,存入相应的动作表中.
			struct action{
				int src;
				int des;
			}
		    vector<action>  act.这样输出的结果就只需要初始状态和动作列表.
			for (i遍历con.size())
			{
				action 对象.src = i ; 
				for (j遍历con.size()且j!=i)
				{
					action 对象.des = j ; 
					act.push_back(对象) ; 
				}
				
			}

		    其中动作列表应该用一个栈(或vector)表示(只要尾部可添加删除).用深度遍历.可用stack<int> 或vector<int> actlist.
			遍历每个动作action.判断动作的合理性,合理则压入,计算压入后的状态,判断是否等分成功,如果成功,则输出当前动作列表,然后弹出此动作,
			返回上一层继续遍历.如果失败,则进入到下一层的调用.
			遍历动作结束后,弹出动作.
		    开始时需要压入一个0,压入,弹出成对. 
		    状态的变化也用一个栈表示,可用stack<vector<container>> 或vector<vector<container>> statuslist.(耗空间)
		    ---还可以用一个状态表示,弹出动作的时候进行状态反运算.(耗计算时间).第二种方法不可行,根本计算不了.例如3升有1升水,5升有2升水,---
		    ---5->3,则此时3升有3升水.反向处理时3->5,此时状态变成5升水有3升水.跟原状态不符,舍弃---
		    
		    也就是所,状态的变化和退回都需要用栈的形式存储.是不是太耗费空间了?
		    对的,可以在actlist中在添加一个变量值,表示从源桶倒入目的桶的水量.这样就可以实现反向运算.
		    struct actinfo{
				int acttype ;
				int water ;
		    }
			vector<actinfo> actlist;

			大致如下 : 
			vector<action>  act;
			vector<actinfo> actlist;初始化(压入一个0)
			vector<container>  Init;还有status  初始状态
			int count = 0 ; 

			void  start(&状态)
			{
				for (i遍历act中的每个动作)
				{
					if(动作合理性和是否状态重复)  插入这里
					{
						处理过程(动作,&水量,&状态);
						actlist.push_back(动作i,水量);
						if (等分成功)
						{
							show actlist,Init(同时记录个数count,以便后面出现0的情况出现提示);
							反向处理过程(&状态);(actlist.pop_back(动作,水量);处理)
						}
						else
						{
							start(&状态);
						}
					}	
				}
				反向处理过程(&状态);(actlist.pop_back(动作,水量);处理)
			}
			

		   二是判断该动作的合理性.只需判断倒入(主动)是否为空,待倒入(被动)是否为满.bool  ???(actcode) ; 
		   判断条件具体为return  src.size != 0 && des.size != des.capacity ; 

		   3.两种情况,1是8->3,由于8>3,则此时3升容器满,8升容器5升水,即(3,3)(5,0)(8,5).2是8->5,此时为(3,0)(5,5)(8,3)
		   --此时处理过程(函数) : 先判断待倒入(被动)的尚需x升水装满,倒入(主动)的容器有y升水,计算y-x的值--
		   --如果>=0,则待倒入的容器装满,剩下y-x的正值继续保留在倒入的容器中 ; <0 ,则倒入容器为空,待倒入的容器尚缺x-y的正值--
		   需要两个函数
		   一是处理过程简化后为 : 先将两桶的水量相加(a+c)与待倒入的容量A.计算a+c-A 的值.
		   若 >=0 ,则A容器为满(A,a=A),C容器有a+c-A的值,水量 = A-a; < 0,则A容器为a+c,C容器为空,水量 = c.
		   二是判断是否等分成功.遍历所有容器,判断if(size != 总/2 ) { if(size!=0)  return false;}  最外围return true;

	结论 : 需要3个vector类型的变量,分别是
		   vector<action>  act;(存放所有动作类型)
		   vector<actinfo> actlist;初始化(压入一个0)(存放当前所有动作序列)
		   vector<container>  Init;还有status  初始状态(存放初始状态和当前状态)
		   需要8个函数.
		   InitCon();初始化Init和status 
		   InitAct();初始化act
		   Start();关键程序,开启执行
		   isvalid();动作是否合法
		   Handleact();执行动作
		   isOK();等分是否成功
		   Show();展示结果.
			   printf 初始状态.
			   for(i遍历当前actlist)
			   {
					Handleact(动作,&水量,&状态);
					printf 动作,水量,状态.
			   }
			   printf 遍历结束.
			   count++ ; 
		   ReHandle(&状态);反向执行操作
			   tmp = actlist.pop_back();
			   tmp.动作  tmp.水量  状态 ; 
			   查询(tmp.动作)找出src和des.将状态中对应于src的+水量,des+水量.返回.

	出现问题 : 当8->3倒入3升水后,3->5倒入3升水,5->3升又倒入3升水.形成(3,0)(5,3)(8,5)和(3,3)(5,0)(8,5)的循环.
			   造成循环的真正原因是在动作移动后,新的状态在之前的状态中重复出现.正如状态1->状态2->状态3,而此时
			   状态3的下一状态是2,形成一个循环.1->2->3->2->3...
			   循环形成的真正条件(原因)?如何打破循环?
			   原因是动作(src,des)和水量.在后续的复杂运算等效于之前的动作.即1->a2->b3->c2的动作总效果等价于1->a2的效果.
			   动作a,b,c的总效果和动作a相同.即b和c的动作总效果为0.广义上将,需计算在actlist是否存在某一段动作总效果为0的情况.
			   具体为src->des为正,des->src为负,总共有3对,分别是3->5,5->3;3->8,8->3;8->5,5->8;
			   则有3->5倒入3升水为+3,5->3倒入2升水为-2.相加和为+1.
			   方案一 : 需计算在actlist是否存在某一段动作总效果即3对数值为0的情况?
			   如果按照现有情况下,则每次添加一个动作,actlist就需从末尾循环向上累加.一旦出现为0的情况,就false,都不为0,返回true;
			   消耗大量的计算时间.(判断的结果对数 = 容器数量 = 状态的判断 ,而方案三不需要对属于哪一结果区分对待.)
			   方案二 : 利用一个栈存放容器经历的所有状态.每添加一个动作之前,先判断该动作产生的新状态是否在已有队列中.
			   消耗空间
			   方案三 : 用一个初始状态和actlist,重新计算经历的每一个状态.判断是否与该动作后的状态是否相同,有相同则返回false;都不同,返true;
			   选取方案三 . 那么在哪里插入合适呢?
			   CONTAIN  tmpInit初始状态,tmpcur当前状态
			   处理动作(动作,水量,&tmpcur);得到动作后的状态
			   for (i遍历actlist,除了第一个)
			   {
			   		处理动作(i.动作,水量,&tmpInit);得到下一个状态
			   		if(两状态是否相等)
			   		{
						return false ; 
			   		}                      
			   }
			   return true;


				两状态是否相等
				for(j遍历状态)
		   		{
					if(tmpInit[j].size !=  tmpcur[j].size)
					{
						return false;
					}
		   		} 
				return true;


 */
#include <iostream>
#include <vector>

using namespace std;
//函数

class  WaterHalf
{
public:
	struct container{
		int capacity ; 
		int size ; 
	};
	typedef  vector<container>  CONTAIN ;

	struct action{
		int src;
		int des;
	};
	typedef  vector<action>  ACTION ;

	struct actinfo{
		int acttype ; 
		int water ; 
    };
	typedef  vector<actinfo> ACTINFO ;

	void InitAll();
	void Loop();
	bool isvalid(int actcode);
	bool isStatusRep(int actcode); //判断是否会出现状态重复
	bool isequally2(CONTAIN &a,CONTAIN &b); //判断两种状态是否相等
	void Handleact(int actcode,int &water,CONTAIN &tmp );
	bool isOK();
	void ShowAll();
	void ShowContainer(CONTAIN &tmp) ; //显示当前的状态
	void ReHandle();
	void Start(); //启动程序

private:
	CONTAIN    	Init,cur ; //Init存储原始状态,cur存储当前状态.
	ACTION     	act ;	//动作种类
	ACTINFO    	actlist ; //存储当前的动作序列
	int 		count ; //所有的可能次数
	int 		tatalwater ; //总水量
};

void WaterHalf::InitAll()//vector<container>  Init,cur ;和count = 0
{
	//count
	count = 0 ;
	tatalwater = 0 ;

	//vector<container>  Init,cur和tatalwater
	int n = 0 ;
	int i = 0 ; 
	printf("请输入桶的数量 n : ");
	scanf("%d",&n);
	for (; i < n; ++i)
	{
		container tmp ; 

		printf("请输入%d号桶的容量 : ",i+1);

		scanf("%d",&tmp.capacity);

		printf("请输入%d号桶的当前水量 : ",i+1);

		scanf("%d",&tmp.size);

		tatalwater += tmp.size ; 

		Init.push_back(tmp);
	}

	//cur = Init ;//待处理,需  注意 2
	cur.assign(Init.begin(),Init.end());

	//vector<action>  act;
	i = 0 ;
	for ( ; i < n ; i++)
	{
		action tmp ;

		tmp.src = i;

		for (int j = 0 ; j < n ; j++)
		{
			if ( i != j )
			{
				tmp.des = j ; 

				act.push_back(tmp) ; 
			}
		}
	}

	//vector<actinfo> actlist添加一个特定值(最后pop用)
	actinfo tmp ; 
	tmp.acttype = 0 ; 
	tmp.water = 0 ; 
	actlist.push_back(tmp) ; 
	printf("3升水桶有2升水的输出的格式如(3,2)\n") ; 
}

void WaterHalf::Loop()//不需要&状态,类里本身就提供了cur.
{
	int n = act.size();
	int water = 0 ; 
	for (int actcode = 0 ; actcode < n ; actcode++)
	{
		if(isvalid(actcode)&&isStatusRep(actcode))
		{
			Handleact(actcode,water,cur);
			
			actinfo tmp ; 

			tmp . acttype = actcode ; 

			tmp . water = water ; 

			actlist.push_back(tmp) ; 

			if (isOK())
			{
				ShowAll();
				ReHandle();
			}
			else
			{
				Loop();
			}
		}	
	}
	ReHandle();
}

bool WaterHalf::isvalid(int actcode)
{
	return cur[act[actcode].src].size != 0 &&  cur[act[actcode].des].size != cur[act[actcode].des].capacity ; 
	/*return  src.size != 0 && des.size != des.capacity */; 
}

bool WaterHalf::isStatusRep(int actcode)
{
	//初始化
	CONTAIN tmpInit,tmpcur ;
	int watertmp = 0 ; 
	int curactcode = 0 ;
	tmpInit.assign(Init.begin(),Init.end());
	tmpcur.assign(cur.begin(),cur.end());

	//得到动作后的状态
	Handleact(actcode,watertmp,tmpcur);

	//先跟初始状态判断
	if (isequally2(tmpInit, tmpcur))
	{
		return false ; 
	}

	ACTINFO::iterator  i = actlist.begin() ; 
	i++;//忽略开头的特定值.
	for (; i != actlist.end() ; i++)
	{
		curactcode = i->acttype ; 
		//得到下一个状态
		Handleact(curactcode,watertmp,tmpInit);

		if(isequally2(tmpInit, tmpcur))
		{
			return false ; 
		}
	}
	return true ; 
	
}
bool WaterHalf::isequally2(CONTAIN &a,CONTAIN &b)
{
	int n = Init.size();
	for (int i = 0; i < n; ++i)
	{
		if (a[i].size != b[i].size)
		{
			return false ; 
		}
	}
	return true ;
}
void WaterHalf::Handleact(int actcode,int &water,CONTAIN &tmp )
{
	int watertotal2 = tmp[act[actcode].src].size + tmp[act[actcode].des].size ; 
	int dif = watertotal2 - tmp[act[actcode].des].capacity ; 
	if (dif >= 0 )
	{
		water = tmp[act[actcode].des].capacity - tmp[act[actcode].des].size ; 
		tmp[act[actcode].des].size = tmp[act[actcode].des].capacity ;  
		tmp[act[actcode].src].size = dif ;
	}
	else
	{
		water = tmp[act[actcode].src].size ; 
		tmp[act[actcode].des].size = watertotal2 ;  
		tmp[act[actcode].src].size = 0 ;
	}
}
bool WaterHalf::isOK()
{
	for (CONTAIN::iterator  i = cur.begin(); i != cur.end() ; i++)
	{
		if (i->size != tatalwater/2)
		{
			if ( i->size != 0 )
			{
				return false ;
			}
		}
	}
	return true ;
}
void WaterHalf::ShowAll()
{
	CONTAIN tmp ; 

	tmp.assign(Init.begin(),Init.end());

	int  actcode = 0 ;
	int  water = 0 ;
	count ++ ;

	printf("第%d种情况是\n",count) ; 
	printf("初始状态是\n") ; 

	ShowContainer(tmp) ; 

	ACTINFO::iterator  i = actlist.begin() ; 
	i++;//忽略开头的特定值.
	for (; i != actlist.end() ; i++)
	{
		actcode = i->acttype ; 

		Handleact(actcode,water,tmp);

		printf("%d升桶向%d升桶中倒入%d升水\n",tmp[act[actcode].src].capacity,tmp[act[actcode].des].capacity,water) ; 

		printf("当前状态是") ; 

		ShowContainer(tmp) ; 
	}
	printf("%d种情况结束\n\n",count) ; 

}
void WaterHalf::ShowContainer(CONTAIN &tmp)
{
	for (CONTAIN::iterator i = tmp.begin(); i != tmp.end() ; ++i)
	{
		printf("(%d,%d) ",i->capacity,i->size) ; 
	}
	printf("\n\n") ; 
}

void WaterHalf::ReHandle()
{
	actinfo tmp = actlist[actlist.size()-1];

	actlist.pop_back(); 

	int actcode = tmp.acttype ; 
	int water =  tmp.water ; 
	cur[act[actcode].src].size += water ; 
	cur[act[actcode].des].size -= water ; 
}

void WaterHalf::Start()
{
	InitAll() ; 

	Loop() ; 

	if (count == 0)
	{
		printf("不存在2等分的情况\n") ; 
	}

}

//测试
int main(int argc, char const *argv[])
{
	WaterHalf test;
	test.Start();
	system("pause");
	return 0;
}
