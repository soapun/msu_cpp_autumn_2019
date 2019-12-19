#include <iostream>
#include <fstream>

using namespace std;

int main(const int argc, const char *argv[]) {
    ofstream f(argv[1], ios::binary);
    for (size_t i; i < atoi(argv[2]) * (1 << 20); ++i) {
        uint64_t x = rand();
        f.write(reinterpret_cast<const char *>(&x), sizeof(uint64_t));
    }
    f.close();
    return 0;
}