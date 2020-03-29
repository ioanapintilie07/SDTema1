#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std::chrono;
using namespace std;

int f[1000000], w[100000001], buck[256][10001];


void reset(int a[], const int b[], int n) {
    int i;
    for (i = 1; i <= n; ++i)
        a[i] = b[i];
}


void generareSir(int v[], int n, int maxim) {
    int i;
    srand(time(NULL));
    for (i = 1; i <= n; ++i)
        v[i] = (rand() % (maxim)) + 1;
}


void bubbleSort(int v[], int n) { //RESTRICTIE: maxim 10^4 numere
    int i, ok, aux;
    do {
        ok = 0;
        for (i = 1; i < n; ++i)
            if (v[i] > v[i + 1]) {
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
                ok = 1;
            }
    } while (ok == 1);
}


void interclasare(int v[], int st, int dr) {
    int m, i, j, k;
    m = (st + dr) / 2;
    k = 0;
    i = st;
    j = m + 1;
    while (i <= m && j <= dr) {
        if (v[i] < v[j]) w[++k] = v[i++];
        else w[++k] = v[j++];
    }
    while (i <= m) w[++k] = v[i++];
    while (j <= dr) w[++k] = v[j++];
    for (i = st, j = 1; i <= dr; i++, j++) v[i] = w[j];
}


void mergeSort(int v[], int st, int dr) {
    if (st < dr) {
        int m = (st + dr) / 2;
        mergeSort(v, st, m);
        mergeSort(v, m + 1, dr);
        interclasare(v, st, dr);
    }
}


void countSort(int v[], int n, int maxi) { //RESTRICTIE: numere naturale, maxim 10^6
    int i, k = 0, j;
    for (i = 1; i <= n; ++i)
        f[v[i]]++;
    for (i = 0; i <= maxi; ++i)
        for (j = 1; j <= f[i]; ++j)
            v[++k] = i;
}


bool testSort(const int v[], int n) {
    int i;
    for (i = 1; i < n; ++i)
        if (v[i] > v[i + 1])
            return false;
    return true;
}


int pivot(int v[], int st, int dr) {
    int x, aux, p;
    p = rand() % (dr - st) + st;
    aux = v[p];
    v[p] = v[st];
    v[st] = aux;
    x = v[st];
    while (st < dr) {
        while (st < dr && v[dr] > x)dr--;
        v[st] = v[dr];
        while (st < dr && v[st] <= x)st++;
        v[dr] = v[st];
    }
    v[st] = x;
    return st;
}


void quickSort(int v[], int st, int dr) {
    int p;
    if (st < dr) {
        p = pivot(v, st, dr);
        quickSort(v, st, p - 1);
        quickSort(v, p + 1, dr);
    }
}


void radixSort(int v[], int n) {
    int k, x, i, j, index;
    for (i = 0; i < 256; ++i)
        buck[i][0] = 0;
    for (k = 0; k < 32; k += 8) {
        for (i = 1; i <= n; ++i) {
            x = v[i] >> k & 255;
            buck[x][++buck[x][0]] = v[i];
        }
        index = 0;
        for (i = 0; i < 256; ++i) {
            for (j = 1; j <= buck[i][0]; ++j)
                v[++index] = buck[i][j];
            buck[i][0] = 0;
        }
    }
}

int v[100000001], copie[100000001];

int main() {
    ifstream fin("intrare.in");
    ofstream fout("iesire.out");
    int n, maxim, T, i;
    fin >> T;
    for (i = 1; i <= T; ++i) {
        fin >> n >> maxim;
        fout << "N = " << n << "; MAX = " << maxim << "\n";
        generareSir(v, n, maxim);
        reset(copie, v, n);
        fout << "BUBBLE SORT: \n";
        if (n > 10000)
            fout << "Nu putem sorta acest sir cu Bubble Sort. \n";
        else {
            auto start = high_resolution_clock::now();
            bubbleSort(v, n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            fout << "Timpul de executare: " <<double(duration.count()) / 1000000 << " secunde. ";
            if(testSort(v, n)) fout << "Sirul a fost sortat corect. \n";
            else fout << "Sirul NU a fost sortat corect. \n";
            reset(v, copie, n);
        }
        fout << "COUNT SORT: \n";
        if(maxim > 1000000)
            fout << "Nu putem sorta acest sir cu Count Sort. \n";
        else{
            auto start = high_resolution_clock::now();
            countSort(v, n, maxim);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            fout << "Timpul de executare: " <<double(duration.count()) / 1000000 << " secunde. ";
            if(testSort(v, n)) fout << "Sirul a fost sortat corect. \n";
            else fout << "Sirul NU a fost sortat corect. \n";
            reset(v, copie, n);
        }
        fout << "QUICK SORT: \n";
        auto start = high_resolution_clock::now();
        quickSort(v, 1, n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        fout << "Timpul de executare: " <<double(duration.count()) / 1000000 << " secunde. ";
        if(testSort(v, n)) fout << "Sirul a fost sortat corect. \n";
        else fout << "Sirul NU a fost sortat corect. \n";
        reset(v, copie, n);
        fout << "MERGE SORT: \n";
        start = high_resolution_clock::now();
        mergeSort(v, 1, n);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        fout << "Timpul de executare: " <<double(duration.count()) / 1000000 << " secunde. ";
        if(testSort(v, n)) fout << "Sirul a fost sortat corect. \n";
        else fout << "Sirul NU a fost sortat corect. \n";
        reset(v, copie, n);
        fout << "RADIX SORT: \n";
        start = high_resolution_clock::now();
        radixSort(v, n);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        fout << "Timpul de executare: " <<double(duration.count()) / 1000000 << " secunde. ";
        if(testSort(v, n)) fout << "Sirul a fost sortat corect. \n";
        else fout << "Sirul NU a fost sortat corect. \n";
        fout << "\n";
    }
    fin.close();
    return 0;
}
