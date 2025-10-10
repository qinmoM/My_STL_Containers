#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

class DSU
{
public:
    DSU(std::vector<std::vector<int>>& v)
    {
        int max_ = 0;
        for (std::vector<int>& vec : v)
        {
            max_ = std::max(max_, *std::max_element(vec.begin(), vec.end()));
        }
        parent.assign(max_ + 1, -1);
        int connect = -1;
        for (std::vector<int>& vec : v)
        {
            add(vec[0]);
            for (int i = 1; i < vec.size(); ++i)
            {
                if (find(vec[i]) != -1)
                {
                    connect = vec[i];
                }
                add(vec[i], vec[0]);
            }
            if (connect != -1)
            {
                merge(vec[0], connect);
                connect = -1;
            }
        }
    }

    int find(int x)
    {
        if (x >= parent.size() || parent[x] == -1)
        {
            return -1;
        }

        if (parent[x] == x)
        {
            return x;
        }
        else
        {
            return parent[x] = find(parent[x]);
        }
    }

    void merge(int x, int y)
    {
        int px = find(x);
        int py = find(y);
        if (px != py)
        {
            if (count[px] < count[py])
            {
                parent[px] = py;
                count[py] += count[px];
                count.erase(count.find(px));
            }
            else
            {
                parent[py] = px;
                count[px] += count[py];
                count.erase(count.find(py));
            }
        }
    }

    bool add(int x, int target = -1)
    {
        if (find(x) != -1)
        {
            return false;
        }

        int pt = find(target);
        if (pt == -1)
        {
            parent[x] = x;
            count[x] = 1;
        }
        else
        {
            count[pt] += 1;
            if (x >= parent.size())
            {
                parent.resize(x + 1, -1);
                parent[x] = pt;
            }
            else
            {
                parent[x] = pt;
            }
        }
        return true;
    }

private:
    std::vector<int> parent;
    std::unordered_map<int, int> count;

};
