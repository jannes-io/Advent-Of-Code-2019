#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int calcFuel(const int mass) 
{
    return mass / 3 - 2;
}

int calcFuelR(const int mass)
{
    const auto fuel = calcFuel(mass);
    return fuel <= 0 ? 0 : fuel + calcFuelR(fuel);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }

    printf("Calculating Day 1!\n");

    std::vector<int>    input;
    std::ifstream       file;
    std::string         line;

    file.open(argv[1]);
    while (std::getline(file, line)) {
        input.push_back(atoi(line.c_str()));
    }
    file.close();

    int p1fuel = 0;
    int p2fuel = 0;
    for (const auto &mass : input) {
        p1fuel += calcFuel(mass);
        p2fuel += calcFuelR(mass);
    }
    printf("Part 1: %d\n", p1fuel);
    printf("Part 2: %d\n", p2fuel);
    printf("Press any key to close.\n");
    std::cin.get();
    return 0;
}