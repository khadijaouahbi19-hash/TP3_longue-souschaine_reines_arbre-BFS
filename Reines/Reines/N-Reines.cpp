#include <iostream>
#include <cmath>
#include <chrono>
 #include <vector>
using namespace std;
class NReines{
    private:
        int N;
        vector<int> reine;
    public:
        NReines(int n){
            N = n;
            reine.resize(N);
            for(int i=0;i<N;i++){
                reine[i]=-1;
            }
        }
        bool estValide(int ligne,int colonne){
            for(int i=0;i<ligne;i++){
                if(reine[i]==colonne)
                    return false;
                if(abs(reine[i]-colonne)==abs(i-ligne))
                    return false;

            }
            return true;
        }
        bool Resoudre(int ligne ){
           if (ligne == N){
            cout << "Solution trouvee :" << endl;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (reine[i] == j) {
                    cout << "R ";
                } else {
                    cout << ". ";
                }
        }
        cout << endl;
    }

            return true;
            }
            for(int colonne=0; colonne<N;colonne++){
            if(estValide(ligne,colonne)){
                reine[ligne]=colonne;
                if(Resoudre(ligne+1)){
                    return true;
                }
                }

            }
            return false;
       }
};
int main()
{
    int n;
    cout << "Entrez le nombre de reines : ";
    cin >> n;
    if(n<1){
        cout << "Le nombre de reines doit etre superieur ou egal a 1." << endl;
        return 1;
    }

    NReines jeu(n);
    auto start = std::chrono::high_resolution_clock::now();
    jeu.Resoudre(0);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Temps d'execution : " << duration.count() << " microsecondes" << std::endl;
    return 0;
}