#include "util.hpp"
#include "Program.hpp"
#include <iostream>
#include <vector>

int64_t runUntilFound(Program &program, int desiredOutput)
{
    for (size_t noun = 0; noun < 100; noun++) {
        for (size_t verb = 0; verb < 100; verb++) {
            program.reset();
            program.state[1] = noun;
            program.state[2] = verb;

            program.run();
            auto output = program.state[0];
            if (output == desiredOutput) {
                return 100 * program.state[1] + program.state[2];
            }
        }
    }
    return 0;
}

void runPartOne(Program program)
{
    program.state[1] = 12;
    program.state[2] = 2;
    program.run();
    std::cout << "Part 1: " << program.state[0] << std::endl;
}

void runPartTwo(Program program)
{
    const auto output = runUntilFound(program, 19690720);
    std::cout << "Part 2: " << output << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }
    printf("Calculating Day 2!\n");

    const auto file = readFile(argv[1]);
    std::vector<int64_t> instructions;
    for (const auto &el : split(file.front(), ","))
        instructions.push_back(atoll(el.c_str()));

    auto program = Program(instructions);

    runPartOne(program);
    runPartTwo(program);
    return 0;
}