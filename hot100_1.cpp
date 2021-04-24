//LeetCode热题HOT100

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <math.h>
#include <algorithm>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//3：字符/数组子串Ⅰ(最长不含重复字符子串)
int lengthOfLongestSubstring(string s)
{
    int length = s.size();
    if (length <= 1)
    {
        return length;
    }
    unordered_map<char, int> letter;
    vector<int> store(length, 0);
    store[0] = 1;
    letter[s[0]] = 0;
    int res = 1;
    for (int i = 1; i < length; ++i)
    {
        if (!letter.count(s[i]))
        {
            store[i] = store[i - 1] + 1;
        }
        else
        {
            store[i] = min(i - letter[s[i]], store[i - 1] + 1);
        }
        res = max(res, store[i]);
        letter[s[i]] = i;
    }
    return res;
}

//5：字符/数组子串Ⅱ(最长回文子串)
string longestPalindrome(string &s, int length, int left, int right)
{
    while (left >= 0 && right < length && s[left] == s[right])
    {
        --left;
        ++right;
    }
    return s.substr(left + 1, right - left - 1);
}
string longestPalindrome(string s)
{
    string res;
    int length = s.size();
    if (length <= 1)
    {
        return s;
    }
    for (int i = 0; i < length; ++i)
    {
        string temp = longestPalindrome(s, length, i, i);
        if (temp.size() > res.size())
        {
            res = temp;
        }
        temp = longestPalindrome(s, length, i, i + 1);
        if (temp.size() > res.size())
        {
            res = temp;
        }
    }
    return res;
}

//76：字符/数组子串Ⅲ(最小覆盖子串)
bool compare(vector<int> &s, vector<int> &t)
{
    for (int i = 0; i < 64; ++i)
    {
        if (s[i] < t[i])
        {
            return false;
        }
    }
    return true;
}
string minWindow(string s, string t)
{
    vector<int> stores(64, 0);
    vector<int> storet(64, 0);
    string res;
    if (s.size() < t.size() || t.size() <= 0)
    {
        return res;
    }
    for (int i = 0; i < t.size(); ++i)
    {
        ++stores[s[i] - 'A'];
        ++storet[t[i] - 'A'];
    }
    if (compare(stores, storet))
    {
        res = s.substr(0, t.size());
    }
    int left = 0, right = t.size() - 1;
    while (right < s.size())
    {
        if (left + t.size() - 1 > right || !compare(stores, storet))
        {
            if (right == s.size() - 1)
            {
                break;
            }
            ++stores[s[right + 1] - 'A'];
            ++right;
        }
        else
        {
            if (res.empty() || res.size() > right - left + 1)
            {
                res = s.substr(left, right - left + 1);
            }
            --stores[s[left] - 'A'];
            ++left;
        }
    }
    return res;
}

//647：字符/数组子串Ⅳ(回文子串总数)
int countSubstrings(string &s, int left, int right)
{
    while (left >= 0 && right < s.size() && s[left] == s[right])
    {
        --left;
        ++right;
    }
    return right - left - 1;
}
int countSubstrings(string s)
{
    int res = 0;
    int length = s.size();
    for (int i = 0; i < length; ++i)
    {
        res += (countSubstrings(s, i, i) + 1) >> 1;
        res += countSubstrings(s, i, i + 1) >> 1;
    }
    return res;
}

//718：字符/数组子串Ⅴ(最长公共子串)(字符不存在输出"-1")
int findLength(vector<int> &A, vector<int> &B)
{
    int length1 = A.size();
    int length2 = B.size();
    int res = 0;
    for (int i = -(length1 - 1); i <= length2 - 1; ++i)
    {
        int temp = 0;
        int store = 0;
        for (int j = max(0, i); j < min(length2, length1 + i); ++j)
        {
            if (A[j - i] == B[j])
            {
                ++store;
            }
            else
            {
                store = 0;
            }
            temp = max(temp, store);
        }
        res = max(res, temp);
    }
    return res;
}
string LCS(string text1, string text2)
{
    int length1 = text1.size();
    int length2 = text2.size();
    string res;
    for (int i = -(length1 - 1); i <= length2 - 1; ++i)
    {
        string temp;
        string store;
        for (int j = max(0, i); j < min(length2, length1 + i); ++j)
        {
            if (text1[j - i] == text2[j])
            {
                store += text1[j - i];
            }
            else
            {
                store.clear();
            }
            if (store.size() > temp.size())
            {
                temp = store;
            }
        }
        if (temp.size() > res.size())
        {
            res = temp;
        }
    }
    return res.empty() ? "-1" : res;
}

//1044：字符/数组子串Ⅵ(最长重复子串,不重叠不能二分重叠能二分)
bool search(string &s, int length, int target)
{
    bool flag = true;
    for (int i = 0; i <= length - 2 * target; ++i)
    {
        for (int j = 0; j < target; ++j)
        {
            if (s[i + j] != s[i + j + target])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            return true;
        }
        else
        {
            flag = true;
        }
    }
    return false;
}
int solve(string s)
{
    int length = s.size();
    if (length <= 1)
    {
        return 0;
    }
    int res = length >> 1;
    while (res)
    {
        if (search(s, length, res))
        {
            return 2 * res;
        }
        --res;
    }
    return 2 * res;
}
bool search(string &s, int length, int target, string &res)
{
    unordered_set<string> store;
    for (int i = 0; i <= length - target; ++i)
    {
        res = s.substr(i, target);
        if (store.count(res))
        {
            return true;
        }
        store.insert(res);
    }
    res.clear();
    return false;
}
string longestDupSubstring(string s)
{
    string res;
    int length = s.size();
    if (!length)
    {
        return res;
    }
    int left = 0;
    int right = length - 1;
    while (left <= right)
    {
        int mid = (left + right) >> 1;
        string temp;
        if (search(s, length, mid, temp))
        {
            res = temp;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return res;
}

//300：最长递增子序列(非连续)
// int lengthOfLIS(vector<int> &nums)
// {
//     int length = nums.size();
//     if (!length)
//     {
//         return 0;
//     }
//     vector<int> store(length, 1);
//     int res = 1;
//     for (int i = 1; i < length; ++i)
//     {
//         for (int j = i - 1; j >= 0; --j)
//         {
//             if (nums[i] > nums[j])
//             {
//                 store[i] = max(store[i], store[j] + 1);
//                 res = max(res, store[i]);
//             }
//         }
//     }
//     return res;
// }
int lengthOfLIS(vector<int> &nums)
{
    int length = nums.size();
    if (!length)
    {
        return 0;
    }
    vector<int> store(length, 0);
    store[0] = nums[0];
    int len = 0;
    for (int i = 1; i < length; ++i)
    {
        if (nums[i] > store[len])
        {
            store[len + 1] = nums[i];
            ++len;
        }
        else
        {
            int left = 0, right = len - 1;
            while (left <= right)
            {
                int middle = (left + right) >> 1;
                if (store[middle] < nums[i])
                {
                    left = middle + 1;
                }
                else
                {
                    right = middle - 1;
                }
            }
            store[left] = nums[i];
        }
    }
    return len + 1;
}

//最长公共子序列
int longestCommonSubsequence(string text1, string text2)
{
    vector<vector<int>> store(text1.size() + 1, vector<int>(text2.size() + 1, 0));
    for (int i = 1; i <= text1.size(); ++i)
    {
        for (int j = 1; j <= text2.size(); ++j)
        {
            if (text1[i - 1] == text2[j - 1])
            {
                store[i][j] = store[i - 1][j - 1] + 1;
            }
            else
            {
                store[i][j] = max(store[i - 1][j], store[i][j - 1]);
            }
        }
    }
    return store[text1.size()][text2.size()];
}

//11：接雨水Ⅰ(两个柱子能接多少水)
int maxArea(vector<int> &height)
{
    int length = height.size();
    if (length <= 1)
    {
        return 0;
    }
    int left = 0;
    int right = length - 1;
    int res = (right - left) * min(height[left], height[right]);
    while (left < right)
    {
        if (height[left] < height[right])
        {
            ++left;
        }
        else
        {
            --right;
        }
        res = max(res, (right - left) * min(height[left], height[right]));
    }
    return res;
}

//42：接雨水Ⅱ(所有柱子能接多少水)
// int trap(vector<int> &height)
// {
//     int length = height.size();
//     if (length <= 2)
//     {
//         return 0;
//     }
//     int res = 0;
//     vector<int> storel(length, 0);
//     vector<int> storer(length, 0);
//     int left = height[0];
//     for (int i = 1; i < length - 1; ++i)
//     {
//         storel[i] = left;
//         left = max(left, height[i]);
//     }
//     int right = height[length - 1];
//     for (int i = length - 2; i > 0; --i)
//     {
//         storer[i] = right;
//         right = max(right, height[i]);
//     }
//     for (int i = 1; i <= length - 2; ++i)
//     {
//         res += max(0, min(storel[i], storer[i]) - height[i]);
//     }
//     return res;
// }
int trap(vector<int> &height)
{
    int length = height.size();
    if (length <= 2)
    {
        return 0;
    }
    int res = 0;
    int left = 1, right = length - 2;
    int lmax = height[0], rmax = height[length - 1];
    while (left < right)
    {
        if (lmax <= rmax)
        {
            res += max(0, lmax - height[left]);
            lmax = max(lmax, height[left]);
            ++left;
        }
        else
        {
            res += max(0, rmax - height[right]);
            rmax = max(rmax, height[right]);
            --right;
        }
    }
    return res;
}

//407：接雨水Ⅲ(二维空间所有柱子能接多少水)(不能由一维到二维,无题解,放弃)
int trapRainWater(vector<vector<int>> &heightMap)
{
    if (!heightMap.size() || !heightMap[0].size())
    {
        return 0;
    }
    int length1 = heightMap.size();
    int length2 = heightMap[0].size();
    if (length1 <= 2 || length2 <= 2)
    {
        return 0;
    }
    int res = 0;
    vector<vector<int>> store(length1, vector<int>(length2, 0));
    for (int i = 1; i <= length1 - 2; ++i)
    {
        int left = 1, right = length2 - 2;
        int lmax = heightMap[i][0], rmax = heightMap[i][length2 - 1];
        while (left <= right)
        {
            if (lmax <= rmax)
            {
                store[i][left] = lmax;
                lmax = max(lmax, heightMap[i][left]);
                ++left;
            }
            else
            {
                store[i][right] = rmax;
                rmax = max(rmax, heightMap[i][right]);
                --right;
            }
        }
    }
    for (int i = 1; i <= length2 - 2; ++i)
    {
        int up = 1, down = length1 - 2;
        int umax = heightMap[0][i], dmax = heightMap[length1 - 1][i];
        while (up <= down)
        {
            if (umax <= dmax)
            {
                res += max(0, min(store[up][i], umax) - heightMap[up][i]);
                umax = max(umax, heightMap[up][i]);
                ++up;
            }
            else
            {
                res += max(0, min(store[down][i], dmax) - heightMap[down][i]);
                dmax = max(dmax, heightMap[down][i]);
                --down;
            }
        }
    }
    return res;
}

//20：有效的括号
bool isValid(string s)
{
    stack<char> store;
    int length = s.size();
    if (length & 1)
    {
        return false;
    }
    for (int i = 0; i < length; ++i)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            store.push(s[i]);
        }
        else if (!store.empty() && ((s[i] == ')' && store.top() == '(') ||
                                    (s[i] == ']' && store.top() == '[') ||
                                    (s[i] == '}' && store.top() == '{')))
        {
            store.pop();
        }
        else
        {
            return false;
        }
    }
    return store.empty();
}

//22：括号生成
void dfs(int target, string &store, vector<string> &res, int left, int right)
{
    if (left == target && right == target)
    {
        res.push_back(store);
        return;
    }
    if (left == right)
    {
        store.push_back('(');
        dfs(target, store, res, left + 1, right);
        store.pop_back();
    }
    else if (left > right && left < target)
    {
        store.push_back('(');
        dfs(target, store, res, left + 1, right);
        store.pop_back();
        store.push_back(')');
        dfs(target, store, res, left, right + 1);
        store.pop_back();
    }
    else if (left > right && left == target)
    {
        store.push_back(')');
        dfs(target, store, res, left, right + 1);
        store.pop_back();
    }
}
vector<string> generateParenthesis(int n)
{
    vector<string> res;
    string store;
    dfs(n, store, res, 0, 0);
    return res;
}

//32：最长有效括号
int longestValidParentheses(string s)
{
    int res = 0;
    int length = s.size();
    if (length <= 1)
    {
        return res;
    }
    stack<int> store;
    store.push(-1);
    for (int i = 0; i < length; ++i)
    {
        if (s[i] == '(')
        {
            store.push(i);
        }
        else
        {
            store.pop();
            if (store.empty())
            {
                store.push(i);
            }
            else
            {
                res = max(res, i - store.top());
            }
        }
    }
    return res;
}

//301：删除无效的括号(flag:(比)多的个数)
void dfs(string &s, string temp, unordered_set<string> &res, int index, int flag, int ltarget, int rtarget)
{
    if (!flag && !ltarget && !rtarget && index == s.size())
    {
        res.insert(temp);
        return;
    }
    else if (flag < 0 || index > s.size() || ltarget < 0 || rtarget < 0)
    {
        return;
    }
    if (s[index] == '(')
    {
        dfs(s, temp + s[index], res, index + 1, flag + 1, ltarget, rtarget);
        dfs(s, temp, res, index + 1, flag, ltarget - 1, rtarget);
    }
    else if (s[index] == ')')
    {
        dfs(s, temp + s[index], res, index + 1, flag - 1, ltarget, rtarget);
        dfs(s, temp, res, index + 1, flag, ltarget, rtarget - 1);
    }
    else
    {
        dfs(s, temp + s[index], res, index + 1, flag, ltarget, rtarget);
    }
}
vector<string> removeInvalidParentheses(string s)
{
    unordered_set<string> res;
    int length = s.size();
    int leftDelete = 0, rightDelete = 0;
    for (int i = 0; i < length; ++i)
    {
        if (s[i] == '(')
        {
            ++leftDelete;
        }
        else if (s[i] == ')')
        {
            if (leftDelete > 0)
            {
                --leftDelete;
            }
            else
            {
                ++rightDelete;
            }
        }
    }
    string temp;
    dfs(s, temp, res, 0, 0, leftDelete, rightDelete);
    return vector<string>(res.begin(), res.end());
}

//39：组合总和Ⅰ(无限被选取)
void combinationSum(vector<vector<int>> &res, vector<int> &temp, int target, vector<int> &nums, int index)
{
    if (target == 0)
    {
        res.push_back(temp);
        return;
    }
    else if (target < 0 || index >= nums.size())
    {
        return;
    }
    combinationSum(res, temp, target, nums, index + 1);
    if (target >= nums[index])
    {
        temp.push_back(nums[index]);
        combinationSum(res, temp, target - nums[index], nums, index);
        temp.pop_back();
    }
}
vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    vector<vector<int>> res;
    if (!target || !candidates.size())
    {
        return res;
    }
    vector<int> temp;
    combinationSum(res, temp, target, candidates, 0);
    return res;
}

//40：组合总和Ⅱ(只选取一次)
void combinationSum2(vector<vector<int>> &res, vector<int> &temp, int target, vector<int> &nums, int index)
{
    if (target == 0)
    {
        res.push_back(temp);
        return;
    }
    else if (target < 0 || index >= nums.size())
    {
        return;
    }
    int count = index + 1;
    while (count < nums.size() && nums[count] == nums[index])
    {
        ++count;
    }
    for (int i = 0; i <= count - index; ++i)
    {
        temp.insert(temp.end(), i, nums[index]);
        combinationSum2(res, temp, target - i * nums[index], nums, count);
        for (int j = 0; j < i; ++j)
        {
            temp.pop_back();
        }
    }
}
vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
{
    vector<vector<int>> res;
    if (!candidates.size() || !target)
    {
        return res;
    }
    sort(candidates.begin(), candidates.end());
    vector<int> temp;
    combinationSum2(res, temp, target, candidates, 0);
    return res;
}

//216：组合总和Ⅲ(1~9的组合限定个数)
void combinationSum3(vector<vector<int>> &res, vector<int> &temp, int k, int n, int index)
{
    if (k == 0 && n == 0)
    {
        res.push_back(temp);
        return;
    }
    else if (k <= 0 || n <= 0 || index > 9)
    {
        return;
    }
    combinationSum3(res, temp, k, n, index + 1);
    temp.push_back(index);
    combinationSum3(res, temp, k - 1, n - index, index + 1);
    temp.pop_back();
}
vector<vector<int>> combinationSum3(int k, int n)
{
    vector<vector<int>> res;
    if (k > 9 || n > 45)
    {
        return res;
    }
    vector<int> temp;
    combinationSum3(res, temp, k, n, 1);
    return res;
}

//377：组合总和Ⅳ(无限背包)
int combinationSum4(vector<int> &nums, int target)
{
    vector<int> store(target + 1, 0);
    store[0] = 1;
    int length = nums.size();
    for (int i = 1; i <= target; ++i)
    {
        for (int j = 0; j < length; ++j)
        {
            if (i >= nums[j] && store[i] <= INT_MAX >> 1)
            {
                store[i] += store[i - nums[j]];
            }
        }
    }
    return store[target];
}

//41：缺失的第一个正数(从1开始有重复)
int firstMissingPositive(vector<int> &nums)
{
    int length = nums.size();
    for (int i = 0; i < length; ++i)
    {
        while (1 <= nums[i] && nums[i] <= length && (i + 1) != nums[i] && nums[i] != nums[nums[i] - 1])
        {
            swap(nums[i], nums[nums[i] - 1]);
        }
    }
    for (int i = 0; i < length; ++i)
    {
        if ((i + 1) != nums[i])
        {
            return i + 1;
        }
    }
    return length + 1;
}

//268：缺失的数字(从0开始无重复)
int missingNumber(vector<int> &nums)
{
    int length = nums.size();
    for (int i = 0; i < length; ++i)
    {
        while (nums[i] != length && i != nums[i])
        {
            swap(nums[i], nums[nums[i]]);
        }
    }
    for (int i = 0; i < length; ++i)
    {
        if (i != nums[i])
        {
            return i;
        }
    }
    return length;
}

//96：不同的二叉搜索树
int numTrees(int n)
{
    vector<int> store(n + 1, 0);
    store[0] = store[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            store[i] += store[j - 1] * store[i - j];
        }
    }
    return store[n];
}

//114：二叉树展开为链表
void flatten(TreeNode *root)
{
    while (root)
    {
        if (!root->right)
        {
            root->right = root->left;
            root->left = NULL;
        }
        else if (root->left && root->right)
        {
            TreeNode *temp = root->left;
            while (temp->right)
            {
                temp = temp->right;
            }
            temp->right = root->right;
            root->right = root->left;
            root->left = NULL;
        }
        root = root->right;
    }
}

//199：二叉树的右视图
vector<int> rightSideView(TreeNode *root)
{
    vector<int> res;
    if (!root)
    {
        return res;
    }
    queue<TreeNode *> store;
    store.push(root);
    while (!store.empty())
    {
        int length = store.size();
        int val = 0;
        while (length--)
        {
            TreeNode *temp = store.front();
            store.pop();
            if (!length)
            {
                val = temp->val;
            }
            if (temp->left)
            {
                store.push(temp->left);
            }
            if (temp->right)
            {
                store.push(temp->right);
            }
        }
        res.push_back(val);
    }
    return res;
}

//222：完全二叉树的节点个数
bool findNodes(TreeNode *root, int target, int k)
{
    for (int i = k - 2; i >= 0; --i)
    {
        if (target & (1 << i))
        {
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }
    return root != NULL;
}
int countNodes(TreeNode *root)
{
    if (!root)
    {
        return 0;
    }
    int k = 0;
    TreeNode *temp = root;
    while (temp)
    {
        temp = temp->left;
        ++k;
    }
    int left = pow(2, k - 1);
    int right = pow(2, k) - 1;
    while (left <= right)
    {
        int mid = left + ((right - left) >> 1);
        if (findNodes(root, mid, k))
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return right;
}

//230：二叉搜索树中第k小的元素
void dfs(TreeNode *root, int &target, int &res)
{
    if (!root || target <= 0)
    {
        return;
    }
    dfs(root->left, target, res);
    --target;
    if (!target)
    {
        res = root->val;
        return;
    }
    dfs(root->right, target, res);
}
int kthSmallest(TreeNode *root, int k)
{
    int res = 0;
    dfs(root, k, res);
    return res;
}

//257：二叉树的所有路径
void dfs(TreeNode *root, vector<string> &store, string s)
{
    if (!root)
    {
        return;
    }
    s += to_string(root->val);
    if (!root->left && !root->right)
    {
        store.push_back(s);
        return;
    }
    s += "->";
    dfs(root->left, store, s);
    dfs(root->right, store, s);
}
vector<string> binaryTreePaths(TreeNode *root)
{
    vector<string> res;
    if (!root)
    {
        return res;
    }
    dfs(root, res, "");
    return res;
}

//347：路径总和
int dfs(TreeNode *root, unordered_map<int, int> &store, int &count, int sum)
{
    if (!root)
    {
        return 0;
    }
    int res = 0;
    count += root->val;
    if (count == sum)
    {
        ++res;
    }
    if (store.count(count - sum))
    {
        res += store[count - sum];
    }
    if (store.count(count))
    {
        ++store[count];
    }
    else
    {
        store[count] = 1;
    }
    int left = dfs(root->left, store, count, sum);
    int right = dfs(root->right, store, count, sum);
    --store[count];
    count -= root->val;
    return res + left + right;
}
int pathSum(TreeNode *root, int sum)
{
    unordered_map<int, int> store;
    int count = 0;
    return dfs(root, store, count, sum);
}

//501：二叉搜索树中的众数
void dfs(TreeNode *root, int &value, int &count, int &maxCount, vector<int> &res)
{
    if (!root)
    {
        return;
    }
    dfs(root->left, value, count, maxCount, res);
    if (root->val == value)
    {
        ++count;
    }
    else
    {
        value = root->val;
        count = 1;
    }
    if (count > maxCount)
    {
        maxCount = count;
        res = {value};
    }
    else if (count == maxCount && res.back() != value)
    {
        res.push_back(value);
    }
    dfs(root->right, value, count, maxCount, res);
}
vector<int> findMode(TreeNode *root)
{
    vector<int> res;
    if (!root)
    {
        return res;
    }
    int value = 0, count = 0, maxCount = 0;
    dfs(root, value, count, maxCount, res);
    return res;
}

//538：把二叉搜索树转换为累加树
void dfs(TreeNode *root, int &count)
{
    if (!root)
    {
        return;
    }
    dfs(root->right, count);
    root->val += count;
    count = root->val;
    dfs(root->left, count);
}
TreeNode *convertBST(TreeNode *root)
{
    int count = 0;
    dfs(root, count);
    return root;
}

//617：合并二叉树
void dfs(TreeNode *root1, TreeNode *root2, TreeNode *&res)
{
    if (!root1 && !root2)
    {
        return;
    }
    else if (!root1)
    {
        res = new TreeNode(root2->val);
        dfs(NULL, root2->left, res->left);
        dfs(NULL, root2->right, res->right);
    }
    else if (!root2)
    {
        res = new TreeNode(root1->val);
        dfs(root1->left, NULL, res->left);
        dfs(root1->right, NULL, res->right);
    }
    else
    {
        res = new TreeNode(root1->val + root2->val);
        dfs(root1->left, root2->left, res->left);
        dfs(root1->right, root2->right, res->right);
    }
}
TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2)
{
    TreeNode *res = NULL;
    dfs(root1, root2, res);
    return res;
}

//121：买卖股票的最佳时机Ⅰ(单次买卖)(同剑指offer63)
int maxProfit1(vector<int> &prices)
{
    int res = 0;
    int length = prices.size();
    if (!length)
    {
        return res;
    }
    int minBefore = prices[0];
    for (int i = 1; i < length; ++i)
    {
        res = max(res, prices[i] - minBefore);
        minBefore = min(minBefore, prices[i]);
    }
    return res;
}

//122：买卖股票的最佳时机Ⅱ(多次买卖)
int maxProfit2(vector<int> &prices)
{
    int res = 0;
    int length = prices.size();
    for (int i = 1; i < length; ++i)
    {
        res += max(0, prices[i] - prices[i - 1]);
    }
    return res;
}

//309：买卖股票的最佳时机Ⅲ(多次买卖有冷冻期)
int maxProfit3(vector<int> &prices)
{
    int length = prices.size();
    if (!length)
    {
        return 0;
    }
    int store1 = -prices[0]; //当天持有
    int store2 = 0;          //当天卖出
    int store3 = 0;          //当天未卖出且不持有
    for (int i = 1; i < length; ++i)
    {
        int temp1 = store1;
        int temp2 = store2;
        int temp3 = store3;
        store1 = max(temp1, temp3 - prices[i]);
        store2 = temp1 + prices[i];
        store3 = max(temp2, temp3);
    }
    return max(store2, store3);
}

//714：买卖股票的最佳时机Ⅳ(多次买卖有手续费)
int maxProfit4(vector<int> &prices, int fee)
{
    int length = prices.size();
    if (!length)
    {
        return 0;
    }
    int store1 = -prices[0] - fee; //当天持有
    int store2 = 0;                //当天不持有
    for (int i = 1; i < length; ++i)
    {
        int temp1 = store1;
        int temp2 = store2;
        store1 = max(temp1, temp2 - prices[i] - fee);
        store2 = max(temp1 + prices[i], temp2);
    }
    return store2;
}

//123：买卖股票的最佳时机Ⅴ(最多两次买卖)
int maxProfit5(vector<int> &prices)
{
    int length = prices.size();
    if (!length)
    {
        return 0;
    }
    int store0 = 0;          //未进行买卖
    int store1 = -prices[0]; //第一次持有
    int store2 = 0;          //第一次卖出后
    int store3 = -prices[0]; //第二次持有
    int store4 = 0;          //第二次卖出后
    for (int i = 1; i < length; ++i)
    {
        int temp1 = store1;
        int temp2 = store2;
        int temp3 = store3;
        int temp4 = store4;
        store1 = max(0 - prices[i], temp1);
        store2 = max(temp1 + prices[i], temp2);
        store3 = max(temp2 - prices[i], temp3);
        store4 = max(temp3 + prices[i], temp4);
    }
    return max(store2, store4);
}

//188：买卖股票的最佳时机Ⅵ(最多k次买卖)
int maxProfit6(int k, vector<int> &prices)
{
    int length = prices.size();
    if (length < 2 || !k)
    {
        return 0;
    }
    k = min(length >> 1, k);
    vector<int> store1(k, -prices[0]);
    vector<int> store2(k, 0);
    for (int i = 1; i < length; ++i)
    {
        for (int j = k - 1; j > 0; --j)
        {
            store2[j] = max(store1[j] + prices[i], store2[j]);
            store1[j] = max(store2[j - 1] - prices[i], store1[j]);
        }
        store2[0] = max(store1[0] + prices[i], store2[0]);
        store1[0] = max(0 - prices[i], store1[0]);
        // store1[1] = max(store2[0] - prices[i], store1[1]);
        // store2[1] = max(store1[1] + prices[i], store2[1]);
    }
    int res = 0;
    for (int i = 0; i < k; ++i)
    {
        res = max(store2[i], res);
    }
    return res;
}

//198：打家劫舍Ⅰ(打劫一排房屋)
int rob1(vector<int> &nums)
{
    int length = nums.size();
    if (!length)
    {
        return 0;
    }
    else if (length == 1)
    {
        return nums[0];
    }
    int store1 = nums[0];
    int store2 = max(nums[0], nums[1]);
    int res = store2;
    for (int i = 2; i < length; ++i)
    {
        int temp = store2;
        store2 = max(store2, store1 + nums[i]);
        store1 = temp;
        res = max(res, store2);
    }
    return res;
}

//213：打家劫舍Ⅱ(打劫一圈房屋)
int rob2(vector<int> &nums)
{
    int length = nums.size();
    if (length <= 3)
    {
        int res = 0;
        for (int i = 0; i < length; ++i)
        {
            res = max(res, nums[i]);
        }
        return res;
    }
    int store1 = nums[0];
    int store2 = max(nums[0], nums[1]);
    int res1 = store2;
    for (int i = 2; i <= length - 2; ++i)
    {
        int temp = store2;
        store2 = max(store2, store1 + nums[i]);
        store1 = temp;
        res1 = max(res1, store2);
    }
    store1 = nums[1];
    store2 = max(nums[1], nums[2]);
    int res2 = store2;
    for (int i = 3; i <= length - 1; ++i)
    {
        int temp = store2;
        store2 = max(store2, store1 + nums[i]);
        store1 = temp;
        res2 = max(res2, store2);
    }
    return max(res1, res2);
}

//337：打家劫舍Ⅲ(打劫树状房屋)
vector<int> dfs(TreeNode *root)
{
    if (!root)
    {
        return vector<int>{0, 0};
    }
    vector<int> left = dfs(root->left);
    vector<int> right = dfs(root->right);
    int f = left[1] + right[1] + root->val;
    int g = max(left[0], left[1]) + max(right[0], right[1]);
    return vector<int>{f, g};
}
int rob3(TreeNode *root)
{
    vector<int> res = dfs(root);
    return max(res[0], res[1]);
}

//416：分割等和子集(0-1背包)
bool canPartition(vector<int> &nums)
{
    int length = nums.size();
    if (length <= 1)
    {
        return false;
    }
    int target = nums[0];
    for (int i = 1; i < length; ++i)
    {
        target += nums[i];
    }
    if (target & 1)
    {
        return false;
    }
    target = target >> 1;
    vector<bool> store(target + 1, false);
    store[0] = true;
    for (int i = 0; i < length; ++i)
    {
        for (int j = target; j >= 1; --j)
        {
            if (j >= nums[i] && store[j - nums[i]])
            {
                store[j] = store[j - nums[i]];
            }
        }
    }
    return store[target];
}

//474：一和零(0-1背包)
void count(const string &s, int &mIndex, int &nIndex)
{
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '0')
        {
            ++mIndex;
        }
        else if (s[i] == '1')
        {
            ++nIndex;
        }
    }
}
int findMaxForm(vector<string> &strs, int m, int n)
{
    vector<vector<int>> store(m + 1, vector<int>(n + 1, 0));
    int length = strs.size();
    int res = 0;
    for (int i = 0; i < length; ++i)
    {
        int mIndex = 0, nIndex = 0;
        count(strs[i], mIndex, nIndex);
        for (int j = m; j >= mIndex; --j)
        {
            for (int k = n; k >= nIndex; --k)
            {
                if ((!(j - mIndex) && !(k - nIndex)) || store[j - mIndex][k - nIndex])
                {
                    store[j][k] = max(store[j][k], store[j - mIndex][k - nIndex] + 1);
                    res = max(res, store[j][k]);
                }
            }
        }
    }
    return res;
}

//494：目标和(0-1背包)
int findTargetSumWays(vector<int> &nums, int S)
{
    int length = nums.size();
    if (!length)
    {
        return 0;
    }
    int sum = nums[0];
    for (int i = 1; i < length; ++i)
    {
        sum += nums[i];
    }
    if (S > abs(sum))
    {
        return 0;
    }
    vector<int> store1(2 * sum + 1, 0);
    vector<int> store2(2 * sum + 1, 0);
    ++store1[sum + nums[0]];
    ++store1[sum - nums[0]];
    int flag = 1;
    for (int i = 1; i < length; ++i)
    {
        if (flag)
        {
            fill(store2.begin(), store2.end(), 0);
        }
        else
        {
            fill(store1.begin(), store1.end(), 0);
        }
        for (int j = 0; j <= 2 * sum; ++j)
        {
            if (flag)
            {
                if (store1[j])
                {
                    store2[j + nums[i]] += store1[j];
                    store2[j - nums[i]] += store1[j];
                }
            }
            else
            {
                if (store2[j])
                {
                    store1[j + nums[i]] += store2[j];
                    store1[j - nums[i]] += store2[j];
                }
            }
        }
        flag = 1 - flag;
    }
    return flag ? store1[sum + S] : store2[sum + S];
}

//139：单词拆分(无限背包)
bool wordBreak(string s, vector<string> &wordDict)
{
    unordered_set<string> store;
    for (int i = 0; i < wordDict.size(); ++i)
    {
        store.insert(wordDict[i]);
    }
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true;
    for (int i = 1; i <= s.size(); ++i)
    {
        for (int j = i - 1; j >= 0; --j)
        {
            if (store.count(s.substr(j, i - j)) && dp[j])
            {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[s.size()];
}

//322：零钱兑换Ⅰ(无限背包之最少硬币)
int coinChange(vector<int> &coins, int amount)
{
    int myMax = amount + 1;
    vector<int> store(amount + 1, myMax);
    store[0] = 0;
    int length = coins.size();
    for (int i = 1; i <= amount; ++i)
    {
        for (int j = 0; j < length; ++j)
        {
            if (i >= coins[j])
            {
                store[i] = min(store[i], store[i - coins[j]] + 1);
            }
        }
    }
    return store[amount] > amount ? -1 : store[amount];
}

//518：零钱兑换Ⅱ(无限背包之方案总数)
int change(int amount, vector<int> &coins)
{
    int length = coins.size();
    vector<int> store(amount + 1, 0);
    store[0] = 1;
    for (int i = 0; i < length; ++i)
    {
        for (int j = 0; j <= amount - coins[i]; ++j)
        {
            if (store[j])
            {
                store[j + coins[i]] += store[j];
            }
        }
    }
    return store[amount];
}

int main()
{
    { //字符子串
        string s3 = "abcabcbb";
        int res3 = lengthOfLongestSubstring(s3);

        string s5 = "babad";
        string res5 = longestPalindrome(s5);

        string s76_1 = "ADOBECODEBANC";
        string s76_2 = "ABC";
        string res76 = minWindow(s76_1, s76_2);

        string s647 = "abc";
        int res647 = countSubstrings(s647);

        vector<int> nums718_1 = {1, 2, 3, 2, 1};
        vector<int> nums718_2 = {3, 2, 1, 4, 7};
        int res718_1 = findLength(nums718_1, nums718_2);
        string s718_1 = "1AB2345CD";
        string s718_2 = "12345EF";
        string res718_2 = LCS(s718_1, s718_2);

        string s1044_1 = "ababc";
        int res1044_1 = solve(s1044_1);
        string s1044_2 = "banana";
        string res1044_2 = longestDupSubstring(s1044_2);
    }

    { //子序列
        vector<int> nums300 = {0, 1, 0, 3, 2, 3};
        int res300 = lengthOfLIS(nums300);

        string s1143_1 = "abcde";
        string s1143_2 = "ace";
        int res1143 = longestCommonSubsequence(s1143_1, s1143_2);
    }

    { //接雨水
        vector<int> nums11 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        int res11 = maxArea(nums11);

        vector<int> nums42 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        int res42 = trap(nums42);

        vector<vector<int>> matrix407 = {{1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}};
        int res407 = trapRainWater(matrix407);
    }

    { //括号
        string s20 = "()[]{}";
        bool res20 = isValid(s20);

        vector<string> res22 = generateParenthesis(3);

        string s32 = "(()";
        int res32 = longestValidParentheses(s32);

        string s301 = "()())()";
        vector<string> res301 = removeInvalidParentheses(s301);
    }

    { //组合总和
        vector<int> nums39 = {2, 3, 6, 7};
        vector<vector<int>> res39 = combinationSum(nums39, 7);

        vector<int> nums40 = {2, 3, 6, 7};
        vector<vector<int>> res40 = combinationSum2(nums40, 7);

        vector<vector<int>> res216 = combinationSum3(3, 7);

        vector<int> nums377 = {3, 33, 333};
        int res377 = combinationSum4(nums377, 10000);
    }

    { //缺失的数字(未排序换位,排序二分)
        vector<int> nums41 = {1, 2, 0};
        int res41 = firstMissingPositive(nums41);

        vector<int> nums268 = {3, 0, 1};
        int res268 = missingNumber(nums268);
    }

    { //二叉树
        int res96 = numTrees(3);

        TreeNode *tree114 = new TreeNode(1);
        tree114->left = new TreeNode(2);
        tree114->right = new TreeNode(5);
        tree114->left->left = new TreeNode(3);
        tree114->left->right = new TreeNode(4);
        tree114->right->right = new TreeNode(6);
        flatten(tree114);

        TreeNode *tree199 = new TreeNode(1);
        tree199->left = new TreeNode(2);
        tree199->right = new TreeNode(3);
        tree199->left->right = new TreeNode(5);
        tree199->right->right = new TreeNode(4);
        vector<int> res199 = rightSideView(tree199);

        TreeNode *tree222 = new TreeNode(1);
        tree222->left = new TreeNode(2);
        tree222->right = new TreeNode(3);
        tree222->left->left = new TreeNode(4);
        tree222->left->right = new TreeNode(5);
        tree222->right->left = new TreeNode(6);
        int res222 = countNodes(tree222);

        TreeNode *tree230 = new TreeNode(3);
        tree230->left = new TreeNode(1);
        tree230->right = new TreeNode(4);
        tree230->left->right = new TreeNode(2);
        int res230 = kthSmallest(tree230, 1);

        TreeNode *tree257 = new TreeNode(1);
        tree257->left = new TreeNode(2);
        tree257->right = new TreeNode(3);
        tree257->left->right = new TreeNode(5);
        vector<string> res257 = binaryTreePaths(tree257);

        TreeNode *tree347 = new TreeNode(10);
        tree347->left = new TreeNode(5);
        tree347->right = new TreeNode(-3);
        tree347->left->left = new TreeNode(3);
        tree347->left->right = new TreeNode(2);
        tree347->right->right = new TreeNode(11);
        tree347->left->left->left = new TreeNode(3);
        tree347->left->left->right = new TreeNode(-2);
        tree347->left->right->right = new TreeNode(1);
        int res347 = pathSum(tree347, 8);

        TreeNode *tree501 = new TreeNode(1);
        tree501->right = new TreeNode(2);
        tree501->right->left = new TreeNode(2);
        vector<int> res501 = findMode(tree501);

        TreeNode *tree538 = new TreeNode(4);
        tree538->left = new TreeNode(1);
        tree538->right = new TreeNode(6);
        tree538->left->left = new TreeNode(0);
        tree538->left->right = new TreeNode(2);
        tree538->right->left = new TreeNode(5);
        tree538->right->right = new TreeNode(7);
        tree538->left->right->right = new TreeNode(3);
        tree538->right->right->right = new TreeNode(8);
        TreeNode *res538 = convertBST(tree538);

        TreeNode *tree617_1 = new TreeNode(1);
        tree617_1->left = new TreeNode(3);
        tree617_1->right = new TreeNode(2);
        tree617_1->left->left = new TreeNode(5);
        TreeNode *tree617_2 = new TreeNode(2);
        tree617_2->left = new TreeNode(1);
        tree617_2->right = new TreeNode(3);
        tree617_2->left->right = new TreeNode(4);
        tree617_2->right->right = new TreeNode(7);
        TreeNode *res617 = mergeTrees(tree617_1, tree617_2);
    }

    { //买卖股票
        vector<int> nums121 = {7, 1, 5, 3, 6, 4};
        int res121 = maxProfit1(nums121);

        vector<int> nums122 = {7, 1, 5, 3, 6, 4};
        int res122 = maxProfit2(nums122);

        vector<int> nums309 = {1, 2, 3, 0, 2};
        int res309 = maxProfit3(nums309);

        vector<int> nums714 = {1, 3, 2, 8, 4, 9};
        int res714 = maxProfit4(nums714, 2);

        vector<int> nums123 = {3, 3, 5, 0, 0, 3, 1, 4};
        int res123 = maxProfit5(nums123);

        vector<int> nums124 = {2, 4, 1};
        int res124 = maxProfit6(2, nums124);
    }

    { //打家劫舍
        vector<int> nums198 = {1, 2, 3, 1};
        int res198 = rob1(nums198);

        vector<int> nums213 = {1, 2, 3, 1};
        int res213 = rob2(nums213);

        TreeNode *tree337 = new TreeNode(3);
        tree337->left = new TreeNode(2);
        tree337->right = new TreeNode(3);
        tree337->left->right = new TreeNode(3);
        tree337->right->right = new TreeNode(1);
        int res337 = rob3(tree337);
    }

    { //背包问题
        vector<int> nums416 = {1, 5, 11, 5};
        bool res416 = canPartition(nums416);

        vector<string> nums474 = {"10", "0001", "111001", "1", "0"};
        int res474 = findMaxForm(nums474, 5, 5);

        vector<int> nums494 = {1, 1, 1, 1, 1};
        int res494 = findTargetSumWays(nums494, 3);

        string s139 = "leetcode";
        vector<string> nums139 = {"leet", "code"};
        bool res139 = wordBreak(s139, nums139);

        vector<int> nums322 = {1, 2, 5};
        int res322 = coinChange(nums322, 11);

        vector<int> nums518 = {1, 2, 5};
        int res518 = change(5, nums518);
    }

    return 0;
}
