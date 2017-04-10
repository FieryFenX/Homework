#include <iostream>

template <typename T>
class aQueue
{
private:
    T * arr = new T[1];
    size_t maxsize = 1;
    size_t _size = 0;
    void newarr(T ** ptarr, size_t newsz, size_t sz);
public:
    void push(T * el);
    void pop();
    T * top();
    size_t size();
    size_t showmaxsize();
    void setmaxsize(size_t value);
};

template <typename T>
void aQueue<T>::newarr(T ** ptarr, size_t newsz, size_t sz)
{
    T * arr1 = new T[newsz];
    for (size_t i = 0; i < std::min(sz,newsz); ++i)
        arr1[i] = (*ptarr)[i];
    delete *ptarr;
    *ptarr = arr1;
}

template <typename T>
void aQueue<T>::push(T * el)
{
    if (maxsize == _size)
    {
        maxsize *= 2;
        newarr(&arr, maxsize, _size);
    }
    arr[_size++] = *el;
}

template <typename T>
void aQueue<T>::pop()
{
    for (size_t i = 0; i < _size; ++i)
        arr[i] = arr[i+1];
    arr[_size--] = 0;
}

template <typename T>
T * aQueue<T>::top()
{
    if (_size > 0) return &arr[0];
    else return nullptr;
}

template <typename T>
size_t aQueue<T>::size()
{
    return _size;
}

template <typename T>
size_t aQueue<T>::showmaxsize()
{
    return maxsize;
}

template <typename T>
void aQueue<T>::setmaxsize(size_t value)
{
    maxsize = value;
    newarr(&arr, maxsize, _size);
    _size = std::min(maxsize, _size);
}

int main()
{
    aQueue<int> aqueue;
    int x = 5;
    aqueue.push(&x);
    int y = -10;
    aqueue.push(&y);
    int z = 47;
    aqueue.push(&z);
    std::cout << aqueue.showmaxsize() << std::endl
              << aqueue.size() << std::endl
              << *aqueue.top() << std::endl;
    aqueue.pop();
    std::cout << aqueue.showmaxsize() << std::endl
              << aqueue.size() << std::endl
              << *aqueue.top() << std::endl;
    aqueue.setmaxsize(1);
    std::cout << aqueue.showmaxsize() << std::endl
              << aqueue.size() << std::endl
              << *aqueue.top() << std::endl;
    aqueue.pop();
    std::cout << aqueue.showmaxsize() << std::endl
              << aqueue.size() << std::endl;
    aqueue.top() != nullptr ? std::cout << *aqueue.top() << std::endl : std::cout << "NULL" << std::endl;
    return 0;
}
