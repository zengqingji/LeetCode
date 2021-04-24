//LeetCode热题HOT100

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;

//45：跳跃游戏Ⅱ
int jump(vector<int> &nums)
{
    int maxPose = 0, end = 0, res = 0;
    for (int i = 0; i < nums.size() - 1; ++i)
    {
        if (maxPose < i)
        {
            return -1;
        }
        maxPose = max(maxPose, i + nums[i]);
        if (end == i)
        {
            end = maxPose;
            ++res;
        }
    }
    return res;
}

//55：跳跃游戏
bool canJump(vector<int> &nums)
{
    if (nums.empty())
    {
        return false;
    }
    int maxLength = nums[0];
    int length = nums.size();
    for (int i = 1; i <= length - 2; ++i)
    {
        if (maxLength < i)
        {
            return false;
        }
        maxLength = max(maxLength, i + nums[i]);
    }
    return maxLength >= length - 1;
}

//406：根据身高重建队列
bool cmp406(const vector<int> &a, const vector<int> &b)
{
    if (a[0] != b[0])
    {
        return a[0] < b[0];
    }
    else
    {
        return a[1] > b[1];
    }
}
vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
{
    sort(people.begin(), people.end(), cmp406);
    vector<vector<int>> res;
    int length = people.size();
    for (int i = length - 1; i >= 0; --i)
    {
        res.insert(res.begin() + people[i][1], people[i]);
    }
    return res;
}

//621：任务调度器
int leastInterval(vector<char> &tasks, int n)
{
    vector<int> store(26, 0);
    int length = tasks.size();
    for (int i = 0; i < length; ++i)
    {
        ++store[tasks[i] - 'A'];
    }
    int maxValue = 0, maxCount = 0;
    for (int i = 0; i < 26; ++i)
    {
        if (store[i] > maxValue)
        {
            maxValue = store[i];
            maxCount = 1;
        }
        else if (store[i] == maxValue)
        {
            ++maxCount;
        }
    }
    return max(length, (maxValue - 1) * (n + 1) + maxCount);
}

//56：合并区间
bool cmp56(const vector<int> &a, const vector<int> &b)
{
    return a[0] < b[0];
}
vector<vector<int>> merge(vector<vector<int>> &intervals)
{
    vector<vector<int>> res;
    sort(intervals.begin(), intervals.end(), cmp56);
    if (intervals.empty())
    {
        return res;
    }
    int length = intervals.size();
    int begin = intervals[0][0], end = intervals[0][1];
    for (int i = 1; i < length; ++i)
    {
        if (intervals[i][0] <= end)
        {
            end = max(end, intervals[i][1]);
        }
        else
        {
            res.push_back(vector<int>{begin, end});
            begin = intervals[i][0];
            end = intervals[i][1];
        }
    }
    res.push_back(vector<int>{begin, end});
    return res;
}

//57：插入区间
vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
{
    bool flag = false;
    vector<vector<int>> res;
    for (int i = 0; i < intervals.size();)
    {
        if (!flag && intervals[i][0] > newInterval[1])
        {
            res.push_back(newInterval);
            flag = true;
        }
        if (!flag && intervals[i][1] >= newInterval[0])
        {
            int index = i + 1;
            while (index < intervals.size() && intervals[index][0] <= newInterval[1])
            {
                ++index;
            }
            res.push_back({min(intervals[i][0], newInterval[0]), max(intervals[index - 1][1], newInterval[1])});
            i = index;
            flag = true;
        }
        else
        {
            res.push_back(intervals[i]);
            ++i;
        }
    }
    if (!flag)
    {
        res.push_back(newInterval);
    }
    return res;
}

//69：x的平方根
int mySqrt(int x)
{
    if (x <= 1)
    {
        return x;
    }
    int left = 1;
    int right = x;
    int res = 0;
    while (left <= right)
    {
        int mid = ((right - left) >> 1) + left;
        int temp = x / mid;
        if (mid > temp)
        {
            right = mid - 1;
        }
        else if (mid < temp)
        {
            left = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return left - 1;
}

//75：颜色分类
void sortColors(vector<int> &nums)
{
    int length = nums.size();
    if (length <= 0)
    {
        return;
    }
    int left = 0, right = length - 1;
    for (int i = 0; i < length;)
    {
        if (i > left && nums[i] == 0)
        {
            swap(nums[left], nums[i]);
            ++left;
        }
        else if (i < right && nums[i] == 2)
        {
            swap(nums[right], nums[i]);
            --right;
        }
        else
        {
            ++i;
        }
    }
}

//207：课程表(无环图)
bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
{
    unordered_map<int, vector<int>> store;
    unordered_map<int, int> degree;
    int length = prerequisites.size();
    if (!length)
    {
        return true;
    }
    for (int i = 0; i < length; ++i)
    {
        if (store.count(prerequisites[i][0]))
        {
            store[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }
        else
        {
            store[prerequisites[i][0]] = vector<int>{prerequisites[i][1]};
        }
        if (!degree.count(prerequisites[i][0]))
        {
            degree[prerequisites[i][0]] = 0;
        }
        if (degree.count(prerequisites[i][1]))
        {
            ++degree[prerequisites[i][1]];
        }
        else
        {
            degree[prerequisites[i][1]] = 1;
        }
    }
    queue<int> bfs;
    int count = 0;
    for (auto iter = degree.begin(); iter != degree.end(); ++iter)
    {
        if (!iter->second)
        {
            bfs.push(iter->first);
        }
    }
    while (!bfs.empty())
    {
        for (auto iter = store[bfs.front()].begin(); iter != store[bfs.front()].end(); ++iter)
        {
            --degree[*iter];
            if (!degree[*iter])
            {
                bfs.push(*iter);
            }
        }
        ++count;
        bfs.pop();
    }
    return count == degree.size();
}

//399：除法求值
int findf399(vector<int> &f, vector<double> &w, int x)
{
    if (f[x] != x)
    {
        int father = findf399(f, w, f[x]);
        w[x] *= w[f[x]];
        f[x] = father;
    }
    return f[x];
}
void merge399(vector<int> &f, vector<double> &w, int x, int y, double x2y)
{
    int fx = findf399(f, w, x);
    int fy = findf399(f, w, y);
    f[fx] = fy;
    w[fx] = x2y * w[y] / w[x];
}
vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
{
    unordered_map<string, int> store;
    int count = 0;
    for (const auto &e : equations)
    {
        if (!store.count(e[0]))
        {
            store[e[0]] = count++;
        }
        if (!store.count(e[1]))
        {
            store[e[1]] = count++;
        }
    }
    vector<int> father(count, 0);
    for (int i = 0; i < count; ++i)
    {
        father[i] = i;
    }
    vector<double> w(count, 1.0);
    for (int i = 0; i < equations.size(); ++i)
    {
        merge399(father, w, store[equations[i][0]], store[equations[i][1]], values[i]);
    }
    vector<double> res;
    for (const auto &q : queries)
    {
        if (!store.count(q[0]) || !store.count(q[1]))
        {
            res.push_back(-1.0);
            continue;
        }
        else
        {
            int f1 = findf399(father, w, store[q[0]]);
            int f2 = findf399(father, w, store[q[1]]);
            if (f1 != f2)
            {
                res.push_back(-1.0);
            }
            else
            {
                res.push_back(w[store[q[0]]] / w[store[q[1]]]);
            }
        }
    }
    return res;
}

//547：省份数量
int findf547(vector<int> &f, int x)
{
    if (f[x] != x)
    {
        int father = findf547(f, f[x]);
        f[x] = father;
    }
    return f[x];
}
void merge547(vector<int> &f, int x, int y)
{
    int fx = findf547(f, x);
    int fy = findf547(f, y);
    f[fx] = fy;
}
int findCircleNum(vector<vector<int>> &isConnected)
{
    if (isConnected.empty() || isConnected[0].empty() || isConnected.size() != isConnected[0].size())
    {
        return 0;
    }
    int length = isConnected.size();
    vector<int> f(length, 0);
    for (int i = 1; i < length; ++i)
    {
        f[i] = i;
    }
    for (int i = 0; i < length; ++i)
    {
        for (int j = i + 1; j < length; ++j)
        {
            if (isConnected[i][j])
            {
                merge547(f, i, j);
            }
        }
    }
    int res = 0;
    vector<bool> visited(length, false);
    for (int i = 0; i < length; ++i)
    {
        int father = findf547(f, i);
        if (!visited[father])
        {
            visited[father] = true;
            ++res;
        }
    }
    return res;
}

//721：账户合并
int findf721(vector<int> &f, int x)
{
    if (f[x] != x)
    {
        int father = findf721(f, f[x]);
        f[x] = father;
    }
    return f[x];
}
void merge(vector<int> &f, int x, int y)
{
    int fx = findf721(f, x);
    int fy = findf721(f, y);
    f[fx] = fy;
}
vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
{
    vector<vector<string>> res;
    unordered_map<string, int> hashmap;
    unordered_map<string, string> hashname;
    int count = 0;
    for (int i = 0; i < accounts.size(); ++i)
    {
        for (int j = 1; j < accounts[i].size(); ++j)
        {
            if (!hashmap.count(accounts[i][j]))
            {
                hashmap[accounts[i][j]] = count++;
            }
            if (!hashname.count(accounts[i][j]))
            {
                hashname[accounts[i][j]] = accounts[i][0];
            }
        }
    }
    vector<int> f(count, 0);
    for (int i = 1; i < count; ++i)
    {
        f[i] = i;
    }
    for (int i = 0; i < accounts.size(); ++i)
    {
        int temp = accounts[i].size() - 1;
        for (int j = 1; j < temp; ++j)
        {
            merge(f, hashmap[accounts[i][j]], hashmap[accounts[i][temp]]);
        }
    }
    vector<int> visited(count, -1);      //父亲有没有被建立
    vector<bool> visited2(count, false); //自身有没有被访问
    int count2 = 0;
    for (int i = 0; i < accounts.size(); ++i)
    {
        for (int j = 1; j < accounts[i].size(); ++j)
        {
            if (visited2[hashmap[accounts[i][j]]])
            {
                continue;
            }
            visited2[hashmap[accounts[i][j]]] = true;
            int father = findf721(f, hashmap[accounts[i][j]]);
            if (visited[father] == -1)
            {
                visited[father] = count2++;
                res.push_back({hashname[accounts[i][j]], accounts[i][j]});
            }
            else
            {
                res[visited[father]].push_back(accounts[i][j]);
            }
        }
    }
    for (int i = 0; i < res.size(); ++i)
    {
        sort(res[i].begin(), res[i].end());
    }
    return res;
}

//字节3.7：图书放在同一个架子上
int findflib(vector<int> &f, int x)
{
    if (f[x] != x)
    {
        int father = findflib(f, f[x]);
        f[x] = father;
    }
    return f[x];
}
void mergelib(vector<int> &f, int x, int y)
{
    int fx = findflib(f, x);
    int fy = findflib(f, y);
    f[fy] = fx;
}
int searchlib(vector<vector<int>> &v1, vector<vector<int>> &v2)
{
    unordered_map<int, int> map;
    int count = 0;
    for (int i = 0; i < v1.size(); ++i)
    {
        if (!map.count(v1[i][0]))
        {
            map[v1[i][0]] = count++;
        }
        if (!map.count(v1[i][1]))
        {
            map[v1[i][1]] = count++;
        }
    }
    vector<int> f(count, 0);
    for (int i = 1; i < count; ++i)
    {
        f[i] = i;
    }
    for (const auto &v : v1)
    {
        mergelib(f, map[v[0]], map[v[1]]);
    }
    int res = 0;
    for (const auto &v : v2)
    {
        if (!map.count(v[0]) || !map.count(v[1]))
        {
            continue;
        }
        else
        {
            int f1 = findflib(f, map[v[0]]);
            int f2 = findflib(f, map[v[1]]);
            if (f1 != f2)
            {
                ++res;
            }
        }
    }
    return res;
}

//62：不同路径
int uniquePaths(int m, int n)
{
    if (!m || !n)
    {
        return 0;
    }
    vector<int> store(m, 1);
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < m; ++j)
        {
            store[j] += store[j - 1];
        }
    }
    return store[m - 1];
}

//64：最小路径和
int minPathSum(vector<vector<int>> &grid)
{
    if (!grid.size() || !grid[0].size())
    {
        return 0;
    }
    int length1 = grid.size();
    int length2 = grid[0].size();
    vector<int> store(length2, 0);
    store[0] = grid[0][0];
    for (int j = 1; j < length2; ++j)
    {
        store[j] = grid[0][j] + store[j - 1];
    }
    for (int i = 1; i < length1; ++i)
    {
        store[0] += grid[i][0];
        for (int j = 1; j < length2; ++j)
        {
            store[j] = grid[i][j] + min(store[j], store[j - 1]);
        }
    }
    return store[length2 - 1];
}

//72：最小编辑代价(nowcoder-35)
int minDistance(string word1, string word2)
{
    int length1 = word1.size();
    int length2 = word2.size();
    vector<vector<int>> store(length1 + 1, vector<int>(length2 + 1, 0));
    for (int i = 1; i <= length1; ++i)
    {
        store[i][0] = i;
    }
    for (int i = 1; i <= length2; ++i)
    {
        store[0][i] = i;
    }
    for (int i = 1; i <= length1; ++i)
    {
        for (int j = 1; j <= length2; ++j)
        {
            if (word1[i - 1] == word2[j - 1])
            {
                store[i][j] = min(store[i - 1][j - 1], min(store[i - 1][j] + 1, store[i][j - 1] + 1));
            }
            else
            {
                store[i][j] = min(store[i - 1][j - 1] + 1, min(store[i - 1][j] + 1, store[i][j - 1] + 1));
            }
        }
    }
    return store[length1][length2];
}

//221：最大正方形(相邻三数取最小)
int maximalSquare(vector<vector<char>> &matrix)
{
    if (!matrix.size() || !matrix[0].size())
    {
        return 0;
    }
    int length1 = matrix.size();
    int length2 = matrix[0].size();
    int res = 0;
    vector<vector<int>> store(length1, vector<int>(length2, 0));
    for (int i = 0; i < length1; ++i)
    {
        for (int j = 0; j < length2; ++j)
        {
            if (matrix[i][j] == '1')
            {
                if (!i || !j)
                {
                    store[i][j] = 1;
                }
                else
                {
                    store[i][j] = min(store[i - 1][j - 1], min(store[i - 1][j], store[i][j - 1])) + 1;
                }
                res = max(res, store[i][j]);
            }
        }
    }
    return res * res;
}

//279：完全平方数(本质是完全背包)
int numSquares(int n)
{
    vector<int> store(n + 1, n);
    store[0] = 0;
    store[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 1; j * j <= i; ++j)
        {
            store[i] = min(store[i], store[i - j * j] + 1);
        }
    }
    return store[n];
}

//312：戳气球(困难须思考)
int maxCoins(vector<int> &nums)
{
    int length = nums.size();
    vector<vector<int>> store(length + 2, vector<int>(length + 2, 0));
    for (int begin = length - 1; begin >= 0; --begin)
    {
        for (int end = begin + 2; end <= length + 1; ++end)
        {
            for (int index = begin + 1; index <= end - 1; ++index)
            {
                int temp = nums[index - 1];
                if (begin >= 1)
                {
                    temp *= nums[begin - 1];
                }
                if (end <= length)
                {
                    temp *= nums[end - 1];
                }
                store[begin][end] = max(store[begin][end], temp + store[begin][index] + store[index][end]);
            }
        }
    }
    return store[0][length + 1];
}

//338：比特位计数
vector<int> countBits(int num)
{
    vector<int> store(num + 1, 0);
    for (int i = 1; i <= num; ++i)
    {
        store[i] = store[i >> 1] + (i & 1);
    }
    return store;
}

//17：电话号码的字母组合
void dfs(string &digits, int index, vector<string> &res, string &temp)
{
    if (index == digits.size())
    {
        res.push_back(temp);
        return;
    }
    for (int i = 0; i < 4; ++i)
    {
        if (i == 3 && digits[index] >= '2' && digits[index] <= '6')
        {
            continue;
        }
        else if (i == 0 && digits[index] >= '8' && digits[index] <= '9')
        {
            continue;
        }
        temp.push_back(3 * (digits[index] - '2') + i + 'a');
        dfs(digits, index + 1, res, temp);
        temp.pop_back();
    }
    if (digits[index] == '9')
    {
        temp.push_back(25 + 'a');
        dfs(digits, index + 1, res, temp);
        temp.pop_back();
    }
}
vector<string> letterCombinations(string digits)
{
    vector<string> res;
    if (digits.empty())
    {
        return res;
    }
    string temp;
    dfs(digits, 0, res, temp);
    return res;
}

//78：子集
void dfs(vector<int> &nums, int index, vector<vector<int>> &res, vector<int> &temp)
{
    if (index == nums.size())
    {
        res.push_back(temp);
        return;
    }
    dfs(nums, index + 1, res, temp);
    temp.push_back(nums[index]);
    dfs(nums, index + 1, res, temp);
    temp.pop_back();
}
vector<vector<int>> subsets(vector<int> &nums)
{
    vector<vector<int>> res;
    vector<int> temp;
    dfs(nums, 0, res, temp);
    return res;
}

//93：数字字符串转化成IP地址
void dfs(string &s, vector<string> &res, string temp, int begin, int count)
{
    if (count == 4)
    {
        if (begin == s.size())
        {
            res.push_back(temp);
        }
        return;
    }
    else if (begin >= s.size())
    {
        return;
    }
    else if (begin != 0)
    {
        temp.push_back('.');
    }
    if (s[begin] == '0')
    {
        dfs(s, res, temp + '0', begin + 1, count + 1);
    }
    else
    {
        int num1 = s[begin] - '0';
        int num2 = 0, num3 = 0;
        dfs(s, res, temp + to_string(num1), begin + 1, count + 1);
        if (begin <= s.size() - 2)
        {
            num2 = num1 * 10 + s[begin + 1] - '0';
            dfs(s, res, temp + to_string(num2), begin + 2, count + 1);
        }
        if (begin <= s.size() - 3)
        {
            num3 = num2 * 10 + s[begin + 2] - '0';
            if (num3 <= 255)
            {
                dfs(s, res, temp + to_string(num3), begin + 3, count + 1);
            }
        }
    }
}
vector<string> restoreIpAddresses(string s)
{
    vector<string> res;
    string temp;
    dfs(s, res, temp, 0, 0);
    return res;
}

//394：字符串解码
string dfs(string &s, int &index)
{
    int num = 0;
    string res;
    for (; index < s.size(); ++index)
    {
        if (s[index] == '[')
        {
            string letter = dfs(s, ++index);
            if (num)
            {
                while (num--)
                {
                    res.insert(res.size(), letter);
                }
                num = 0;
            }
            else
            {
                res.insert(res.size(), letter);
            }
        }
        else if (s[index] == ']')
        {
            break;
        }
        else if (s[index] >= '0' && s[index] <= '9')
        {
            num = num * 10 + s[index] - '0';
        }
        else
        {
            res.push_back(s[index]);
        }
    }
    return res;
}
string decodeString(string s)
{
    int index = 0;
    return dfs(s, index);
}

//200：岛屿数量(注意char和bool不同)
int numIslands(vector<vector<char>> &grid)
{
    if (!grid.size() || !grid[0].size())
    {
        return 0;
    }
    int length1 = grid.size();
    int length2 = grid[0].size();
    int res = 0;
    for (int i = 0; i < length1; ++i)
    {
        for (int j = 0; j < length2; ++j)
        {
            if (grid[i][j] == '1')
            {
                ++res;
                grid[i][j] = '0';
                queue<vector<int>> store;
                store.push({i, j});
                while (!store.empty())
                {
                    int tempi = store.front()[0];
                    int tempj = store.front()[1];
                    if (tempi > 0 && grid[tempi - 1][tempj] == '1')
                    {
                        grid[tempi - 1][tempj] = '0';
                        store.push({tempi - 1, tempj});
                    }
                    if (tempi < length1 - 1 && grid[tempi + 1][tempj] == '1')
                    {
                        grid[tempi + 1][tempj] = '0';
                        store.push({tempi + 1, tempj});
                    }
                    if (tempj > 0 && grid[tempi][tempj - 1] == '1')
                    {
                        grid[tempi][tempj - 1] = '0';
                        store.push({tempi, tempj - 1});
                    }
                    if (tempj < length2 - 1 && grid[tempi][tempj + 1] == '1')
                    {
                        grid[tempi][tempj + 1] = '0';
                        store.push({tempi, tempj + 1});
                    }
                    store.pop();
                }
            }
        }
    }
    return res;
}

//43：字符串相乘
string multiply(string num1, string num2)
{
    if (num1 == "0" || num2 == "0")
    {
        return "0";
    }
    int length1 = num1.size();
    int length2 = num2.size();
    vector<int> store(length1 + length2, 0);
    for (int i = 0; i < length1; ++i)
    {
        for (int j = 0; j < length2; ++j)
        {
            int temp = (num1[i] - '0') * (num2[j] - '0');
            store[length1 + length2 - 2 - i - j] += temp;
        }
    }
    int up = 0;
    for (int i = 0; i < length1 + length2; ++i)
    {
        store[i] += up;
        up = store[i] / 10;
        store[i] %= 10;
    }
    string res;
    int index = length1 + length2 - 1;
    while (index >= 0 && store[index] == 0)
    {
        --index;
    }
    while (index >= 0)
    {
        res.push_back(store[index] + '0');
        --index;
    }
    return res;
}

//89：格雷编码
vector<int> grayCode(int n)
{
    vector<int> res;
    res.push_back(0);
    for (int i = 0; i < n; ++i)
    {
        int temp = 1 << i;
        int length = res.size();
        for (int j = length - 1; j >= 0; --j)
        {
            res.push_back(temp + res[j]);
        }
    }
    return res;
}

//504：进制转换
string solve(int M, int N)
{
    string res;
    bool flag = true;
    string store[6] = {"A", "B", "C", "D", "E", "F"};
    if (!M)
    {
        return "0";
    }
    else if (M < 0)
    {
        M = -M;
        flag = false;
    }
    while (M)
    {
        int temp = M % N;
        string resTemp = temp < 10 ? to_string(temp) : store[temp - 10];
        res.insert(0, resTemp);
        M /= N;
    }
    if (!flag)
    {
        res.insert(0, "-");
    }
    return res;
}

//31：下一个排列
void nextPermutation(vector<int> &nums)
{
    int length = nums.size();
    int l1 = length - 2, l2 = length - 1;
    while (l1 >= 0 && nums[l1] >= nums[l1 + 1])
    {
        --l1;
    }
    if (l1 >= 0)
    {
        while (l2 > l1 && nums[l2] <= nums[l1])
        {
            --l2;
        }
        swap(nums[l1], nums[l2]);
    }
    for (int i = l1 + 1; i <= (l1 + length - 1) >> 1; ++i)
    {
        swap(nums[i], nums[l1 + length - i]);
    }
    return;
}

//49：字母异位词分组(hash)
vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    unordered_map<string, int> store;
    vector<vector<string>> res;
    int length = strs.size();
    int count = 0;
    for (int i = 0; i < length; ++i)
    {
        string temp = strs[i];
        sort(strs[i].begin(), strs[i].end());
        if (store.count(strs[i]))
        {
            res[store[strs[i]]].push_back(temp);
        }
        else
        {
            store[strs[i]] = count;
            res.resize(count + 1);
            res[count].push_back(temp);
            ++count;
        }
    }
    return res;
}

//287：寻找重复数(原地排序)
int findDuplicate(vector<int> &nums)
{
    int length = nums.size();
    for (int i = 0; i < length; ++i)
    {
        while (i + 1 != nums[i])
        {
            if (nums[i] == nums[nums[i] - 1])
            {
                return nums[i];
            }
            swap(nums[i], nums[nums[i] - 1]);
        }
    }
    return nums[length - 1];
}

//347：前K个高频元素(hash+最大堆)
struct cmp347
{
    bool operator()(const vector<int> &a, const vector<int> &b)
    {
        return a[1] > b[1];
    }
};
vector<int> topKFrequent(vector<int> &nums, int k)
{
    priority_queue<vector<int>, vector<vector<int>>, cmp347> resMax;
    unordered_map<int, int> store;
    vector<int> res;
    int length = nums.size();
    for (int i = 0; i < length; ++i)
    {
        if (store.count(nums[i]))
        {
            ++store[nums[i]];
        }
        else
        {
            store[nums[i]] = 1;
        }
    }
    for (auto iter = store.begin(); iter != store.end(); ++iter)
    {
        vector<int> temp = {iter->first, iter->second};
        if (resMax.size() < k)
        {
            resMax.push(temp);
        }
        else if (temp[1] > resMax.top()[1])
        {
            resMax.pop();
            resMax.push(temp);
        }
    }
    while (!resMax.empty())
    {
        res.push_back(resMax.top()[0]);
        resMax.pop();
    }
    return res;
}

//438：找到字符串中所有字母异位词(hash)
vector<int> findAnagrams(string s, string p)
{
    int slength = s.size();
    int plength = p.size();
    vector<int> res;
    if (slength < plength)
    {
        return res;
    }
    vector<int> store1(26, 0);
    vector<int> store2(26, 0);
    for (int i = 0; i < plength; ++i)
    {
        ++store1[p[i] - 'a'];
        ++store2[s[i] - 'a'];
    }
    for (int j = 0; j < 26; ++j)
    {
        if (store1[j] != store2[j])
        {
            break;
        }
        else if (j == 25)
        {
            res.push_back(0);
        }
    }
    for (int i = 1; i <= slength - plength; ++i)
    {
        --store2[s[i - 1] - 'a'];
        ++store2[s[i + plength - 1] - 'a'];
        for (int j = 0; j < 26; ++j)
        {
            if (store1[j] != store2[j])
            {
                break;
            }
            else if (j == 25)
            {
                res.push_back(i);
            }
        }
    }
    return res;
}

//560：和为K的子数组(hash,前缀和)
int subarraySum(vector<int> &nums, int k)
{
    if (nums.empty())
    {
        return 0;
    }
    int length = nums.size();
    unordered_map<int, int> store;
    int res = 0, temp = 0;
    for (int i = 0; i < length; ++i)
    {
        temp += nums[i];
        if (temp == k)
        {
            ++res;
        }
        if (store.count(temp - k))
        {
            res += store[temp - k];
        }
        if (store.count(temp))
        {
            ++store[temp];
        }
        else
        {
            store[temp] = 1;
        }
    }
    return res;
}

//84：柱状图中最大的矩形
int largestRectangleArea(vector<int> &heights)
{
    stack<int> left;
    int length = heights.size();
    vector<int> storel(length, -1);
    vector<int> storer(length, length);
    for (int i = 0; i < length; ++i)
    {
        if (left.empty() || heights[i] > heights[left.top()])
        {
            storel[i] = left.empty() ? -1 : left.top();
            left.push(i);
        }
        else
        {
            while (!left.empty() && heights[i] <= heights[left.top()])
            {
                storer[left.top()] = i;
                left.pop();
            }
            storel[i] = left.empty() ? -1 : left.top();
            left.push(i);
        }
    }
    int res = 0;
    for (int i = 0; i < length; ++i)
    {
        res = max(res, heights[i] * (storer[i] - storel[i] - 1));
    }
    return res;
}

//85：最大矩形
int maximalRectangle(vector<vector<char>> &matrix)
{
    if (!matrix.size() || !matrix[0].size())
    {
        return 0;
    }
    int length1 = matrix.size();
    int length2 = matrix[0].size();
    vector<vector<int>> store(length1, vector<int>(length2, 0));
    for (int i = 0; i < length1; ++i)
    {
        int count = 0;
        for (int j = 0; j < length2; ++j)
        {
            count = (matrix[i][j] == '0') ? 0 : count + 1;
            store[i][j] = count;
        }
    }
    int res = 0;
    for (int j = 0; j < length2; ++j)
    {
        vector<int> up(length1, -1);
        vector<int> down(length1, length1);
        stack<int> temp;
        for (int i = 0; i < length1; ++i)
        {
            if (temp.empty() || store[i][j] > store[temp.top()][j])
            {
                up[i] = temp.empty() ? -1 : temp.top();
                temp.push(i);
            }
            else
            {
                while (!temp.empty() && store[i][j] <= store[temp.top()][j])
                {
                    down[temp.top()] = i;
                    temp.pop();
                }
                up[i] = temp.empty() ? -1 : temp.top();
                temp.push(i);
            }
        }
        for (int i = 0; i < length1; ++i)
        {
            res = max(res, store[i][j] * (down[i] - up[i] - 1));
        }
    }
    return res;
}

//739：每日温度
vector<int> dailyTemperatures(vector<int> &T)
{
    if (T.empty())
    {
        return T;
    }
    int length = T.size();
    vector<int> res(length, 0);
    stack<int> store;
    for (int i = 0; i < length; ++i)
    {
        if (store.empty() || T[store.top()] >= T[i])
        {
            store.push(i);
        }
        else
        {
            while (!store.empty() && T[store.top()] < T[i])
            {
                res[store.top()] = i - store.top();
                store.pop();
            }
            store.push(i);
        }
    }
    return res;
}

//225：用队列实现栈
class MyStack
{
public:
    MyStack() {}
    void push(int x)
    {
        _queue.push(x);
        int size = _queue.size();
        while (size > 1)
        {
            _queue.push(_queue.front());
            _queue.pop();
            --size;
        }
    }
    int pop()
    {
        int res = _queue.front();
        _queue.pop();
        return res;
    }
    int top() { return _queue.front(); }
    bool empty() { return _queue.empty(); }

private:
    queue<int> _queue;
};

//232：用栈实现队列
class MyQueue
{
public:
    MyQueue() {}
    void push(int x)
    {
        stack<int> temp;
        while (!_stack.empty())
        {
            temp.push(_stack.top());
            _stack.pop();
        }
        _stack.push(x);
        while (!temp.empty())
        {
            _stack.push(temp.top());
            temp.pop();
        }
    }
    int pop()
    {
        int res = _stack.top();
        _stack.pop();
        return res;
    }
    int peek() { return _stack.top(); }
    bool empty() { return _stack.empty(); }

private:
    stack<int> _stack;
};

int main()
{
    { //贪心算法
        vector<int> nums45 = {2, 3, 1, 1, 4};
        int res45 = jump(nums45);

        vector<int> nums55 = {2, 3, 1, 1, 4};
        bool res55 = canJump(nums55);

        vector<vector<int>> nums406 = {{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}};
        vector<vector<int>> res406 = reconstructQueue(nums406);

        vector<char> nums621 = {'A', 'A', 'A', 'B', 'B', 'B'};
        int res621 = leastInterval(nums621, 2);


    }

    { //合并/插入区间
        vector<vector<int>> nums56 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
        vector<vector<int>> res56 = merge(nums56);

        vector<vector<int>> nums57_1 = {{1, 3}, {6, 9}};
        vector<int> nums57_2 = {2, 5};
        vector<vector<int>> res57 = insert(nums57_1, nums57_2);
    }

    { //二分法
        int res69 = mySqrt(4);
    }

    { //双指针
        vector<int> nums75 = {2, 0, 2, 1, 1, 0};
        sortColors(nums75);
    }

    { //拓扑排序、图
        vector<vector<int>> nums207 = {{1, 0}};
        bool res207 = canFinish(2, nums207);
    }

    { //并查集、图
        vector<vector<string>> nums399_1 = {{"a", "b"}, {"b", "c"}};
        vector<double> nums399_2 = {2.0, 3.0};
        vector<vector<string>> nums399_3 = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
        vector<double> res399 = calcEquation(nums399_1, nums399_2, nums399_3);

        vector<vector<int>> matrix547 = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
        int res547 = findCircleNum(matrix547);

        vector<vector<string>> matrix721 = {{"John", "johnsmith@mail.com", "john_newyork@mail.com"},
                                            {"John", "johnsmith@mail.com", "john00@mail.com"},
                                            {"Mary", "mary@mail.com"},
                                            {"John", "johnnybravo@mail.com"}};
        vector<vector<string>> res721 = accountsMerge(matrix721);
    }

    { //动态规划
        int res62 = uniquePaths(3, 7);

        vector<vector<int>> nums64 = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
        int res64 = minPathSum(nums64);

        string s72_1 = "horse";
        string s72_2 = "ros";
        int res72 = minDistance(s72_1, s72_2);

        vector<vector<char>> matrix221 = {{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}};
        int res221 = maximalSquare(matrix221);

        int res279 = numSquares(12);

        vector<int> nums312 = {3, 1, 5, 8};
        int res312 = maxCoins(nums312);

        vector<int> res338 = countBits(2);
    }

    { //深度优先(递归/栈用的少)
        string s17 = "23";
        vector<string> res17 = letterCombinations(s17);

        vector<int> nums78 = {1, 2, 3};
        vector<vector<int>> res78 = subsets(nums78);

        string s93 = "25525511135";
        vector<string> res93 = restoreIpAddresses(s93);

        string s394 = "3[a2[c]]";
        string res394 = decodeString(s394);
    }

    { //广度优先(队列)
        vector<vector<char>> nums200 = {{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}};
        int res200 = numIslands(nums200);
    }

    { //位运算
        string s43_1 = "0";
        string s43_2 = "3";
        string res43 = multiply(s43_1, s43_2);

        vector<int> nums89 = grayCode(2);

        string res504 = solve(-7, 16);
    }

    { //数组技巧
        vector<int> nums31 = {1, 3, 2};
        nextPermutation(nums31);

        vector<string> nums49 = {"eat", "tea", "tan", "ate", "nat", "bat"};
        vector<vector<string>> res49 = groupAnagrams(nums49);

        vector<int> nums287 = {1, 3, 4, 2, 2};
        int res287 = findDuplicate(nums287);

        vector<int> nums347 = {1, 1, 1, 2, 2, 3};
        vector<int> res347 = topKFrequent(nums347, 2);

        string s438_1 = "cbaebabacd";
        string s438_2 = "abc";
        vector<int> res438 = findAnagrams(s438_1, s438_2);

        vector<int> nums560 = {1, 1, 1};
        int res560 = subarraySum(nums560, 2);
    }

    { //单调栈
        vector<int> nums84 = {2, 1, 5, 6, 2, 3};
        int res84 = largestRectangleArea(nums84);

        vector<vector<char>> matrix85 = {{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}};
        int res85 = maximalRectangle(matrix85);

        vector<int> nums739 = {73, 74, 75, 71, 69, 72, 76, 73};
        vector<int> res739 = dailyTemperatures(nums739);
    }

    { //栈与队列
        MyStack *obj_225 = new MyStack();
        obj_225->push(10);
        obj_225->push(8);
        int param225_1 = obj_225->pop();
        int param225_2 = obj_225->top();
        bool param225_3 = obj_225->empty();

        MyQueue *obj232 = new MyQueue();
        obj232->push(10);
        obj232->push(8);
        int param232_1 = obj232->pop();
        int param232_2 = obj232->peek();
        bool param232_3 = obj232->empty();
    }

    return 0;
}