#include <iterator>

template<typename T>
class MyQueue{
    private:
        T* my_queue;
        int size_queue;

    public:
        MyQueue();
        MyQueue(T collection);
        ~MyQueue(){delete[] this->my_queue;}

    public:
        void pushBack(T element);
        T getFirst(){
            //if(this->size_queue == 0) return NAN; //we need exeption
            return this->my_queue[0];
        }
        void popFirst();
        bool isEmpty(){return (this->size_queue == 0)?(true):(false);}
        int getSize(){return this->size_queue;}

    class Iterator : public std::iterator<std::input_iterator_tag, T>{
        private:
            T* ptr;

        public:
            explicit Iterator(T* p) : ptr(p) {}
            Iterator(const Iterator& other) : ptr(other.ptr) {}

            Iterator& operator++() {
                ++ptr;
                return *this;
            }
            Iterator operator++(int) {
                Iterator tmp(*this);
                operator++(); 
                return tmp; 
            }
            bool operator==(const Iterator& rhs) const { return ptr == rhs.ptr; }
            bool operator!=(const Iterator& rhs) const { return ptr != rhs.ptr; }
            T& operator*() { return *ptr; }
    };

    Iterator begin() { return Iterator(my_queue); }
    Iterator end() { return Iterator(my_queue + size_queue); }


};

template<typename T>
MyQueue<T>::MyQueue(){
    this->my_queue = new T[0];
    this->size_queue = 0;
}

template<typename T>
MyQueue<T>::MyQueue(T collection){
    this->my_queue = new T[0];
    this->size_queue = 0;

    for(auto a:collection){
        this->my_queue.pushBack(a);
        this->size_queue++;
    }
}



template<typename T>
void  MyQueue<T>::pushBack(T element){
    T pereh[this->size_queue];
    for (int i = 0; i < this->size_queue; i++){
        pereh[i] = this->my_queue[i];
    }

    delete[] this->my_queue;

    this->my_queue = new T[this->size_queue + 1];
    for (int i = 0; i < this->size_queue; i++){
        this->my_queue[i] = pereh[i];
    }

    this->my_queue[this->size_queue] = element;
    this->size_queue++; 
    
    return;
}

template<typename T>
void MyQueue<T>::popFirst(){
    T pereh[this->size_queue];
    for (int i = 0; i < this->size_queue; i++){
        pereh[i] = this->my_queue[i];
    }

    delete[] this->my_queue;

    this->my_queue = new T[this->size_queue - 1];
    this->size_queue--; 
    for (int i = 0; i < this->size_queue; i++){
        this->my_queue[i] = pereh[i + 1];
    } 
    
    return;
}
