//
// Created by Dominik on 12/28/2020.
//

#ifndef AGEOFWAR_BOARD_HPP
#define AGEOFWAR_BOARD_HPP


#include <vector>
#include <iterator>
#include <memory>
#include <cereal/types/vector.hpp>

#include "../units/IBaseUnit.hpp"
#include "GameLogger.hpp"

#define UNIT_POINTER IBaseUnit*
typedef std::shared_ptr<IBaseUnit> TPtrUnit;
using std::vector;

class Board : public IDrawable {
public:
    //General
    Board(std::shared_ptr<IPlayer> pPlayerOne,std::shared_ptr<IPlayer> pPlayerTwo, std::shared_ptr<GameLogger> pGameLogger,int size = 12);
    Board() { _boardData.insert(_boardData.begin(), 12, nullptr); };
    ~Board();

    //Methods
    vector<std::shared_ptr<IBaseUnit>> getPlayerUnits(std::shared_ptr<IPlayer> pOwner, bool isEnemyBaseDirection);
    void addUnit(std::shared_ptr<IBaseUnit> pUnit, std::shared_ptr<IPlayer> player);
    void moveUnitForward(std::shared_ptr<IBaseUnit> pUnit, int count);
    int findUnitPosition(std::shared_ptr<IBaseUnit> pUnit);
    vector<int> getDistancesToEnemies(std::shared_ptr<IBaseUnit> pUnit);
    void attackRelativePositions(std::shared_ptr<IBaseUnit> pUnit, std::vector<int> attackedPositions);
    bool canPlayerAddUnit(const IPlayer& player);
    void draw() override;
    void clear();
    std::string test() {return p_playerOne->getName();}

private:
    //Variables
    int _size;
    vector<std::shared_ptr<IBaseUnit>> _boardData;
    std::shared_ptr<IPlayer> p_playerOne;
    std::shared_ptr<IPlayer> p_playerTwo;
    std::shared_ptr<GameLogger> p_gameLogger;
    //Methods
    int getDistanceValueFromIndexes(int index1, int index2);
    std::string getUnitStringWithPosition(std::shared_ptr<IBaseUnit> unit, int position);

    friend class cereal::access;

    template<class Archive> void serialize(Archive & archive){
        archive(CEREAL_NVP(_size), CEREAL_NVP(p_playerOne), CEREAL_NVP(p_playerTwo),CEREAL_NVP(p_gameLogger));
    }
};


#endif //AGEOFWAR_BOARD_HPP
