#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <deque>
#include <set>
#include <stack>
#include <string>
#include <algorithm>
#include <math.h>
#include <sstream>

using namespace std;

//28：实现strStr()
//needle在haystack中出现了几次
// int kmp(string needle, string haystack)
// {
//     if (needle.size() <= 0)
//     {
//         return 0;
//     }
//     vector<int> next(needle.size(), 0);
//     for (int i = 1, j = 0; i < needle.size(); ++i)
//     {
//         while (j && needle[i] != needle[j])
//         {
//             j = next[j - 1];
//         }
//         if (needle[i] == needle[j])
//         {
//             ++j;
//         }
//         next[i] = j;
//     }
//     int res = 0;
//     for (int i = 0, j = 0; i < haystack.size(); ++i)
//     {
//         while (j && haystack[i] != needle[j])
//         {
//             j = next[j - 1];
//         }
//         if (haystack[i] == needle[j])
//         {
//             ++j;
//         }
//         if (j == needle.size())
//         {
//             ++res;
//             j = next[j - 1];
//         }
//     }
//     return res;
// }
int strStr(string haystack, string needle)
{
    if (needle.size() <= 0)
    {
        return 0;
    }
    vector<int> next(needle.size(), 0);
    for (int i = 1, j = 0; i < needle.size(); ++i)
    {
        while (j && needle[i] != needle[j])
        {
            j = next[j - 1];
        }
        if (needle[i] == needle[j])
        {
            ++j;
        }
        next[i] = j;
    }
    for (int i = 0, j = 0; i < haystack.size(); ++i)
    {
        while (j && haystack[i] != needle[j])
        {
            j = next[j - 1];
        }
        if (haystack[i] == needle[j])
        {
            ++j;
        }
        if (j == needle.size())
        {
            return i - j + 1;
        }
    }
    return -1;
}

//131：分割回文串
void dfs(vector<vector<bool>> &dp, string &s, vector<vector<string>> &res, vector<string> &temp, int begin, int end)
{
    if (end == s.size() - 1)
    {
        if (dp[begin][end])
        {
            res.push_back(temp);
        }
        return;
    }
    if (dp[begin][end])
    {
        temp.push_back(s.substr(end + 1, 1));
        dfs(dp, s, res, temp, end + 1, end + 1);
        temp.pop_back();
    }
    temp[temp.size() - 1].push_back(s[end + 1]);
    dfs(dp, s, res, temp, begin, end + 1);
}
vector<vector<string>> partition(string s)
{
    int l = s.size();
    vector<vector<bool>> dp(l, vector<bool>(l, true));
    vector<vector<string>> res;
    for (int i = l - 1; i >= 0; --i)
    {
        for (int j = i + 1; j < l; ++j)
        {
            dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]);
        }
    }
    vector<string> temp;
    temp.push_back(s.substr(0, 1));
    dfs(dp, s, res, temp, 0, 0);
    return res;
}

//132：分割回文串Ⅱ
int minCut(string s)
{
    int l = s.size();
    vector<vector<bool>> dp(l, vector<bool>(l, true));
    for (int i = l - 1; i >= 0; --i)
    {
        for (int j = i + 1; j < l; ++j)
        {
            dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]);
        }
    }
    vector<int> dp2(l, INT_MAX);
    for (int i = 0; i < l; ++i)
    {
        if (dp[0][i])
        {
            dp2[i] = 0;
            continue;
        }
        for (int j = 1; j < i; ++j)
        {
            if (dp[j + 1][i])
            {
                dp2[i] = min(dp2[i], dp2[j] + 1);
            }
        }
    }
    return dp2[l - 1];
}

//6：Z字型变换
string convert(string s, int numRows)
{
    int divide = 2 * (numRows - 1);
    if (divide <= 0)
    {
        return s;
    }
    string res;
    for (int i = 0; i < numRows; ++i)
    {
        int j = 0;
        while ((j * divide + i) < s.size())
        {
            if (i == 0 || i == numRows - 1)
            {
                res.push_back(s[j * divide + i]);
            }
            else
            {
                res.push_back(s[j * divide + i]);
                if ((j * divide + divide - i) < s.size())
                {
                    res.push_back(s[j * divide + divide - i]);
                }
            }
            ++j;
        }
    }
    return res;
}

//14：最长公共前缀
string longestCommonPrefix(vector<string> &strs)
{
    string res;
    if (!strs.size())
    {
        return res;
    }
    for (int i = 0; i < strs[0].size(); ++i)
    {
        char temp = strs[0][i];
        bool flag = true;
        for (int j = 1; j < strs.size(); j++)
        {
            if (strs[j].size() > i && strs[j][i] == temp)
            {
                continue;
            }
            else
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            res += temp;
        }
        else
        {
            break;
        }
    }
    return res;
}

//448：找到所有数组中消失的数字
vector<int> findDisappearedNumbers(vector<int> &nums)
{
    vector<int> res;
    int length = nums.size();
    for (int i = 0; i < length; ++i)
    {
        if (nums[abs(nums[i]) - 1] > 0)
        {
            nums[abs(nums[i]) - 1] *= (-1);
        }
    }
    for (int i = 0; i < length; ++i)
    {
        if (nums[i] > 0)
        {
            res.push_back(i + 1);
        }
    }
    return res;
}

//463：岛屿的周长
int islandPerimeter(vector<vector<int>> &grid)
{
    if (grid.empty() || grid[0].empty())
    {
        return 0;
    }
    int l1 = grid.size(), l2 = grid[0].size();
    int res = 0;
    for (int i = 0; i < l1; ++i)
    {
        for (int j = 0; j < l2; ++j)
        {
            if (grid[i][j] == 1)
            {
                if (i == 0 || grid[i - 1][j] == 0)
                {
                    ++res;
                }
                if (j == 0 || grid[i][j - 1] == 0)
                {
                    ++res;
                }
                if (i == l1 - 1 || grid[i + 1][j] == 0)
                {
                    ++res;
                }
                if (j == l2 - 1 || grid[i][j + 1] == 0)
                {
                    ++res;
                }
            }
        }
    }
    return res;
}

//628：三个数的最大乘积
int maximumProduct(vector<int> &nums)
{
    multiset<int> myMin = {nums[0], nums[1]}, myMax{nums[0], nums[1], nums[2]};
    for (int i = 2; i < (int)nums.size(); ++i)
    {
        if (*myMin.rbegin() > nums[i])
        {
            myMin.erase(--myMin.end());
            myMin.insert(nums[i]);
        }
        if (*myMax.begin() < nums[i] && i != 2)
        {
            myMax.erase(myMax.begin());
            myMax.insert(nums[i]);
        }
    }
    int res1 = (*myMax.begin()) * (*(++myMax.begin())) * (*myMax.rbegin());
    int res2 = (*myMax.rbegin()) * (*myMin.begin()) * (*myMin.rbegin());
    return max(res1, res2);
}

//695：岛屿的最大面积
int maxAreaOfIsland(vector<vector<int>> &grid)
{
    int length1 = grid.size();
    if (!length1)
    {
        return 0;
    }
    int length2 = grid[0].size(), res = 0;
    if (!length2)
    {
        return 0;
    }
    vector<vector<bool>> store(length1, vector<bool>(length2, false));
    for (int i = 0; i < length1; ++i)
    {
        for (int j = 0; j < length2; ++j)
        {
            if (store[i][j] || !grid[i][j])
            {
                continue;
            }
            int count = 1;
            store[i][j] = true;
            deque<vector<int>> temp = {vector<int>{i, j}};
            while (!temp.empty())
            {
                int m = temp.front()[0], n = temp.front()[1];
                temp.pop_front();
                if (m > 0 && !store[m - 1][n] && grid[m - 1][n])
                {
                    temp.push_back(vector<int>{m - 1, n});
                    ++count;
                    store[m - 1][n] = true;
                }
                if (m < length1 - 1 && !store[m + 1][n] && grid[m + 1][n])
                {
                    temp.push_back(vector<int>{m + 1, n});
                    ++count;
                    store[m + 1][n] = true;
                }
                if (n > 0 && !store[m][n - 1] && grid[m][n - 1])
                {
                    temp.push_back(vector<int>{m, n - 1});
                    ++count;
                    store[m][n - 1] = true;
                }
                if (n < length2 - 1 && !store[m][n + 1] && grid[m][n + 1])
                {
                    temp.push_back(vector<int>{m, n + 1});
                    ++count;
                    store[m][n + 1] = true;
                }
            }
            res = max(res, count);
        }
    }
    return res;
}

//697：数组的度
int findShortestSubArray(vector<int> &nums)
{
    unordered_map<int, vector<int>> store;
    int res = 1, degree = 1, index = nums[0];
    for (int i = 0; i < (int)nums.size(); ++i)
    {
        if (store.count(nums[i]))
        {
            store[nums[i]][1] = i;
            ++store[nums[i]][2];
            if (index == nums[i] || store[nums[i]][2] > degree ||
                (store[nums[i]][2] == degree && i - store[nums[i]][0] + 1 < res))
            {
                res = i - store[nums[i]][0] + 1;
                degree = store[nums[i]][2];
                index = nums[i];
            }
        }
        else
        {
            store[nums[i]] = vector<int>{i, i, 1};
        }
    }
    return res;
}

//1010：总持续时间可被 60 整除的歌曲
int numPairsDivisibleBy60(vector<int> &time)
{
    int res = 0;
    int store[60] = {0};
    for (int i = 0; i < (int)time.size(); ++i)
    {
        ++store[time[i] % 60];
    }
    res += (store[0] * (store[0] - 1) / 2 + store[31] * (store[31] - 1) / 2);
    for (int i = 1; i < 30; ++i)
    {
        res += store[i] * store[60 - i];
    }
    return res;
}

//1051：高度检查器
int heightChecker(vector<int> &heights)
{
    int store[100] = {0}, length = heights.size(), res = 0, count = 0;
    for (int i = 0; i < length; ++i)
    {
        ++store[heights[i] - 1];
    }
    for (int i = 0; i < 100; ++i)
    {
        while ((store[i]--) > 0)
        {
            if (heights[count++] != i + 1)
            {
                ++res;
            }
        }
    }
    return res;
}

//1185：一周中的第几天
string dayOfTheWeek(int day, int month, int year)
{
    string weeks[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int monthsP[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int monthsR[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int res = 0;
    res += 365 * (year - 1971) + ((year - 1969) / 4);
    if (year % 4 == 0 && year != 2100)
    {
        for (int i = 0; i < month - 1; ++i)
        {
            res += monthsR[i];
        }
    }
    else
    {
        for (int i = 0; i < month - 1; ++i)
        {
            res += monthsP[i];
        }
    }
    res += day;
    return weeks[(res + 4) % 7];
}

//1287：有序数组中出现次数超过25%的元素
int findSpecialInteger(vector<int> &arr)
{
    int size = arr.size(), index = size / 4 + 1;
    int count = index * 3 < size ? 4 : 3;
    for (int i = 0; i < count; ++i)
    {
        int target = arr[i * index];
        int left = 0, right = size - 1, store = 0;
        while (left <= right)
        {
            int middle = (left + right) / 2;
            if (arr[middle] > target)
            {
                right = middle - 1;
            }
            else
            {
                left = middle + 1;
            }
        }
        store = left, left = 0;
        while (left <= right)
        {
            int middle = (left + right) / 2;
            if (arr[middle] >= target)
            {
                right = middle - 1;
            }
            else
            {
                left = middle + 1;
            }
        }
        store -= left;
        if (store * 4 > size)
        {
            return arr[left];
        }
    }
    return 0;
}

//1337：矩阵中战斗力最弱的 K 行
vector<int> kWeakestRows(vector<vector<int>> &mat, int k)
{
    multimap<int, int> store;
    vector<int> res;
    for (int i = 0; i < (int)mat.size(); ++i)
    {
        int left = 0, right = mat[i].size() - 1;
        while (left <= right)
        {
            int middle = (left + right) / 2;
            if (mat[i][middle])
            {
                left = middle + 1;
            }
            else
            {
                right = middle - 1;
            }
        }
        if (store.size() < k)
        {
            store.insert(make_pair(left, i));
        }
        else if ((--store.end())->first > left)
        {
            store.erase(--store.end());
            store.insert(make_pair(left, i));
        }
    }
    for (auto iter = store.begin(); iter != store.end(); ++iter)
    {
        res.push_back(iter->second);
    }
    return res;
}

//1385：两个数组间的距离值
int findTheDistanceValue(vector<int> &arr1, vector<int> &arr2, int d)
{
    sort(arr2.begin(), arr2.end());
    int res = 0;
    for (int i = 0; i < (int)arr1.size(); ++i)
    {
        int left = 0, right = arr2.size() - 1;
        while (left <= right)
        {
            int index = (left + right) / 2;
            if (arr1[i] > arr2[index])
            {
                left = index + 1;
            }
            else if (arr1[i] < arr2[index])
            {
                right = index - 1;
            }
            else
            {
                left = -1;
                break;
            }
        }
        if (left == -1)
        {
            continue;
        }
        else if (left == 0)
        {
            if (abs(arr1[i] - arr2[left]) > d)
            {
                ++res;
            }
        }
        else if (left == arr2.size())
        {
            if (abs(arr1[i] - arr2[left - 1]) > d)
            {
                ++res;
            }
        }
        else
        {
            if (abs(arr1[i] - arr2[left]) > d && abs(arr1[i] - arr2[left - 1]) > d)
            {
                ++res;
            }
        }
    }
    return res;
}

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//2：两数相加
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    ListNode *lSum = new ListNode(0), *templ = lSum;
    int upFlag = 0, tempflag = 0;
    while (l1 || l2)
    {
        int val1 = 0, val2 = 0;
        if (l1)
        {
            val1 = l1->val;
        }
        if (l2)
        {
            val2 = l2->val;
        }
        int flag = val1 + val2 + upFlag;
        tempflag = flag % 10;
        upFlag = flag / 10;
        templ->next = new ListNode(tempflag);
        templ = templ->next;
        if (l1)
        {
            l1 = l1->next;
        }
        if (l2)
        {
            l2 = l2->next;
        }
    }
    if (upFlag)
    {
        templ->next = new ListNode(upFlag);
    }
    return lSum->next;
}

//19：删除链表的倒数第 N 个结点
ListNode *removeNthFromEnd(ListNode *head, int n)
{
    ListNode *slow = head, *fast = head;
    while (n)
    {
        fast = fast->next;
        --n;
    }
    if (!fast)
    {
        return head->next;
    }
    while (fast->next)
    {
        slow = slow->next;
        fast = fast->next;
    }
    slow->next = slow->next->next;
    return head;
}

//24：两两交换链表中节点
ListNode *swapPairs(ListNode *head)
{
    ListNode *res = new ListNode(0);
    res->next = head;
    ListNode *temp = res;
    while (temp && temp->next && temp->next->next)
    {
        ListNode *pre = temp->next, *mid = temp->next->next, *last = temp->next->next->next;
        temp->next = mid;
        mid->next = pre;
        pre->next = last;
        temp = temp->next->next;
    }
    return res->next;
}

//61：旋转链表
ListNode *rotateRight(ListNode *head, int k)
{
    ListNode *res = NULL, *slow = head, *fast = head;
    int tempM = 0;
    while (slow)
    {
        ++tempM;
        slow = slow->next;
    }
    if (!tempM)
    {
        return NULL;
    }
    int mover = k % tempM;
    if (!mover)
    {
        return head;
    }
    while (mover)
    {
        fast = fast->next;
        --mover;
    }
    slow = head;
    while (fast->next)
    {
        slow = slow->next;
        fast = fast->next;
    }
    res = slow->next;
    slow->next = NULL;
    fast->next = head;
    return res;
}

//86：分隔链表Ⅰ
ListNode *partition(ListNode *head, int x)
{
    ListNode *res1 = new ListNode(0);
    ListNode *res2 = new ListNode(0);
    ListNode *tempres1 = res1, *tempres2 = res2;
    while (head)
    {
        if (head->val < x)
        {
            tempres1->next = head;
            tempres1 = tempres1->next;
        }
        else
        {
            tempres2->next = head;
            tempres2 = tempres2->next;
        }
        head = head->next;
    }
    tempres1->next = res2->next;
    tempres2->next = NULL;
    return res1->next;
}

//147：对链表进行插入排序
ListNode *insertionSortList(ListNode *head)
{
    if (!head || !head->next)
    {
        return head;
    }
    ListNode *temp = head;
    ListNode *res = new ListNode(0);
    res->next = head;
    int numble = 1;
    while (temp && temp->next)
    {
        ListNode *node = temp->next;
        temp->next = temp->next->next;
        ListNode *change = res;
        int id = numble;
        while (change->next && change->next->val < node->val && id--)
        {
            change = change->next;
        }
        node->next = change->next;
        change->next = node;
        temp = res->next, id = numble;
        while (id--)
        {
            temp = temp->next;
        }
        ++numble;
    }
    return res->next;
}

//234：回文链表
// bool isPalindrome(ListNode* head)
// {
// 	stack<int> res;
// 	ListNode* temp = head;
// 	while (temp)
// 	{
// 		res.push(temp->val);
// 		temp = temp->next;
// 	}
// 	while (head)
// 	{
// 		if (head->val != res.top()) { return false; }
// 		head = head->next;
// 		res.pop();
// 	}
// 	return true;
// }
bool isPalindrome(ListNode *head)
{
    int num = 0;
    ListNode *fast = head, *slow = head;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    fast = NULL;
    ListNode *slowCopy = slow;
    while (slowCopy)
    {
        ListNode *temp = slowCopy;
        slowCopy = slowCopy->next;
        temp->next = fast;
        fast = temp;
    }
    while (fast)
    {
        if (fast->val != head->val)
        {
            return false;
        }
        fast = fast->next;
        head = head->next;
    }
    return true;
}

//328：奇偶链表
ListNode *oddEvenList(ListNode *head)
{
    ListNode *left = new ListNode(0);
    ListNode *right = new ListNode(0);
    ListNode *templeft = left, *tempright = right;
    int change = 1;
    while (head)
    {
        if (change)
        {
            templeft->next = head;
            templeft = templeft->next;
        }
        else
        {
            tempright->next = head;
            tempright = tempright->next;
        }
        change = 1 - change;
        head = head->next;
    }
    templeft->next = right->next;
    tempright->next = NULL;
    return left->next;
}

//445：两数相加Ⅱ
ListNode *addTwoNumbersN(ListNode *l1, ListNode *l2)
{
    ListNode *res = NULL;
    stack<int> s1, s2;
    while (l1)
    {
        s1.push(l1->val);
        l1 = l1->next;
    }
    while (l2)
    {
        s2.push(l2->val);
        l2 = l2->next;
    }
    int upval = 0;
    while (!s1.empty() || !s2.empty() || upval)
    {
        int val1 = s1.empty() ? 0 : s1.top();
        int val2 = s2.empty() ? 0 : s2.top();
        int tempval = (val1 + val2 + upval) % 10;
        upval = (val1 + val2 + upval) / 10;
        ListNode *temp = new ListNode(tempval);
        temp->next = res;
        res = temp;
        if (!s1.empty())
        {
            s1.pop();
        }
        if (!s2.empty())
        {
            s2.pop();
        }
    }
    return res;
}

//725：分隔链表Ⅱ
vector<ListNode *> splitListToParts(ListNode *root, int k)
{
    vector<ListNode *> res;
    int num = 0;
    ListNode *temp = root;
    while (temp)
    {
        temp = temp->next;
        ++num;
    }
    temp = root;
    while (k--)
    {
        if (!num)
        {
            res.push_back(NULL);
            continue;
        }
        if (!k)
        {
            res.push_back(temp);
            break;
        }
        int divide = 0;
        if (num % (k + 1) == 0)
        {
            divide = num / (k + 1);
            num -= divide;
        }
        else
        {
            divide = num / (k + 1) + 1;
            num -= divide;
        }
        ListNode *divideList = temp;
        while (--divide)
        {
            temp = temp->next;
        }
        ListNode *temp2 = temp;
        temp = temp->next;
        temp2->next = NULL;
        res.push_back(divideList);
    }
    return res;
}

//817：链表组件
int numComponents(ListNode *head, vector<int> &G)
{
    unordered_set<int> myset;
    for (int i = 0; i < G.size(); ++i)
    {
        myset.insert(G[i]);
    }
    int res = 0;
    while (head && head->next)
    {
        if (myset.count(head->val) && !myset.count(head->next->val))
        {
            ++res;
        }
        head = head->next;
    }
    if (head && myset.count(head->val))
    {
        ++res;
    }
    return res;
}

//1019：链表中的下一个更大节点
vector<int> nextLargerNodes(ListNode *head)
{
    vector<int> trans;
    ListNode *temp = head;
    while (temp)
    {
        trans.push_back(temp->val);
        temp = temp->next;
    }
    vector<int> res;
    res.resize(trans.size());
    stack<int> largeIndex;
    for (int i = 0; i < (int)trans.size(); ++i)
    {
        while (!largeIndex.empty() && trans[largeIndex.top()] < trans[i])
        {
            res[largeIndex.top()] = trans[i];
            largeIndex.pop();
        }
        largeIndex.push(i);
    }
    return res;
}

//1171：从链表中删去总和值为零的连续节点
ListNode *removeZeroSumSublists(ListNode *head)
{
    if (!head)
    {
        return NULL;
    }
    unordered_map<int, ListNode *> store;
    int sum = 0;
    ListNode *res = new ListNode(0);
    res->next = head;
    store.insert(make_pair(sum, res));
    ListNode *temp = head;
    while (temp)
    {
        sum += temp->val;
        if (store.count(sum))
        {
            ListNode *del = store[sum]->next;
            int delnum = sum;
            store[sum]->next = temp->next;
            while (del)
            {
                delnum += del->val;
                if (delnum == sum)
                {
                    break;
                }
                store.erase(delnum);
                del = del->next;
            }
        }
        else
        {
            store.insert(make_pair(sum, temp));
        }
        temp = temp->next;
    }
    return res->next;
}

//430：扁平化多级双向链表(无样例)
class Node
{
public:
    int val;
    Node *prev;
    Node *next;
    Node *child;
    Node(int x) : val(x), prev(NULL), next(NULL), child(NULL) {}
};
Node *flatten(Node *head)
{
    Node *father = head;
    while (father)
    {
        if (father->child)
        {
            Node *next = father->next;
            father->next = father->child;
            father->child = NULL;
            Node *son = father->next;
            son->prev = father;
            while (son->next)
            {
                son = son->next;
            }
            son->next = next;
            if (next)
            {
                next->prev = son;
            }
        }
        father = father->next;
    }
    return head;
}

//707：设计链表
class MyLinkedList
{
public:
    MyLinkedList() : head(NULL) {}
    int get(int index)
    {
        ListNode *temp = head;
        while (index--)
        {
            if (temp)
            {
                temp = temp->next;
            }
            else
            {
                return -1;
            }
        }
        if (!temp)
        {
            return -1;
        }
        return temp->val;
    }
    void addAtHead(int val)
    {
        ListNode *temp = new ListNode(val);
        temp->next = head;
        head = temp;
    }
    void addAtTail(int val)
    {
        if (!head)
        {
            head = new ListNode(val);
        }
        ListNode *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new ListNode(val);
    }
    void addAtIndex(int index, int val)
    {
        if (!index)
        {
            return addAtHead(val);
        }
        ListNode *temp = head;
        while (--index)
        {
            temp = temp->next;
        }
        ListNode *temp2 = temp->next;
        temp->next = new ListNode(val);
        temp->next->next = temp2;
    }
    void deleteAtIndex(int index)
    {
        if (!index)
        {
            head = head->next;
            return;
        }
        ListNode *temp = head;
        while (--index)
        {
            if (!temp)
            {
                return;
            }
            temp = temp->next;
        }
        if (!temp || !temp->next)
        {
            return;
        }
        temp->next = temp->next->next;
    }

private:
    ListNode *head;
};

//316：去除重复字母
string removeDuplicateLetters(string s)
{
    vector<int> store(26, 0);
    int L = s.size();
    for (int i = 0; i < L; ++i)
    {
        ++store[s[i] - 'a'];
    }
    deque<char> sq;
    vector<bool> visited(26, false);
    for (int i = 0; i < L; ++i)
    {
        if (!visited[s[i] - 'a'])
        {
            while (!sq.empty() && store[sq.back() - 'a'] >= 1 && sq.back() > s[i])
            {
                visited[sq.back() - 'a'] = false;
                sq.pop_back();
            }
            sq.push_back(s[i]);
            visited[s[i] - 'a'] = true;
        }
        --store[s[i] - 'a'];
    }
    string res;
    while (!sq.empty())
    {
        res.push_back(sq.front());
        sq.pop_front();
    }
    return res;
}

//321：拼接最大数
void find(vector<int> &nums, vector<int> &res, int k)
{
    if (k <= 0)
    {
        return;
    }
    for (int i = 0; i < nums.size(); ++i)
    {
        while (!res.empty() && res.back() < nums[i] && i + k < nums.size())
        {
            res.pop_back();
            ++k;
        }
        res.push_back(nums[i]);
        --k;
    }
    while (k < 0)
    {
        res.pop_back();
        ++k;
    }
    return;
}
bool compare2(vector<int> &nums1, vector<int> &nums2, int l1, int l2)
{
    int len1 = nums1.size(), len2 = nums2.size();
    while (l1 < len1 && l2 < len2)
    {
        if (nums1[l1] > nums2[l2])
        {
            return true;
        }
        else if (nums1[l1] < nums2[l2])
        {
            return false;
        }
        else
        {
            ++l1;
            ++l2;
        }
    }
    if (l1 < len1)
    {
        int target = nums2[l2 - 1];
        while (l1 < len1)
        {
            if (nums1[l1] > target)
            {
                return true;
            }
            else if (nums1[l1] < target)
            {
                return false;
            }
            else
            {
                ++l1;
            }
        }
    }
    if (l2 < len2)
    {
        int target = nums1[l1 - 1];
        while (l2 < len2)
        {
            if (target > nums2[l2])
            {
                return true;
            }
            else if (target < nums2[l2])
            {
                return false;
            }
            else
            {
                ++l2;
            }
        }
    }
    return false;
}
void merge(vector<int> &res, vector<int> &nums1, vector<int> &nums2)
{
    int id1 = 0, id2 = 0, L1 = nums1.size(), L2 = nums2.size();
    while (id1 < L1 && id2 < L2)
    {
        if (nums1[id1] > nums2[id2] || (nums1[id1] == nums2[id2] && compare2(nums1, nums2, id1, id2)))
        {
            res.push_back(nums1[id1]);
            ++id1;
        }
        else
        {
            res.push_back(nums2[id2]);
            ++id2;
        }
    }
    while (id1 < L1)
    {
        res.push_back(nums1[id1]);
        ++id1;
    }
    while (id2 < L2)
    {
        res.push_back(nums2[id2]);
        ++id2;
    }
    return;
}
bool compare(vector<int> &nums1, vector<int> &nums2)
{
    if (nums1.size() < nums2.size())
    {
        return true;
    }
    for (int i = 0; i < nums1.size(); ++i)
    {
        if (nums1[i] < nums2[i])
        {
            return true;
        }
        else if (nums1[i] > nums2[i])
        {
            return false;
        }
    }
    return false;
}
vector<int> maxNumber(vector<int> &nums1, vector<int> &nums2, int k)
{
    vector<int> res;
    for (int i = max(0, k - (int)nums2.size()); i <= min((int)nums1.size(), k); ++i)
    {
        vector<int> res1, res2;
        find(nums1, res1, i);
        find(nums2, res2, k - i);
        vector<int> temp;
        merge(temp, res1, res2);
        res = compare(res, temp) ? temp : res;
    }
    return res;
}

//402：移掉K位数字
string removeKdigits(string num, int k)
{
    deque<char> store;
    for (int i = 0; i < num.size(); ++i)
    {
        while (k > 0 && !store.empty() && store.back() > num[i])
        {
            store.pop_back();
            --k;
        }
        store.push_back(num[i]);
    }
    while (k > 0)
    {
        store.pop_back();
        --k;
    }
    string res;
    while (!store.empty() && store.front() == '0')
    {
        store.pop_front();
    }
    while (!store.empty())
    {
        res.push_back(store.front());
        store.pop_front();
    }
    return res == "" ? "0" : res;
}

//763：划分字母区间
vector<int> partitionLabels(string S)
{
    vector<int> begin(26, -1);
    vector<int> end(26, -1);
    for (int i = 0; i < S.size(); ++i)
    {
        if (begin[S[i] - 'a'] == -1)
        {
            begin[S[i] - 'a'] = i;
        }
        end[S[i] - 'a'] = i;
    }
    vector<int> res;
    int b = begin[S[0] - 'a'];
    int e = end[S[0] - 'a'];
    for (int i = 0; i < S.size(); ++i)
    {
        if (e == i)
        {
            res.push_back(e - b + 1);
            if (i < S.size() - 1)
            {
                b = begin[S[i + 1] - 'a'];
                e = end[S[i + 1] - 'a'];
            }
        }
        else if (e > i)
        {
            e = max(e, end[S[i] - 'a']);
        }
    }
    return res;
}

//767：重构字符串
struct sReorganize
{
    int i;
    int c;
    sReorganize(int count, int letter) : i(count), c(letter) {}
};
struct cmp767
{
    bool operator()(sReorganize &s1, sReorganize &s2)
    {
        return s1.i < s2.i;
    }
};
string reorganizeString(string S)
{
    vector<int> store(26, 0);
    for (int i = 0; i < S.size(); ++i)
    {
        ++store[S[i] - 'a'];
    }
    int maxL = (S.size() + 1) >> 1;
    for (int i = 0; i < 26; ++i)
    {
        if (store[i] > maxL)
        {
            return "";
        }
    }
    string res;
    priority_queue<sReorganize, vector<sReorganize>, cmp767> maxHeap;
    for (int i = 0; i < 26; ++i)
    {
        if (store[i] > 0)
        {
            maxHeap.push(sReorganize(store[i], i));
        }
    }
    while (maxHeap.size() >= 2)
    {
        sReorganize s1 = maxHeap.top();
        maxHeap.pop();
        sReorganize s2 = maxHeap.top();
        maxHeap.pop();
        res.push_back(s1.c + 'a');
        res.push_back(s2.c + 'a');
        --s1.i;
        --s2.i;
        if (s1.i)
        {
            maxHeap.push(s1);
        }
        if (s2.i)
        {
            maxHeap.push(s2);
        }
    }
    if (!maxHeap.empty())
    {
        res.push_back(maxHeap.top().c + 'a');
    }
    return res;
}

//395：至少有K个重复字符的最长子串
int longestSubstring(string s, int k)
{
    int res = 0;
    for (int i = 1; i <= 26; ++i)
    {
        vector<int> store(26, 0);
        int count = 0, less = 0;
        int left = 0, right = 0;
        while (right < s.size())
        {
            ++store[s[right] - 'a'];
            if (store[s[right] - 'a'] == 1)
            {
                ++less;
                ++count;
            }
            if (store[s[right] - 'a'] == k)
            {
                --less;
            }
            while (count > i)
            {
                --store[s[left] - 'a'];
                if (store[s[left] - 'a'] == 0)
                {
                    --count;
                    --less;
                }
                if (store[s[left] - 'a'] == k - 1)
                {
                    ++less;
                }
                ++left;
            }
            if (less == 0)
            {
                res = max(res, right - left + 1);
            }
            ++right;
        }
    }
    return res;
}

//424：替换后的最长重复子串
int characterReplacement(string s, int k)
{
    if (s.size() <= k + 1)
    {
        return s.size();
    }
    vector<int> store(26, 0);
    int maxL = 0, res = 0;
    int left = 0, right = 0;
    while (right < s.size())
    {
        ++store[s[right] - 'A'];
        maxL = max(maxL, store[s[right] - 'A']);
        if (right - left + 1 > maxL + k)
        {
            --store[s[left] - 'A'];
            ++left;
        }
        res = max(res, right - left + 1);
        ++right;
    }
    return res;
}

//977：有序数组的平方
vector<int> sortedSquares(vector<int> &nums)
{
    int left = 0, right = nums.size() - 1, index = nums.size() - 1;
    vector<int> res(nums.size());
    while (left <= right)
    {
        if (nums[left] * nums[left] <= nums[right] * nums[right])
        {
            res[index--] = nums[right] * nums[right];
            --right;
        }
        else
        {
            res[index--] = nums[left] * nums[left];
            ++left;
        }
    }
    return res;
}

int main()
{
    { //KMP算法
        string s28_1 = "mississippi";
        string s28_2 = "aaaaaa";
        int res28 = strStr(s28_1, s28_2);
    }

    { //动态规划预处理
        string s131 = "aab";
        vector<vector<string>> res131 = partition(s131);

        string s132 = "aab";
        int res132 = minCut(s132);
    }

    { //技巧题
        string s6 = "LEETCODEISHIRING";
        string res6 = convert(s6, 4);

        vector<string> nums14 = {"flower", "flow", "flight"};
        string res14 = longestCommonPrefix(nums14);

        vector<int> nums448 = {4, 3, 2, 7, 8, 2, 3, 1};
        vector<int> res448 = findDisappearedNumbers(nums448);

        vector<vector<int>> matrix463 = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}};
        int res463 = islandPerimeter(matrix463);

        vector<int> nums628 = {1, 2, 3};
        int res628 = maximumProduct(nums628);

        vector<vector<int>> matrix695 = {
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};
        int res695 = maxAreaOfIsland(matrix695);

        vector<int> nums697 = {1, 2, 2, 3, 1};
        int res697 = findShortestSubArray(nums697);

        vector<int> nums1010 = {30, 20, 150, 100, 40};
        int res1010 = numPairsDivisibleBy60(nums1010);

        vector<int> nums1051 = {1, 1, 4, 2, 1, 3};
        int res1051 = heightChecker(nums1051);

        string res1185 = dayOfTheWeek(31, 8, 2019);

        vector<int> nums1287 = {1, 2, 2, 6, 6, 6, 6, 7, 10};
        int res1287 = findSpecialInteger(nums1287);

        vector<vector<int>> matrix1337 = {{1, 1, 0, 0, 0}, {1, 1, 1, 1, 0}, {1, 0, 0, 0, 0}, {1, 1, 0, 0, 0}, {1, 1, 1, 1, 1}};
        vector<int> res1337 = kWeakestRows(matrix1337, 3);

        vector<int> nums1385_1 = {4, 5, 8};
        vector<int> nums1385_2 = {10, 9, 1, 8};
        int res1385 = findTheDistanceValue(nums1385_1, nums1385_2, 2);
    }

    { //链表综合
        ListNode *list2_1 = new ListNode(2);
        list2_1->next = new ListNode(4);
        list2_1->next->next = new ListNode(3);
        ListNode *list2_2 = new ListNode(5);
        list2_2->next = new ListNode(6);
        list2_2->next->next = new ListNode(4);
        ListNode *res2 = addTwoNumbers(list2_1, list2_2);

        ListNode *list19 = new ListNode(1);
        list19->next = new ListNode(2);
        list19->next->next = new ListNode(3);
        list19->next->next->next = new ListNode(4);
        list19->next->next->next->next = new ListNode(5);
        ListNode *res19 = removeNthFromEnd(list19, 4);

        ListNode *list24 = new ListNode(1);
        list24->next = new ListNode(2);
        list24->next->next = new ListNode(3);
        list24->next->next->next = new ListNode(4);
        list24->next->next->next->next = new ListNode(5);
        ListNode *res24 = swapPairs(list24);

        ListNode *list61 = new ListNode(1);
        list61->next = new ListNode(2);
        list61->next->next = new ListNode(3);
        list61->next->next->next = new ListNode(4);
        list61->next->next->next->next = new ListNode(5);
        ListNode *res61 = rotateRight(list61, 2);

        ListNode *list86 = new ListNode(1);
        list86->next = new ListNode(4);
        list86->next->next = new ListNode(3);
        list86->next->next->next = new ListNode(2);
        list86->next->next->next->next = new ListNode(5);
        list86->next->next->next->next->next = new ListNode(2);
        ListNode *res86 = partition(list86, 3);

        ListNode *list147 = new ListNode(-1);
        list147->next = new ListNode(5);
        list147->next->next = new ListNode(3);
        list147->next->next->next = new ListNode(4);
        list147->next->next->next->next = new ListNode(0);
        ListNode *res147 = insertionSortList(list147);

        ListNode *list234 = new ListNode(1);
        list234->next = new ListNode(2);
        list234->next->next = new ListNode(2);
        list234->next->next->next = new ListNode(1);
        bool res234 = isPalindrome(list234);

        ListNode *list328 = new ListNode(1);
        list328->next = new ListNode(2);
        list328->next->next = new ListNode(3);
        list328->next->next->next = new ListNode(4);
        list328->next->next->next->next = new ListNode(5);
        ListNode *res328 = oddEvenList(list328);

        ListNode *list445_1 = new ListNode(7);
        list445_1->next = new ListNode(2);
        list445_1->next->next = new ListNode(4);
        list445_1->next->next->next = new ListNode(3);
        ListNode *list445_2 = new ListNode(5);
        list445_2->next = new ListNode(6);
        list445_2->next->next = new ListNode(4);
        ListNode *res445 = addTwoNumbersN(list445_1, list445_2);

        ListNode *list725 = new ListNode(1);
        list725->next = new ListNode(2);
        list725->next->next = new ListNode(3);
        list725->next->next->next = new ListNode(4);
        vector<ListNode *> res725 = splitListToParts(list725, 5);

        ListNode *list817 = new ListNode(0);
        list817->next = new ListNode(1);
        list817->next->next = new ListNode(2);
        list817->next->next->next = new ListNode(3);
        vector<int> nums817 = {0, 1, 3};
        int res817 = numComponents(list817, nums817);

        ListNode *list1019 = new ListNode(2);
        list1019->next = new ListNode(1);
        list1019->next->next = new ListNode(5);
        vector<int> res1019 = nextLargerNodes(list1019);

        ListNode *list1171 = new ListNode(1);
        list1171->next = new ListNode(3);
        list1171->next->next = new ListNode(2);
        list1171->next->next->next = new ListNode(-3);
        list1171->next->next->next->next = new ListNode(-2);
        list1171->next->next->next->next->next = new ListNode(5);
        list1171->next->next->next->next->next->next = new ListNode(5);
        list1171->next->next->next->next->next->next->next = new ListNode(-5);
        list1171->next->next->next->next->next->next->next->next = new ListNode(1);
        ListNode *res1171 = removeZeroSumSublists(list1171);
    }

    { //奇特链表
        Node *list430 = new Node(1);
        list430->next = new Node(2);
        list430->next->prev = list430;
        list430->next->next = new Node(3);
        list430->next->next->prev = list430->next;
        list430->next->next->next = new Node(4);
        list430->next->next->next->prev = list430->next->next;
        list430->next->next->next->next = new Node(5);
        list430->next->next->next->next->prev = list430->next->next->next;
        list430->next->next->next->next->next = new Node(6);
        list430->next->next->next->next->next->prev = list430->next->next->next->next;
        list430->next->next->child = new Node(7);
        list430->next->next->child->next = new Node(8);
        list430->next->next->child->next->prev = list430->next->next->child;
        list430->next->next->child->next->next = new Node(9);
        list430->next->next->child->next->next->prev = list430->next->next->child->next;
        list430->next->next->child->next->next->next = new Node(10);
        list430->next->next->child->next->next->next->prev = list430->next->next->child->next->next;
        list430->next->next->child->next->child = new Node(11);
        list430->next->next->child->next->child->next = new Node(12);
        list430->next->next->child->next->child->next->prev = list430->next->next->child->next->child;
        Node *res430 = flatten(list430);

        MyLinkedList *list707 = new MyLinkedList();
        list707->addAtHead(1);
        list707->addAtTail(3);
        list707->addAtIndex(1, 2); //链表变为1-> 2-> 3
        list707->get(1);           //返回2
        list707->deleteAtIndex(1); //现在链表是1-> 3
        list707->get(1);
    }

    { //贪心算法
        string s316 = "bcabc";
        string res316 = removeDuplicateLetters(s316);

        vector<int> nums321_1 = {6, 7};
        vector<int> nums321_2 = {6, 0, 4};
        vector<int> res321 = maxNumber(nums321_1, nums321_2, 5);

        string s402 = "10";
        string res402 = removeKdigits(s402, 1);

        string s763 = "caedbdedda";
        vector<int> res763 = partitionLabels(s763);

        string s767 = "aab";
        string res767 = reorganizeString(s767);
    }

    { //双指针
        string s395 = "aaabb";
        int res395 = longestSubstring(s395, 3);

        string s424 = "ABAB";
        int res424 = characterReplacement(s424, 2);

        vector<int> nums977 = {-4, -1, 0, 3, 10};
        vector<int> res977 = sortedSquares(nums977);
    }

    return 0;
}