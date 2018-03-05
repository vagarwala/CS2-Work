#include "grid.hpp"

using namespace std;

/**
 * @brief: Game, as described in the assignment.
 */

class Game
{
    private:
        int moves;
        Grid grid;
    public:
        Game();
        ~Game();
        char[] getMove();
        void printGrid();
        void Run();
};