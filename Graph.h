#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <memory>

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
