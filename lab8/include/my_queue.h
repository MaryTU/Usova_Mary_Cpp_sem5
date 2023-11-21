#include <stdexcept>

template<typename T>
class MyQueue{
    private:
        T* my_queue;
        int size_queue;

    public:
        /**
         * @brief Construct a new My Queue object
         * 
         */
        MyQueue();
        /**
         * @brief Destroy the My Queue object
         * 
         */
        ~MyQueue(){delete[] this->my_queue;}

    public:
        /**
         * @brief add element in the end queue
         * 
         * @param element added element
         */
        void pushBack(T element);
        /**
         * @brief Get the First element in the queue
         * 
         * @return T First element in the queue
         */
        T getFirst(){
            if(this->size_queue == 0) throw std::runtime_error("The queue is empty"); //we need exeption else we get undef value
            return this->my_queue[0];
        }
        /**
         * @brief delete first element from the queue
         * 
         */
        void popFirst();
        /**
         * @brief check if the queue is empty
         * 
         * @return true if the queue is empty
         * @return false if the queue isn't empty
         */
        bool isEmpty(){return (this->size_queue == 0)?(true):(false);}
        /**
         * @brief Get an amount all elements in queue
         * 
         * @return int amount all elements in queue
         */
        int getSize(){return this->size_queue;}

    private:
        class Iterator{
            private:
                T* ptr; ///< Указатель на элемент контейнера

            public:
                /**
                 * @brief Конструктор, принимающий указатель на элемент контейнера
                 * 
                 * @param p Указатель на элемент контейнера
                 */
                explicit Iterator(T* p) : ptr(p) {}
                 /**
                 * @brief Конструктор копирования
                 * 
                 * @param other Другой объект Iterator
                 */
                Iterator(const Iterator& other) : ptr(other.ptr) {}

                /**
                 * @brief Оператор префиксного инкремента
                 * 
                 * Увеличивает указатель на один и возвращает ссылку на текущий объект
                 * 
                 * @return Iterator& Ссылка на текущий объект
                 */
                Iterator& operator++() { ++ptr; return *this; }
                // /**
                //  * @brief Оператор постфиксного инкремента
                //  * 
                //  * Создает временный объект, увеличивает указатель на один и возвращает временный объект
                //  * 
                //  * @return Iterator Временный объект
                //  */
                // Iterator operator++(int) {
                //     Iterator tmp(*this);
                //     operator++(); 
                //     return tmp; 
                // }
                /**
                 * @brief Оператор сравнения на равенство
                 * 
                 * Возвращает true, если два итератора указывают на одно и то же место
                 * 
                 * @param rhs Другой объект Iterator
                 * @return true Если два итератора указывают на одно и то же место
                 * @return false В противном случае
                 */
                bool operator==(const Iterator& rhs) const { return ptr == rhs.ptr; }
                /**
                 * @brief Оператор сравнения на неравенство
                 * 
                 * Возвращает true, если два итератора указывают на разные места
                 * 
                 * @param rhs Другой объект Iterator
                 * @return true Если два итератора указывают на разные места
                 * @return false В противном случае
                 */
                bool operator!=(const Iterator& rhs) const { return ptr != rhs.ptr; }
                /**
                 * @brief Оператор разыменования
                 * 
                 * Возвращает ссылку на элемент контейнера, на который указывает ptr
                 * 
                 * @return T& Ссылка на элемент контейнера
                 */
                T& operator*() { return *ptr; }
        };
    
    public:
         /**
         * @brief Возвращает итератор, указывающий на начало контейнера
         * 
         * @return Iterator Итератор, указывающий на начало контейнера
         */
        Iterator begin() { return Iterator(my_queue); }
        /**
         * @brief Возвращает итератор, указывающий на конец контейнера
         * 
         * @return Iterator Итератор, указывающий на конец контейнера
         */
        Iterator end() { return Iterator(my_queue + size_queue); }


};

template<typename T>
MyQueue<T>::MyQueue(){
    this->my_queue = new T[0];
    this->size_queue = 0;
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
