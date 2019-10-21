#include <iostream>
#include "LinearAllocator.h"

using namespace std;

int main(int argc, char *argv[]) {
    LinearAllocator x;
    try {
        x = LinearAllocator(atoi(argv[1]));
    } catch(bad_alloc e) {
        cout << e.what() << endl;
        return 1;
    }

    for (int i = 2; i < argc; ++i) {
        string buf = argv[i];
        if (buf == "r") {
            x.reset();
        } else {
            size_t amo = stoi(buf);
            if (static_cast<void *>(x.alloc(amo)) != nullptr)
            {
                cout << "allocated " << amo << " byte";
                if (amo > 1)
                    cout << "s";
                cout << endl;
            } else {
                cout << "not enough space" << endl;
            }
        }
    }

}