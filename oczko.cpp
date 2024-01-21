#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>


//using std::cin, std::cout, std::vector, std::endl, std::pair, std::string, std::random_device, std::mt19937;
using namespace std;

///////////////////////////////////////////////////////////
// Klasa reprezentuj�ca talie kart do gry.
///////////////////////////////////////////////////////////
class Karty {
public:
    // Wektory reprezentuj�ce dost�pne warto�ci kart i kolory.
    vector<string> karta = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Walet", "Dama", "Krol", "As" };
    vector<string> kolor = { "pik", "kier", "karo", "trefl" };

    // Wektor par reprezentuj�cych karty w talii.
    vector<pair<string, string>> talia;

    // Konstruktor inicjalizuj�cy talie kart.
    Karty() {
        for (int i = 0; i < kolor.size(); ++i) {
            for (int j = 0; j < karta.size(); ++j) {
                talia.push_back(make_pair(karta[j], kolor[i]));
            }
        }
    }
};

///////////////////////////////////////////////////////////
// Klasa reprezentuj�ca gr� w oczko.
///////////////////////////////////////////////////////////
class Oczko {
private:
    // Wektory przechowuj�ce talie kart oraz r�ce gracza i komputera.
    vector<pair<string, string>> taliaKart;
    vector<pair<string, string>> rekaGracza;
    vector<pair<string, string>> rekaKomputera;

public:
    // Konstruktor inicjalizuj�cy talie kart i tasuj�cy je.
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

    // Oblicza warto�� r�ki gracza lub komputera.
    // INPUT:
    //      reka - wektor par reprezentuj�cych karty w r�ce
    // OUTPUT:
    //      Warto�� r�ki (int)
    // REMARKS:
    //      Warto�� as�w dostosowana do sytuacji.
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
                wartosc += stoi(reka[i].first); //funkcja 'stoi' konwertuje warto�ci string na int
            }
        }
        //dostosowanie warto�ci Asa w zale�no�ci od sytuacji
        while (wartosc > 21 && liczbaAsow > 0) {
            wartosc -= 10;
            liczbaAsow--;
        }

        return wartosc;
    }

    // Rozdaje pocz�tkowe karty graczowi i komputerowi.
    // INPUT:
    //      None
    // OUTPUT:
    //      None
    // REMARKS:
    //      Karty s� dodawane do r�ki gracza i komputera.
    void rozdaniePoczatkowe() {
        dobierzKarte(rekaGracza);
        dobierzKarte(rekaKomputera);
        dobierzKarte(rekaGracza);


        cout << "Twoje karty: ";
        pokazReke(rekaGracza);
        cout << "Warto�� Twoich kart: " << wartoscReki(rekaGracza) << endl;

        cout << "Karta komputera: " << rekaKomputera[0].first << " " << rekaKomputera[0].second << endl;
    }

    // Wy�wietla karty w r�ce.
    // INPUT:
    //      reka - wektor par reprezentuj�cych karty w r�ce
    // OUTPUT:
    //      None
    // REMARKS:
    //      Karty wy�wietlane s� na standardowym wyj�ciu.
    void pokazReke(const vector<pair<string, string>>& reka) {
        for (int i = 0; i < reka.size(); i++) {
            cout << reka[i].first << " " << reka[i].second;
            if (i < reka.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }

    // Dobiera kart� do r�ki gracza lub komputera.
    // INPUT:
    //      reka - wektor par reprezentuj�cych karty w r�ce
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
    //      Gracz decyduje, czy dobrac karte, czy spasowa�.
    void graj() {
        char wybor;
        do {
            cout << "Czy chcesz dobrac karte? (D - dobierz, S - stoj): ";
            cin >> wybor;

            if (wybor == 'D' || wybor == 'd') {
                dobierzKarte(rekaGracza);
                cout << "Twoje karty: ";
                pokazReke(rekaGracza);
                cout << "Warto�� Twoich kart: " << wartoscReki(rekaGracza) << endl;

                if (wartoscReki(rekaGracza) > 21) {
                    cout << "Przekroczy�e� 21! Przegra�e�." << endl;
                    return;
                }
            }
            else if (wybor == 'S' || wybor == 's') {
                break;
            }
            else {
                cout << "Niepoprawny wyb�r. Wybierz ponownie." << endl;
            }
        } while (true);

        cout << "Ruch krupiera:" << endl;
        while (wartoscReki(rekaKomputera) < 17) {
            dobierzKarte(rekaKomputera);
            pokazReke(rekaKomputera);
            cout << "Warto�� kart krupiera: " << wartoscReki(rekaKomputera) << endl;
        }

        int wartoscGracza = wartoscReki(rekaGracza);
        int wartoscKomputera = wartoscReki(rekaKomputera);

        cout << "Twoje karty: ";
        pokazReke(rekaGracza);
        cout << "Warto�� Twoich kart: " << wartoscGracza << endl;

        cout << "Karty komputera: ";
        pokazReke(rekaKomputera);
        cout << "Warto�� kart komputera: " << wartoscKomputera << endl;

        if (wartoscGracza > wartoscKomputera && wartoscGracza <= 21) {
            cout << "Gratulacje! Wygra�e�." << endl;
        }
        else if (wartoscKomputera > 21) {
            cout << "Komputer przekroczy� 21! Wygra�e�." << endl;
        }
        else if (wartoscGracza == wartoscKomputera) {
            cout << "Remis!" << endl;
        }
        else {
            cout << "Przegra�e�." << endl;
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
// Funkcja g��wna programu gry w oczko.
///////////////////////////////////////////////////////////
int main() {
    char grajPonownie;
    do {
        Oczko oczko;
        oczko.rozdaniePoczatkowe();
        oczko.graj();

        cout << "Czy chcesz zagra� ponownie? (T - tak, N - nie): ";
        cin >> grajPonownie;
    } while (grajPonownie == 'T' || grajPonownie == 't');

    return 0;
}