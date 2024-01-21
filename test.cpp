#include "pch.h"
#include "oczko.h"


// Test konstruktora talii klasowego obiektu Karty
TEST(KartyTest, KonstruktorTalii) {
    Karty talia;
    // Oczekujemy, �e po utworzeniu obiektu talia, liczba kart w talii wynosi 52
    EXPECT_EQ(talia.talia.size(), 52);
}

// Test metody tasuj�cej tali� klasy Oczko
TEST(OczkoTest, Tasowanie) {
    Oczko gra;
    // Pobieramy tali� przed tasowaniem
    vector<pair<string, string>> taliaPrzedTasowaniem = gra.getTaliaKart();

    // Wywo�ujemy metod� tasuj�c�
    gra.tasowanie();

    // Pobieramy tali� po tasowaniu
    vector<pair<string, string>> taliaPoTasowaniu = gra.getTaliaKart();

    // Oczekujemy, �e talia przed tasowaniem nie jest r�wna talii po tasowaniu
    EXPECT_NE(taliaPrzedTasowaniem, taliaPoTasowaniu);
}

// Test metody obliczaj�cej warto�� r�ki klasy Oczko
TEST(OczkoTest, WartoscReki) {
    Oczko gra;
    vector<pair<string, string>> reka;

    // Testujemy warto�� r�ki z zestawem kart o warto�ciach 4, 6, 8
    reka = { {"4", "pik"}, {"6", "kier"}, {"8", "trefl"} };
    EXPECT_EQ(gra.wartoscReki(reka), 18);

    // Testujemy warto�� r�ki z zestawem kart As, Walet
    reka = { {"As", "karo"}, {"Walet", "pik"} };
    EXPECT_EQ(gra.wartoscReki(reka), 21);

    // Testujemy warto�� r�ki z zestawem kart Dama, Kr�l
    reka = { {"Dama", "trefl"}, {"Krol", "kier"} };
    EXPECT_EQ(gra.wartoscReki(reka), 20);
}



TEST(OczkoTest, GrajTest) {
    Oczko gra;

    // Testujemy funkcj� graj() pod k�tem braku rzucania wyj�tk�w
    EXPECT_NO_THROW(gra.graj());
}

// Test warto�ci r�ki po dobraniu karty As klasy Oczko
TEST(OczkoTest, WartoscRekiPoDobraniuAsa) {
    Oczko gra;
    // Testujemy warto�� r�ki z zestawem kart 4, As
    vector<pair<string, string>> reka = { {"4", "pik"}, {"As", "karo"} };

    // Oczekujemy, �e warto�� r�ki uwzgl�dnia poprawne zliczanie Asa (As = 11)
    EXPECT_EQ(gra.wartoscReki(reka), 15);
}

// Test rozdania pocz�tkowego klasy Oczko
TEST(OczkoTest, RozdaniePoczatkowe) {
    Oczko gra;

    // Rozdanie pocz�tkowe, oczekujemy, �e ka�dy gracz ma dwie karty
    gra.rozdaniePoczatkowe();
    EXPECT_EQ(gra.getRekaGracza().size(), 2);
    EXPECT_EQ(gra.getRekaKomputera().size(), 1);

    // Oczekujemy, �e talia zawiera odpowiedni� liczb� kart po rozdaniu pocz�tkowym
    EXPECT_EQ(gra.getTaliaKart().size(), 49);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
