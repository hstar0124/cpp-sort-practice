#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

void BubbleSort(vector<int>& v)
{
    const int n = v.size();

    // O(N^2)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (v[j] > v[j + 1])
            {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

void SelectionSort(vector<int>& v)
{
    const int n = v.size();

    // O(N^2)
    for (int i = 0; i < n - 1; i++)
    {
        int bestIdx = i;

        for (int j = i + 1; j < n; j++)
        {
            if (v[j] < v[bestIdx])
                bestIdx = j;
        }

        if(i != bestIdx)
            swap(v[i], v[bestIdx]);
    }
}

void HeapSort(vector<int>& v)
{
    priority_queue<int, vector<int>, greater<int>> pq;

    // O(NlogN)
    for (int num : v)
        pq.push(num);   // O(logN)

    v.clear();

    // O(NlogN)
    while (pq.empty() == false)
    {
        v.push_back(pq.top());  // O(1)
        pq.pop();               // O(logN)
    }
}


// 분할 정복 (Divide and Conquer)
// - 분할
// - 정복
// - 결합

// O(N)
void MergeResult(vector<int>& v, int left, int mid, int right)
{
    int leftIdx = left;
    int rightIdx = mid + 1;

    vector<int> temp;

    while (leftIdx <= mid && rightIdx <= right)
    {
        if (v[leftIdx] <= v[rightIdx]) 
        {
            temp.push_back(v[leftIdx]);
            leftIdx++;
        }
        else
        {
            temp.push_back(v[rightIdx]);
            rightIdx++;
        }
    }

    if (leftIdx > mid)
    {
        while (rightIdx <= right)
        {
            temp.push_back(v[rightIdx]);
            rightIdx++;
        }
    }
    else
    {
        while (leftIdx <= mid)
        {
            temp.push_back(v[leftIdx]);
            leftIdx++;
        }
    }

    for (int i = 0; i < temp.size(); i++)
        v[left + i] = temp[i];

}

// O(logN)
void MergeSort(vector<int>& v, int left, int right)
{
    if (left >= right)
        return;


    int mid = (left + right) / 2;    
    MergeSort(v, left, mid);
    MergeSort(v, mid + 1, right);

    MergeResult(v, left, mid, right);
}


// 퀵소트
int Partition(vector<int>& v, int left, int right)
{
    int pivot = v[left];
    int low = left + 1;
    int high = right;

    while (low <= high)
    {
        while (low <= right && pivot >= v[low])
            low++;

        while (high >= left + 1 && pivot <= v[high])
            high--;

        if (low < high)
            swap(v[low], v[high]);
    }

    swap(v[left], v[high]);
    return high;
}

void QuickSort(vector<int>& v, int left, int right)
{
    if (left > right)
        return;

    int pivot = Partition(v, left, right);
    QuickSort(v, left, pivot - 1);
    QuickSort(v, pivot + 1, right);
}

int main()
{
    vector<int> v{ 1, 5, 3, 4, 2 };
    //BubbleSort(v);                    // O(N^2)
    //SelectionSort(v);                 // O(N^2)
    //HeapSort(v);                      // O(NlogN)

    //MergeSort(v, 0, v.size() - 1);      // O(NlogN)
    QuickSort(v, 0, v.size() - 1);      // O(NlogN) 하지만 최악의 경우 O(N^2) 이 나온다.
}
