//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_IPURCHASABLE_H
#define AGEOFWAR_IPURCHASABLE_H

//https://stackoverflow.com/questions/1390913/are-static-variables-in-a-base-class-shared-by-all-derived-classes

template <typename T>
class IPurchasable {
public:
    int GetPrice() { return _price; }
protected:
    static int _price;
};

template <typename T> int IPurchasable<T>::_price(0);


#endif //AGEOFWAR_IPURCHASABLE_H
