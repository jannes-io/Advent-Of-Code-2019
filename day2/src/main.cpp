#include <iostream>
#include <vector>
#include "util.hpp"

void runProgram(std::vector<int> &p)
{
    for (size_t i = 0; p[i] != 99; i += 4)
    {
        switch (p[i]) {
            case 1: p[p[i + 3]] = p[p[i + 1]] + p[p[i + 2]]; break;
            case 2: p[p[i + 3]] = p[p[i + 1]] * p[p[i + 2]]; break;
            default: break;
        }
    }
}

int runUntilFound(std::vector<int> program, int desiredOutput)
{
    for (size_t noun = 0; noun < 100; noun++) {
        for (size_t verb = 0; verb < 100; verb++) {
            auto newProgram = program;
            newProgram[1] = noun;
            newProgram[2] = verb;

            runProgram(newProgram);
            if (newProgram[0] == desiredOutput) {
                return 100 * newProgram[1] + newProgram[2];
            }
        }
    }
    return 0;
}

void runPartOne(std::vector<int> program)
{
    program[1] = 12;
    program[2] = 2;
    runProgram(program);
    printf("Part 1: %d\n", program[0]);
}

void runPartTwo(std::vector<int> program)
{
    const auto output = runUntilFound(program, 19690720);
    printf("Part 2: %d\n", output);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }
    printf("Calculating Day 2!\n");

    const auto file = readFile(argv[1]);
    std::vector<int> program;
    for (const auto &el : split(file.front(), ","))
        program.push_back(atoi(el.c_str()));

    runPartOne(program);
    runPartTwo(program);
    return 0;
}