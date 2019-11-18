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

string format(const string &s) {
    return s;
}

template <class ...Args>
string format(const string &s, Args&&... args) {
    vector<string> input {to_string(std::forward<Args>(args))...};
    stringstream res;
    size_t arg_idx;
    size_t end = -1;
    size_t b_sym, e_sym;
    bool flag = false;
    while ((b_sym = s.find("{", end + 1)) != string::npos) {
        flag ^= true;
        e_sym = s.find("}", end + 1);
        if (e_sym < b_sym || e_sym == string::npos) {
            throw runtime_error("Error");
        }
        flag ^= true;
        size_t beg = end + 1;
        try {
            arg_idx = stoull(s.substr(b_sym + 1) , &end);
            end += b_sym + 1;
        }
        catch (logic_error e) {
            throw runtime_error("Error");
        }
        if (s[end] != '}' || arg_idx >= input.size()) {
            throw runtime_error("Error");
        }
        res << s.substr(beg, b_sym - beg) << input[arg_idx];
    }
    flag ^= (s.find("}", end + 1) != string::npos);
    if (flag)
        throw runtime_error("Error");
    return res.str();
}
