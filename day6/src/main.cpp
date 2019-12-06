#include "util.hpp"
#include <algorithm>
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

std::string findParent(const Map &map, const std::string &id)
{
    for (const auto &m : map)
        for (const auto &l : m.second)
            if (l == id)
                return m.first;
    return "COM";
}

uint32_t distance(const Map &map, const std::string &firstId, const std::string &secondId)
{
    std::vector<std::string> visited1 = { firstId };
    std::vector<std::string> visited2 = { secondId };
    while (visited1.back() != "COM") {
        const auto parent = findParent(map, visited1.back());
        visited1.push_back(parent);
    }

    while (visited2.back() != "COM") {
        const auto parent = findParent(map, visited2.back());
        for (size_t i = 0; i < visited1.size(); i++) {
            if (parent == visited1[i]) {
                return i + visited2.size() - 2;
            }
        }

        visited2.push_back(parent);
    }

    return 0;
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

    const auto d = distance(map, std::string("YOU"), std::string("SAN"));

    printf("Part 1: %d\n", c);
    printf("Part 1: %d\n", d);

    return 0;
}