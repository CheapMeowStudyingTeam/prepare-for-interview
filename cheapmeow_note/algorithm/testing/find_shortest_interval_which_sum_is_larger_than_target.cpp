#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/minimum-size-subarray-sum/description/

class Solution
{
public:
    int minSubArrayLen(int target, vector<int>& nums)
    {
        int left = 0, right = 0;
        int sum     = 0;
        int min_len = numeric_limits<int>::max();
        for (; right < nums.size(); right++)
        {
            sum += nums[right];
            if (sum >= target)
            {
                while (sum - nums[left] >= target)
                {
                    sum -= nums[left];
                    left++;
                }

                if (right - left + 1 < min_len)
                    min_len = right - left + 1;
            }
        }

        if (sum >= target)
            return min_len;
        else
            return 0;
    }
};

int main()
{
    Solution    sol;
    vector<int> test_arr {5, 1, 3, 5, 10, 7, 4, 9, 2, 8};
    int         len = sol.minSubArrayLen(15, test_arr);
    cout << len << endl;
}