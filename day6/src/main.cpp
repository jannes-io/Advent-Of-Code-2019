#include "util.hpp"
#include <unordered_map>

typedef std::unordered_map<std::string, std::vector<std::string>> Map;

Map createLinks(std::vector<std::string> links)
{
    Map map;
    for (const auto &str: links) {
        const auto ids = split(str, ")");

        auto lnk = map.find(ids[0]);
        if (lnk == map.end())
            map.insert({ ids[0], { ids[1] } });
        else
            lnk->second.push_back(ids[1]);
    }
    return map;
}

uint32_t countLinks(Map &map, std::string &firstId)
{
    int c = 0;
    for (const auto &lnk : map[firstId]) {
        
    }
}

int main (int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }
    printf("Calculating Day 5\n");

    const auto input = readFile(argv[1]);
    const auto map = createLinks(input);
}