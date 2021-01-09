#include <vector>

class A {
public:
 std::vector<int*> values;
 void add(int x) { values.push_back(new int(x)); }
};


int main() {
 A a, sliced;
 a.add(0); a.add(1); a.add(2); a.add(3); a.add(4); a.add(5);
 sliced.values = slice(a.values, 1, 1, 4);
 *(sliced.values[0]) = 800;
 std::cout << *(a.values[1]) << std::endl;
 return 0;
}