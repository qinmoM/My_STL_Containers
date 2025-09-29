#pragma once

#include "md5.h"
#include <string>
#include <set>
#include <list>
#include <stdexcept>

using uint = unsigned int;

class PhysicalHost;

class VirtualHost
{
public:
    VirtualHost(const std::string& ip, PhysicalHost* pHost)
        : ip_(ip)
        , pHost_(pHost)
    {
        md5_ = md5(ip.c_str());
    }

    const PhysicalHost* getPhysical() const
    {
        return pHost_;
    }

    uint getMD5() const
    {
        return md5_;
    }

    std::string getIP() const
    {
        return ip_;
    }

    bool operator==(const VirtualHost& other) const
    {
        return md5_ == other.md5_;
    }

    bool operator!=(const VirtualHost& other) const
    {
        return md5_ != other.md5_;
    }

    bool operator<(const VirtualHost& other) const
    {
        return md5_ < other.md5_;
    }

    bool operator>(const VirtualHost& other) const
    {
        return md5_ > other.md5_;
    }

protected:
    std::string ip_;
    uint md5_;
    PhysicalHost* pHost_;

};

class PhysicalHost
{
public:
    PhysicalHost(const std::string& ip, int numVirtual)
        : ip_(ip)
    {
        for (int i = 0; i < numVirtual; ++i)
        {
            vHosts_.emplace_back(ip + "#" + std::to_string(i), this);
        }
    }

    const std::list<VirtualHost>& getHost() const
    {
        return vHosts_;
    }

    std::string getIP() const
    {
        return ip_;
    }

    bool operator==(const PhysicalHost& other) const
    {
        return ip_ == other.ip_;
    }

    bool operator!=(const PhysicalHost& other) const
    {
        return ip_ != other.ip_;
    }

protected:
    std::string ip_;
    std::list<VirtualHost> vHosts_;

};

class ConsistentHash
{
public:
    ConsistentHash() = default;

    void addHost(const PhysicalHost& pHost)
    {
        for (const std::list<VirtualHost>::value_type& vHost : pHost.getHost())
        {
            vHosts_.insert(vHost);
        }
    }

    void removeHost(const PhysicalHost& pHost)
    {
        for (const std::list<VirtualHost>::value_type& vHost : pHost.getHost())
        {
            vHosts_.erase(vHost);
        }
    }

    std::string getHost(const std::string& clientIP) const
    {
        if (vHosts_.empty())
        {
            throw std::runtime_error("no server available!");
        }
        uint key_md5 = md5(clientIP.c_str());
        for (const VirtualHost& vHost : vHosts_)
        {
            if (key_md5 <= vHost.getMD5())
            {
                return vHost.getPhysical()->getIP();
            }
        }
        return vHosts_.begin()->getPhysical()->getIP();
    }

protected:
    std::set<VirtualHost> vHosts_;

};
