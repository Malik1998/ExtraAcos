//
// Created by user on 26.11.18.
//

#ifndef TREEDIFFERNTIAL_DATA_H
#define TREEDIFFERNTIAL_DATA_H


#include <string>

class Data {
public:
    enum Type {
        sign_plus,
        sign_mins,
        sign_mult,
        sign_div,
        sin,
        cos,
        const_number,
        variable
    } type;

public:
    Data(Type type);

    Data();

    int getNumber() const;

    void setNumber(int number);

    Type getType() const;

    void setType(Type type);

    std::string toString() const;

private:

    int number;


};


#endif //TREEDIFFERNTIAL_DATA_H
