#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int min, N;
    vector<int> arr;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        arr.insert(arr.end(), 0);
        cin >> arr[i];
    }
    for (int i = 0; i < N - 1; i++) //C1 - n
    {
        min = i; //C2 - n-1
        for (int j = i + 1; j < N; j++) //C3 - for i=0 to n-1 sum(t(i))
            if (arr[j] < arr[min]) //C4 - for i=0 to n-1 sum(t(i)-1)
                min = j; //C5 - for i=0 to n-1 sum(t(i)-1)
        if (arr[i] == arr[min]) //C6 - n-1
            continue; //C7 - n-1
        swap(arr[i],arr[min]); //C8 - n-1
    }
    for (int i = 0; i < N; i++) cout << arr[i] << ' ';
}
