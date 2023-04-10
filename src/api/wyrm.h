
namespace WyrmAPI {
struct Data {
  int num;
  void *data;

  Data(int num) { this->num = num; }

  Data() {}
};
}