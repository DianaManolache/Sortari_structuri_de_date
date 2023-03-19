#include <iostream>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace std::chrono;


ifstream fin("numere.in");

int testSort(int v[], int n) {
    int i;
    for (i = 0; i < n - 1; i++)
        if (v[i] > v[i + 1])
            return 0;
    return 1;
}

void MergeSort(int v[], int st, int dr) {
    int w[10001];
    if (st < dr) {
        int m = (st + dr) / 2;
        MergeSort(v, st, m);
        MergeSort(v, m + 1, dr);
        //Interclasare
        int i = st, j = m + 1, k = 0;
        while (i <= m && j <= dr)
            if (v[i] < v[j])
                w[++k] = v[i++];
            else
                w[++k] = v[j++];
        while (i <= m)
            w[++k] = v[i++];
        while (j <= dr)
            w[++k] = v[j++];
        for (i = st, j = 1; i <= dr; i++, j++)
            v[i] = w[j];
    }
}

void InsertionSort(int v[], int n) {
    int i, j, cheie;
    for (i = 1; i < n; i++) {
        cheie = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > cheie) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = cheie;
    }
}

void ShellSort(int v[], int n) {
    int gap, i, j, x;
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            x = v[i];
            for (j = i; j >= gap && v[j - gap] > x; j -= gap)
                v[j] = v[j - gap];

            v[j] = x;
        }
    }
}

//QuickSort cu pivotul pe prima pozitie
void QuickSort1(int v[], int st, int dr) {
    if (st < dr) {
        //pivotul este inițial v[st]
        int m = (st + dr) / 2;
        int aux = v[st];
        v[st] = v[m];
        v[m] = aux;
        int i = st, j = dr, d = 0;
        while (i < j) {
            if (v[i] > v[j]) {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        QuickSort1(v, st, i - 1);
        QuickSort1(v, i + 1, dr);
    }
}

//QuickSort cu pivotul pe pozitie random
void QuickSort2(int v[], int st, int dr) {
    if (st < dr) {
        int m = (st + dr) / 2;
        int r = st + rand() % (dr - st);
        int aux = v[r];
        v[r] = v[m];
        v[m] = aux;
        int i = st, j = dr, d = 0;
        while (i < j) {
            if (v[i] > v[j]) {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        QuickSort2(v, st, i - 1);
        QuickSort2(v, i + 1, dr);
    }
}

//Radix Sort banal
void RadixSort(int v[], int n) {
    int putere = 1, maxi = -1;
    for (int i = 0; i < n; i++)
        if (v[i] > maxi)
            maxi = v[i];
    int part[10][n];
    int indice[10];
    while (maxi / putere != 0) {
        for (int i = 0; i <= 9; i++)
            indice[i] = 0;
        for (int i = 0; i < n; i++) {
            int aux = (v[i] / putere) % 10;
            part[aux][indice[aux]] = v[i];
            indice[aux]++;
        }
        int t = 0;
        for (int i = 0; i <= 9; i++) {
            for (int j = 0; j < indice[i]; j++) {
                v[t] = part[i][j];
                t++;
            }
        }
        putere = putere * 10;
    }
}

//Radix Sort folosind operatii pe biti
void radixSort2(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());

    for (int exp = 1; maxVal/exp > 0; exp <<= 1) {
        vector<vector<int>> buckets(2);

        for (int i = 0; i < arr.size(); i++) {
            int bucketIdx = (arr[i] / exp) % 2;
            buckets[bucketIdx].push_back(arr[i]);
        }

        int k = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < buckets[i].size(); j++) {
                arr[k++] = buckets[i][j];
            }
        }
    }
}
void afis(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        cout << v[i] << " ";
}

int main() {
    int T, N, Max, i, a[100001], b[100001], c[100001], d[100001], e[100001], f[100001];
    fin >> T;
    int k=0;
//    for( i = 0; i < T; i++ )            //verificare quicksort cu pivot ales diferit
//    {
//        fin >> N >> Max;
//        for(int j = 0; j < N; j++)
//        {
//            w[j] = rand() % Max;
//            v[j] = w[j];
//        }
//
//        auto start1 = high_resolution_clock::now();
//        QuickSort1(v,0,N-1);
//        auto stop1 = high_resolution_clock::now();
//        auto duration1 = duration_cast <microseconds> (stop1 - start1);
//        cout << "Durata sortarii Quick sort cu pivot ales random: " << duration1.count() << " microsecunde\n";
//
//        auto start2 = high_resolution_clock::now();
//        QuickSort2(w,0,N-1);
//        auto stop2 = high_resolution_clock::now();
//        auto duration2 = duration_cast <microseconds> (stop2 - start2);
//        cout << "Durata sortarii Quick sort cu pivot la stanga: " << duration2.count() << " microsecunde\n";
//        cout << ++k << endl;
//    }

    for( i = 0; i < T; i++ )
    {
        fin >> N >> Max;
        for(int j = 0; j < N; j++)
        {
            a[j] = rand() % Max;
            b[j] = a[j];
            c[j] = a[j];
            d[j] = a[j];
            e[j] = a[j];
            f[j] = a[j];
        }

        auto start1 = high_resolution_clock::now();
        MergeSort(a,0,N-1);
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast <microseconds> (stop1 - start1);
        cout << "Durata sortarii Quick Sort: " << duration1.count() << " microsecunde\n";

        auto start2 = high_resolution_clock::now();
        InsertionSort(b,N);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast <microseconds> (stop2 - start2);
        cout << "Durata sortarii Insertion Sort: " << duration2.count() << " microsecunde\n";

        auto start3 = high_resolution_clock::now();
        ShellSort(c,N);
        auto stop3 = high_resolution_clock::now();
        auto duration3 = duration_cast <microseconds> (stop3 - start3);
        cout << "Durata sortarii Shell Sort: " << duration3.count() << " microsecunde\n";

        auto start4 = high_resolution_clock::now();
        QuickSort1(d,0, N-1);
        auto stop4 = high_resolution_clock::now();
        auto duration4 = duration_cast <microseconds> (stop4 - start4);
        cout << "Durata sortarii Quick Sort: " << duration4.count() << " microsecunde\n";

        auto start5 = high_resolution_clock::now();
        RadixSort(e, N);
        auto stop5 = high_resolution_clock::now();
        auto duration5 = duration_cast <microseconds> (stop5 - start5);
        cout << "Durata sortarii Radix Sort: " << duration5.count() << " microsecunde\n";

        auto start6 = high_resolution_clock::now();
        sort(f,f+N);
        auto stop6 = high_resolution_clock::now();
        auto duration6 = duration_cast <microseconds> (stop6 - start6);
        cout << "Durata sortarii specifice C++: " << duration6.count() << " microsecunde\n";
        cout << endl;
    }
    return 0;
}
