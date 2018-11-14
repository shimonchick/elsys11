#include <iostream>
using namespace std;

class ListException{};
class List{
    private:
        struct Node{
            int data;
            Node* prev;
            Node* next;
            Node(int data_param) : data(data_param) {}
            
        
        };

        Node* head;

    public:
        List() : head(new Node(0)){
            head->next = head;
            head->prev = head;
        }

        List(const List& other) : List() {
            Node* node = other.head->next;
            while(node != other.head){
                push_back(node->data);
                node = node->next;
            }

        }

        List& operator=(const List& other){
            if(this != &other){
                clear();
                Node* node = other.head -> next;
                while(node != other.head){
                    push_back(node->data);
                    node = node->next;
                }
            }
            return *this;
        }
        void push_back(int value){
            Node* current = new Node(value);
            Node* last = head->prev;
            
            last->next = current;
            current->prev = last;

            head->prev = current;
            current->next = head;

        }
        void clear(){
            while(!empty()){
                pop_back();
            }

        }
        int pop_back(){
            if(empty()){
                throw ListException();
            }
            Node* last = head->prev;
            Node* previous = last->prev;
            
            previous->next = last->next;
            head->prev = previous;

            int result = last->data;
            
            delete last;

            return result;
        }
        int back() const{
            if(empty()){
                throw ListException();
            }
            return head->prev->data; 
        }
        bool empty() const{
            return head->prev == head;
        }
        ~List(){
            clear();
            delete head;

        }


};

int main(){
    List l1;
    try{
        l1.push_back(5);
    } catch(ListException e){
        cout << "List is empty" << endl;
    }
    cout << l1.back();

    return 0;
}
