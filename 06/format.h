#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

template <class T>
string to_string(const T &t) {
    stringstream ss;
    ss << t;
    return ss.str();
}

template <class ...Args>
string format(const string &s, Args&&... args) {
    vector<string> input {to_string(forward<Args>(args))...};
    stringstream res;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '}')
            throw runtime_error("Error");
        if (s[i] == '{') {
            size_t arg_idx, end;
            try {
                arg_idx = stoull(s.substr(++i), &end);
            } catch (logic_error &e) {
                throw runtime_error("Error");
            }
            i += end;
            if (arg_idx >= input.size() || s[i] != '}')
                throw runtime_error("Error");
            res << input[arg_idx];
        } else {
            res << s[i];
        }
    }
    return res.str();
}
