#include "serializer.h"
#include "../_base.h"

// TODO: Això el que fa es guardar la IR de Wyrm i posar-la tot molt bonica
// en principi si s'executa Wyrm sense cap runner, en principi haria de guardar
// en arxius representacions intermitges, en cas contrari, es passa al respectiu
// runner

using namespace Wyrm;

Serializer::Serializer(Book *book) { this->book = book; }

void Serializer::SerializeToFile(WyrmAPI::TreeCode codeInfo,
                                 std::string fileName) {
  FILE *f = fopen(fileName.c_str(), "wb");
  if (!f) {
    WyrmAPI::Debug::LogError("Error writing to file!");
    return;
  }

  std::vector<std::string> deps = codeInfo.GetDependencies();
  unsigned int libCount = deps.size();
  fwrite(&libCount, sizeof(unsigned int), 1, f);

  for (int i = 0; i < libCount; i++) {
    SerializeString(f, deps[i]);
  }

  SerializeNode(f, codeInfo.root, codeInfo.GetDependencies());

  fclose(f);
}

void Serializer::SerializeString(FILE *f, std::string s) {
  unsigned int size = s.size();
  fwrite(&size, sizeof(unsigned int), 1, f);
  fwrite(&s, sizeof(char), size, f);
}

void Serializer::SerializeAtom(FILE *f, WyrmAPI::Atom *atom) {
  int typeId = atom->typeId;
  fwrite(&typeId, sizeof(int), 1, f);
  fwrite(&(atom->data->num), sizeof(int), 1, f);
  fwrite(&(atom->data->data), 1, atom->data->num, f); // Va en bytes i tal
}

void Serializer::SerializeNode(FILE *f, WyrmAPI::Node *n,
                               std::vector<std::string> &libs) {
  if (n->atom != NULL)
    SerializeAtom(f, n->atom);

  fwrite(&(n->allocable), sizeof(bool), 1, f);
  fwrite(&(n->nd), sizeof(int), 1, f);

  int type = (int)n->type;
  fwrite(&type, sizeof(int), 1, f);

  SerializeString(f, n->sData);

  unsigned int nodeCount = n->children.size();
  fwrite(&nodeCount, sizeof(unsigned int), 1, f);

  for (int i = 0; i < nodeCount; i++) {
    SerializeNode(f, n->children[i], libs);
  }
}

/*
void Serializer::SerializeFromFile(std::string fileName, MachineCode *code) {
  FILE *f = fopen(fileName.c_str(), "rb");
  if (!f) {
    Debug::LogError("Error reading file " + fileName + "!");
    return;
  }

  MachineCode machinCode;

  unsigned int regCount;
  fread(&regCount, sizeof(unsigned int), 1, f);

  machinCode.regCount = regCount;

  unsigned int s; // Constant size
  fread(&s, sizeof(unsigned int), 1, f);

  // std::cout << "S: " << s << std::endl;

  for (unsigned int i = 0; i < s; i++) {
    // ReadConst(f, &machinCode.constants);
  }

  while (ReadInstruction(f, &machinCode.instructions))
    ; // Lee instrucciones hasta que se acaben creo

  fclose(f);
  *code = machinCode;
}
*/
