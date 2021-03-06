# 嵌入式系统C语言编程基础

# 目录

## 关于本环节

### 为什么进行本环节

会C语法与会用C语言写程序是两个概念

C的灵活性以及由此而产生的陷阱非常多

本环节将嵌入式系统中最基本的（最经常用到的）概念与技巧介绍给大家

## 小测验

**Quiz 1**

所有嵌入式系统的主流程最后都进入一个死循环，怎样用C语言实现一个死循环？

**Quiz 2**

while(){...}和do{...}while()有什么区别？

**Quiz 3**

用变量a给出下列定义：

a）一个整型数

b）一个指向整型数的指针

c）一个有10个整型数的数组

d）一个有10个指针的数组，该指针是指向一个整型数的

**Quiz 4**

关键字static的作用是什么？

**Quiz 5**

关键字const的作用是什么？

**Quiz 6**

定义一个标准宏MIN，这个宏输入两个参数并返回较小的一个。

**Quiz 7**

嵌入式系统中经常要对变量或寄存器进行位操作。给定一个int型变量a，写两段代码，第一个将a的bit 3置为1，第二个将a的bit 3置为0。以上两个操作中，要保持其它位不变。

**Quiz 8**

嵌入式系统具有经常去直接访问物理地址的特点。在某工程中，要求设置一绝对地址为0x5a00的整型变量的值为0xaa55。写代码去完成这一任务。

**Quiz 9**

下面这段代码的输出是什么？

```c
void foo(void)
{
    unsigned int a = 6;
    int b = -20;
    (a+b > 6)?puts(">6"):puts("<6");
}
```

**Quiz 10**

请评论下面一段程序代码：

```c
void test()
{
    char string[10];
    char *str = "0123456789";
    strcpy(string,str);
}
```

**Quiz 11**

请评论下面一段程序代码：

```c
void GetMemory(char *p){
	p = (char *)malloc(0x20);
}
void Test(void){
    char *str = NULL;
    GetMemory(str);
    strcpy(str,"Hello World!");
    printf(str);
}
```

**Quiz 12**

终端是嵌入式系统的重要组成部分。请评论下面一段终端服务子程序代码：

```c
_interrupt double compute_area(double radius)
{
    double area = PI*radius*radius;
    printf("\nArea = %f",area);
    return area;
}
```

### 解答

**Quiz 1 Answer**

- while(1){...}

**Quiz 2 Answer**

while(){...}为入口条件循环，即在每次执行循环之前先检查判断条件；do{...}while()为退出条件循环，即在执行循环之后再检查判断条件。

**Quiz 3 Answer**

a）int a;

b）int *a;

c）int a[10];

d）int *a[10];

**Quiz 4 Answer**

在C语言中，关键字static有三个明显的作用：

1. 在函数体内，一个被声明为静态的变量在这一函数被调用过程中维持其值不变。
2. 在模块内（但在函数体外），一个被声明为静态的变量可以被模块内所用函数访问，但不能被模块外其它函数访问。它是一个本地的全局变量。
3. 在模块内，一个被声明为静态的函数只可被这一模块内的其它函数调用。那就是，这个函数被限制在声明它的模块的本地范围内使用。

**Quiz 5 Answer**

const是constant的缩写，“恒定不变”的意思。被const修饰的东西都受到强制保护，可以预防意外的变动，能提高程序的健壮性。

const常量与#define常量：前者有数据类型，后者只是字符替换（而且可能产生意料不到的错误），所以编译器可以对前者进行安全性检查。

**Quiz 6 Answer**

```c
#define MIN(A,B)((A) <= B)?(A):(B))
```

#define宏的副作用，下面的代码执行后会发生什么事：

```c
least = MIN(*p++,b); 
```

*p就会发生改变，出现宏定义中不匹配的问题。

**Quiz 7 Answer**

```c
const int BIT3 = 0x01 << 3;
static int a;
void SetBit3(void){
    a |= BIT3;
}
void ClearBit3(void){
    a &= ~BIT3;
}
```

**Quiz 8 Answer**

```c
int *ptTemp = (int *)0x5a00;
*ptTemp = 0xaa55;
```

**Quiz 9 Answer**

输出为“>6”，原因是当表达式中存在有符合类型和无符号类型时所有的操作数都自动转换为无符号类型。因此-20变成了一个非常大的正整数，所以该表达式计算出的结果大于6。这一点对于频繁用到无符号数据类型的嵌入式系统来说是非常重要的。

**Quiz 10 Answer**

字符串str需要11个字节才能村方向（包括末尾的'\0'），而string只有10个字节的空间，所以strcpy会导致数组越界。

**Quiz 11 Answer**

编译器总是要为函数的每个参数制作临时副本，指针参数p的副本是_p，编译器使 _p = p。本例中， _p申请了新的内存，但只是 _p的值改变了，p的值却丝毫未变，仍然为NULL。事实上，每执行一次GetMemory就会泄露一块内存。

**Quiz 12 Answer**

1）ISR不能返回值；

2）不能向ISR传递参数；

3）ISR应该是短而有效的，因而在ISR中做浮点运算、使用printf等是不明智的，会经常有重入和性能上的问题。
## C语言复习

### 1.循环与分支

#### (1)几种循环语句：

```c
for(initialize;test;update){body;}
while(test){body;}
do{body;}while(test);
```

#### (2)循环辅助手段：

==break==语句用于跳出循环，==continue==语句用于结束本次循环。

#### (3)三种形式的if语句：

```c
if(expression){...}

if(expression){...}else{...}

if(expression1){...}
else if(expression){...}
...
else{...}
```

#### (4)条件运算符?:

```c
expression1 ? expression2 : expression3
```

如果expression1为真，整个表达式的值为expression2的值，否则为expression3的值；

是if...else...的简写形式，但是编译器可以产生比if..else..更优化的代码。

#### (5)多重选择：switch

```c
switch(expression){
    case constant1:statements;break;
    case constant2:statements;break;
    ...
    default:statements;break;
}
```



### 2.作用域与存储类

#### (1)作用域

==代码块==作用域（局部变量）

==代码块==：包含在开始花括号和对应结束花括号和对应结束花括号之内的一段代码。

==作用域==：从定义变量位置到该代码块的末尾。

==文件==作用域（全局变量）

在所有函数之外定义的变量具有文件作用域。

==作用域==：从定义变量位置到包含该定义的文件的结尾处。在其他位置使用该变量应用extern来声明该变量。

#### (2)存储时期

==静态存储时期==：程序运行期间一直存在，给变量分配固定的存储空间；

==所有全局变量==具有静态存储时期（具有静态存储时期的并不都是全局变量），但是修饰全局变量的==关键词static==表明的是链接类型，并非存储时期。

==动态（自动）存储时期==：运行期间根据需要动态的给变量分配存储空间。

#### (3)5种存储类

| 存储类     | 存储时期 | 作用域 | 链接 | 声明方式                       |
| ---------- | -------- | ------ | ---- | ------------------------------ |
| 自动       | 自动     | 代码块 | 空   | 代码块内                       |
| 寄存器     | 自动     | 代码块 | 空   | 代码块内，使用关键字register   |
| 外部静态   | 静态     | 文件   | 外部 | 所有函数之外                   |
| 内部静态   | 静态     | 文件   | 内部 | 所有函数之外，使用关键字static |
| 代码块静态 | 静态     | 代码块 | 空   | 代码块内，使用关键字static     |

### 3.内存与指针

#### (1)内存分配方式

从==静态存储器==分配。内存在程序编译的时候就已经分配好，这块内存在程序的整个运行期间都存在。例如==全局变量==，==static变量==；

从==栈上创建==。在执行函数时，函数内==局部变量==的存储单元都可以在栈上创建，函数执行==结束时==这些存储单元==自动==被释放。栈内存分配运算内置于处理器的指令集中，效率很高，但是分配的内存容量有限；

动态分配内存。程序在运行的时候由程序员自己负责申请和释放内存。

#### (2)内存陷阱

C语言的灵活性，指针的应用，以及C语法的宽容性很容易造成代码的错误，这其中最主要的就是==内存单元的溢出==。

1. 堆栈溢出

2. 数组越界

   ...

将错误锁定在一个函数中以后，首先应该关注内存的问题。

举例，看看下面这段代码有什么问题

```c
char *DoSomething()
{
    char i[32*1024];
    ...
        return i;
}
//两个重大问题：
//1、临时变量在堆栈上创建，太大的临时变量数组会冲掉堆栈；
//2、返回堆栈中的地址是没有意义的，因为堆栈中的内容永远是不确定的。
```

##### 数组越界的危险

==临时数组==：在栈上创建，因此临时数组越界有可能导致某些局部变量莫名其妙被改，函数返回时崩溃等等；

==全局数组==：在静态存储器创建，因此全局数据越界有可能导致某些全局变量莫名其妙被改，被冲的动态内存无法释放等等。

#### (3)指针

##### 指针是什么？

指针是==一个变量==，它的==值是另外一个变量的地址==。

##### 指针的类型

指针所指向的变量的类型，就是指针的类型。

举例，右边的运算有何不同：

```c
int X[2], *pX=&X[0];			pX++;//指向下一个元素，假设整型占4个字节，pX要加4才能指向X[1]的地址。
char Y[2], *pY=&Y[0];			pY++;
```

##### 指针的三要素

1. 指针指向的地址；
2. 指针指向地址上的内容；
3. 指针本身的地址；

举例：

```c
int A, *pA, **ppA;
pA = &A;
ppA = &pA;
```

##### 指针的大小（指针变量占用的内存空间）

​	举例，一下为ARM平台下的一段32位C程序，请计算sizeof的值

```c
	char str[] = "Hello";	//6个元素（包含'\0'）
	char *p = str;			//32位占4个字节
	int n = 10;				//32位占4个字节

sizeof(str) = 6
sizeof(p) = 4
sizeof(n) = 4
```

##### 指针的初始化

指针变量在==没==有被初始化之前，它的值是==随机==的；一个==指向不明==的指针是非常危险的。

当创建一个指针时，系统只分配了用来存储指针本身的内存空间，并不分配用来存储数据的内存空间。使用指针之前，==必须==给它赋予一个已分配的内存地址。

指针与数组

举例，下列操作是否合法：

```c
int a[4],*p;
p = a;				//等价于p=&a[0];
*(a+2) = 0x00;		//等价于a[2];
p[2] = 0x01;		//等价于*(p+2);
//合法，但是数组名不同于指针：
//数组名a是指向数组起始位置的“常量”。
//因此不能对数组名进行赋值操作，如：
a = p;		//错误
a++;		//错误
```

指针与数组什么时候是相同的

举例，一下为ARM平台下的一段32位C程序，请计算sizeof的值。

```c
void Func(char a[100]){
    sizeof(a) = ?
}

//sizeof(a) = 4
```

1. ==数组名==作为==函数形参==的时，在函数体内，其失去了本身的内涵，==仅仅只是一个指针==；
2. 很遗憾，在失去其内涵的同时，它还失去了其常量特性，可以坐自增、自减等操作，可以被修改。

数组与指针运用规则

![数组与指针运用规则](C:\Users\hp\Desktop\单片机\MSP432\学习\第一章-环境及C语言基础\数组与指针运用规则.png)

### 4.位操作

#### (1)位操作的用途

硬件寄存器控制；

压缩和加密操作；

提高程序运行效率；

...

因为位是程序可以操作的最小数据单位，所以理论上可以用“位操作”完成所有的运算与操作。

#### (2)位运算符

##### 位逻辑运算符

​	==&==		 位与（两个数对应位都为1结果才为1）

​	==|==		  位或（两个数对应位仅有一个为1结果则为1）

​	==^==	 	 位异或（两个数对应位不同结果则为1）

​	==~==		  按位取反（单目运算符）

##### 移位运算符

​	==<<==		左移

​	==>>==		右移

#### (3)用法：掩码

位操作符通常跟掩码一起用。掩码是某些位为开而某些位为关的位组合。例：

flag &=MASK;

MASK

|  0   |  0   |  0   |  0   |  0   |  0   |  1   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |

&

flag

|  1   |  0   |  1   |  1   |  0   |  1   |  1   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |

=

|  0   |  0   |  0   |  0   |  0   |  0   |  1   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |

#### (4)用法：打开位、关闭位、转置位

打开位：

flag = flag | MASK;或flag |= MASK;

关闭位：

flag = flag &~ MASK;或flag &= ~MASK;

转置位：

flag = flag ^ MASK;或flag ^= MASK;

#### (5)用法：查看某一位的值

错误用法：

if(flag == MASK)

正确用法：

if((flag&MASK) == MASK)

位运算符的优先级低于 == ，因此需要在flag&MASK的两侧加上圆括号。

#### (6)用法：移位操作

unsigned char ch=0x07;	//00000111

unsigned char i;

i = ch << 6;

i = ch >> 2;

|  0   |  0   |  0   |  0   |  0   |  1   |  1   |  1   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |

00000111左移6位变成

|  1   |  1   |  0   |  0   |  0   |  0   |  0   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |

00000111右移2位变成

|  0   |  0   |  0   |  0   |  0   |  0   |  0   |  1   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |

### 5.预编译处理

C编译系统在对程序进行编译之前，先进行预处理。C提供的预处理功能主要有以下三种：

**宏定义**

**文件包含**

**条件编译**

#### (1)宏定义

**类对象宏**

例：#define STX 0x02

**类函数宏**

例：#define SQUARE(x) ((x)*(x))

几点说明：

1. **宏定义不是C语句，不在行末加分号；**
2. **宏名有效范围为从定义处到本源文件结束；**
3. **在宏定义时，可以引用已经定义的宏名；**
4. **宏替换不占运行时间，只占编译时间；**

#### (2)文件包含：#include

预处理器发现#include后，就会寻找后跟的这个文件并把这个文件的内容复制到当前位置替换#include指令；

使用#include指令的一些例子：

| #include <stdio.h>             | 从标准库路径开始搜索文件       |
| ------------------------------ | ------------------------------ |
| **#include "def.h"**           | **从当前工作路径开始搜索文件** |
| **#include "/usr/head/def.h"** | **搜索“/usr/head/”目录**       |

#### (3)条件编译

条件编译指不对整个程序编译，而是编译满足条件的那部分。条件编译有以下几种形式：

a. **#ifdef** 标识符
    程序段1;
   **#else**
	程序段2;
   **#endif**
它的作用：当==标识符==在==前面==已经定义过，则对程序段1进行编译，否则对程序段2进行编译。

b. **#ifndef** 标识符
    程序段1;
   **#else**
	程序段2;
   **#endif**

它的作用和#ifdef相反，当==标识符==之前==没被定义==过，则对程序段1进行编译，否则就对程序段2进行编译。

c. **#if** 表达式
    程序段1;
   **#else**
	程序段2;
   **#endif**

它的作用：当表达式的值为真时，对程序段1进行编译，都则就对程序段2进行编译。

举例，下面是某工程文件中.h文件中的一段程序，请说明#ifndef/#define/#endif结构的作用。

```C
#ifndef DEF_H
#define DEF_H

#include <math.h>
#include "graphics.h"
...
#endif
    
//防止头文件被重复引用
```

## 编程规范

### (1)规范的作用

改善代码质量

提高开发速度

增加团队精神

养成良好习惯

### (2)编程规范

**养成良好的编程习惯**

#### 什么是好的程序

**1.易读**

理想的情况：能把一个程序代码读出声音来，别人听了后就知道这个程序是解决什么样的问题，是如何解决的

**2.精炼简洁**

**3.运行快**

**4.结构明了**

#### 程序设计风格

标识符的命名

推荐一种C程序标识符命名法

标识符命名应注意的一些细节

书写格式

编程习惯

#### **标识符的命名**

##### 标识符命名体系

匈牙利命名法、GNU编程风格、Java命名规则，Pascal命名规则

匈牙利命名法：

匈牙利命名法是由Microsoft的著名开发人员、Excel的主要设计者查尔斯·西蒙尼在他的博士论文中提出来的，由于西蒙尼的祖籍是匈牙利，所以这种命名法叫匈牙利命名法。

==匈牙利命名法==为C程序标识符的命名定义了一种非常标准化的方式，这种命名方式是以两条规则为基础的：

1. 变量的名字以一个或者多个==小写字母==前缀开头，前缀能够体现变量==数据类型==、==作用域==等信息。
2. 在标识符内，前缀以后就是一个或者多个第一个==字母大写==的单词，这些单词清楚地指出了该标识符的作用。

##### 推荐一种C程序标识符命名法

(1)变量命名加前缀

c			char

s			short

n			int		nDoorNum

l			 long

b			boolean取值只为真和假的整型变量 如 bValid

f			 float		浮点数

d			double

a			数组	a[5]

(2)变量名中单词开头字母大写，其他字母小写

但是常用的意义明显的变量，如i,j,k,坐标x,y等不必遵循(1),(2)	StudentName,TeacherName

(3)常量和宏都是大写，单词之间用 '_' 分隔

```c
#define MAX_WIDTH	5

#define PI	3.14

#define ABS(x)	((x)>=0>(x):-(x))
```



##### 标识符命名应注意的一些细节

(1)标识符号应能提高足够信息，最好是可以发音的。

(2)为全局变量取长的，描述信息多的名字，为局部变量取短的名字

(3)名字太长时可以适当采用单词的缩写。但要注意，缩写方式要一致。要缩写就全部缩写。

比如 单词Number，如果某个变量里缩写成了：int **nDoorNum**;那么最好包含 Number单词的变量都缩写成Num。

(4)注意使用单词的复数形式。如

int nTotalStudents, nStudents ;容易让人理解成代表学生数目，而 nStudent 含义就不十分明显。

(5)对于返回值为真或假的函数，加 “ Is ”前缀如：

```c
int IsCanceled();

int isalpha();//C语言标准库函数

BOOL		IsButtonPushed();
```

(6)对于获取某个数值的函数，加 “ Get ”前缀

```c
char *GetFileName();
```

(7)对于设置某个数值的含糊，加 “ Set ”前缀

```c
void SetMaxVolume();
```

(8)**一般变量和结构名用名词，函数名用动词或动宾词组。**

#### 程序书写格式注意事项

(1)正确使用缩进

首先，一定要有缩进，否则代码的层次不明显。

缩进应为4个空格较好。需要缩进时一律按Tab键，或一律按空格键，不要有时用Tab键缩进，有时用空格键缩进。一般开发环境都能设置一个Tab键相当于多少个空格，此时就都用Tab键。

(2)行宽与拆行

一行不要太长，不能超过显示区域。以免阅读不便。太长则应拆行。拆行最后发生在运算符前面，不要发生在运算符后面如

```c
if( Condition1()) && Condition2()
    && Condition3()){
}
```

(3)注意	' { ',' } '位置不可随意，要统一

如果写了：

```c
if( Condition1()) {
    DoSomething();
}
```

别处就不要写：

```
if( Condition2()) 
{
    DoSomething();
}
```

(4)变量和运算符之间最后加1个空格

```c
int nAge = 5;
nAge = 4;
if( nAge >= 4)
    printf("%d",nAge);

for( i = 0;i < 100;i ++);
```

#### 一些好的编程习惯

(1)尽量不要使用立即数，而用#define（C++中用const）定义成常量，以便以后修改

```c
#define MAX_STUDENTS 20
struct SStudent aStudents [MAX_STUDENTS]
    struct SStudent aStudents [20];

#define TOTAL_ELEMENTS 100
for( int i = 0; i < TOTAL_ELEMENTS;i ++) {
}
```

(2)带参数的宏定义应该在整个宏体外加括号，而且宏参数都要用括号包裹

```c
#define SQUARE(x)			x*x			//平方

则		SQUARE(k + 1);	编程	k+1*k+1;错

即使	#define SQUARE(x)			(x)*(x)

也不保险

应该:

#define SQUARE(x)			((x)*(x))		//平方
```

(3)稍复杂的表达式中要积极使用括号，以免优先级理解上的混乱

```c
n = k+++j;		//不好
n = ( k++ )+j;	//好一点
```

(4)不很容易理解的表达式应分几行写：

```c
n = ( k++ )+j;应该写成：
n = k + j;
k++;
```

(5)不提倡在表达式中使用 `?:` 形式，而用 `if..else` 语句替代

```c
xp = 2*k < (n-m) ? c[k+1] : d[k--];
if(2*k < (n-m))
    xp = c[k+1];
else
    xp = d[k--];
```

(6)嵌套的if else语句要多使用 {}

```c
if(Condition1())
    if(Condition2())
        DoSomething();
	else
        NoCondition2();
不够好，应该：
if(Condition1()){
    if(Condition2())
    {
        DoSomething();
    }
	else
    {
        NoCondition2();
    }
}
```

(7)遵循一些惯例的写法，如：

```c
循环的固定写法：

for( i = 0;i < n;i++)	array[i] = 0;

而非	
i = 0;

while( i <= n-1)	array[i++] = 0;

死循环写法：

for( ; ; ) {...}	或	while(1) {...}
```

(8)写出来的代码应该容易读出声

```c
比如
if(!(n > m)&& !(s >t))
就不如
if((m <= n) && (t <= s))
 
if(!(c == 'y' || c == 'z'))
不如
if(c!='y' && c!='z')
```

## 开发高效程序的技巧

(1)ARM编程中局部变量的使用

举例，请看下面一段程序：

```c
int checksum(int *data)
{
	char i;
    ...
    for(i = 0;i < 64;i++){
        ...;
    }
    ...
}
```

=>

```
...
ADD r1,r1,#1
AND r1,r1,#0xFF
CMP r1,#0x40
...
```

把上面的程序段将i声明为==unsigned int==类型，比较一下：

```c
...
AND r1,r1,#1
CMP r1,#0x40
...
```

ARM编程中局部变量类型的使用

char或short类型并不比int类型占用更小的寄存器空间或者堆栈空间，==应尽量不要使用char或short作为局部变量==，以防止做不必要的转换；除非要使用char或short的溢出归零特性，如255+1=0。

(2)ARM编程中函数参数的传递

4寄存器原则(four-register rule)：

ARM-Thumb过程调用标准(ATPCS)定义了{R0-R3}四个寄存器作为参数传递和结果返回寄存器，如果参数超过4个，则使用堆栈进行传递（额外的指令和慢速的存储器操作）。因为内部寄存器的访问速度要远远大于存储器，所以我们应==尽量把函数的参数控制在4个以下==。

(3)结构体安排

举例，对下面两个结构体进行比较

```c
struct A{
    char a;
    int b;
    char c;
    short d;
}

struct B{
    char a;
    char c;
    short d;
    int b;
}
```

A内存空间

| pad          | pad          | pad         | a[7,0]     |
| ------------ | ------------ | ----------- | ---------- |
| **b[31,24]** | **b[23,16]** | **b[15,8]** | **b[7,0]** |
| **d[15,8]**  | **d[7,0]**   | **pad**     | **c[7,0]** |

B内存空间

| d[15,8]      | d[7,0]       | c[7,0]      | a[7,0]     |
| ------------ | ------------ | ----------- | ---------- |
| **b[31,24]** | **b[23,16]** | **b[15,8]** | **b[7,8]** |

A读出内存速度会比B速度慢，因为A要读三次，B只要两次

(4)C语言中的封装思想

举例，给出这样一个人机界面：

![人机界面](C:\Users\hp\Desktop\单片机\MSP432\学习\第一章-环境及C语言基础\人机界面.png)

要求：以中间的按键切换液晶显示菜单，左右两个按键对当前项的值进行增减操作。

我曾经这样做：

```c
void onLeftKey()
{
    switch(currentFocus){
        case MENU1:
            menu1onLeft();
            break;
        case MENU2:
            menu2onLeft();
            break;
        ...
    }
}
void onMidkey()
{
    currentFocus++;
    switch(currentFocus){
        case MENU1:
            MenuText = "...";
            break;
        ...
    }
}
void onRightKey()
{
    switch(currentFocus){
        case MENU1:
            menu1onRight();
            break;
        case MENU2:
            menu2onRight();
            break;
        ...
    }
}
```

后来我这样做：

```c
//将菜单的属性和操作“封装”在一起
typedef struct KeyAdjMenu{
    UCHAR *text;//液晶显示文本
    void(*onAdjKey)(int key);
    void(*onMidkey)();
}
//定义菜单时，只需这样：
struct KeyAdjMenu menu[NUM] = 
{
    { "menu1" ,menu1onAdj,onMidkey},
    { "menu2" ,menu2onAdj,onMidkey},
    ...
}
//按键的处理变成：
swirch(key){
    case LEFT:
    case RIGHT:
    
menu[currentFocus].onAdjKey(key);
    break;
    case MIDDLE:
      currentFocus++;
      if(currentFocus > NUM)
          currentFocus = 0;
    
LcdDisplay(menu[currentFocus].text);
    break;
}
```

(5)Bug的修正

别着急改，想想，再想想，想清楚了再动手；

考虑所做的修改是否对系统造成新的影响；

考虑是否对全局数据结构或其他人的代码造成影响；

修改完了，应该有详细的代码注释和文档，并对修改过的代码进行测试。

## 一些有益的建议

长期坚持好的Coding Style；

避免编写技巧性很高的代码；

长期坚持良好的文档写作习惯；

不要崇拜那些独来独往、不受约束且带点邪气的所谓“真正的编程高手”；

基础最重要，坚持学习，天天向上

