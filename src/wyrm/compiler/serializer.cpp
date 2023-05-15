#include "serializer.h"
#include "../_base.h"

// TODO: Això el que fa es guardar la IR de Wyrm i posar-la tot molt bonica
// en principi si s'executa Wyrm sense cap runner, en principi haria de guardar
// en arxius representacions intermitges, en cas contrari, es passa al respectiu
// runner

using namespace Wyrm;

Serializer::Serializer(Book *book) { this->book = book; }

// Carreguem les llibreries
std::filesystem::path Serializer::GetExecPath() {
#ifndef WINDOWS
  std::filesystem::path p =
      std::filesystem::canonical("/proc/self/exe").parent_path();
#else
  WCHAR path[MAX_PATH];
  GetModuleFileNameW(NULL, path, MAX_PATH);
  std::filesystem::path p = std::filesystem::path(path).parent_path();
#endif
  return p;
}
void Serializer::SerializeToFile(WyrmAPI::TreeCode codeInfo,
                                 std::string fileName) {
  FILE *f = fopen((GetExecPath().string() + fileName).c_str(), "wb");
  if (!f) {
    WyrmAPI::Debug::LogError("Error writing to file!");
    return;
  }
  std::cout << fileName.c_str() << std::endl;

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
  for (int i = 0; i < size; i++) {
    char c = s[i];
    fwrite(&c, sizeof(char), 1, f);
  }
}

void Serializer::SerializeAtom(FILE *f, WyrmAPI::Atom *atom) {
  if (atom == NULL) {
    int m1 = -1;
    fwrite(&m1, sizeof(int), 1, f);
  } else {
    int typeId = atom->typeId;
    // std::cout << "typeID: " << typeId << std::endl;
    fwrite(&typeId, sizeof(int), 1, f);
    fwrite(&(atom->data->num), sizeof(int), 1, f);
    for (int i = 0; i < atom->data->num; i++) {
      fwrite((char *)atom->data->data + i, sizeof(char), 1,
             f); // Va en bytes i tal
    }
  }
}

void Serializer::SerializeNode(FILE *f, WyrmAPI::Node *n,
                               std::vector<std::string> &libs) {
  SerializeAtom(f, n->atom);

  //  fwrite(&(n->allocable), sizeof(bool), 1, f);
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

WyrmAPI::TreeCode Serializer::LoadFromFile(std::string fileName) {

  FILE *f = fopen(fileName.c_str(), "rb");
  WyrmAPI::TreeCode result;

  if (!f) {
    WyrmAPI::Debug::LogError("Error reading file " + fileName + "!");
    return result;
  }

  // Carreguem deps
  unsigned int depCount;
  fread(&depCount, sizeof(unsigned int), 1, f);
  for (unsigned int i = 0; i < depCount; i++) {
    std::string lib = ReadString(f);
    result.AddDependency(lib);
  }

  result.root = ReadNode(f);

  return result;
}

std::string Serializer::ReadString(FILE *f) {
  unsigned int size;
  fread(&size, sizeof(unsigned int), 1, f);

  std::string read = "";
  char c;
  for (unsigned int i = 0; i < size; i++) {
    fread(&c, sizeof(char), 1, f);
    read += c;
  }

  return read;
}

WyrmAPI::Node *Serializer::ReadNode(FILE *f) {}

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
