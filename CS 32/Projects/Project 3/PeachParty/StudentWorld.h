#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include <string>
#include <list>

class Actor;
class Avatar;

const int WAITING_TO_ROLL = 0;
const int WALKING = 1;
const int PAUSED = 2;
const int NUMPLAYERS = 2;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld{
    public:
    StudentWorld(std::string assetPath);
        ~StudentWorld();
        virtual int init();
        virtual int move();
        virtual void cleanUp();

        Actor* getSquare(int x, int y);
        void addDroppingSquare(int x, int y);
        void addVortex(int x, int y, int dir, int playerNum);
    
        bool checkEmpty(int x, int y) {return bd.getContentsOf(x/SPRITE_WIDTH,y/SPRITE_HEIGHT) == Board::GridEntry::empty;}
    
        Avatar* getPlayer (int playerNum) const {
            if (playerNum==1)
                return peach;
            return yoshi;
        }
        
        int getBank() const {return m_bank;}
        void setBank(int x) {m_bank = x;}
    
        Actor* overlapBaddie(int x, int y);
        
    
        //TODO: maybe delete later
        std::string getGridEntry(int x, int y) {
            switch (bd.getContentsOf(x/SPRITE_WIDTH,y/SPRITE_HEIGHT)){
                case Board::empty:
                    return "empty";
                    break;
                case Board::player:
                    return "player";
                    break;
                case Board::blue_coin_square:
                    return "blue_coin_square";
                    break;
                case Board::red_coin_square:
                    return "red_coin_square";
                    break;
                case Board::star_square:
                    return "star_square";
                    break;
                case Board::up_dir_square:
                    return "up_dir_square";
                    break;
                case Board::down_dir_square:
                    return "down_dir_square";
                    break;
                case Board::left_dir_square:
                    return "left_dir_square";
                    break;
                case Board::right_dir_square:
                    return "right_dir_square";
                    break;
                case Board::event_square:
                    return "event_square";
                    break;
                case Board::bank_square:
                    return "bank_square";
                    break;
                case Board::bowser:
                    return "bowser";
                    break;
                case Board::boo:
                    return "boo";
                    break;
            }
        }
    private:
        std::list<Actor*> actors;
        Board bd;
        Avatar* peach;
        Avatar* yoshi;
        int m_bank;
};

#endif // STUDENTWORLD_H_
