#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;
class QuatreReines{
    private:
        int reine[4];
    public:
        QuatreReines(){
            for(int i=0;i<4;i++){
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
           if (ligne == 4){
            cout << "Solution trouvee :" << endl;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
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
            for(int colonne=0; colonne<4;colonne++){
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
    QuatreReines jeu;
    auto start = std::chrono::high_resolution_clock::now();
    jeu.Resoudre(0);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Temps d'execution : " << duration.count() << " microsecondes" << std::endl;
    return 0;
}