#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>


using namespace std;

class IteratorException{};

class ListOfArrays {
    private:
        class ArrayNode {
            public:

                int* data_;
                int size_;
                ArrayNode* prev_;
                ArrayNode* next_;

                ArrayNode(int* data, int size)
                    : data_(data), size_(size), next_(nullptr), prev_(nullptr) {}

                ~ArrayNode() {
                    delete [] data_;
                }

        };

        ArrayNode* head_;
        int size_;

    public:

    class Iterator {

        friend class ListOfArrays;
        ArrayNode* current_;
        public:

        Iterator(ArrayNode* current)
            : current_(current) {}

        bool operator==(const Iterator& other){
            if(current_->size_ != other.current_->size_){
                return false;
            }
            for(int i = 0; i < size(); i++){
                if(current_->data_[i] != other.current_->data_[i]){
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const Iterator& other){
            return ! operator==(other);
        }

        Iterator& operator++(){ // ++it
            current_ = current_->next_;
            return *this;
        }

        Iterator operator++(int){ // it++
            Iterator result(current_);
            current_ = current_->next_;
            return result;
        }
        Iterator& operator--(){ // --it
            current_ = current_->prev_;
            return *this;
        }
        bool operator<(const Iterator& other){
            if(this->size() > other.size()) return false;
            if(this-> size() < other.size()) return true;
            
            for(int i = 0; i< size(); i++){
                if(current_->data_[i] > other.current_->data_[i]) return false;
            }
            return true;
        }
        bool operator>(const Iterator& other){
            if(this->size() < other.size()) return false;
            if(this-> size() > other.size()) return true;
            
            for(int i = 0; i< size(); i++){
                if(current_->data_[i] < other.current_->data_[i]) return false;
            }
            return true;
        
        }
        int& operator[](const int& index){
            if(size() == 0){
                throw IteratorException();
            }
            if(index >= 0 && index < size()){
                return current_->data_[index];
            }
        }

        int size() const{
            return current_->size_;
        }

        void show(){
            for(int i = 0; i < size(); i++){
                cout << current_->data_[i] << " ";
            }
            cout << ";";
        }
        
        double average(){
            return sum() / size();
        }
        
        double median(){
            ordered(true); // sort 
            if(size() % 2 == 0){ // check even
                double median = (current_->data_[size()/2] + current_->data_[size()/2 + 1]) / 2;
                return median;
            }
            else{
                return current_->data_[size()/2];
            }
        }
        
        int sum(){
            int sum = 0;
            for(int i = 0; i < size(); i++){
                sum += current_->data_[i];
            }
            return sum;
        }
        
        Iterator& ordered(bool ascending = true){
            for(int i = 0; i < size(); i++){
                for(int j = i; j < size() - 1; j++){
                    if(ascending){
                        if(current_->data_[j] > current_->data_[j + 1]){
                            int temp = current_->data_[j];
                            current_->data_[j] = current_->data_[j + 1];
                            current_->data_[j+1] = temp;
                        }
                    }
                    else{
                        if(current_->data_[j] < current_->data_[j + 1]){
                            int temp = current_->data_[j];
                            current_->data_[j] = current_->data_[j + 1];
                            current_->data_[j+1] = temp;
                        }
                    }
                }
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
        for(ArrayNode* current = head_->next_; current != head_; current = current->next_){
            ArrayNode* node = current;
            delete node;
        }
    }

    ListOfArrays(const ListOfArrays& other) : ListOfArrays(){
        for(ArrayNode* current = other.head_->next_; current != head_; current = current->next_){
            push(current->data_, 0, current->size_);
        }
    }

    ListOfArrays& operator=(const ListOfArrays& other){
        for(ArrayNode* current = other.head_->next_; current != head_; current = current->next_){
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

        delete data;
    }

    void averages(double averages[]){
        int i = 0;
        for(Iterator it = begin(); it != end(); it++){
            averages[i] = it.average();
        }
    }

    void medians(double medians[]){
        int i = 0;
        for(Iterator it = begin(); it != end(); it++){
            medians[i] = it.median();
        }

    }
    
    void sizes(int sizes[]){
        int i = 0;
        for(Iterator it = begin(); it != end(); it++){
            sizes[i] = it.size();
        }

    }
    
    void sums(int sums[]){
        int i = 0;
        for(Iterator it = begin(); it != end(); it++){
            sums[i] = it.sum();
        }

    }

    Iterator begin(){
        return Iterator(head_->next_);
    }

    Iterator end(){
        return Iterator(head_);
    }

    ListOfArrays& ordered(bool ascending = true){
        for(Iterator it = begin(); it != end(); it++){
            it.ordered(ascending);
        }
        for(Iterator it1 = begin(); it1 != end(); it1++){
            for(Iterator it2 = it1; it2 != --end(); it2++){
                if(ascending){
                    if(it1 > it2){
                        Iterator* temp = &it1;
                        it1 = it2;
                        it2 = *temp;
                    }
                }
                else{
                    if(it1 < it2){
                        Iterator* temp = &it1;
                        it1 = it2;
                        it2 = *temp;
                    }
                }
            }
        }
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
        cout <<"> >";
        for(Iterator it = begin; it != end(); it++){
            it.show;
        }
        cout << endl;
    }
};

class ListParser{
    private:
        ListOfArrays list;
    public:
        
        void parse(){
            read_matrix();
            string commands;
            do{
                cout << "> ";
                getline(cin, commands);
                execute_line(commands);
            }while(commands != "quit");
        }
        void read_matrix(){
            string array;
            while(!(getline(cin, array, ';').eof())){
                istringstream values(array);
                int* data = new int[this->list.size()];
                int count = 0;
                while(!values.eof()){
                    values >> data[count];
                    count++;
                }
                list.push(data, 0, count);
                delete data;
            }
        }
        void execute_line(const string& commands){
            istringstream iss(commands);
            string command;
            do{
                getline(iss, command, '.');
                if(command == "show"){
                    list.show();
                }
                else if(command == "size"){
                    list.size();
                }
                else if(command == "averages"){
                    double* averages = new double[list.size()];
                    list.averages(averages);
                    cout << "> ";
                    for(int i = 0; i < list.size(); i++){
                        cout << averages[i] << " ";
                    }
                    cout << endl;
                }
                else if(command == "medians"){
                    double* medians = new double[list.size()];
                    list.medians(medians);
                    cout << "> ";
                    for(int i = 0; i < list.size(); i++){
                        cout << medians[i] << " ";
                    }
                    cout << endl;

                }
                else if(command == "sizes"){
                    cout << "> ";
                    for(Iterator it = list.begin(); it!= list.end(); it++){

                    }
                    cout << endl;

                }
                else if(command == "sum"){
                    cout << list.sum() << endl;
                }
                else if(command == "")
            }while(!iss.eof());
        }
};

int main(){
    
}
