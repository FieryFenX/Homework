#include "list.cpp"

template <typename T>
class lQueue
{
private:
    DLList ls;
    size_t maxsize = 1;
public:
    void push(T & el);
    void pop();
    T * top();
    size_t size();
    size_t showmaxsize();
    void setmaxsize(size_t value);
};

template <typename T>
void lQueue<T>::push(T & el)
{
    int s = ls.size();
    ls.insert(s,&el);
    if (maxsize == s) maxsize *= 2;
}

template <typename T>
void lQueue<T>::pop()
{
    ls.removeFront();
}

template <typename T>
T * lQueue<T>::top()
{
    if (ls.ptrbegin() != nullptr) return (T*)ls.ptrbegin()->data;
    else return nullptr;
}

template <typename T>
size_t lQueue<T>::size()
{
    return ls.size();
}

template <typename T>
size_t lQueue<T>::showmaxsize()
{
    return maxsize;
}

template <typename T>
void lQueue<T>::setmaxsize(size_t value)
{
    maxsize = value;
    while (maxsize < ls.size()) ls.removeBack();
}

int main()
{
    testlist();

    lQueue<int> lqueue;
    int x = 5;
    lqueue.push(x);
    int y = -10;
    lqueue.push(y);
    int z = 47;
    lqueue.push(z);
    std::cout << lqueue.showmaxsize() << std::endl
              << lqueue.size() << std::endl
              << *lqueue.top() << std::endl;
    lqueue.pop();
    std::cout << lqueue.showmaxsize() << std::endl
              << lqueue.size() << std::endl
              << *lqueue.top() << std::endl;
    lqueue.setmaxsize(1);
    std::cout << lqueue.showmaxsize() << std::endl
              << lqueue.size() << std::endl
              << *lqueue.top() << std::endl;
    lqueue.pop();
    std::cout << lqueue.showmaxsize() << std::endl
              << lqueue.size() << std::endl;
    lqueue.top() != nullptr ? std::cout << *lqueue.top() << std::endl : std::cout << "NULL" << std::endl;
    return 0;
}
