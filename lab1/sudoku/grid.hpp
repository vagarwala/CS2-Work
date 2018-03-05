#include <string>
using namespace std;
/**
 * @brief: board, as described in the assignment.
 */

class Grid
{
    private:
        int **grid;
        int size;
    public:
        Grid();
        Grid(int s);
        ~Grid();
        void loadBoard(string filename);
        int isComplete();
        int checkValid(int x, int y, char val);
        void writeNum(int x, int y, char val);
        void undoNum(int x, int y);
};