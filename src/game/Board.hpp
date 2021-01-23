//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_BOARD_HPP
#define AGEOFWAR_BOARD_HPP


#include <vector>
#include <iterator>
#include "../units/IBaseUnit.hpp"
#include "GameLogger.hpp"
#include <memory>

using std::vector;

class Board : public IDrawable {
public:
    //General
    Board(std::shared_ptr<IPlayer> pPlayerOne,std::shared_ptr<IPlayer> pPlayerTwo, GameLogger* pGameLogger,int size = 12);
    ~Board();
    //Methods
    vector<IBaseUnit*> getPlayerUnits(std::shared_ptr<IPlayer> pOwner, bool isEnemyBaseDirection);
    void addUnit(IBaseUnit* pUnit, std::shared_ptr<IPlayer> player);
    void moveUnitForward(IBaseUnit* pUnit, int count);
    int findUnitPosition(IBaseUnit* pUnit);
    vector<int> getDistancesToEnemies(IBaseUnit* pUnit);
    void attackRelativePositions(IBaseUnit* pUnit, std::vector<int> attackedPositions);
    bool canPlayerAddUnit(std::shared_ptr<IPlayer>player);
    void draw() override;
    void clear();

private:
    //Variables
    int _size;
    vector<IBaseUnit*> _boardData;
    int* test = nullptr;
    std::shared_ptr<IPlayer> p_PlayerOne;
    std::shared_ptr<IPlayer> p_PlayerTwo;
    GameLogger* p_gameLogger;
    //Methods
    int getDistanceValueFromIndexes(int index1, int index2);
    std::string getUnitStringWithPosition(IBaseUnit* unit, int position);
};


#endif //AGEOFWAR_BOARD_HPP
