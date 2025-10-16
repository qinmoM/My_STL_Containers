#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <set>
#include <memory>
#include "DSU.h"

class Graph
{
public:
    struct Vertex
    {
        Vertex(const std::string& name)
            : name(name)
        { }

        std::string name;
        std::list<Vertex*> out;
        std::list<Vertex*> in;
    };

public:
    Graph() = default;

    ~Graph() = default;

public:
    void add(const std::string& name)
    {
        if (dict.find(name) == dict.end())
        {
            dict[name] = std::make_unique<Vertex>(name);
        }
    }

    bool addEdge(const std::string& from, const std::string& to)
    {
        std::unordered_map<std::string, std::unique_ptr<Vertex>>::iterator itF = dict.find(from);
        std::unordered_map<std::string, std::unique_ptr<Vertex>>::iterator itT = dict.find(to);
        if (itF == dict.end() || itT == dict.end())
        {
            return false;
        }

        itF->second->out.push_back(itT->second.get());
        itT->second->in.push_back(itF->second.get());
        return true;
    }

    void removeEdge(const std::string& from, const std::string& to)
    {
        std::unordered_map<std::string, std::unique_ptr<Vertex>>::iterator itF = dict.find(from);
        std::unordered_map<std::string, std::unique_ptr<Vertex>>::iterator itT = dict.find(to);
        if (itF == dict.end() || itT == dict.end())
        {
            return;
        }

        itF->second->out.remove(itT->second.get());
        itT->second->in.remove(itF->second.get());
    }

    template<typename Func>
    void dfs(const std::string& start, Func& func)
    {
        std::unordered_map<std::string, std::unique_ptr<Vertex>>::iterator it = dict.find(start);
        if (it == dict.end())
        {
            return;
        }

        std::unordered_set<Vertex*> visited;
        dfs(it->second.get(), func, visited);
    }

    template<typename Func>
    void bfs(const std::string& start, Func& func)
    {
        std::unordered_map<std::string, std::unique_ptr<Vertex>>::iterator it = dict.find(start);
        if (it == dict.end())
        {
            return;
        }

        std::queue<Vertex*> queue;
        std::unordered_set<Vertex*> visited;
        queue.push(it->second.get());
        visited.insert(it->second.get());
        while (!queue.empty())
        {
            Vertex* v = queue.front();
            queue.pop();
            func(v->name);
            for (Vertex* ver : v->out)
            {
                if (visited.find(ver) == visited.end())
                {
                    queue.push(ver);
                    visited.insert(ver);
                }
            }
        }
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Vertex>> dict;

private:
    template<typename Func>
    void dfs(Vertex* v, Func& func, std::unordered_set<Vertex*>& visited)
    {
        func(v->name);
        visited.insert(v);
        for (Vertex* ver : v->out)
        {
            if (visited.find(ver) == visited.end())
            {
                dfs(ver, func, visited);
            }
        }
    }

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

    constexpr static int INF = static_cast<int>((~0U) >> 1);

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



// Dijkstra algorithm
// Floyd algorithm
class GraphMatrix
{
public:
    constexpr static int INF = static_cast<int>((~0U) >> 1);

    using pair_II = std::pair<int, int>;

public:
    GraphMatrix(std::vector<std::vector<int>>& matrix)
        : matrix_(matrix)
    { }

    ~GraphMatrix() = default;

public:
    std::vector<pair_II> dijkstra(const int start)
    {
        std::vector<pair_II> S;
        std::multiset<std::pair<int, int>> U;
        for (int i = 0; i < matrix_.size(); ++i)
        {
            U.emplace(matrix_[start][i], i);
        }

        while (!U.empty())
        {
            std::pair<int, int> u = *(U.begin());
            U.erase(U.begin());
            if (u.first == INF)
            {
                break;
            }
            S.emplace_back(u.second, u.first);
            for (std::set<pair_II>::iterator it = U.begin(); it != U.end(); )
            {
                int temp = 0;
                if (matrix_[u.second][it->second] != INF && ((temp = matrix_[u.second][it->second] + u.first) < it->first))
                {
                    int index = it->second;
                    it = U.erase(it);
                    U.emplace(temp, index);
                }
                else
                {
                    ++it;
                }
            }
        }
        return S;
    }

protected:
    std::vector<std::vector<int>> matrix_;

};