#include "util.hpp"
#include <algorithm>
#include <unordered_map>

bool isOrdered(uint32_t n)
{
    uint8_t d = UINT8_MAX;
    while (n > 0)
    {
        uint8_t digit = n % 10;
        if (digit > d) return false;
        n /= 10;
        d = digit;
    }

    return true;
}

bool hasDouble(uint32_t n)
{
    uint8_t d = UINT8_MAX;
    while (n > 0)
    {
        uint8_t digit = n % 10;
        if (digit == d) return true;
        n /= 10;
        d = digit;
    }
    return false;
}

bool hasDoubleGroup(uint32_t n)
{
    uint8_t ns[10] = {};
    while (n > 0)
    {
        uint8_t digit = n % 10;
        n /= 10;
        ns[digit]++;
    }

    for (const auto &count : ns) {
        if (count == 2)
            return true;
    }
    return false;
}

struct Bounds {
    uint32_t lower;
    uint32_t upper;
    Bounds(const std::string &str)
    {
        const auto parts = split(str, "-");
        this->lower = atoi(parts[0].c_str());
        this->upper = atoi(parts[1].c_str());
    }
};

int main (int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }
    printf("Calculating Day 4!\n");

    const auto file = readFile(argv[1]);
    Bounds bounds = Bounds(file[0]);
    
    uint32_t count1 = 0;
    uint32_t count2 = 0;
    for (uint32_t n = bounds.lower; n <= bounds.upper; n++) {
        if (!isOrdered(n)) continue;
        if (!hasDouble(n)) continue;
        count1++;
        if (hasDoubleGroup(n)) count2++;
    }
    printf("Part 1: %d\n", count1);
    printf("Part 2: %d\n", count2);

    return 0;
}