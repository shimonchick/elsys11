#include <iostream>
#include <list>
#include "turtle.hh"

using namespace std;

class NQueenSolver{
    private:
        int rows, cols;
        bool** grid;
        int step;
        PSTurtle turtle;
        int offset;
        int x_iteration_offset;
        int y_iteration_offset;
        
        int graphs_row_count;
        int graphs_col_count;
         
    public:
        NQueenSolver(int rows_param)
            :rows(rows_param), cols(rows_param),step(10)
            ,graphs_row_count(5), graphs_col_count(10)
            ,turtle(rows * step * graphs_row_count, cols * step * graphs_col_count)
            , offset(0), x_iteration_offset(0), y_iteration_offset(0)
              { // since its a square grid
                grid = new bool*[rows];
                for(int i = 0; i < rows; i++){
                    grid[i] = new bool[rows];
                    for(int j = 0; j < cols; j++){
                        grid[i][j] = false;
                    }
                }

                turtle.setup();
                turtle.penup();
                turtle.moveto(Point(0,0));

            }
        ~NQueenSolver(){
            for(int i = 0; i < rows; i++){
                delete grid[i];
            }
            delete grid;
        }
        bool canPlace(int row, int col){
            for(int i = col - 1; i >= 0; i--){ // row check
                if(grid[row][i]){
                    return false;
                }
            }
            for(int i = col - 1, j = row - 1; i >= 0 && j >= 0; i--, j--){
                if(grid [j][i]){
                    return false;
                }
            }
            for(int i = col - 1, j = row + 1; i >=0 && j < rows; i--, j++){
                if(grid[j][i]){
                    return false;
                }
            }
            return true;
        }
        void solve(){
            solve(0);
        }
        void solve(int col){
            if(col == cols){
                draw_solution();
                return;
            }
            for(int row = 0; row < rows; row++){
                if(canPlace(row, col)){
                    grid[row][col] = true;
                    solve(col + 1);
                    grid[row][col] = false;
                }
            }
        }
        void print_solution(){
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    if(grid[i][j]){
                        cout << "Q";
                    }
                    else{
                        cout << "_";
                    }
                }
                cout << endl;
            }
            cout << endl << endl;
        }
        void draw_solution(){
            
            
            //turtle.pendown();
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    if(grid[i][j]){
                       
                        turtle.moveto(Point(x_iteration_offset + i * step , y_iteration_offset + j * step));
                        if(!turtle.is_pendown()){
                            turtle.pendown();
                        }
                    }

                }
            }
            turtle.penup();

            offset++;
            x_iteration_offset += rows * step;
            //if(x_iteration_offset + rows * step > turtle.get_width()){
            if(offset == graphs_row_count){
                x_iteration_offset = 0;
                y_iteration_offset += rows * step;
                offset = 0;
            }
            
            Point p(0, 0);
            //p += turtle.get_pos();
            p += Point(x_iteration_offset, y_iteration_offset);
            turtle.set_pos(p);
            
            turtle.moveto(p);
        }
};


int main(){
    int n;
    cin >> n;
     
    NQueenSolver solver(n);
    solver.solve();

    return 0;

}
