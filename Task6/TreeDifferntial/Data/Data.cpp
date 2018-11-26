//
// Created by user on 26.11.18.
//

#include "Data.h"

int Data::getNumber() const {
    return number;
}

void Data::setNumber(int number) {
    Data::number = number;
}


Data::Type Data::getType() const {
    return type;
}

void Data::setType(Data::Type type) {
    Data::type = type;
}

Data::Data(Data::Type type) : type(type) {}

Data::Data() {}

std::string Data::toString() const {
    if (type != const_number) {
        switch (type) {
            case sign_mult:
                return "*";
            case sign_plus:
                return "+";
            case sign_mins:
                return "-";
            case sign_div:
                return "/";
            case variable:
                return "x";
            case sin:
                return "sin";
            case cos:
                return "cos";
        }
    } else {
        return std::to_string(number);
    }
}
