#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<int> vec;

int mypartition(std::vector<int> &vec, int b, int e)
{
    int x(0);

    for (size_t i = 0; i < 3; ++i)
    {
        int rndidx(rand() % vec.size());
        x += vec[rndidx];
    }

    x = x / 3;

    int i(b - 1);
    int j(e + 1);
    while (true)
    {
        do
            --j;
        while (vec[j] > x);
        do
            ++i;
        while (vec[i] < x);
        if (i < j)
            std::swap(vec[i],vec[j]);
        else
            return j;
    }
}

void myquicksort(std::vector<int> &vec, int b, int e)
{
    if (b < e)
    {
        int m(mypartition(vec, b, e));
        myquicksort(vec, b, m);
        myquicksort(vec, m + 1, e);
    }
}

int main()
{
    srand(clock());
    std::cout << "Please, enter the number of elements: ";
    int n, k;
    std::cin >> n;
    std::vector<int> mas;
    std::cout << std::endl << "Write your " << n << " elements below:" << std::endl;
    for (size_t i = 0; i < n; ++i)
    {
        std::cin >> k;
        mas.push_back(k);
    }
    myquicksort(mas, 0, n - 1);
    std::cout << std::endl << "Sorted elements:" << std::endl;
    for (size_t i = 0; i < n; ++i)
        std::cout << mas[i] << ' ';
    std::cout << std::endl;

    return 0;
}
