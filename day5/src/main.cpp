#include "util.hpp"
#include "Program.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }
    printf("Calculating Day 5\n");

    const auto file = readFile(argv[1]);
    std::vector<int> instructions;
    for (const auto &el : split(file.front(), ","))
        instructions.push_back(atoi(el.c_str()));


    auto program = Program(instructions);

    printf("Part 1:\n");
    program.input = 1;
    program.run();
    printf("----------\n");
    
    program.reset();

    printf("Part 2:\n");
    program.input = 5;
    program.run();
    printf("----------\n");

    return 0;
}