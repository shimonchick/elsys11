#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

class point {
    private:
        int x_, y_;
        bool is_flagged;
        
        int bomb_neighbours_count;
    public:

        bool is_closed;
        bool is_bomb;
        bool is_visited;
        point(int x = 0, int y = 0) : x_(x), y_(y) {
            is_flagged = false;
            is_closed = true;
            is_visited = false;
            is_bomb = false;
            bomb_neighbours_count = 0;
        }

        void set_bomb_neighbours(int count){
            bomb_neighbours_count = count;
        }
        int get_bomb_neighbours() const{
            return bomb_neighbours_count;
        }
        int get_x() const {
            return x_;
        }

        int get_y() const {
            return y_;
        }

        point& set_x(int x) {
            x_ = x;
            return *this;
        }

        point& set_y(int y) {
            y_ = y;
            return *this;
        }
        void set_bomb(){
            is_bomb = true;
        }
        void flag(){
            is_flagged = !is_flagged;
        }
        bool operator== (const point& other){
            return this->x_ == other.x_ && this->y_ == other.y_;
        }
        bool operator <(const point& other){
            if(this-> y_ < other.y_){
                return true;
            }
            else if(this->y_ > other.y_){
                return false;
            }
            else if(this->x_ < other.x_){
                return true;
            }
            else{
                return false;
            }
        }
        void show(ostream& out){
            if(is_closed){
                if(is_flagged){
                    out << "!";
                }
                else{
                    out << "_";
                }
            }
            else{
                if(is_bomb){
                    out << "*";
                }
                else{
                    out << bomb_neighbours_count;
                }
            }
        }
};

istream& operator>>(istream& in, point& p) {
    int x, y;
    char c;
    in >> x >> c;
    if(c != ',') {
        in.clear(ios_base::badbit);
        return in;
    }
    in >> y;
    p.set_x(x);
    p.set_y(y);
    return in;
}
class MatrixException{};

class Matrix {
private:
    point** matrix;
    int width, height;


public:
    Matrix(int width_param, int height_param, vector<point> &bombs)
            : width(width_param), height(height_param) 
        {
        //sort(bombs.begin(), bombs.end());
        //int bomb_index = 0;
        //point bomb = bombs[bomb_index];
        
        matrix = new point*[height];
        for(int rows = 0; rows < height; rows++){
            point* row = new point[width];
            for(int cols = 0; cols < width; cols++){
                point p(cols, rows);
                row[cols] = p;
            }
            matrix[rows] = row;
        }
        
        for (int rows = 0; rows < height; rows++)
        {
            for (int cols = 0; cols < width; cols++) 
            {
                matrix[rows][cols].set_x(cols).set_y(rows);
                for(vector<point>::iterator it = bombs.begin(); it != bombs.end(); it++)
                {
                    if (cols == (*it).get_y() && rows == (*it).get_x()) { // TODO: check if this is right
                        matrix[rows][cols].is_bomb = true;
                    }
                }
            }
        }
        for(int rows = 0; rows < height; rows++){
            for(int cols = 0; cols < width; cols++){
                int bomb_neighbours = get_bomb_neighbours_count(matrix[rows][cols]);
                matrix[rows][cols].set_bomb_neighbours(bomb_neighbours);
            }
        }
        //cout << "bomb neighbours: " << bomb_neighbours << endl;
        
    }
    ~Matrix(){
        for(int rows = 0; rows < height; rows++){
            delete [] matrix[rows];
        }
        delete [] matrix;
    }

    point* at(int row, int col){
        if(col < 0 ||  col >= width || row < 0 || row >= height){
            return NULL;
        }
        return &matrix[row][col];
    }

    vector<point> get_neighbours(const point& current) {
        point* neighbours[8];
        int cols = current.get_x();
        int rows = current.get_y();
        vector<point> result;
        neighbours[0] = at(rows - 1, cols - 1);

        neighbours[1] = at(rows - 1, cols);

        neighbours[2] = at(rows - 1, cols + 1);

        neighbours[3] = at(rows, cols -1);

        neighbours[4] = at(rows, cols + 1);

        neighbours[5] = at(rows + 1, cols -1);

        neighbours[6] = at(rows + 1, cols);

        neighbours[7] = at(rows + 1, cols + 1);
        for(int i = 0; i < 8; i++){
            if(neighbours[i]) {
                result.push_back(*neighbours[i]);
             
            }
        }
        return result;

    }
    int get_bomb_neighbours_count(const point& point){
        int result = 0;
        //cout << "point neighbours: " << get_neighbours(point).size();
        for(auto neighbour : get_neighbours(point)){
            if(neighbour.is_bomb){
                result++;
            }
        }
        return result;
    }
    int clicked(){
        int result = 0;
        for(int rows = 0; rows < height; rows++){
            for(int cols = 0; cols < width; cols++){
                if(matrix[rows][cols].is_closed)
                result++;
            }
        }
        return result;
    }


    void show(ostream &out) {
        for (int rows = 0; rows < height; rows++) {
            for (int cols = 0; cols < width; cols++) {
                matrix[rows][cols].show(out);
                //cout << "showing point :" << i * width + j << endl;
            }
            out << endl;
        }
    }
    void show_all(ostream& out){
        for(int rows = 0; rows < height; rows++){
            for(int cols = 0; cols < width; cols++){
                if(matrix[rows][cols].is_bomb){
                    out << "*";
                }
                else{
                    out << matrix[rows][cols].get_bomb_neighbours();
                }
            }
            out << endl;
        }
    }
    bool check_win() {
        for(int rows = 0; rows < height; rows++){
            for(int cols = 0; cols < width; cols++){
                point p = matrix[rows][cols];
                if (p.is_closed && !p.is_bomb) return false;
            }
           
        }
        return true;
    }
    void set_unvisited(){
        for(int rows = 0; rows < height; rows++){
            for(int cols = 0; cols < width; cols++){
                point p = matrix[rows][cols];
                p.is_visited = false;
            }
           
        }
        
    }
};
/* Enter your code here. */   
class Command{
    protected:
        string name_;
        Matrix& matrix;
    public:
        Command(const string& name, Matrix& matrix_param) : name_(name), matrix(matrix_param){}
        string get_name() const{
            return name_;
        }
        virtual void execute(int x, int y) =0;
};
class Flag : public Command{
    public:
        Flag(const string& name, Matrix& matrix_param) : Command(name, matrix_param){}
        void execute(int x, int y) override{
            point* point = matrix.at(x, y);
            if(point){
                point->flag();
            }
        }
};
class GameOverException{};
class Click : public Command{
    private:
        ostream& out;
    public:
        Click(const string& name, Matrix& matrix_param, ostream& out_param)
            : Command(name, matrix_param), out(out_param)
            {}
        void execute(int x, int y) override {
            point *point = matrix.at(x, y);
            if (point) {
                if(point->is_bomb) {
                    throw GameOverException();
                } else {
                    //out << "opening boxes:" << endl;
                    point->is_closed = false;
                    matrix.set_unvisited();
                    this->open_box(x, y);
                }
            }
        }
        void open_box(int x, int y)
        {
            point *point = matrix.at(x, y);
            if (!point) return;
            //out << "point exists" << endl;
            if(point->is_visited) return;
            //out << "point is closed" << endl;
            if (point->is_bomb) return;
            //out << "point is not a bomb" << endl;
            
            
            //out << "opening box: " << point->get_x() <<  "," << point->get_y() << endl;
            point->is_closed = false;
            point->is_visited = true;
            
            if(point->get_bomb_neighbours() != 0) return;

            for(auto neighbour : matrix.get_neighbours(*point)){
                
                open_box(neighbour.get_x(), neighbour.get_y());
            }
            //out << "boxes open: " << matrix.clicked() << endl;
            /*
            open_box(x - 1, y - 1);
            open_box(x, y - 1);
            open_box(x + 1, y - 1);
            open_box(x - 1, y);
            open_box(x + 1, y);
            open_box(x - 1, y + 1);
            open_box(x, y + 1);
            open_box(x + 1, y + 1);
        */
        }

};

class Hint : public Command{
    
    private:
        ostream& out;

    public:
        Hint(const string& name, Matrix& matrix_param, ostream& out_param )
            : Command(name, matrix_param), out(out_param)
            {}
        void execute(int x, int y){
            point* point = matrix.at(x, y);
            if(point){
                if(point->is_bomb){
                    out << "bomb" << endl;
                }
                else{
                    out << "not a bomb" << endl;
                }
            }
        }
};
class minesweeper {

    private:
        int width, height;
        list<Command*> operations;
        ostream& out;
        istream& in;
        Matrix matrix;

        void read_command(string& command, point& point){
            string operation;
            getline(in, operation);
            istringstream iss(operation);
            iss >> command;
            iss >> point;
        }

        void setup_operations(){
            operations.push_back(new Hint("hint", matrix, out));
            operations.push_back(new Click("click", matrix, out));
            operations.push_back(new Flag("flag", matrix));
        }
        /*
        void setup_matrix(vector<point> bombs){
            sort(bombs.begin(), bombs.end());
            int bomb_index = 0;
            point bomb = bombs[bomb_index];
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    if(bomb.get_x() == j && bomb.get_y() == i){
                        matrix.push_back(point(j, i, true));
                        bomb_index++;
                        bomb = bombs[bomb_index];
                    }
                    else{
                        matrix.push_back(point(j, i, false));
                    }
                }
            }
        }
        */
        Command* get_command(const string& name) const{
            for(list<Command*>::const_iterator it = operations.begin(); it != operations.end(); it++){
                if((*it)->get_name() == name){
                    return *it;
                }
            }
            return NULL;
        }
    public:

        minesweeper(int width_param, int height_param, vector<point>& bombs, istream& in_param, ostream& out_param)
            : width(width_param), height(height_param), in(in_param), out(out_param), matrix(width, height, bombs)
        {
            setup_operations();
        }
        void run() {
            bool done = false;
            while(!done && !in.eof()){
                point point;
                string command;
                
                //read_command(command, point);
                matrix.show(out);

                out << "> ";
                read_command(command, point);
                //out << "command: " << command;

                int x = point.get_x();
                int y = point.get_y();
                //out << "x: " << x << "y: " << y << endl;
                Command* operation = get_command(command);
                //out << "got command" << endl;
                if(operation){
                    try{
                        //out << "executing command" << endl;
                        operation->execute(x, y); // reminder: it turns out that the commands accepts rows and cols and not x and y so they should be reversed
                        //out << "executed command" << endl;
                    } catch(GameOverException e){
                        out << "game over" << endl;
                        done = true;
                        matrix.show_all(out);
                    }
                }
                if(matrix.check_win()){
                    out << "game win" << endl;
                    matrix.show_all(out);  
                    done = true;
                }
                
                //out << "boxes open: " << matrix.clicked() << endl;
                //matrix.show(out);
            }
        }
};

int main() {
    string line;

    getline(cin, line);
    istringstream iss(line);
    int width, height;
    iss >> width >> height;

    getline(cin, line);
    iss.str(line);
    iss.clear();
    int bombs_count;
    iss >> bombs_count;
    vector<point> bombs;
    for (int i = 0; i < bombs_count; i++) {
        point p;
        getline(cin, line);
        iss.str(line);
        iss.clear();
        iss >> p;
        bombs.push_back(p);
    }
    minesweeper game(width, height, bombs, cin, cout);
    game.run();
    return 0;
}

