//剑指Offer

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string.h>

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

//面试题3：数组中重复的数字
int findRepeatNumber(vector<int> &nums)
{
    int length = nums.size();
    if (length <= 1)
    {
        return -1;
    }
    for (int i = 0; i < length;)
    {
        if (i == nums[i])
        {
            ++i;
            continue;
        }
        if (nums[nums[i]] == nums[i])
        {
            return nums[i];
        }
        else
        {
            swap(nums[nums[i]], nums[i]);
        }
    }
    return -1;
}
// int countNums(vector<int> &nums, int length, int begin, int end)
// {
//     int res = 0;
//     for (int i = 0; i < length; ++i)
//     {
//         if (nums[i] >= begin && nums[i] <= end)
//         {
//             ++res;
//         }
//     }
//     return res;
// }
// int findRepeatNumber(vector<int> &nums)
// {
//     int length = nums.size();
//     if (length <= 1)
//     {
//         return -1;
//     }
//     int left = 0;
//     int right = length - 1;
//     while (left < right)
//     {
//         int middle = (left + right) >> 1;
//         int count = countNums(nums, length, left, middle);
//         if (count > middle - left + 1)
//         {
//             right = middle;
//         }
//         else
//         {
//             left = middle + 1;
//         }
//     }
//     return left;
// }

//面试题4：二维数组中的查找
bool findNumberIn2DArray(vector<vector<int>> &matrix, int target)
{
    if (!matrix.size() || !matrix[0].size())
    {
        return false;
    }
    int row = matrix.size();
    int col = matrix[0].size();
    int begin1 = 0;
    int begin2 = col - 1;
    while (begin1 < row && begin2 >= 0)
    {
        if (matrix[begin1][begin2] > target)
        {
            int left = 0, right = begin2 - 1;
            while (left < right)
            {
                int middle = (left + right) >> 1;
                if (matrix[begin1][middle] < target)
                {
                    left = middle + 1;
                }
                else if (matrix[begin1][middle] > target)
                {
                    right = middle - 1;
                }
                else
                {
                    return true;
                }
            }
            begin2 = min(left, begin2 - 1);
        }
        else if (matrix[begin1][begin2] < target)
        {
            int left = begin1, right = row - 1;
            while (left < right)
            {
                int middle = (left + right) >> 1;
                if (matrix[middle][begin2] < target)
                {
                    left = middle + 1;
                }
                else if (matrix[middle][begin2] > target)
                {
                    right = middle - 1;
                }
                else
                {
                    return true;
                }
            }
            begin1 = max(left, begin1 + 1);
        }
        else
        {
            return true;
        }
    }
    return false;
}

//面试题5：替换空格
// string replaceSpace(string s)
// {
//     int length = s.size();
//     int space = 0;
//     for (int i = 0; i < length; ++i)
//     {
//         if (s[i] == ' ')
//         {
//             ++space;
//         }
//     }
//     int newSize = length + space * 2;
//     s.resize(newSize);
//     while (length >= 0)
//     {
//         if (newSize == length)
//         {
//             return s;
//         }
//         if (s[length] != ' ')
//         {
//             s[newSize--] = s[length--];
//         }
//         else
//         {
//             --length;
//             s[newSize--] = '0';
//             s[newSize--] = '2';
//             s[newSize--] = '%';
//         }
//     }
//     return s;
// }
string replaceSpace(string s)
{
    int length = s.size();
    for (int i = 0; s[i] != '\0';)
    {
        if (s[i] != ' ')
        {
            ++i;
        }
        else
        {
            s.insert(i, "%20");
            i += 3;
            s.erase(i, 1);
        }
    }
    return s;
}

//面试题6：从尾到头打印链表
vector<int> reversePrint(ListNode *head)
{
    stack<int> store;
    vector<int> res;
    while (head)
    {
        store.push(head->val);
        head = head->next;
    }
    while (!store.empty())
    {
        res.push_back(store.top());
        store.pop();
    }
    return res;
}

//面试题7：重建二叉树(先序确定起点,中序确定边界)
TreeNode *dfs(vector<int> &preorder, int root, int left, int right, unordered_map<int, int> &store)
{
    if (left > right)
    {
        return NULL;
    }
    TreeNode *res = new TreeNode(preorder[root]);
    int temp = store[preorder[root]]; //inorder
    res->left = dfs(preorder, root + 1, left, temp - 1, store);
    res->right = dfs(preorder, root + temp - left + 1, temp + 1, right, store);
    return res;
}
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    TreeNode *res = NULL;
    int length1 = preorder.size(), length2 = inorder.size();
    if (length1 <= 0 || length1 != length2)
    {
        return res;
    }
    unordered_map<int, int> store;
    for (int i = 0; i < length2; ++i)
    {
        store[inorder[i]] = i;
    }
    res = dfs(preorder, 0, 0, length1 - 1, store);
    return res;
}

//面试题8：二叉树的下一个节点
struct TreeLinkNode
{
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};
TreeLinkNode *GetNext(TreeLinkNode *pNode)
{
    if (!pNode)
    {
        return NULL;
    }
    else if (pNode->right)
    {
        TreeLinkNode *res = pNode->right;
        while (res->left)
        {
            res = res->left;
        }
        return res;
    }
    TreeLinkNode *res = pNode;
    while (res && res->next)
    {
        if (res->next->left == res)
        {
            return res->next;
        }
        res = res->next;
    }
    return NULL;
}

//面试题9：用两个栈inc实现队列
class CQueue
{
public:
    CQueue() {}

    void appendTail(int value)
    {
        s1.push(value);
    }

    int deleteHead()
    {
        if (s2.empty())
        {
            if (s1.empty())
            {
                return -1;
            }
            while (!s1.empty())
            {
                int temp = s1.top();
                s1.pop();
                s2.push(temp);
            }
        }
        int res = s2.top();
        s2.pop();
        return res;
    }

private:
    stack<int> s1;
    stack<int> s2;
};

//面试题10-1：斐波那契数列
int fib(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    int fib1 = 1, fib2 = 0, res = 0;
    while (--n)
    {
        res = fib1 + fib2;
        while (res >= (1e9 + 7))
        {
            res -= (1e9 + 7);
        }
        fib2 = fib1;
        fib1 = res;
    }
    return res;
}

//面试题10-2：青蛙跳台阶问题
int numWays(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else if (n == 1)
    {
        return 1;
    }
    int fib1 = 1, fib2 = 1, res = 0;
    while (--n)
    {
        res = fib1 + fib2;
        while (res >= (1e9 + 7))
        {
            res -= (1e9 + 7);
        }
        fib2 = fib1;
        fib1 = res;
    }
    return res;
}

//面试题11-1：旋转数组的最小数字(只能和right比)
int minArray(vector<int> &numbers)
{
    int length = numbers.size();
    int left = 0, right = length - 1;
    while (left < right)
    {
        if (numbers[left] < numbers[right])
        {
            return numbers[left];
        }
        int middle = (left + right) >> 1;
        if (numbers[middle] > numbers[right])
        {
            left = middle + 1;
        }
        else if (numbers[middle] < numbers[right])
        {
            right = middle;
        }
        else
        {
            --right;
        }
    }
    return numbers[left];
}

//面试题11-2：搜索旋转排序数组(LeetCode-33,LeetCode-81)
bool search(vector<int> &nums, int target)
{
    int length = nums.size();
    if (!length)
    {
        return false;
    }
    int left = 0;
    int right = length - 1;
    while (left < right)
    {
        int middle = (left + right) >> 1;
        if (nums[middle] < nums[right])
        {
            if (nums[middle] == target || nums[right] == target)
            {
                return true;
            }
            else if (nums[middle] < target && target < nums[right])
            {
                left = middle + 1;
            }
            else
            {
                right = middle - 1;
            }
        }
        else if (nums[middle] > nums[right])
        {
            if (nums[left] == target || nums[middle] == target)
            {
                return true;
            }
            else if (nums[left] < target && target < nums[middle])
            {
                right = middle - 1;
            }
            else
            {
                left = middle + 1;
            }
        }
        else
        {
            --right;
        }
    }
    return nums[left] == target;
}

//面试题12：矩阵中的路径
bool findLetter(vector<vector<char>> &board, vector<vector<bool>> &mask, string word, int &index, int icount, int jcount)
{
    if (word[index] == '\0')
    {
        return true;
    }
    if (board[icount][jcount] != word[index])
    {
        return false;
    }
    mask[icount][jcount] = true;
    ++index;
    if (index == word.size())
    {
        return true;
    }
    if (icount > 0 && !mask[icount - 1][jcount] && findLetter(board, mask, word, index, icount - 1, jcount))
    {
        return true;
    }
    else if (icount < board.size() - 1 && !mask[icount + 1][jcount] && findLetter(board, mask, word, index, icount + 1, jcount))
    {
        return true;
    }
    else if (jcount > 0 && !mask[icount][jcount - 1] && findLetter(board, mask, word, index, icount, jcount - 1))
    {
        return true;
    }
    else if (jcount < board[0].size() - 1 && !mask[icount][jcount + 1] && findLetter(board, mask, word, index, icount, jcount + 1))
    {
        return true;
    }
    mask[icount][jcount] = false;
    --index;
    return false;
}
bool exist(vector<vector<char>> &board, string word)
{
    int length1 = board.size();
    int length2 = board[0].size();
    int index = 0;
    vector<vector<bool>> mask(length1, vector<bool>(length2, false));
    for (int i = 0; i < length1; ++i)
    {
        for (int j = 0; j < length2; ++j)
        {
            if (findLetter(board, mask, word, index, i, j))
            {
                return true;
            }
        }
    }
    return false;
}

//面试题13：机器人的运动范围
bool whetherIn(int indexi, int indexj, int k)
{
    int temp = 0;
    while (indexi / 10)
    {
        temp += (indexi % 10);
        indexi /= 10;
    }
    temp += indexi;
    while (indexj / 10)
    {
        temp += (indexj % 10);
        indexj /= 10;
    }
    temp += indexj;
    return temp <= k;
}
void subCount(int m, int n, int k, vector<vector<bool>> &mask, int &res, int indexi, int indexj)
{
    if (whetherIn(indexi, indexj, k))
    {
        ++res;
        mask[indexi][indexj] = true;
        if (indexi > 0 && !mask[indexi - 1][indexj])
        {
            subCount(m, n, k, mask, res, indexi - 1, indexj);
        }
        if (indexi < m - 1 && !mask[indexi + 1][indexj])
        {
            subCount(m, n, k, mask, res, indexi + 1, indexj);
        }
        if (indexj > 0 && !mask[indexi][indexj - 1])
        {
            subCount(m, n, k, mask, res, indexi, indexj - 1);
        }
        if (indexj < n - 1 && !mask[indexi][indexj + 1])
        {
            subCount(m, n, k, mask, res, indexi, indexj + 1);
        }
    }
    return;
}
int movingCount(int m, int n, int k)
{
    vector<vector<bool>> mask(m, vector<bool>(n, false));
    int res = 0;
    subCount(m, n, k, mask, res, 0, 0);
    return res;
}

//面试题14：剪绳子(是否大于1e9+7 && 两种方法)
// int cuttingRope(int n)
// {
//     if (n < 2)
//     {
//         return 0;
//     }
//     else if (n == 2)
//     {
//         return 1;
//     }
//     else if (n == 3)
//     {
//         return 2;
//     }
//     int *store = new int[n + 1];
//     store[0] = 0;
//     store[1] = 1;
//     store[2] = 2;
//     store[3] = 3;
//     for (int i = 4; i <= n; ++i)
//     {
//         int temp = 0;
//         for (int j = 1; j <= i / 2; ++j)
//         {
//             temp = max(temp, store[j] * store[i - j]);
//         }
//         store[i] = temp;
//     }
//     int res = store[n];
//     delete[] store;
//     return res;
// }
int cuttingRope(int n)
{
    if (n < 2)
    {
        return 0;
    }
    else if (n == 2)
    {
        return 1;
    }
    else if (n == 3)
    {
        return 2;
    }
    unsigned int res = 1;
    while (n > 4)
    {
        n -= 3;
        res *= 3;
        while (res > (1e9 + 7))
        {
            res -= (1e9 + 7);
        }
    }
    if (n)
    {
        res *= n;
        while (res > (1e9 + 7))
        {
            res -= (1e9 + 7);
        }
    }
    return res;
}

//面试题15：二进制中1的个数
// int hammingWeight(uint32_t n)
// {
//     int res = 0;
//     uint32_t comp = 1;
//     while (comp)
//     {
//         if (comp & n)
//         {
//             ++res;
//         }
//         comp = comp << 1;
//     }
//     return res;
// }
int hammingWeight(uint32_t n)
{
    int res = 0;
    while (n)
    {
        n = n & (n - 1);
        ++res;
    }
    return res;
}

//面试题16：数值的整数次方(二分法先平方可，后平方不可)
bool doubleEqual(double x, double y)
{
    if ((x - y) < 0.0000001 && (x - y) > -0.0000001)
    {
        return true;
    }
    return false;
}
bool invalidInput = false;
double aPowN1(double x, long n)
{
    if (n == 0)
    {
        return 1.0;
    }
    else if (doubleEqual(x, 0.0) || doubleEqual(x, 1.0) || n == 1)
    {
        return x;
    }
    else if (n & 1)
    {
        return aPowN1(x, n >> 1) * aPowN1(x, n >> 1) * x;
    }
    return aPowN1(x, n >> 1) * aPowN1(x, n >> 1);
}
double aPowN2(double x, long n)
{
    if (n == 0)
    {
        return 1.0;
    }
    else if (doubleEqual(x, 0.0) || doubleEqual(x, 1.0) || n == 1)
    {
        return x;
    }
    else if (n & 1)
    {
        return aPowN2(x * x, n >> 1) * x;
    }
    return aPowN2(x * x, n >> 1);
}
double myPow(double x, long n)
{
    if (doubleEqual(x, 0.0) && n < 0)
    {
        invalidInput = true;
        return 0.0;
    }
    else if (n < 0)
    {
        return 1.0 / myPow(x, -n);
    }
    // double res = 1.0;
    // for (int i = 0; i < n; ++i)
    // {
    //     res *= x;
    // }
    return aPowN2(x, n);
}

//面试题17：打印从1到最大的n位数
vector<int> printNumbers(int n)
{
    int temp = 0;
    vector<int> res;
    for (int i = 0; i < n; ++i)
    {
        temp = temp * 10 + 9;
    }
    for (int i = 1; i <= temp; ++i)
    {
        res.push_back(i);
    }
    return res;
}
bool Increment(char *nums, int length)
{
    int upflag = 0;
    for (int i = (length - 1); i >= 0; --i)
    {
        int temp = nums[i] - '0';
        if (i == (length - 1))
        {
            ++temp;
        }
        temp += upflag;
        upflag = 0;
        if (temp >= 10)
        {
            temp -= 10;
            upflag = 1;
        }
        nums[i] = temp + '0';
        if (i == 0 && upflag)
        {
            return true;
        }
    }
    return false;
}
void Print1Number(char *nums, int length)
{
    bool beginZero = true;
    for (int i = 0; i < length; ++i)
    {
        if (nums[i] == '0' && beginZero)
        {
            continue;
        }
        beginZero = false;
        printf("%c", nums[i]);
    }
    printf("\n");
}
void Print1ToMaxOfNDigits(int n)
{
    char *nums = new char[n + 1];
    memset(nums, '0', n * sizeof(char));
    nums[n] = '\0';
    while (!Increment(nums, n))
    {
        Print1Number(nums, n);
    }
}

//面试题18-1：删除链表的节点
// ListNode *deleteNode(ListNode *head, int val)
// {
//     if (!head)
//     {
//         return NULL;
//     }
//     else if (head->val == val)
//     {
//         return head->next;
//     }
//     ListNode *temp1 = head;
//     while (temp1->next)
//     {
//         if (temp1->next->val == val)
//         {
//             temp1->next = temp1->next->next;
//             break;
//         }
//         temp1 = temp1->next;
//     }
//     return head;
// }
ListNode *deleteNode(ListNode *head, int val)
{
    if (!head)
    {
        return NULL;
    }
    else if (head->val == val)
    {
        return head->next;
    }
    ListNode *temp1 = head;
    while (temp1)
    {
        if (temp1->next && !temp1->next->next && temp1->next->val == val)
        {
            temp1->next = NULL;
        }
        else if (temp1->val == val)
        {
            temp1->val = temp1->next->val;
            temp1->next = temp1->next->next;
            break;
        }
        temp1 = temp1->next;
    }
    return head;
}

//面试题18-2：删除链表中重复节点(LeetCode-82)
ListNode *deleteDuplicates(ListNode *head)
{
    if (!head || !head->next)
    {
        return head;
    }
    ListNode *newHead = new ListNode(0);
    ListNode *nodePre = newHead;
    ListNode *nodeTemp = head;
    nodePre->next = head;
    while (nodeTemp && nodeTemp->next)
    {
        if (nodeTemp->val != nodeTemp->next->val)
        {
            nodePre = nodeTemp;
            nodeTemp = nodeTemp->next;
        }
        else
        {
            int val = nodeTemp->val;
            while (nodeTemp && nodeTemp->val == val)
            {
                nodeTemp = nodeTemp->next;
            }
            nodePre->next = nodeTemp;
        }
    }
    return newHead->next;
}

//面试题18-3：删除链表中重复元素(LeetCode-83)
ListNode *deleteDuplicates2(ListNode *head)
{
    ListNode *temp = head;
    while (temp && temp->next)
    {
        if (temp->val == temp->next->val)
        {
            temp->next = temp->next->next;
        }
        else
        {
            temp = temp->next;
        }
    }
    return head;
}

//面试题19：正则表达式匹配
// bool isMatch(string s, string p)
// {
//     if (s[0] == '\0' && p[0] == '\0')
//     {
//         return true;
//     }
//     else if (s[0] != '\0' && p[0] == '\0')
//     {
//         return false;
//     }
//     else if (p[1] == '*')
//     {
//         if (p[0] == s[0] || p[0] == '.')
//         {
//             return (s.size() && isMatch(s.substr(1, s.size()), p.substr(0, p.size()))) ||
//                    isMatch(s.substr(0, s.size()), p.substr(2, p.size()));
//         }
//         else
//         {
//             return isMatch(s.substr(0, s.size()), p.substr(2, p.size()));
//         }
//     }
//     else if (p[0] == s[0] || p[0] == '.')
//     {
//         return (s.size() && isMatch(s.substr(1, s.size()), p.substr(1, p.size())));
//     }
//     else
//     {
//         return false;
//     }
// }
bool isMatch(string s, string p)
{
    int sLength = s.size();
    int pLength = p.size();
    vector<vector<bool>> store(sLength + 1, vector<bool>(pLength + 1, false));
    store[0][0] = true;
    for (int j = 2; j <= pLength; j += 2)
    {
        if (p[j - 1] != '*')
        {
            break;
        }
        else
        {
            store[0][j] = true;
        }
    }
    for (int i = 1; i <= sLength; ++i)
    {
        for (int j = 1; j <= pLength; ++j)
        {
            if (j >= 2 && p[j - 1] == '*')
            {
                store[i][j] = (store[i - 1][j] && (p[j - 2] == s[i - 1] || p[j - 2] == '.')) || store[i][j - 2];
            }
            else
            {
                store[i][j] = store[i - 1][j - 1] && (p[j - 1] == s[i - 1] || p[j - 1] == '.');
            }
        }
    }
    return store[sLength][pLength];
}

//面试题20：表示数值的字符串
bool scanUnsignedInteger(string &s)
{
    int nums = 0;
    while (s[nums] != '\0')
    {
        if (s[nums] >= '0' && s[nums] <= '9')
        {
            ++nums;
        }
        else
        {
            break;
        }
    }
    s = s.substr(nums, s.size());
    return nums > 0 ? true : false;
}
bool scanInteger(string &s)
{
    if (s[0] == '+' || s[0] == '-')
    {
        s = s.substr(1, s.size());
    }
    return scanUnsignedInteger(s);
}
bool isNumber(string s)
{
    if (s.empty())
    {
        return false;
    }
    int spaceBegin = 0;
    while (s[spaceBegin] == ' ')
    {
        ++spaceBegin;
    }
    s = s.substr(spaceBegin, s.size());
    bool flag = scanInteger(s);
    if (s[0] == '.')
    {
        s = s.substr(1, s.size());
        flag |= scanUnsignedInteger(s);
    }
    if (!flag)
    {
        return flag;
    }
    if (s[0] == 'e' || s[0] == 'E')
    {
        s = s.substr(1, s.size());
        flag &= scanInteger(s);
    }
    int spaceEnd = 0;
    while (s[spaceEnd] == ' ')
    {
        ++spaceEnd;
    }
    s = s.substr(spaceEnd, s.size());
    return flag && s[0] == '\0';
}

//面试题21：调整数组顺序使奇数位于偶数前面
bool decision(int n)
{
    return n & 1; //奇数true，偶数false
}
vector<int> exchange(vector<int> &nums)
{
    int length = nums.size();
    if (length <= 1)
    {
        return nums;
    }
    int left = 0, right = length - 1;
    while (left < right)
    {
        while (left < right && decision(nums[left]))
        {
            ++left;
        }
        while (left < right && !decision(nums[right]))
        {
            --right;
        }
        if (left < right)
        {
            swap(nums[left], nums[right]);
            ++left;
            --right;
        }
    }
    return nums;
}

//面试题22：链表中倒数第k个节点
ListNode *getKthFromEnd(ListNode *head, int k)
{
    if (!head || !k)
    {
        return NULL;
    }
    ListNode *fast = head;
    ListNode *slow = head;
    while (k && fast)
    {
        fast = fast->next;
        --k;
    }
    if (k != 0)
    {
        return NULL;
    }
    while (fast)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

//面试题23：链表中环的入口节点(LeetCode-142) a+nb必为链表起点
ListNode *detectCycle(ListNode *head)
{
    if (!head || !head->next)
    {
        return NULL;
    }
    ListNode *fast = head->next->next;
    ListNode *slow = head->next;
    while (fast != slow)
    {
        if (!fast || !fast->next)
        {
            return NULL;
        }
        fast = fast->next->next;
        slow = slow->next;
    }
    slow = head;
    while (fast != slow)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}

//面试题24-1：反转链表
ListNode *reverseList(ListNode *head)
{
    if (!head || !head->next)
    {
        return head;
    }
    ListNode *pre = NULL;
    ListNode *temp = head;
    ListNode *next = head->next;
    while (next)
    {
        temp->next = pre;
        pre = temp;
        temp = next;
        next = next->next;
    }
    temp->next = pre;
    return temp;
}

//面试题24-2：反转链表Ⅱ(LeetCode-92)
ListNode *reverseBetween(ListNode *head, int m, int n)
{
    ListNode *before = NULL, *first = head, *next = first->next;
    int i = m - 1;
    if (i)
    {
        before = head, first = first->next, next = next->next;
    }
    while (--i > 0)
    {
        before = before->next;
        first = first->next;
        next = next->next;
    }
    i = n - m;
    ListNode *after = first;
    while (i--)
    {
        ListNode *last = next->next;
        next->next = first;
        first = next;
        next = last;
    }
    if (!before)
    {
        before = first, after->next = next;
        return before;
    }
    before->next = first;
    after->next = next;
    return head;
}

//面试题25：合并两个排序的链表
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
    ListNode *res = new ListNode(0);
    ListNode *temp = res;
    while (l1 || l2)
    {
        if (!l1)
        {
            temp->next = l2;
            l2 = l2->next;
        }
        else if (!l2)
        {
            temp->next = l1;
            l1 = l1->next;
        }
        else if (l1->val <= l2->val)
        {
            temp->next = l1;
            l1 = l1->next;
        }
        else
        {
            temp->next = l2;
            l2 = l2->next;
        }
        temp = temp->next;
    }
    return res->next;
}

//面试题26：树的子结构
bool compareSubtree(TreeNode *A, TreeNode *B)
{
    if (!B)
    {
        return true;
    }
    if (!A)
    {
        return false;
    }
    if (A->val != B->val)
    {
        return false;
    }
    return compareSubtree(A->left, B->left) && compareSubtree(A->right, B->right);
}
bool isSubStructure(TreeNode *A, TreeNode *B)
{
    if (!A || !B)
    {
        return false;
    }
    bool res = false;
    if (A->val == B->val)
    {
        res = compareSubtree(A, B);
    }
    if (!res)
    {
        res = isSubStructure(A->left, B);
    }
    if (!res)
    {
        res = isSubStructure(A->right, B);
    }
    return res;
}

//面试题27：二叉树的镜像
TreeNode *mirrorTree(TreeNode *root)
{
    if (!root)
    {
        return root;
    }
    TreeNode *temp = root->left;
    root->left = mirrorTree(root->right);
    root->right = mirrorTree(temp);
    return root;
}

//面试题28：对称的二叉树
bool isSymmetric(TreeNode *root1, TreeNode *root2)
{
    if (!root1 && !root2)
    {
        return true;
    }
    else if (!root1 || !root2)
    {
        return false;
    }
    else if (root1->val != root2->val)
    {
        return false;
    }
    return isSymmetric(root1->left, root2->right) && isSymmetric(root1->right, root2->left);
}
bool isSymmetric(TreeNode *root)
{
    return isSymmetric(root, root);
}

//面试题29：顺时针打印矩阵
void printCircle(vector<vector<int>> &matrix, vector<int> &res, int count, int row, int col)
{
    for (int j = count; j < (col - count); ++j)
    {
        res.push_back(matrix[count][j]);
    }
    for (int i = count + 1; i < (row - count); ++i)
    {
        res.push_back(matrix[i][col - count - 1]);
    }
    for (int j = col - count - 2; 2 * count < (row - 1) && j >= count; --j)
    {
        res.push_back(matrix[row - count - 1][j]);
    }
    for (int i = row - count - 2; 2 * count < (col - 1) && i > count; --i)
    {
        res.push_back(matrix[i][count]);
    }
    return;
}
vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    vector<int> res;
    if (matrix.empty() || !matrix.size() || !matrix[0].size())
    {
        return res;
    }
    int row = matrix.size();
    int col = matrix[0].size();
    for (int i = 0; (i < (row + 1) >> 1) && (i < (col + 1) >> 1); ++i)
    {
        printCircle(matrix, res, i, row, col);
    }
    return res;
}

//面试题30：包含min函数的栈
class MinStack
{
public:
    MinStack() {}
    void push(int x)
    {
        data.push(x);
        if (data_min.empty() || data_min.top() >= x)
        {
            data_min.push(x);
        }
        else
        {
            data_min.push(data_min.top());
        }
        return;
    }
    void pop()
    {
        if (!data.empty())
        {
            data.pop();
            data_min.pop();
        }
        return;
    }
    int top()
    {
        if (!data.empty())
        {
            return data.top();
        }
        return 0;
    }
    int min()
    {
        if (!data_min.empty())
        {
            return data_min.top();
        }
        return 0;
    }

private:
    stack<int> data;
    stack<int> data_min;
};

//面试题31：栈的压入、弹出序列
bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
{
    stack<int> store;
    if (pushed.size() != popped.size())
    {
        return false;
    }
    else if (pushed.size() <= 1)
    {
        return true;
    }
    int length = pushed.size();
    int left = 0;
    int right = 0;
    while (right < length)
    {
        if (left < length && pushed[left] == popped[right])
        {
            ++left;
            ++right;
        }
        else if (!store.empty() && store.top() == popped[right])
        {
            store.pop();
            ++right;
        }
        else if (left >= length)
        {
            return false;
        }
        else
        {
            store.push(pushed[left]);
            ++left;
        }
    }
    return true;
}

//面试题32-1：从上到下打印二叉树
vector<int> levelOrder(TreeNode *root)
{
    vector<int> res;
    queue<TreeNode *> store;
    if (!root)
    {
        return res;
    }
    store.push(root);
    while (!store.empty())
    {
        TreeNode *temp = store.front();
        res.push_back(temp->val);
        store.pop();
        if (temp->left)
        {
            store.push(temp->left);
        }
        if (temp->right)
        {
            store.push(temp->right);
        }
    }
    return res;
}

//面试题32-2：从上到下打印二叉树Ⅱ
vector<vector<int>> levelOrder2(TreeNode *root)
{
    vector<vector<int>> res;
    vector<int> tempRes;
    if (!root)
    {
        return res;
    }
    queue<TreeNode *> store;
    store.push(root);
    int thisLevel = 1;
    int nextLevel = 0;
    while (!store.empty())
    {
        TreeNode *temp = store.front();
        tempRes.push_back(temp->val);
        store.pop();
        --thisLevel;
        if (temp->left)
        {
            store.push(temp->left);
            ++nextLevel;
        }
        if (temp->right)
        {
            store.push(temp->right);
            ++nextLevel;
        }
        if (!thisLevel)
        {
            res.push_back(tempRes);
            tempRes.clear();
            thisLevel = nextLevel;
            nextLevel = 0;
        }
    }
    return res;
}

//面试题32-3：从上到下打印二叉树Ⅲ(odd为奇数,even为偶数)
vector<vector<int>> levelOrder3(TreeNode *root)
{
    vector<vector<int>> res;
    vector<int> tempRes;
    if (!root)
    {
        return res;
    }
    stack<TreeNode *> odd;
    stack<TreeNode *> even;
    odd.push(root);
    while (!odd.empty() || !even.empty())
    {
        while (!odd.empty())
        {
            TreeNode *temp = odd.top();
            tempRes.push_back(temp->val);
            odd.pop();
            if (temp->left)
            {
                even.push(temp->left);
            }
            if (temp->right)
            {
                even.push(temp->right);
            }
        }
        if (!tempRes.empty())
        {
            res.push_back(tempRes);
            tempRes.clear();
        }
        while (!even.empty())
        {
            TreeNode *temp = even.top();
            tempRes.push_back(temp->val);
            even.pop();
            if (temp->right)
            {
                odd.push(temp->right);
            }
            if (temp->left)
            {
                odd.push(temp->left);
            }
        }
        if (!tempRes.empty())
        {
            res.push_back(tempRes);
            tempRes.clear();
        }
    }
    return res;
}

//面试题33：二叉搜索树的后序遍历
bool verifyPostorder(vector<int> &postorder, int begin, int end)
{
    if (begin >= end)
    {
        return true;
    }
    int root = postorder[end];
    int countl = begin;
    while (countl < end && postorder[countl] <= postorder[end])
    {
        ++countl;
    }
    int countr = countl;
    while (countr < end && postorder[countr] >= postorder[end])
    {
        ++countr;
    }
    return countr == end && verifyPostorder(postorder, begin, countl - 1) && verifyPostorder(postorder, countl, end - 1);
}
bool verifyPostorder(vector<int> &postorder)
{
    int length = postorder.size();
    if (length <= 2)
    {
        return true;
    }
    return verifyPostorder(postorder, 0, length - 1);
}

int main()
{
    vector<int> nums3 = {0, 1, 2, 0, 4, 5, 6, 7, 8, 9};
    int res3 = findRepeatNumber(nums3);

    vector<vector<int>> matrix4_1 = {{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}};
    vector<vector<int>> matrix4_2 = {{1}, {3}, {5}};
    bool res4_1 = findNumberIn2DArray(matrix4_1, 20);
    bool res4_2 = findNumberIn2DArray(matrix4_2, 4);

    string s5 = "We are happy.";
    string res5 = replaceSpace(s5);

    ListNode *list6 = new ListNode(1);
    list6->next = new ListNode(3);
    list6->next->next = new ListNode(2);
    vector<int> res6 = reversePrint(list6);

    vector<int> nums7_1 = {1, 2, 3};
    vector<int> nums7_2 = {3, 2, 1};
    TreeNode *res7 = buildTree(nums7_1, nums7_2);

    TreeLinkNode *tree8 = new TreeLinkNode(1);
    tree8->left = new TreeLinkNode(2);
    tree8->right = new TreeLinkNode(3);
    tree8->left->next = tree8;
    tree8->right->next = tree8;
    TreeLinkNode *res8 = GetNext(tree8->right);

    CQueue *obj9 = new CQueue();
    obj9->appendTail(1);
    int param9 = obj9->deleteHead();

    int res10_1 = fib(45);

    int res10_2 = numWays(3);

    vector<int> nums11_1 = {2, 2, 2, 0, 1};
    int res11_1 = minArray(nums11_1);

    vector<int> nums11_2 = {2, 5, 6, 0, 0, 1, 2};
    bool res11_2 = search(nums11_2, 0);

    vector<vector<char>> board12_1 = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    vector<vector<char>> board12_2 = {{'a'}};
    bool res12_1 = exist(board12_1, "ABCCED");
    bool res12_2 = exist(board12_2, "a");

    int res13 = movingCount(2, 3, 1);

    int res14 = cuttingRope(10);

    int res15 = hammingWeight(9);

    double res16 = myPow(0.00001, 2147483647);

    vector<int> res17 = printNumbers(3);
    // Print1ToMaxOfNDigits(3);

    ListNode *list18_1 = new ListNode(4);
    list18_1->next = new ListNode(5);
    list18_1->next->next = new ListNode(1);
    list18_1->next->next->next = new ListNode(9);
    ListNode *res18_1 = deleteNode(list18_1, 5);

    ListNode *list18_2 = new ListNode(1);
    list18_2->next = new ListNode(2);
    list18_2->next->next = new ListNode(3);
    list18_2->next->next->next = new ListNode(3);
    list18_2->next->next->next->next = new ListNode(4);
    list18_2->next->next->next->next->next = new ListNode(4);
    list18_2->next->next->next->next->next->next = new ListNode(5);
    ListNode *res18_2 = deleteDuplicates(list18_2);

    ListNode *list18_3 = new ListNode(3);
    list18_3->next = new ListNode(2);
    list18_3->next->next = new ListNode(1);
    list18_3->next->next->next = new ListNode(1);
    list18_3->next->next->next->next = new ListNode(2);
    list18_3->next->next->next->next->next = new ListNode(3);
    ListNode *res18_3 = deleteDuplicates2(list18_3);

    string s19 = "ab";
    string p19 = ".*";
    bool res19 = isMatch(s19, p19);

    string s20 = " 2";
    bool res20 = isNumber(s20);

    vector<int> nums21 = {1, 2, 3, 4};
    vector<int> res21 = exchange(nums21);

    ListNode *list22 = new ListNode(1);
    list22->next = new ListNode(2);
    list22->next->next = new ListNode(3);
    list22->next->next->next = new ListNode(4);
    list22->next->next->next->next = new ListNode(5);
    ListNode *res22 = getKthFromEnd(list22, 2);

    ListNode *list23 = new ListNode(3);
    list23->next = new ListNode(2);
    list23->next->next = new ListNode(0);
    list23->next->next->next = new ListNode(-4);
    list23->next->next->next->next = list23->next;
    ListNode *res23 = detectCycle(list23);

    ListNode *list24_1 = new ListNode(1);
    list24_1->next = new ListNode(2);
    list24_1->next->next = new ListNode(3);
    list24_1->next->next->next = new ListNode(4);
    list24_1->next->next->next->next = new ListNode(5);
    ListNode *res24_1 = reverseList(list24_1);

    ListNode *list24_2 = new ListNode(1);
    list24_2->next = new ListNode(2);
    list24_2->next->next = new ListNode(3);
    list24_2->next->next->next = new ListNode(4);
    list24_2->next->next->next->next = new ListNode(5);
    ListNode *res24_2 = reverseBetween(list24_2, 2, 4);

    ListNode *list25_1 = new ListNode(1);
    list25_1->next = new ListNode(2);
    list25_1->next->next = new ListNode(3);
    ListNode *list25_2 = new ListNode(1);
    list25_2->next = new ListNode(2);
    list25_2->next->next = new ListNode(4);
    ListNode *res25 = mergeTwoLists(list25_1, list25_2);

    TreeNode *tree26_A = new TreeNode(3);
    tree26_A->left = new TreeNode(4);
    tree26_A->right = new TreeNode(5);
    tree26_A->left->left = new TreeNode(1);
    tree26_A->left->right = new TreeNode(2);
    TreeNode *tree26_B = new TreeNode(4);
    tree26_B->left = new TreeNode(1);
    bool res26 = isSubStructure(tree26_A, tree26_B);

    TreeNode *tree27 = new TreeNode(4);
    tree27->left = new TreeNode(2);
    tree27->right = new TreeNode(7);
    tree27->left->left = new TreeNode(1);
    tree27->left->right = new TreeNode(3);
    tree27->right->left = new TreeNode(6);
    tree27->right->right = new TreeNode(9);
    TreeNode *res27 = mirrorTree(tree27);

    TreeNode *tree28 = new TreeNode(1);
    tree28->left = new TreeNode(2);
    tree28->right = new TreeNode(2);
    tree28->left->left = new TreeNode(3);
    tree28->left->right = new TreeNode(4);
    tree28->right->left = new TreeNode(4);
    tree28->right->right = new TreeNode(3);
    bool res28 = isSymmetric(tree28);

    vector<vector<int>> matrix29 = {{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}};
    vector<int> res29 = spiralOrder(matrix29);

    MinStack *obj30 = new MinStack();
    obj30->push(2);
    obj30->pop();
    int param30_1 = obj30->top();
    int param30_2 = obj30->min();

    vector<int> pushed31 = {1, 2, 3, 4, 5};
    vector<int> popped31 = {4, 5, 3, 2, 1};
    bool res31 = validateStackSequences(pushed31, popped31);

    TreeNode *tree32_1 = new TreeNode(3);
    tree32_1->left = new TreeNode(9);
    tree32_1->right = new TreeNode(20);
    tree32_1->right->left = new TreeNode(15);
    tree32_1->right->right = new TreeNode(7);
    vector<int> res32_1 = levelOrder(tree32_1);

    TreeNode *tree32_2 = new TreeNode(3);
    tree32_2->left = new TreeNode(9);
    tree32_2->right = new TreeNode(20);
    tree32_2->right->left = new TreeNode(15);
    tree32_2->right->right = new TreeNode(7);
    vector<vector<int>> res32_2 = levelOrder2(tree32_2);

    TreeNode *tree32_3 = new TreeNode(3);
    tree32_3->left = new TreeNode(9);
    tree32_3->right = new TreeNode(20);
    tree32_3->right->left = new TreeNode(15);
    tree32_3->right->right = new TreeNode(7);
    vector<vector<int>> res32_3 = levelOrder3(tree32_3);

    vector<int> postorder33 = {4, 6, 7, 5};
    bool res33 = verifyPostorder(postorder33);

    return 0;
}