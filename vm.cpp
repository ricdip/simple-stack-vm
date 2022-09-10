#include "include/vm.hpp"
#include "include/is.hpp"

#include <cstdint>
#include <iostream>
#include <stdexcept>

VM::VM(int32_t pc, int32_t *prog, int32_t progLength)
    : PC(pc), SP(0), FP(0), program(prog), programLength(progLength) {}

int32_t VM::fetch() {
  if (PC > programLength) {
    throw std::runtime_error("Program Counter exceeded program length");
  }
  return program[PC++];
}

int32_t VM::pop() {
  if (SP - 1 < 0) {
    throw std::runtime_error("Stack Underflow");
  }
  return stack[--SP];
}

void VM::push(int32_t value) {
  if (SP > STACK_SIZE) {
    throw std::runtime_error("Stack Overflow");
  }
  stack[SP++] = value;
}

void VM::run() {
  do {
    int32_t opcode = fetch();
    int32_t value, op1, op2, addr, argc;

    switch (opcode) {
    case PUSH:
      value = fetch();

      push(value);

      break;

    case POP:
      pop();

      break;

    case DUP:
      value = pop();

      push(value);
      push(value);

      break;

    case ADD:
      op1 = pop();
      op2 = pop();

      value = op2 + op1;

      push(value);

      break;

    case SUBT:
      op1 = pop();
      op2 = pop();

      value = op2 - op1;

      push(value);

      break;

    case MULT:
      op1 = pop();
      op2 = pop();

      value = op2 * op1;

      push(value);

      break;

    case EQ:
      op1 = pop();
      op2 = pop();

      value = op2 == op1;

      push(value);

      break;

    case NEQ:
      op1 = pop();
      op2 = pop();

      value = op2 != op1;

      push(value);

      break;

    case GT:
      op1 = pop();
      op2 = pop();

      value = op2 > op1;

      push(value);

      break;

    case LT:
      op1 = pop();
      op2 = pop();

      value = op2 < op1;

      push(value);

      break;

    case GTE:
      op1 = pop();
      op2 = pop();

      value = op2 >= op1;

      push(value);

      break;

    case LTE:
      op1 = pop();
      op2 = pop();

      value = op2 <= op1;

      push(value);

      break;

    case AND:
      op1 = pop();
      op2 = pop();

      value = op2 && op1;

      push(value);

      break;

    case OR:
      op1 = pop();
      op2 = pop();

      value = op2 || op1;

      push(value);

      break;

    case NOT:
      op1 = pop();

      value = !op1;

      push(value);

      break;

    case JMP:
      addr = fetch();

      PC = addr;

      break;

    case JMPT:
      addr = fetch();
      value = pop();

      if (value) {
        PC = addr;
      }

      break;

    case JMPF:
      addr = fetch();
      value = pop();

      if (!value) {
        PC = addr;
      }

      break;

    // CALL func #arg
    case CALL:
      // function address
      addr = fetch();
      // number of function args
      argc = fetch();

      // push current program counter on stack
      push(PC);

      // push argc on stack
      push(argc);

      // push new stack frame address on stack
      push(FP);

      // most recent frame pointer starts from current stack pointer (new frame
      // on stack)
      FP = SP;

      // push function args on new stack frame
      for (int32_t c = 0; c < argc; c++) {
        // current arg in in position SP - 1 - argc + c:
        // SP - 1 points to saved FP
        // SP - 2 points to saved argc
        // SP - 3 points to saved PC
        // SP - 3 - argc points to first function arg pushed on stack
        // SP - 3 - argc + c points to current function arg to be pushed on
        // stack frame
        value = stack[SP - 3 - argc + c];
        // push current arg on stack frame
        push(value);
      }

      // PC set to function address
      PC = addr;

      break;

    case RET:
      // function return value
      value = pop();

      // stack pointer set to start stack frame address
      SP = FP;

      // current stack frame start address
      FP = pop();

      // number of function args
      argc = pop();

      // pre-function call PC
      addr = pop();

      // pop function call args from stack
      for (int32_t c = 1; c <= argc; c++) {
        pop();
      }

      // push function return value on stack
      push(value);

      // current PC set to pre-function call PC
      PC = addr;

      break;

    case POPANDPRINT:
      value = pop();
      std::cout << "PRINT: " << value << std::endl;

      break;

    case HALT:
      std::cout << "HALT" << std::endl;
      return;

    default:
      throw std::runtime_error("Invalid Opcode");
    }
  } while (true);
}