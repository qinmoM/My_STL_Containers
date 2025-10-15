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
            if (x >= parent.size())
            {
                parent.resize(x + 1, -1);
            }
            parent[x] = x;
            count[x] = 1;
        }
        else
        {
            count[pt] += 1;
            if (x >= parent.size())
            {
                parent.resize(x + 1, -1);
            }
            parent[x] = pt;
        }
        return true;
    }

private:
    std::vector<int> parent;
    std::unordered_map<int, int> count;

};



// Kruskal's algorithm
class GraphEdge
{
public:
    struct Edge
    {
        Edge(const int from, const int to, const int weight)
            : from(from), to(to), weight(weight)
        { }

        bool operator<(const Edge& other) const
        {
            return weight < other.weight;
        }

        int from;
        int to;
        int weight;
    };

public:
    GraphEdge() = default;

    ~GraphEdge() = default;

public:
    void addEdge(const int from, const int to, const int weight)
    {
        edges_.emplace_back(from, to, weight);
    }

    std::vector<Edge> kruskal()
    {
        std::sort(edges_.begin(), edges_.end());
        std::vector<std::vector<int>> temp(1, { edges_[0].from, edges_[0].to });
        DSU dsu(temp);
        std::vector<Edge> result(1, edges_[0]);
        for (int i = 1; i < edges_.size(); ++i)
        {
            int from = edges_[i].from;
            int to = edges_[i].to;
            if (dsu.find(from) == -1 && dsu.find(to) == -1)
            {
                dsu.add(from);
                dsu.add(to);
                dsu.merge(from, to);
            }
            else if (dsu.find(from) != -1 && dsu.find(to) != -1)
            {
                if (dsu.find(from) == dsu.find(to))
                {
                    continue;
                }
                dsu.merge(from, to);
            }
            else if (dsu.find(from) != -1)
            {
                dsu.add(to, from);
            }
            else
            {
                dsu.add(from, to);
            }
            result.emplace_back(from, to, edges_[i].weight);
        }
        return result;
    }

protected:
    std::vector<Edge> edges_;

};
