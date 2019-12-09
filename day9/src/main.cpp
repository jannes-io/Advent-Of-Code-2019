#include "util.hpp"
#include "Program.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }
    printf("Calculating Day 9\n");

    const auto file = readFile(argv[1]);
    std::vector<long long> instructions;
    for (const auto &el : split(file.front(), ","))
        instructions.push_back(atoll(el.c_str()));

    auto program = Program(instructions);
    //for (const auto &out : program.state)
    //    printf("%lld,", out);

    program.run();
    program.input(1);
    for (const auto &out : program.output)
        printf("%lld,", out);

    return 0;
}