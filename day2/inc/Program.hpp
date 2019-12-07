#pragma once

#include <vector>
#include <iostream>

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
    std::vector<int> output;
    size_t i;
    bool done;

    Program(const std::vector<int> &p)
        : initial(p), state(p), i(0), done(false) {}
    Program(const Program &p)
        : initial(p.initial), state(p.state), i(p.i), done(p.done) {}

    void run();
    void input(int val);
    int getArg(const Opcode &opcode, size_t pointer, size_t argc);
    void reset();
};

void Program::run()
{
    auto &p = this->state;
    while (!this->done)
    {
        const auto oc = Opcode(p[i]);
        if (oc.instruction == 99) {
            this->done = true;
            return;
        }

        switch (oc.instruction) {
            case 1: p[p[i + 3]] = getArg(oc, i, 1) + getArg(oc, i, 2)         ; i += 4; break; // Add
            case 2: p[p[i + 3]] = getArg(oc, i, 1) * getArg(oc, i, 2)         ; i += 4; break; // Mul
            case 3: return;
            case 4: this->output.push_back(getArg(oc, i, 1))                  ; i += 2; break; // Out
            case 5: if (getArg(oc, i, 1) != 0) i = getArg(oc, i, 2); else       i += 3; break; // Jit
            case 6: if (getArg(oc, i, 1) == 0) i = getArg(oc, i, 2); else       i += 3; break; // Jif
            case 7: p[p[i + 3]] = getArg(oc, i, 1) < getArg(oc, i, 2) ? 1 : 0 ; i += 4; break; // <
            case 8: p[p[i + 3]] = getArg(oc, i, 1) == getArg(oc, i, 2) ? 1 : 0; i += 4; break; // eq
            default: printf("Invalid opcode! %d\n", p[i]);exit(1)                     ; break; // ERR
        }
    }
}

void Program::input(int val)
{
    auto &p = this->state;
    p[p[i + 1]] = val;
    this->i += 2;
    this->run();
}

int Program::getArg(const Opcode &opcode, size_t pointer, size_t argc)
{
    auto &p = this->state;
    return opcode.modes[argc - 1] == 0
        ? p[p[pointer + argc]]
        : p[pointer + argc];
}

void Program::reset()
{
    this->state = this->initial;
    this->i = 0; 
    this->done = false;
    this->output.clear();
}
