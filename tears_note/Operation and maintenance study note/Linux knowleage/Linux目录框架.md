# Linux目录框架



## FHS

全名Filesystem Hierarchy standard，而将目录定义分成四种交互作用形态。

|                            | 可分享的(shareable)        | 不可分享的(unshareable) |
| -------------------------- | -------------------------- | ----------------------- |
| 不變的(static)             | /usr (软件防止处)          | /etc (設定檔)           |
| /opt (第三方合作软件)      | /boot (开机核心档)         |                         |
| 可變動的(variable)         | /var/mail (使用者郵件信箱) | /var/run (程序相關)     |
| /var/spool/news (新聞群組) | /var/lock (程序相關)       |                         |