#pragma once

#include <vector>

struct Program {
    std::vector<int> initial;
    std::vector<int> state;

    Program(const std::vector<int> &p);

    int run();
    void reset();
};

Program::Program(const std::vector<int> &p) : initial(p), state(p) {}

int Program::run()
{
    auto &p = this->state;

    for (size_t i = 0; p[i] != 99; i += 4)
    {
        switch (p[i]) {
            case 1: p[p[i + 3]] = p[p[i + 1]] + p[p[i + 2]]; break;
            case 2: p[p[i + 3]] = p[p[i + 1]] * p[p[i + 2]]; break;
            default: break;
        }
    }
    return p[0];
}

void Program::reset()
{
    this->state = this->initial;
}
