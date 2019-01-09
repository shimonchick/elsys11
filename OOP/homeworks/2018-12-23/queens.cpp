#include <iostream>

using namespace std;

class NQueenSolver{
    private:
        int rows, cols;
        bool** grid;
    public:
        NQueenSolver(int rows_param)
            :rows(rows_param), cols(rows_param) { // since its a square grid
                grid = new bool*[rows];
                for(int i = 0; i < rows; i++){
                    grid[i] = new bool[rows];
                    for(int j = 0; j < cols; j++){
                        grid[i][j] = false;
                    }
                }
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
                print_solution();
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
};


int main(){
    int n;
    cin >> n;
    NQueenSolver solver(n);
    solver.solve();

    return 0;

}
