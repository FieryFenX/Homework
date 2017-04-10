#include <iostream>
#include <vector>

template <typename T>
struct BTNode
{
    T key;
    BTNode<T> * left;
    BTNode<T> * right;
    BTNode<T> * p;
public:
    BTNode();
};

template <typename T>
BTNode<T>::BTNode():
    key(0),
    left(nullptr),
    right(nullptr),
    p(nullptr)
{
}

template <typename T>
class Bin_tree
{
private:
    BTNode<T> * top = nullptr;
public:
    BTNode<T> * BTfind(T key);
    BTNode<T> * BTfind(BTNode<T> * node, T key);
    void BTinsert(T key);
    void BTinsert(BTNode<T> * node, T key);
    void BTdelete(T key);
    void BTwalk(std::vector<T> * vec);
    void BTwalk(BTNode<T> * node, std::vector<T> * vec);
    T key(BTNode<T> * node);
    BTNode<T> * left(BTNode<T> * node);
    BTNode<T> * right(BTNode<T> * node);
    BTNode<T> * p(BTNode<T> * node);
};

template <typename T>
BTNode<T> * Bin_tree<T>::BTfind(T key)
{
    return BTfind(top, key);
}

template <typename T>
BTNode<T> * Bin_tree<T>::BTfind(BTNode<T> * node, T key)
{
    if (node == nullptr) return nullptr;
    if (node->key == key) return node;
    if (key < node->key) return BTfind(node->left, key);
    if (key > node->key) return BTfind(node->right, key);
}

template <typename T>
void Bin_tree<T>::BTinsert(T key)
{
    if (top == nullptr)
    {
        BTNode<T> * newnode = new BTNode<T>;
        newnode->key = key;
        top = newnode;
        return;
    }
    BTinsert(top, key);
}

template <typename T>
void Bin_tree<T>::BTinsert(BTNode<T> * node, T key)
{
    if (key < node->key)
    {
        if (node->left == nullptr)
        {
            BTNode<T> * newleft = new BTNode<T>;
            newleft->key = key;
            newleft->p = node;
            node->left = newleft;
            return;
        }
        BTinsert(node->left, key);
    }
    if (key > node->key)
    {
        if (node->right == nullptr)
        {
            BTNode<T> * newright = new BTNode<T>;
            newright->key = key;
            newright->p = node;
            node->right = newright;
            return;
        }
        BTinsert(node->right, key);
    }

}

template <typename T>
void Bin_tree<T>::BTdelete(T key)
{
    BTNode<T> * node = BTfind(key);
    if (node == nullptr) return;
    if ((node->left != nullptr) && (node->right != nullptr))
    {
        BTNode<T> * successor = node->right;
        while (successor->left != nullptr) successor = successor->left;
        std::swap(node->key, successor->key);
        node = successor;
    }
    if ((node->left == nullptr) && (node->right == nullptr))
    {
        delete node;
        return;
    }
    if ((node->left == nullptr) && (node->right != nullptr))
    {
        BTNode<T> * swapnode = node;
        if (node->p->left == node) node->p->left = node->right;
        else node->p->right = node->right;
        delete swapnode;
        node = node->right;
        node->right = nullptr;
        return;
    }
    if ((node->left != nullptr) && (node->right == nullptr))
    {
        BTNode<T> * swapnode = node;
        if (node->p->left == node) node->p->left = node->left;
        else node->p->right = node->left;
        delete swapnode;
        node = node->left;
        node->left = nullptr;
        return;
    }
}

template <typename T>
void Bin_tree<T>::BTwalk(std::vector<T> * vec)
{
    if (top == nullptr) return;
    BTwalk(top->left, vec);
    vec->push_back(top->key);
    BTwalk(top->right, vec);
}

template <typename T>
void Bin_tree<T>::BTwalk(BTNode<T> * node, std::vector<T> * vec)
{
    if (node == nullptr) return;
    BTwalk(node->left, vec);
    vec->push_back(node->key);
    BTwalk(node->right, vec);
}

template <typename T>
T Bin_tree<T>::key(BTNode<T> * node)
{
    return node->key;
}

template <typename T>
BTNode<T> * Bin_tree<T>::left(BTNode<T> * node)
{
    return node->left;
}

template <typename T>
BTNode<T> * Bin_tree<T>::right(BTNode<T> * node)
{
    return node->right;
}

template <typename T>
BTNode<T> * Bin_tree<T>::p(BTNode<T> * node)
{
    return node->p;
}

template <typename T>
void BTsort(std::vector<T> * vec)
{
    Bin_tree<T> btree;
    for (size_t i = 0; i < vec->size(); ++i)
        btree.BTinsert((*vec)[i]);
    vec->clear();
    btree.BTwalk(vec);
}

int main()
{
    setlocale(0, "");

    std::vector<int> BTvec;
    int k, N;
    std::cout << "Введите количество элементов: ";
    std::cin >> N;
    std::cout << "Введите " << N << " элементов: ";
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> k;
        BTvec.push_back(k);
    }
    BTsort(&BTvec);
    std::cout << "Отсортированный массив:";
    for (size_t i = 0; i < N; ++i)
        std::cout << ' ' << BTvec[i];
    std::cout << std::endl;

    Bin_tree<int> btree;
    btree.BTinsert(1);
    btree.BTinsert(2);
    btree.BTinsert(0);
    btree.BTinsert(3);
    std::cout << btree.BTfind(1)->left->key << btree.BTfind(1)->key << btree.BTfind(1)->right->key << btree.BTfind(1)->right->right->key << std::endl;
    btree.BTdelete(1);
    std::cout << btree.left(btree.BTfind(2))->key << btree.p(btree.left(btree.BTfind(2)))->key << btree.right(btree.BTfind(2))->key << std::endl;
    if (btree.BTfind(1) == nullptr) std::cout << "NULL" << std::endl;
    else std::cout << btree.key(btree.BTfind(1)) << std::endl;
}
