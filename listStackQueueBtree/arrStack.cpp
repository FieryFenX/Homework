#include <iostream>

template <typename T>
class aStack
{
private:
    T * arr = new T[1];
    size_t maxsize = 1;
    size_t _size = 0;
    void newarr(T ** ptarr, size_t newsz, size_t sz);
public:
    void push(T * el);
    void pop();
    T * back();
    size_t size();
    size_t showmaxsize();
    void setmaxsize(size_t value);
};

template <typename T>
void aStack<T>::newarr(T ** ptarr, size_t newsz, size_t sz)
{
    T * arr1 = new T[newsz];
    for (size_t i = 0; i < std::min(sz,newsz); ++i)
        arr1[i] = (*ptarr)[i];
    delete *ptarr;
    *ptarr = arr1;
}

template <typename T>
void aStack<T>::push(T * el)
{
    if (maxsize == _size)
    {
        maxsize *= 2;
        newarr(&arr, maxsize, _size);
    }
    arr[_size++] = *el;
}

template <typename T>
void aStack<T>::pop()
{
    arr[_size--] = 0;
}

template <typename T>
T * aStack<T>::back()
{
    if (_size > 0) return &arr[_size - 1];
    else return nullptr;
}

template <typename T>
size_t aStack<T>::size()
{
    return _size;
}

template <typename T>
size_t aStack<T>::showmaxsize()
{
    return maxsize;
}

template <typename T>
void aStack<T>::setmaxsize(size_t value)
{
    maxsize = value;
    newarr(&arr, maxsize, _size);
    _size = std::min(maxsize, _size);
}

int ()
{
    aStack<int> astack;
    int x = 5;
    astack.push(&x);
    int y = -10;
    astack.push(&y);
    int z = 47;
    astack.push(&z);
    std::cout << astack.showmaxsize() << std::endl
              << astack.size() << std::endl
              << *astack.back() << std::endl;
    astack.pop();
    std::cout << astack.showmaxsize() << std::endl
              << astack.size() << std::endl
              << *astack.back() << std::endl;
    astack.setmaxsize(1);
    std::cout << astack.showmaxsize() << std::endl
              << astack.size() << std::endl
              << *astack.back() << std::endl;
    astack.pop();
    std::cout << astack.showmaxsize() << std::endl
              << astack.size() << std::endl;
    astack.back() != nullptr ? std::cout << *astack.back() << std::endl : std::cout << "NULL" << std::endl;
    return 0;
}
