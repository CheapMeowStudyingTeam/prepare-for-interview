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