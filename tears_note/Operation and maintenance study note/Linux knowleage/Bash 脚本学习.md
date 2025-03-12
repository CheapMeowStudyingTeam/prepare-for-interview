# Vi编辑&Bash 脚本学习

## 1.1 **Vim文本编辑器**

Vim编辑器中设置了3种模式—命令模式、末行模式和编辑模式，每种模式分别又支持多种不同的命令快捷键，这大大提高了工作效率，而且用户在习惯之后也会觉得相当顺手。要想高效地操作文本，就必须先搞清这3种模式的操作区别以及模式之间的切换方法

**命令模式**：控制光标移动，可对文本进行复制、粘贴、删除和查找等工作。

**输入模式**：正常的文本录入。

**末行模式**：保存或退出文档，以及设置编辑环境。

![第4章 Vim编辑器与Shell命令脚本第4章 Vim编辑器与Shell命令脚本](./assets/vim不同模式间的切换-1724897576779-6.png)

​                              命令模式中最常用的一些命令

| 命令 | 作用                                               |
| ---- | -------------------------------------------------- |
| dd   | 删除（剪切）光标所在整行                           |
| 5dd  | 删除（剪切）从光标处开始的5行                      |
| yy   | 复制光标所在整行                                   |
| 5yy  | 复制从光标处开始的5行                              |
| n    | 显示搜索命令定位到的下一个字符串                   |
| N    | 显示搜索命令定位到的上一个字符串                   |
| u    | 撤销上一步的操作                                   |
| p    | 将之前删除（dd）或复制（yy）过的数据粘贴到光标后面 |

​                              末行模式中最常用的一些命令

| 命令          | 作用                                 |
| ------------- | ------------------------------------ |
| :w            | 保存                                 |
| :q            | 退出                                 |
| :q!           | 强制退出（放弃对文档的修改内容）     |
| :wq!          | 强制保存退出                         |
| :set nu       | 显示行号                             |
| :set nonu     | 不显示行号                           |
| :命令         | 执行该命令                           |
| :整数         | 跳转到该行                           |
| :s/one/two    | 将当前光标所在行的第一个one替换成two |
| :s/one/two/g  | 将当前光标所在行的所有one替换成two   |
| :%s/one/two/g | 将全文中的所有one替换成two           |
| ?字符串       | 在文本中从下至上搜索该字符串         |
| /字符串       | 在文本中从上至下搜索该字符串         |



## **2.1 编写简单的脚本**

Vim example.sh

```shell
#! /bin/bash
#welcome to linux program
echo $0
echo $1,$3,$5
echo $#, $*

```

结果：

```shell
# bash haha.sh a b c d e f g
haha.sh
a,c,e
7,a b c d e f g
```

## 2.2 **判断用户的参数**

按照测试对象来划分，条件测试语句可以分为4种：

> 文件测试语句；
>
> 逻辑测试语句；
>
> 整数值比较语句；
>
> 字符串比较语句。

![条件执行格式](./assets/条件执行格式-1724896148411-2.jpg)



###                         文件测试所用的参数

| 操作符 | 作用                       |
| ------ | -------------------------- |
| -d     | 测试文件是否为目录类型     |
| -e     | 测试文件是否存在           |
| -f     | 判断是否为一般文件         |
| -r     | 测试当前用户是否有权限读取 |
| -w     | 测试当前用户是否有权限写入 |
| -x     | 测试当前用户是否有权限执行 |

下面使用文件测试语句来判断/etc/fstab是否为一个目录类型的文件，然后通过Shell解释器的内设$?变量显示上一条命令执行后的返回值。如果返回值为0，则目录存在；如果返回值为非零的值，则意味着它不是目录，或这个目录不存在：

```shell
[root@linuxprobe ~]# [ -d /etc/fstab ]
[root@linuxprobe ~]# echo $?
1
```

再使用文件测试语句来判断/etc/fstab是否为一般文件，如果返回值为0，则代表文件存在，且为一般文件：

```shell
[root@linuxprobe ~]# [ -f /etc/fstab ]
[root@linuxprobe ~]# echo $?
0
```

判断与查询一定要敲两次命令吗？其实可以一次搞定。

逻辑语句用于对测试结果进行逻辑分析，根据测试结果可实现不同的效果。例如在Shell终端中逻辑“与”的运算符号是&&，它表示当前面的命令执行成功后才会执行它后面的命令，因此可以用来判断/dev/cdrom文件是否存在，若存在则输出Exist字样。

```shell
[root@linuxprobe ~]# [ -e /dev/cdrom ] && echo "Exist"
Exist
```

除了逻辑“与”外，还有逻辑“或”，它在Linux系统中的运算符号为||，表示当前面的命令执行失败后才会执行它后面的命令，因此可以用来结合系统环境变量USER来判断当前登录的用户是否为非管理员身份：

```shell
[root@linuxprobe ~]# echo $USER
root
[root@linuxprobe ~]# [ $USER = root ] || echo "user"
[root@linuxprobe ~]# su - linuxprobe 
[linuxprobe@linuxprobe ~]$ [ $USER = root ] || echo "user"
user
```

  

  整数比较运算符仅是对数字的操作，不能将数字与字符串、文件等内容一起操作，而且不能想当然地使用日常生活中的等号、大于号、小于号等来判断。因为等号与赋值命令符冲突，大于号和小于号分别与输出重定向命令符和输入重定向命令符冲突。因此一定要使用规范的整数比较运算符来进行操作。

###                    可用的整数比较运算符

| 操作符 | 作用           |
| ------ | -------------- |
| -eq    | 是否等于       |
| -ne    | 是否不等于     |
| -gt    | 是否大于       |
| -lt    | 是否小于       |
| -le    | 是否等于或小于 |
| -ge    | 是否大于或等于 |

接下来先测试一下10是否大于10以及10是否等于10（通过输出的返回值内容来判断）：

```
[root@linuxprobe ~]# [ 10 -gt 10 ]
[root@linuxprobe ~]# echo $?
1
[root@linuxprobe ~]# [ 10 -eq 10 ]
[root@linuxprobe ~]# echo $?
0
```

在free命令中，它能够用来获取当前系统正在使用及可用的内存量信息。接下来先使用free -m命令查看内存使用量情况（单位为MB），然后通过“grep Mem:”命令过滤出剩余内存量的行，再用awk '{print $4}'命令只保留第4列。

```shell
[root@linuxprobe ~]# free -m
              total        used        free      shared  buff/cache   available
Mem:           1966        1374         128          16         463         397
Swap:          2047          66        1981
[root@linuxprobe ~]# free -m | grep Mem:
Mem:           1966        1374         128          16         463         397
[root@linuxprobe ~]# free -m | grep Mem: | awk '{print $4}'
128
```

如果想把这个命令写入到Shell脚本中，那么建议把输出结果赋值给一个变量，以方便其他命令进行调用：

```shell
[root@linuxprobe ~]# FreeMem=`free -m | grep Mem: | awk '{print $4}'`
[root@linuxprobe ~]# echo $FreeMem 
128
```

上面用于获取内存可用量的命令以及步骤可能有些“超纲”了，如果不能理解领会也不用担心，接下来才是重点。我们使用整数运算符来判断内存可用量的值是否小于1024，若小于则会提示“Insufficient Memory”（内存不足）的字样：

```shell
[root@linuxprobe ~]# [ $FreeMem -lt 1024 ] && echo "Insufficient Memory"
Insufficient Memory
```

字符串比较语句用于判断测试字符串是否为空值，或两个字符串是否相同。它经常用来判断某个变量是否未被定义（即内容为空值），理解起来也比较简单。

###                     常见的字符串比较运算符

| 操作符 | 作用                   |
| ------ | ---------------------- |
| =      | 比较字符串内容是否相同 |
| !=     | 比较字符串内容是否不同 |
| -z     | 判断字符串内容是否为空 |

接下来通过判断String变量是否为空值，进而判断是否定义了这个变量：

```shell
[root@linuxprobe ~]# [ -z $String ]
[root@linuxprobe ~]# echo $?
0
```

再次尝试引入逻辑运算符来试一下。当用于保存当前语系的环境变量值LANG不是英语（en.US）时，则会满足逻辑测试条件并输出“Not en.US”（非英语）的字样：

```shell
[root@linuxprobe ~]# echo $LANG
en_US.UTF-8
[root@linuxprobe ~]# [ ! $LANG = "en.US" ] && echo "Not en.US"
Not en.US
```

## 3.1 **流程控制语句**

### 3.1.1 **if条件测试语句**

#### ）1 单条件

  if条件语句的单分支结构由if、then、fi关键词组成，而且只在条件成立后才执行预设的命令，相当于口语的“如果……那么……”。单分支的if语句属于最简单的一种条件判断结构

![单分支的if语句](./assets/单分支的if语句.png)

下面使用单分支的if条件语句来判断/media/cdrom目录是否存在，若不存在就创建这个目录，反之则结束条件判断和整个Shell脚本的执行。

```shell
[root@linuxprobe ~]# vim mkcdrom.sh
#!/bin/bash
DIR="/media/cdrom"
if [ ! -d $DIR ]
then    
        mkdir -p $DIR
fi 
```

#### ) 2 双分支 

 if条件语句的双分支结构由if、then、else、fi关键词组成，它进行一次条件匹配判断，如果与条件匹配，则去执行相应的预设命令；反之则去执行不匹配时的预设命令，相当于口语的“如果……那么……或者……那么……”。if条件语句的双分支结构也是一种很简单的判断结构

![双分支结构-1](./assets/双分支结构-1.png)

下面使用双分支的if条件语句来验证某台主机是否在线，然后根据返回值的结果，要么显示主机在线信息，要么显示主机不在线信息。这里的脚本主要使用ping命令来测试与对方主机的网络连通性，而Linux系统中的ping命令不像Windows一样尝试4次就结束，因此为了避免用户等待时间过长，需要通过-c参数来规定尝试的次数，并使用-i参数定义每个数据包的发送间隔，以及使用-W参数定义等待超时时间。

```shell
[root@linuxprobe ~]# vim chkhost.sh
#!/bin/bash
ping -c 3 -i 0.2 -W 3 $1 &> /dev/null
if [ $? -eq 0 ]
then
        echo "Host $1 is On-line."
else
        echo "Host $1 is Off-line."
fi
```

我们在之前用过$?变量，作用是显示上一次命令的执行返回值。若前面的那条语句成功执行，则$?变量会显示数字0，反之则显示一个非零的数字（可能为1，也可能为2，取决于系统版本）。因此可以使用整数比较运算符来判断$?变量是否为0，从而获知那条语句的最终判断情况。这里的服务器IP地址为192.168.10.10，我们来验证一下脚本的效果：

```shell
[root@linuxprobe ~]# bash chkhost.sh 192.168.10.10
Host 192.168.10.10 is On-line.
[root@linuxprobe ~]# bash chkhost.sh 192.168.10.20
Host 192.168.10.20 is Off-line.
```

#### ）3 多分支

if条件语句的多分支结构由if、then、else、elif、fi关键词组成，它进行多次条件匹配判断，这多次判断中的任何一项在匹配成功后都会执行相应的预设命令，相当于口语的“如果……那么……如果……那么……”。if条件语句的多分支结构是工作中最常使用的一种条件判断结构，尽管相对复杂但是更加灵活

下面使用多分支的if条件语句来判断用户输入的分数在哪个成绩区间内，然后输出如Excellent、Pass、Fail等提示信息。在Linux系统中，read是用来读取用户输入信息的命令，能够把接收到的用户输入信息赋值给后面的指定变量，-p参数用于向用户显示一些提示信息。

![多分支的if条件语句](./assets/多分支的if条件语句.png)

在下面的脚本示例中，只有当用户输入的分数大于等于85分且小于等于100分时，才输出Excellent字样；若分数不满足该条件（即匹配不成功），则继续判断分数是否大于等于70分且小于等于84分，如果是，则输出Pass字样；若两次都落空（即两次的匹配操作都失败了），则输出Fail字样：

```shell
[root@linuxprobe ~]# vim chkscore.sh
#!/bin/bash
read -p "Enter your score（0-100）：" GRADE
if [ $GRADE -ge 85 ] && [ $GRADE -le 100 ] ; then
        echo "$GRADE is Excellent"
elif [ $GRADE -ge 70 ] && [ $GRADE -le 84 ] ; then
        echo "$GRADE is Pass"
else
        echo "$GRADE is Fail" 
fi
[root@linuxprobe ~]# bash chkscore.sh
Enter your score（0-100）：88
88 is Excellent
[root@linuxprobe ~]# bash chkscore.sh 
Enter your score（0-100）：80
80 is Pass
```

下面执行该脚本。当用户输入的分数分别为30和200时，其结果如下：

```shell
[root@linuxprobe ~]# bash chkscore.sh  
Enter your score（0-100）：30
30 is Fail
[root@linuxprobe ~]# bash chkscore.sh
Enter your score（0-100）：200 
200 is Fail
```

为什么输入的分数为200时，依然显示Fail呢？原因很简单—没有成功匹配脚本中的两个条件判断语句，因此自动执行了最终的兜底策略。可见，这个脚本还不是很完美，建议读者自行完善这个脚本，使得用户在输入大于100或小于0的分数时，给予Error报错字样的提示。