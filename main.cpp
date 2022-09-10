#include "include/is.hpp"
#include "include/vm.hpp"
#include <cstdint>

int main(void) {
  // clang-format off
  /*int32_t testprog[] = {
    PUSH, 2,
    PUSH, 3,
    ADD,
    // on stack: 5
    PUSH, 2,
    // on stack 5, 2
    // call func: addr 13
    CALL, 13, 1,
    // on stack: 5, 3
    POPANDPRINT,
    // print: 3, on stack: 5
    POPANDPRINT,
    // print: 5, on stack: /
    HALT,
    // halt
    // function func: addr 13
    PUSH, 1,
    // on stack frame 2, 1
    ADD,
    // on stack frame 3
    RET
  };*/
  
  int32_t factprog[] = {
    // function fact: addr 0
    // stack: n
    DUP,
    // stack: n, n
    PUSH, 0,
    // stack: n, n, 0
    EQ,
    // stack: n, n == 0
    JMPF, 9,
    // n == 0: true, stack: n
    PUSH, 1,
    // stack: n, 1
    RET,
    // return 1
    //
    // n == 0: false, stack: n
    DUP,
    // stack: n, n
    PUSH, 1,
    // stack: n, n, 1
    SUBT,
    // stack: n, n - 1
    CALL, 0, 1,
    // stack: n, fact(n - 1)
    MULT,
    // stack: n * fact(n - 1)
    RET,
    // return n * fact(n - 1)
    //
    // main
    PUSH, 5,
    // stack: 3
    CALL, 0, 1,
    // stack: n * fact(n - 1)
    POPANDPRINT,
    HALT
  };

  /*int32_t stackoverflowprog[] = {
    CALL, 4, 0,
    RET,
    CALL, 0, 0,
    RET,
    HALT,
  };*/
  // clang-format on

  VM vm(18, factprog, sizeof(factprog) / sizeof(int32_t));
  // VM vm(0, testprog, sizeof(testprog) / sizeof(int32_t));

  vm.run();

  return 0;
}
