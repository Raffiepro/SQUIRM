#include "literals.h"

#include "string.h"

ThatAPI::Literal Base::GIntLit() {

  return ThatAPI::Literal("Integer",
                          [](char *c, int size) -> ThatAPI::LexerInfo {
                            std::string num = "";

                            int i = 0;
                            while (c[i] >= '0' && c[i] <= '9') {
                              num += c[i];
                              i++;
                            }

                            return ThatAPI::LexerInfo(num, i, true);
                          });
}
