#include <iostream>
#include <map>
#include <vector>
#include <numeric>
#include "defs.h"
#include "factorial.h"

int main(int , char**)
{
    std::vector<int> keys(MAX_ELEMENTS_COUNT, 0);
    std::iota(keys.begin(), keys.end(), 0);

    std::map<int, int> standard_map;

    for(auto&& key : keys)
        standard_map[key] = factorial(key);

    for(auto&& [key, val] : standard_map)
        std::cout << key << " " << val << std::endl;

    std::map<int, int> map_with_custom_allocator;

    for(auto&& key : keys)
        map_with_custom_allocator[key] = factorial(key);

    for(auto&& [key, val] : map_with_custom_allocator)
        std::cout << key << " " << val << std::endl;

    // Прикладной код должен содержать следующие вызовы:
    // - создание экземпляра std::map<int, int>
    // - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    // - создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10
    // элементами
    // - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    // - вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
    // - создание экземпляра своего контейнера для хранения значений типа int
    // - заполнение 10 элементами от 0 до 9
    // - создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
    // ограниченным 10 элементами
    // - заполнение 10 элементами от 0 до 9
    // - вывод на экран всех значений, хранящихся в контейнере
    return 0;
}