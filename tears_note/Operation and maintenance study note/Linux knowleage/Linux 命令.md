

# Linux 命令



# 一、**常用系统工作命令**

## 1.1 Echo

用于在终端设备上输出字符串或变量提取后的值，语法格式为“echo [字符串] [$变量]”

其中$符号的意思是提取变量的实际值，以便后续的输出操作

eg：

```shell
#echo LinuxProbe.com
LinuxProbe.com//显示结果
echo $SHELL
/bin/bas
```

## 1.2 Date

### 如何显示

eg：

```shell
#date "+%Y-%m-&d" →2023-10-24
#date "+%H:%M:%S"→16：53：31
#date "+%Y-%m-%d %H:%M:%S" →2023-10-24 16：53：31
```

### 如何设置时间

```shell
//设置时区
#set-timezone Asia/Shanghai

//如果遇到这个问题则是系统同步时间
Automatic time synchronization is enable
//关闭操作流程
1、#set-ntp
2、#set-ntp false

```

## 1.3 Linux进程的类型

五大状态

R：Running 正常服务

S：stopped、Sleeping 停止服务

D：unstopped 不可中断

Z：zombie 僵尸进程 没有提供服务但是会消耗进程

T Stopped 停止

## 1.4 PS

ps -a（查看所有进程） -u（查看进程详细信息） -x（显示没有终端进行） 或者 ps -aux

pstree 层级关系显示（只能执行一次）

top（动态实时更新）

## 1.5 nice

nice命令用于调整进程的优先级，语法格式为“nice优先级数字 服务名称”

## 1.6 pidof

pidof命令用于查询某个指定服务进程的PID号码值，语法格式为“pidof [参数] 服务名称”

每次重启pid会更换，且pid值是唯一值

```shell
# pidof httpd
```

## 1.7 killall

对当前进程进行批量处理关闭

语法格式为“killall [参数] 服务名称”

eg:

```shell
#killall httpd
```



# 二、**系统状态检测命令**

## 2.1 ifconfig

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

## 2.2 uname

用于查看系统内核版本与系统架构等信息，英文全称为“unix name”，语法格式为“uname [-a]”

使用uname命令时，一般要固定搭配上-a参数来完整地查看当前系统的内核名称、主机名、内核发行版本、节点名、压制时间、硬件名称、硬件平台、处理器类型以及操作系统名称等信息

要查看当前系统版本的详细信息，则需要查看redhat-release文件

```shell
[root@linuxprobe ~]# uname -a
Linux linuxprobe.com 4.18.0-80.el8.x86_64 #1 SMP Wed Mar 13 12:02:46 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
[root@linuxprobe ~]# cat /etc/redhat-release
Red Hat Enterprise Linux release 8.0 (Ootpa)
```

## 2.3 **uptime**

用于查看系统的负载信息

平均负载值指的是系统在最近1分钟、5分钟、15分钟内的压力情况，负载值越低越好(时间从右到左依次减小即15-5-1)，建议负载值保持在1左右，在生产环境中不要超过5就好

```shell
[root@linuxprobe ~]# uptime
22:49:55 up 10 min, 1 users, load average: 0.01, 0.19, 0.18
```

## 2.4**free**

用于显示当前系统中内存的使用量信息，语法格式为“free [-h]”

如果不使用-h（易读模式）查看内存使用量情况，则默认以KB为单位。这样一来，服务器如果有几百GB的内存，则换算下来就会是一大长串的数字，真不利于阅读

```shell
[root@linuxprobe ~]# free -h
```

## 2.5 last

用于调取主机的被访记录，输入该命令后按回车键执行即可

此命令调用文件lastlog

```shell
#cat /var/log/lastlog
```

## 2.6 ping

用于测试主机之间的网络连通性，语法格式为“ping [参数] 主机地址”

| 参数 | 作用               |
| ---- | ------------------ |
| -c   | 总共发送次数       |
| -l   | 指定网卡名称       |
| -i   | 每次间隔时间（秒） |
| -W   | 最长等待时间（秒） |

## 2.7 tracepath

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

## 2.8 netstat

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

## 2.9 history命令

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

## 2.10 sosreport

用于收集系统配置及架构信息并输出诊断文档，输入该命令后按回车键执行即可。



# 三、**查找定位文件命令**

## 3.1pwd

用于显示用户当前所处的工作目录，英文全称为“print working directory”

```shell
[root@linuxprobe etc]# pwd
/etc
```

## 3.2cd

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

## 3.3 ls

用于显示目录中的文件信息，英文全称为“list”，语法格式为“ls [参数] [文件名称]”

![ls指令说明](./assets/WXWorkCapture_17246457382970-1724651842388-5.png)  

```shell
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

## 3.4 tree

tree命令用于以树状图的形式列出目录内容及结构，输入该命令后按回车键执行即可

tree命令则能够以树状图的形式列出目录内所有文件的结构

```shell
[root@linuxprobe ~]# tree
.
├── A
│   └── B
│       └── C
├── anaconda-ks.cfg
├── Desktop
├── Documents
├── Downloads
├── initial-setup-ks.cfg
├── Music
├── Pictures
├── Public
├── Templates
└── Videos
```

## 3.5 find 

find命令用于按照指定条件来查找文件所对应的位置，语法格式为“find [查找范围] 寻找条件”

 find命令中的参数以及作用

| 参数              | 作用                                                         |
| ----------------- | ------------------------------------------------------------ |
| -name             | 匹配名称                                                     |
| -perm             | 匹配权限（mode为完全匹配，-mode为包含即可）                  |
| -user             | 匹配所有者                                                   |
| -group            | 匹配所有组                                                   |
| -mtime -n +n      | 匹配修改内容的时间（-n指n天以内，+n指n天以前）               |
| -atime -n +n      | 匹配访问文件的时间（-n指n天以内，+n指n天以前）               |
| -ctime -n +n      | 匹配修改文件权限的时间（-n指n天以内，+n指n天以前）           |
| -nouser           | 匹配无所有者的文件                                           |
| -nogroup          | 匹配无所有组的文件                                           |
| -newer f1 !f2     | 匹配比文件f1新但比f2旧的文件                                 |
| -type b/d/c/p/l/f | 匹配文件类型（后面的字母依次表示块设备、目录、字符设备、管道、链接文件、文本文件） |
| -size             | 匹配文件的大小（+50KB为查找超过50KB的文件，而-50KB为查找小于50KB的文件） |
| -prune            | 忽略某个目录                                                 |
| -exec …… {}\;     | 后面可跟用于进一步处理搜索结果的命令                         |

根据文件系统层次标准（Filesystem Hierarchy Standard）协议，Linux系统中的配置文件会保存到/etc目录中。如果要想获取该目录中所有以host开头的文件列表，可以执行如下命令

```shell
[root@linuxprobe ~]# find /etc -name "host*" -print
```

## 3.6 locate

locate命令用于按照名称快速搜索文件所对应的位置，语法格式为“locate文件名称”

在使用locate命令时，先使用updatedb命令生成一个索引库文件，这个库文件的名字是/var/lib/mlocate/mlocate.db，后续在使用locate命令搜索文件时就是在该库中进行查找操作，速度会快很多。

```shell
[root@linuxprobe ~]# updatedb 
[root@linuxprobe ~]# ls -l /var/lib/mlocate/mlocate.db
-rw-r-----. 1 root slocate 2945917 Sep 13 17:54 /var/lib/mlocate/mlocate.db
```

使用locate命令搜索出所有包含“whereis”名称的文件所在的位置eg:

```shell
[root@linuxprobe ~]# locate whereis
/usr/bin/whereis
/usr/share/bash-completion/completions/whereis
/usr/share/man/man1/whereis.1.gz
```

## 3.7 whereis

用于按照名称快速搜索二进制程序（命令）、源代码以及帮助文件所对应的位置，语法格式为“whereis命令名称”

whereis命令也是基于updatedb命令所生成的索引库文件进行搜索，它与locate命令的区别是不关心那些相同名称的文件，仅仅是快速找到对应的命令文件及其帮助文件所在的位置

eg:

```shell
[root@linuxprobe ~]# whereis ls
ls: /usr/bin/ls /usr/share/man/man1/ls.1.gz /usr/share/man/man1p/ls.1p.gz
[root@linuxprobe ~]# whereis pwd
pwd: /usr/bin/pwd /usr/share/man/man1/pwd.1.gz /usr/share/man/man1p/pwd.1p.gz
```

## 3.8 which

用于按照指定名称快速搜索二进制程序（命令）所对应的位置，语法格式为“which命令名称”

which命令是在PATH变量所指定的路径中，按照指定条件搜索命令所在的路径。也就是说，如果我们既不关心同名文件（find与locate），也不关心命令所对应的源代码和帮助文件（whereis），仅仅是想找到命令本身所在的路径，那么这个which命令就合适了

```shell
[root@linuxprobe ~]# which locate
/usr/bin/locate
[root@linuxprobe ~]# which whereis
/usr/bin/whereis
```

# 四、**文本文件编辑命令**

## 4.1 cat

用于查看纯文本文件（内容较少的），英文全称为“concatenate”，语法格式为“cat [参数] 文件名称”

cat命令就是用于查看内容较少的纯文本文件

如果在查看文本内容时还想顺便显示行号的话，不妨在cat命令后面追加一个-n参数

```shell
[root@linuxprobe ~]# cat -n initial-setup-ks.cfg 
     1	#version=RHEL8
     2	# X Window System configuration information
     3	xconfig  --startxonboot
     4	# License agreement
     5	eula --agreed
     6	# Use graphical install
     7	graphical
     8	# Network information
     9	network  --bootproto=dhcp --device=ens160 --onboot=off --ipv6=auto --no-activate
    10	network  --bootproto=dhcp --hostname=localhost.localdomain
    11	repo --name="AppStream" --baseurl=file:///run/install/repo/AppStream
    12	ignoredisk --only-use=sda
    13	# Use CDROM installation media
    14	cdrom
    15	# Run the Setup Agent on first boot
    16	firstboot --enable
    17	# System services
………………省略部分输出信息………………
```

## 4.2 more

用于查看纯文本文件（内容较多的），语法格式为“more [参数] 文件名称”

因此对于长篇的文本内容，推荐使用more命令来查看。more命令会在最下面使用百分比的形式来提示您已经阅读了多少内容；还可以使用空格键或回车键向下翻页

eg:

```shell
[root@linuxprobe ~]# more initial-setup-ks.cfg 
#version=RHEL8
# X Window System configuration information
xconfig  --startxonboot
# License agreement
eula --agreed
# Use graphical install
graphical
# Network information
network  --bootproto=dhcp --device=ens160 --onboot=off --ipv6=auto --no-activate
network  --bootproto=dhcp --hostname=localhost.localdomain
repo --name="AppStream" --baseurl=file:///run/install/repo/AppStream
ignoredisk --only-use=sda
# Use CDROM installation media
cdrom
# Run the Setup Agent on first boot
firstboot --enable
# System services
services --disabled="chronyd"
# Keyboard layouts
keyboard --vckeymap=us --xlayouts='us'
# System language
lang en_US.UTF-8
--More--(41%)
```

## 4.3 head 

用于查看纯文本文件的前*N*行，语法格式为“head [参数] 文件名称”

如果只想查看文本中前10行的内容，该怎么办呢？head命令就能派上用场了

```shell
[root@linuxprobe ~]# head -n 10 initial-setup-ks.cfg 
#version=RHEL8
# X Window System configuration information
xconfig --startxonboot
# License agreement
eula --agreed
# Use graphical install
graphical
# Network information
network --bootproto=dhcp --device=ens160 --onboot=off --ipv6=auto --no-activate
network --bootproto=dhcp --hostname=localhost.localdomain
```

## 4.4 tail

用于查看纯文本文件的后*N*行或持续刷新文件的最新内容，语法格式为“tail [参数] 文件名称”

tail命令的操作方法与head命令非常相似，只需要执行“tail -n 10文件名称”命令就可以达到这样的效果

eg:

```
[root@linuxprobe ~]# tail -n 10 initial-setup-ks.cfg 
%addon com_redhat_subscription_manager 
%end
%addon ADDON_placeholder --disable --reserve-mb=auto
%end

%anaconda
pwpolicy root --minlen=6 --minquality=1 --notstrict --nochanges --notempty
pwpolicy user --minlen=6 --minquality=1 --notstrict --nochanges --emptyok
pwpolicy luks --minlen=6 --minquality=1 --notstrict --nochanges --notempty
%end
```

tail命令最强悍的功能是能够持续刷新一个文件的内容，当想要实时查看最新的日志文件时，这特别有用，此时的命令格式为“tail -f 文件名称”：

eg:

```
[root@linuxprobe ~]# tail -f /var/log/messages
Sep 15 00:14:01 localhost rsyslogd[1392]: imjournal: sd_journal_get_cursor() failed: Cannot assign requested address [v8.37.0-9.el8]
Sep 15 00:14:01 localhost rsyslogd[1392]: imjournal: journal reloaded... [v8.37.0-9.el8 try http://www.rsyslog.com/e/0 ]
Sep 15 00:14:01 localhost systemd[1]: Started update of the root trust anchor for DNSSEC validation in unbound.
Sep 15 00:14:01 localhost sssd[kcm][2764]: Shutting down
Sep 15 00:14:06 localhost systemd[1]: Starting SSSD Kerberos Cache Manager...
Sep 15 00:14:06 localhost systemd[1]: Started SSSD Kerberos Cache Manager.
Sep 15 00:14:06 localhost sssd[kcm][3989]: Starting up
Sep 15 00:14:26 localhost NetworkManager[1203]: <info> [1600100066.4675] audit: op="sleep-control" arg="off" pid=3990 uid=0 result="fail" reason="Already awake"
Sep 15 00:19:04 localhost org.gnome.Shell.desktop[2600]: Window manager warning: last_user_time (2361102) is greater than comparison timestamp (2361091). This most likely represents a buggy client sending inaccurate timestamps in messages such as _NET_ACTIVE_WINDOW. Trying to work around...
Sep 15 00:19:04 localhost org.gnome.Shell.desktop[2600]: Window manager warning: W14 (root@local) appears to be one of the offending windows with a timestamp of 2361102. Working around...
```

## 4.5  tr

用于替换文本内容中的字符，英文全称为“transform”，语法格式为“tr [原始字符] [目标字符]”

在很多时候，我们想要快速地替换文本中的一些词汇，又或者想把整个文本内容都进行替换。如果进行手工替换，难免工作量太大，尤其是需要处理大批量的内容时，进行手工替换更是不现实。这时，就可以先使用cat命令读取待处理的文本，然后通过管道符把这些文本内容传递给tr命令进行替换操作即可。例如，把某个文本内容中的英文全部替换为大写

eg:

```shell
[root@linuxprobe ~]# cat anaconda-ks.cfg | tr [a-z] [A-Z]
#VERSION=RHEL8
IGNOREDISK --ONLY-USE=SDA
AUTOPART --TYPE=LVM
# PARTITION CLEARING INFORMATION
CLEARPART --ALL --INITLABEL --DRIVES=SDA
# USE GRAPHICAL INSTALL
GRAPHICAL
REPO --NAME="APPSTREAM" --BASEURL=FILE:///RUN/INSTALL/REPO/APPSTREAM
# USE CDROM INSTALLATION MEDIA
CDROM
# KEYBOARD LAYOUTS
KEYBOARD --VCKEYMAP=US --XLAYOUTS='US'
# SYSTEM LANGUAGE
LANG EN_US.UTF-8
# NETWORK INFORMATION
NETWORK --BOOTPROTO=DHCP --DEVICE=ENS160 --ONBOOT=OFF --IPV6=AUTO --NO-ACTIVATE
NETWORK --HOSTNAME=LOCALHOST.LOCALDOMAIN
# ROOT PASSWORD
ROOTPW --ISCRYPTED $6$TTBUW5DKOPYQQ.VI$RMK9FCGHOJOQ2QAPRURTQM.QOK2NN3YFN/I4F/FALVGGGND9XOIYFBRXDN16WWIZIASJ0/CR06U66IPEOGLPJ.
# X WINDOW SYSTEM CONFIGURATION INFORMATION
XCONFIG --STARTXONBOOT
# RUN THE SETUP AGENT ON FIRST BOOT
FIRSTBOOT --ENABLE
# SYSTEM SERVICES
SERVICES --DISABLED="CHRONYD"
# SYSTEM TIMEZONE
TIMEZONE ASIA/SHANGHAI --ISUTC --NONTP
………………省略部分输出信息………………
```

## 4.6 wc

用于统计指定文本文件的行数、字数或字节数，英文全称为“word counts”，语法格式为“wc [参数] 文件名称”

​    wc命令中的参数以及作用

| 参数 | 作用         |
| ---- | ------------ |
| -l   | 只显示行数   |
| -w   | 只显示单词数 |
| -c   | 只显示字节数 |

在Linux系统中，/etc/passwd是用于保存所有用户信息的文件，要统计当前系统中有多少个用户，可以使用下面的命令来进行查询

```shell
[root@linuxprobe ~]# wc -l /etc/passwd
45 /etc/passwd
```

## 4.7 stat

用于查看文件的具体存储细节和时间等信息，英文全称为“status”，语法格式为“stat文件名称”

大家都知道，文件有一个修改时间。其实，除了修改时间之外，Linux系统中的文件包含3种时间状态，分别是Access Time（内容最后一次被访问的时间，简称为Atime），Modify Time（内容最后一次被修改的时间，简称为Mtime）以及Change Time（文件属性最后一次被修改的时间，简称为Ctime）。

下面使用state命令查看文件的这3种时间状态信息：

```shell
[root@linuxprobe ~]# stat anaconda-ks.cfg
  File: anaconda-ks.cfg
  Size: 1407      	Blocks: 8          IO Block: 4096   regular file
Device: fd00h/64768d	Inode: 35321091    Links: 1
Access: (0600/-rw-------)  Uid: (    0/    root)   Gid: (    0/    root)
Context: system_u:object_r:admin_home_t:s0
Access: 2020-07-21 05:16:52.347279499 +0800
Modify: 2020-07-21 05:09:16.421009316 +0800
Change: 2020-07-21 05:09:16.421009316 +0800
 Birth: -
```

## 4.8 grep 

用于按行提取文本内容，语法格式为“grep [参数] 文件名称”

grep命令两个最常用的参数：

> -n参数用来显示搜索到的信息的行号；
>
> -v参数用于反选信息（即没有包含关键词的所有信息行）。

   grep命令中的参数及其作用

| 参数 | 作用                                           |
| ---- | ---------------------------------------------- |
| -b   | 将可执行文件(binary)当作文本文件（text）来搜索 |
| -c   | 仅显示找到的行数                               |
| -i   | 忽略大小写                                     |
| -n   | 显示行号                                       |
| -v   | 反向选择——仅列出没有“关键词”的行               |

在Linux系统中，/etc/passwd文件保存着所有的用户信息，而一旦用户的登录终端被设置成/sbin/nologin，则不再允许登录系统，因此可以使用grep命令查找出当前系统中不允许登录系统的所有用户的信息

eg:

```shell
[root@linuxprobe ~]# grep /sbin/nologin /etc/passwd
bin:x:1:1:bin:/bin:/sbin/nologin
daemon:x:2:2:daemon:/sbin:/sbin/nologin
adm:x:3:4:adm:/var/adm:/sbin/nologin
lp:x:4:7:lp:/var/spool/lpd:/sbin/nologin
mail:x:8:12:mail:/var/spool/mail:/sbin/nologin
operator:x:11:0:operator:/root:/sbin/nologin
games:x:12:100:games:/usr/games:/sbin/nologin
………………省略部分输出过程信息………………
```



## 4.9 cut 

命令用于按“列”提取文本内容，语法格式为“cut [参数] 文件名称”

系统文件在保存用户数据信息时，每一项值之间是采用冒号来间隔的，先查看一下：

```shell
[root@linuxprobe ~]# head -n 2 /etc/passwd 
root:x:0:0:root:/root:/bin/bash 
bin:x:1:1:bin:/bin:/sbin/nologin
```

一般而言，按基于“行”的方式来提取数据是比较简单的，只需要设置好要搜索的关键词即可。但是如果按“列”搜索，不仅要使用-f参数设置需要查看的列数，还需要使用-d参数来设置间隔符号。

接下来使用下述命令尝试提取出passwd文件中的用户名信息，即提取以冒号（：）为间隔符号的第一列内容

eg:

```shell
[root@linuxprobe ~]# cut -d : -f 1 /etc/passwd
root
bin
daemon
adm
lp
sync
shutdown
halt
mail
operator
games
ftp
nobody
dbus
………………省略部分输出信息………………
```

## 4.10 diff

## 4.11 uniq

## 4.12 sort