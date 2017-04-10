#include "list.cpp"

template <typename T>
class lStack
{
private:
    DLList ls;
    size_t maxsize = 1;
public:
    void push(T * el);
    void pop();
    T * back();
    size_t size();
    size_t showmaxsize();
    void setmaxsize(size_t value);
};

template <typename T>
void lStack<T>::push(T * el)
{
    int s = ls.size();
    ls.insert(s,el);
    if (maxsize == s) maxsize *= 2;
}

template <typename T>
void lStack<T>::pop()
{
    ls.removeBack();
}

template <typename T>
T * lStack<T>::back()
{
    if (ls.ptrend() != nullptr) return (T*)ls.ptrend()->data;
    else return nullptr;
}

template <typename T>
size_t lStack<T>::size()
{
    return ls.size();
}

template <typename T>
size_t lStack<T>::showmaxsize()
{
    return maxsize;
}

template <typename T>
void lStack<T>::setmaxsize(size_t value)
{
    maxsize = value;
    while (maxsize < ls.size()) ls.removeBack();
}

int main()
{
    testlist();

    lStack<int> lstack;
    int x = 5;
    lstack.push(&x);
    int y = -10;
    lstack.push(&y);
    int z = 47;
    lstack.push(&z);
    std::cout << lstack.showmaxsize() << std::endl
              << lstack.size() << std::endl
              << *lstack.back() << std::endl;
    lstack.pop();
    std::cout << lstack.showmaxsize() << std::endl
              << lstack.size() << std::endl
              << *lstack.back() << std::endl;
    lstack.setmaxsize(1);
    std::cout << lstack.showmaxsize() << std::endl
              << lstack.size() << std::endl
              << *lstack.back() << std::endl;
    lstack.pop();
    std::cout << lstack.showmaxsize() << std::endl
              << lstack.size() << std::endl;
    lstack.back() != nullptr ? std::cout << *lstack.back() << std::endl : std::cout << "NULL" << std::endl;
    return 0;
}
