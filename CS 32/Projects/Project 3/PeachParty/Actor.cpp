#include "Actor.h"
#include "StudentWorld.h"

void Actor::doSomething(){}

void Mover::doSomething(){
    if (!getWalkDirValid()){
        setRandomDirection();
        setWalkDirValid(true);
    }
}

void Avatar::doSomething(){
    if (getState() == WAITING_TO_ROLL){
        Mover::doSomething();
        int tempKey = getWorld()->getAction(m_playerNum);
        if (tempKey == ACTION_ROLL){
            m_dieRoll = randInt(1, 10);
            setTicks(getDieRoll() * 8);
            setState(WALKING);
            setChanged(false);
        } else if (tempKey == ACTION_FIRE){
            //setVor(true);
            if (getVor()) {
                int x = getX(); int y = getY();
                getPositionInThisDirection(getWalkDir(), SPRITE_WIDTH, x, y);
                getWorld()->addVortex(x, y, getWalkDir(), getPlayerNum());
            }
        } else {
            return;
        }
    }
    int x = getX();
    int y = getY();
    if (getState() == WALKING) {
        //1. If the Avatar is directly on top of a directional square 
        if (getOnDir()){}
        else {
        //2. Else if the Avatar is directly on top of a square at a fork (with multiple directions where it could move next)
            int countPossibleDirs = 0;
            for (int i = 0; i <= 270; i += 90){
                getPositionInThisDirection(i, 16, x, y);
                if (!(getWorld()->checkEmpty(x, y)) && onSquare()){
                    countPossibleDirs++;
                }
            }
            if (countPossibleDirs >= 3){
                switch(getWorld()->getAction(m_playerNum)){
                    case ACTION_LEFT:
                        getPositionInThisDirection(left, SPRITE_HEIGHT, x, y);
                        if (getWorld()->checkEmpty(x, y) || (getWalkDir() == right))
                            return;
                        setWalkDir(left);
                        setSpriteDir();
                        break;
                    case ACTION_UP:
                        getPositionInThisDirection(up, SPRITE_HEIGHT, x, y);
                        if (getWorld()->checkEmpty(x, y) || (getWalkDir() == down))
                            return;
                        setWalkDir(up);
                        setSpriteDir();
                        break;
                    case ACTION_RIGHT:
                        getPositionInThisDirection(right, SPRITE_HEIGHT, x, y);
                        if (getWorld()->checkEmpty(x, y) || (getWalkDir() == left))
                            return;
                        setWalkDir(right);
                        setSpriteDir();
                        break;
                    case ACTION_DOWN:
                        getPositionInThisDirection(down, SPRITE_HEIGHT, x, y);
                        if (getWorld()->checkEmpty(x, y) || (getWalkDir() == up))
                            return;
                        setWalkDir(down);
                        setSpriteDir();
                        break;
                    default:
                        return;
                }
            }
        //3. Else if the Avatar can't continue moving forward in its current direction:
            else if (onSquare()) atTurningPoint();
        }
//        Move two pixels in the walk direction. Decrement the ticks_to_move count by 1.
//        If ticks_to_move is 0 then:
//            Change the Avatar's state to the waiting to roll state.
        getPositionInThisDirection(getWalkDir(), 2, x, y);
        setOnDir(false);
        setOnEvent(false);
        moveTo(x,y);
        setTicks(getTicks()-1);
        if (getTicks()==0){
            setState(WAITING_TO_ROLL);
        }
    }
}

void Baddie::doSomething(){
    if (impacted())
        doImpacted();
    if (getState() == PAUSED){
        setPauseCounter(getPauseCounter()-1);
        if (getPauseCounter() <= 0){
            if (isBowser())
                m_travelDistance = randInt(1,10);
            else
                m_travelDistance = randInt(1,3);
            setTicks(m_travelDistance * 8);
            setRandomDirection();
            setSpriteDir();
            setState(WALKING);
        }
    }
    if (getState() == WALKING){
        int x = getX();
        int y = getY();
        int countPossibleDirs = 0;
        for (int i = 0; i <= 270; i += 90){
            getPositionInThisDirection(i, 16, x, y);
            if (!(getWorld()->checkEmpty(x, y)) && onSquare()){
                countPossibleDirs++;
            }
        }
        if (countPossibleDirs >= 3 && onSquare()){
            setRandomDirection();
            setSpriteDir();
        }
        else if (onSquare()) atTurningPoint();
        getPositionInThisDirection(getWalkDir(), 2, x, y);
        setOnDir(false);
        moveTo(x,y);
        setTicks(getTicks()-1);
        if (getTicks()==0){
            setState(PAUSED);
            setPauseCounter(180);
            if (isBowser())
                doBowser();
        }
    }
}
void Boo::doSomething(){
    if (getState() == PAUSED){
        for (int i=1; i<=NUMPLAYERS; i++){
            Avatar* player = getWorld()->getPlayer(i);
            if ( (player->getX()==getX() && player->getY()==getY()) && player->getState()==WAITING_TO_ROLL && !(player->getChanged()) ) {
                std::cerr << "LANDED ON BOO" << std::endl;
                
                Avatar* playerOther;
                if (i==1) playerOther = getWorld()->getPlayer(2);
                else playerOther = getWorld()->getPlayer(1);
            
                switch (randInt(1,2)){
                    case 1: {
                        int tempCoins = playerOther->getCoins();
                        playerOther->setCoins(player->getCoins());
                        player->setCoins(tempCoins);
                        std::cerr << "SWAPPED COINS" << std::endl;
                        break; }
                    case 2: {
                        int tempStars = playerOther->getStars();
                        playerOther->setStars(player->getStars());
                        player->setStars(tempStars);
                        std::cerr << "SWAPPED STARS" << std::endl;
                        break; }
                }
                player->setChanged(true);
                getWorld()->playSound(SOUND_BOO_ACTIVATE);
            }
        }
    }
    Baddie::doSomething();
}

void Bowser::doSomething(){
    if (getState() == PAUSED){
        for (int i=1; i<=NUMPLAYERS; i++){
            Avatar* player = getWorld()->getPlayer(i);
            if ( (player->getX()==getX() && player->getY()==getY()) && player->getState()==WAITING_TO_ROLL && !(player->getChanged()) ) {
                std::cerr << "LANDED ON BOWSER" << std::endl;
                switch (randInt(1,2)){
                    case 1:
                        player->setCoins(0);
                        player->setStars(0);
                        std::cerr << "TOOK AWAY ALL COINS AND STARS" << std::endl;
                        player->setChanged(true);
                        getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
                        break;
                    default:
                        return;
                }
            }
        }
    }
    Baddie::doSomething();
}

void Square::doSomething(){
    if (!getAlive())
        return;
}
void CoinSquare::doSomething(){
    if (isBaddie()) return;
    Square::doSomething();
    for (int i = 1; i <= NUMPLAYERS; i++){
        Avatar* player = getWorld()->getPlayer(i);
        if ((player->getX() == getX()) && (player->getY() == getY())){
            if (player->getState() == WAITING_TO_ROLL && !(player->getChanged())){
                if (m_color == 'b') {
                    doBlue(player);
                }
                if (m_color == 'r') {
                    if (player->getCoins() == 0) return;
                    doRed(player);
                }
                player->setChanged(true);
            }
        }
    }
}

void StarSquare::doSomething(){
    if (isBaddie()) return;
    Square::doSomething();
    for (int i = 1; i <= NUMPLAYERS; i++){
        Avatar* player = getWorld()->getPlayer(i);
        if ((player->getX() == getX()) && (player->getY() == getY())){
            if (player->getState() == WALKING)
                addStar(player);
            else {
                addStar(player);
                player->setChanged(true);
            }
        }
    }
}

void DirSquare::doSomething(){
    if (isBaddie()) return;
    Square::doSomething();
    for (int i = 1; i <= NUMPLAYERS; i++){
        Avatar* player = getWorld()->getPlayer(i);
        if (player->onSquare() && player->getX() == getX() && player->getY() == getY()){
            player->setWalkDir(m_forcingDir);
            player->setSpriteDir();
            player->setOnDir(true);
        }
    }
}

void BankSquare::doSomething(){
    if (isBaddie()) return;
    Square::doSomething();
    for (int i = 1; i <= NUMPLAYERS; i++){
        Avatar* player = getWorld()->getPlayer(i);
        if ((player->getX() == getX()) && (player->getY() == getY())){
            if (player->getState() == WAITING_TO_ROLL){
                if (getWorld()->getBank() == 0) return;
                withdrawBank(player);
                player->setChanged(true);
            }
            else{
                if (player->getCoins() == 0) return; //nothing to deposit if there are no coins
                depositBank(player);
            }
        }
    }
}

void EventSquare::doSomething(){
    if (isBaddie()) return;
    Square::doSomething();
    for (int i = 1; i <= NUMPLAYERS; i++){
        Avatar* player = getWorld()->getPlayer(i);
        if ((player->getX() == getX()) && (player->getY() == getY()) && (player->getState() == WAITING_TO_ROLL) && !(player->getChanged())){
            player->setOnEvent(true);
            doSomethingHelper(player);
        }
    }
}

void DroppingSquare::doSomething(){
    Square::doSomething();
    for (int i = 1; i <= NUMPLAYERS; i++){
        Avatar* player = getWorld()->getPlayer(i);
        if ((player->getX() == getX()) && (player->getY() == getY()) && (player->getState() == WAITING_TO_ROLL) && !(player->getChanged())){
            switch(randInt(1,2)){
                case 1: {
                    if (player->getCoins() == 0) return;
                    if (player->getCoins() >= 10) {
                        std::cerr<<"TOOK 10 COINS from " << player->getCoins() << std::endl;
                        player->setCoins(player->getCoins() - 10);
                    } else{
                        std::cerr<<"TOOK " << player->getCoins() << " COINS" << std::endl;
                        player->setCoins(0);
                    }
                    break; }
                case 2: {
                    std::cerr<<"TOOK STAR"<<std::endl;
                    if (player->getStars() == 0) return;
                    player->setStars(player->getStars() - 1);
                    break; }
            }
            player->setChanged(true);
            getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
        }
    }
}

void Vortex::doSomething(){
    if (!getAlive())
        return;
    if (getX() < 0 || getY() < 0 || getX() >= VIEW_WIDTH || getY() >= VIEW_HEIGHT){
        setDead();
        return;
    }
    
    moveAtAngle(m_fireDir, 2);
    std::cerr << "VORTEX MOVED" << std::endl;

    if (getWorld()->overlapBaddie(getX(), getY()) != nullptr){
        std::cerr << "BADDIE HIT" << std::endl;
        setDead();
        getWorld()->playSound(SOUND_HIT_BY_VORTEX);
    }
    
    getWorld()->getPlayer(m_playerNum)->setVor(false);
}
