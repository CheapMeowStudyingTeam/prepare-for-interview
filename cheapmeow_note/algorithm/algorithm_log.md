- [刷题记录](#刷题记录)
  - [不要过度设计](#不要过度设计)
  - [排列组合以遍历索引为起点](#排列组合以遍历索引为起点)
  - [计数排序原理：记录每个元素出现的次数，也可以用在别的地方](#计数排序原理记录每个元素出现的次数也可以用在别的地方)

# 刷题记录

## 不要过度设计

1.
万万没想到之聪明的编辑
我叫王大锤，是一家出版社的编辑。我负责校对投稿来的英文稿件，这份工作非常烦人，因为每天都要去修正无数的拼写错误。但是，优秀的人总能在平凡的工作中发现真理。我发现一个发现拼写错误的捷径：

1. 三个同样的字母连在一起，一定是拼写错误，去掉一个的就好啦：比如 helllo -> hello
2. 两对一样的字母（AABB型）连在一起，一定是拼写错误，去掉第二对的一个字母就好啦：比如 helloo -> hello
3. 上面的规则优先“从左到右”匹配，即如果是AABBCC，虽然AABB和BBCC都是错误拼写，应该优先考虑修复AABB，结果为AABCC

我特喵是个天才！我在蓝翔学过挖掘机和程序设计，按照这个原理写了一个自动校对器，工作效率从此起飞。用不了多久，我就会出任CEO，当上董事长，迎娶白富美，走上人生巅峰，想想都有点小激动呢！
……
万万没想到，我被开除了，临走时老板对我说： “做人做事要兢兢业业、勤勤恳恳、本本分分，人要是行，干一行行一行。一行行行行行；要是不行，干一行不行一行，一行不行行行不行。” 我现在整个人红红火火恍恍惚惚的……

请听题：请实现大锤的自动校对程序

数据范围： 
1
≤
n
≤
50
 
1≤n≤50  ，每个用例的字符串长度满足 
1
≤
l
≤
1000
 
1≤l≤1000 
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32M，其他语言64M
输入描述：
第一行包括一个数字N，表示本次用例包括多少个待校验的字符串。

后面跟随N行，每行为一个待校验的字符串。
输出描述：
N行，每行包括一个被修复后的字符串。

示例1
输入例子：
2
helloo
wooooooow
输出例子：
hello
woow

示例2
输入例子：
1
nowcoder

我一开始的想法是

```cpp
#include <array>
#include <iostream>
using namespace std;

std::string formatStr(const std::string& input) {
    if (input.length() <= 2)
        return input;

    int output_length = 2;
    std::string output(input.length(), 'a');
    for (int i = 0; i < 2; i++)
        output[i] = input[i];

    int ring_begin = 0;
    int ring_end = 0;
    constexpr int ring_length = 4;
    std::array<char, ring_length> ring_window;
    constexpr char invalid_char = '*';

    for (int i = 0; i < 3; i++)
        ring_window[i] = input[i];

    ring_window[3] = invalid_char;
    ring_end = 2;

    for (int i = 2; i < input.length(); i++) {
        ring_window[ring_end] = input[i];

        ring_end++;
        ring_end %= ring_length;

        if (ring_end == ring_begin) {
            ring_begin++;
            ring_begin %= ring_length;
        }

        // 三个同样的字母连在一起，一定是拼写错误，去掉一个
        if (ring_window[ring_begin] == ring_window[(ring_begin + 1) % ring_length] &&
            ring_window[(ring_begin + 1) % ring_length] == ring_window[(ring_begin + 2) % ring_length])
        {
            ring_end--;
            ring_end %= ring_length;
        }
        else 
        {
            
        }
    }

    return output;
}

int main() {
    int n = 0;
    cin >> n;

    for (int i = 0; i < n; i++) {
        std::string str;
        cin >> str;

        cout << formatStr(str);
    }

    return 0;
}
// 64 位输出请用 printf("%lld")
```

写了一个开头就觉得很复杂了

检查一个窗口因为我觉得像滑动窗口，于是这么写了，但是感觉就是很麻烦

实际上一个简单的模拟题啊！不维护窗口直接遍历就可以啊

我把我这个窗口的想法扔掉，直接遍历，不就行了吗

```cpp
#include <array>
#include <iostream>
using namespace std;

std::string formatStr(const std::string& input) {
    if (input.length() <= 2)
        return input;

    int output_length = 2;
    std::string output(input.length(), 'a');
    for (int i = 0; i < 2; i++)
        output[i] = input[i];

    for (int i = 2; i < input.length(); i++) {
        if (output[output_length - 1] == output[output_length - 2] &&
                output[output_length - 1] == input[i]) {
            continue;
        }

        if (output_length >= 3) {
            if (output[output_length - 2] == output[output_length - 3]
                    && output[output_length - 1] == input[i]) {
                continue;
            }
        }

        output[output_length++] = input[i];
    }

    output = output.substr(0, output_length);

    return output;
}

int main() {
    int n = 0;
    cin >> n;

    for (int i = 0; i < n; i++) {
        std::string str;
        cin >> str;

        cout << formatStr(str);
        cout << endl;
    }

    return 0;
}
// 64 位输出请用 printf("%lld")
```

## 排列组合以遍历索引为起点

2.
万万没想到之抓捕孔连顺
我叫王大锤，是一名特工。我刚刚接到任务：在字节跳动大街进行埋伏，抓捕恐怖分子孔连顺。和我一起行动的还有另外两名特工，我提议

1. 我们在字节跳动大街的 N 个建筑中选定 3 个埋伏地点。
2. 为了相互照应，我们决定相距最远的两名特工间的距离不超过 D 。

我特喵是个天才! 经过精密的计算，我们从X种可行的埋伏方案中选择了一种。这个方案万无一失，颤抖吧，孔连顺！
……
万万没想到，计划还是失败了，孔连顺化妆成小龙女，混在cosplay的队伍中逃出了字节跳动大街。只怪他的伪装太成功了，就是杨过本人来了也发现不了的！

请听题：给定 N（可选作为埋伏点的建筑物数）、 D（相距最远的两名特工间的距离的最大值）以及可选建筑的坐标，计算在这次行动中，大锤的小队有多少种埋伏选择。
注意：
1. 两个特工不能埋伏在同一地点
2. 三个特工是等价的：即同样的位置组合( A , B , C ) 只算一种埋伏方法，不能因“特工之间互换位置”而重复使用


数据范围： 
0
<
n
,
d
≤
1
0
6
 
0<n,d≤10 
6
  
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 128M，其他语言256M
输入描述：
第一行包含空格分隔的两个数字 N和D(1 ≤ N ≤ 1000000; 1 ≤ D ≤ 1000000)

第二行包含N个建筑物的的位置，每个位置用一个整数（取值区间为[0, 1000000]）表示，从小到大排列（将字节跳动大街看做一条数轴）
输出描述：
一个数字，表示不同埋伏方案的数量。结果可能溢出，请对 99997867 取模

示例1
输入例子：
4 3
1 2 3 4
输出例子：
4
例子说明：
可选方案 (1, 2, 3), (1, 2, 4), (1, 3, 4), (2, 3, 4)   

示例2
输入例子：
5 19
1 10 20 30 50
输出例子：
1
例子说明：
可选方案 (1, 10, 20)   

示例3
输入例子：
2 100
1 102
输出例子：
0

我一开始的想法是

```cpp
#include <array>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    constexpr int k_member_num = 3;

    long long pos_num, max_dis;
    cin >> pos_num >> max_dis;
    std::vector<long long> coord(pos_num);

    for (long long i = 0; i < pos_num; i++) {
        cin >> coord[i];
    }

    sort(coord.begin(), coord.end());

    long long total_result = 0;

    long long left_index = 0;
    long long right_index = 0;

    while (left_index < pos_num - 2) {
        // 找到可行区间
        for (; right_index < pos_num; right_index++) {
            if (coord[right_index] - coord[left_index] > max_dis) {
                right_index--;
                break;
            }
        }

        if(right_index == pos_num)
        {
            right_index = pos_num - 1;
        }
        // 此时可能 left_index == right_index

        long long interval_length = right_index - left_index + 1;
    
        // 可选择的点位不足时，跳过
        if (interval_length < k_member_num) {
            left_index++;
            continue;
        }

        long long current_result = interval_length * (interval_length - 1) *
                             (interval_length - 2) / 3 / 2;
        current_result %= 99997867;

        total_result += current_result;
        total_result %= 99997867;

        left_index = right_index - 1;
    }
    cout << total_result;
    return 0;
}
// 64 位输出请用 printf("%lld")
```

但是不知道为什么算少了

看了别人的，别人是固定遍历变量为起点，然后取区间里面的另外两个人，所以是 C_n^2

于是改为

```cpp
#include <array>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    constexpr int k_member_num = 3;

    long long pos_num, max_dis;
    cin >> pos_num >> max_dis;
    std::vector<long long> coord(pos_num);

    for (long long i = 0; i < pos_num; i++) {
        cin >> coord[i];
    }

    long long total_result = 0;

    long long left_index = 0;
    long long right_index = 0;

    while (left_index < pos_num - 2) {
        // 找到可行区间
        for (; right_index < pos_num; right_index++) {
            if (coord[right_index] - coord[left_index] > max_dis) {
                right_index--;
                break;
            }
        }

        if (right_index == pos_num) {
            right_index = pos_num - 1;
        }
        // 此时可能 left_index == right_index

        long long interval_length_minus_one = right_index - left_index;
        left_index++;

        // 可选择的点位不足时，跳过
        if (interval_length_minus_one < k_member_num - 1) {
            continue;
        }

        long long current_result = interval_length_minus_one * (interval_length_minus_one - 1) / 2;
        current_result %= 99997867;

        total_result += current_result;
        total_result %= 99997867;
    }
    cout << total_result;
    return 0;
}
// 64 位输出请用 printf("%lld")
```

就好了，为什么呢

## 计数排序原理：记录每个元素出现的次数，也可以用在别的地方

题目：雀魂启动！

小包最近迷上了一款叫做雀魂的麻将游戏，但是这个游戏规则太复杂，小包玩了几个月了还是输多赢少。
于是生气的小包根据游戏简化了一下规则发明了一种新的麻将，只留下一种花色，并且去除了一些特殊和牌方式（例如七对子等），具体的规则如下：

总共有36张牌，每张牌是1~9。每个数字4张牌。
你手里有其中的14张牌，如果这14张牌满足如下条件，即算作和牌
14张牌中有2张相同数字的牌，称为雀头。
除去上述2张牌，剩下12张牌可以组成4个顺子或刻子。顺子的意思是递增的连续3个数字牌（例如234,567等），刻子的意思是相同数字的3个数字牌（例如111,777）

例如：
1 1 1 2 2 2 6 6 6 7 7 7 9 9 可以组成1,2,6,7的4个刻子和9的雀头，可以和牌
1 1 1 1 2 2 3 3 5 6 7 7 8 9 用1做雀头，组123,123,567,789的四个顺子，可以和牌
1 1 1 2 2 2 3 3 3 5 6 7 7 9 无论用1 2 3 7哪个做雀头，都无法组成和牌的条件。

现在，小包从36张牌中抽取了13张牌，他想知道在剩下的23张牌中，再取一张牌，取到哪几种数字牌可以和牌。

解析：

这里有三个点

第一个是对偶问题：缺了一个东西来满足条件 = 加上这个东西看看能不能满足条件

第二个是递归问题：递归每种刻子和顺子的情况，也就是对于刻子，111, 222, ..., 999 可以递归，对于顺子，123, 234, ..., 789 可以递归

第三个是转化数据表达形式：n 张值为 1~9 的牌 = 长度为 9 的数组，索引 i 表示值为 i 的牌有多少张