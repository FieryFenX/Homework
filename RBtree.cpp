#include <iostream>
#include <vector>

const bool RED = false;
const bool BLACK = true;

template <typename T>
struct RBTNode
{
    T key;
    RBTNode<T> * left;
    RBTNode<T> * right;
    RBTNode<T> * p;
    bool color;
public:
    RBTNode();
};

template <typename T>
RBTNode<T>::RBTNode():
    key(0),
    left(nullptr),
    right(nullptr),
    p(nullptr),
    color(RED)
{
}

template <typename T>
class RBtree
{
private:
    RBTNode<T> * root = nullptr;
public:
    void rightRotate(RBTNode<T> * node);
    void leftRotate(RBTNode<T> * node);

    RBTNode<T> * find(T key);
    RBTNode<T> * find(RBTNode<T> * node, T key);

    void insert(T key);
    RBTNode<T> * BTinsert(T key);
    RBTNode<T> * BTinsert(RBTNode<T> * node, T key);

    void RBdelete(T key);

    void walk();
    void walk(RBTNode<T> * node);
    std::vector<T> & walk(std::vector<T> & vec);
    std::vector<T> & walk(RBTNode<T> * node, std::vector<T> & vec);

    T key(RBTNode<T> * node);
    RBTNode<T> * left(RBTNode<T> * node);
    RBTNode<T> * right(RBTNode<T> * node);
    RBTNode<T> * p(RBTNode<T> * node);
};

template <typename T>
void RBtree<T>::rightRotate(RBTNode<T> * node)
{
    if (node->left == nullptr) return;
    RBTNode<T> * nodelr = node->left->right;
    node->left->p = node->p;
    if (node->p != nullptr)
    {
        if (node == node->p->right) node->p->right = node->left;
        else node->p->left = node->left;
    }
    node->p = node->left;
    node->left->right = node;
    node->left = nodelr;
    if (nodelr != nullptr) nodelr->p = node;

    if (root->p != nullptr) root = root->p;
}

template <typename T>
void RBtree<T>::leftRotate(RBTNode<T> * node)
{
    if (node->right == nullptr) return;
    RBTNode<T> * noderl = node->right->left;
    node->right->p = node->p;
    if (node->p != nullptr)
    {
        if (node == node->p->right) node->p->right = node->right;
        else node->p->left = node->right;
    }
    node->p = node->right;
    node->right->left = node;
    node->right = noderl;
    if (noderl != nullptr) noderl->p = node;

    if (root->p != nullptr) root = root->p;
}

template <typename T>
RBTNode<T> * RBtree<T>::find(T key)
{
    return find(root, key);
}

template <typename T>
RBTNode<T> * RBtree<T>::find(RBTNode<T> * node, T key)
{
    if (node == nullptr) return nullptr;
    if (node->key == key) return node;
    if (key < node->key) return find(node->left, key);
    if (key > node->key) return find(node->right, key);
}

template <typename T>
void RBtree<T>::insert(T key)
{
    RBTNode<T> * node = BTinsert(key);
    //node->color = RED;
    if (node != nullptr)
    while (node->p != nullptr && node != root && node->p->color == RED)
    {
        if (node->p->p != nullptr)
        {
            if (node->p == node->p->p->left)
            {
                RBTNode<T> * uncle = node->p->p->right;
                if (uncle != nullptr && uncle->color == RED)
                {
                    node->p->color = BLACK;
                    uncle->color = BLACK;
                    node->p->p->color = RED;
                    node = node->p->p;
                }
                else
                {
                    if (node == node->p->right)
                    {
                        node = node->p;
                        leftRotate(node);
                    }
                    node->p->color = BLACK;
                    node->p->p->color = RED;
                    rightRotate(node->p->p);
                }
            }
            else
            {
                RBTNode<T> * uncle = node->p->p->left;
                if (uncle != nullptr && uncle->color == RED)
                {
                    node->p->color = BLACK;
                    uncle->color = BLACK;
                    node->p->p->color = RED;
                    node = node->p->p;
                }
                else
                {
                    if (node == node->p->left)
                    {
                        node = node->p;
                        rightRotate(node);
                    }
                    node->p->color = BLACK;
                    node->p->p->color = RED;
                    leftRotate(node->p->p);
                }
            }
        }
        root->color = BLACK;
    }
}

template <typename T>
RBTNode<T> * RBtree<T>::BTinsert(T key)
{
    if (root == nullptr)
    {
        RBTNode<T> * newnode = new RBTNode<T>;
        newnode->key = key;
        newnode->color = BLACK;
        root = newnode;
        return root;
    }
    return BTinsert(root, key);
}

template <typename T>
RBTNode<T> * RBtree<T>::BTinsert(RBTNode<T> * node, T key)
{
    if (key < node->key)
    {
        if (node->left == nullptr)
        {
            RBTNode<T> * newleft = new RBTNode<T>;
            newleft->key = key;
            newleft->p = node;
            node->left = newleft;
            return newleft;
        }
        return BTinsert(node->left, key);
    }
    if (key > node->key)
    {
        if (node->right == nullptr)
        {
            RBTNode<T> * newright = new RBTNode<T>;
            newright->key = key;
            newright->p = node;
            node->right = newright;
            return newright;
        }
        return BTinsert(node->right, key);
    }
}

template <typename T>
void RBtree<T>::RBdelete(T key)
{
    RBTNode<T> * node = find(key);
    RBTNode<T> * sibling;
    if (node == nullptr) return;

    if (node->left != nullptr && node->right != nullptr)
    {
        RBTNode<T> * successor = node->right;
        while (successor->left != nullptr) successor = successor->left;
        std::swap(node->key, successor->key);
        node = successor;
    }

    if (node->p != nullptr)
    {
        if (node == node->p->left) sibling = node->p->right;
        else sibling = node->p->left;
    }
    else
    {
        if (node->left != nullptr)
            node->left->p = node->right;
        if (node->right != nullptr)
        {
            node->right->p = nullptr;
            node->right->left = node->left;
            root = node->right;
        }
        else root = node->left;
        if (root != nullptr) root->color = BLACK;
        delete node;
        return;
    }

    if (node->left == nullptr && node->right == nullptr && node->color == RED)
    {
        if (node == node->p->left) node->p->left = nullptr;
        else node->p->right = nullptr;
        if (root->p != nullptr) root = root->p;
        delete node;
        return;
    }

    if (node->left == nullptr && node->right != nullptr && node->color != node->right->color)
    {
        node->color = node->right->color = BLACK;
        if (node->p->left == node) node->p->left = node->right;
        else node->p->right = node->right;
        node->right->p = node->p;
        if (root->p != nullptr) root = root->p;
        delete node;
        return;
    }

    if (node->left != nullptr && node->right == nullptr && node->color != node->left->color)
    {
        node->color = node->left->color = BLACK;
        if (node->p->left == node) node->p->left = node->left;
        else node->p->right = node->left;
        node->left->p = node->p;
        if (root->p != nullptr) root = root->p;
        delete node;
        return;
    }

    RBTNode<T> * swapnode = node;
    std::vector<T> vec;

    while (sibling != nullptr)
    {
        if (sibling->color == BLACK)
        {
            if (sibling == node->p->left && sibling->left != nullptr && sibling->left->color == RED)
            {
                rightRotate(node->p);
                sibling->left->color = BLACK;
                break;
            }
            if (sibling == node->p->left && sibling->right != nullptr && sibling->right->color == RED)
            {
                leftRotate(sibling);
                sibling->p->color = BLACK;
                rightRotate(node->p);
                break;
            }
            if (sibling == node->p->right && sibling->right != nullptr && sibling->right->color == RED)
            {
                leftRotate(node->p);
                sibling->right->color = BLACK;
                break;
            }
            if (sibling == node->p->right && sibling->left != nullptr && sibling->left->color == RED)
            {
                rightRotate(sibling);
                sibling->p->color = BLACK;
                leftRotate(node->p);
                break;
            }
            sibling->color = RED;
            if (node->p->color == RED)
            {
                node->p->color = BLACK;
                break;
            }
            node = node->p;
        }
        else //sibling->color == RED
        {
            sibling->p->color = RED;
            sibling->color = BLACK;
            if (sibling == node->p->left) rightRotate(sibling->p);
            else leftRotate(sibling->p);
        }
        if (node->p != nullptr)
        {
            if (node == node->p->left) sibling = node->p->right;
            else sibling = node->p->left;
        }
        else break;
    }

    if (swapnode->left != nullptr && swapnode->right == nullptr)
    {
        if (swapnode->p->left == swapnode) swapnode->p->left = swapnode->left;
        else swapnode->p->right = swapnode->left;
        swapnode->left->p = swapnode->p;
        delete swapnode;
        return;
    }

    if (swapnode->left == nullptr && swapnode->right != nullptr)
    {
        if (swapnode->p->left == swapnode) swapnode->p->left = swapnode->right;
        else swapnode->p->right = swapnode->right;
        swapnode->right->p = swapnode->p;
        delete swapnode;
        return;
    }

    //swapnode->left == nullptr && swapnode->right == nullptr
    if (swapnode->p->left == swapnode) swapnode->p->left = nullptr;
    else swapnode->p->right = nullptr;
    delete swapnode;
}

template <typename T>
void RBtree<T>::walk()
{
    if (root == nullptr)
    {
        std::cout << "empty set";
        return;
    }
    walk(root->left);
    std::cout << root->key << ' ';
    walk(root->right);
}

template <typename T>
void RBtree<T>::walk(RBTNode<T> * node)
{
    if (node == nullptr) return;
    walk(node->left);
    std::cout << node->key << ' ';
    walk(node->right);
}

template <typename T>
std::vector<T> & RBtree<T>::walk(std::vector<T> & vec)
{
    vec.clear();
    if (root == nullptr) return vec;
    walk(root->left, vec);
    vec.push_back(root->key);
    walk(root->right, vec);

    return vec;
}

template <typename T>
std::vector<T> & RBtree<T>::walk(RBTNode<T> * node, std::vector<T> & vec)
{
    if (node == nullptr) return vec;
    walk(node->left, vec);
    vec.push_back(node->key);
    walk(node->right, vec);

    return vec;
}

template <typename T>
T RBtree<T>::key(RBTNode<T> * node)
{
    return node->key;
}

template <typename T>
RBTNode<T> * RBtree<T>::left(RBTNode<T> * node)
{
    return node->left;
}

template <typename T>
RBTNode<T> * RBtree<T>::right(RBTNode<T> * node)
{
    return node->right;
}

template <typename T>
RBTNode<T> * RBtree<T>::p(RBTNode<T> * node)
{
    return node->p;
}

int main()
{
    RBtree<size_t> rbt;
    for (size_t i = 11; i != 0; --i)
        rbt.insert(i);
    rbt.walk();
    std::cout << std::endl;

    size_t arr[13] = {12,10,6,4,1,3,9,5,7,11,2,6,8};
    for (size_t * i = arr; i < arr+13; ++i)
    {
        rbt.RBdelete(*i);
        rbt.walk();
        std::cout << std::endl;
    }

    return 0;
}
