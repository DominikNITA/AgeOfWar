//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_IPURCHASABLE_H
#define AGEOFWAR_IPURCHASABLE_H


class IPurchasable {
public:
    int GetPrice() { return _price; }
protected:
    int _price;
};


#endif //AGEOFWAR_IPURCHASABLE_H
