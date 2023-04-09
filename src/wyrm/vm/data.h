#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../../api/wyrm.h"
#include "../compiler/nodes.h"

namespace Wyrm {

/*
enum Type {
    INT,
    NUMBER,
    REAL,
    STRING,
    BOOL,
    FUNCTION,
    _NULL,
};
*/

struct Reservation {
  std::string identifier;
  bool isFree;
  bool isIdentifier;

  Reservation() {
    isFree = false;
    isIdentifier = false;
  }
};

enum ParamType {
  E,
  A,
  AB,
  ABC,
  ABCD,
};

enum InstructionID {
  LOADC,
  MOVE, // A, B

  CALL, // A, B, C // A(B+1, B+2, ..., B+C-1)
  DEF,
  ICL, // A, B, C // A(B+1,B+2,...,B+C-1) // Internal call
  RET, // Return something from reg A

  // Operacions
  // Important no canviar d'ordre
  UNARY,
  BINARY,
  ASSIGNARY,

  /* ADD, // A = B + C
  SUB, // A = B - C
  MUL, // A = B * C
  DIV, // A = B / C
  MOD,

  AND,
  OR,
  NOT,

  EQ,
  NEQ,
  GT,
  LT,
  GEQ,
  LEQ, */
  // ---------------------

  TO,
  END,
  JUMP,
  TEST,
  HALT,
};

class Instruction {
public:
  Instruction();
  Instruction(InstructionID type, ParamType paramType);

  void SetA(int a);
  void SetB(int b);
  void SetC(int c);
  void SetD(int d);

  int GetA();
  int GetB();
  int GetC();
  int GetD();

  InstructionID type;
  int temp;
  ParamType paramType;

private:
  int a, b, c, d;
};

struct MachineCode {
  std::vector<Atom *> constants;
  std::vector<Instruction> instructions;
  int regCount;
};
} // namespace Wyrm
