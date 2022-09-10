#pragma once

// VM Istruction Set
enum {
  // stack operations
  PUSH,
  POP,
  DUP,
  // math operations
  ADD,
  SUBT,
  MULT,
  // comparison operations
  EQ,
  NEQ,
  GT,
  LT,
  GTE,
  LTE,
  // boolean operations
  AND,
  OR,
  NOT,
  // jump operations
  JMP,
  JMPT,
  JMPF,
  // function operations
  CALL,
  RET,
  // special operations
  POPANDPRINT,
  HALT
};