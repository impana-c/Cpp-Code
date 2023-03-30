#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <list>
using namespace std;

GameWorld* createStudentWorld(string assetPath){
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath) : GameWorld(assetPath){
    m_bank = 0;
}

int StudentWorld::init(){
    string board_file = assetPath() + "board0" + to_string(getBoardNumber()) + ".txt";
    Board::LoadResult result = bd.loadBoard(board_file);
    if (result == Board::load_fail_file_not_found)
        cerr << "Could not find board0" + to_string(getBoardNumber()) + ".txt data file\n";
    else if (result == Board::load_fail_bad_format)
        cerr << "Your board was improperly formatted\n";
    else if (result == Board::load_success)
        cerr << "Successfully loaded board\n";
    
    for (int y = 0; y < BOARD_HEIGHT; y++){
        for (int x = 0; x < BOARD_WIDTH; x++){
            switch (bd.getContentsOf(x, y)){
                case Board::empty:
                    break;
                case Board::player:
                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, x, y, 'b'));
                    peach = new Avatar(this, IID_PEACH, x, y, 1);
                    actors.push_back(peach);
                    yoshi = new Avatar(this, IID_YOSHI, x, y, 2);
                    actors.push_back(yoshi);
                    break;
                case Board::blue_coin_square:
                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, x, y, 'b'));
                    break;
                case Board::red_coin_square:
                    actors.push_back(new CoinSquare(this, IID_RED_COIN_SQUARE, x, y, 'r'));
                    break;
                case Board::star_square:
                    actors.push_back(new StarSquare(this, IID_STAR_SQUARE, x, y));
                    break;
                case Board::up_dir_square:
                    actors.push_back(new DirSquare(this, IID_DIR_SQUARE, x, y, 90));
                    break;
                case Board::down_dir_square:
                    actors.push_back(new DirSquare(this, IID_DIR_SQUARE, x, y, 270));
                    break;
                case Board::left_dir_square:
                    actors.push_back(new DirSquare(this, IID_DIR_SQUARE, x, y, 180));
                    break;
                case Board::right_dir_square:
                    actors.push_back(new DirSquare(this, IID_DIR_SQUARE, x, y, 0));
                    break;
                case Board::event_square:
                    actors.push_back(new EventSquare(this, IID_EVENT_SQUARE, x, y));
                    break;
                case Board::bank_square:
                    actors.push_back(new BankSquare(this, IID_BANK_SQUARE, x, y));
                    break;
                case Board::bowser:
                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, x, y, 'b'));
                    actors.push_back(new Bowser(this, IID_BOWSER, x, y));
                    break;
                case Board::boo:
                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, x, y, 'b'));
                    actors.push_back(new Boo(this, IID_BOO, x, y));
                    break;
            }
        }
    }
    startCountdownTimer(100);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move(){
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.
    
    list<Actor*>::iterator it = actors.begin();
    while ( it != actors.end() ){
        (*it)->doSomething();
        if (!(*it)->getAlive()){ 
            delete *it;
            it=actors.erase(it);
            cerr << "DELETED ACTOR" << endl;
        }
        it++;
    }
    string statText;
    //TODO: Implement for Yoshi
    
    statText = "P1 Roll: " + to_string((peach->getTicks()/8)) + " Stars: " + to_string(peach->getStars()) + " $$: " + to_string(peach->getCoins());
    if (peach->getVor())
        statText += " VOR";
    statText += " | Time: " + to_string(timeRemaining()) + " | Bank: " + to_string(getBank()) + " | P2 Roll: " + to_string((yoshi->getTicks()/8)) + " Stars: " + to_string(yoshi->getStars()) + " $$: " + to_string(yoshi->getCoins());
    if (yoshi->getVor())
        statText += + " VOR ";
    setGameStatText(statText);
    
    if (timeRemaining() <= 0){
        if ( ((20*peach->getStars()) + peach->getCoins()) > ((20*yoshi->getStars()) + yoshi->getCoins())){
            playSound(SOUND_GAME_FINISHED);
            setFinalScore(peach->getStars(), peach->getCoins());
            return GWSTATUS_PEACH_WON;
        } else if ( ((20*peach->getStars()) + peach->getCoins()) < ((20*yoshi->getStars()) + yoshi->getCoins())){
            playSound(SOUND_GAME_FINISHED);
            setFinalScore(yoshi->getStars(), yoshi->getCoins());
            return GWSTATUS_YOSHI_WON;
        } else {
            switch (randInt(1,2)){
                case 1:
                    playSound(SOUND_GAME_FINISHED);
                    setFinalScore(peach->getStars(), peach->getCoins());
                    return GWSTATUS_PEACH_WON;
                    break;
                case 2:
                    playSound(SOUND_GAME_FINISHED);
                    setFinalScore(yoshi->getStars(), yoshi->getCoins());
                    return GWSTATUS_YOSHI_WON;
                    break;
            }
        }
    }
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp(){
    list<Actor*>::iterator it = actors.begin();

    while ( it != actors.end() ){
        delete *it;
        actors.erase(it);
        it++;
    }
    peach = nullptr;
    delete peach;
    yoshi = nullptr;
    delete yoshi;
    actors.clear();
}

StudentWorld:: ~StudentWorld(){
    if (!actors.empty())
        cleanUp();
}

Actor* StudentWorld::getSquare(int x, int y){
    list<Actor*>::iterator it = actors.begin();
    while ( it != actors.end() ){
        if ((*it)->getX()==x && (*it)->getY()==y && (*it)->isSquare())
            return *it;
        it++;
    }
    it--;
    return *it;
}

void StudentWorld::addDroppingSquare(int x, int y){
    actors.push_back(new DroppingSquare(this, IID_DROPPING_SQUARE, x/SPRITE_WIDTH, y/SPRITE_HEIGHT));
    playSound(SOUND_DROPPING_SQUARE_CREATED);
}

void StudentWorld::addVortex(int x, int y, int dir, int playerNum){
    actors.push_back(new Vortex(this, IID_VORTEX, x/SPRITE_WIDTH, y/SPRITE_HEIGHT, dir, playerNum));
    playSound(SOUND_PLAYER_FIRE);
}

Actor* StudentWorld::overlapBaddie(int vorX, int vorY){
    int vorXTop = vorX+SPRITE_WIDTH-1;
    int vorYTop = vorY+SPRITE_HEIGHT-1;
    list<Actor*>::iterator it = actors.begin();
    while ( it != actors.end() ){
        if ((*it)->isBaddie()){
            int leftEdge = (*it)->getX(); int rightEdge = (*it)->getX()+SPRITE_WIDTH-1;
            int bottomEdge = (*it)->getY(); int topEdge = (*it)->getY()+SPRITE_HEIGHT-1;
            if (rightEdge >= vorX && rightEdge <= vorXTop){
                if (bottomEdge >= vorY && bottomEdge <= vorYTop){
                    (*it)->setImpacted(true);
                    return (*it);
                }
                if (topEdge <= vorYTop && topEdge >= vorY){
                    (*it)->setImpacted(true);
                    return (*it);
                }
            }
            if (leftEdge <= vorXTop && leftEdge >= vorX){
                if (bottomEdge >= vorY && bottomEdge <= vorYTop){
                    (*it)->setImpacted(true);
                    return (*it);
                }
                if (topEdge <= vorYTop && topEdge >= vorY){
                    (*it)->setImpacted(true);
                    return (*it);
                }
            }
        }
        it++;
    }
    return nullptr;
}



