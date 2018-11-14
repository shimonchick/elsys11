

#include <iostream>

using namespace std;

class ListException{};
template<typename T>
class List{
    private:
        class Node{
            public:

                T data;
                Node* prev;
                Node* next;
                Node(T val) : data(val), prev(NULL), next(NULL){}

        };
    public:
        Node* head;
        Node* tail;
        int size;
        List(): head(NULL), tail(NULL), size(0){}
        List(const List& other){
            List();
            Node* node = &(other.head);
            while(node != NULL){
                push_back(node->data);
                node = node->next;
            }
        }
        List& operator=(const List& other){
            if(this != &other){
                clear();
                Node* node = &(other.head);
                while(node !=NULL){
                    push_back(node->data);
                    node = node->next;
                }
            }
        }

        void push_back(const T& val){
            Node* temp = new Node(val);
            if(empty()){
                head = temp;
                tail = temp;
                size ++;
            }
            else{
                tail->next = temp;
                temp->prev = tail;
                temp->next = 0;
                tail = temp;
                size++;
            }
        }

        T pop_back(){
            if(empty()){
                throw ListException();
            }
            else{
                T result;
                result = tail->data;
                Node* current = tail;
                if(tail->prev){
                    tail = tail->prev;
                    tail->next = NULL;
                }
                else{
                    tail = NULL;
                    head = NULL;
                }
                delete current;

                size--;
                

                return result;
            }
        }
        bool empty() const{
            return size == 0;
        }
        T back() const{
            if(empty()){
                throw ListException();
            }
            return tail->data;
        }
        void clear(){
            while(!empty()){
                pop_back();
            }
        }
        int length(){
            return size;
        }
        T element_at(int index){
            if(index >= length()){
                throw ListException();
            }
            if(index >=0){
                Node* current = head;
                for(int i = 0; i < index; i++){
                    current = current->next;
                }
                return current;

            } else{
                Node * current = tail;
                for(int i = 0; i < index; i++){
                    current = current->prev;
                }
                return current;
            }
        }

        ~List(){
            clear();
        }

        class iterator{
            friend class List; // so we can call private constructor
            private:
                Node* current;
                iterator(Node* node = NULL) : current(node) {}

            public:
                T& operator*(){
                    return current->data;
                }
                
                iterator& operator++(){ // ++it
                    current = current->next;
                    return *this;
                }
                iterator operator++(int){ //it++ increments, but returns the operator before incrementing
                    iterator result(current);
                    
                    current = current->next;
                    
                    return result;
                }
                iterator& operator--(){ // --it 
                    current = current->prev;
                    return *this;
                }
                iterator operator--(int){
                    iterator result(current);
                    current=current->prev;
                    return result;
                }

                bool operator==(const iterator& other){
                    return this->current == other.current;
                }
                bool operator!=(const iterator& other){
                    return ! operator==(other);
                }

        }; // iterator end
        class const_iterator{
            friend class List; // so we can call private constructor
            private:
                Node* current;
                const_iterator(Node* node = NULL) : current(node) {}

            public:
                const T& operator*(){
                    return current->data;
                }
                
                const_iterator& operator++(){ // ++it
                    current = current->next;
                    return *this;
                }
                const_iterator operator++(int){ //it++ increments, but returns the operator before incrementing
                    const_iterator result(current);
                    
                    current = current->next;
                    
                    return result;
                }
                const_iterator& operator--(){ // --it 
                    current = current->prev;
                    return *this;
                }
                const_iterator operator--(int){
                    const_iterator result(current);
                    current=current->prev;
                    return result;
                }

                bool operator==(const const_iterator& other){
                    return this->current == other.current;
                }
                bool operator!=(const const_iterator& other){
                    return this->current != other.current;
                }

        }; // const_iterator end
        class reverse_iterator{
            friend class List; // so we can call private constructor
            private:
                Node* current;
                reverse_iterator(Node* node) : current(node) {}

            public:
                reverse_iterator() : current(nullptr){}
                T& operator*(){
                    return current->data;
                }
                
                reverse_iterator& operator++(){ // ++it
                    current = current->prev;
                    return *this;
                }
                reverse_iterator operator++(int){ //it++ increments, but returns the operator before incrementing
                    reverse_iterator result(current);

                    current = current->prev;
                    
                    return result;
                }
                reverse_iterator& operator--(){ // --it 
                    current = current->next;
                    return *this;
                }
                reverse_iterator operator--(int){
                    reverse_iterator result(current);
                    current = current->next;
                    return result;
                }

                bool operator==(const reverse_iterator& other){
                    return current == other.current;
                }
                bool operator !=(const reverse_iterator& other){
                    return ! operator==(other);
                }
        }; //reverse iterator end

        iterator begin() {
            return iterator(head);
        }
        iterator end() {
            return iterator(NULL);
        }
        const_iterator begin() const{
            return const_iterator(head);
        }
        const_iterator end() const{
            return const_iterator(NULL);
        }
        reverse_iterator rend() const{
            return reverse_iterator(NULL);
        }
        reverse_iterator rbegin() const{
            return reverse_iterator(tail);
        }

};

int main(){

    List<int> l1;
    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(32);
    const List<int>& cl = l1;
    for(List<int>::const_iterator it = cl.begin(); it != cl.end(); it++){
       // *it = 333;
        cout << *it << endl;
    }
    return 0;

}

