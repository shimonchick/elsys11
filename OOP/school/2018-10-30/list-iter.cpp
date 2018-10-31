
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
        size_t size;
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
                temp->next = NULL;
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

                size --;
                

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
        ~List(){
            clear();
        }

        class iterator{
            friend class List; // so we can call private constructor
            private:
                Node* current;
                iterator(Node* node) : current(node) {}

            public:
                iterator() : current(nullptr){}
                T& operator*(){
                    return current->data;
                }
                
                iterator& operator++(){ // ++it
                    current = current->next;
                    return *this;
                }
                iterator operator++(int){ //it++ increments, but returns the operator before incrementing
                    iterator result(current);

                    current = current-> next;
                    
                    return result;
                }
                iterator& operator--(){ // --it 
                    current = current->prev;
                    return *this;
                }
                iterator operator--(int){
                    iterator result(current);
                    current = current->prev;
                    return result;
                }

                bool operator==(const iterator& other){
                    return current == other.current;
                }
                bool operator !=(const iterator& other){
                    return ! operator==(other);
                }

        }; // iterator end
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

        iterator begin(){
            return iterator(head);
        }
        iterator end(){
            return iterator(tail + 1);
        }
        reverse_iterator rend(){
            return reverse_iterator(tail);
        }
        reverse_iterator rbegin(){
            return reverse_iterator(head);
        }

};

int main(){

    List<int> l1;
    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(32);
    cout << l1.back() << endl;

    List<int>::iterator it = l1.begin();
    cout << "*it = " << *it << endl;
    *it = 18;
    ++it;
    cout << "*it =" << *it << endl;

    int v2 = *(it++);
    cout << "v2 =" << v2 << endl;

    if(it == l1.end()){
        cout << "End of list" << endl;
    }
    for(List<int>::iterator it1 = l1.begin(); it1 != l1.end(); ++it1){
        cout << *it1 << endl;
    }
/*    for(List<int>::reverse_iterator it2 = l1.rend(); it2 != l1.rbegin(); ++it2){
        cout << *it2 << endl;
    } */
    return 0;

}

