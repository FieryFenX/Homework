#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

void bucketsort(vector<double> & vec, double k, size_t & j)
{
    if (--j == 0) return;
    vector< vector<double> > buckets;
    for (size_t i = 0; i < 10; ++i)
    buckets.push_back({});
    for (size_t i = 0; i < vec.size(); ++i)
        buckets[(int)(vec[i] / k) % 10].push_back(vec[i]);
    for (size_t i = 0; i < 10; ++i)
        if (buckets[i].size() > 1) bucketsort(buckets[i], k / 10, j);
    for (size_t i = 0; i < vec.size(); )
        for (size_t ii = 0; ii < 10; ++ii)
            for (size_t iii = 0; iii < buckets[ii].size(); ++iii)
            {
                vec[i] = buckets[ii][iii];
                ++i;
            }
}

size_t bucketsort(vector<double> & vec)
{
    vector<double> vec1 = vec;
    size_t j = 0, j1 = 0;
    for (size_t i = 0; i < vec1.size(); ++i)
    {
        while (vec1[i] != 0)
        {
            vec1[i] = vec1[i] * 10 - round(vec1[i] * 10);
            j++;
        }
        if (j > j1) j1 = j;
        j = 0;
    }
    j = j1 + 1;
    bucketsort(vec, 0.1, j);
    return j1;
}

int main()
{
    cout << "Please, enter the number of elements: ";
    size_t n;
    double el;
    cin >> n;
    vector<double> els;
    cout << endl << "Write your " << n << " elements below:" << endl;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> el;
        els.push_back(el);
    }
    n = bucketsort(els);
    cout << endl << "Sorted elements:" << endl;
    for (size_t i = 0; i < n; ++i)
        cout << fixed << setprecision(n) << els[i] << ' ';
    cout << endl;

    return 0;
}
