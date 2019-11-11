#include <iostream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    std::ostream &out;
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out_) : out(out_) {}

    template <class T>
    Error save(T& object) { return object.serialize(*this);}

    template <class... ArgsT>
    Error operator()(ArgsT&&... args) { return process(args...);}

private:
    Error process() { return Error::NoError;}

    Error process(uint64_t val) {
        out << val << Separator;
        return Error::NoError;
    }

    Error process(bool val) {
        out << (val ? "true" : "false") << Separator;
        return Error::NoError;
    }

    template <class T, class... Args>
    Error process(T&& val, Args&&... args) {
        return (process(val) == Error::NoError) ? process(std::forward<Args>(args)...) : Error::CorruptedArchive;
    }
};

class Deserializer
{
    std::istream& in;
public:
    explicit Deserializer(std::istream& in_) : in(in_) {}

    template <class T>
    Error load(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args) {
        return process(args...);
    }

private:
    Error process() {
        return Error::NoError;
    }

    Error process(uint64_t& value) {
        std::string t;
        in >> t;

        if (t[0] == '-')
            return Error::CorruptedArchive;
        value = std::stoull(t.c_str());
        return Error::NoError;
    }

    Error process(bool& value) {
        std::string t;
        in >> t;
        if (t == "true")
            value = true;
        else if (t == "false")
            value = false;
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    }

    template <class T, class... Args>
    Error process(T&& val, Args&&... args) {
        return (process(val) == Error::NoError) ? process(std::forward<Args>(args)...) : Error::CorruptedArchive;
    }
};
