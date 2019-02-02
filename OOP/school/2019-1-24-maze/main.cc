#include "turtle.hh"
#include <vector>


enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class Cell{
    private:

        bool walls[4];
        bool is_visited;
    
    public:
    
        void drill(Direction dir){

        }
};

class Maze{
    private:
        PSTurtle& turtle;
        vector<vector<Cell>> cells;
        has_unvisited_neighbours(Cell& cell){

        }

        Cell* at(int x, int y){
            if(x > cells[0].length || y > cells.length)
                return NULL;
            return cells[x][y]
        }
    
    public:
        void generate(int x, int y){
            Cell& cell = at(x,y);
            if(!has_unvisited_neighbours(cell)){
                return;
            }
            Direction dir = get_random_unvisited_direction(cell);

            cell.drill(dir);
            Cell* other = cell.get_neighbour(dir);
            if(other){
                other->drill((Direction)((dir + 2) % 4));
            }
        }  
};

int main(){

}