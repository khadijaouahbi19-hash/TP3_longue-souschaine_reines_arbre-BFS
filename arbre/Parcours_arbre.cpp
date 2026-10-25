
#include <iostream>
#include <queue>

using namespace std;

class Noeud
{
private:
    int valeur;
    Noeud* fg;
    Noeud* fd;

public:
    // Constructeur
    Noeud(int val) : valeur(val), fg(nullptr), fd(nullptr) {}

    // Methodes pour definir les enfants
    void setFg(Noeud* gauche) { fg = gauche; }

    void setFd(Noeud* droite) {fd = droite;}
    Noeud* get_fg() { return fg; }
    Noeud* get_fd() { return fd; }

    // Parcours en largeur
    void parcoursLargeur(Noeud* racine)
    {
        if (racine == nullptr)
            return;

        queue<Noeud*> file;
        file.push(racine);
         Noeud* courant ;

        cout << "Parcours en largeur : ";
        cout << racine->valeur << " ";

        while (!file.empty()&&(courant=file.front())!=nullptr )
        {
           
            file.pop();

            if (courant->fg != nullptr)
                file.push(courant->fg);
                cout << courant->fg->valeur << " ";

            if (courant->fd != nullptr)
                file.push(courant->fd);
                cout << courant->fd->valeur << " ";
        }

        cout << endl;
    }
};

int main()
{
    Noeud* racine = new Noeud(1);

    racine->setFg(new Noeud(2));
    racine->setFd(new Noeud(3));

    racine->setFg(new Noeud(2));
    racine->setFd(new Noeud(3));

    racine->parcoursLargeur(racine);

    return 0;
}
