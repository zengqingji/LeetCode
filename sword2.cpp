//剑指Offer

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//面试题34：二叉树中和为某一值的路径(注意是叶子结点)
void pathSum(TreeNode *root, int sum, vector<vector<int>> &res, vector<int> &tempRes, int count)
{
    count += root->val;
    tempRes.push_back(root->val);
    if (count == sum && !root->left && !root->right)
    {
        res.push_back(tempRes);
    }
    if (root->left)
    {
        pathSum(root->left, sum, res, tempRes, count);
    }
    if (root->right)
    {
        pathSum(root->right, sum, res, tempRes, count);
    }
    count -= root->val;
    tempRes.pop_back();
    return;
}
vector<vector<int>> pathSum(TreeNode *root, int sum)
{
    vector<vector<int>> res;
    vector<int> tempRes;
    if (!root)
    {
        return res;
    }
    pathSum(root, sum, res, tempRes, 0);
    return res;
}

//面试题35：复杂链表的复制(三步走)
class Node1
{
public:
    int val;
    Node1 *next;
    Node1 *random;
    Node1() {}
    Node1(int _val) : val(_val), next(NULL), random(NULL) {}
};
Node1 *copyRandomList(Node1 *head)
{
    if (!head)
    {
        return NULL;
    }
    Node1 *traverse1 = head;
    while (traverse1)
    {
        Node1 *temp = traverse1->next;
        traverse1->next = new Node1(traverse1->val);
        traverse1->next->next = temp;
        traverse1 = traverse1->next->next;
    }

    traverse1 = head;
    while (traverse1)
    {
        if (traverse1->random)
        {
            traverse1->next->random = traverse1->random->next;
        }
        traverse1 = traverse1->next->next;
    }

    Node1 *res = head->next;
    traverse1 = head;
    Node1 *traverse2 = res;
    while (traverse2->next)
    {
        traverse1->next = traverse2->next;
        traverse2->next = traverse2->next->next;
        traverse1 = traverse1->next;
        traverse2 = traverse2->next;
    }
    traverse1->next = NULL;
    return res;
}

//面试题36：二叉搜索树与双向链表(还需两个节点,一个是整个链表头节点,还有一个是当前节点的前一个节点)
class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node() {}
    Node(int _val) : val(_val), left(NULL), right(NULL) {}
    Node(int _val, Node *_left, Node *_right) : val(_val), left(_left), right(_right) {}
};
void treeToDoubleList(Node *root, Node *&head, Node *&pre)
{
    if (!root)
    {
        return;
    }
    treeToDoubleList(root->left, head, pre);
    if (!pre)
    {
        head = root;
    }
    else
    {
        pre->right = root;
        root->left = pre;
    }
    pre = root;
    treeToDoubleList(root->right, head, pre);
    return;
}
Node *treeToDoublyList(Node *root)
{
    if (!root)
    {
        return NULL;
    }
    Node *head = NULL;
    Node *pre = NULL;
    treeToDoubleList(root, head, pre);
    head->left = pre;
    pre->right = head;
    return head;
}

//面试题37：序列化二叉树
class Codec
{
public:
    void serialize(TreeNode *root, string &res)
    {
        if (!root)
        {
            res += "$,";
            return;
        }
        res += to_string(root->val);
        res.push_back(',');
        serialize(root->left, res);
        serialize(root->right, res);
        return;
    }
    string serialize(TreeNode *root)
    {
        string res;
        serialize(root, res);
        return res;
    }

    void deserialize(string &data, TreeNode *&tree)
    {
        if (data.empty())
        {
            return;
        }
        else if (data[0] == '$')
        {
            tree = NULL;
            data = data.substr(2, data.size());
            return;
        }
        int count = 0;
        int i = 0;
        bool flag = false; //判断正负号
        if (data[0] == '-')
        {
            ++i;
            flag = true;
        }
        while (data[i] != ',')
        {
            count = count * 10 + (data[i] - '0');
            ++i;
        }
        if (flag)
        {
            count = -count;
        }
        tree = new TreeNode(count);
        data = data.substr(i + 1, data.size());
        deserialize(data, tree->left);
        deserialize(data, tree->right);
        return;
    }
    TreeNode *deserialize(string data)
    {
        TreeNode *tree = NULL;
        deserialize(data, tree);
        return tree;
    }
};

//面试题38-1：字符串的排列(剪枝：不能和自己交换&&不能和两相同交换)(LeetCode-46,LeetCode-47)
void permutation(string &s, vector<string> &res, int begin, int end)
{
    if (begin == end)
    {
        res.push_back(s);
        return;
    }
    for (int i = begin; i <= end; ++i)
    {
        bool flag = false;
        for (int j = begin; j < i; ++j)
        {
            if (s[j] == s[i])
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            continue;
        }
        swap(s[begin], s[i]);
        permutation(s, res, begin + 1, end);
        swap(s[begin], s[i]);
    }
    return;
}
vector<string> permutation(string s)
{
    vector<string> res;
    if (s.empty())
    {
        return res;
    }
    int length = s.size();
    permutation(s, res, 0, length - 1);
    return res;
}

//面试题38-2：字符串的组合(LeetCode-77)
void combine(vector<int> &nums, vector<vector<int>> &res, vector<int> &temp, int nbegin, int k)
{
    int nend = nums.size();
    if (!k)
    {
        res.push_back(temp);
        return;
    }
    else if (nend - nbegin == k)
    {
        for (int i = nbegin; i < nend; ++i)
        {
            temp.push_back(nums[i]);
        }
        res.push_back(temp);
        for (int i = nbegin; i < nend; ++i)
        {
            temp.pop_back();
        }
        return;
    }
    temp.push_back(nums[nbegin]);
    combine(nums, res, temp, nbegin + 1, k - 1);
    temp.pop_back();
    combine(nums, res, temp, nbegin + 1, k);
    return;
}
vector<vector<int>> combine(int n, int k)
{
    vector<vector<int>> res;
    vector<int> nums;
    vector<int> temp;
    if (k <= 0 || n <= 0 || k > n)
    {
        return res;
    }
    for (int i = 1; i <= n; ++i)
    {
        nums.push_back(i);
    }
    combine(nums, res, temp, 0, k);
    return res;
}

//面试题39：数组中出现次数超过一半的数字(投票算法)
int majorityElement(vector<int> &nums)
{
    if (nums.empty())
    {
        return -1;
    }
    int res = nums[0];
    int count = 1;
    int length = nums.size();
    for (int i = 1; i < length; ++i)
    {
        if (nums[i] == res)
        {
            ++count;
        }
        else
        {
            --count;
        }
        if (count < 0)
        {
            res = nums[i];
            count = 1;
        }
    }
    return res;
}

//面试题40：最小的k个数(priority_queue最大堆)
vector<int> getLeastNumbers(vector<int> &arr, int k)
{
    vector<int> res;
    if (!k)
    {
        return res;
    }
    priority_queue<int> store;
    int length = arr.size();
    for (int i = 0; i < length; ++i)
    {
        if (store.size() < k)
        {
            store.push(arr[i]);
        }
        else if (store.top() > arr[i])
        {
            store.pop();
            store.push(arr[i]);
        }
    }
    while (!store.empty())
    {
        res.push_back(store.top());
        store.pop();
    }
    return res;
}

//面试题41：数据流中的中位数(less最大堆,greater最小堆)
class MedianFinder
{
public:
    MedianFinder() {}
    void addNum(int num)
    {
        if (maxHeap.size() == minHeap.size())
        {
            maxHeap.push(num);
        }
        else
        {
            minHeap.push(num);
        }
        if (minHeap.size() && maxHeap.top() > minHeap.top())
        {
            int temp1 = maxHeap.top();
            int temp2 = minHeap.top();
            maxHeap.pop();
            minHeap.pop();
            maxHeap.push(temp2);
            minHeap.push(temp1);
        }
        return;
    }
    double findMedian()
    {
        if (maxHeap.empty())
        {
            return 0.0;
        }
        else if (maxHeap.size() > minHeap.size())
        {
            return (double)maxHeap.top();
        }
        return double(maxHeap.top() + minHeap.top()) * 0.5;
    }

private:
    priority_queue<int, vector<int>, less<int>> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
};

//面试题42：连续子数组的最大和
int maxSubArray(vector<int> &nums)
{
    int length = nums.size();
    if (!length)
    {
        return 0;
    }
    int res = nums[0];
    int *store = new int[length];
    store[0] = nums[0];
    for (int i = 1; i < length; ++i)
    {
        store[i] = max(nums[i], store[i - 1] + nums[i]);
        res = max(res, store[i]);
    }
    return res;
}

//面试题43：1~n整数中1出现的次数
int countDigitOne(int n)
{
    int high = n / 10;
    int cur = n % 10;
    int low = 0;
    int res = 0;
    int digits = 0;
    while (high || cur)
    {
        if (cur == 0)
        {
            res += high * pow(10, digits);
        }
        else if (cur == 1)
        {
            res += (high * pow(10, digits) + low + 1);
        }
        else
        {
            res += (high + 1) * pow(10, digits);
        }
        low += cur * pow(10, digits);
        cur = high % 10;
        high = high / 10;
        ++digits;
    }
    return res;
}

//面试题44：数字序列中某一位的数字
int findNthDigit(int n)
{
    if (n < 10)
    {
        return n;
    }
    int begin = 1;
    int digits = 1;
    int store = 9;
    while (n > store)
    {
        n -= store;
        begin *= 10;
        ++digits;
        store = digits * 9 * begin;
    }
    int nums = begin + (n - 1) / digits;
    int whichnum = (n - 1) % digits;
    while (++whichnum < digits)
    {
        nums /= 10;
    }
    return nums % 10;
}

//面试题45：把数组排成最小的数(sort比较函数需为static)
static int cmp(const int &a, const int &b)
{
    string s1 = to_string(a) + to_string(b);
    string s2 = to_string(b) + to_string(a);
    return s1 < s2;
}
string minNumber(vector<int> &nums)
{
    string res;
    int length = nums.size();
    if (!length)
    {
        return res;
    }
    sort(nums.begin(), nums.end(), cmp);
    for (int i = 0; i < length; ++i)
    {
        res += to_string(nums[i]);
    }
    return res;
}

//面试题46：把数字翻译成字符串
bool inRange(char a, char b)
{
    int temp = (a - '0') * 10 + (b - '0');
    return temp >= 10 && temp <= 25;
}
int translateNum(int num)
{
    if (num < 10)
    {
        return 1;
    }
    string s = to_string(num);
    int length = s.size();
    int *store = new int[length];
    memset(store, 0, sizeof(int) * length);
    store[0] = 1;
    store[1] = inRange(s[0], s[1]) ? 2 : 1;
    for (int i = 2; i < length; ++i)
    {
        store[i] += store[i - 1];
        if (inRange(s[i - 1], s[i]))
        {
            store[i] += store[i - 2];
        }
    }
    return store[length - 1];
}

//面试题47：礼物的最大价值(存一行就可以)
int maxValue(vector<vector<int>> &grid)
{
    int length1 = grid.size();
    int length2 = grid[0].size();
    vector<int> row(length2, 0);
    row[0] = grid[0][0];
    for (int i = 1; i < length2; ++i)
    {
        row[i] = grid[0][i] + row[i - 1];
    }
    for (int i = 1; i < length1; ++i)
    {
        row[0] += grid[i][0];
        for (int j = 1; j < length2; ++j)
        {
            row[j] = max(row[j], row[j - 1]) + grid[i][j];
        }
    }
    return row[length2 - 1];
}

//面试题48：最长不含重复字符的子字符串(有特殊字符用Hash表)
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

//面试题49：丑数
int nthUglyNumber(int n)
{
    vector<int> res(n, 0);
    res[0] = 1;
    int index2 = 0, index3 = 0, index5 = 0;
    int M2 = 0, M3 = 0, M5 = 0;
    for (int i = 1; i < n; ++i)
    {
        M2 = res[index2] * 2;
        M3 = res[index3] * 3;
        M5 = res[index5] * 5;
        res[i] = min(min(M2, M3), M5);
        if (res[i] == M2)
        {
            ++index2;
        }
        if (res[i] == M3)
        {
            ++index3;
        }
        if (res[i] == M5)
        {
            ++index5;
        }
    }
    return res[n - 1];
}

//面试题50：第一个只出现一次的字符
// char firstUniqChar(string s)
// {
//     int length = s.size();
//     char res = ' ';
//     if (!length)
//     {
//         return res;
//     }
//     vector<int> store(26, 0);
//     for (int i = 0; i < length; ++i)
//     {
//         ++store[s[i] - 'a'];
//     }
//     for (int i = 0; i < length; ++i)
//     {
//         if (store[s[i] - 'a'] == 1)
//         {
//             return s[i];
//         }
//     }
//     return res;
// }
char firstUniqChar(string s)
{
    int length = s.size();
    char res = ' ';
    if (!length)
    {
        return res;
    }
    vector<int> store(26, -1);
    for (int i = 0; i < length; ++i)
    {
        if (store[s[i] - 'a'] == -1)
        {
            store[s[i] - 'a'] = i;
        }
        else if (store[s[i] - 'a'] >= 0)
        {
            store[s[i] - 'a'] = -2;
        }
    }
    for (int i = 0; i < 26; ++i)
    {
        if (store[i] >= 0 && (res == ' ' || store[i] < store[res - 'a']))
        {
            res = i + 'a';
        }
    }
    return res;
}

//面试题51：数组中的逆序对
void mergeSort(vector<int> &nums, vector<int> &store, int &res, int begin, int end)
{
    if (begin >= end)
    {
        return;
    }
    int middle = (begin + end) >> 1;
    mergeSort(nums, store, res, begin, middle);
    mergeSort(nums, store, res, middle + 1, end);
    int i = middle;
    int j = end;
    int storek = end;
    while (i >= begin || j >= middle + 1)
    {
        while (i >= begin && j >= middle + 1)
        {
            if (nums[i] <= nums[j])
            {
                store[storek--] = nums[j--];
            }
            else
            {
                store[storek--] = nums[i--];
                res += (j - middle);
            }
        }
        while (i >= begin)
        {
            store[storek--] = nums[i--];
        }
        while (j >= middle + 1)
        {
            store[storek--] = nums[j--];
        }
    }
    for (int i = begin; i <= end; ++i)
    {
        nums[i] = store[i];
    }
    return;
}
int reversePairs(vector<int> &nums)
{
    int length = nums.size();
    if (length <= 1)
    {
        return 0;
    }
    int res = 0;
    vector<int> store(length, 0);
    mergeSort(nums, store, res, 0, length - 1);
    return res;
}

//面试题52：两个链表的第一个公共节点
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    int count = 0;
    ListNode *temp1 = headA;
    ListNode *temp2 = headB;
    while (temp1 && temp2)
    {
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    if (temp1)
    {
        while (temp1)
        {
            temp1 = temp1->next;
            ++count;
        }
        temp1 = headA;
        while (count--)
        {
            temp1 = temp1->next;
        }
        temp2 = headB;
    }
    else if (temp2)
    {
        while (temp2)
        {
            temp2 = temp2->next;
            ++count;
        }
        temp2 = headB;
        while (count--)
        {
            temp2 = temp2->next;
        }
        temp1 = headA;
    }
    else
    {
        temp1 = headA;
        temp2 = headB;
    }
    while (temp1)
    {
        if (temp1 == temp2)
        {
            return temp1;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return NULL;
}

//面试题53-1：在排序数组中查找数字I
int search(vector<int> &nums, int target)
{
    int length = nums.size();
    if (!length)
    {
        return 0;
    }
    int left = 0, right = length - 1;
    while (left <= right)
    {
        int middle = (left + right) >> 1;
        if (nums[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }
    int res1 = left;
    left = 0, right = length - 1;
    while (left <= right)
    {
        int middle = (left + right) >> 1;
        if (nums[middle] > target)
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }
    int res2 = left;
    return res2 - res1;
}

//面试题53-2：0~n-1中缺失的数字
int missingNumber(vector<int> &nums)
{
    int length = nums.size();
    int left = 0;
    int right = length - 1;
    while (left <= right)
    {
        int middle = (left + right) >> 1;
        if (nums[middle] == middle)
        {
            left = middle + 1;
        }
        else if (nums[middle] > middle)
        {
            right = middle - 1;
        }
    }
    return left;
}

//面试题54：二叉搜索树的第k大节点
void recursion(TreeNode *root, int &k, int &res)
{
    if (!root || k <= 0)
    {
        return;
    }
    recursion(root->right, k, res);
    --k;
    if (!k)
    {
        res = root->val;
        return;
    }
    recursion(root->left, k, res);
}
int kthLargest(TreeNode *root, int k)
{
    int res = 0;
    recursion(root, k, res);
    return res;
}

//面试题55-1：二叉树的深度
int maxDepth(TreeNode *root)
{
    if (!root)
    {
        return 0;
    }
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

//面试题55-2：平衡二叉树
int recursion(TreeNode *root, bool &flag)
{
    if (!root || !flag)
    {
        return 0;
    }
    int left = recursion(root->left, flag);
    int right = recursion(root->right, flag);
    if (abs(left - right) > 1)
    {
        flag = false;
        return 0;
    }
    return 1 + max(left, right);
}
bool isBalanced(TreeNode *root)
{
    bool flag = true;
    int temp = recursion(root, flag);
    return flag;
}

//面试题56-1：数组中数字出现的次数
vector<int> singleNumbers(vector<int> &nums)
{
    int temp1 = 0;
    int length = nums.size();
    for (int i = 0; i < length; ++i)
    {
        temp1 ^= nums[i];
    }
    int cmp = 1;
    while (!(cmp & temp1))
    {
        cmp = cmp << 1;
    }
    temp1 = 0;
    int temp2 = 0;
    for (int i = 0; i < length; ++i)
    {
        if (cmp & nums[i])
        {
            temp1 ^= nums[i];
        }
        else
        {
            temp2 ^= nums[i];
        }
    }
    vector<int> res{temp1, temp2};
    return res;
}

//面试题56-2：数组中数字出现的次数
int singleNumber(vector<int> &nums)
{
    vector<int> store(32, 0);
    int count = nums.size();
    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < 32; ++j)
        {
            int temp = 1 << j;
            if (temp & nums[i])
            {
                ++store[j];
            }
        }
    }
    int res = 0;
    for (int j = 0; j < 32; ++j)
    {
        if (store[j] % 3)
        {
            res += (1 << j);
        }
    }
    return res;
}

//面试题57-1：和为s的两个数字
vector<int> twoSum(vector<int> &nums, int target)
{
    vector<int> res;
    int length = nums.size();
    if (length <= 1)
    {
        return res;
    }
    int left = 0;
    int right = length - 1;
    while (left < right)
    {
        if (nums[left] + nums[right] < target)
        {
            ++left;
        }
        else if (nums[left] + nums[right] > target)
        {
            --right;
        }
        else
        {
            res.push_back(nums[left]);
            res.push_back(nums[right]);
            return res;
        }
    }
    return res;
}

//面试题57-2：和为s的连续正数数列
vector<vector<int>> findContinuousSequence(int target)
{
    vector<vector<int>> res;
    int left = 1;
    int right = 2;
    int cmp = 3;
    while (left < right && right < target)
    {
        if (cmp < target)
        {
            ++right;
            cmp += right;
        }
        else if (cmp > target)
        {
            ++left;
            cmp -= (left - 1);
        }
        else
        {
            vector<int> temp;
            for (int i = left; i <= right; ++i)
            {
                temp.push_back(i);
            }
            res.push_back(temp);
            ++left;
            ++right;
            cmp = cmp + right - left + 1;
        }
    }
    return res;
}

//面试题58-1：翻转单词顺序
// void swapWords(string &s, int begin, int end)
// {
//     int middle = (begin + end - 1) >> 1;
//     for (int i = begin; i <= middle; ++i)
//     {
//         swap(s[i], s[begin + end - i]);
//     }
//     return;
// }
void eraseSpace(string &s, int begin, int end)
{
    s.erase(s.begin() + begin, s.begin() + end);
    return;
}
string reverseWords(string s)
{
    int length = s.size();
    reverse(s.begin(), s.end());
    int left = 0;
    int right = 0;
    while (right < length && s[right] != '\0')
    {
        while (s[right] == ' ')
        {
            ++right;
        }
        if (right - left)
        {
            if (left == 0 || s[right] == '\0')
            {
                eraseSpace(s, left, right);
            }
            else
            {
                eraseSpace(s, left, right - 1);
                ++left;
            }
            right = left;
        }
        while (s[right] != ' ' && s[right] != '\0')
        {
            ++right;
        }
        reverse(s.begin() + left, s.begin() + right);
        left = right;
    }
    return s;
}

//面试题58-2：左旋转字符串
string reverseLeftWords(string s, int n)
{
    int length = s.size();
    if (length <= 1 || n % length == 0)
    {
        return s;
    }
    reverse(s.begin(), s.end());
    n %= length;
    n = length - n;
    reverse(s.begin(), s.begin() + n);
    reverse(s.begin() + n, s.end());
    return s;
}

//面试题59-1：滑动窗口的最大值
vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
    int length = nums.size();
    vector<int> res;
    if (!length || k > length || !k)
    {
        return res;
    }
    deque<int> index;
    for (int i = 0; i < length; ++i)
    {
        if (i - index.front() == k)
        {
            index.pop_front();
        }
        while (!index.empty() && nums[index.back()] <= nums[i])
        {
            index.pop_back();
        }
        index.push_back(i);
        if (i >= k - 1)
        {
            res.push_back(nums[index.front()]);
        }
    }
    return res;
}

//面试题59-2：队列的最大值
class MaxQueue
{
public:
    MaxQueue() {}
    int max_value()
    {
        if (data.empty())
        {
            return -1;
        }
        return max.front();
    }
    void push_back(int value)
    {
        data.push(value);
        while (!max.empty() && max.back() < value)
        {
            max.pop_back();
        }
        max.push_back(value);
        return;
    }
    int pop_front()
    {
        if (data.empty())
        {
            return -1;
        }
        int temp = data.front();
        data.pop();
        if (max.front() == temp)
        {
            max.pop_front();
        }
        return temp;
    }

private:
    queue<int> data;
    deque<int> max;
};

//面试题60：n个骰子的点数
//https://leetcode-cn.com/problems/nge-tou-zi-de-dian-shu-lcof/solution/nge-tou-zi-de-dian-shu-dong-tai-gui-hua-ji-qi-yo-3/
vector<double> dicesProbability(int n)
{
    int diceFaces = 6;
    int denominator = pow(diceFaces, n);
    vector<double> store(diceFaces * n + 1, 0);
    for (int i = 1; i <= diceFaces; ++i)
    {
        store[i] = 1;
    }
    for (int i = 2; i <= n; ++i)
    {
        for (int j = diceFaces * i; j >= i; --j)
        {
            store[j] = 0;
            for (int k = 1; k <= diceFaces; ++k)
            {
                if (j - k <= 0)
                {
                    break;
                }
                store[j] += store[j - k];
            }
        }
        for (int j = 0; j < i; ++j)
        {
            store[j] = 0;
        }
    }
    vector<double> res;
    for (int i = n; i <= diceFaces * n; ++i)
    {
        res.push_back((double)store[i] / (double)denominator);
    }
    return res;
}

//面试题61：扑克牌中的顺子
bool isStraight(vector<int> &nums)
{
    int length = nums.size();
    if (length != 5)
    {
        return false;
    }
    sort(nums.begin(), nums.end());
    int countZero = 0;
    for (int i = 0; i < 5; ++i)
    {
        if (i && nums[i] && nums[i] == nums[i - 1])
        {
            return false;
        }
        if (!nums[i])
        {
            ++countZero;
        }
    }
    return (nums[4] - nums[countZero]) < (5 + countZero);
}

//面试题62：圆圈中最后剩下的数字
//https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/solution/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-by-lee/
int lastRemaining(int n, int m)
{
    vector<int> store(n, 0);
    for (int i = 1; i < n; ++i)
    {
        store[i] = (m % (i + 1) + store[i - 1]) % (i + 1);
    }
    return store[n - 1];
}

//面试题63：股票的最大利润
int maxProfit(vector<int> &prices)
{
    int length = prices.size();
    if (length < 2)
    {
        return 0;
    }
    int res = 0;
    int beforeMin = prices[0];
    for (int i = 1; i < length; ++i)
    {
        res = max(res, prices[i] - beforeMin);
        beforeMin = min(beforeMin, prices[i]);
    }
    return res;
}

//面试题64：求1+2+...+n(短路效应,sizeof)
// int sumNums(int n)
// {
//     n && (n += sumNums(n - 1));
//     return n;
// }
int sumNums(int n)
{
    bool temp[n][n + 1];
    return sizeof(temp) >> 1;
}

//面试题65：不用加减乘除做加法
int add(int a, int b)
{
    int sum1 = a ^ b;
    int sum2 = (unsigned int)(a & b) << 1;
    while (sum2)
    {
        int temp = sum1;
        sum1 ^= sum2;
        sum2 = (unsigned int)(temp & sum2) << 1;
    }
    return sum1;
}

//面试题66：构建乘积数组
vector<int> constructArr(vector<int> &a)
{
    vector<int> b;
    int length = a.size();
    if (!length)
    {
        return b;
    }
    b.resize(length, 1);
    vector<int> store(length, 1);
    for (int i = 1; i < length; ++i)
    {
        store[i] = store[i - 1] * a[i - 1];
        b[i] = store[i];
    }
    store[length - 1] = 1;
    for (int i = length - 2; i >= 0; --i)
    {
        store[i] = store[i + 1] * a[i + 1];
        b[i] *= store[i];
    }
    return b;
}

//面试题67：把字符串转换成整数
int strToInt(string str)
{
    int length = str.size();
    bool positive = true;
    long res = 0;
    for (int i = 0; i < length; ++i)
    {
        if (str[i] == ' ')
        {
        }
        else if (str[i] == '+' || str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
        {
            if (str[i] == '+')
            {
                ++i;
            }
            else if (str[i] == '-')
            {
                ++i;
                positive = false;
            }
            while (str[i] >= '0' && str[i] <= '9')
            {
                res = res * 10 + (str[i] - '0');
                if (res > INT_MAX)
                {
                    return positive ? INT_MAX : INT_MIN;
                }
                ++i;
            }
            return positive ? res : -res;
        }
        else
        {
            return res;
        }
    }
    return res;
}

//面试题68-1：二叉搜索树的最近公共祖先
// TreeNode *lowestCommonAncestor1(TreeNode *root, TreeNode *p, TreeNode *q)
// {
//     if (p->val > q->val)
//     {
//         return lowestCommonAncestor1(root, q, p);
//     }
//     if (p == root || q == root || (p->val < root->val && q->val > root->val))
//     {
//         return root;
//     }
//     else if (q->val < root->val)
//     {
//         return lowestCommonAncestor1(root->left, p, q);
//     }
//     else
//     {
//         return lowestCommonAncestor1(root->right, p, q);
//     }
//     return NULL;
// }
TreeNode *lowestCommonAncestor1(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (p->val > q->val)
    {
        return lowestCommonAncestor1(root, q, p);
    }
    while (root)
    {
        if (q->val < root->val)
        {
            root = root->left;
        }
        else if (p->val > root->val)
        {
            root = root->right;
        }
        else
        {
            return root;
        }
    }
    return NULL;
}

//面试题68-2：二叉树的最近公共祖先(未排序)
bool findNode(TreeNode *root, TreeNode *target, vector<TreeNode *> &path)
{
    if (!root)
    {
        return false;
    }
    else if (root->val == target->val)
    {
        path.push_back(root);
        return true;
    }
    path.push_back(root);
    bool inpath1 = findNode(root->left, target, path);
    bool inpath2 = findNode(root->right, target, path);
    if (!inpath1 && !inpath2)
    {
        path.pop_back();
    }
    return inpath1 || inpath2;
}
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    vector<TreeNode *> path1;
    vector<TreeNode *> path2;
    bool inpath1 = findNode(root, p, path1);
    bool inpath2 = findNode(root, q, path2);
    int length = min(path1.size(), path2.size());
    if (!inpath1 || !inpath2 || !length || path1[0]->val != path2[0]->val)
    {
        return NULL;
    }
    for (int i = 1; i < length; ++i)
    {
        if (path1[i]->val != path2[i]->val)
        {
            return path1[i - 1];
        }
    }
    return path1[length - 1];
}

int main()
{
    TreeNode *tree34 = new TreeNode(5);
    tree34->left = new TreeNode(4);
    tree34->right = new TreeNode(8);
    tree34->left->left = new TreeNode(11);
    tree34->right->left = new TreeNode(13);
    tree34->right->right = new TreeNode(4);
    tree34->left->left->left = new TreeNode(7);
    tree34->left->left->right = new TreeNode(2);
    tree34->right->right->left = new TreeNode(5);
    tree34->right->right->right = new TreeNode(1);
    vector<vector<int>> res34 = pathSum(tree34, 22);

    Node1 *list35 = new Node1(7);
    list35->next = new Node1(13);
    list35->next->next = new Node1(11);
    list35->next->next->next = new Node1(10);
    list35->next->next->next->next = new Node1(1);
    list35->next->random = list35;
    list35->next->next->random = list35->next->next->next->next;
    list35->next->next->next->random = list35->next->next;
    list35->next->next->next->next->random = list35;
    Node1 *res35 = copyRandomList(list35);

    Node *list36 = new Node(4);
    list36->left = new Node(2);
    list36->right = new Node(5);
    list36->left->left = new Node(1);
    list36->left->right = new Node(3);
    Node *res36 = treeToDoublyList(list36);

    Codec codec37;
    TreeNode *tree37 = new TreeNode(-1);
    tree37->left = new TreeNode(2);
    tree37->right = new TreeNode(3);
    tree37->right->left = new TreeNode(4);
    tree37->right->right = new TreeNode(5);
    string s37 = codec37.serialize(tree37);
    TreeNode *res37 = codec37.deserialize(s37);

    string s38_1 = "abc";
    vector<string> res38_1 = permutation(s38_1);

    vector<vector<int>> res38_2 = combine(5, 1);

    vector<int> nums39 = {1, 2, 3, 2, 2, 2, 5, 4, 2};
    int res39 = majorityElement(nums39);

    vector<int> nums40 = {3, 2, 1};
    vector<int> res40 = getLeastNumbers(nums40, 2);

    MedianFinder *obj41 = new MedianFinder();
    obj41->addNum(1);
    double param41 = obj41->findMedian();

    vector<int> nums42 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int res42 = maxSubArray(nums42);

    int res43 = countDigitOne(12);

    int res44 = findNthDigit(1000);

    vector<int> nums45 = {10, 2, 11};
    string res45 = minNumber(nums45);

    int res46 = translateNum(624);

    vector<vector<int>> matrix47 = {{1, 2, 5}, {3, 2, 1}};
    int res47 = maxValue(matrix47);

    string s48 = "abcabcbb";
    int res48 = lengthOfLongestSubstring(s48);

    int res49 = nthUglyNumber(10);

    string s50 = "leetcode";
    char res50 = firstUniqChar(s50);

    vector<int> nums51 = {7, 5, 6, 4};
    int res51 = reversePairs(nums51);

    ListNode *list52_1 = new ListNode(4);
    list52_1->next = new ListNode(1);
    list52_1->next->next = new ListNode(8);
    list52_1->next->next->next = new ListNode(4);
    list52_1->next->next->next->next = new ListNode(5);
    ListNode *list52_2 = new ListNode(5);
    list52_2->next = new ListNode(0);
    list52_2->next->next = new ListNode(1);
    list52_2->next->next->next = list52_1->next->next;
    ListNode *res52 = getIntersectionNode(list52_1, list52_2);

    vector<int> nums53_1 = {5, 7, 7, 8, 8, 10};
    int res53_1 = search(nums53_1, 8);

    vector<int> nums53_2 = {0, 1, 3};
    int res53_2 = missingNumber(nums53_2);

    TreeNode *tree54 = new TreeNode(3);
    tree54->left = new TreeNode(1);
    tree54->right = new TreeNode(4);
    tree54->left->right = new TreeNode(2);
    int res54 = kthLargest(tree54, 1);

    TreeNode *tree55_1 = new TreeNode(3);
    tree55_1->left = new TreeNode(9);
    tree55_1->right = new TreeNode(20);
    tree55_1->right->left = new TreeNode(15);
    tree55_1->right->right = new TreeNode(7);
    int res55_1 = maxDepth(tree55_1);

    TreeNode *tree55_2 = new TreeNode(3);
    tree55_2->left = new TreeNode(9);
    tree55_2->right = new TreeNode(20);
    tree55_2->right->left = new TreeNode(15);
    tree55_2->right->right = new TreeNode(7);
    bool res55_2 = isBalanced(tree55_2);

    vector<int> nums56_1 = {4, 1, 4, 6};
    vector<int> res56_1 = singleNumbers(nums56_1);

    vector<int> nums56_2 = {3, 4, 3, 3};
    int res56_2 = singleNumber(nums56_2);

    vector<int> nums57_1 = {2, 7, 11, 15};
    vector<int> res57_1 = twoSum(nums57_1, 9);

    vector<vector<int>> res57_2 = findContinuousSequence(9);

    string s58_1 = "  hello world!  ";
    string res58_1 = reverseWords(s58_1);

    string s58_2 = "abcdefg";
    string res58_2 = reverseLeftWords(s58_2, 2);

    vector<int> nums59_1 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> res59_1 = maxSlidingWindow(nums59_1, 3);

    MaxQueue *obj59_2 = new MaxQueue();
    int param59_2 = obj59_2->max_value();
    obj59_2->push_back(1);
    param59_2 = obj59_2->pop_front();

    vector<double> res60 = dicesProbability(3);

    vector<int> nums61 = {0, 0, 1, 2, 5};
    bool res61 = isStraight(nums61);

    int res62 = lastRemaining(5, 3);

    vector<int> nums63 = {7, 1, 5, 3, 6, 4};
    int res63 = maxProfit(nums63);

    int res64 = sumNums(3);

    int res65 = add(-1, 2);

    vector<int> nums66 = {1, 2, 3, 4, 5};
    vector<int> res66 = constructArr(nums66);

    string s67 = "42";
    int res67 = strToInt(s67);

    TreeNode *tree68_1 = new TreeNode(6);
    tree68_1->left = new TreeNode(2);
    tree68_1->right = new TreeNode(8);
    tree68_1->left->left = new TreeNode(0);
    tree68_1->left->right = new TreeNode(4);
    tree68_1->right->left = new TreeNode(7);
    tree68_1->right->right = new TreeNode(9);
    tree68_1->left->right->left = new TreeNode(3);
    tree68_1->left->right->right = new TreeNode(5);
    TreeNode *res68_1 = lowestCommonAncestor1(tree68_1, tree68_1->left, tree68_1->right);

    TreeNode *tree68_2 = new TreeNode(3);
    tree68_2->left = new TreeNode(5);
    tree68_2->right = new TreeNode(1);
    tree68_2->left->left = new TreeNode(6);
    tree68_2->left->right = new TreeNode(2);
    tree68_2->right->left = new TreeNode(0);
    tree68_2->right->right = new TreeNode(8);
    tree68_2->left->right->left = new TreeNode(7);
    tree68_2->left->right->right = new TreeNode(4);
    TreeNode *res68_2 = lowestCommonAncestor(tree68_2, tree68_2->left, tree68_2->left->right->right);

    return 0;
}