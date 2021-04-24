#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <algorithm>
#include <math.h>
#include <sstream>

using namespace std;

//1：两数之和
vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> store;
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i)
    {
        if (store.count(target - nums[i]))
        {
            res.push_back(store[target - nums[i]]);
            res.push_back(i);
            return res;
        }
        else
        {
            store[nums[i]] = i;
        }
    }
    return res;
}

//15：三数之和
vector<vector<int>> threeSum(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    int length = nums.size();
    vector<vector<int>> res;
    if (length <= 2)
    {
        return res;
    }
    for (int i = 0; i < length - 2; ++i)
    {
        if (nums[i] > 0 || nums[i] + nums[i + 1] + nums[i + 2] > 0)
        {
            return res;
        }
        else if (i && nums[i] == nums[i - 1])
        {
            continue;
        }
        int left = i + 1, right = length - 1;
        while (left < right)
        {
            int temp = nums[i] + nums[left] + nums[right];
            if (temp == 0)
            {
                res.push_back({nums[i], nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1])
                {
                    ++left;
                }
                ++left;
                while (left < right && nums[right - 1] == nums[right])
                {
                    --right;
                }
                --right;
            }
            else if (temp < 0)
            {
                while (left < right && nums[left] == nums[left + 1])
                {
                    ++left;
                }
                ++left;
            }
            else
            {
                while (left < right && nums[right - 1] == nums[right])
                {
                    --right;
                }
                --right;
            }
        }
    }
    return res;
}

//16：最接近的三数之和
int threeSumClosest(vector<int> &nums, int target)
{
    sort(nums.begin(), nums.end());
    int length = nums.size();
    if (length <= 2)
    {
        return 0;
    }
    int res = nums[0] + nums[1] + nums[2];
    for (int i = 0; i < length - 2; ++i)
    {
        if (nums[i] + nums[i + 1] + nums[i + 2] >= res && res > target)
        {
            return res;
        }
        else if (nums[i] + nums[length - 2] + nums[length - 1] <= res && res < target)
        {
            continue;
        }
        else if (i && nums[i] == nums[i - 1])
        {
            continue;
        }
        int left = i + 1, right = length - 1;
        while (left < right)
        {
            int temp = nums[i] + nums[left] + nums[right];
            if (temp > target)
            {
                --right;
            }
            else if (temp < target)
            {
                ++left;
            }
            else
            {
                return target;
            }
            if (abs(temp - target) < abs(res - target))
            {
                res = temp;
            }
        }
    }
    return res;
}

//18；四数之和
vector<vector<int>> fourSum(vector<int> &nums, int target)
{
    int length = nums.size();
    vector<vector<int>> res;
    if (length <= 3)
    {
        return res;
    }
    sort(nums.begin(), nums.end());
    for (int i = 0; i < length - 3; ++i)
    {
        if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
        {
            return res;
        }
        else if (i && nums[i] == nums[i - 1])
        {
            continue;
        }
        else if (nums[i] + nums[length - 3] + nums[length - 2] + nums[length - 1] < target)
        {
            continue;
        }
        for (int j = i + 1; j < length - 2; ++j)
        {
            if (j > i + 1 && nums[j] == nums[j - 1])
            {
                continue;
            }
            else if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
            {
                break;
            }
            else if (nums[i] + nums[j] + nums[length - 2] + nums[length - 1] < target)
            {
                continue;
            }
            int left = j + 1, right = length - 1;
            while (left < right)
            {
                int temp = nums[i] + nums[j] + nums[left] + nums[right];
                if (temp < target)
                {
                    ++left;
                    while (left < right && nums[left] == nums[left - 1])
                    {
                        ++left;
                    }
                }
                else if (temp > target)
                {
                    --right;
                    while (left < right && nums[right] == nums[right + 1])
                    {
                        --right;
                    }
                }
                else
                {
                    res.push_back({nums[i], nums[j], nums[left], nums[right]});
                    ++left;
                    while (left < right && nums[left] == nums[left - 1])
                    {
                        ++left;
                    }
                    --right;
                    while (left < right && nums[right] == nums[right + 1])
                    {
                        --right;
                    }
                }
            }
        }
    }
    return res;
}

//454：四数相加Ⅱ
int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D)
{
    unordered_map<int, int> store;
    int res = 0;
    for (const auto &a : A)
    {
        for (const auto &b : B)
        {
            if (store.count(a + b))
            {
                ++store[a + b];
            }
            else
            {
                store[a + b] = 1;
            }
        }
    }
    for (const auto &c : C)
    {
        for (const auto &d : D)
        {
            if (store.count(-c - d))
            {
                res += store[-c - d];
            }
        }
    }
    return res;
}

//7：整数翻转
int reverse(int x)
{
    bool flag = x >= 0 ? true : false;
    if (x == INT_MIN)
    {
        return 0;
    }
    x = x < 0 ? -x : x;
    int res = 0;
    while (x)
    {
        if (res > INT_MAX / 10 || (res == INT_MAX / 10 && x > 8) || (res == INT_MAX / 10 && x == 8 && flag))
        {
            return 0;
        }
        res = res * 10 + x % 10;
        x /= 10;
    }
    return flag ? res : -res;
}

//9：回文数
bool isPalindrome(int x)
{
    if (x < 0)
    {
        return false;
    }
    else if (x < 10)
    {
        return true;
    }
    string s = to_string(x);
    for (int i = 0; i < s.size() >> 1; ++i)
    {
        if (s[i] != s[s.size() - 1 - i])
        {
            return false;
        }
    }
    return true;
}

//172：阶乘后的零
int trailingZeroes(int n)
{
    int res = 0;
    while (n)
    {
        n /= 5;
        res += n;
    }
    return res;
}

//202：快乐数
int getNext(int n)
{
    int m = 0;
    while (n)
    {
        m += (n % 10) * (n % 10);
        n /= 10;
    }
    return m;
}
bool isHappy(int n)
{
    while (n > 1)
    {
        n = getNext(n);
        if (n == 4)
        {
            return false;
        }
    }
    return true;
}

//1399：统计最大组的数目
int countSum(int n)
{
    int res = 0;
    while (n)
    {
        res += n % 10;
        n /= 10;
    }
    return res;
}
int countLargestGroup(int n)
{
    vector<int> store(37, 0);
    for (int i = 1; i <= n; ++i)
    {
        ++store[countSum(i)];
    }
    int myMax = 0, res = 0;
    for (int i = 1; i <= 36; ++i)
    {
        if (store[i] > myMax)
        {
            myMax = store[i];
            res = 1;
        }
        else if (store[i] == myMax)
        {
            ++res;
        }
    }
    return res;
}

//8：字符串转换整数 (atoi)
// int myAtoi(string str)
// {
//     long long res = 0;
//     bool flag = false;
//     unordered_map<string, vector<string>> mytable =
//         {
//             {"start", {"start", "signed", "in_number", "end"}},
//             {"signed", {"end", "end", "in_number", "end"}},
//             {"in_number", {"end", "end", "in_number", "end"}},
//             {"end", {"end", "end", "end", "end"}}};
//     string state = "start";
//     for (int i = 0; i < str.size(); ++i)
//     {
//         if (isspace(str[i]))
//         {
//             state = mytable[state][0];
//         }
//         else if (str[i] == '+' || str[i] == '-')
//         {
//             state = mytable[state][1];
//         }
//         else if (isdigit(str[i]))
//         {
//             state = mytable[state][2];
//         }
//         else
//         {
//             state = mytable[state][3];
//         }
//         if (state == "signed" && str[i] == '-')
//         {
//             flag = true;
//         }
//         else if (state == "in_number")
//         {
//             if (res > (long long)INT_MAX)
//             {
//                 return flag ? INT_MIN : INT_MAX;
//             }
//             res = res * 10 + str[i] - '0';
//         }
//         else if (state == "end")
//         {
//             return flag ? max(-res, (long long)INT_MIN) : min(res, (long long)INT_MAX);
//         }
//     }
//     return flag ? max(-res, (long long)INT_MIN) : min(res, (long long)INT_MAX);
// }
int myAtoi(string str)
{
    int res = 0;
    bool flag = false;
    int index = 0;
    while (index < str.size() && str[index] == ' ')
    {
        ++index;
    }
    if (index < str.size() && (str[index] == '+' || str[index] == '-'))
    {
        if (str[index] == '-')
        {
            flag = true;
        }
        ++index;
    }
    while (index < str.size() && str[index] >= '0' && str[index] <= '9')
    {
        if (res > INT_MAX / 10 || (res == INT_MAX / 10 && str[index] > '7'))
        {
            return flag ? INT_MIN : INT_MAX;
        }
        res = res * 10 + str[index] - '0';
        ++index;
    }
    return flag ? -res : res;
}

//12：整数转罗马数字
string intToRoman(int num)
{
    int intArray[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string romanArray[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    string res;
    for (int i = 0; i < 13; ++i)
    {
        int temp = num / intArray[i];
        while (temp--)
        {
            res.insert(res.size(), romanArray[i]);
        }
        num %= intArray[i];
        if (num == 0)
        {
            return res;
        }
    }
    return res;
}

//13：罗马数字转整数
int romanToInt(string s)
{
    int res = 0, i = 0;
    while (i < s.size())
    {
        switch (s[i])
        {
        case 'M':
        {
            res += 1000;
            ++i;
            break;
        }
        case 'D':
        {
            res += 500;
            ++i;
            break;
        }
        case 'L':
        {
            res += 50;
            ++i;
            break;
        }
        case 'V':
        {
            res += 5;
            ++i;
            break;
        }
        case 'C':
        {
            if (i + 1 < s.size() && s[i + 1] == 'M')
            {
                res += 900;
                i += 2;
            }
            else if (i + 1 < s.size() && s[i + 1] == 'D')
            {
                res += 400;
                i += 2;
            }
            else
            {
                res += 100;
                ++i;
            }
            break;
        }
        case 'X':
        {
            if (i + 1 < s.size() && s[i + 1] == 'C')
            {
                res += 90;
                i += 2;
            }
            else if (i + 1 < s.size() && s[i + 1] == 'L')
            {
                res += 40;
                i += 2;
            }
            else
            {
                res += 10;
                ++i;
            }
            break;
        }
        case 'I':
        {
            if (i + 1 < s.size() && s[i + 1] == 'X')
            {
                res += 9;
                i += 2;
            }
            else if (i + 1 < s.size() && s[i + 1] == 'V')
            {
                res += 4;
                i += 2;
            }
            else
            {
                res += 1;
                ++i;
            }
            break;
        }
        }
    }
    return res;
}

//最大公因数
int gcd(int a, int b)
{
    return !b ? a : gcd(b, a % b);
}
//最小公倍数
int lcm(int a, int b)
{
    int temp = gcd(a, b);
    return a * b / temp;
}
//914：卡牌分组
bool hasGroupsSizeX(vector<int> &deck)
{
    unordered_map<int, int> store;
    if (deck.size() <= 1)
    {
        return false;
    }
    for (int i = 0; i < deck.size(); ++i)
    {
        if (store.count(deck[i]))
        {
            ++store[deck[i]];
        }
        else
        {
            store[deck[i]] = 1;
        }
    }
    int res = 0;
    for (auto iter = store.begin(); iter != store.end(); ++iter)
    {
        if (iter == store.begin())
        {
            res = iter->second;
        }
        else
        {
            res = gcd(res, iter->second);
        }
        if (res < 2)
        {
            return false;
        }
    }
    return res >= 2;
}

//315：计算右侧小于当前元素的个数
void merge(vector<int> &nums, vector<int> &store, vector<int> &index, vector<int> &storeIndex, vector<int> &res, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int middle = (left + right) >> 1;
    merge(nums, store, index, storeIndex, res, left, middle);
    merge(nums, store, index, storeIndex, res, middle + 1, right);
    int l = left, r = middle + 1, lr = left;
    while (l <= middle && r <= right)
    {
        if (nums[l] <= nums[r])
        {
            storeIndex[lr] = index[l];
            res[index[l]] += r - middle - 1;
            store[lr++] = nums[l++];
        }
        else
        {
            storeIndex[lr] = index[r];
            store[lr++] = nums[r++];
        }
    }
    while (l <= middle)
    {
        storeIndex[lr] = index[l];
        res[index[l]] += r - middle - 1;
        store[lr++] = nums[l++];
    }
    while (r <= right)
    {
        storeIndex[lr] = index[r];
        store[lr++] = nums[r++];
    }
    for (int i = left; i <= right; ++i)
    {
        nums[i] = store[i];
        index[i] = storeIndex[i];
    }
    return;
}
vector<int> countSmaller(vector<int> &nums)
{
    int length = nums.size();
    vector<int> index(length, 0);
    for (int i = 1; i < length; ++i)
    {
        index[i] = i;
    }
    vector<int> store(length, 0);
    vector<int> storeIndex(length, 0);
    vector<int> res(length, 0);
    merge(nums, store, index, storeIndex, res, 0, length - 1);
    return res;
}

//134：加油站
int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
{
    if (gas.empty() || gas.size() != cost.size())
    {
        return -1;
    }
    int length = gas.size();
    for (int i = 0; i < length;)
    {
        if (gas[i] < cost[i])
        {
            ++i;
        }
        else
        {
            int index = i;
            int g = 0, c = 0;
            while (i < length && g >= c)
            {
                g += gas[i];
                c += cost[i];
                ++i;
            }
            if (i == length)
            {
                for (int j = 0; j < index; ++j)
                {
                    g += gas[j];
                    c += cost[j];
                    if (g < c)
                    {
                        return -1;
                    }
                }
                return index;
            }
        }
    }
    return -1;
}

//253：会议室Ⅱ
bool cmp253(vector<int> &a, vector<int> &b)
{
    return a[0] < b[0];
}
int minMeetingRooms(vector<vector<int>> &intervals)
{
    sort(intervals.begin(), intervals.end(), cmp253);
    int length = intervals.size();
    if (length <= 1)
    {
        return length;
    }
    int res = 0;
    priority_queue<int, vector<int>, greater<int>> store;
    for (int i = 0; i < length; ++i)
    {
        if (!store.empty() && store.top() <= intervals[i][0])
        {
            store.pop();
            store.push(intervals[i][1]);
        }
        else
        {
            store.push(intervals[i][1]);
        }
        res = max(res, (int)store.size());
    }
    return res;
}

//413：等差数列划分Ⅰ(子串、连续)
int numberOfArithmeticSlices1(vector<int> &nums)
{
    int length = nums.size();
    int sum = 0, dp = 0;
    for (int i = 2; i < length; ++i)
    {
        if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2])
        {
            dp += 1;
        }
        else
        {
            dp = 0;
        }
        sum += dp;
    }
    return sum;
}

//446：等差数列划分Ⅱ(子序列、非连续)
typedef long long ll;
int numberOfArithmeticSlices2(vector<int> &A)
{
    int length = A.size();
    if (length <= 2)
    {
        return 0;
    }
    int sum = 0;
    vector<unordered_map<ll, int>> store(length);
    for (int i = 1; i < length; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            ll diff = (ll)A[i] - (ll)A[j];
            int temp = 0;
            if (store[j].count(diff))
            {
                temp = store[j][diff];
            }
            store[i][diff] += temp + 1;
            sum += temp;
        }
    }
    return sum;
}

//581：最短无序连续子数组
int findUnsortedSubarray(vector<int> &nums)
{
    int length = nums.size();
    if (length <= 1)
    {
        return 0;
    }
    int begin = 0;
    while (begin < length - 1 && nums[begin] <= nums[begin + 1])
    {
        ++begin;
    }
    int end = length - 1;
    while (begin < end && nums[end - 1] <= nums[end])
    {
        --end;
    }
    if (begin >= end)
    {
        return 0;
    }
    int Min = nums[begin], Max = nums[begin];
    for (int i = begin + 1; i <= end; ++i)
    {
        Min = min(Min, nums[i]);
        Max = max(Max, nums[i]);
    }
    int left = -1, right = length;
    for (int i = begin - 1; i >= 0; --i)
    {
        if (nums[i] <= Min)
        {
            left = i;
            break;
        }
    }
    for (int i = end + 1; i < length; ++i)
    {
        if (Max <= nums[i])
        {
            right = i;
            break;
        }
    }
    return right - left - 1;
}

//最长递增子序列的个数
int findNumberOfLIS(vector<int> &nums)
{
    int length = nums.size();
    if (length <= 0)
    {
        return 0;
    }
    vector<int> dp(length, 1);
    vector<int> count(length, 1);
    int myMax = 1;
    int myCount = 1;
    for (int i = 1; i < length; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (nums[i] > nums[j])
            {
                if (dp[i] < dp[j] + 1)
                {
                    dp[i] = dp[j] + 1;
                    count[i] = count[j];
                }
                else if (dp[i] == dp[j] + 1)
                {
                    count[i] += count[j];
                }
            }
        }
        if (dp[i] > myMax)
        {
            myMax = dp[i];
            myCount = count[i];
        }
        else if (dp[i] == myMax)
        {
            myCount += count[i];
        }
    }
    return myCount;
}

//941：有效的山脉数组
bool validMountainArray(vector<int> &arr)
{
    int length = arr.size();
    if (length < 3 || arr[0] >= arr[1] || arr[length - 2] <= arr[length - 1])
    {
        return false;
    }
    int index = 1;
    while (index < length && arr[index] < arr[index + 1])
    {
        ++index;
    }
    for (int i = index; i < length - 1; ++i)
    {
        if (arr[i] <= arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

//149：直线上最多的点数
int maxPoints(vector<vector<int>> &points)
{
    if (points.size() <= 2)
    {
        return points.size();
    }
    int length = points.size();
    unordered_map<string, int> store;
    int res = 1;
    for (int i = 0; i <= length - 2; ++i)
    {
        int same = 1, count = 0;
        for (int j = i + 1; j <= length - 1; ++j)
        {
            if (points[i][0] == points[j][0] && points[i][1] == points[j][1])
            {
                ++same;
            }
            else if (points[i][0] == points[j][0])
            {
                ++store["1,0"];
                count = max(count, store["1,0"]);
            }
            else if (points[i][1] == points[j][1])
            {
                ++store["0,1"];
                count = max(count, store["0,1"]);
            }
            else
            {
                int a = points[i][1] - points[j][1];
                int b = points[i][0] - points[j][0];
                int temp = gcd(a, b);
                a /= temp;
                b /= temp;
                ++store[to_string(a) + ',' + to_string(b)];
                count = max(count, store[to_string(a) + ',' + to_string(b)]);
            }
        }
        res = max(res, same + count);
        store.clear();
    }
    return res;
}

//815：公交路线
bool isIntersect(vector<int> &a, vector<int> &b)
{
    int ap = 0, bp = 0;
    while (ap < a.size() && bp < b.size())
    {
        if (a[ap] == b[bp])
        {
            return true;
        }
        else if (a[ap] < b[bp])
        {
            ++ap;
        }
        else if (a[ap] > b[bp])
        {
            ++bp;
        }
    }
    return false;
}
bool isInside(vector<int> &a, int tar)
{
    int left = 0, right = a.size() - 1;
    while (left <= right)
    {
        int middle = left + ((right - left) >> 1);
        if (a[middle] == tar)
        {
            return true;
        }
        else if (a[middle] < tar)
        {
            left = middle + 1;
        }
        else if (a[middle] > tar)
        {
            right = middle - 1;
        }
    }
    return false;
}
int numBusesToDestination(vector<vector<int>> &routes, int source, int target)
{
    if (source == target)
    {
        return 0;
    }
    int length = routes.size();
    for (int i = 0; i < length; ++i)
    {
        sort(routes[i].begin(), routes[i].end());
    }
    vector<vector<int>> store(length);
    for (int i = 0; i < length - 1; ++i)
    {
        for (int j = i + 1; j < length; ++j)
        {
            if (isIntersect(routes[i], routes[j]))
            {
                store[i].push_back(j);
                store[j].push_back(i);
            }
        }
    }
    unordered_set<int> begin;
    unordered_set<int> end;
    vector<bool> visited(length, false);
    queue<int> mq;
    for (int i = 0; i < length; ++i)
    {
        if (isInside(routes[i], source))
        {
            begin.insert(i);
            mq.push(i);
            visited[i] = true;
        }
        if (isInside(routes[i], target))
        {
            end.insert(i);
        }
    }
    int res = 0;
    while (!mq.empty())
    {
        int count = mq.size();
        ++res;
        for (int i = 0; i < count; ++i)
        {
            int temp = mq.front();
            mq.pop();
            if (end.count(temp))
            {
                return res;
            }
            for (int j = 0; j < store[temp].size(); ++j)
            {
                if (!visited[store[temp][j]])
                {
                    mq.push(store[temp][j]);
                    visited[store[temp][j]] = true;
                }
            }
        }
    }
    return -1;
}

//1388：3n块披萨
int maxSizeSlices(vector<int> &slices)
{
    int length = slices.size();
    vector<vector<int>> store(length + 1, vector<int>((length + 2) / 3 + 1, 0));
    store[1][1] = slices[0];
    for (int i = 2; i <= length; ++i)
    {
        for (int j = 1; j <= min((length + 2) / 3, i); ++j)
        {
            store[i][j] = max(store[i - 2][j - 1] + slices[i - 1], store[i - 1][j]);
        }
    }
    int res = store[length - 1][(length + 2) / 3];
    store[1][1] = 0;
    for (int i = 2; i <= length; ++i)
    {
        for (int j = 1; j <= min((length + 2) / 3, i); ++j)
        {
            store[i][j] = max(store[i - 2][j - 1] + slices[i - 1], store[i - 1][j]);
        }
    }
    return max(res, store[length][(length + 2) / 3]);
}

//1411：给Nx3网格图涂色的方案数
int numOfWays(int n)
{
    long dp1 = 6, dp0 = 6;
    --n;
    while (n--)
    {
        long temp1 = 2 * dp1 + 2 * dp0;
        long temp0 = 2 * dp1 + 3 * dp0;
        dp1 = temp1;
        dp1 %= (int)(1e9 + 7);
        dp0 = temp0;
        dp0 %= (int)(1e9 + 7);
    }
    return (dp1 + dp0) % (int)(1e9 + 7);
}

//找满足条件的工人劳动方案数
void dfs(vector<vector<int>> &a, int index, int n, int p, int &res)
{
    if (index == a.size() && n >= 0 && p <= 0)
    {
        ++res;
        return;
    }
    else if (index >= a.size() || n < 0)
    {
        return;
    }
    dfs(a, index + 1, n, p, res);
    dfs(a, index + 1, n - a[index][0], p - a[index][1], res);
}
int countPlans(vector<vector<int>> &a, int n, int p)
{
    int res = 0;
    dfs(a, 0, n, p, res);
    return res;
}

//1539：第k个缺失的正整数
int findKthPositive(vector<int> &arr, int k)
{
    int target = 1;
    int length = arr.size();
    int left = 0, right = length - 1;
    while (left <= right)
    {
        int middle = left + ((right - left) >> 1);
        if (arr[middle] - middle - 1 < k)
        {
            left = middle + 1;
        }
        else if (arr[middle] - middle - 1 >= k)
        {
            right = middle - 1;
        }
    }
    return k + target + right;
}

//棋盘排列所有车到对角线不让其他车打到
//https://www.cnblogs.com/lr599909928/p/14169774.html
int findf(vector<int> &f, int x)
{
    if (f[x] != x)
    {
        int father = findf(f, f[x]);
        f[x] = father;
    }
    return f[x];
}
void merge(vector<int> &f, int x, int y)
{
    int fx = findf(f, x);
    int fy = findf(f, y);
    f[fx] = fy;
}
int count(int n, int m, vector<vector<int>> &store)
{
    int count = 0;
    vector<int> f(n + 1, 0);
    for (int i = 1; i < m; ++i)
    {
        f[i] = i;
    }
    for (int i = 0; i < m; ++i)
    {
        if (store[i][0] == store[i][1])
        {
            --count;
            continue;
        }
        int f0 = findf(f, store[i][0]);
        int f1 = findf(f, store[i][1]);
        if (f1 = f0)
        {
            ++count;
        }
        else
        {
            merge(f, store[i][0], store[i][1]);
        }
    }
    return count + m;
}

//读取字符串,中间有,
// int main()
// {
//     vector<vector<string>> store;
//     vector<string> temp;
//     string s;
//     while (cin >> s)
//     {
//         stringstream ss(s);
//         string stemp;
//         while (getline(ss, stemp, ','))
//         {
//             temp.push_back(stemp);
//         }
//         store.push_back(temp);
//         temp.clear();
//     }
//     for (int i = 0; i < store.size(); ++i)
//     {
//         sort(store[i].begin(), store[i].end());
//         for (int j = 0; j < store[i].size(); ++j)
//         {
//             if (j != store[i].size() - 1)
//             {
//                 cout << store[i][j] << ",";
//             }
//             else
//             {
//                 cout << store[i][j];
//             }
//         }
//         cout << endl;
//     }
//     return 0;
// }

//读取字符串Ⅱ
// int main()
// {
//     int a, b, c;
//     cin >> a >> b >> c;
//     char s;
//     int begini, beginj;
//     vector<vector<bool>> store(a, vector<bool>(b, false));
//     for (int i = 0; i < a; ++i)
//     {
//         for (int j = 0; j < b; ++j)
//         {
//             cin >> s;
//             if (s == '.')
//             {
//                 store[i][j] = true;
//             }
//             else if (s == '@')
//             {
//                 begini = i;
//                 beginj = j;
//             }
//         }
//     }
//     return 0;
// }

//从字符串中找出数字
void removeZero(vector<string> &res)
{
    for (int i = 0; i < res.size(); ++i)
    {
        int j = 0;
        while (j < res[i].size() && res[i][j] == '0')
        {
            ++j;
        }
        if (j == res[i].size())
        {
            res[i] = "0";
        }
        else
        {
            res[i] = res[i].substr(j, res[i].size() - j);
        }
    }
}
bool cmp(string &a, string &b)
{
    if (a.size() != b.size())
    {
        return a.size() < b.size();
    }
    else
    {
        for (int i = 0; i < a.size(); ++i)
        {
            if (a[i] != b[i])
            {
                return a[i] < b[i];
            }
        }
    }
    return false;
}
vector<string> findNums(string &s)
{
    vector<string> res;
    for (int i = 0; i < s.size();)
    {
        while (i < s.size() && s[i] >= 'a' && s[i] <= 'z')
        {
            ++i;
        }
        int temp = i;
        while (i < s.size() && s[i] >= '0' && s[i] <= '9')
        {
            ++i;
        }
        if (i > temp)
        {
            res.push_back(s.substr(temp, i - temp));
        }
    }
    removeZero(res);
    sort(res.begin(), res.end(), cmp);
    return res;
}

//给定n个数,求每个窗口大小为m的众数是多少
vector<int> manyNums(vector<int> &nums, int n, int m)
{
    vector<int> res;
    unordered_map<int, int> store;
    int temp = 0;
    int count = 0;
    for (int j = 0; j < m; ++j)
    {
        ++store[nums[j]];
        if (store[nums[j]] > count || (store[nums[j]] == count && nums[j] < temp))
        {
            temp = nums[j];
            count = store[nums[j]];
        }
    }
    res.push_back(temp);
    for (int i = 1; i <= n - m; ++i)
    {
        --store[nums[i - 1]];
        ++store[nums[i + m - 1]];
        temp = 0;
        count = 0;
        for (auto iter = store.begin(); iter != store.end(); ++iter)
        {
            if (iter->second > count || (iter->second == count && iter->first < temp))
            {
                temp = iter->first;
                count = iter->second;
            }
        }
        res.push_back(temp);
    }
    return res;
}

//没有相邻节点的树的权重最大值(0不带2带)
void dfs(vector<int> &w, vector<vector<int>> &tree, int index, vector<vector<int>> &dp)
{
    for (int i = 0; i < tree[index].size(); ++i)
    {
        dfs(w, tree, tree[index][i], dp);
    }
    dp[index][1] = INT_MAX;
    dp[index][2] = w[index];
    dp[index][3] = w[index];
    for (int i = 0; i < tree[index].size(); ++i)
    {
        int child = tree[index][i];
        if (dp[child][0] > dp[child][2] || (dp[child][0] == dp[child][2] && dp[child][1] < dp[child][3]))
        {
            dp[index][0] += dp[child][0];
            dp[index][1] = dp[child][1];
        }
        else
        {
            dp[index][0] += dp[child][2];
            dp[index][1] = dp[child][3];
        }
        dp[index][2] += dp[child][0];
        dp[index][3] = min(dp[index][3], dp[child][1]);
    }
}
vector<int> findMax(int n, int m, vector<int> &w, vector<vector<int>> &link)
{
    w.insert(w.begin(), 0);
    vector<vector<int>> tree(n + 1);
    for (int i = 0; i < m; ++i)
    {
        tree[link[i][0]].push_back(link[i][1]);
    }
    vector<vector<int>> dp(n + 1, vector<int>(4, 0));
    int begin = 1;
    dfs(w, tree, begin, dp);
    if (dp[begin][0] < dp[begin][2])
    {
        return vector<int>{dp[begin][2], dp[begin][3]};
    }
    else if (dp[begin][0] > dp[begin][2])
    {
        return vector<int>{dp[begin][0], dp[begin][1]};
    }
    else
    {
        if (dp[begin][1] < dp[begin][3])
        {
            return vector<int>{dp[begin][0], dp[begin][1]};
        }
        else
        {
            return vector<int>{dp[begin][2], dp[begin][3]};
        }
    }
}

//操作系统
int wasteData(string s, string a)
{
    if (a.empty())
    {
        return 0;
    }
    vector<vector<int>> store(26);
    for (int i = 0; i < s.size(); ++i)
    {
        store[s[i] - 'a'].push_back(i);
    }
    int res = store[a[0] - 'a'][0];
    int index = store[a[0] - 'a'][0];
    int count = 0;
    for (int i = 1; i < a.size(); ++i)
    {
        bool flag = true;
        for (int j = 0; j < store[a[i] - 'a'].size(); ++j)
        {
            if (count * 26 + store[a[i] - 'a'][j] > index)
            {
                res += count * 26 + store[a[i] - 'a'][j] - index - 1;
                index = count * 26 + store[a[i] - 'a'][j];
                flag = false;
                break;
            }
        }
        if (flag)
        {
            ++count;
            res += count * 26 + store[a[i] - 'a'][0] - index - 1;
            index = count * 26 + store[a[i] - 'a'][0];
        }
    }
    return res;
}

//值日
int duty(vector<vector<int>> &nums, int m)
{
    int storem = m;
    if (m <= 2)
    {
        return m == 1 ? 1 : 2;
    }
    int i = 1, j = 2, id = 0;
    int res = nums[j][i];
    unordered_map<string, int> store;
    vector<int> store2;
    m -= 2;
    while (m--)
    {
        i = j;
        j = res;
        res = nums[j][i];
        string comp = to_string(j) + ',' + to_string(i);
        if (store.count(comp))
        {
            break;
        }
        else
        {
            store[comp] = id;
            store2.push_back(res);
        }
    }
    return m > 0 ? store2[(storem - 1) % store2.size()] : res;
}

//分割数组的最大值
int splitArray(vector<int> &nums, int m)
{
    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX));
    dp[0][0] = 0;
    vector<int> sub(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        sub[i] += (sub[i - 1] + nums[i - 1]);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= min(i, m); ++j)
        {
            for (int k = i - 1; k >= j - 1; --k)
            {
                dp[i][j] = min(dp[i][j], max(dp[k][j - 1], sub[i] - sub[k]));
            }
        }
    }
    return dp[n][m];
}

//135：分发糖果
int candy(vector<int> &ratings)
{
    int length = ratings.size();
    vector<int> storel(length, 1);
    vector<int> storer(length, 1);
    for (int i = 1; i < length; ++i)
    {
        if (ratings[i] > ratings[i - 1])
        {
            storel[i] = storel[i - 1] + 1;
        }
    }
    for (int i = length - 2; i >= 0; --i)
    {
        if (ratings[i] > ratings[i + 1])
        {
            storer[i] = storer[i + 1] + 1;
        }
    }
    int sum = 0;
    for (int i = 0; i < length; ++i)
    {
        sum += max(storel[i], storer[i]);
    }
    return sum;
}

int main()
{
    { //N数之和
        vector<int> nums1 = {2, 7, 11, 15};
        vector<int> res1 = twoSum(nums1, 9);

        vector<int> nums15 = {-1, 0, 1, 2, -1, -4};
        vector<vector<int>> res15 = threeSum(nums15);

        vector<int> nums16 = {-1, 2, 1, -4};
        int res16 = threeSumClosest(nums16, 1);

        vector<int> nums18 = {0, 0, 0, 0};
        vector<vector<int>> res18 = fourSum(nums18, 0);

        vector<int> nums454_1 = {1, 2};
        vector<int> nums454_2 = {-2, -1};
        vector<int> nums454_3 = {-1, 2};
        vector<int> nums454_4 = {0, 2};
        int res454 = fourSumCount(nums454_1, nums454_2, nums454_3, nums454_4);
    }

    { //整数技巧
        int res7 = reverse(1534236469);

        bool res9 = isPalindrome(21120);

        int res172 = trailingZeroes(3);

        bool res202 = isHappy(19);

        int res1399 = countLargestGroup(13);
    }

    { //字符串转换
        int res8 = myAtoi("21474836460");

        string res12 = intToRoman(1994);

        string s13 = "MCMXCIV";
        int res13 = romanToInt(s13);
    }

    { //最小公倍数和最大公因数
        vector<int> nums914 = {1, 2, 3, 4, 4, 3, 2, 1};
        bool res914 = hasGroupsSizeX(nums914);
    }

    { //归并排序
        vector<int> nums315 = {0, 2, 1};
        vector<int> res315 = countSmaller(nums315);
    }

    { //贪心算法
        vector<int> nums134_1 = {5, 8, 2, 8};
        vector<int> nums134_2 = {6, 5, 6, 6};
        int res = canCompleteCircuit(nums134_1, nums134_2);

        vector<vector<int>> matrix253 = {{0, 30}, {5, 10}, {15, 20}};
        int res253 = minMeetingRooms(matrix253);
    }

    { //动态规划
        vector<int> nums413 = {1, 2, 3, 4};
        int res413 = numberOfArithmeticSlices1(nums413);

        vector<int> nums446 = {2, 2, 3, 4};
        int res446 = numberOfArithmeticSlices2(nums446);

        vector<int> nums581 = {2, 6, 4, 8, 10, 9, 15};
        int res581 = findUnsortedSubarray(nums581);

        vector<int> nums673 = {2, 2, 2, 2, 2};
        int res673 = findNumberOfLIS(nums673);

        vector<int> nums941 = {2, 1};
        bool res941 = validMountainArray(nums941);
    }

    { //阿里笔试
        vector<vector<int>> nums149 = {{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}};
        int res149 = maxPoints(nums149);

        vector<vector<int>> matrix815 = {{1, 2, 7}, {3, 6, 7}};
        int res815 = numBusesToDestination(matrix815, 1, 6);

        vector<int> nums1388 = {8, 9, 8, 6, 1, 1};
        int res1388 = maxSizeSlices(nums1388);

        int res1411 = numOfWays(1);

        vector<vector<int>> matrix = {{10, 30}, {5, 25}, {2, 8}, {20, 50}};
        int res = countPlans(matrix, 30, 40);

        vector<int> nums1539 = {2, 3, 4, 7, 11};
        int res1539 = findKthPositive(nums1539, 5);

        vector<vector<int>> matrix1 = {{2, 1}, {1, 2}};
        int res1 = count(3, 2, matrix1);
        vector<vector<int>> matrix2 = {{2, 3}};
        int res2 = count(3, 1, matrix2);
    }

    { //美团笔试
        string s1 = "000h001fbcwdwu2139hnsdf999999999999";
        vector<string> res1 = findNums(s1);

        vector<int> nums2 = {1, 2, 2, 1, 3};
        vector<int> res2 = manyNums(nums2, 5, 3);

        vector<int> nums3 = {3, 4, 1, 4, 9};
        vector<vector<int>> matrix3 = {{1, 2}, {1, 3}, {2, 4}, {3, 5}};
        vector<int> res3 = findMax(5, 4, nums3, matrix3);

        string s4 = "abcdefghigklmnopqrstuvwxyz";
        string a4 = "meituan";
        int res4 = wasteData(s4, a4);

        vector<vector<int>> matrix5 = {{0, 0, 0, 0}, {0, 0, 3, 2}, {0, 3, 0, 3}, {0, 2, 1, 0}};
        int res5 = duty(matrix5, 7);

        vector<int> nums6 = {7, 2, 5, 10, 8};
        int res6 = splitArray(nums6, 2);
    }

    { //热题
        vector<int> nums = {1, 0, 2};
        int res135 = candy(nums);
    }

    return 0;
}
