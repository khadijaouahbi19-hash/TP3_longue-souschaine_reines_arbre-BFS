
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace std::chrono;

//  FROM SCRATCH

class TasMax {
private:
    vector<int> A;

    void echanger(int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }

public:

    void maxHeapify(int i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest;

        if (l < A.size() && A[l] > A[i])
            largest = l;
        else
            largest = i;

        if (r < A.size() && A[r] > A[largest])
            largest = r;

        if (largest != i) {
            echanger(A[i], A[largest]);
            maxHeapify(largest);
        }
    }

    void construireTasMax() {
        for (int i = (int)A.size() / 2 - 1; i >= 0; i--) {
            maxHeapify(i);
        }
    }

    void inserer(int valeur) {
        A.push_back(valeur);
        construireTasMax();
    }

    int extraireMax() {
        if (A.empty())
            return -1;

        int max = A[0];

        A[0] = A.back();
        A.pop_back();

        if (!A.empty())
            maxHeapify(0);

        return max;
    }

    int maximum() {
        return A.empty() ? -1 : A[0];
    }

    int taille() {
        return (int)A.size();
    }

    bool estVide() {
        return A.empty();
    }

    void afficherTas() {
        for (int i = 0; i < A.size(); i++)
            cout << A[i] << " ";

        cout << endl;
    }
};



int main() {

    const int N = 50000;

    // Generer les memes nombres pour les deux versions

    vector<int> v;

    mt19937 gen(42);
    uniform_int_distribution<int> dist(1, 1000000);

    for (int i = 0; i < N; i++) {
        v.push_back(dist(gen));
    }

    // INSERTION STL

    priority_queue<int> pq;

    auto debut2 = high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        pq.push(v[i]);
    }

    auto fin2 = high_resolution_clock::now();

    double temps2 =
        duration<double, milli>(fin2 - debut2).count();

    // INSERTION FROM SCRATCH

    TasMax tas;

    auto debut1 = high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        tas.inserer(v[i]);
    }

    auto fin1 = high_resolution_clock::now();

    double temps1 =
        duration<double, milli>(fin1 - debut1).count();

    // VERIFICATION DU MAXIMUM

    cout << "\n--- VERIFICATION ---" << endl;

    cout << "Maximum From Scratch : "
         << tas.maximum() << endl;

    cout << "Maximum STL : "
         << pq.top() << endl;

    // EXTRACTION STL (UN SEUL MAXIMUM)

    auto debut4 = high_resolution_clock::now();

    if (!pq.empty()) {
        pq.pop();
    }

    auto fin4 = high_resolution_clock::now();

    double duree4 =
        duration<double, nano>(fin4 - debut4).count();

        // EXTRACTION FROM SCRATCH (UN SEUL MAXIMUM)

    auto debut3 = high_resolution_clock::now();

    if (!tas.estVide()) {
        tas.extraireMax();
    }

    auto fin3 = high_resolution_clock::now();

    double duree3 =
        duration<double, nano>(fin3 - debut3).count();

    cout << "\n\n";
    cout << "==========================================================" << endl;
    cout << "                 TABLEAU COMPARATIF                       " << endl;
    cout << "==========================================================" << endl;

    cout << "\nNombre d'elements initial : " << N << endl;

    cout << fixed << setprecision(3);

    cout << "\n";

    cout << left
         << setw(25) << "Operation"
         << setw(22) << "From Scratch"
         << setw(22) << "STL"
         << endl;

    cout << string(69, '-') << endl;

    cout << left
         << setw(25) << "Insertion (ms)"
         << setw(22) << temps1
         << setw(22) << temps2
         << endl;

    cout << left
         << setw(25) << "Extraction (ns)"
         << setw(22) << duree3
         << setw(22) << duree4
         << endl;

    cout << left
         << setw(25) << "Elements restants"
         << setw(22) << tas.taille()
         << setw(22) << pq.size()
         << endl;

    cout << string(69, '-') << endl;

    return 0;
}
