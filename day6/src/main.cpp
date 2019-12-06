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

uint32_t countLinks(const Map &map, const std::string &id)
{
    const auto it = map.find(id);
    if (it == map.end())
        return 0;

    int c = 0;
    for (const auto &lnk : it->second)
        c += countLinks(map, lnk) + 1;
    return c;
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

    uint32_t c = 0;
    for (const auto &p : map) {
        c += countLinks(map, p.first);
    }

    printf("Part 1: %d\n", c);
    printf("Part 1: %d\n", 0);

    return 0;
}