#include "pch.h"
#include "oczko.h"


// Test konstruktora talii klasowego obiektu Karty
TEST(KartyTest, KonstruktorTalii) {
    Karty talia;
    // Oczekujemy, ¿e po utworzeniu obiektu talia, liczba kart w talii wynosi 52
    EXPECT_EQ(talia.talia.size(), 52);
}

// Test metody tasuj¹cej taliê klasy Oczko
TEST(OczkoTest, Tasowanie) {
    Oczko gra;
    // Pobieramy taliê przed tasowaniem
    vector<pair<string, string>> taliaPrzedTasowaniem = gra.getTaliaKart();

    // Wywo³ujemy metodê tasuj¹c¹
    gra.tasowanie();

    // Pobieramy taliê po tasowaniu
    vector<pair<string, string>> taliaPoTasowaniu = gra.getTaliaKart();

    // Oczekujemy, ¿e talia przed tasowaniem nie jest równa talii po tasowaniu
    EXPECT_NE(taliaPrzedTasowaniem, taliaPoTasowaniu);
}

// Test metody obliczaj¹cej wartoœæ rêki klasy Oczko
TEST(OczkoTest, WartoscReki) {
    Oczko gra;
    vector<pair<string, string>> reka;

    // Testujemy wartoœæ rêki z zestawem kart o wartoœciach 4, 6, 8
    reka = { {"4", "pik"}, {"6", "kier"}, {"8", "trefl"} };
    EXPECT_EQ(gra.wartoscReki(reka), 18);

    // Testujemy wartoœæ rêki z zestawem kart As, Walet
    reka = { {"As", "karo"}, {"Walet", "pik"} };
    EXPECT_EQ(gra.wartoscReki(reka), 21);

    // Testujemy wartoœæ rêki z zestawem kart Dama, Król
    reka = { {"Dama", "trefl"}, {"Krol", "kier"} };
    EXPECT_EQ(gra.wartoscReki(reka), 20);
}



TEST(OczkoTest, GrajTest) {
    Oczko gra;

    // Testujemy funkcjê graj() pod k¹tem braku rzucania wyj¹tków
    EXPECT_NO_THROW(gra.graj());
}

// Test wartoœci rêki po dobraniu karty As klasy Oczko
TEST(OczkoTest, WartoscRekiPoDobraniuAsa) {
    Oczko gra;
    // Testujemy wartoœæ rêki z zestawem kart 4, As
    vector<pair<string, string>> reka = { {"4", "pik"}, {"As", "karo"} };

    // Oczekujemy, ¿e wartoœæ rêki uwzglêdnia poprawne zliczanie Asa (As = 11)
    EXPECT_EQ(gra.wartoscReki(reka), 15);
}

// Test rozdania pocz¹tkowego klasy Oczko
TEST(OczkoTest, RozdaniePoczatkowe) {
    Oczko gra;

    // Rozdanie pocz¹tkowe, oczekujemy, ¿e ka¿dy gracz ma dwie karty
    gra.rozdaniePoczatkowe();
    EXPECT_EQ(gra.getRekaGracza().size(), 2);
    EXPECT_EQ(gra.getRekaKomputera().size(), 1);

    // Oczekujemy, ¿e talia zawiera odpowiedni¹ liczbê kart po rozdaniu pocz¹tkowym
    EXPECT_EQ(gra.getTaliaKart().size(), 49);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
