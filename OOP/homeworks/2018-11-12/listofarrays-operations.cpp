#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iomanip> 
#include <cmath>
#include <regex>
#include <list>

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
            Iterator() : list_(NULL), current_(NULL){};
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

// why do programmers go to such lenghts to avoid using if else chains ? -.- too many classes for me
class Command{
    protected:
        string name_;
    public:
        Command(const string& name) : name_(name){}
        string get_name() const{
            return name_;
        }
        //methods are not pure because I need to implement one of them in derived class and not both
        virtual void execute(){
            cout << "called base execute" <<endl;
        }
        virtual void execute(string name){
            cout << "called base execute" <<endl;
            }
};
class CommandException{
private:
    string message_;
public:
    CommandException(const string& message): message_(message){}
    string get_message() const{
        return message_;
    }
};

class ListCommand :  public Command{
    protected:
        ListOfArrays& list;
    public:
        ListCommand(const string& name, ListOfArrays& list_param) : Command(name), list(list_param){}
        virtual void execute(){
            cout << "listcommand execute called" << endl;
        }
        virtual void execute(string s){
            cout << "listcommand execute called" << endl;
        }
};
class IteratorCommand : public Command{
protected:
    ListOfArrays::Iterator& iterator;
public:
    IteratorCommand(const string& name, ListOfArrays::Iterator& iterator_param) : Command(name), iterator(iterator_param){}
    virtual void execute(){
        cout << "iteratorcommand execute called" << endl;
    }
    virtual void execute(string s){
        cout << "iteratorcommand execute called" << endl;
    }
};

class CommandNotFoundException{};

class ListShow : public ListCommand{
public:
    ListShow(const string& name, ListOfArrays& list_param) : ListCommand(name, list_param){}
    void execute() override{
        list.show();
    }
};

class ListSize : public ListCommand{
public:
    ListSize(const string& name, ListOfArrays& list_param) : ListCommand(name, list_param){}
    void execute(){
        cout << list.size() << endl;
    }
};
class ListAverages : public ListCommand{
public:
    ListAverages(const string& name, ListOfArrays& list_param) : ListCommand(name, list_param){}
    void execute(){
        double* averages = new double[list.size()];
        list.averages(averages);
        cout << fixed;
        for(int i = 0; i < list.size(); i++){
            //int precision = get_precision(averages[i]);
            //cout << setprecision(min(precision, 3)) << averages[i] << " ";
            //print_number(averages[i]);
            cout << averages[i] << " ";
        }
        delete averages;
        cout << endl;
    }
};
class ListMedians : public ListCommand{
public:
    ListMedians(const string& name, ListOfArrays& list_param) : ListCommand(name, list_param){}
    void execute(){
        double* medians = new double[list.size()];
        list.medians(medians);
        cout << fixed;
        for(int i = 0; i < list.size(); i++){
            //print_number(medians[i]);
            //int precision = get_precision(medians[i]);
            //cout << setprecision(min(precision, 3)) << medians[i] << " ";
            cout << medians[i] << " ";
        }
        delete medians;
        cout << endl;
    }
};
class ListSizes : public ListCommand{
public:
    ListSizes(const string& name, ListOfArrays& list_param) : ListCommand(name, list_param){}
    void execute(){
        int* sizes = new int[list.size()];
        list.sizes(sizes);

        for(int i = 0; i < list.size(); i++){
            cout  << sizes[i] << " ";
        }
        delete sizes;
        cout << endl;
    }
};
class ListSums : public ListCommand{
public:
    ListSums(const string& name, ListOfArrays& list_param) : ListCommand(name, list_param){}
    void execute(){
        int* sums = new int[list.size()];
        list.sums(sums);

        for(int i = 0; i < list.size(); i++){
            cout  << sums[i] << " ";
        }
        delete sums;
        cout << endl;
    }
};

class ListOrdered : public ListCommand{
public:
    ListOrdered(const string& name, ListOfArrays& list_param) : ListCommand(name, list_param){
    }
    void execute(string state){
        bool ascending;
        if(state == "true"){
            ascending = true;
        }else{
            ascending = false;
        }

        list.ordered(ascending);
    }
};
class ListMul : public ListCommand{
public:
    ListMul(const string& name, ListOfArrays& list_param) : ListCommand(name, list_param){}
    void execute(string mul){
        int multiplier = stoi(mul);
        list *= multiplier;
    }

};
class ListAdd : public ListCommand{
public:
    ListAdd(const string& name, ListOfArrays& list_param) : ListCommand(name, list_param){}
    void execute(string number){
        int adder = stoi(number);
        list += adder;
    };


};

class IteratorShow : public IteratorCommand{
public:
    IteratorShow(const string& name, ListOfArrays::Iterator& iterator_param) : IteratorCommand(name, iterator_param){}
    void execute(){
        iterator.show();
        cout << endl;
    }
};


class IteratorNext : public IteratorCommand{
private:
    ListOfArrays& list;
public:
    IteratorNext(const string& name, ListOfArrays::Iterator& iterator_param, ListOfArrays& list_param)
        : IteratorCommand(name, iterator_param), list(list_param){}
    void execute(){
        if(++iterator == list.end()){
            throw CommandException("ERROR: End of iteration");

        }
    }
};
class IteratorAt : public IteratorCommand{
public:
    IteratorAt(const string& name, ListOfArrays::Iterator& iterator_param) : IteratorCommand(name, iterator_param){}

    void execute(string i){
        try{
            int index = stoi(i);
            cout << iterator[index] << endl;
        } catch(IteratorException e){
            throw CommandException("ERROR: Index out of bounds");
        }
    }

};
class IteratorOrdered : public IteratorCommand{
public:
    IteratorOrdered(const string& name, ListOfArrays::Iterator& iterator_param) : IteratorCommand(name, iterator_param){}

    void execute(string state){
        bool ascending;
        if(state == "true"){
            ascending = true;
        }else{
            ascending = false;
        }

        iterator.ordered(ascending);
    }

};
class IteratorSize : public IteratorCommand{
public:
    IteratorSize(const string& name, ListOfArrays::Iterator& iterator_param) : IteratorCommand(name, iterator_param){}
    void execute(){
        cout << iterator.size() << endl;
    }
};
class IteratorSum : public IteratorCommand{
public:
    IteratorSum(const string& name, ListOfArrays::Iterator& iterator_param) : IteratorCommand(name, iterator_param){}
    void execute(){
        cout << iterator.sum() << endl;
    }
};
class IteratorAverage : public IteratorCommand{
public:
    IteratorAverage(const string& name, ListOfArrays::Iterator& iterator_param) : IteratorCommand(name, iterator_param){}
    void execute(){
        cout << iterator.average() << endl;
    }
};
class IteratorMedian : public IteratorCommand{
public:
    IteratorMedian(const string& name, ListOfArrays::Iterator& iterator_param) : IteratorCommand(name, iterator_param){}
    void execute(){
        cout << iterator.median() << endl;
    }
};


class ListParser{
    private:
        ListOfArrays listOfArrays;
        ListOfArrays initial_list;
        ListOfArrays::Iterator iterator;
        list<Command*> list_commands;
        list<Command*> iterator_commands;
        Command* get_list_command(const string& name){
            for(list<Command*>::iterator it = list_commands.begin(); it != list_commands.end(); it++){
                   if( (*it) -> get_name() == name){
                       return *it;
                   }
            }
            throw CommandNotFoundException();
        }
        Command* get_iterator_command(const string& name){
            for(list<Command*>::iterator it = iterator_commands.begin(); it != iterator_commands.end(); it++){
                if( (*it) -> get_name() == name){
                    return *it;
                }
            }
            throw CommandNotFoundException();
        }
        void add_command(list<Command*>& list, Command* command){
            list.push_back(command);
        }

        void setup_operations(){
            list_commands.push_back(new ListOrdered("ordered", listOfArrays));
            list_commands.push_back(new ListMul("mul", listOfArrays));
            list_commands.push_back(new ListAdd("add", listOfArrays));
            list_commands.push_back(new ListShow("show", listOfArrays));
            list_commands.push_back(new ListSize("size", listOfArrays));
            list_commands.push_back(new ListAverages("averages", listOfArrays));
            list_commands.push_back(new ListMedians("medians", listOfArrays));
            list_commands.push_back(new ListSums("sums", listOfArrays));
            list_commands.push_back(new ListSizes("sizes", listOfArrays));
            
            iterator_commands.push_back(new IteratorNext("next", iterator, listOfArrays));
            iterator_commands.push_back(new IteratorShow("show", iterator));
            iterator_commands.push_back(new IteratorAt("at", iterator));
            iterator_commands.push_back(new IteratorSize("size", iterator));
            iterator_commands.push_back(new IteratorAverage("average", iterator));
            iterator_commands.push_back(new IteratorMedian("median", iterator));
            iterator_commands.push_back(new IteratorSum("sum", iterator));
            iterator_commands.push_back(new IteratorOrdered("ordered", iterator));
        }
        void execute_list_commands(string commands){
            istringstream iss(commands);
            string command;
            do{
                getline(iss, command, '.');
                //cout << command << endl;
                size_t position;
                
                if((position = command.find(":")) != string::npos){
                    try{
                        
                        Command* operation = get_list_command(command.substr(0, position));
                        
                        string parameter = command.substr(position + 1);
                        //cout << "operation: " << command.substr(0, position) << "parameter: " << command.substr(position + 1) << endl;
                        operation ->execute(parameter);
                    } catch(CommandNotFoundException e){
                        cout << "ERROR: Unknown operation";
                        break;
                    }
                    catch(CommandException e){
                        cout << e.get_message() << endl;
                    }
                }
                else{
                    try{
                        Command* operation = get_list_command(command);
                        //cout << "operation: " << command.substr(0, position) << endl;
                        operation->execute();
                    } catch(CommandNotFoundException e){
                        cout << "ERROR: Unknown operation";
                        break;
                    }
                    catch(CommandException e){
                        cout << e.get_message() << endl;
                    }
                }

            }while(!iss.eof());
        }
        void execute_iterator_commands(string commands){
            istringstream iss(commands);
            string command;
            //cout << command << endl;
            do{
                getline(iss, command, '.');
                size_t position;
                try{
                    if((position = command.find(":")) != string::npos){
                        Command* operation = get_iterator_command(command.substr(0, position));
                        string parameter = command.substr(position + 1);
                        //cout << "operation: " << command.substr(0, position) << "parameter: " << command.substr(position + 1) << endl;
                        operation->execute(parameter);
                    }
                    else{
                        Command* operation = get_iterator_command(command);
                        //cout << "operation: " << command.substr(0, position) << endl;
                        operation->execute();
                    }
                } catch(CommandNotFoundException e){
                    cout << "ERROR: Unknown operation";
                    break;
                }
                catch(CommandException e){
                    cout << e.get_message() << endl;
                }

            }while(!iss.eof());
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
    
    public:
        ListParser() {
            iterator = listOfArrays.begin();
        }
        
        void parse(){
            setup_operations();
            read_matrix();

            string commands;
            cout.precision(3);
            cout << "> ";
            do{
                listOfArrays = initial_list;
                getline(cin, commands);
                
                commands = regex_replace(commands, regex("^ +| +$|( ) +"), "$1");
                cout << "> " ;
                size_t position;
                if((position = commands.find("begin")) != string::npos){
                    commands.erase(position, 6);
                    iterator = listOfArrays.begin();
                    execute_iterator_commands(commands);
                }
                else {
                    execute_list_commands(commands);
                }
            }while(commands != "quit");
            //double number = 907.667;
            //cout << "precision: " << get_precision(number) << endl;
        }
        
};

int main(){
    ListParser parser;
    parser.parse();
    
}

