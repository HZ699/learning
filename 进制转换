#include <iostream>
#include <atlstr.h>
using namespace std;
//transform  
const char tab[] = "0123456789ABCDEF";
string  trans(string input,int bytes);

//达到的效果是实现数字进制的转化，具体是输入一个十进制数字，输出具有需要字节数的
//十六进制(若位数不够，则能自动补齐),结果如下
CString  Strhex(CString DesStr,int bytes);

/*int main(int argc, char const *argv[])
{
	
	CString output=trans("253",1);
	cout<<output<<endl;
	system("pause");
	return 0;
}*/

string  trans(string input,int bytes){
	int input_temp=stoi(input);
	cout<<input_temp<<endl;
	int m=2*bytes;//位数
	int max=1<<8*bytes;//能表示的最大数值
	// cout<<max<<endl;
	if (input_temp<0||input_temp>=max)return "error_data";//判断input是否符合要求
	string output=string(m--,'0');
	while(input_temp){
		output[m--]=tab[input_temp%16];
		input_temp/=16;
	}
	return output;
}

整理出的链接如下
https://www.zybuluo.com/hsj1234/note/425499
cmd markdown源代码
# 进制转换(初稿)

标签： 进制 

---
[TOC]
###目的
>实现**进制**之间的转换


###具体要求
>1. 实现各种进制之间的转换
2. 输出结果有**字节数要求**(即位数不够时,需要在高位补0)
3. 判断输入是否超过要求字节数所能表示的范围


###基础知识

>#### **按权相加法**(m进制转换为十进制)
m进制数从低位到高位（即从右往左）计算，第0位的权值是m的0次方，第1位的权值是m的1次方，第2位的权值是m的2次方，依次递增下去，把最后的结果相加的值就是十进制的值了。
公式如下:
$$result=a_0{m^0}+a_1{m^1}+a_2{m^2}+\dots+a_x{m^x}$$
$a_0,a_1,a_2,a_x$分别表示m进制的第$0,1,2,x$位的数值 
$m_0,m_1,m_x$分别表示m进制对应于第$0,1,2,x$位的权值
$result$表示转换结果(十进制)
>#### **除数取余法**(十进制转换为m进制)
对于整数部分，用被除数反复除以m，除第一次外，每次除以m均取前一次商的整数部分作被除数并依次记下每次的余数。另外，所得到的商的最后一位余数是所求二进制数的最高位。
对于小数部分，采用连续乘以基数m，并依次取出的整数部分，直至结果的小数部分为0为止。故该法称“乘基取整法”。


###流程图
```flow
st=>start: Start
io=>inputoutput: m进制的 input 和要求的字节数 bytes
op1=>operation: bytes能表示的范围[0,MAX=1<<8*bytes]
cond1=>condition: input是否在这个范围内
cond2=>condition: input==0
sub=>subroutine: 除16取余
e=>end

st->io->op1->cond1
cond1(no)->e
cond1(yes)->cond2
cond2(no)->sub->cond2 
cond2(yes)->e
```

###接口(10->16)
    string  trans(string input,int bytes)
>`input`代表输入的十进制数字
`bytes`代表需要输出的字节数要求
该函数返回的是要求字节数的十六进制

###具体实现
``` 
string  trans(string input,int bytes)
{
	int input_temp=stoi(input);
	int m=2*bytes;//位数
	int max=1<<8*bytes;//能表示的最大数值
	if (input_temp<0||input_temp>=max)return "error_data";//判断input是否符合要求
	string output=string(m--,'0');
	//主要用到除16取余法
	while(input_temp){
		output[m--]=tab[input_temp%16];
		input_temp/=16;
	}
	return output;
}
```
###参考文献
[二、八、十、十六进制转换（图解篇）](http://www.cnblogs.com/gaizai/p/4233780.html)

###待办事项
- [ ] 基本知识
  - [ ] 按权相加法
  - [ ] 短除法
- [x] 流程图

###总结
<table>
    <tr>
        <th>尚待改进</th>
        <th>意见</th>
    </tr>
    <tr>
        <td rowspan="3">
            <p>基础知识内容中 文字过多堆砌,影响阅读</p>
            <p>语言不够简练明了</p>
            <p>代码不够精炼</p>
            <p>整体逻辑,效果不够理想</p>
            <p>流程图效果不佳</p>
        </td>
        <td>
            <p>常看专业文档-->加强整体排版,规范用词用图(最好是图文交叉进行.文少图多)</p> 
            <p>看hihocoder的提示-->学会用伪代码写</p> 
            <p>看逻辑方面的书籍-->了解和增强逻辑结构</p>
            <p>用专业的图形编辑器-->暂时用ProcessOn</p>
        </td>
        
    </tr>
</table>
链接
[hihocoder](http://hihocoder.com/)
[ProcessOn](https://www.processon.com/)

###给个赞吧 <i class="icon-thumbs-up"></i>


