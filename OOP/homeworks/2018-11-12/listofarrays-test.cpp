#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iomanip> 
#include <cmath>
#include <regex>
#include <unordered_map>

using namespace std;

class IteratorException{};
class ListException{};

typedef void (*ScriptFunction)(void);

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
    //TODO: research if namespace can be used instead of class
    private:
        static ListOfArrays listOfArrays;
        static ListOfArrays initial_list;
        static ListOfArrays::Iterator iterator;
        static bool is_iterator;
        static bool stop_commands;
        static unordered_map<string, ScriptFunction> list_map;
        static unordered_map<string, ScriptFunction> iterator_map;
        static unordered_map<string, ScriptFunction> operations_map;
        
       static void show();
       static void size();
       static void averages();
       static void medians();
       static void sizes();
       static void sums();
       static void ordered(string ascending);
       static void add(string coeficient);
       static void mul(string mul);
       static void iterator_show();
       static void begin();
       static void next();
       static void at(string index);
       static void iterator_size();
       static void average();
       static void sum();
       static void median();
       static void iterator_ordered(string ascending);
       static void setup_maps();
    static void parse();
    static void read_matrix();
    static void print_number(double number);
    static void execute_line(const string& commands);

        
};

void ListParser::setup_maps(){
    list_map.emplace("ordered", &ordered);
    list_map.emplace("show", &show);
    list_map.emplace("size", &size);
    list_map.emplace("averages" &averages);
    list_map.emplace("medians", &medians);
    list_map.emplace("sums", &sums);
    list_map.emplace("sizes", &sizes);
    list_map.emplace("begin", &begin);
    list_map.emplace("ordered", &ordered);
    iterator_map.emplace("next", &next);
    iterator_map.emplace("show", &iterator_show);
    iterator_map.emplace("size", &iterator_size);
    iterator_map.emplace("average", &average);
    iterator_map.emplace("median", &median);
    iterator_map.emplace("sum", &sum);
    iterator_map.emplace("ordered", &iterator_ordered);
    operations_map.emplace("add", &add);
    operations_map.emplace("mul", &mul);
    operations_map.emplace("at", &at);
}
void ListParser::parse(){
    setup_maps();
    read_matrix();

    string commands;
    cout.precision(3);
    cout << "> ";
    do{
        listOfArrays = initial_list;
        getline(cin, commands);

        commands = regex_replace(commands, regex("^ +| +$|( ) +"), "$1"); // trim whitespace
        cout << "> " ;
        execute_line(commands);
    }while(commands != "quit");
    //double number = 907.667;
    //cout << "precision: " << get_precision(number) << endl;
}
void ListParser::execute_line(const string& commands){
    //TODO: map strings to functions
    //TODO: iterator and list commands in different functions
    istringstream iss(commands);
    string command;
    is_iterator = false;
    stop_commands = false;
    do{
        getline(iss, command, '.');
        bool is_called = false;

        size_t position = command.find(":");
        if(position != string::npos){ // if the command has : in it search it from the operations map
            string other = command.substr(position + 1);
            auto iter = operations_map.find(command.substr(0, position));
            if(iter != operations_map.end()){
                (*iter->second)(other);
                is_called = true;
            }
        }
        else if(is_iterator){
            auto iter = iterator_map.find(command);
            if(iter != iterator_map.end()){
                (*iter->second)();
                is_called = true;
            }
        }
        else{
            auto iter = list_map.find(command.substr(0, position));
            if(iter != list_map.end()){
                (*iter->second)();
                is_called = true;
            }
        }

        if(!is_called){
            cout << "ERROR: Unknown operation" << endl;
        }

    }while(!iss.eof() && !stop_commands);
}

void ListParser::read_matrix(){
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
void ListParser::print_number(double number){
    string str = to_string(number);
    str.erase ( str.find_last_not_of('0') + 1, string::npos );
    if(str.back() == '.'){
        str.pop_back();
    }
    cout << str << " " ;

}
void ListParser::show(){
    listOfArrays.show();
}
void ListParser::size(){
    cout << listOfArrays.size() << endl;
}
void ListParser::averages(){
    double* averages = new double[listOfArrays.size()];
    listOfArrays.averages(averages);
    cout << fixed;    
    for(int i = 0; i < listOfArrays.size(); i++){
        print_number(averages[i]); 
    }
    delete averages;
    cout << endl;   
}
void ListParser::medians(){
    double* medians = new double[listOfArrays.size()];
    listOfArrays.medians(medians);
    cout << fixed;
    for(int i = 0; i < listOfArrays.size(); i++){
        print_number(medians[i]);
        
    }
    delete medians;
    cout << endl;

}
void ListParser::sizes(){
    int* sizes = new int[listOfArrays.size()];
    listOfArrays.sizes(sizes);
    
    for(int i = 0; i < listOfArrays.size(); i++){
        cout  << sizes[i] << " ";
    }
    delete sizes;
    cout << endl;

}
void ListParser::sums(){
    int* sums = new int[listOfArrays.size()];
    listOfArrays.sums(sums);
    
    for(int i = 0; i < listOfArrays.size(); i++){
        cout  << sums[i] << " ";
    }
    delete sums;
    cout << endl;
}
void ListParser::ordered(string ascending){
    if(ascending == "true"){
        listOfArrays.ordered(true);
    }
    else{
        listOfArrays.ordered(false);
    }
}
void ListParser::add(string coeficient){
    int coef = stoi(coeficient);
    listOfArrays += coef;
}
void ListParser::mul(string mul){
    int multiplier = stoi(mul);
    listOfArrays *= multiplier;
}
void ListParser::iterator_show(){
    iterator.show();
    cout << endl;
}
void ListParser::begin(){
    iterator = listOfArrays.begin();
    is_iterator = true;
}
void ListParser::next(){
    if(++iterator == listOfArrays.end()){
        cout << "ERROR: End of iteration" << endl;
        stop_commands = true;
    }
}
void ListParser::at(string i){
    int index = stoi(i);
    try{
        cout << iterator[index] << endl;
    } catch(IteratorException e){
        cout << "ERROR: Index out of bounds" << endl;
    }
}
void ListParser::iterator_size(){
    cout << iterator.size() << endl;
}
void ListParser::average(){
    print_number(iterator.average());
    cout << endl;
}
void ListParser::sum(){
    cout << iterator.sum() << endl;
}
void ListParser::median(){
    print_number(iterator.median());
    cout << endl;
}
void ListParser::iterator_ordered(string ascending){
    if(ascending == "true"){
        iterator.ordered(true);
    }
    else{
        iterator.ordered(false);
    }
}

int main(){
    ListParser parser;
    parser::parse();
    
}
