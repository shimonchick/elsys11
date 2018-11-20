#include <iostream>
using namespace std;

class VectorException{};
class IteratorException{};


template <typename T>
class Vector{
    private:
        int size_;
        int capacity_;
        T* data;

    public:
        Vector(int capacity_param) : size_(0), capacity_(capacity_param), data(new T[capacity_param]){}
        Vector() : size_(0), capacity_(0), data(NULL) {}
        ~Vector(){
            delete [] data;
            size_ = 0;
            capacity_ = 0;
        }
        void resize(int capacity){
            T* new_data = new T[capacity];
            for(int i = 0; i < size(); i++){
                new_data[i] = data[i];
            }
            data = new_data;
        }

        int size() const{
            return size_;
        }
        bool empty() const{
            return size_ == 0;
        }
        int capacity() const{
            return capacity_;
        }
        T& front(){
            if(empty()){
                throw VectorException();
            }
            return data[0];
        }
        const T& front() const{
            if(empty()){
                throw VectorException();
            }
            return data[0];
        }
        T& back(){
            if(empty()){
                throw VectorException();
            }
            return data[size_-1];
        }
        const T& back() const{
            return back();
        }
        void push_back(T val){
            if(size_ == capacity_){
                if(capacity_ == 0){
                    capacity_ = 1;
                    resize(capacity_);
                }
                else{
                    capacity_ *= 2;
                    resize(capacity_);

                }
            }
            data[size_] = val;
            size_++;
        }
        void pop_back(){
            if(empty()){
                throw VectorException();
            }
            size_--;
        }
        Vector(const Vector& other) : Vector(other.capacity_){
            this->size_ = other.size_;
            for(int i = 0; i < other.size(); i++){
                this->data[i] = other.data[i];
            }
        }
        void clear(){
            delete [] data;
            capacity_ = 0;
            size_ = 0;
        }


        void operator=(const Vector& other){
            this->capacity_ = other.capacity_;
            this->size = other.size_;
            for(int i = 0; i < other.size(); i++){
                this->data[i] = other.data[i];
            }
        }
        T& operator[](int index){
            return data[index];
        }
        const T& operator[](int index) const{
            return data[index];
        }
        T& at(int index){
            if(empty()){
                throw VectorException();
            }
            if(index < 0 || index >= size){
                throw VectorException();
            }
            return data[index];
        }
        class iterator{
            friend class Vector;
            private:
                int pos;
                Vector<T>* vector;
                iterator() : pos(0){}
            public:
                iterator(int position, Vector<T>* vector_param) : pos(position), vector(vector_param){}
                
                iterator& operator++(){ // ++it
                    ++pos;
                    return *this;
                }

                iterator operator++(int){ // it++
                    iterator result(pos, vector);
                    ++pos;
                    return result;    
                }
                iterator operator--(){ // --it
                    iterator result(pos, vector);
                    --pos;
                    return result;
                }
                bool operator==(const iterator& other) const{
                    return this->pos == other.pos;
                }
                bool operator!=(const iterator& other) const{
                    return ! operator==(other);
                }
                T& operator*(){
                    return vector->data[pos];
                }
                T* operator->(){
                    return vector->data[pos];
                }
                

        }; // iterator end;
        class const_iterator{
            friend class Vector;
            private:
                int pos;
                const Vector<T>* vector;
                const_iterator() : pos(0){}
            public:
                const_iterator(int position, const Vector<T>* vector_param) : pos(position), vector(vector_param){}
                
                const_iterator& operator++(){ // ++it
                    
                    ++pos;
                    return *this;
                }

                const_iterator operator++(int){ // it++
                    const_iterator result(pos, vector);
                    ++pos;
                    return result;    
                }
                const_iterator operator--(){ // --it
                    const_iterator result(pos, vector);
                    --pos;
                    return result;
                }
                bool operator==(const const_iterator& other) const{
                    return this->pos == other.pos;
                }
                bool operator!=(const const_iterator& other) const{
                    return ! operator==(other);
                }
                const T& operator*(){
                    return vector->data[pos];
                }
                const T* operator->(){
                    return vector->data[pos];
                }
                

        }; // const_iterator end;
        class reverse_iterator{
            friend class Vector;
            private:
                int pos;
                Vector<T>* vector;
                reverse_iterator() : pos(0){}
            public:
                reverse_iterator(int position,Vector<T>* vector_param) : pos(position), vector(vector_param){}
                
                reverse_iterator& operator++(){ // ++it
                    if(pos < 0){
                        throw IteratorException();
                    }
                    --pos;
                    return *this;
                }

                reverse_iterator operator++(int){ // it++
                    if(pos < 0){
                        throw VectorException();
                    }
                    reverse_iterator result(pos, vector);
                    --pos;
                    return result;    
                }
                reverse_iterator operator--(){ // --it
                    reverse_iterator result(pos, vector);
                    ++pos;
                    return result;
                }
                
                bool operator==(const reverse_iterator& other) const{
                    return this->pos == other.pos;
                }
                bool operator!=(const reverse_iterator& other) const{
                    return ! operator==(other);
                }
                T& operator*(){
                    return vector->data[pos];
                }
                T* operator->(){
                    return data[pos];
                }
                

        }; // reverse_iterator end;
        class const_reverse_iterator{
            friend class Vector;
            private:
                int pos;
                Vector<T>* vector;
                const_reverse_iterator() : pos(0){}
            public:
                const_reverse_iterator(int position,Vector<T>* vector_param) : pos(position), vector(vector_param){}
                
                const_reverse_iterator& operator++(){ // ++it
                    if(pos < 0){
                        throw IteratorException();
                    }
                    --pos;
                    return *this;
                }

                const_reverse_iterator& operator++(int){ // it++
                    if(pos < 0){
                        throw VectorException();
                    }
                    reverse_iterator result(pos, vector);
                    --pos;
                    return result;    
                }
                bool operator==(const const_reverse_iterator& other) const{
                    return this->pos == other.pos;
                }
                bool operator!=(const const_reverse_iterator& other) const{
                    return ! operator==(other);
                }
                const T& operator*(){
                    return vector->data[pos];
                }
                const T* operator->(){
                    return vector->data[pos];
                }
                
                const_reverse_iterator operator--(){ // --it
                    const_reverse_iterator result(pos, vector);
                    ++pos;
                    return result;
                }
                

        }; // reverse_iterator end;
        
        iterator begin(){
            return iterator(0, this);
        }
        iterator end(){
            return iterator(size_, this);
        }
        const_iterator begin() const{
            return const_iterator(0, this);
        }
        const_iterator end() const{
            return const_iterator(size_, this);
        }
        reverse_iterator rbegin(){
            return reverse_iterator(size_ - 1, this); 
        }
        reverse_iterator rend(){
            return reverse_iterator(-1, this);
        }
        const_reverse_iterator rbegin() const{
            return const_reverse_iterator(size - 1, this);
        }
        const_reverse_iterator rend() const{
            return const_reverse_iterator(-1, this);
        }
        iterator insert(iterator pos, const T& x){
            if(size_ + 1 >= capacity_){
                capacity_ *= 2;
                resize(capacity_);
            }
            iterator it1 = end(), it2 = --end();
            for( ; it2 != pos; --it1, --it2){
                iterator next();
                *it2 = *it1;
            }
            *it2 = x;
            return iterator(0, this);
        }
        iterator erase(iterator pos){
            for(iterator it1 = pos, it2 = ++pos; it2 != end(); it1++, it2++){
                *it2 = *it1;
            }
            size_--;

            return begin();
        }
        iterator erase(iterator first, iterator last){
            for(iterator it1 = first, it2 = last; it2 != end(); it1++, it2++){
                *it1 = *it2;
            }
            return first;
        }

};


