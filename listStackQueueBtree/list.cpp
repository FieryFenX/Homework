#include <iostream>
#include <cstdlib>

struct Node
{
    int key;
    Node * prev;
    void * data;
    Node * next;
public:
    Node();
};

Node::Node():
    key(0),
    prev(nullptr),
    data(nullptr),
    next(nullptr)
{
}

class DLList
{
private:
    Node * begin = nullptr;
    Node * end = nullptr;
public:
    size_t size();
    void * find(int key);
    Node * ptrbegin();
    Node * ptrend();
    Node * findNode(int key);
    void insert(int key, void * data);
    void remove(int key);
    void removeFront();
    void removeBack();
};

size_t DLList::size()
{
    int * k = new int(0);
    Node * it = begin;
    for(;it != nullptr; (*k)++) it = it->next;
    return *k;
}

void * DLList::find(int key)
{
    Node * elb = begin;
    Node * ele = end;
    if (elb == nullptr) return nullptr;
    while ((elb->key != key) && (ele->key != key))
    {
       elb = elb->next;
       ele = ele->prev;
    }
    if (ele->key == key) return elb->data;
    return ele->data;
}

Node * DLList::ptrbegin()
{
    return begin;
}

Node * DLList::ptrend()
{
    return end;
}

Node * DLList::findNode(int key)
{
    Node * elb = begin;
    Node * ele = end;
    while ((elb != nullptr) && (elb->key != key) && (ele->key != key))
    {
       elb = elb->next;
       ele = ele->prev;
    }
    if (elb == nullptr) return nullptr;
    if (ele->key == key) return elb;
    return ele;
}

void DLList::insert(int key, void * data)
{
    Node * d = findNode(key);
    if (d != nullptr)
    {
        std::free(d->data);
        d->data = data;
        return;
    }
    Node * newNode = new Node;
    newNode->key = key;
    newNode->data = data;
    if (begin == nullptr)
    {
        begin = newNode;
        end = newNode;
        return;
    }
    newNode->prev = end;
    end->next = newNode;
    end = newNode;
}

void DLList::remove(int key)
{
    Node * d = findNode(key);
    if (d == nullptr) return;
    if (d == begin)
    {
        removeFront();
        return;
    }
    if (d == end)
    {
        removeBack();
        return;
    }
    d->prev->next = d->next;
    d->next->prev = d->prev;
    delete d;
}

void DLList::removeFront()
{
    if (begin == nullptr) return;
    Node * d = begin;
    begin = begin->next;
    delete d;
    if (begin != nullptr) begin->prev = nullptr;
    else end = nullptr;
}

void DLList::removeBack()
{
    if (end == nullptr) return;
    Node * d = end;
    end = end->prev;
    delete d;
    if (end != nullptr) end->next = nullptr;
    else begin = nullptr;
}

void testlist()
{
    DLList dllist;
    int k = 345;
    dllist.insert(0,&k);
    char c = '3';
    dllist.insert(2,&c);
    double x = 34.5;
    dllist.insert(1,&x);
    std::cout << dllist.size() << std::endl;
    std::cout << *(int*)dllist.ptrbegin()->data << std::endl;
    std::cout << *(char*)dllist.find(2) << std::endl;
    std::cout << *(double*)dllist.ptrend()->data << std::endl;
    dllist.remove(2);
    std::cout << dllist.size() << std::endl;
    std::cout << *(double*)dllist.ptrbegin()->next->data << std::endl;
    std::cout << *(int*)dllist.ptrend()->prev->data << std::endl;
    dllist.removeFront();
    std::cout << dllist.size() << std::endl;
    std::cout << *(double*)dllist.ptrbegin()->data << std::endl;
    std::cout << *(double*)dllist.ptrend()->data << std::endl;
    dllist.removeBack();
    std::cout << dllist.size() << std::endl;
    if (dllist.ptrbegin() == nullptr) std::cout << "List is empty" << std::endl;
    else
    {
        std::cout << dllist.ptrbegin()->data << std::endl;
        std::cout << dllist.ptrend()->data << std::endl;
    }
}
