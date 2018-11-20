#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iomanip> 
#include <cmath>
#include <regex>

using namespace std;

class IteratorException{};
class ListException{};


class ListOfArrays {
    private:
        class ArrayNode {
            public:

                int* data_;
                int size_;
                ArrayNode* prev_;
                ArrayNode* next_;

                ArrayNode(int* data, int size)
                    : data_(data), size_(size), next_(NULL), prev_(NULL) {

                    }

                ~ArrayNode() {
                    delete [] data_;
                }

        };

        static bool comp(ArrayNode* first, ArrayNode* second){
            if(first->size_ == second->size_){
                for(int i = 0; i < first->size_; i++){
                    if(first->data_[i] < second->data_[i]){
                        return true;
                    }
                    else if(first->data_[i] > second->data_[i]){
                        return false;
                    }
                }
            }
            return first->size_ < second->size_; 
        }
        ArrayNode* head_;
        int size_;

    public:

        class Iterator {

            friend class ListOfArrays;
            ListOfArrays* list_;
            ArrayNode* current_;
            
            public:
            Iterator(ListOfArrays* list, ArrayNode* current)
                : list_(list), current_(current) {}

            bool operator==(const Iterator& other){
                return current_ == other.current_;
                //if(this->current_->prev_ == other.current_->prev_ && this->current_->next_ == other.current_->next_) return true;
                //return false;
                
                //if(current_->size_ != other.current_->size_){
                //    return false;
                //}
                //for(int i = 0; i < size(); i++){
                //    if(current_->data_[i] != other.current_->data_[i]){
                //        return false;
                //    }
                //}
                //return true;
            }

            bool operator!=(const Iterator& other){
                return ! operator==(other);
            }

            Iterator& operator++(){ // ++it
                current_ = current_->next_;
                return *this;
            }

            Iterator operator++(int){ // it++
                Iterator result(list_, current_);
                current_ = current_->next_;
                return result;
            }
            Iterator& operator--(){ // --it
                current_ = current_->prev_;
                return *this;
            }
            Iterator operator--(int){ // it--
                Iterator result(list_, current_);
                current_ = current_->prev_;
                return result;
            }
            int& operator[](const int& index){
                if(index < 0 || index >= size()){
                    throw IteratorException();
                }
                return current_->data_[index];
            }

            int size() const{
                return current_->size_;
            }

            void show(){
                for(int i = 0; i < size() - 1; i++){
                    cout << current_->data_[i] << " ";
                }
                cout << current_->data_[size() - 1];
            }
            
            double average(){
                return (double)sum() / (double)size();
            }
            
            double median(){
                ordered(true); // sort 
                double result = 0;
                if(size() % 2 == 0){ // check even
                    result = (current_->data_[size()/2] + current_->data_[size()/2 - 1]) /2.0;
                }
                else{
                    return current_->data_[size()/2];
                }
                return result;
            }
            
            int sum(){
                int sum = 0;
                for(int i = 0; i < size(); i++){
                    sum += current_->data_[i];
                }
                
                return sum;
            }
            
            Iterator& ordered(bool ascending = true){

                vector<int> v;
                for(int i = 0; i < size(); i++){
                    v.push_back(current_->data_[i]);
                }
                sort(v.begin(), v.end());
                if(!ascending){
                    reverse(v.begin(), v.end());
                }
                for(int i = 0; i < size(); i++){
                    current_->data_[i] = v[i];
                }
                
                return *this;
            }



        };

        ListOfArrays()
                : size_(0), head_(new ArrayNode(0, 0)) {
            head_->next_ = head_;
            head_->prev_ = head_;
        }

        ~ListOfArrays(){
            clear();
            delete head_;
        }

        ListOfArrays(const ListOfArrays& other) : ListOfArrays(){
            for(ArrayNode* current = other.head_->next_; current != head_; current = current->next_){
                push(current->data_, 0, current->size_);
            }
        }
        bool empty() const {
            return head_->prev_ == head_;
        }
        void clear(){
            while(!empty()){
                pop_back();
            }
        }
        void pop_back(){
            if(empty()){
                throw ListException();
            }
            ArrayNode* last = head_->prev_;
            ArrayNode* new_last = last->prev_;
            
            new_last->next_ = head_;
            head_->prev_ = new_last;
            
            size_--;
            
            delete last;

        }
        ListOfArrays& operator=(const ListOfArrays& other){

            clear();
            for(ArrayNode* current = other.head_->next_; current != other.head_; current = current->next_){
                push(current->data_, 0, current->size_);
            }
            return *this;     
         }
        int size(){
            return size_;
        }

        void push(int array[], int position, int length){
            int* data = new int[length];
            for(int i = 0; i < length; i++){
                data[i] = array[position + i];
            }
            ArrayNode* node = new ArrayNode(data, length);
            ArrayNode* last = head_->prev_;
            
            last->next_ = node;
            node->prev_ = last;
            node->next_ = head_;
            head_->prev_ = node;
            
            size_++;
        }

        void averages(double averages[]){
            int i = 0;
            for(Iterator it = begin(); it != end(); it++){
                averages[i] = it.average();
                i++;
            }
        }

        void medians(double medians[]){
            int i = 0;
            for(Iterator it = begin(); it != end(); it++){
                medians[i] = it.median();
                i++;
            }

        }
        
        void sizes(int sizes[]){
            int i = 0;
            for(Iterator it = begin(); it != end(); it++){
                sizes[i] = it.size();
                i++;
            }

        }
        
        void sums(int sums[]){
            int i = 0;
            for(Iterator it = begin(); it != end(); it++){
                sums[i] = it.sum();
                i++;
            }
            

        }

        Iterator begin(){
            return Iterator(this, head_->next_);
        }

        Iterator end(){
            return Iterator(this, head_);
        }

        ListOfArrays& ordered(bool ascending = true){
            for(Iterator it = begin(); it != end(); it++){
                it.ordered(ascending);
            }
            vector<ArrayNode*> v;
            for(ArrayNode* current = head_->next_; current != head_; current = current->next_){
                v.push_back(current);
            }
            sort(v.begin(), v.end(), comp);
            if(!ascending){
                reverse(v.begin(), v.end());
            }
            ListOfArrays new_list;
            for(int i = 0; i < v.size(); i++){
                new_list.push(v[i]->data_, 0, v[i]->size_);
            }

            *this = new_list; // overloaded operator = 
            
            return *this;
        }

        ListOfArrays& operator*=(const int& coef){
            for(Iterator it = begin(); it != end(); it++){
                for(int i = 0; i < it.size(); i++){
                    it[i] *= coef;
                }
            }
            return *this;
        }

        ListOfArrays& operator+=(const int& value){
            for(Iterator it = begin(); it != end(); it++){
                for(int i = 0; i < it.size(); i++){
                    it[i] += value;

                }
            }
            return *this;
        }

        void show(){
            for(Iterator it = begin(); it != --end(); it++){
                it.show();
                cout << "; ";
            }
            Iterator it = --end();
            it.show();
            cout << endl;
        }
};

class ListParser{
    private:
        ListOfArrays list;
        ListOfArrays initial_list;
        ListOfArrays::Iterator iterator;
        bool is_iterator;
    public:
        ListParser() : iterator(list.begin()), is_iterator(false){}
        
        void parse(){
            
            read_matrix();
            
            string commands;
            cout.precision(3);
            cout << "> ";
            do{
                list = initial_list;
                getline(cin, commands);
                
                commands = regex_replace(commands, regex("^ +| +$|( ) +"), "$1"); // trim whitespace
                cout << "> " ;
                execute_line(commands);
            }while(commands != "quit");
            //double number = 907.667;
            //cout << "precision: " << get_precision(number) << endl;
        }
        void read_matrix(){
            string matrix;
            getline(cin, matrix);
            string array;
            size_t position = 0;
            do{
                position = matrix.find(";"); 
                array = matrix.substr(0, position);
                istringstream values(array);
                vector<int> v;
                int data;
                while(!values.eof()){
                    values >> data;
                    v.push_back(data);
                }
                initial_list.push(&v[0], 0, v.size());
                matrix.erase(0, position + 1);
            }while(position != string::npos);
        }
        void execute_line(const string& commands){
            //TODO: map strings to functions
            //TODO: iterator and list commands in different functions
            istringstream iss(commands);
            string command;
            is_iterator = false;
            do{
                getline(iss, command, '.');
                
                if(command == "show" && !is_iterator){
                    
                    list.show();
                }
                else if(command == "size"  && !is_iterator){
                    
                    cout << list.size() << endl;
                }
                else if(command == "averages" && !is_iterator){
                    double* averages = new double[list.size()];
                   list.averages(averages);
                    cout << fixed;    
                    for(int i = 0; i < list.size(); i++){
                        //int precision = get_precision(averages[i]);
                        //cout << setprecision(min(precision, 3)) << averages[i] << " ";
                        print_number(averages[i]); 
                    }
                    delete averages;
                    cout << endl;
                }
                else if(command == "medians" && !is_iterator){
                    double* medians = new double[list.size()];
                    list.medians(medians);
                    cout << fixed;
                    for(int i = 0; i < list.size(); i++){
                        print_number(medians[i]);
                        //int precision = get_precision(medians[i]);
                        //cout << setprecision(min(precision, 3)) << medians[i] << " ";
                        
                    }
                    delete medians;
                    cout << endl;

                }
                else if(command == "sizes" && !is_iterator){
                    int* sizes = new int[list.size()];
                    list.sizes(sizes);
                    
                    for(int i = 0; i < list.size(); i++){
                        cout  << sizes[i] << " ";
                    }
                    delete sizes;
                    cout << endl;

                }
                else if(command == "sums" && !is_iterator){
                    int* sums = new int[list.size()];
                    list.sums(sums);
                    
                    for(int i = 0; i < list.size(); i++){
                        cout  << sums[i] << " ";
                    }
                    delete sums;
                    cout << endl;
                }
                else if((command.find("ordered") != string::npos) && !is_iterator){
                    string state = command.substr(command.find(":"));
                    state.erase(0, 1);
                    bool ascending;
                    if(state == "true"){
                        ascending = true; 
                    }else{
                        ascending = false;
                    }
                    
                    list.ordered(ascending);
                }
                else if(command.find("mul") != string::npos && !is_iterator){
                    string mul = command.substr(command.find(":") + 1);
                    int multiplier = stoi(mul);
                    list *= multiplier;
                }
                else if(command.find("add") != string::npos && !is_iterator){
                    string add_str = command.substr(command.find(":") + 1);
                    int add = stoi(add_str);
                    list += add;
                }
                else if(command == "begin"){
                    iterator = list.begin();
                    is_iterator = true;
                }
                else if(command == "next" && is_iterator){
                    if(++iterator == list.end()){
                        cout << "ERROR: End of iteration" << endl;
                        break;
                    }
                        
                }
                else if(command == "show" && is_iterator){
                    
                    iterator.show();
                    cout << endl;
                }
                else if(command.find("at") != string::npos && is_iterator){
                    int index = stoi(command.substr(command.find(":")  + 1));
                    try{
                        cout << iterator[index] << endl;
                    } catch(IteratorException e){
                        cout << "ERROR: Index out of bounds" << endl;
                    }
                }
                else if(command == "size" && is_iterator){
                    
                    cout << iterator.size() << endl;
                }
                else if(command == "average" && is_iterator){
                    print_number(iterator.average());
                    cout << endl;
                    //int precision = get_precision(iterator.average());
                    //cout << setprecision(min(precision, 3)) << iterator.average() << endl;
                    
                }
                else if(command == "sum" && is_iterator){
                    
                    cout << iterator.sum() << endl;
                }
                else if(command == "median" && is_iterator){
                    print_number(iterator.median());
                    cout << endl;
                    //int precision = get_precision(iterator.median());
                    //cout << setprecision(min(precision, 3)) << iterator.median() << endl;
                
                }
                else if((command.find("ordered")!= string::npos) && is_iterator && is_iterator){
                    bool ascending = (command.substr(command.find(":")  + 1 ) == "true") ? true : false;
                    iterator.ordered(ascending);
                }
                else if(command == "quit"){
                    break;
                }
                else{
                    cout << "ERROR: Unknown operation" << endl;
                    break;
                }    
                
            }while(!iss.eof());
        }
        int get_precision(double num){
            string s = to_string(num);
            cout << "string: " << s << endl;
            size_t dot_pos = s.find(".");
            cout << "dot_pos: " << dot_pos << endl;
            string start = s.substr(dot_pos + 1);
            cout << "start: " << start << endl;
            size_t zero_pos = start.find("0");
            cout << "dot_pos: " << dot_pos << "zero_pos: " << zero_pos << endl;
            //if(zero_pos == string::npos){
            //    return 0;
            //}
           return zero_pos;
        }
        void print_number(double number){
            string str = to_string(number);
            str.erase ( str.find_last_not_of('0') + 1, string::npos );
            if(str.back() == '.'){
                str.pop_back();
            }
            cout << str << " " ;
            
        }
    
        
};

int main(){
    ListParser parser;
    parser.parse();
    
}
