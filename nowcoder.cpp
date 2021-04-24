//牛客网算法题

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <stack>
#include <math.h>
#include <algorithm>
#include <time.h>
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

//NC2：重排链表(LeetCode-143)
void reorderList(ListNode *head)
{
    if (!head || !head->next || !head->next->next)
    {
        return;
    }
    ListNode *fast = head;
    ListNode *slow = head;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    bool flag = fast ? true : false;
    fast = fast ? slow->next : slow;

    ListNode *pre = NULL;
    while (fast)
    {
        ListNode *temp = fast->next;
        fast->next = pre;
        pre = fast;
        fast = temp;
    }

    fast = head;
    slow = head->next;
    while (pre)
    {
        fast->next = pre;
        pre = pre->next;
        fast = fast->next;
        if (pre || (!pre && flag))
        {
            fast->next = slow;
            slow = slow->next;
            fast = fast->next;
        }
    }
    fast->next = NULL;
}

//NC50：链表中的节点每k个一组翻转(LeetCode-25)
ListNode *reverseKGroup(ListNode *head, int k)
{
    int length = 0;
    ListNode *temp = head;
    while (temp)
    {
        temp = temp->next;
        ++length;
    }
    if (k > length)
    {
        return head;
    }
    int count = length / k;
    ListNode *tail = new ListNode(-1);
    tail->next = head;
    ListNode *pre = tail;
    temp = head;
    for (int i = 0; i < count; ++i)
    {
        ListNode *first = NULL;
        ListNode *second = temp;
        for (int j = 0; j < k; ++j)
        {
            ListNode *third = second->next;
            second->next = first;
            first = second;
            second = third;
        }
        pre->next = first;
        temp->next = second;
        pre = temp;
        temp = temp->next;
    }
    return tail->next;
}

//NC51：合并k个已排序的链表(LeetCode-23)
struct cmp
{
    bool operator()(ListNode *a, ListNode *b)
    {
        return a->val >= b->val;
    }
};
ListNode *mergeKLists(vector<ListNode *> &lists)
{
    priority_queue<ListNode *, vector<ListNode *>, cmp> store;
    ListNode *res = new ListNode(-1);
    if (lists.empty())
    {
        return res->next;
    }
    int length = lists.size();
    for (int i = 0; i < length; ++i)
    {
        if (lists[i])
        {
            store.push(lists[i]);
        }
    }
    ListNode *temp = res;
    while (!store.empty())
    {
        temp->next = store.top();
        temp = temp->next;
        store.pop();
        if (temp->next)
        {
            store.push(temp->next);
        }
    }
    return res->next;
}

//NC70：单链表的选择排序(LeetCode-148)
ListNode *sortList(ListNode *head)
{
    if (!head || !head->next)
    {
        return head;
    }
    int length = 0;
    ListNode *temp = head;
    while (temp)
    {
        temp = temp->next;
        ++length;
    }
    ListNode *tail = new ListNode(-1);
    tail->next = head;
    int count = 1;
    while (count < length)
    {
        temp = tail;
        while (temp->next)
        {
            ListNode *list[3];
            list[0] = temp->next;
            list[1] = temp->next;
            int index = 0;
            for (; index < count && list[1]; ++index)
            {
                list[1] = list[1]->next;
            }
            if (!list[1])
            {
                break;
            }
            list[2] = list[1];
            for (index = 0; index < count && list[2]; ++index)
            {
                list[2] = list[2]->next;
            }
            int index1 = count, index2 = index;
            while (list[0] && list[1] && index1 && index2)
            {
                if (list[0]->val <= list[1]->val)
                {
                    temp->next = list[0];
                    list[0] = list[0]->next;
                    --index1;
                }
                else
                {
                    temp->next = list[1];
                    list[1] = list[1]->next;
                    --index2;
                }
                temp = temp->next;
            }
            if (list[0] && index1 > 0)
            {
                temp->next = list[0];
                while (index1--)
                {
                    temp = temp->next;
                }
            }
            if (list[1] && index2 > 0)
            {
                temp->next = list[1];
                while (index2--)
                {
                    temp = temp->next;
                }
            }
            temp->next = list[2];
        }
        count *= 2;
    }
    return tail->next;
}

//NC5：二叉树根节点到叶子节点的所有路径和(LeetCode-129)
void dfs(TreeNode *root, vector<int> &store, int temp)
{
    if (!root->left && !root->right)
    {
        store.push_back(temp * 10 + root->val);
        return;
    }
    if (root->left)
    {
        dfs(root->left, store, temp * 10 + root->val);
    }
    if (root->right)
    {
        dfs(root->right, store, temp * 10 + root->val);
    }
}
int sumNumbers(TreeNode *root)
{
    vector<int> store;
    if (!root)
    {
        return 0;
    }
    dfs(root, store, 0);
    int res = 0;
    int length = store.size();
    for (int i = 0; i < length; ++i)
    {
        res += store[i];
    }
    return res;
}

//NC6：二叉树的最大路径和(LeetCode-124)
int dfs(TreeNode *root, int &maxPath)
{
    if (!root)
    {
        return 0;
    }
    int left = dfs(root->left, maxPath);
    int right = dfs(root->right, maxPath);
    int res = max(root->val, max(root->val + left, root->val + right));
    maxPath = max(maxPath, max(res, root->val + left + right));
    return res;
}
int maxPathSum(TreeNode *root)
{
    if (!root)
    {
        return 0;
    }
    int maxPath = root->val;
    int res = dfs(root, maxPath);
    return maxPath;
}

//NC45：实现二叉树前序、中序、后序遍历(LeetCode-144、94、145)
void dfs1(TreeNode *root, vector<int> &res)
{
    if (!root)
    {
        return;
    }
    res.push_back(root->val);
    dfs1(root->left, res);
    dfs1(root->right, res);
}
void dfs2(TreeNode *root, vector<int> &res)
{
    if (!root)
    {
        return;
    }
    dfs2(root->left, res);
    res.push_back(root->val);
    dfs2(root->right, res);
}
void dfs3(TreeNode *root, vector<int> &res)
{
    if (!root)
    {
        return;
    }
    dfs3(root->left, res);
    dfs3(root->right, res);
    res.push_back(root->val);
}
vector<vector<int>> threeOrders(TreeNode *root)
{
    vector<vector<int>> res;
    vector<int> res1, res2, res3;
    dfs1(root, res1);
    dfs2(root, res2);
    dfs3(root, res3);
    res.push_back(res1);
    res.push_back(res2);
    res.push_back(res3);
    return res;
}

//NC60：判断一棵树是否为搜索二叉树和完全二叉树(LeetCode-98、958)
bool isValidBST(TreeNode *root, vector<int> &store)
{
    if (!root)
    {
        return true;
    }
    bool left = isValidBST(root->left, store);
    if (store.empty())
    {
        store.push_back(root->val);
    }
    else if (root->val <= store[0] || !left)
    {
        return false;
    }
    store[0] = root->val;
    bool right = isValidBST(root->right, store);
    return right;
}
bool isValidBST(TreeNode *root)
{
    vector<int> store;
    return isValidBST(root, store);
}
bool isCompleteTree(TreeNode *root)
{
    if (!root)
    {
        return true;
    }
    queue<TreeNode *> store1;
    queue<int> store2;
    store1.push(root);
    store2.push(1);
    int count = 0;
    TreeNode *temp1 = root;
    int temp2 = 0;
    while (!store1.empty())
    {
        temp1 = store1.front();
        temp2 = store2.front();
        store1.pop();
        store2.pop();
        if (!temp1->left && temp1->right)
        {
            return false;
        }
        if (temp1->left)
        {
            store1.push(temp1->left);
            store2.push(2 * temp2);
        }
        if (temp1->right)
        {
            store1.push(temp1->right);
            store2.push(2 * temp2 + 1);
        }
        ++count;
        if (count != temp2)
        {
            return false;
        }
    }
    return count == temp2;
}
vector<bool> judgeIt(TreeNode *root)
{
    bool res1 = isValidBST(root);
    bool res2 = isCompleteTree(root);
    return vector<bool>{res1, res2};
}

//NC19：子数组最大累计和(LeetCode-53)
int maxsumofSubarray(vector<int> &arr)
{
    int length = arr.size();
    if (!length)
    {
        return 0;
    }
    int res = arr[0];
    for (int i = 1; i < length; ++i)
    {
        arr[i] = max(arr[i - 1] + arr[i], arr[i]);
        res = max(res, arr[i]);
    }
    return res;
}

//NC83：子数组最大乘积(LeetCode-152)
int maxProduct(vector<int> &nums)
{
    int length = nums.size();
    if (!length)
    {
        return 0;
    }
    int nmax = nums[0];
    int nmin = nums[0];
    int res = nums[0];
    for (int i = 1; i < length; ++i)
    {
        int temp = nmax;
        nmax = max(nmax * nums[i], max(nmin * nums[i], nums[i]));
        nmin = min(nmin * nums[i], min(temp * nums[i], nums[i]));
        res = max(res, nmax);
    }
    return res;
}

//NC95：数组中的最长连续子数列(LeetCode-128)
int longestConsecutive(vector<int> &nums)
{
    unordered_set<int> store;
    int length = nums.size();
    for (int i = 0; i < length; ++i)
    {
        if (!store.count(nums[i]))
        {
            store.insert(nums[i]);
        }
    }
    int res = 0;
    for (int i = 0; i < length; ++i)
    {
        if (store.count(nums[i] - 1))
        {
            continue;
        }
        int tempres = 1;
        int temp = nums[i] + 1;
        while (store.count(temp))
        {
            ++tempres;
            ++temp;
        }
        res = max(res, tempres);
    }
    return res;
}

//NC36：两个长度相等的排序数组中找到上中位数(LeetCode-4)
int findMedianinTwoSortedAray(vector<int> &arr1, vector<int> &arr2)
{
    int length1 = arr1.size();
    int length2 = arr2.size();
    if (!length1 && !length2)
    {
        return 0;
    }
    else if (length1 > length2 || (length1 == length2 && arr1[length1 - 1] > arr2[length2 - 1]))
    {
        return findMedianinTwoSortedAray(arr2, arr1);
    }
    int index1 = 0, index2 = 0;
    int target = (length1 + length2 + 1) >> 1;
    while (target)
    {
        if (index1 == length1)
        {
            return arr2[target - 1 + index2];
        }
        else if (target == 1)
        {
            return min(arr1[index1], arr2[index2]);
        }
        int temp = min(target / 2, length1 - index1);
        if (arr1[temp + index1 - 1] < arr2[temp + index2 - 1])
        {
            index1 += temp;
            target -= temp;
        }
        else if (arr1[temp + index1 - 1] > arr2[temp + index2 - 1])
        {
            index2 += temp;
            target -= temp;
        }
        else
        {
            target -= 2 * temp;
            if (!target)
            {
                return max(arr1[temp + index1 - 1], arr2[temp + index2 - 1]);
            }
            index1 += temp;
            index2 += temp;
        }
    }
    return max(arr1[index1 - 1], arr2[index2 - 1]);
}
int findMedianSortedArrays(vector<int> &arr1, vector<int> &arr2, int target)
{
    int length1 = arr1.size();
    int length2 = arr2.size();
    int index1 = 0, index2 = 0;
    while (target)
    {
        if (index1 == length1)
        {
            return arr2[target - 1 + index2];
        }
        else if (target == 1)
        {
            return min(arr1[index1], arr2[index2]);
        }
        int temp = min(target / 2, length1 - index1);
        if (arr1[temp + index1 - 1] < arr2[temp + index2 - 1])
        {
            index1 += temp;
            target -= temp;
        }
        else if (arr1[temp + index1 - 1] > arr2[temp + index2 - 1])
        {
            index2 += temp;
            target -= temp;
        }
        else
        {
            target -= 2 * temp;
            if (!target)
            {
                return max(arr1[temp + index1 - 1], arr2[temp + index2 - 1]);
            }
            index1 += temp;
            index2 += temp;
        }
    }
    return max(arr1[index1 - 1], arr2[index2 - 1]);
}
double findMedianSortedArrays(vector<int> &arr1, vector<int> &arr2)
{
    int length1 = arr1.size();
    int length2 = arr2.size();
    if (!length1 && !length2)
    {
        return 0.0;
    }
    else if (length1 > length2 || (length1 == length2 && arr1[length1 - 1] > arr2[length2 - 1]))
    {
        return findMedianSortedArrays(arr2, arr1);
    }
    int target = (length1 + length2 + 1) >> 1;
    if ((length1 + length2) % 2)
    {
        return (double)findMedianSortedArrays(arr1, arr2, target);
    }
    else
    {
        return (double)(findMedianSortedArrays(arr1, arr2, target) + findMedianSortedArrays(arr1, arr2, target + 1)) / 2;
    }
}

//NC54：数组中相加和为0的三个数(LeetCode-15)
vector<vector<int>> threeSum(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    int length = nums.size();
    if (length <= 2)
    {
        return res;
    }
    for (int i = 0; i <= length - 3; ++i)
    {
        int left = i + 1;
        int right = length - 1;
        if (nums[i] > 0)
        {
            break;
        }
        else if (i && nums[i] == nums[i - 1])
        {
            continue;
        }
        while (left < right)
        {
            if (nums[i] + nums[left] + nums[right] > 0)
            {
                --right;
                while (left < right && right <= length - 2 && nums[right] == nums[right + 1])
                    --right;
            }
            else if (nums[i] + nums[left] + nums[right] < 0)
            {
                ++left;
                while (left < right && left > i && nums[left - 1] == nums[left])
                    ++left;
            }
            else
            {
                vector<int> temp{nums[i], nums[left], nums[right]};
                res.push_back(temp);
                ++left;
                --right;
                while (left < right && left > i && nums[left - 1] == nums[left])
                    ++left;
                while (left < right && right <= length - 2 && nums[right] == nums[right + 1])
                    --right;
            }
        }
    }
    return res;
}

//NC88：数组中的第K个最大元素(LeetCode-215)
void findKthLargest(vector<int> &nums, int k, int begin, int end, int length)
{
    if (begin >= end)
    {
        return;
    }
    int index = begin;
    for (int i = begin; i < end; ++i)
    {
        if (nums[i] <= nums[end])
        {
            swap(nums[index], nums[i]);
            ++index;
        }
    }
    swap(nums[index], nums[end]);
    if (length - index > k)
    {
        findKthLargest(nums, k, index + 1, end, length);
    }
    else if (length - index < k)
    {
        findKthLargest(nums, k, begin, index - 1, length);
    }
}
int findKthLargest(vector<int> &nums, int k)
{
    int length = nums.size();
    if (!k || k > length)
    {
        return 0;
    }
    findKthLargest(nums, k, 0, length - 1, length);
    return nums[length - k];
}

//NC93：LRU缓存机制(双向链表、非循环链表)(LeetCode-146)
struct DoubleList
{
    int key, value;
    DoubleList *prev;
    DoubleList *next;
    DoubleList() : key(0), value(0), prev(NULL), next(NULL) {}
    DoubleList(int a, int b) : key(a), value(b), prev(NULL), next(NULL) {}
};
class LRUCache
{
public:
    LRUCache(int capacity) : cap(capacity), size(0)
    {
        head = new DoubleList();
        tail = new DoubleList();
        head->next = tail;
        tail->prev = head;
    }
    int get(int key)
    {
        if (!hashmap.count(key))
        {
            return -1;
        }
        else
        {
            DoubleList *temp = hashmap[key];
            if (head->next != temp)
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                temp->prev = head;
                temp->next = head->next;
                head->next->prev = temp;
                head->next = temp;
            }
            return head->next->value;
        }
    }
    void put(int key, int value)
    {
        if (hashmap.count(key))
        {
            hashmap[key]->value = value;
            int temp = get(key);
        }
        else
        {
            ++size;
            DoubleList *temp = new DoubleList(key, value);
            temp->prev = head;
            temp->next = head->next;
            head->next->prev = temp;
            head->next = temp;
            hashmap[key] = temp;
            if (size > cap)
            {
                DoubleList *preNode = tail->prev;
                preNode->prev->next = tail;
                tail->prev = preNode->prev;
                hashmap.erase(preNode->key);
                delete preNode;
                --size;
            }
        }
    }

private:
    int cap;
    int size;
    unordered_map<int, DoubleList *> hashmap;
    DoubleList *head;
    DoubleList *tail;
};

//NC94：LFU缓存(LeetCode-460)(用指针则需重载compare,否则就是比较指针的值)
struct LFUNode
{
public:
    int frequency;
    int time;
    int key;
    int val;
    LFUNode() : frequency(0), time(0), key(0), val(0) {}
    LFUNode(int f, int t, int k, int v) : frequency(f), time(t), key(k), val(v) {}
    bool operator<(const LFUNode &rhs) const
    {
        if (frequency != rhs.frequency)
        {
            return frequency < rhs.frequency;
        }
        else
        {
            return time < rhs.time;
        }
    }
};
class LFUCache
{
public:
    LFUCache(int capacity) : cap(capacity), time(0)
    {
        rbTree.clear();
        hashmap.clear();
    }
    int get(int key)
    {
        ++time;
        if (!cap || !hashmap.count(key))
        {
            return -1;
        }
        LFUNode &temp = hashmap[key];
        rbTree.erase(temp);
        ++temp.frequency;
        temp.time = time;
        rbTree.insert(temp);
        return temp.val;
    }
    void put(int key, int value)
    {
        ++time;
        if (!cap)
        {
            return;
        }
        if (hashmap.count(key))
        {
            LFUNode &temp = hashmap[key];
            rbTree.erase(temp);
            ++temp.frequency;
            temp.time = time;
            temp.val = value;
            rbTree.insert(temp);
        }
        else
        {
            LFUNode temp = LFUNode(1, time, key, value);
            hashmap[key] = temp;
            if (cap == rbTree.size())
            {
                hashmap.erase(rbTree.begin()->key);
                rbTree.erase(rbTree.begin());
            }
            rbTree.insert(temp);
        }
    }

private:
    int cap;
    int time;
    set<LFUNode> rbTree;
    unordered_map<int, LFUNode> hashmap;
};

//NC124：实现前缀树(LeetCode-208)(isEnd为了同时存app和apple)
class Trie
{
public:
    Trie() : isEnd(false)
    {
        memset(next, 0, 26 * sizeof(next[0]));
    }
    void insert(string word)
    {
        int length = word.size();
        Trie *temp = this;
        for (int i = 0; i < length; ++i)
        {
            if (!temp->next[word[i] - 'a'])
            {
                temp->next[word[i] - 'a'] = new Trie();
            }
            temp = temp->next[word[i] - 'a'];
        }
        temp->isEnd = true;
    }
    bool search(string word)
    {
        int length = word.size();
        Trie *temp = this;
        for (int i = 0; i < length; ++i)
        {
            if (!temp->next[word[i] - 'a'])
            {
                return false;
            }
            temp = temp->next[word[i] - 'a'];
        }
        return temp->isEnd;
    }
    bool startsWith(string prefix)
    {
        int length = prefix.size();
        Trie *temp = this;
        for (int i = 0; i < length; ++i)
        {
            if (!temp->next[prefix[i] - 'a'])
            {
                return false;
            }
            temp = temp->next[prefix[i] - 'a'];
        }
        return true;
    }

private:
    bool isEnd;
    Trie *next[26];
};

//NC137：表达式求值(LeetCode-224、227、772)
int solve(string s, int &begin)
{
    long res = 0;
    long temp = 0;
    char sign = '+';
    stack<long> store;
    for (; begin <= s.size(); ++begin)
    {
        if (s[begin] <= '9' && s[begin] >= '0')
        {
            temp = temp * 10 + s[begin] - '0';
        }
        else if (s[begin] == '+' || s[begin] == '-' || s[begin] == '*' || s[begin] == ')' || s[begin] == '\0')
        {
            if (sign == '+')
            {
                store.push(temp);
            }
            else if (sign == '-')
            {
                store.push(-temp);
            }
            else if (sign == '*')
            {
                int multiplication = store.top();
                store.pop();
                store.push(multiplication * temp);
            }
            if (s[begin] == ')')
            {
                break;
            }
            sign = s[begin];
            temp = 0;
        }
        else if (s[begin] == '(')
        {
            ++begin;
            temp = solve(s, begin);
        }
    }
    while (!store.empty())
    {
        temp = store.top();
        store.pop();
        res += temp;
    }
    return res;
}
int solve(string s)
{
    int begin = 0;
    return solve(s, begin);
}

//NC140：快速排序(LeetCode-912)
void MySort(vector<int> &arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    srand(time(0));
    int rd = rand() % (right - left + 1) + left;
    swap(arr[rd], arr[right]);
    int index = left;
    for (int i = left; i < right; ++i)
    {
        if (arr[i] <= arr[right])
        {
            swap(arr[index], arr[i]);
            ++index;
        }
    }
    swap(arr[index], arr[right]);
    MySort(arr, left, index - 1);
    MySort(arr, index + 1, right);
}
vector<int> MySort(vector<int> &arr)
{
    int length = arr.size();
    if (length <= 1)
    {
        return arr;
    }
    MySort(arr, 0, length - 1);
    return arr;
}

int main()
{
    { //链表
        ListNode *list2 = new ListNode(1);
        list2->next = new ListNode(2);
        list2->next->next = new ListNode(3);
        list2->next->next->next = new ListNode(4);
        list2->next->next->next->next = new ListNode(5);
        reorderList(list2);

        ListNode *list50 = new ListNode(1);
        list50->next = new ListNode(2);
        list50->next->next = new ListNode(3);
        list50->next->next->next = new ListNode(4);
        list50->next->next->next->next = new ListNode(5);
        ListNode *res50 = reverseKGroup(list50, 2);

        ListNode *list51_1 = new ListNode(1);
        list51_1->next = new ListNode(4);
        list51_1->next->next = new ListNode(5);
        ListNode *list51_2 = new ListNode(1);
        list51_2->next = new ListNode(3);
        list51_2->next->next = new ListNode(4);
        ListNode *list51_3 = new ListNode(2);
        list51_3->next = new ListNode(6);
        vector<ListNode *> list51 = {list51_1, list51_2, list51_3};
        ListNode *res51 = mergeKLists(list51);

        ListNode *list70 = new ListNode(4);
        list70->next = new ListNode(2);
        list70->next->next = new ListNode(1);
        list70->next->next->next = new ListNode(3);
        ListNode *res70 = sortList(list70);
    }

    { //二叉树
        TreeNode *tree5 = new TreeNode(1);
        tree5->left = new TreeNode(2);
        tree5->right = new TreeNode(3);
        int res5 = sumNumbers(tree5);

        TreeNode *tree6 = new TreeNode(1);
        tree6->left = new TreeNode(2);
        tree6->right = new TreeNode(3);
        int res6 = sumNumbers(tree6);

        TreeNode *tree45 = new TreeNode(1);
        tree45->left = new TreeNode(2);
        tree45->right = new TreeNode(3);
        vector<vector<int>> res = threeOrders(tree45);

        TreeNode *tree60 = new TreeNode(1);
        tree60->left = new TreeNode(2);
        tree60->right = new TreeNode(3);
        tree60->left->left = new TreeNode(4);
        tree60->left->right = new TreeNode(5);
        tree60->right->left = new TreeNode(6);
        bool res60 = isCompleteTree(tree60);
    }

    { //数组(子数组3题&&排序数组3题)
        vector<int> nums19 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        int res19 = maxsumofSubarray(nums19);

        vector<int> nums83 = {2, 3, -2, 4};
        int res83 = maxProduct(nums83);

        vector<int> nums95 = {100, 4, 200, 1, 3, 2};
        int res95 = longestConsecutive(nums95);

        vector<int> nums36_1 = {1, 2, 3, 4};
        vector<int> nums36_2 = {3, 4, 5, 6};
        double res36 = findMedianinTwoSortedAray(nums36_1, nums36_2);

        vector<int> nums54 = {-1, 0, 1, 2, -1, -4};
        vector<vector<int>> res54 = threeSum(nums54);

        vector<int> nums88 = {3, 1, 2, 4};
        int res88 = findKthLargest(nums88, 2);
    }

    { //设计结构
        LRUCache *obj93 = new LRUCache(2);
        obj93->put(1, 0);
        obj93->put(2, 2);
        int param93 = obj93->get(1);
        obj93->put(3, 3);
        param93 = obj93->get(2);
        obj93->put(4, 4);
        param93 = obj93->get(1);
        param93 = obj93->get(3);
        param93 = obj93->get(4);

        LFUCache *obj94 = new LFUCache(6);
        obj94->put(1, 1);
        obj94->put(2, 2);
        int param94 = obj94->get(1);
        obj94->put(3, 3);
        param94 = obj94->get(2);
        param94 = obj94->get(3);
        param94 = obj94->get(1);
        param94 = obj94->get(3);
        param94 = obj94->get(4);
        obj94->put(4, 4);

        Trie *obj_124 = new Trie();
        obj_124->insert("apple");
        bool param124_1 = obj_124->search("apple");
        bool param124_2 = obj_124->startsWith("app");
    }

    { //基本计算器
        string s137 = "(5+(2-3))";
        int res137 = solve(s137);
    }

    { //快速排序
        vector<int> nums140 = {5, 2, 3, 1, 4};
        vector<int> res140 = MySort(nums140);
    }

    return 0;
}