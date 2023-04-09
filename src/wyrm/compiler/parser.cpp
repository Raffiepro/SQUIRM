#include "parser.h"

#include "../headers/debug.hpp"
#include "airthmetic.h"
#include "nodes.h"

#include <iostream>
#include <vector>

using namespace Wyrm;

Parser::Parser(Book *book, std::vector<Token> tokens) {
  this->tokens = tokens;
  this->book = book;

  // Nodes::Node root(Nodes::NodeType::NODE);
  root = new Nodes::Node();
  try {
    GenerateCode(0, this->tokens.size(), root);
    // root->Debug();
  } catch (std::string p) {
    // Erroreado
    Debug::LogError(p);
  }
}

Nodes::Node *Parser::GetAST() { return root; }

bool Parser::CodeLoop(int *from, int *nF, Nodes::Node *parent) {
  // No hi ha manera de treure això ja que son funcions estàtiques
  Nodes::Node *next;

  try {
    GetCodeFunction(&next, *from, nF);
    if (*nF != *from) {
      parent->children.push_back(next);
      *from = *nF;
      return true;
    }

    GetCodeConditional(&next, *from, nF);
    if (*nF != *from) {
      parent->children.push_back(next);
      *from = *nF;
      return true;
    }

    GetCodeWhile(&next, *from, nF);
    if (*nF != *from) {
      parent->children.push_back(next);
      *from = *nF;
      return true;
    }

    GetCodeReturn(&next, *from, nF);
    if (*nF != *from) {
      parent->children.push_back(next);
      *from = *nF;
      return true;
    }

    GetCodeFor(&next, *from, nF);
    if (*nF != *from) {
      parent->children.push_back(next);
      *from = *nF;
      return true;
    }

    GetCodeBreak(&next, *from, nF);
    if (*nF != *from) {
      parent->children.push_back(next);
      *from = *nF;
      return true;
    }

    GetCodeSkip(&next, *from, nF);
    if (*nF != *from) {
      parent->children.push_back(next);
      *from = *nF;
      return true;
    }
  } catch (std::string s) {
    throw(s);
  }
  return false;
}

void Parser::GenerateCode(int from, int to, Nodes::Node *parent) {

  int currentEnd;
  while (from < to) {
    // Val aqui anem a fer check de una funció!
    int nF = from;

    try {
      if (CodeLoop(&from, &nF, parent))
        continue;
    } catch (std::string s) {
      throw(s);
    }

    currentEnd = GetNext(from, to, WyrmAPI::TokenType::SEPARATOR);
    if (currentEnd == to &&
        tokens[currentEnd].type != WyrmAPI::TokenType::SEPARATOR)
      throw(std::string("Syntax error: Expected ';' at end of expression"));
    GetCodeLine(parent, from, currentEnd);
    from = currentEnd + 1;

    // Per si n hi ha 2
    if (tokens[from].type == WyrmAPI::TokenType::SEPARATOR) {
      if (from < to)
        from++;
    }

    // throw std::string("Miau por la ventana");
  }
}

void Parser::GetCodeBreak(Nodes::Node **root, int from, int *end) {
  if (!Eat(from, WyrmAPI::TokenType::BREAK, &from))
    return;

  Nodes::Node *brek = new Nodes::Node(Nodes::NodeType::BREAK);

  *end = from + 1;
  *root = brek;
}

void Parser::GetCodeSkip(Nodes::Node **root, int from, int *end) {
  if (!Eat(from, WyrmAPI::TokenType::CONTINUE, &from))
    return;

  Nodes::Node *skip = new Nodes::Node(Nodes::NodeType::SKIP);

  *end = from + 1;
  *root = skip;
}

void Parser::GetCodeFor(Nodes::Node **root, int from, int *end) {
  if (!Eat(from, WyrmAPI::TokenType::FOR, &from))
    return;

  int to = GetNextCodeSep(from, -1);
  // Suport per : ?

  // Ara aconseguim les 3 expressions que hi ha a dins de to!

  Nodes::Node *fo = new Nodes::Node(Nodes::NodeType::FOR);
  Nodes::Node *exp, *code = new Nodes::Node();
  // for <a> ; <b> ; <c> {}

  int tempTo;
  // a - Es una code line
  tempTo = GetNext(from, -1, WyrmAPI::TokenType::SEMICOLON);
  exp = new Nodes::Node();
  GetCodeLine(exp, from, tempTo);
  fo->children.push_back(exp);

  from = tempTo + 1;
  // b, una expression
  Nodes::Node *skip = new Nodes::Node(Nodes::NodeType::SKIP);

  *end = from + 1;
  *root = skip;
}

void Parser::GetCodeReturn(Nodes::Node **root, int from, int *end) {
  if (!Eat(from, WyrmAPI::TokenType::RETURN, &from))
    return;

  Nodes::Node *ret = new Nodes::Node(Nodes::NodeType::RETURN), *exp;
  int to = GetNext(from, -1, WyrmAPI::TokenType::SEMICOLON);

  // std::cout << from << " " << to << std::endl;
  if (from != to) {
    try {
      GetExpression(from, to - 1, &exp);
    } catch (std::string p) {
      throw p;
    }

    ret->children.push_back(exp);
  }
  *root = ret;
  *end = to + 1;
}
/*
if(<condició>){
    // Codi
} else if(<condició>) {
    // Codi
} else {
    // Codi
}
*/

void Parser::GetCodeConditional(Nodes::Node **root, int from, int *end) {
  if (!Eat(from, WyrmAPI::TokenType::IF, &from))
    return;

  Nodes::Node *theIf = new Nodes::Node(Nodes::NodeType::IF);

  GetConditional(from, &from, theIf);

  while (Eat(from, WyrmAPI::TokenType::ELSE, &from)) {
    if (Eat(from, WyrmAPI::TokenType::IF, &from)) {
      GetConditional(from, &from, theIf);
      theIf->nd += 1;
      continue;
    } else {
      Nodes::Node *theElse = new Nodes::Node(Nodes::NodeType::NODE);
      GetCodeBlock(from, &from, theElse);
      theIf->children.push_back(theElse);
    }

    break;
  }

  *root = theIf;
  *end = from;
}

// Simplement es
/*
while expressió {
    // codi
}
*/
void Parser::GetCodeWhile(Nodes::Node **root, int from, int *end) {
  if (!Eat(from, WyrmAPI::TokenType::WHILE, &from))
    return;

  Nodes::Node *bucle = new Nodes::Node(Nodes::NodeType::WHILE);
  GetConditional(from, end, bucle);

  *root = bucle;
}

/*
Aconsegueix parsejar una cosa de la forma
(expressió) {
    // Codi
}
*/
void Parser::GetConditional(int from, int *end, Nodes::Node *pushNode) {
  // Aconseguim la condició
  Nodes::Node *content = new Nodes::Node(Nodes::NodeType::NODE);

  int to = GetNextCodeSep(from, -1);

  // std::cout << "EXP: " << from << " " << to - 1 << std::endl;
  Nodes::Node *expression;
  try {
    GetExpression(from, to - 1, &expression);
  } catch (std::string p) {
    throw(p);
  }

  GetCodeBlock(from, end, content);

  pushNode->children.push_back(expression);
  pushNode->children.push_back(content);
}

/*
Volem un node de la forma
func nd: nombre de params
1: Identificador de la funció
2: Tipus que retorna la funció
3: Codi de dins
4 <-> 4+nd: Paràmetres que rep

-1-
func <def> : (<type def1, ..., type defn>) => type {
    <AST>
}

Val estaria guai fer que es pugui escriure també de forma

-2-
func <def> { // Sense arguments i no retorna res
    <AST>
}

-3-
func <def> : <type def1, ..., type defn> { // Amb arguments i no retorna res
    <AST>
}

-4-
func <def> => type { // Sense arguments retorna el tipus
    <AST>
}
*/
void Parser::GetCodeFunction(Nodes::Node **root, int from, int *end) {

  if (!Eat(from, WyrmAPI::TokenType::FUNCTION_DECLARATION, &from))
    return;

  Nodes::Node *function = new Nodes::Node(Nodes::NodeType::FUNCTION);

  // A partir d'aqui són excepcions
  if (!Eat(from, WyrmAPI::TokenType::IDENTIFIER, &from))
    throw(std::string("Syntax error: Expected function identifier"));

  from--;
  std::string funcIdentifier = this->tokens[from].value;
  from++;

  std::vector<Nodes::Node *> parameters;
  Nodes::Node *code = new Nodes::Node(),
              *type = new Nodes::Node(Nodes::NodeType::TYPE),
              *identifier = new Nodes::Node(Nodes::NodeType::REFERENCE);

  int to, to2;
  if (Eat(from, WyrmAPI::TokenType::TWO_POINTS, &from)) {
    // Tipus 1, 3 - Tenim paràmetres! Ara falta veure si hi ha return type
    // if(!Eat(this->tokens[from].type, Token::TokenType::PARENTHESIS_OPEN,
    // &from)) return; Val ara estem apuntant al primer parèntesis i ara
    // agafarem les coses

    function->nd = parameters.size();

    int finTo = GetNext(from, -1, WyrmAPI::TokenType::CURLY_BRACKET_OPEN);

    to = GetNext(from, finTo, WyrmAPI::TokenType::WIDE_ARROW_LEFT);
    to2 = GetNext(from, -1, WyrmAPI::TokenType::TWO_POINTS);
    if (to2 < to)
      to = to2;

    GetFunctionParameters(from, to - 1,
                          &parameters); // Lo de dins sense parèntesis

    from = to;

    // from = to+1;
  }

  if (Eat(from, WyrmAPI::TokenType::WIDE_ARROW_LEFT, &from)) {
    // Ara tenim return type! Anem a llegir-lo!
    if (this->tokens[from].type != WyrmAPI::TokenType::TYPE) {
      throw std::string("Syntax error: Expected return type");
    };
    int typeId = book->GetTypeFromName(this->tokens[from].value);

    type->nd = typeId;
    from++;
  } else {
    type->nd = -1; // Suposo que això és void
  }

  GetCodeBlock(from - 1, end, code);
  // Empenyem info bàsica
  identifier->SetDataString(funcIdentifier);
  function->children.push_back(identifier);
  function->children.push_back(type);

  // L'afegim
  function->children.push_back(code);

  // I els parametres
  for (int i = 0; i < parameters.size(); i++) {
    function->children.push_back(parameters[i]);
  }

  *root = function;
}

// int a, string b, real c
void Parser::GetFunctionParameters(int from, int to,
                                   std::vector<Nodes::Node *> *container) {
  if (from > to)
    return;

  Nodes::Node *next;
  int tA = from;

  do {
    tA = GetNext(from, to + 1, WyrmAPI::TokenType::COMMA);

    GetFunctionParameter(from, tA - 1, &next);
    container->push_back(next);

    from = tA + 1;
  } while (from < to || tA < to);
}

// int a
void Parser::GetFunctionParameter(int from, int to, Nodes::Node **writeNode) {
  // En principi to - from = 1
  Nodes::Node *param = new Nodes::Node(Nodes::NodeType::PARAMETER),
              *typeNode = new Nodes::Node(Nodes::NodeType::TYPE);
  param->SetDataString(this->tokens[to].value);
  typeNode->nd = book->GetTypeFromName(this->tokens[from].value);
  param->children.push_back(typeNode);

  *writeNode = param;
}

// Aconseguim una linea de codi de la forma
// <tipus> <var> = exp
// On var es opcional, pero si es posa cal el "="
// i tipus és opcional en cas que l'expressió sigui <var> = exp
void Parser::GetCodeLine(Nodes::Node *root, int from, int to) {

  if (this->tokens[from].type == WyrmAPI::TokenType::TYPE) {
    // Aqui podriem optimitzar memòria
    Nodes::Node *typeNode = new Nodes::Node(Nodes::NodeType::TYPE);
    typeNode->nd = book->GetTypeFromName(
        this->tokens[from]
            .value); // Hauriem de tenir una taula amb tipus més endavant?

    // Vale ok podem ara llegir el nom de la variable i tal
    from++;

    // AQUI CAL FER UNA AMABLE LLISTA DE EXPRESSIONS I MODIFICAR-LES SEGONS EL
    // TIPUS
    std::vector<Nodes::Node *> assignations;
    try {
      GetAssignations(from, to - 1, &assignations);
    } catch (std::string p) {
      throw p;
    }

    // Modifiquem les assignacions per tal de fer declaracions
    for (int i = 0; i < assignations.size(); i++) {

      assignations[i]->type = Nodes::NodeType::DECLARATION;
      assignations[i]->children.push_back(typeNode);

      // Posem les declaracions a dins!
      root->children.push_back(assignations[i]);
    }
  } else if (this->tokens[from].type == WyrmAPI::TokenType::IDENTIFIER &&
             IsOf(assignations, this->tokens[from + 1].type)) {
    // Només assignations, res a veure

    std::vector<Nodes::Node *> assignations;

    try {
      GetAssignations(from, to - 1, &assignations);
    } catch (std::string p) {
      throw p;
    }

    for (int i = 0; i < assignations.size(); i++) {
      root->children.push_back(assignations[i]);
    }
  } else {
    // És una expressió, la afegim simplement (PERO AIXO ES UN PRINT!!!)
    // detectem comes i les entrellacem!
    Nodes::Node *exp;

    int tA, tB;
    do {
      tA = GetNext(from, -1, WyrmAPI::TokenType::COMMA);

      if (tA > to)
        tA = to;

      try {
        GetExpression(from, tA - 1, &exp);
      } catch (std::string p) {
        throw(p);
      }
      Nodes::Node *def = new Nodes::Node(Nodes::NodeType::DEF_FUNCTION);
      def->children.push_back(exp);

      root->children.push_back(def);

      // Ara desplaçem from
      from = tA + 1;
    } while (from < to || tA < to);
    /*
    try {

        GetExpression(from, to-1, &exp);
    } catch(std::string p){
        throw(p);
    }
    def->children.push_back(exp);
    root->children.push_back(def);
    */
  }
}

void Parser::GetAssignation(int from, int to, Nodes::Node **writeNode) {
  // En principi from es l'identifier, despres va un igual, i després una
  // expressió fins a to
  std::string id = this->tokens[from].value;
  Nodes::Node *exp;

  if (from == to) {
    Nodes::Node *assignation = new Nodes::Node(Nodes::ASSIGNATION);
    assignation->SetDataString(id);

    *writeNode = assignation;
    return;
  }

  from++;
  if (!IsOf(assignations, this->tokens[from].type)) {
    // Throw exception
    throw(std::string("Syntax error: Expected assignation"));
  }

  from++;

  if (!ContainsAssignation(from, to)) {
    try {
      GetExpression(from, to, &exp);
    } catch (std::string p) {
      throw p;
    }
  } else {
    throw(std::string("Syntax error: Unexcepted assignation"));
  }

  Nodes::Node *assignation = new Nodes::Node(Nodes::ASSIGNATION);
  assignation->SetDataString(id);

  if (this->tokens[from - 1].type != WyrmAPI::TokenType::ASSIGMENT) {
    // Es una operació cal operar ara mateix!!!
    Nodes::Node *op = new Nodes::Node(Nodes::NodeType::EXP_BINARY);
    Nodes::Node *ref = new Nodes::Node(Nodes::NodeType::REFERENCE);

    ref->SetDataString(id);
    op->nd = (int)opMap[this->tokens[from - 1].type];

    op->children.push_back(ref);
    op->children.push_back(exp);

    assignation->children.push_back(op);
  } else
    assignation->children.push_back(exp);
  // Ara tenim a exp l'expressió, falta ara construir l'assignació final

  *writeNode = assignation;
}

void Parser::GetAssignations(int from, int to,
                             std::vector<Nodes::Node *> *container) {
  /*
  Tenim uns tokens de la forma
  a = 3, b += 5, c = "Hola que tal", d = f(2,3) + c, e = 4
  Volem separar les assignacions per comes i anar cridant GetAssignation
  */
  if (from > to)
    return;

  Nodes::Node *next;

  if (from == to) {
    // Empty assignation
    try {
      GetAssignation(from, to, &next);
    } catch (std::string p) {
      throw(p);
    }
    container->push_back(next);
  }

  int tA = from;

  do {
    tA = GetNext(from, to + 1, WyrmAPI::TokenType::COMMA);
    // Val llavors tenim que:
    // a = 3 + 5, b =
    // | f      | tA
    try {
      GetAssignation(from, tA - 1, &next);
    } catch (std::string p) {
      throw(p);
    }
    container->push_back(next);

    // Ara desplaçem from
    from = tA + 1;
  } while (from < to || tA < to);
}

bool Parser::Eat(int pos, WyrmAPI::TokenType comp, int *from) {
  WyrmAPI::TokenType tok = this->tokens[pos].type;
  if (*from >= this->tokens.size())
    return false;

  if (tok == comp) {
    *from += 1;
    return true;
  } else {
    // Call error, unexcepted identifier
    return false;
  }
}

int Parser::GetNext(int from, int lim, WyrmAPI::TokenType type) {
  // Trobem el proxim type respectant la jerarquia de parèntesis
  int j = 0;
  WyrmAPI::TokenType t = this->tokens[from].type;
  while (from < this->tokens.size() && t != type) {
    do {
      if (t == WyrmAPI::TokenType::PARENTHESIS_CLOSE)
        j--;
      if (t == WyrmAPI::TokenType::PARENTHESIS_OPEN)
        j++;

      if (t == WyrmAPI::TokenType::CURLY_BRACKET_CLOSE)
        j--;
      if (t == WyrmAPI::TokenType::CURLY_BRACKET_OPEN)
        j++;

      if (t == WyrmAPI::TokenType::SQUARE_BRACKET_CLOSE)
        j--;
      if (t == WyrmAPI::TokenType::SQUARE_BRACKET_OPEN)
        j++;

      from++;
      if (from > tokens.size()) {
        throw std::string("Syntax error: Unexpected token");
      }
      if (from < this->tokens.size())
        t = this->tokens[from].type;

      // Es podrien agafar excepcions si j < 0
    } while (j > 0);
  }
  if (from > tokens.size()) {
    throw -1;
  }
  if (from < lim || lim == -1)
    return from;
  else
    return lim;
}

void Parser::GetArguments(int from, int to,
                          std::vector<Nodes::Node *> *parent) {
  // Tenim expressions separades per comes, ex:
  // 2, 3, hola(), f() + 45
  // Volem passar-les a una llista guardada dins de parent

  // Cas aillat en cas que from > to
  if (from > to)
    return;

  Nodes::Node *next;
  int tA = from;

  do {
    tA = GetNext(from, to + 1, WyrmAPI::TokenType::COMMA);
    // Val llavors tenim que:
    // 3 + 5, f()
    // | f      | tA
    try {
      GetExpression(from, tA - 1, &next);
    } catch (std::string p) {
      throw p;
    }

    parent->push_back(next);

    // Ara desplaçem from
    from = tA + 1;
  } while (from < to || tA < to);
}

// TODO: Que aixo funcioni amb les politiques dels tipus i tal
void Parser::GetLiteral(int index, Nodes::Node **writeNode) {
  Token token = this->tokens[index];
  Nodes::Node *lit = new Nodes::Node(Nodes::NodeType::VALUE);

  lit->data = book->literals[token.data].toData(token.value);

  *writeNode = lit;
}

void Parser::GetExpression(int from, int to, Nodes::Node **writeNode) {
  // std::cout << "F: " << from << " T: " << to << std::endl;
  if (from > to) {
    throw(std::string("Syntax error: Expected expression"));
  }
  if (from == to) {
    // En cas que la longitud sigui 1
    // std::cout << from << "!!!" << std::endl;
    if (this->tokens[from].IsLiteral()) {
      GetLiteral(from, writeNode);
    }

    if (this->tokens[from].IsIdentifier()) {
      Nodes::Node *id = new Nodes::Node(Nodes::NodeType::REFERENCE);
      id->SetDataString(this->tokens[from].value);
      *writeNode = id;
      // std::cout << "IDENTIFIER" << std::endl;
    }

    return;
  }

  // Comprovem primer ara si això es una call
  if (this->tokens[from].IsIdentifier()) {
    if (this->tokens[from + 1].type == WyrmAPI::TokenType::PARENTHESIS_OPEN) {
      int l = GetNext(from + 1, to, WyrmAPI::TokenType::PARENTHESIS_CLOSE);

      if (l == to) {
        std::string value = this->tokens[from].value;

        from++;
        if (Eat(from, WyrmAPI::TokenType::PARENTHESIS_OPEN, &from)) {
          Nodes::Node *call = new Nodes::Node(Nodes::NodeType::EXP_CALL);
          call->SetDataString(value);

          GetArguments(from, to - 1, &(call->children));
          *writeNode = call;

          return;
        }
      }
    }
  }

  // Cas que els parèntesis siguin buits
  if (this->tokens[from].type == WyrmAPI::TokenType::PARENTHESIS_OPEN) {
    if (this->tokens[to].type == WyrmAPI::TokenType::PARENTHESIS_CLOSE) {
      int f = from + 1;
      f = GetNext(f, -1, WyrmAPI::TokenType::PARENTHESIS_CLOSE);
      if (f == to) {

        try {
          GetExpression(from + 1, to - 1, writeNode);
        } catch (std::string p) {
          throw(p);
        }

        return;
      }
    }
  }

  int i, k;

  for (i = opOrder.size() - 1; i >= 0; i--) {
    for (k = 0; k < opOrder[i].size(); k++) {
      int n;
      try {
        n = GetNext(from, to, opOrder[i][k]);

        // std::cout << "Vale tenim el desto a " << n << std::endl;
      } catch (std::string p) {
        throw(p);
      }

      // Val estem en la forma exp (simbol) exp, hem de trobar el simbol, estem
      // al final doncs iterem fins a trobar algun simbol potser
      Nodes::Node *op, *first, *second;
      if (n == from) {

        // std::cout << "Vale tenim el ???a " << n << std::endl;
        // Ei és una operació unaria!
        op = new Nodes::Node(Nodes::NodeType::EXP_UNARY);

        op->nd = (int)tokenToSymbol[opOrder[i][k]];

        try {
          GetExpression(from + 1, to, &first);
        } catch (std::string p) {
          throw p;
        }

        op->children.push_back(first);
        *writeNode = op;
        return;
      }

      if (n != to) { // L'hem trobat
        // from --- n simbol n --- to
        op = new Nodes::Node(Nodes::NodeType::EXP_BINARY);

        // Aqui suposo que s'haura de passar per algun map
        op->nd = (int)tokenToSymbol[opOrder[i][k]];

        try {
          GetExpression(from, n - 1, &first);
        } catch (std::string p) {
          throw p;
        }

        try {
          GetExpression(n + 1, to, &second);
        } catch (std::string p) {
          throw p;
        }

        op->children.push_back(first);
        op->children.push_back(second);
        *writeNode = op;

        return;
      }
    }
  }

  throw(std::string("Syntax error: Expected expression"));
}

bool Parser::IsOf(std::vector<WyrmAPI::TokenType> list,
                  WyrmAPI::TokenType type) {
  for (int i = 0; i < list.size(); i++)
    if (type == list[i])
      return true;
  return false;
}

int Parser::GetNextCodeSep(int from, int lim) {
  // Ok eh hem d'aconseguir el proxim '{', o ':', el que vingui abans:
  int c, p;
  try {
    c = GetNext(from, lim, WyrmAPI::TokenType::CURLY_BRACKET_OPEN);
    p = GetNext(from, lim, WyrmAPI::TokenType::TWO_POINTS);
  } catch (std::string r) {
    throw(r);
  }

  if (c < p)
    return c;
  return p;
}

// ------- {
//   |
// from
//      <codi>
// }

// o

// ----------------- : <linea>
//   |
// from
void Parser::GetCodeBlock(int from, int *to, Nodes::Node *parent) {

  try {
    from = GetNextCodeSep(from, -1);
  } catch (std::string p) {
    throw(p);
  }

  if (Eat(from, WyrmAPI::TokenType::CURLY_BRACKET_OPEN, &from)) {
    *to = GetNext(from, -1, WyrmAPI::TokenType::CURLY_BRACKET_CLOSE);

    GenerateCode(from, *to, parent);
    *to = *to + 1;
  } else if (Eat(from, WyrmAPI::TokenType::TWO_POINTS, &from)) {
    *to = GetNext(from, -1, WyrmAPI::TokenType::SEMICOLON);
    GenerateCode(from, *to, parent);
    *to = *to + 1;
  } else {
    throw(std::string("Error: S'esperava '{' o ':'"));
    // std::cout << "Hola???? Aixo es que has programat malament" << std::endl;
  }
}

bool Parser::ContainsAssignation(int from, int to) {
  for (int i = from; i < to; i++) {
    if (IsOf(assignations, this->tokens[i].type))
      return true;
  }
  return false;
}
