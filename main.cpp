#include <iostream>
#include <vector>
#include <string>
#include <unistd.h> // pour sleep() et usleep()

// —————————————————————————————
// FONCTIONS D'AFFICHAGE
// —————————————————————————————

void effacerEcran() {
    std::cout << "\033[2J\033[H";
}

void animationTexte(const std::string& texte) {
    effacerEcran();
    for (char c : texte) {
        std::cout << c << std::flush;
        usleep(20000); // 20 millisecondes par lettre
    }
    std::cout << std::endl;
}

// —————————————————————————————
// FONCTION POUR CHAQUE OPTION
// —————————————————————————————

void afficherSousMenu(int numero) {
    std::string reponse;
    while (true) {
        effacerEcran();
        std::cout << "Bienvenue dans l'option n°" << numero << " ✨" << std::endl;
        std::cout << "Souhaitez-vous revenir au menu principal ? (o/n) : ";
        std::getline(std::cin, reponse);
        if (reponse == "o") break;
    }
}

// —————————————————————————————
// FONCTION PRINCIPALE
// —————————————————————————————

int main() {
    std::vector<std::string> options = {
        "Option 1 : Saluer",
        "Option 2 : Afficher une date",
        "Option 3 : Autre message",
        "Quitter"
    };

    int selection = 0;
    std::string saisie;
    bool continuer = true;

    while (continuer) {
        effacerEcran();
        std::cout << "=== MENU PRINCIPAL ===" << std::endl;
        std::cout << "(Z = haut, S = bas, Entrée = valider, Q = quitter)\n\n";

        // Affichage des options avec surbrillance sur l’option sélectionnée
        for (std::size_t i = 0; i < options.size(); ++i) {
            if (static_cast<int>(i) == selection) {
                std::cout << "> " << options[i] << " <" << std::endl;
            } else {
                std::cout << "  " << options[i] << std::endl;
            }
        }

        // Lecture de la saisie utilisateur
        std::getline(std::cin, saisie);

        if (saisie == "z") {
            selection = (selection - 1 + options.size()) % options.size();
        } else if (saisie == "s") {
            selection = (selection + 1) % options.size();
        } else if (saisie == "q") {
            continuer = false;
        } else if (saisie == "") { // Entrée valide une option
            switch (selection) {
                case 0:
                    afficherSousMenu(1);
                    break;
                case 1:
                    afficherSousMenu(2);
                    break;
                case 2:
                    afficherSousMenu(3);
                    break;
                case 3:
                    continuer = false;
                    break;
            }
        }
    }

    effacerEcran();
    animationTexte("Merci d’avoir utilisé ce programme ✨\nÀ bientôt dans les lignes de commande 💚");

    return 0;
}
