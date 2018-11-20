#include <iostream>
#include <iostream>
#include <cstring>

using namespace std;
class StringException{};

class String{
    private:
        int capacity_;
        int size_;
        char* buffer_;
    public:
        String(int capacity) : capacity_(capacity), size_(0), buffer_(new char[capacity]){}
        String(const char* str) {
            size_  = strlen(str);
            capacity_ = size_ + 1;
            buffer_ = new char[capacity_];
            for(int i = 0; i < size_; i++){
                buffer_[i] = str[i];
            }
        }
        String(const String& other) : String(other.capacity_){
            size_ = other.size_;
            for(int i = 0; i< size_; i++){
                buffer_[i] = other.buffer_[i];
            }
        }
        String& operator=(const String& other){
            size_ = other.size_;
            capacity_ = other.capacity;
            delete buffer_;
            buffer_ = new char[other.capacity_];
            for(int i = 0; i < size_; i++){
                buffer_[i] = other.buffer_[i];
            }
        }

        ~String(){
            clear();
        }

        int size() const{
            return size_;
        }
        int length() const{
            return size_;
        }
        int capacity() const{
            return capacity_;
        }
        bool empty() const{
            return size_ == 0;
        }
        void clear(){
            delete [] buffer_;
            size_ = 0;
            capacity_ = 0;
            buffer_ = nullptr;
        }
        char& operator[](int index) const{
            if(buffer_){
                return buffer_[index];
            }
        }
        char& at(int index) const{
            if(index >= 0 && index < size_){
                return buffer_[index];
            }
        }
        bool operator==(const String& other){
            strcmp(buffer_, other.buffer_) == 0;
        }
        bool operator!=(const String& other){
            return strcmp(buffer_, other.buffer_) != 0;
        }
        bool operator<(const String& other){
            return strcmp(buffer_, other.buffer_) < 0;
        }
        bool operator>(const String& other){
            return strcmp(buffer_, other.buffer_) > 0;
        }

        bool operator<=(const String& other){
            return ! operator<(other);
        }
        bool operator>=(const String& other){
            return ! operator>(other);
        }
        class iterator{
            friend class String;
            private:
                int pos;
                String* string;
            public:
                iterator(int position, String* string_param) : pos(position), string(string_param){}
                char& operator*(){
                    return string->buffer_[pos];
                }
                iterator operator++(){ // ++it
                    iterator result(pos, string);
                    pos++;
                    return result;
                }
                iterator operator++(int){ // it++
                    pos++;
                    return iterator(pos, string);
                }


        }; // iterator end
        iterator begin(){
            return iterator(0, this);
        }
        iterator end(){
            return iterator(size_, this);
        }
};

ostream& operator<<(ostream& out, const String& str){
    for(int i = 0; i < str.size(); i++){
        out<<str[i];
    }
}


int main(){

    return 0;
}
