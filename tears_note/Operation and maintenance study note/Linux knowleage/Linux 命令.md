# Linux 命令



# 一、**常用系统工作命令**

## 1、Echo

用于在终端设备上输出字符串或变量提取后的值，语法格式为“echo [字符串] [$变量]”

其中$符号的意思是提取变量的实际值，以便后续的输出操作

eg：

```shell
#echo LinuxProbe.com
LinuxProbe.com//显示结果
echo $SHELL
/bin/bas
```

## 2、Date

### 如何显示

eg：

```shell
#date "+%Y-%m-&d" →2023-10-24
#date "+%H:%M:%S"→16：53：31
#date "+%Y-%m-%d %H:%M:%S" →2023-10-24 16：53：31
```

如何设置时间

```shell
//设置时区
#set-timezone Asia/Shanghai

//如果遇到这个问题则是系统同步时间
Automatic time synchronization is enable
//关闭操作流程
1、#set-ntp
2、#set-ntp false

```

## 3、Linux进程的类型

五大状态

R：Running 正常服务

S：stopped、Sleeping 停止服务

D：unstopped 不可中断

Z：zombie 僵尸进程 没有提供服务但是会消耗进程

T Stopped 停止

## 4、PS

ps -a（查看所有进程） -u（查看进程详细信息） -x（显示没有终端进行） 或者 ps -aux

pstree 层级关系显示（只能执行一次）

top（动态实时更新）

## 5、nice

nice命令用于调整进程的优先级，语法格式为“nice优先级数字 服务名称”

## 6、pidof

pidof命令用于查询某个指定服务进程的PID号码值，语法格式为“pidof [参数] 服务名称”

每次重启pid会更换，且pid值是唯一值

```shell
# pidof httpd
```

## 7、killall

对当前进程进行批量处理关闭

语法格式为“killall [参数] 服务名称”

eg:

```shell
#killall httpd
```



# 二、**系统状态检测命令**

## 8、ipconfig

用于获取网卡配置与网络状态等信息，英文全称为“interface config”。

语法格式为“ifconfig [参数] [网络设备]”

主要查看的就是网卡名称、inet参数后面的IP地址、ether参数后面的网卡物理地址（又称为MAC地址），以及RX、TX的接收数据包与发送数据包的个数及累计流量

eg：

```shell
[root@linuxprobe ~]# ifconfig
ens160: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.10.10  netmask 255.255.255.0  broadcast 192.168.10.255
        inet6 fe80::c8f8:f5c5:8251:aeaa  prefixlen 64  scopeid 0x20
        ether 00:0c:29:7d:27:bf  txqueuelen 1000  (Ethernet)
        RX packets 304  bytes 33283 (32.5 KiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 91  bytes 11052 (10.7 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 376  bytes 31784 (31.0 KiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 376  bytes 31784 (31.0 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

virbr0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        ether 52:54:00:a2:89:54  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```

## 9、uname

用于查看系统内核版本与系统架构等信息，英文全称为“unix name”，语法格式为“uname [-a]”

使用uname命令时，一般要固定搭配上-a参数来完整地查看当前系统的内核名称、主机名、内核发行版本、节点名、压制时间、硬件名称、硬件平台、处理器类型以及操作系统名称等信息

要查看当前系统版本的详细信息，则需要查看redhat-release文件

```shell
[root@linuxprobe ~]# uname -a
Linux linuxprobe.com 4.18.0-80.el8.x86_64 #1 SMP Wed Mar 13 12:02:46 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
[root@linuxprobe ~]# cat /etc/redhat-release
Red Hat Enterprise Linux release 8.0 (Ootpa)
```

### 10、**uptime**

用于查看系统的负载信息

平均负载值指的是系统在最近1分钟、5分钟、15分钟内的压力情况，负载值越低越好(时间从右到左依次减小即15-5-1)，建议负载值保持在1左右，在生产环境中不要超过5就好

```shell
[root@linuxprobe ~]# uptime
22:49:55 up 10 min, 1 users, load average: 0.01, 0.19, 0.18
```

### 11、**free**

用于显示当前系统中内存的使用量信息，语法格式为“free [-h]”

如果不使用-h（易读模式）查看内存使用量情况，则默认以KB为单位。这样一来，服务器如果有几百GB的内存，则换算下来就会是一大长串的数字，真不利于阅读

```shell
[root@linuxprobe ~]# free -h
```

### 12、last

用于调取主机的被访记录，输入该命令后按回车键执行即可

此命令调用文件lastlog

```shell
#cat /var/log/lastlog
```

### 13、ping

用于测试主机之间的网络连通性，语法格式为“ping [参数] 主机地址”

| 参数 | 作用               |
| ---- | ------------------ |
| -c   | 总共发送次数       |
| -l   | 指定网卡名称       |
| -i   | 每次间隔时间（秒） |
| -W   | 最长等待时间（秒） |

### 14、tracepath

用于显示数据包到达目的主机时途中经过的所有路由信息，语法格式为“tracepath [参数] 域名”

当两台主机之间无法正常ping通时，要考虑两台主机之间是否有错误的路由信息，导致数据被某一台设备错误地丢弃。这时便可以使用tracepath命令追踪数据包到达目的主机时途中的所有路由信息，以分析是哪台设备出了问题。

eg:

```shell
[root@linuxprobe ~]# tracepath www.linuxprobe.com
 1?: [LOCALHOST]                                          pmtu 1500
 1:  no reply
 2:  11.223.0.189                                          5.954ms asymm  1 
 3:  11.223.0.14                                           6.256ms asymm  2 
 4:  11.220.159.62                                         3.313ms asymm  3 
 5:  116.251.107.13                                        1.841ms 
 6:  140.205.50.237                                        2.416ms asymm  5 
 7:  101.95.211.117                                        2.772ms 
 8:  101.95.208.45                                        40.839ms 
 9:  101.95.218.217                                       13.898ms asymm  8 
10:  202.97.81.162                                         8.113ms asymm  9 
11:  221.229.193.238                                      15.693ms asymm 10 
12:  no reply
13:  no reply
14:  no reply
15:  no reply
16:  no reply
17:  no reply
18:  no reply
```

就可以从11这个ip查找相关原因。

### 15、netstat

用于显示如网络连接、路由表、接口状态等的网络相关信息，英文全称为“network status”，语法格式为“netstat [参数]”

netstat命令中的参数以及作用

| 参数 | 作用                     |
| ---- | ------------------------ |
| -a   | 显示所有连接中的Socket   |
| -p   | 显示正在使用的Socket信息 |
| -t   | 显示TCP协议的连接状态    |
| -u   | 显示UDP协议的连接状态    |
| -n   | 使用IP地址，不使用域名   |
| -l   | 仅列出正在监听的服务状态 |
| -i   | 显示网卡列表信息         |
| -r   | 显示路由表信息           |

eg：

```shell
[root@linuxprobe ~]# netstat -a
Active Internet connections (servers and established)
Proto Recv-Q Send-Q Local Address           Foreign Address         State      
tcp        0      0 0.0.0.0:ssh             0.0.0.0:*               LISTEN     
tcp        0      0 localhost:ipp           0.0.0.0:*               LISTEN     
tcp        0      0 0.0.0.0:sunrpc          0.0.0.0:*               LISTEN     
tcp6       0      0 [::]:ssh                [::]:*                  LISTEN     
tcp6       0      0 localhost:ipp           [::]:*                  LISTEN     
tcp6       0      0 [::]:sunrpc             [::]:*                  LISTEN     
udp        0      0 0.0.0.0:bootps          0.0.0.0:*                          
udp        0      0 0.0.0.0:sunrpc          0.0.0.0:*                          
udp        0      0 0.0.0.0:mdns            0.0.0.0:*                          
udp        0      0 0.0.0.0:37396           0.0.0.0:*                          
udp6       0      0 [::]:sunrpc             [::]:*                             
udp6       0      0 [::]:mdns               [::]:*                             
udp6       0      0 [::]:38541              [::]:*       
```

### 16、history命令

用于显示执行过的命令历史，语法格式为“history [-c]”

执行history命令能显示出当前用户在本地计算机中执行过的最近1000条命令记录。如果觉得1000不够用，可以自定义/etc/profile文件中的HISTSIZE变量值。在使用history命令时，可以使用-c参数清空所有的命令历史记录。还可以使用“!编码数字”的方式来重复执行某一次的命令

```shell
[root@linuxprobe ~]# history
1 ifconfig
2 uname -a
3 cat /etc/redhat-release
4 uptime
5 free -h
6 who
7 last
8 ping -c 192.168.10.10
9 ping -c 192.168.10.20
10 tracepath www.linuxprobe.com
11 netstat -a
12 netstat -i
13 history
[root@linuxprobe ~]# !3
cat /etc/redhat-release
Red Hat Enterprise Linux release 8.0 (Ootpa)
```

清空当前用户在本机上执行的Linux命令历史记录信息，可执行如下命令

```shell
# history -c
```

### 17、sosreport

用于收集系统配置及架构信息并输出诊断文档，输入该命令后按回车键执行即可。



## **查找定位文件命令**

### 18、pwd

用于显示用户当前所处的工作目录，英文全称为“print working directory”

```shell
[root@linuxprobe etc]# pwd
/etc
```

### 19、cd

用于切换当前的工作路径，英文全称为“change directory”，语法格式为“cd [参数] [目录]”

用“cd -”命令返回到上一次所处的目录，使用“cd ..”命令进入上级目录，以及使用“cd ~”命令切换到当前用户的家目录，抑或使用“cd ~username”命令切换到其他用户的家目录

返回到上一次的目录（即/etc目录）

```
[root@linuxprobe bin]# cd -
/etc
[root@linuxprobe etc]#
```

可以通过下面的命令快速切换到用户的家目录：

```shell
[root@linuxprobe etc]# cd ~
[root@linuxprobe ~]#
```

### 20.ls

用于显示目录中的文件信息，英文全称为“list”，语法格式为“ls [参数] [文件名称]”

![WXWorkCapture_17246457382970](C:\Users\fanghaofu\AppData\Local\Temp\WXWorkCapture_17246457382970.png)

```
[root@linuxprobe ~]# ls -al
total 48
dr-xr-x---. 15 root root 4096 Jul 24 06:33 .
dr-xr-xr-x. 17 root root  224 Jul 21 05:04 ..
-rw-------.  1 root root 1407 Jul 21 05:09 anaconda-ks.cfg
-rw-------.  1 root root  335 Jul 24 06:33 .bash_history
-rw-r--r--.  1 root root   18 Aug 13  2018 .bash_logout
-rw-r--r--.  1 root root  176 Aug 13  2018 .bash_profile
-rw-r--r--.  1 root root  176 Aug 13  2018 .bashrc
drwx------. 10 root root  230 Jul 21 05:19 .cache
drwx------. 11 root root  215 Jul 24 06:27 .config
-rw-r--r--.  1 root root  100 Aug 13  2018 .cshrc
drwx------.  3 root root   25 Jul 21 05:16 .dbus
drwxr-xr-x.  2 root root    6 Jul 21 05:19 Desktop
drwxr-xr-x.  2 root root    6 Jul 21 05:19 Documents
drwxr-xr-x.  2 root root    6 Jul 21 05:19 Downloads
-rw-------.  1 root root   16 Jul 21 05:19 .esd_auth
-rw-------.  1 root root  620 Jul 24 06:26 .ICEauthority
-rw-r--r--.  1 root root 1562 Jul 21 05:18 initial-setup-ks.cfg
drwx------.  3 root root   19 Jul 21 05:19 .local
drwxr-xr-x.  2 root root    6 Jul 21 05:19 Music
drwxr-xr-x.  2 root root    6 Jul 21 05:19 Pictures
drwxr-----.  3 root root   19 Jul 21 05:19 .pki
drwxr-xr-x.  2 root root    6 Jul 21 05:19 Public
-rw-r--r--.  1 root root  129 Aug 13  2018 .tcshrc
drwxr-xr-x.  2 root root    6 Jul 21 05:19 Templates
drwxr-xr-x.  2 root root    6 Jul 21 05:19 Videos
-rw-------.  1 root root 3235 Jul 24 06:32 .viminfo
```