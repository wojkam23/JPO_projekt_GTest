#ifndef OCZKO_H
#define OCZKO_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

//using std::cin, std::cout, std::vector, std::endl, std::pair, std::string, std::random_device, std::mt19937;
using namespace std;

class Karty {
public:
    vector<string> karta = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Walet", "Dama", "Krol", "As" };
    vector<string> kolor = { "pik", "kier", "karo", "trefl" };
    vector<pair<string, string>> talia;

    Karty() {
        for (int i = 0; i < kolor.size(); ++i) {
            for (int j = 0; j < karta.size(); ++j) {
                talia.push_back(make_pair(karta[j], kolor[i]));
            }
        }
    }
};

class Oczko {
private:
    vector<pair<string, string>> taliaKart;
    vector<pair<string, string>> rekaGracza;
    vector<pair<string, string>> rekaKomputera;

public:
    Oczko() {
        Karty talia;
        taliaKart = talia.talia;
        tasowanie();
    }

    void tasowanie() {
        random_device rd;
        mt19937 g(rd());
        shuffle(taliaKart.begin(), taliaKart.end(), g);
    }

    int wartoscReki(const vector<pair<string, string>>& reka) {
        int wartosc = 0;
        int liczbaAsow = 0;

        for (int i = 0; i < reka.size(); ++i) {
            if (reka[i].first == "As") {
                wartosc += 11;
                liczbaAsow++;
            }
            else if (reka[i].first == "Walet" || reka[i].first == "Dama" || reka[i].first == "Krol") {
                wartosc += 10;
            }
            else {
                wartosc += stoi(reka[i].first);
            }
        }

        while (wartosc > 21 && liczbaAsow > 0) {
            wartosc -= 10;
            liczbaAsow--;
        }

        return wartosc;
    }

    void rozdaniePoczatkowe() {
        dobierzKarte(rekaGracza);
        dobierzKarte(rekaKomputera);
        dobierzKarte(rekaGracza);

        cout << "Twoje karty: ";
        pokazReke(rekaGracza);
        cout << "Wartosc Twoich kart: " << wartoscReki(rekaGracza) << endl;

        cout << "Karta komputera: " << rekaKomputera[0].first << " " << rekaKomputera[0].second << endl;
    }

    void pokazReke(const vector<pair<string, string>>& reka) {
        for (int i = 0; i < reka.size(); i++) {
            cout << reka[i].first << " " << reka[i].second;
            if (i < reka.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }

    void dobierzKarte(vector<pair<string, string>>& reka) {
        reka.push_back(taliaKart.back());
        taliaKart.pop_back();
    }

    void graj() {
        char wybor;
        do {
            cout << "Czy chcesz dobrac karte? (D - dobierz, S - stoj): ";
            cin >> wybor;

            if (wybor == 'D' || wybor == 'd') {
                dobierzKarte(rekaGracza);
                cout << "Twoje karty: ";
                pokazReke(rekaGracza);
                cout << "Wartosc Twoich kart: " << wartoscReki(rekaGracza) << endl;

                if (wartoscReki(rekaGracza) > 21) {
                    cout << "Przekroczyles 21! Przegrales." << endl;
                    return;
                }
            }
            else if (wybor == 'S' || wybor == 's') {
                break;
            }
            else {
                cout << "Niepoprawny wybor. Wybierz ponownie." << endl;
            }
        } while (true);

        cout << "Ruch komputera:" << endl;
        while (wartoscReki(rekaKomputera) < 17) {
            dobierzKarte(rekaKomputera);
            pokazReke(rekaKomputera);
            cout << "Wartosc kart komputera: " << wartoscReki(rekaKomputera) << endl;
        }

        int wartoscGracza = wartoscReki(rekaGracza);
        int wartoscKomputera = wartoscReki(rekaKomputera);

        cout << "Twoje karty: ";
        pokazReke(rekaGracza);
        cout << "Wartosc Twoich kart: " << wartoscGracza << endl;

        cout << "Karty komputera: ";
        pokazReke(rekaKomputera);
        cout << "Wartosc kart komputera: " << wartoscKomputera << endl;

        if (wartoscGracza > wartoscKomputera && wartoscGracza <= 21) {
            cout << "Gratulacje! Wygrales." << endl;
        }
        else if (wartoscKomputera > 21) {
            cout << "Komputer przekroczyl 21! Wygrales." << endl;
        }
        else if (wartoscGracza == wartoscKomputera) {
            cout << "Remis!" << endl;
        }
        else {
            cout << "Przegra³eœ." << endl;
        }
    }

    vector<pair<string, string>> getTaliaKart() const {
        return taliaKart;
    }

    vector<pair<string, string>> getRekaGracza() const {
        return rekaGracza;
    }

    vector<pair<string, string>> getRekaKomputera() const {
        return rekaKomputera;
    }
};

#endif
