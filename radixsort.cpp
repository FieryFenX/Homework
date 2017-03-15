#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

int myCountingSort(std::vector<long long> &A, unsigned char Apcs[], std::vector<long long> &B, int k)
{
    std::vector<unsigned char> C;
    for (size_t i = 0; i <= k; ++i)
        C.push_back((unsigned char)0);
    for (size_t j = 0; j < A.size(); ++j)
        C[Apcs[j]] += 1;
    for (size_t i = 1; i <= k; ++i)
        C[i] += C[i-1];
    for (size_t j = A.size(); j--; )
    {
        B[C[Apcs[j]] - 1] = A[j];
        C[Apcs[j]] -= 1;
    }
}

void myRadixSort(std::vector<long long> &vec, int dgt)
{
    unsigned char piece[vec.size()];
    for (size_t i = 0; i < dgt; ++i)
    {
        for (size_t j = 0; j < vec.size(); ++j)
            piece[j] = (unsigned char)(vec[j] >> 8 * i << 8 * (dgt - 1) >> 8 * (dgt - 1));
        std::vector<long long> vecCS(vec);
        myCountingSort(vec, piece, vecCS, 255);
        vec = vecCS;
    }
}
//2541551403420444553 3771334298718075024 1311768465173141112 2541551403420444553 1311768465173141112 3771334298718075024 3771334298718075024
int main()
{
    std::cout << "Please, enter the number of elements: ";
    int n;
    long long k;
    std::cin >> n;
    std::vector<long long> mas;
    std::cout << std::endl << "Write your " << n << " elements below:" << std::endl;
    for (size_t i = 0; i < n; ++i)
    {
        std::cin >> k;
        mas.push_back(k);
    }
    myRadixSort(mas, 8);
    std::cout << std::endl << "Sorted elements:" << std::endl;
    for (size_t i = 0; i < n; ++i)
        std::cout << mas[i] << ' ';
    std::cout << std::endl;

    return 0;
}
