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

};

class iterator{

};


int main(){

    List<int> l1;
    try{
        for(int i = 0; i < 10; i++){
            l1.push_back(i);
        }        
        for(int i = 0; i < 10; i++){
            cout << l1.pop_back() << endl;
        }
    } catch(ListException e){
        cout << "List is empty" << endl;
    }

    return 0;
}
