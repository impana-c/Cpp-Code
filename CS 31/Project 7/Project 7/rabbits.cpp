// rabbits.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in the arena
const int MAXCOLS = 25;               // max number of columns in the arena
const int MAXRABBITS = 100;           // max number of rabbits allowed

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

const int EMPTY      = 0;
const int HAS_POISON = 1;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Rabbit declaration.

class Rabbit
{
  public:
      // Constructor
    Rabbit(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
      // TODO: You'll probably find that a rabbit object needs additional
      // data members to support your implementation of the behavior affected
      // by poisoned carrots.
    int    m_turns;
    int    m_carrotsEaten;
    bool   m_go;
};

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    string dropPoisonedCarrot();
    string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     rabbitCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfRabbitsAt(int r, int c) const;
    void    display(string msg) const;

      // Mutators
    void setCellStatus(int r, int c, int status);
    bool addRabbit(int r, int c);
    bool addPlayer(int r, int c);
    void moveRabbits();

  private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Rabbit* m_rabbits[MAXRABBITS];
    int     m_nRabbits;
    int     m_turns;

      // Helper functions
    void checkPos(int r, int c, string functionName) const;
    bool isPosInBounds(int r, int c) const;
};

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

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool decodeDirection(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Rabbit implementation
///////////////////////////////////////////////////////////////////////////

Rabbit::Rabbit(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A rabbit must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Rabbit created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_carrotsEaten = 0;
    m_go = true;
    m_turns = 0;
}

int Rabbit::row() const
{
    return m_row;
}

int Rabbit::col() const
{
      // DONE: TRIVIAL:  Return what column the Rabbit is at
      // Delete the following line and replace it with the correct code.
    return m_col;
}

bool Rabbit::isDead() const
{
      // DONE: Return whether the Rabbit is dead
      // Delete the following line and replace it with the correct code.
    return (m_carrotsEaten >= 2);  // This implementation compiles, but is incorrect.
}

void Rabbit::move()
{
    m_turns++;
      // DONE:
      //   Return without moving if the rabbit has eaten one poisoned
      //   carrot (so is supposed to move only every other turn) and
      //   this is a turn it does not move.
    if (m_carrotsEaten == 1) {
        if (m_go == false){
            m_go = true;
            return;
        }
        m_go = false;
    }
      //   Otherwise, attempt to move in a random direction; if can't
      //   move, don't move.  If it lands on a poisoned carrot, eat the
      //   carrot and remove it from the game (so it is no longer on that
      //   grid point).
    
    int randDir = randInt(0,3);
    switch (randDir){
        case NORTH:
            if (m_row-1 >= 1){
                m_row--;
            }
            break;
        case SOUTH:
            if (m_row+1 <= m_arena->rows()){
                m_row++;
            }
            break;
        case EAST:
            if (m_col+1 <= m_arena->cols()){
                m_col++;
            }
            break;
        case WEST:
            if (m_col-1 >= 1){
                m_col--;
            }
            break;
    }
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON){
        m_carrotsEaten++;
        m_go = false;
        m_arena->setCellStatus(m_row, m_col, EMPTY);
    }
    
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
      // DONE: TRIVIAL:  Return what row the Player is at
      // Delete the following line and replace it with the correct code.
    return m_row;
}

int Player::col() const
{
      // DONE: TRIVIAL:  Return what column the Player is at
      // Delete the following line and replace it with the correct code.
    return m_col;
}

string Player::dropPoisonedCarrot()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        return "There's already a poisoned carrot at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_POISON);
    return "A poisoned carrot has been dropped.";
}

string Player::move(int dir)
{
      // DONE:  Attempt to move the player one step in the indicated
      //        direction.  If this fails,
      //        return "Player couldn't move; player stands."
      //        A player who moves onto a rabbit, and this
      //        returns "Player walked into a rabbit and died."
      //        Otherwise, return one of "Player moved north.",
      //        "Player moved east.", "Player moved south.", or
      //        "Player moved west."
    if (m_arena->numberOfRabbitsAt(m_row, m_col) > 0){
        m_dead = true;
        return "Player walked into a rabbit and died.";
    }
    switch (dir){
        case NORTH:
            if (attemptMove(*m_arena, NORTH, m_row, m_col))
              return "Player moved north.";
            break;
        case SOUTH:
            if (attemptMove(*m_arena, SOUTH, m_row, m_col))
                return "Player moved south.";
            break;
        case EAST:
            if (attemptMove(*m_arena, EAST, m_row, m_col))
                return "Player moved east.";
            break;
        case WEST:
            if (attemptMove(*m_arena, WEST, m_row, m_col))
                return "Player moved west.";
            break;
    }
    return "Player couldn't move; player stands.";
}

bool Player::isDead() const
{
      // DONE: Return whether the Player is dead
      // Delete the following line and replace it with the correct code.
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRabbits = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    // DONE:  Deallocate the player and all remaining dynamically allocated
    //        rabbits.
    delete m_player;
    for (int i=0; i < m_nRabbits; i++){
        delete m_rabbits[i];
    }
}

int Arena::rows() const
{
      // DONE: TRIVIAL:  Return the number of rows in the arena
      // Delete the following line and replace it with the correct code.
    return m_rows;
}

int Arena::cols() const
{
      // DONE: TRIVIAL:  Return the number of columns in the arena
      // Delete the following line and replace it with the correct code.
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::rabbitCount() const
{
      // DONE: TRIVIAL:  Return the number of rabbits in the arena
      // Delete the following line and replace it with the correct code.
    return m_nRabbits;
    
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c, "Arena::getCellStatus");
    return m_grid[r-1][c-1];
}

int Arena::numberOfRabbitsAt(int r, int c) const
{
    int count = 0;
    for (int i=0; i<m_nRabbits; i++){
        if ( (m_rabbits[i]->row() == r) && (m_rabbits[i]->col() == c) ){
            count++;
        }
    }
      // DONE:  Return the number of rabbits at row r, column c
      // Delete the following line and replace it with the correct code.
    return count;  // This implementation compiles, but is incorrect.
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill displayGrid with dots (empty) and stars (poisoned carrots)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');

      // Indicate each rabbit's position
      // DONE:  If one rabbit is at some grid point, set the displayGrid char
      //        to 'R'.  If it's 2 though 8, set it to '2' through '8'.
      //        For 9 or more, set it to '9'.

    for (r = 1; r <= rows(); r++){
        for (c = 1; c <= cols(); c++) {
            if (numberOfRabbitsAt(r, c) == 1){
                displayGrid[r-1][c-1] = 'R';
            } else if ((numberOfRabbitsAt(r, c) >= 2) && (numberOfRabbitsAt(r, c) <= 8)){
                displayGrid[r-1][c-1] = '0' + numberOfRabbitsAt(r, c);
            } else if (numberOfRabbitsAt(r, c) >= 9){
                displayGrid[r-1][c-1] = '9';
            }
        }
    }
    
      // Indicate the player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;

      // Write message, rabbit, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << rabbitCount() << " rabbits remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Arena::setCellStatus");
    m_grid[r-1][c-1] = status;
}

bool Arena::addRabbit(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a rabbit on a spot with a poisoned carrot
    if (getCellStatus(r, c) != EMPTY)
        return false;

      // Don't add a rabbit on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;

      // If there are MAXRABBITS existing rabbits, return false.  Otherwise,
      // dynamically allocate a new rabbit at coordinates (r,c).  Save the
      // pointer to newly allocated rabbit and return true.
      // DONE:  Implement this.
    
    if (m_nRabbits == MAXRABBITS){
        return false;
    }
    m_rabbits[m_nRabbits] = new Rabbit(this, r, c);
    m_nRabbits++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player on a spot with a rabbit
    if (numberOfRabbitsAt(r, c) > 0)
        return false;

    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveRabbits()
{
      // Move all rabbits
      // DONE:  Move each rabbit.  Mark the player as dead if necessary.
      //        Deallocate any dead dynamically allocated rabbit.

      // Another turn has been taken
    for (int i=0; i<m_nRabbits; i++){
        m_rabbits[i]->move();
        if (m_rabbits[i]->isDead()){
            delete m_rabbits[i];
            for (int j=i+1; j<m_nRabbits; j++)
                m_rabbits[j-1] = m_rabbits[j];
            m_nRabbits--;
            i--;
        }
    }
    if (numberOfRabbitsAt(m_player->row(), m_player->col()) != 0){
        m_player->setDead();
    }
    m_turns++;
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid arena position (" << r << ","
             << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRabbits)
{
    if (nRabbits < 0)
    {
        cout << "***** Cannot create Game with negative number of rabbits!" << endl;
        exit(1);
    }
    if (nRabbits > MAXRABBITS)
    {
        cout << "***** Trying to create Game with " << nRabbits
             << " rabbits; only " << MAXRABBITS << " are allowed!" << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nRabbits - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
             << cols << " arena, which is too small too hold a player and "
             << nRabbits << " rabbits!" << endl;
        exit(1);
    }

      // Create arena
    m_arena = new Arena(rows, cols);

      // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);

      // Populate with rabbits
    while (nRabbits > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addRabbit(r, c);
        nRabbits--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/c or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonedCarrot();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'c')
                return player->dropPoisonedCarrot();
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/c." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_arena->rabbitCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        m_arena->moveRabbits();
        m_arena->display(msg);
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

  // Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(lowest, highest);
    return distro(generator);
}

bool decodeDirection(char ch, int& dir)
{
    switch (tolower(ch))
    {
      default:  return false;
      case 'n': dir = NORTH; break;
      case 'e': dir = EAST;  break;
      case 's': dir = SOUTH; break;
      case 'w': dir = WEST;  break;
    }
    return true;
}

  // Return false without changing anything if moving one step from (r,c)
  // in the indicated direction would run off the edge of the arena.
  // Otherwise, update r and c to the position resulting from the move and
  // return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
      // DONE:  Implement this function
      // Delete the following line and replace it with the correct code.
    switch (dir){
        case NORTH:
            if (r-1 < 1)
                return false;
            r--;
            break;
        case SOUTH:
            if (r+1 > a.rows())
                return false;
            r++;
            break;
        case EAST:
            if (c+1 > a.cols())
                return false;
            c++;
            break;
        case WEST:
            if (c-1 < 1)
                return false;
            c--;
            break;
    }
    return true;
}

//check if attempt is possible without actually changing the rows or column
bool checkAttempt(const Arena& a, int dir, int& r, int& c)
{
      // DONE:  Implement this function
      // Delete the following line and replace it with the correct code.
    switch (dir){
        case NORTH:
            if (r-1 < 1)
                return false;
            break;
        case SOUTH:
            if (r+1 > a.rows())
                return false;
            break;
        case EAST:
            if (c+1 > a.cols())
                return false;
            break;
        case WEST:
            if (c-1 < 1)
                return false;
            break;
    }
    return true;
}

  // Recommend a move for a player at (r,c):  A false return means the
  // recommendation is that the player should drop a poisoned carrot and
  // not move; otherwise, this function sets bestDir to the recommended
  // direction to move and returns true.
int rabbitsPerDirection(const Arena& a, int r, int c, int dir){
    int numRabbits = 0;
    switch (dir){
        case NORTH:
            r--;
            break;
        case SOUTH:
            r++;
            break;
        case EAST:
            c++;
            break;
        case WEST:
            c--;
            break;
    }
    numRabbits += a.numberOfRabbitsAt(r-1, c);
    numRabbits += a.numberOfRabbitsAt(r+1, c);
    numRabbits += a.numberOfRabbitsAt(r, c+1);
    numRabbits += a.numberOfRabbitsAt(r, c-1);
    return numRabbits;
}

bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    int moves [5];
    
    //eliminates all failed attempts to move in a direction
    for (int i = 0; i < 4; i++){
        if (checkAttempt(a, i, r, c) == false){
            moves[i] = MAXRABBITS;
        }
    }
    
    //eliminates moving into a point that already has rabbit(s)
    if (a.numberOfRabbitsAt(r-1, c) > 0){
        moves[NORTH] = MAXRABBITS;
    }
    if (a.numberOfRabbitsAt(r+1, c) > 0){
        moves[SOUTH] = MAXRABBITS;
    }
    if (a.numberOfRabbitsAt(r, c+1) > 0){
        moves[EAST] = MAXRABBITS;
    }
    if (a.numberOfRabbitsAt(r, c-1) > 0){
        moves[WEST] = MAXRABBITS;
    }
    
    int min = MAXRABBITS;
    int minPos = 4;
    for(int i = 0; i < 5; i++){
        if (moves[i] != MAXRABBITS){
            moves[i] = rabbitsPerDirection(a, r, c, i);
            if (moves[i] < min){
                min = moves[i];
                minPos = i;
            }
        }
    }
    
    if (minPos != 4){
        bestDir = minPos;
        return true;
    }
    return false;
    
      // TODO:  Implement this function
      // Delete the following line and replace it with your code.
      // This implementation compiles, but is incorrect.

      // Your replacement implementation should do something intelligent.
      // You don't have to be any smarter than the following, although
      // you can if you want to be:  If staying put runs the risk of a
      // rabbit possibly moving onto the player's location when the rabbits
      // move, yet moving in a particular direction puts the player in a
      // position that is safe when the rabbits move, then the chosen
      // action is to move to a safer location.  Similarly, if staying put
      // is safe, but moving in certain directions puts the player in
      // danger of dying when the rabbits move, then the chosen action should
      // not be to move in one of the dangerous directions; instead, the player
      // should stay put or move to another safe position.  In general, a
      // position that may be moved to by many rabbits is more dangerous than
      // one that may be moved to by few.
      //
      // Unless you want to, you do not have to take into account that a
      // rabbit might be poisoned and thus sometimes less dangerous than one
      // that is not.  That requires a more sophisticated analysis that
      // we're not asking you to do.
}

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////
int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10, 12, 10);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif

