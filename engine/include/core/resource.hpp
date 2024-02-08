#pragma once
#include "engine.hpp"

#include <map>
#include <string>
#include <memory>

template <typename T>
class ResourceAllocator
{
private:
    int currentId;
    std::map<std::string, std::pair<i32, std::shared_ptr<T>>> resources;
public:
    int add(const std::string &filePath);
    void remove(i32 id);
};

