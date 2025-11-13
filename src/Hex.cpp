#include "Hex.h"
#include <iostream>
#include <iomanip>

Hex::Hex() :dataHex(nullptr), hexSize(0) {
    std::cout << "Конструктор по умолчанию" << std::endl;
}

Hex::Hex(const size_t& hexSize, unsigned char defaultValue) {
    std::cout << "Конструктор с заполнением" << std::endl;
    if (defaultValue > 15) {
        throw std::invalid_argument("Значение должно быть в диапазоне от 0 до 15");
    }
    this->hexSize = hexSize;
    this->dataHex = new unsigned char[hexSize];
    for (size_t i = 0; i < hexSize; ++i) {
        this->dataHex[i] = defaultValue;
    }
}


Hex::Hex(const std::initializer_list<unsigned char>& initialValue) {
    std::cout << "Конструктор из списка инициализации" << std::endl;
    hexSize = initialValue.size();
    dataHex = new unsigned char[hexSize];
    size_t index = 0;
    for (const auto& value : initialValue) {
        if (value > 15) {
            delete[] dataHex;
            throw std::invalid_argument("Значение должно быть задано в диапазоне от 0 до 15");
        }
        dataHex[index++] = value;
    }
}

Hex::Hex(const std::string& sourceString) {
    std::cout << "Конструктор с заполнением из строки" << std::endl;
    hexSize = sourceString.size();
    dataHex = new unsigned char[hexSize];
    for (size_t i = 0; i < hexSize; ++i) {
        char c = sourceString[i];
        if (c >= '0' && c <= '9') {
            dataHex[i] = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            dataHex[i] = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            dataHex[i] = c - 'a' + 10;
        } else {
            delete[] dataHex;
            throw std::invalid_argument("Недопустимый символ");
        }
    }
}

Hex::Hex(const Hex& other) {
    std::cout << "Копирующий конструктор" << std::endl;
    hexSize = other.hexSize;
    dataHex = new unsigned char[hexSize];
    for (size_t i = 0; i < hexSize; ++i) {
        dataHex[i] = other.dataHex[i];
    }
}

Hex::Hex(Hex&& other) noexcept {
    std::cout << "Перемещающий конструктор" << std::endl;
    hexSize = other.hexSize;
    dataHex = other.dataHex;
    other.hexSize = 0;
    other.dataHex = nullptr;
}

std::ostream& Hex::print(std::ostream& outputStream) const {
    const char hexChars[] = "0123456789ABCDEF";
    for (size_t i = 0; i < hexSize; ++i) {
        outputStream << hexChars[dataHex[i]];
    }
    return outputStream;
}

Hex::~Hex() {
    std::cout << "Деструктор" << std::endl;
    delete[] dataHex;
    dataHex = nullptr;
    hexSize = 0;
}

Hex Hex::add(const Hex& other) const {
    size_t maxSize = std::max(hexSize, other.hexSize);
    unsigned char* a = new unsigned char[maxSize]();
    unsigned char* b = new unsigned char[maxSize]();
    for (size_t i = 0; i < hexSize; ++i)
        a[maxSize - hexSize + i] = dataHex[i];

    for (size_t i = 0; i < other.hexSize; ++i)
        b[maxSize - other.hexSize + i] = other.dataHex[i];
    unsigned char* result = new unsigned char[maxSize + 1]();
    unsigned char carry = 0;
    for (size_t i = maxSize; i > 0; --i) {
        unsigned char sum = a[i - 1] + b[i - 1] + carry;
        result[i] = sum % 16;
        carry = sum / 16;
    }
    result[0] = carry;
    size_t finalSize;
    size_t startIndex;
    if (carry > 0) {
        finalSize = maxSize + 1;
        startIndex = 0;
    } else {
        finalSize = maxSize;
        startIndex = 1;
    }
    Hex newHex;
    newHex.hexSize = finalSize;
    newHex.dataHex = new unsigned char[finalSize];
    for (size_t i = 0; i < finalSize; ++i)
        newHex.dataHex[i] = result[startIndex + i];
    delete[] a;
    delete[] b;
    delete[] result;
    return newHex;
}

bool Hex::lessThen(const Hex& other) const {
    if (hexSize != other.hexSize) {
        return hexSize < other.hexSize;
    }
    for (size_t i = 0; i < hexSize; ++i) {
        if (dataHex[i] != other.dataHex[i]) {
            return dataHex[i] < other.dataHex[i];
        }
    }
    return false;
}

bool Hex::biggerThen(const Hex& other) const {
    if (hexSize != other.hexSize) {
        return hexSize > other.hexSize;
    }
    for (size_t i = 0; i < hexSize; ++i) {
        if (dataHex[i] != other.dataHex[i]) {
            return dataHex[i] > other.dataHex[i];
        }
    }
    return false;
}

bool Hex::equal(const Hex& other) const {
    if (hexSize != other.hexSize) {
        return false;
    }
    for (size_t i = 0; i < hexSize; ++i) {
        if (dataHex[i] != other.dataHex[i]) {
            return false;
        }
    }
    return true;
}

Hex Hex::remove(const Hex& other) const {
    if (this->lessThen(other)) {
        throw std::invalid_argument("Результат отрицательный");
    }
    size_t maxSize = hexSize;
    unsigned char* a = new unsigned char[maxSize]();
    unsigned char* b = new unsigned char[maxSize]();
    for (size_t i = 0; i < hexSize; ++i)
        a[maxSize - hexSize + i] = dataHex[i];

    for (size_t i = 0; i < other.hexSize; ++i)
        b[maxSize - other.hexSize + i] = other.dataHex[i];
    unsigned char* result = new unsigned char[maxSize]();
    unsigned char borrow = 0;
    for (size_t i = maxSize; i > 0; --i) {
        int diff = a[i - 1] - b[i - 1] - borrow;
        if (diff < 0) {
            diff += 16;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i - 1] = diff;
    }
    size_t startIndex = 0;
    while (startIndex < maxSize - 1 && result[startIndex] == 0) {
        ++startIndex;
    }
    size_t finalSize = maxSize - startIndex;
    Hex newHex;
    newHex.hexSize = finalSize;
    newHex.dataHex = new unsigned char[finalSize];
    for (size_t i = 0; i < finalSize; ++i)
        newHex.dataHex[i] = result[startIndex + i];
    delete[] a;
    delete[] b;
    delete[] result;
    return newHex;
}
