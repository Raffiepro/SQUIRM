#pragma once

#include <map>
#include <string>
#include <vector>

#include "wyrm.h"

namespace WyrmAPI {

enum NodeType {
  NODE,
  ERROR_NODE,
  DECLARATION,
  ASSIGNATION,
  REFERENCE,
  PARAMETER,
  TYPE_NODE,
  IF_NODE,
  WHILE_NODE,
  FOR_NODE,
  BREAK_NODE,
  SKIP,
  RETURN_NODE,
  FUNCTION,
  DEF_FUNCTION,
  NODE_ERROR,
  EXP_BINARY,
  EXP_UNARY,
  EXP_CALL,
  VALUE,
};

struct Atom {
  Data *data;
  int typeId;
};

class Node {

public:
  // Node(NodeType type);
  // void Execute(); // Això per execució un cop construida la estructura del
  // codi
  Node(NodeType type) {
    this->type = type;
    this->children.reserve(1);
    this->allocable = false;
  };
  Node() {
    this->type = NodeType::NODE;
    this->children.reserve(1);
    this->allocable = false;
  }
  ~Node() {
    for (int i = 0; i < children.size(); i++) {
      delete children[i];
    }
  }

  std::vector<Node *> children;
  NodeType type;

  bool allocable = false;
  int nd;
  std::string sData;
  Atom *atom = NULL;

  void Debug() {
    std::map<NodeType, std::string> trans = {{NODE, "NODE"},
                                             {ERROR_NODE, "ERROR"},
                                             {DECLARATION, "DECLARATION"},
                                             {ASSIGNATION, "ASSIGNATION"},
                                             {REFERENCE, "REFERENCE"},
                                             {PARAMETER, "PARAMETER"},
                                             {TYPE_NODE, "TYPE"},
                                             {IF_NODE, "IF"},
                                             {WHILE_NODE, "WHILE"},
                                             {FUNCTION, "FUNCTION"},
                                             {DEF_FUNCTION, "DEF_FUNCTION"},
                                             {RETURN_NODE, "RETURN"},
                                             {FOR_NODE, "FOR"},
                                             {BREAK_NODE, "BREAK"},
                                             {SKIP, "SKIP"},
                                             {NODE_ERROR, "NODE_ERROR"},
                                             {EXP_BINARY, "EXP_BINARY"},
                                             {EXP_UNARY, "EXP_UNARY"},
                                             {EXP_CALL, "EXP_CALL"},
                                             {VALUE, "VALUE"}};

    std::cout << "[ ";
    if (trans.find(this->type) == trans.end())
      std::cout << "type: " << termcolor::red << "UNDEFINED" << termcolor::reset
                << ", ";
    else
      std::cout << "type: " << termcolor::green << trans[this->type]
                << termcolor::reset;

    if (this->children.size() > 0) {
      std::cout << ", fills: ";
      for (int i = 0; i < this->children.size(); i++) {
        this->children[i]->Debug();
      }
    }

    if (this->atom != NULL)
      std::cout << ", atom: " << this->atom->data->num;
    std::cout << " ]";
  }

  bool IsValue() { return (this->type == NodeType::VALUE); }
  bool IsExpression() {
    return (IsValue() || this->type == NodeType::EXP_BINARY ||
            this->type == NodeType::EXP_UNARY ||
            this->type == NodeType::EXP_CALL);
  }

  void SetDataString(std::string s) { this->sData = s; }
  std::string GetDataString() { return this->sData; }
};
} // namespace WyrmAPI
