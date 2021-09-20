#include <iostream>
#include <map>
#include <vector>
#include <numeric>
#include "defs.h"
#include "factorial.h"
#include "custom_allocator.h"
#include "custom_container.h"

int main(int , char**)
{
    std::vector<int> keys(MAX_ELEMENTS_COUNT, 0);
    std::iota(keys.begin(), keys.end(), 0);

    {
        std::map<int, int> standard_map;

        for(auto&& key : keys)
            standard_map[key] = factorial(key);

        for(auto&& [key, val] : standard_map)
            std::cout << key << " " << val << std::endl;
    }

    {
        std::map<int, int, std::less<int>, lib::custom_allocator<std::pair<const int, int>>> map_with_custom_allocator;

        for(auto&& key : keys)
            map_with_custom_allocator[key] = factorial(key);

        for(auto&& [key, val] : map_with_custom_allocator)
            std::cout << key << " " << val << std::endl;
    }

    {
        lib::custom_container<int> custom_container;
        for(int i = 0; i <= 9; ++i)
            custom_container.push_back(i);
    }

    {
        lib::custom_container<int, lib::custom_allocator<int, 10>> custom_container_with_custom_allocator;
        for(int i = 2; i <= 9; ++i)
            custom_container_with_custom_allocator.push_back(i);

        for(auto& val : custom_container_with_custom_allocator)
            std::cout << val << std::endl;
    }

    return 0;
}