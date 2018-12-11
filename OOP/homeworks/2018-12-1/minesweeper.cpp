#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

class point {
    private:
        int x_, y_;
        //getters and setters with better names are present ;)
        bool flagged;
        bool closed;
        bool bomb;
        bool visited;
        
        int bomb_neighbours_count;
    public:
        
        point(int x = 0, int y = 0) : x_(x), y_(y) {
            flagged = false;
            closed = true;
            visited = false;
            bomb = false;
            bomb_neighbours_count = 0;
        }
        bool is_visited() const{
            return visited;
        }
        void set_visited(){
            visited = true;
        }
        bool is_closed() const{
            return closed;
        }
        void set_open(){
            closed = false;
        }
        bool is_bomb() const{
            return bomb;
        }
        void set_bomb(){
            bomb = true;
        }
        bool is_flagged() const{
            return flagged;
        }
        void flag(){
            flagged = !flagged;
        }
        void unflag(){
            flagged = false;
        }

        int get_bomb_neighbours() const{
            return bomb_neighbours_count;
        }
        void set_bomb_neighbours(int count){
            bomb_neighbours_count = count;
        }
        
        int get_x() const {
            return x_;
        }

        int get_y() const {
            return y_;
        }

        void set_x(int x) {
            x_ = x;
            
        }

        void set_y(int y) {
            y_ = y;
            
        }
        
        void show(ostream& out){
            if(is_closed()){
                if(is_flagged()){
                    out << "!";
                }
                else{
                    out << "_";
                }
            }
            else{
                if(is_bomb()){
                    out << "*";
                }
                else{
                    out << get_bomb_neighbours();
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
        
        //allocate memory
        matrix = new point*[height];
        for(int rows = 0; rows < height; rows++){
            point* row = new point[width];
            for(int cols = 0; cols < width; cols++){
                point p(cols, rows);
                row[cols] = p;
            }
            matrix[rows] = row;
        }
        
        //set point properties
        for (int rows = 0; rows < height; rows++)
        {
            for (int cols = 0; cols < width; cols++) 
            {
                point* p = at(rows, cols);
                p->set_x(cols);
                p->set_y(rows);
                for(vector<point>::iterator it = bombs.begin(); it != bombs.end(); it++)
                {
                    if (cols == (*it).get_y() && rows == (*it).get_x()) { // TODO: check if this is right
                        p->set_bomb();
                    }
                }
            }
        }
        //set point neighbours
        for(int rows = 0; rows < height; rows++){
            for(int cols = 0; cols < width; cols++){
                point* p = at(rows, cols);
                int bomb_neighbours = get_bomb_neighbours_count(p);
                p->set_bomb_neighbours(bomb_neighbours);
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
    //I will use pointers instead of references to NULL check the neighbours
    //Pointers are not mixed with references for consistency
    point* at(int row, int col){
        if(col < 0 ||  col >= width || row < 0 || row >= height){
            return NULL;
        }
        return &matrix[row][col];
    }

  
    int get_bomb_neighbours_count(const point* current){
        int result = 0;
        //cout << "point neighbours: " << get_neighbours(point).size();
        point* neighbours[8];
        
        int cols = current->get_x();
        int rows = current->get_y();
        
        neighbours[0] = at(rows - 1, cols - 1);

        neighbours[1] = at(rows - 1, cols);

        neighbours[2] = at(rows - 1, cols + 1);

        neighbours[3] = at(rows, cols -1);

        neighbours[4] = at(rows, cols + 1);

        neighbours[5] = at(rows + 1, cols -1);

        neighbours[6] = at(rows + 1, cols);

        neighbours[7] = at(rows + 1, cols + 1);
        
        for(int i = 0; i < 8; i++){
            if(neighbours[i]){
                if(neighbours[i]->is_bomb()){
                    result++;
                }
            }
        }
        return result;
    }


    void show(ostream &out) {
        for (int rows = 0; rows < height; rows++) {
            for (int cols = 0; cols < width; cols++) {
                point* p = at(rows, cols);
                p->show(out);
                //cout << "showing point :" << i * width + j << endl;
            }
            out << endl;
        }
    }

    void show_all(ostream& out){
        for(int rows = 0; rows < height; rows++){
            for(int cols = 0; cols < width; cols++){
                point* p = at(rows, cols);
                if(p->is_bomb()){
                    out << "*";
                }
                else{
                    out << p->get_bomb_neighbours();
                }
            }
            out << endl;
        }
    }
    bool check_win() {
        for(int rows = 0; rows < height; rows++){
            for(int cols = 0; cols < width; cols++){
                point* p = at(rows, cols);
                if (p->is_closed() && !p->is_bomb()) return false;
            }
           
        }
        return true;
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
                if(point->is_closed()){
                    point->flag();
                }
                
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
                if(point->is_flagged()){
                    point->unflag();
                } 
                else if(point->is_bomb()) {
                    throw GameOverException();
                } 
                else{
                    //out << "opening boxes:" << endl;
                    //point->is_closed = false;
                    //matrix.set_unvisited();
                    //if(point->get_bomb_neighbours() == 0){
                        this->open_box(point);
                    //}
                }
            }
        }
        // [old version of code, don't uncomment]
       //turns out vector operations andd recursion are slow when called many times so i will implement it with pointers
       //thought i would add some extra lines so i don't get accused of cheating again ;d
       /* 
        void open_box(point* point)
        {
            if(point->is_visited()) return;
            //out << "point is closed" << endl;
            if (point->is_bomb()) return;
            //out << "point is not a bomb" << endl;
            if(!point->is_closed()) return;
            
            //out << "opening box: " << point->get_x() <<  "," << point->get_y() << endl;
            point->set_open();
            point->set_visited();
            
            if(point->get_bomb_neighbours() == 0){
                for(auto neighbour : matrix.get_neighbours(point)){
                    if(neighbour){
                        open_box(neighbour);
                        
                    }
                }
            }
        
        }
        */
        //and this is too slow aswell ? hell what am i supposed to do then ?
        
        void open_box(point* p){
            if(p->is_visited()) return;
            //if(p->is_bomb()) return;
            if(!p->is_closed()) return;
            if(p->is_flagged()) return;

            p->set_open();
            //p->unflag();
            p->set_visited();

            point* neighbours[8];
            if(p->get_bomb_neighbours() == 0){
                int rows = p->get_y();
                int cols = p->get_x();
                neighbours[0] = matrix.at(rows - 1, cols - 1);

                neighbours[1] = matrix.at(rows - 1, cols);
   
                neighbours[2] = matrix.at(rows - 1, cols + 1);

                neighbours[3] = matrix.at(rows, cols -1);
    
                neighbours[4] = matrix.at(rows, cols + 1);
   
                neighbours[5] = matrix.at(rows + 1, cols -1);

                neighbours[6] = matrix.at(rows + 1, cols);
   
                neighbours[7] = matrix.at(rows + 1, cols + 1);

                for(int i = 0; i < 8; i++){
                    if(neighbours[i]){
                        open_box(neighbours[i]);
                    }
                }
            }
        
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
                if(point->is_bomb()){
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

