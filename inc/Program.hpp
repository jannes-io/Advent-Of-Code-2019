#pragma once

#include <vector>
#include <iostream>
#include <stdint.h>

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
    std::vector<int64_t> initial;
    std::vector<int64_t> state;
    std::vector<int64_t> output;

    size_t  i;
    bool    done;
    int     relativeBase;

    Program(const std::vector<int64_t> &p)
        : initial(p), state(p), i(0), done(false), relativeBase(0) {}

    void run();
    void input(int val);
    void reset();

    // Instruction set
    void add(const Opcode &oc);
    void mul(const Opcode &oc);
    void out(const Opcode &oc);
    void jit(const Opcode &oc);
    void jif(const Opcode &oc);
    void lt (const Opcode &oc);
    void eq (const Opcode &oc);
    void rel(const Opcode &oc);
    void hlt();

    int64_t get(size_t loc);
    void    set(const Opcode &oc, size_t offset, int64_t val);

    int64_t getArg(const Opcode &opcode, size_t offset);
};

void Program::run()
{
    auto &p = this->state;
    while (!this->done)
    {
        const auto oc = Opcode(p[i]);
        switch (oc.instruction) {
            case 1 : add(oc); break;
            case 2 : mul(oc); break;
            case 3 : return;
            case 4 : out(oc); break;
            case 5 : jit(oc); break;
            case 6 : jif(oc); break;
            case 7 : lt (oc); break;
            case 8 : eq (oc); break;
            case 9 : rel(oc); break;
            case 99: hlt(  ); return;
            default:
                std::cout << "Unknown opcode: " << p[1] << std::endl;
                exit(1);
                break;
        }
    }
}

void Program::input(int val)
{
    if (this->done) {
        return;
    }
    const auto oc = Opcode(this->state[i]);
    set(oc, 1, val);
    this->i += 2;
    this->run();
}

void Program::add(const Opcode &oc)
{
    const auto val = getArg(oc, 1) + getArg(oc, 2);
    set(oc, 3, val);
    this->i += 4;
}

void Program::mul(const Opcode &oc)
{
    const auto val = getArg(oc, 1) * getArg(oc, 2);
    set(oc, 3, val);
    this->i += 4;
}

void Program::out(const Opcode &oc)
{
    this->output.push_back(getArg(oc, 1));
    this->i += 2;
}

void Program::jit(const Opcode &oc)
{
    if (getArg(oc, 1) != 0)
        this->i = getArg(oc, 2);
    else
        this->i += 3;
}

void Program::jif(const Opcode &oc)
{
    if (getArg(oc, 1) == 0)
        this->i = getArg(oc, 2);
    else
        this->i += 3;
}

void Program::lt(const Opcode &oc)
{
    const int64_t val = getArg(oc, 1) < getArg(oc, 2);
    set(oc, 3, val);
    this->i += 4;
}

void Program::eq(const Opcode &oc)
{
    const int64_t val = getArg(oc, 1) == getArg(oc, 2);
    set(oc, 3, val);
    this->i += 4;
}

void Program::rel(const Opcode &oc)
{
    this->relativeBase += getArg(oc, 1);
    this->i += 2;
}

void Program::hlt()
{
    this->done = true;
}

int64_t Program::get(size_t loc)
{
    if (loc >= this->state.size()) {
        this->state.resize(loc + 1, 0);
    }
    return this->state[loc];
}

void Program::set(const Opcode &oc, size_t offset, int64_t val)
{
    size_t loc;

    switch(oc.modes[offset - 1]) {
        case 0:
            loc = get(this->i + offset);
            break;
        case 2:
            loc = get(this->i + offset) + this->relativeBase;
            break;
        default:
            std::cout << "Invalid insert mode" << std::endl;
            exit(1);
    }
    if (loc >= this->state.size()) {
        this->state.resize(loc + 1, 0);
    }
    this->state[loc] = val;
}

int64_t Program::getArg(const Opcode &opcode, size_t offset)
{
    const auto loc = this->i + offset;

    switch(opcode.modes[offset - 1]) {
        case 0: return get(get(loc));                     // Position mode
        case 1: return get(loc);                          // Immidiate mode
        case 2: return get(get(loc) + this->relativeBase);// Relative mode
        default: return 0;
    }
}

void Program::reset()
{
    this->state = this->initial;
    this->output.clear();
    this->i = 0;
    this->done = false;
    this->relativeBase = 0;
}
