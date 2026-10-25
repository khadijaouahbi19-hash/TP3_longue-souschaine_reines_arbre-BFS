#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;


class Resultat
{
public:
    vector<string> resultatsMots;

    string sousChaine;
    long long dureeMicrosecondes = 0;

    bool vide() const { return sousChaine.empty(); }
};


class RechercheSousChaine
{
public:
    // Cherche la plus longue sous-chaine commune entre deux mots
    string chercher(const string& m1, const string& m2) const
    {
        string plusLongue;

        for (size_t i = 0; i < m1.size(); ++i)
        {
            for (size_t j = 0; j < m2.size(); ++j)
            {
                size_t k = 0;
                while (i + k < m1.size() &&
                       j + k < m2.size() &&
                       m1[i + k] == m2[j + k])
                {
                    ++k;
                }

                if (k > plusLongue.size())
                {
                    plusLongue = m1.substr(i, k);
                }
            }
        }
        return plusLongue;
    }
};

class FichierLecteur
{
private:
    string nomFichier;

public:
    explicit FichierLecteur(const string& nom) : nomFichier(nom) {}

    // Retourne true si la lecture a reussi, false sinon
    bool lire(vector<string>& mots) const
    {
        ifstream fichier(nomFichier);
        if (!fichier)
        {
            cerr << "Erreur : impossible d'ouvrir le fichier '"
                 << nomFichier << "'." << endl;
            return false;
        }

        string mot;
        while (fichier >> mot)
        {
            mots.push_back(mot);
        }
        return true;
    }
};

class AnalyseurMots
{
private:
    vector<string> mots;
    RechercheSousChaine chercheur;

public:
    explicit AnalyseurMots(vector<string> listeMots)
        : mots(std::move(listeMots)) {}

    size_t nombreDeMots() const { return mots.size(); }

    Resultat analyser() const
    {
        Resultat resultat;

        auto debut = high_resolution_clock::now();

        for (size_t i = 0; i < mots.size(); ++i)
        {
            for (size_t j = i + 1; j < mots.size(); ++j)
            {
                if (mots[i] == mots[j]) continue;

                string sousChaine = chercheur.chercher(mots[i], mots[j]);

                if (sousChaine.size() > resultat.sousChaine.size())
                {
                    resultat.sousChaine = sousChaine;

                }
            }
        }
        // 2 Chercher tous les mots qui contiennent cette sous-chaine
        if (!resultat.sousChaine.empty())
        {
            const string& cible = resultat.sousChaine;

            for (const string& m : mots)
            {
                // On evite les doublons dans le resultat
                // et on ne garde que les mots qui contiennent la sous-chaine
                if (m.find(cible) != string::npos)
                {
                    // Optionnel : eviter d'ajouter deux fois le meme mot
                    bool dejaPresent = false;
                    for (const string& deja : resultat.resultatsMots)
                    {
                        if (deja == m) { dejaPresent = true; break; }
                    }
                    if (!dejaPresent)
                        resultat.resultatsMots.push_back(m);
                }
            }
        }


        auto fin = high_resolution_clock::now();
        resultat.dureeMicrosecondes =
            duration_cast<microseconds>(fin - debut).count();

        return resultat;
    }
};

class Application
{
private:
    string nomFichier;

public:
    explicit Application(const string& fichier) : nomFichier(fichier) {}

    int executer() const
    {
        // 1 Lecture du fichier
        FichierLecteur lecteur(nomFichier);
        vector<string> mots;

        if (!lecteur.lire(mots))
        {
            return 1;
        }

        cout << "Nombre de mots dans le fichier : "
             << mots.size() << endl;

        if (mots.empty())
        {
            cout << "Le fichier est vide." << endl;
            return 0;
        }

        // 2 Analyse
        AnalyseurMots analyseur(std::move(mots));
        Resultat resultat = analyseur.analyser();

        // 3 Affichage
        afficher(resultat);
        return 0;
    }

private:
    void afficher(const Resultat& resultat) const
        {
            cout << endl << "RESULTAT" << endl;

            if (resultat.vide())
            {
                cout << "Aucune sous-chaine commune trouvee." << endl;
            }
            else
            {
                cout << "Sous-chaine       : " << resultat.sousChaine << endl;
                cout << "Longueur          : " << resultat.sousChaine.size() << endl;
                cout << endl;
                cout << "Mots contenant cette sous-chaine ("
                     << resultat.resultatsMots.size() << ") :" << endl;

                for (const string& m : resultat.resultatsMots)
                {
                    cout << "  - " << m << endl;
                }
            }

            cout << endl
                 << "Temps d'execution : "
                 << resultat.dureeMicrosecondes
                 << " microsecondes" << endl;
        }
};

int main()
{
    Application app("fichier.txt");
    return app.executer();
}
