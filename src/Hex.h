#pragma once
#include <iostream>
#include <initializer_list>
#include <string>

class Hex {
private:
    unsigned char* dataHex;
    size_t hexSize;

public:
    Hex();
    Hex(const size_t& hexSize, unsigned char defaultValue);
    Hex(const std::initializer_list<unsigned char>& initialValue);
    Hex(const std::string& sourceString);
    Hex(const Hex& other);
    Hex(Hex&& other) noexcept;

    ~Hex();

    std::ostream& print(std::ostream& outputStream) const;

    Hex add(const Hex& other) const;
    Hex remove(const Hex& other) const;
    bool lessThen(const Hex& other) const;
    bool biggerThen(const Hex& other) const;
    bool equal(const Hex& other) const;
};
