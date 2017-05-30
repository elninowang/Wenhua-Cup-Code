# Wenhua-Cup-Code
2002年大学期间参加"文华杯"算法大赛的获得第二名的代码和文档，现在放在github上

# 2002年"文达杯"算法大赛参赛作品
## 一.参赛说明：	
	本作品共三题答案，分为2道必做题与1道选作题，
上交内容为一张1.44软盘，一份算法说明的材料。
软盘内储存程序源代码及程序的 .exe文件，并且包含程序使用的说明文件：readme.exe
算法说明材料包含三道赛题的原程序代码说明，编程心得。
本份赛题答案是由

计算机科学与技术系0108班 王闻宇  紫崧9D205室

## 二.程序说明：


- Message Decoding:

		源代码：MESSAGE.C
		可执行文件：MESSAGE.EXE

- Mining:
		源代码：MINE.C
		可执行文件：MINE.EXE

- Code Generation:

		源代码：CODE.C	
		可执行文件：CODE.EXE

- 三道题所用语言均为 Turbo C 2.0

## 三.输入与输出的格式

####题目 Message Decoding:

以文件形式输入,以屏幕形式输出:

[屏幕提示]Please input the path of the input file

[输入你要读的文件,例如]D:\Me.txt

[D:\Me.txt如下:]

```
hasdkfhhasdfhjjksfhjshdfhsj
01010010010010011
01010010010010011
001 00000001
011 000 001 010 011 100 101 110 
000 001 010 011 100 101 110 111
000

abcdefghijklmnopqrstuvwxyz12
001 000000001
010 000000000101010110101010 11
011 000000 001001 010010 011011 100100 101101 110110 111
100 00000000 00010001 00100010 00110011 01000100 01010101 01100110 01110111
    10001000 10011001 10101010 10111011 11001100 11011101 11101110 1111
001 000000001
010 000000000101010110101010 11
011 000000 001001 010010 011011 100100 101101 110110 111
100 00000000 00010001 00100010 00110011 01000100 01010101 01100110 01110111
    10001000 10011001 10101010 10111011 11001100 11011101 11101110 1111
101 00000 00000 00000 00001 00001 00001 11111
000
```

[屏幕上打印出以下字符串:]

```
dsadsadsadsahhhhhhhkfhhasdkfhhasd
aaaaaaaabbbbccccddddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzzaaaaaaaabbbbcccc
ddddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz111222
[按任意键结束]
```


#### 题目 Mining:

以键盘形式输入,以屏幕形式输出:

```
[屏幕提示,请输入你要输入的数据的祖数]
Please Input the Number of The Text Case Which Consists of 5 Integers:
[(假设要输入3组数据)输入]3
[屏幕提示]1:  Please Input S W C K M:
[输入]10 20 10 1 5
[输出]40005
[屏幕提示]2:  Please Input S W C K M:
[输入]1000 50000 10 1000 5
[输出]50002005
[屏幕提示]3:  Please Input S W C K M:
[输入]10000 10000 1 10000 0
[输出]100020000
[按任意键结束]
```


#### 题目 Code Generation:

以文件形式输入,以文件形式输出:

```
[屏幕提示]Please input the path of InPut file:
[输入你要读的文件,例如]D:\code.txt
[屏幕提示]Please input the path of Output file:
[输入你的结果所要写入的文件,例如]D:\ouput.txt
[程序立即结束]
[如果 D:\code.txt 如下]
asdf**	-sdf+ @*/asdf////
as+d+d+@@h-j-k*j*h/f/f/
asdf++g*jkj-+@@w-/+
```

[则输出文件 D:\ouput.txt 如下]

```
L a
ST 0
L s
ST 1
L d
M f
M $1
ST 1
L $0
S $1
ST 0
L s
ST 1
L d
A f
N
M $1
ST 1
L $0
D $1
ST 0
L a
ST 1
L s
ST 2
L d
D f
ST 3
L $2
D $3
ST 2
L $1
D $2
ST 1
L $0
D $1

L a
A s
A d
A d
N
N
S h
S j
M k
M j
D h
D f
D f

L a
ST 0
L s
ST 1
L d
A f
A $1
M g
ST 1
L j
ST 2
L k
S j
A $2
N
N
S w
ST 2
L $1
D $2
A $0
```

