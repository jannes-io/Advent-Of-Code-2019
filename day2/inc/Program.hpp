#pragma once

#include <vector>

struct Opcode {
    int instruction;
    int modes[3];

    Opcode(int n)
    {
        int opcode[5] = {};
        size_t i = 5;
        while (n > 0)
        {
            int digit = n % 10;
            n /= 10;
            opcode[--i] = digit;
        }

        this->modes[2] = opcode[0];
        this->modes[1] = opcode[1];
        this->modes[0] = opcode[2];
        this->instruction = opcode[3] * 10 + opcode[4];
    }
};

struct Program {
    std::vector<int> initial;
    std::vector<int> state;

    Program(const std::vector<int> &p);

    int run();
    int* getArgs(const Opcode &opcode, size_t pointer, size_t argc);
    void reset();
};

Program::Program(const std::vector<int> &p) : initial(p), state(p) {}

int Program::run()
{
    auto &p = this->state;
    size_t i = 0;

    while (p[i] != 99)
    {
        const auto oc = Opcode(p[i]);
        switch (p[i]) {
            case 1: *getArgs(oc, i, 3) = *getArgs(oc, i, 1) + *getArgs(oc, i, 2); i += 4; break;
            case 2: *getArgs(oc, i, 3) = *getArgs(oc, i, 1) * *getArgs(oc, i, 2); i += 4; break;
            case 3: *getArgs(oc, i, 1) = *getArgs(oc, i, 2)                     ; i += 3; break;
            case 4: return *getArgs(oc, i, 1); break;
            default: break;
        }
    }
    return p[0];
}

int* Program::getArgs(const Opcode &opcode, size_t pointer, size_t argc)
{
    auto &p = this->state;
    return opcode.modes[argc - 1] == 0
        ? &p[p[pointer + argc]]
        : &p[pointer + argc];
}

void Program::reset()
{
    this->state = this->initial;
}
