#pragma once
#include <memory>
#include <string>
#include <map>

typedef std::string Path;

class Resource {
public:
    Resource(Path const& path) {
    }
};

class ResourceCache {
    std::map<std::string, Path> catalog;
    std::map<std::string, std::shared_ptr<Resource>> cache;
public:
    template<typename T>
    std::shared_ptr<T> getResource(std::string const& name) {

    }
};
