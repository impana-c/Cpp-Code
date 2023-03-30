#ifndef ACTOR_H_
#define ACTOR_H_

#include "StudentWorld.h"
#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject{
    public:
        Actor(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 0, double size = 1.0, bool alive = true) : GraphObject(imageID, startX * SPRITE_WIDTH, startY * SPRITE_HEIGHT, dir, depth, size){
            m_world = world;
            m_alive = true;
            m_isSquare = false;
            m_isBaddie = false;
            m_impacted = false;
        }
        virtual void doSomething();
        bool getAlive() const {return m_alive;}
        void setAlive() {m_alive = true;}
        void setDead() {m_alive = false;}
        bool isSquare() const {return m_isSquare;}
        void setIsSquare() {m_isSquare = true;}
        StudentWorld* getWorld() {return m_world;}
        bool isBaddie() const {return m_isBaddie;}
        void setBaddie() {m_isBaddie = true;}
        bool impacted() const {return m_impacted;}
        void setImpacted(bool impacted) {m_impacted = impacted;}
    private:
        StudentWorld* m_world;
        bool m_alive;
        bool m_isSquare;
        bool m_isBaddie;
        bool m_impacted;
};

class Mover: public Actor{
    public:
        Mover(StudentWorld* world, int imageID, int x, int y, int walkDir = right) : Actor(world, imageID, x, y){
            m_walkDir = walkDir;
            m_walkDirValid = true;
            m_onDir = false;
            m_onEvent = false;
            m_state = 0;
            m_ticks_to_move = 0;
        }
        virtual void doSomething();
        int getWalkDir() const {return m_walkDir;}
        void setWalkDir(int d) {m_walkDir = d;}
        bool getOnDir() const {return m_onDir;}
        void setOnDir(bool on) {m_onDir = on;}
        bool getOnEvent() const {return m_onEvent;}
        void setOnEvent(bool on) {m_onEvent = on;}
        int getState() const {return m_state;}
        void setState(int state) {m_state = state;}
        int getTicks() const {return m_ticks_to_move;}
        void setTicks(int ticks) {m_ticks_to_move = ticks;}
    
        int getSpriteDir() const {
            if (getWalkDir() == left)
                return 180;
            else
                return 0;
        }
        void setSpriteDir(){
            if (getWalkDir() == left)
                setDirection(180);
            else
                setDirection(0);
        }
        bool onSquare() const {return getX() % SPRITE_WIDTH == 0 && getY() % SPRITE_HEIGHT == 0;}
        void setRandomDirection() {
            int z = randInt(0,3);
            int x; int y;
            getPositionInThisDirection(z*90, SPRITE_WIDTH, x, y);
            while(getWorld()->checkEmpty(x, y)){
                z = randInt(0,3);
                getPositionInThisDirection(z*90, SPRITE_WIDTH, x, y);
            }
            setWalkDir(z*90);
            setSpriteDir();
        }
        void teleport() {
            int x = randInt(0, 15);
            int y = randInt(0, 15);
            while (getWorld()->checkEmpty(x*SPRITE_WIDTH, y*SPRITE_HEIGHT)){
                x = randInt(0, 15);
                y = randInt(0, 15);
            }
            moveTo(x*SPRITE_WIDTH, y*SPRITE_HEIGHT);
        }
        void atTurningPoint() {
            int x; int y;
            switch (getWalkDir()){
                case up:
                case down:
                    getPositionInThisDirection(getWalkDir(), SPRITE_HEIGHT, x, y);
                    if (getWorld()->checkEmpty(x, y) && onSquare()){
                        getPositionInThisDirection(right, SPRITE_WIDTH, x, y);
                        if (!getWorld()->checkEmpty(x, y))
                            setWalkDir(right);
                        else
                            setWalkDir(left);
                        setSpriteDir();
                    }
                    break;
                case right:
                case left:
                    getPositionInThisDirection(getWalkDir(), SPRITE_WIDTH, x, y);
                    if (getWorld()->checkEmpty(x, y) && onSquare()){
                        getPositionInThisDirection(up, SPRITE_HEIGHT, x, y);
                        if (!getWorld()->checkEmpty(x, y))
                            setWalkDir(up);
                        else
                            setWalkDir(down);
                        setSpriteDir();
                    }
                    break;
            }
        }
        bool getWalkDirValid() const {return m_walkDirValid;}
        void setWalkDirValid(bool valid) {m_walkDirValid = valid;}
    private:
        int m_walkDir;
        bool m_walkDirValid;
        bool m_onDir;
        bool m_onEvent;
        int m_state;
        int m_ticks_to_move;
};

class Avatar: public Mover{
    public:
        Avatar(StudentWorld* world, int imageID, int x, int y, int playerNum) : Mover(world, imageID, x, y, right){
            m_playerNum = playerNum;
            m_dieRoll = 0;
            m_coins = 0;
            m_stars = 0;
            m_vor = false;
            m_changed = false;
            setState(WAITING_TO_ROLL);
        }
        virtual void doSomething();
        int getPlayerNum() const {return m_playerNum;}
        int getDieRoll() const {return m_dieRoll;}
        int getCoins() const {return m_coins;}
        int getStars() const {return m_stars;}
        bool getVor() const {return m_vor;}
        void setCoins(int coins) {m_coins = coins;}
        void setStars(int stars) {m_stars = stars;}
        void setVor (bool vor) {m_vor = vor;}
    
        //To check if a player is "new"
        bool getChanged(){return m_changed;}
        void setChanged(bool x){m_changed = x;}
        
    private:
        int m_playerNum;
        int m_dieRoll;
        int m_coins;
        int m_stars;
        bool m_vor;
        bool m_changed;
};

class Baddie: public Mover{
    public:
        Baddie(StudentWorld* world, int imageID, int x, int y) : Mover(world, imageID, x, y){
            setState(PAUSED);
            m_pauseCounter = 180;
            m_isBowser = false;
            setBaddie();
        }
        virtual void doSomething();
        int getPauseCounter() const {return m_pauseCounter;}
        void setPauseCounter(int pauseNum) {m_pauseCounter = pauseNum;}
        bool isBowser()const {return m_isBowser;}
        void setisBowser(){m_isBowser = true;}
        virtual void doImpacted(){
            teleport();
            setWalkDir(right);
            setSpriteDir();
            setPauseCounter(180);
            setImpacted(false);
        }
        void doBowser(){
            if ((getTicks()==0) && (randInt(1,4)==1)){
                (getWorld()->getSquare(getX(), getY()))->setDead();
                getWorld()->addDroppingSquare(getX(), getY());
                getWorld()->playSound(SOUND_DROPPING_SQUARE_CREATED);
            }
        }
    private:
        int m_pauseCounter;
        bool m_isBowser;
        int m_travelDistance;
};

class Boo: public Baddie{
    public:
        Boo(StudentWorld* world, int imageID, int x, int y) : Baddie(world, imageID, x, y){}
        virtual void doSomething();
};

class Bowser: public Baddie{
    public:
        Bowser(StudentWorld* world, int imageID, int x, int y) : Baddie(world, imageID, x, y){
            setisBowser();
        }
        virtual void doSomething();
};

class Square: public Actor{
    public:
        Square(StudentWorld* world, int imageID, int x, int y) : Actor(world, imageID, x, y, right, 1){
            setIsSquare();
        }
        virtual void doSomething();
};

class CoinSquare: public Square{
    public:
        CoinSquare(StudentWorld* world, int imageID, int x, int y, char color) : Square(world, imageID, x, y){
            m_color = color;
        }
    virtual void doSomething();
    void doBlue(Avatar* player){
        player->setCoins(player->getCoins() + 3);
        getWorld()->playSound(SOUND_GIVE_COIN);
        std::cerr << "ADDED 3 COINS" << std::endl;
    }
    void doRed(Avatar* player){
        if (player->getCoins() >= 3){
            player->setCoins(player->getCoins() - 3);
            getWorld()->playSound(SOUND_TAKE_COIN);
            std::cerr << "TOOK 3 COINS" << std::endl;
        } else{
            std::cerr << "TOOK " << player->getCoins() << " COINS" << std::endl;
            player->setCoins(0);
            getWorld()->playSound(SOUND_TAKE_COIN);
        }
    }
    private:
        char m_color;
};

class StarSquare: public Square{
    public:
        StarSquare(StudentWorld* world, int imageID, int x, int y) : Square(world, imageID, x, y){
        }
        virtual void doSomething();
        void addStar(Avatar* player){
            if (player->getCoins() < 20)
                return;
            else{
                player->setCoins(player->getCoins() - 20);
                player->setStars(player->getStars() + 1);
                getWorld()->playSound(SOUND_GIVE_STAR);
                player->setChanged(true);
                std::cerr << "ADDED 1 STAR" << std::endl;
            }
        }
};

class DirSquare: public Square{
    public:
        DirSquare(StudentWorld* world, int imageID, int x, int y, int forcingDir) : Square(world, imageID, x, y){
            m_forcingDir = forcingDir;
            switch(m_forcingDir){
                case 0:
                    setDirection(0);
                    break;
                case 90:
                    setDirection(90);
                    break;
                case 180:
                    setDirection(180);
                    break;
                case 270:
                    setDirection(270);
                    break;
            }
        }
        virtual void doSomething();
    private:
        int m_forcingDir;
};

class BankSquare: public Square{
    public:
        BankSquare(StudentWorld* world, int imageID, int x, int y) : Square(world, imageID, x, y){}
        virtual void doSomething();
    
        virtual void withdrawBank(Avatar* player){
            player->setCoins(player->getCoins() + getWorld()->getBank());
            getWorld()->setBank(0);
            getWorld()->playSound(SOUND_WITHDRAW_BANK);
        }
    
        virtual void depositBank(Avatar* player){
            int numCoins = player->getCoins();
            if (numCoins < 5){
                player->setCoins(0);
                getWorld()->setBank(getWorld()->getBank() + numCoins);
            }
            else{
                player->setCoins(player->getCoins() - 5);
                getWorld()->setBank(getWorld()->getBank() + 5);
            }
            getWorld()->playSound(SOUND_DEPOSIT_BANK);
        }
};

class EventSquare: public Square{
    public:
        EventSquare(StudentWorld* world, int imageID, int x, int y) : Square(world, imageID, x, y){}
        virtual void doSomething();
        void swapPlayer(Avatar* player){
            Avatar* playerOther;
            if (player->getPlayerNum() == 1)
                playerOther = getWorld()->getPlayer(2);
            else
                playerOther = getWorld()->getPlayer(1);
            
            if(player->getOnEvent() && playerOther->getOnEvent())
                return;

            int tempX = playerOther->getX();
            int tempY = playerOther->getY();
            playerOther->moveTo(player->getX(), player->getY());
            player->moveTo(tempX, tempY);
                
            int tempTicks = playerOther->getTicks();
            playerOther->setTicks(player->getTicks());
            player->setTicks(tempTicks);
                
            int tempState = playerOther->getState();
            playerOther->setState(player->getState());
            player->setState(tempState);
            
            if (playerOther->getState() == WAITING_TO_ROLL)
                playerOther->setChanged(true);
            if (player->getState() == WAITING_TO_ROLL)
                player->setChanged(true);
            
            int tempWalkDir = playerOther->getWalkDir();
            playerOther->setWalkDir(player->getWalkDir());
            player->setWalkDir(tempWalkDir);
            playerOther->setSpriteDir();
            player->setSpriteDir();
        }
        void doSomethingHelper(Avatar* player){
            switch (randInt(1, 3)){
                case 1:
                    player->teleport();
                    player->setWalkDirValid(false);
                    getWorld()->playSound(SOUND_PLAYER_TELEPORT);
                    std::cerr << "TELEPORT" << std::endl;
                    break;
                case 2:
                    swapPlayer(player);
                    getWorld()->playSound(SOUND_PLAYER_TELEPORT);
                    std::cerr << "SWAP" << std::endl;
                    break;
                case 3:
                    if (!player->getVor()){
                        player->setVor(true);
                        getWorld()->playSound(SOUND_GIVE_VORTEX);
                    }
                    std::cerr << "VORTEX" << std::endl;
                    break;
            }
            player->setChanged(true);
        }
    
};
class DroppingSquare: public Square{
    public:
        DroppingSquare(StudentWorld* world, int imageID, int x, int y) : Square(world, imageID, x, y){}
        virtual void doSomething();
};

class Vortex: public Actor{
    public:
        Vortex(StudentWorld* world, int imageID, int x, int y, int fireDir, int playerNum) : Actor(world, imageID, x, y, fireDir){
            setAlive();
            m_fireDir = fireDir;
            m_playerNum = playerNum;
        }
        virtual void doSomething();
    private:
        int m_fireDir;
        int m_playerNum;
};


#endif // ACTOR_H_
