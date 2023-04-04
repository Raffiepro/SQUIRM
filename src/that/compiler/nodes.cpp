#include "nodes.h"
#include "../headers/termcolor.hpp"
#include "../../api/that.h"

#include <iostream>
#include <map>

using namespace That;


Nodes::Node::Node(NodeType type){
    this->type = type;
    this->children.reserve(1);
    this->allocable = false;
}

Nodes::Node::Node(){
    this->type = NodeType::NODE;
    this->children.reserve(1);
    this->allocable = false;
}

Nodes::Node::~Node(){
    // std::cout << "Miau" << std::endl;
    if(allocable) delete[] data.bytes;
    for(int i = 0; i < children.size(); i++){
        delete children[i];
    }

}

void Nodes::Node::Debug(){
    std::map<NodeType, std::string> trans = {
        {NODE, "NODE"},
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
        {VALUE, "VALUE"}
    };

    std::cout << "[ ";
    std::cout << "type: " << termcolor::green << trans[this->type] << termcolor::reset << ", ";
    std::cout << "fills: ";
    for(int i = 0; i < this->children.size(); i++){
        this->children[i]->Debug();
    }
    std::cout << ", data: " << this->data.integer;
    std::cout << ", nd: " << this->nd;
    std::cout << " ]";
}

void Nodes::Node::SetDataString(std::string s){
    this->nd = s.size();
    this->data.bytes = new char[this->nd];
    this->allocable = true;
    for(int i = 0; i < s.size(); i++) this->data.bytes[i] = s[i];
}

bool Nodes::Node::IsExpression(){
    return (IsValue() ||
    this->type == Nodes::NodeType::EXP_BINARY ||
    this->type == Nodes::NodeType::EXP_UNARY ||
    this->type == Nodes::NodeType::EXP_CALL);
}

bool Nodes::Node::IsValue(){
    return (this->type == Nodes::NodeType::VALUE);
}

std::string Nodes::Node::GetDataString(){
    std::string s = "";
    for(int i = 0; i < this->nd; i++) s += this->data.bytes[i];
    return s;
}

ThatAPI::Data Nodes::Node::GetData(){
    return ThatAPI::Data(); // TODO
}