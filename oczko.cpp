#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>


//using std::cin, std::cout, std::vector, std::endl, std::pair, std::string, std::random_device, std::mt19937;
using namespace std;

///////////////////////////////////////////////////////////
// Klasa reprezentuj¹ca talie kart do gry.
///////////////////////////////////////////////////////////
class Karty {
public:
    // Wektory reprezentuj¹ce dostêpne wartoœci kart i kolory.
    vector<string> karta = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Walet", "Dama", "Krol", "As" };
    vector<string> kolor = { "pik", "kier", "karo", "trefl" };

    // Wektor par reprezentuj¹cych karty w talii.
    vector<pair<string, string>> talia;

    // Konstruktor inicjalizuj¹cy talie kart.
    Karty() {
        for (int i = 0; i < kolor.size(); ++i) {
            for (int j = 0; j < karta.size(); ++j) {
                talia.push_back(make_pair(karta[j], kolor[i]));
            }
        }
    }
};

///////////////////////////////////////////////////////////
// Klasa reprezentuj¹ca grê w oczko.
///////////////////////////////////////////////////////////
class Oczko {
private:
    // Wektory przechowuj¹ce talie kart oraz rêce gracza i komputera.
    vector<pair<string, string>> taliaKart;
    vector<pair<string, string>> rekaGracza;
    vector<pair<string, string>> rekaKomputera;

public:
    // Konstruktor inicjalizuj¹cy talie kart i tasuj¹cy je.
    Oczko() {
        Karty talia;
        taliaKart = talia.talia;
        tasowanie();
    }

    // Tasuje talie kart.
    void tasowanie() {
        random_device rd;    // Inicjalizacja generatora liczb losowych
        mt19937 g(rd()); // Utworzenie obiektu generatora MT
        shuffle(taliaKart.begin(), taliaKart.end(), g); // Tasowanie talii kart
    }

    // Oblicza wartoœæ rêki gracza lub komputera.
    // INPUT:
    //      reka - wektor par reprezentuj¹cych karty w rêce
    // OUTPUT:
    //      Wartoœæ rêki (int)
    // REMARKS:
    //      Wartoœæ asów dostosowana do sytuacji.
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
                wartosc += stoi(reka[i].first); //funkcja 'stoi' konwertuje wartoœci string na int
            }
        }
        //dostosowanie wartoœci Asa w zale¿noœci od sytuacji
        while (wartosc > 21 && liczbaAsow > 0) {
            wartosc -= 10;
            liczbaAsow--;
        }

        return wartosc;
    }

    // Rozdaje pocz¹tkowe karty graczowi i komputerowi.
    // INPUT:
    //      None
    // OUTPUT:
    //      None
    // REMARKS:
    //      Karty s¹ dodawane do rêki gracza i komputera.
    void rozdaniePoczatkowe() {
        dobierzKarte(rekaGracza);
        dobierzKarte(rekaKomputera);
        dobierzKarte(rekaGracza);


        cout << "Twoje karty: ";
        pokazReke(rekaGracza);
        cout << "Wartoœæ Twoich kart: " << wartoscReki(rekaGracza) << endl;

        cout << "Karta komputera: " << rekaKomputera[0].first << " " << rekaKomputera[0].second << endl;
    }

    // Wyœwietla karty w rêce.
    // INPUT:
    //      reka - wektor par reprezentuj¹cych karty w rêce
    // OUTPUT:
    //      None
    // REMARKS:
    //      Karty wyœwietlane s¹ na standardowym wyjœciu.
    void pokazReke(const vector<pair<string, string>>& reka) {
        for (int i = 0; i < reka.size(); i++) {
            cout << reka[i].first << " " << reka[i].second;
            if (i < reka.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }

    // Dobiera kartê do rêki gracza lub komputera.
    // INPUT:
    //      reka - wektor par reprezentuj¹cych karty w rêce
    // OUTPUT:
    //      None
    // REMARKS:
    //      Karta jest pobierana z talii.
    void dobierzKarte(vector<pair<string, string>>& reka) {
        reka.push_back(taliaKart.back());
        taliaKart.pop_back();
    }

    // Logika gry w oczko.
    // INPUT:
    //      None
    // OUTPUT:
    //      None
    // REMARKS:
    //      Gracz decyduje, czy dobrac karte, czy spasowaæ.
    void graj() {
        char wybor;
        do {
            cout << "Czy chcesz dobrac karte? (D - dobierz, S - stoj): ";
            cin >> wybor;

            if (wybor == 'D' || wybor == 'd') {
                dobierzKarte(rekaGracza);
                cout << "Twoje karty: ";
                pokazReke(rekaGracza);
                cout << "Wartoœæ Twoich kart: " << wartoscReki(rekaGracza) << endl;

                if (wartoscReki(rekaGracza) > 21) {
                    cout << "Przekroczy³eœ 21! Przegra³eœ." << endl;
                    return;
                }
            }
            else if (wybor == 'S' || wybor == 's') {
                break;
            }
            else {
                cout << "Niepoprawny wybór. Wybierz ponownie." << endl;
            }
        } while (true);

        cout << "Ruch krupiera:" << endl;
        while (wartoscReki(rekaKomputera) < 17) {
            dobierzKarte(rekaKomputera);
            pokazReke(rekaKomputera);
            cout << "Wartoœæ kart krupiera: " << wartoscReki(rekaKomputera) << endl;
        }

        int wartoscGracza = wartoscReki(rekaGracza);
        int wartoscKomputera = wartoscReki(rekaKomputera);

        cout << "Twoje karty: ";
        pokazReke(rekaGracza);
        cout << "Wartoœæ Twoich kart: " << wartoscGracza << endl;

        cout << "Karty komputera: ";
        pokazReke(rekaKomputera);
        cout << "Wartoœæ kart komputera: " << wartoscKomputera << endl;

        if (wartoscGracza > wartoscKomputera && wartoscGracza <= 21) {
            cout << "Gratulacje! Wygra³eœ." << endl;
        }
        else if (wartoscKomputera > 21) {
            cout << "Komputer przekroczy³ 21! Wygra³eœ." << endl;
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

///////////////////////////////////////////////////////////
// Funkcja g³ówna programu gry w oczko.
///////////////////////////////////////////////////////////
int main() {
    char grajPonownie;
    do {
        Oczko oczko;
        oczko.rozdaniePoczatkowe();
        oczko.graj();

        cout << "Czy chcesz zagraæ ponownie? (T - tak, N - nie): ";
        cin >> grajPonownie;
    } while (grajPonownie == 'T' || grajPonownie == 't');

    return 0;
}