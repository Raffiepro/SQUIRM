#include <string>
#include <vector>

#include "wyrm.h"

namespace WyrmAPI {

enum NodeType {
    NODE,
    ERROR,
    DECLARATION,
    ASSIGNATION,
    REFERENCE,
    PARAMETER,
    TYPE,
    IF,
    WHILE,
    FOR,
    BREAK,
    SKIP,
    RETURN,
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
  Node(NodeType);
  Node();
  ~Node();

  std::vector<Node *> children;
  NodeType type;

  bool allocable = false;
  int nd;
  std::string sData;
  Atom *atom = NULL;

  void Debug();

  bool IsValue();
  bool IsExpression();

  void SetDataString(std::string s);
  std::string GetDataString();
};
} // namespace WyrmAPI
