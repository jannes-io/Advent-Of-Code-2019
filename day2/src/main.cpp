#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<int> parseProgram(std::string str)
{
    std::vector<int> program;

    size_t pos(0);
    while ((pos = str.find(',')) != std::string::npos) {
        const auto token = str.substr(0, pos);
        program.push_back(atoi(token.c_str()));
        str.erase(0, pos + 1);
    }
    program.push_back(atoi(str.c_str()));

    return program;
}

void runProgram(std::vector<int> &program)
{
    for (size_t i = 0; program[i] != 99; i += 4)
    {
        switch (program[i]) {
            case 1:
                program[program[i + 3]] = program[program[i + 1]] + program[program[i + 2]];
                break;
            case 2:
                program[program[i + 3]] = program[program[i + 1]] * program[program[i + 2]];
                break;
            default: break;
        }   
    }
}

std::pair<int, int> runUntilFound(std::vector<int> program, int desiredOutput)
{
    for (size_t noun = 0; noun < 100; noun ++) {
        for (size_t verb = 0; verb < 100; verb++) {
            auto newProgram = program;
            newProgram[1] = noun;
            newProgram[2] = verb;

            runProgram(newProgram);
            if (newProgram[0] == desiredOutput) {
                return {newProgram[1], newProgram[2]};
            }
        }
    }
    return {0, 0};
}

void runPartOne(std::vector<int> program)
{
    runProgram(program);
    printf("Part 1: %d\n", program[0]);
}

void runPartTwo(std::vector<int> program)
{
    const auto output = runUntilFound(program, 19690720);
    printf("Part 2: %d\n", 100 * output.first + output.second);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }
    printf("Calculating Day 2!\n");

    std::ifstream   file;
    std::string     line;

    file.open(argv[1]);
    std::getline(file, line);

    auto program = parseProgram(line);
    program[1] = 12;
    program[2] = 2;

    runPartOne(program);
    runPartTwo(program);

    printf("Press any key to close.\n");
    std::cin.get();
    return 0;
}