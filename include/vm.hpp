#pragma once

#include <cstdint>

#define STACK_SIZE 100

class VM {
private:
  //
  // variables
  //

  // program counter
  int32_t PC;

  // stack pointer
  int32_t SP;

  // frame pointer
  int32_t FP;

  // stack
  int32_t stack[STACK_SIZE];

  // array that contains the code to execute
  int32_t *program;

  // program array length
  int32_t programLength;

  //
  // private methods
  //

  /**
   * @brief Fetch new instruction from program
   *
   * @return next instruction to be executed by the VM
   *
   * @throws std::runtime_error Thrown if PC exceed program length
   */
  int32_t fetch();

  /**
   * @brief Pop value at the top of the stack
   *
   * @return value at the top of the stack
   *
   * @throws std::runtime_error Thrown if Stack Underflow occurs
   */
  int32_t pop();

  /**
   * @brief Push new value at the top of the stack
   *
   * @param value New value to be pushed on stack
   *
   * @throws std::runtime_error Thrown if Stack Overflow occurs
   */
  void push(int32_t value);

public:
  //
  // constructors
  //

  /**
   * @brief VM constructor function
   *
   * @param pc Start address for code execution
   * @param prog Code to be executed by the VM
   * @param progLength Length of @b prog array
   */
  VM(int32_t pc, int32_t *prog, int32_t progLength);

  //
  // public methods
  //

  /**
   * @brief Start VM execution cycle:
   * - fetch: fetch next instruction from program
   * - decode: decode instruction
   * - execute: execute instruction
   *
   * @throws std::runtime_error Thrown if an invalid opcode is detected by the
   * VM during the execution
   */
  void run();
};
