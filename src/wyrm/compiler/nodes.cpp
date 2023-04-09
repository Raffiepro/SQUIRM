#include "nodes.h"
#include "../../api/wyrm.h"
#include "../headers/termcolor.hpp"

#include <iostream>
#include <map>

using namespace Wyrm;

Nodes::Node::Node(NodeType type) {
  this->type = type;
  this->children.reserve(1);
  this->allocable = false;
}

Nodes::Node::Node() {
  this->type = NodeType::NODE;
  this->children.reserve(1);
  this->allocable = false;
}

Nodes::Node::~Node() {
  // std::cout << "Miau" << std::endl;
  for (int i = 0; i < children.size(); i++) {
    delete children[i];
  }
}

void Nodes::Node::Debug() {
  std::map<NodeType, std::string> trans = {{NODE, "NODE"},
                                           {ERROR, "ERROR"},
                                           {DECLARATION, "DECLARATION"},
                                           {ASSIGNATION, "ASSIGNATION"},
                                           {REFERENCE, "REFERENCE"},
                                           {PARAMETER, "PARAMETER"},
                                           {TYPE, "TYPE"},
                                           {IF, "IF"},
                                           {WHILE, "WHILE"},
                                           {FUNCTION, "FUNCTION"},
                                           {DEF_FUNCTION, "DEF_FUNCTION"},
                                           {RETURN, "RETURN"},
                                           {FOR, "FOR"},
                                           {BREAK, "BREAK"},
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

void Nodes::Node::SetDataString(std::string s) { this->sData = s; }

bool Nodes::Node::IsExpression() {
  return (IsValue() || this->type == Nodes::NodeType::EXP_BINARY ||
          this->type == Nodes::NodeType::EXP_UNARY ||
          this->type == Nodes::NodeType::EXP_CALL);
}

bool Nodes::Node::IsValue() { return (this->type == Nodes::NodeType::VALUE); }

std::string Nodes::Node::GetDataString() { return this->sData; }
