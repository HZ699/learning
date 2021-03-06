/**
 * -*- coding : GBK -*-
 * @Author : huangshengjianng
 * @Email : 1005542693@qq.com
 * @Date : 2016-09-14  15:46
 * @Last Modified Date :  2016-09-18 15:44       
 * @FileName : 塔吊移动模拟数据.cpp
 */

/*塔吊移动模拟数据
	目标  :  能够模拟出塔吊系统的每次工作情况的实时数据
	要求 : 只需要输入初始地址和目标地址,塔机自动运行(理想状态下).
	数学模型 : 地址用二维坐标(W,R)表示,初始位置设为(W_src,R_src),目标地址设为(W_des,R_des).
			   w表示角度(与东西方向形成的角度),范围在(0~360),精确到小数点两位,
			   r表示距离(物体与塔吊支撑轴的直线距离),范围在(0~大臂长可设为Arm_Length),精确度到小数点1位.
			   
			   实时数据(力矩,载重,风速,幅度,高度,角度)用(RT_torque,RT_load,RT_wind,RT_range,RT_height,RT_angle),其中
			   RT_load载重每次工作状态中是恒定的.
			   RT_torque≈RT_load×RT_range×0.001,力矩与载重和幅度成正比,
			   RT_wind风速为单独的自变量.
			   RT_range,RT_height,RT_angle.高度/角度/幅度都是可以逐步变化的,一般来说,高度先变化,紧接着是角度或者幅度变化(任选).
			   其中高度又可假定为一个恒定值,只要物体在这个高度之上就可以安全运输.
			   概括而言 : 需要的变量除了力矩.载重,高度外,需要风速,幅度/角度.风速则是设定为0~5之间,就是幅度/角度.
	引申问题 : 两端到中心的快速简洁方法?以及二维方向的选择?

 */

#include <iostream>
#include <time.h>
using namespace std;

#define Arm_Length  33  //塔大臂长33米,塔身高15米.
#define Height_Limit  10	//高度限位为10米

float angle_cur = 0.0;
float angle_des = 0.0;
float range_cur = 0.0;
float range_des = 0.0;
int   RT_load   = 0;	
float RT_height = 0.0;

//函数,用于产生幅度,角度,高度
void  RT_Data_Produce(float &RT_range,float &RT_angle ,float &RT_height){
	if((RT_angle != angle_des || RT_range != range_des) && RT_height < Height_Limit )
	{
		RT_height += 0.5+(rand()%11)/10.0;//0.5~1.5
		return ;
	}
	if(RT_angle == angle_des && RT_range == range_des && RT_height > 0.0 )
	{
		RT_height -= 0.5+(rand()%11)/10.0;
		if (RT_height < 0.0)
		{
			RT_height = 0.0;
		}
		return ;
	}
	//幅度,高度
	if (RT_range == range_des){
		if (RT_angle == angle_des)return;
		if (RT_angle < angle_des)
		{
			RT_angle += 9.00 + (rand()%201)/100.0;//9.00~11.00
			if (RT_angle > angle_des)
			{
				RT_angle = angle_des ;
			}
			return;
		}
		if (RT_angle > angle_des)
		{
			RT_angle -= 9.00 + (rand()%201)/100.0;
			if (RT_angle < angle_des)
			{
				RT_angle = angle_des ;
			}
			return;
		}
	}

	if (RT_range > range_des)
	{
		RT_range -= 0.5+(rand()%11)/10.0;
		if (RT_range < range_des)
		{
			RT_range = range_des;
		}
		return;
	}
	if (RT_range < range_des)
	{
		RT_range += 0.5+(rand()%11)/10.0;
		if (RT_range > range_des)
		{
			RT_range = range_des;
		}
		return;
	}
}




//测试
int main(int argc, char const *argv[])
{
	int n=500;
	while (n)
{
	//随机生成两个(range_src,angle_src),(range_des,angle_des)
		srand(time(NULL));
		if (angle_cur == angle_des && range_cur == range_des && RT_height == 0.0)
		{
			angle_cur=rand()%360 + (rand()%101)/100.0;
			angle_des=rand()%360 + (rand()%101)/100.0;
			range_cur=rand()%Arm_Length + (rand()%11)/10.0;
			range_des=rand()%Arm_Length + (rand()%11)/10.0;
			RT_load  =rand()%1000+4000;	//(4000~5000)
			cout<< "初始幅度:"<<range_cur<<" "<< "初始角度:"<<angle_cur<<" "<< "目标幅度:"<<range_des<<" "<< "目标角度:"<<angle_des<<" "<<endl;
		}
	
		//准备数据
		float RT_torque;
		float RT_wind;
	
		//产生当前幅度和角度,及高度
		RT_Data_Produce(range_cur, angle_cur ,RT_height);
	
		//力矩和风速
		RT_torque = RT_load * range_cur * 0.001 ;
		RT_wind   = rand()%5 + (rand()%11)/10.0;
	
	//力矩,载重,风速,幅度,高度,角度
		cout<<"力矩:"<<RT_torque<<" "<<"载重:"<<RT_load<<" "<<"风速:"<<RT_wind<<" "<<"幅度:"<<range_cur<<" "<<"高度:"<<RT_height<<" "<<"角度:"<<angle_cur<<endl;

		time_t t=time(NULL);
		while(t ==time(NULL));
}
	system( "pause");
	return 0;
}
