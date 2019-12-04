#include "util.hpp"
#include <vector>
#include <algorithm>

bool isOrdered(uint32_t start)
{
    uint8_t d = UINT8_MAX;
    while (start > 0)
    {
        uint8_t digit = start % 10;
        if (digit > d)
            return false;

        start /= 10;
        d = digit;
    }

    return true;
}

struct Bounds {
    uint32_t lower;
    uint32_t upper;
    Bounds(const std::string &str)
    {
        const auto parts = split(str, "-");
        auto lowest = atoi(parts[0].c_str());
        auto highest = atoi(parts[1].c_str());
        while (!isOrdered(lowest))
            lowest++;
        while (!isOrdered(highest))
            highest--;
        this->lower = lowest;
        this->upper = highest;
    }

    void print()
    {
        printf("Lower bound: %d\n", this->lower);
        printf("Upper bound: %d\n", this->upper);
    }
};

int passwordCount(const Bounds &bounds)
{
    uint32_t count = 0;
    for (uint32_t n = bounds.lower; n <= bounds.upper; n++) {
        if (!isOrdered(n))
            continue;
        count++;
    }
    return count;
}

int main (int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }
    printf("Calculating Day 4!\n");

    const auto file = readFile(argv[1]);
    Bounds input = Bounds(file[0]);

    const auto count = passwordCount(input);
    printf("Part 1: %d\n", count);

    return 0;
}