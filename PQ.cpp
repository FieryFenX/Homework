#include <iostream>
#include <vector>

class PriorityQueue
{
    public:
        void push(int el)
        {
            //std::cout << "push" << std::endl;
            q.insert(q.begin(),el);
            heapify(q,0);
        }
        void pop()
        {
            //std::cout << "pop" << std::endl;
            elemswap(q,0,q.size()-1);
            q.pop_back();
            heapify(q,0);
        }
        int top()
        {
            //std::cout << "top" << std::endl;
            return q.front();
        }
        int* at(int i)
        {
            return &q[i];
        }

        void save(std::ostream &os)
        {
            os << std::endl << "Heap:" << std::endl;
            for (int i = 0; i < q.size(); i = (i + 1) * 2 - 1)
            {
                for (int j = i; j < (i + 1) * 2 - 1; ++j)
                    if (j < q.size()) os << q[j] << ' ';
                os << std::endl;
            }
            os << std::endl;
        }
    private:
        std::vector<int> q;

        int left(int i)
        {
            return (i + 1) * 2 - 1;
        }

        int right(int i)
        {
            return (i + 1) * 2;
        }

        void elemswap(std::vector<int> &vec, int i1, int i2)
        {
            std::swap(vec[i1],vec[i2]);
        }

        void heapify(std::vector<int> &vec, int i)
        {
            //std::cout << "heapify" << std::endl;
            int largest = 0;
            int l = left(i);
            int r = right(i);
            if ((l < vec.size()) && (vec[l] > vec[i]))
                largest = l;
            else
                largest = i;
            if ((r < vec.size()) && (vec[r] > vec[largest]))
                largest = r;
            if (largest != i)
            {
                elemswap(vec, i, largest);
                heapify(vec, largest);
            }
        }

        void buildheap(std::vector<int> &vec)
        {
            //std::cout << "buildheap" << std::endl;
            for (int i = vec.size() / 2; i > 0; --i)
                heapify(vec,i);
        }
};

std::ostream & operator <<(std::ostream &os, PriorityQueue & q)
{
    q.save(os);
    return os;
}

void heapsort(std::vector<int> &vec)
{
    PriorityQueue q;
    for(int i = 0; i < vec.size(); ++i)
        q.push(vec[i]);
    std::cout << q;
    for(int i = vec.size() - 1; i >= 0; --i)
    {
        vec[i] = q.top();
        q.pop();
    }
}

int main()
{
    int k, n;
    std::vector<int> heap;
    std::cout << "Please, enter the number of elements:" << ' ';
    std::cin >> n;
    std::cout << std::endl << "Write your " << n << " elements below:" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> k;
        heap.push_back(k);
    }
    heapsort(heap);
    std::cout << "Sorted elements:" << std::endl;
    for (int i = 0; i < heap.size(); ++i)
        std::cout << heap[i] << ' ';
    std::cout << std::endl;
}
