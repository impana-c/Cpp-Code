//
//  Game.h
//  Project 1
//
//  Created by Impana on 1/11/23.
//

#ifndef Game_h
#define Game_h

#include <string>
using namespace std;

class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    string takePlayerTurn();

};

#endif /* Game_h */
