#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

string dizi[3][3];

class Otomasyon {
private:
    string p1 = "O";
    string p2 = "X";
    string currentPlayer;
public:
    Otomasyon() {
        cout << "Uctas Oyununa Hosgeldiniz.." << endl;
        cout << "Lutfen Bir Arkadasinizla Oynayiniz.." << endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                dizi[i][j] = '-';
            }
        }
    }
    void baslangicSecme();
    void tahtaYazdir();
    void hareketKontrol();
    int kazanmaDurumu();

};

void Otomasyon::baslangicSecme() {
    srand(time(0));
    int secim = rand() % 2;
    currentPlayer = (secim == 0) ? p1 : p2;
    cout << "Ilk once " << currentPlayer << " basliyor." << endl;
}

void Otomasyon::tahtaYazdir() {
    // Terminal ekranını temizle
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "Oyun Alaniniz:\n\n";
    cout << "   0     1     2\n"; // X ekseni numaraları
    for (int i = 0; i < 3; ++i) {
        cout << i << " "; // Y ekseni numaraları
        for (int j = 0; j < 3; ++j) {
            cout << "  " << dizi[i][j] << "  ";
        }
        cout << "\n\n";
    }
}

void Otomasyon::hareketKontrol() {
    int hamleX, hamleY;
    while (true) {
        cout << currentPlayer << " Hamleniz: (x ve y ekseni olarak giris yapiniz) ";
        cin >> hamleX >> hamleY;

        if (hamleX >= 0 && hamleX < 3 && hamleY >= 0 && hamleY < 3 && dizi[hamleX][hamleY] == "-") {
            dizi[hamleX][hamleY] = currentPlayer;
            tahtaYazdir();
            int durum = kazanmaDurumu();
            if (durum == 1) {
                cout << currentPlayer << " KAZANDI!!" << endl;
                break;
            }
            else if (durum == -1) {
                cout << "Oyun berabere!" << endl;
                break;
            }
            currentPlayer = (currentPlayer == p1) ? p2 : p1;
        }
        else {
            cout << "Gecersiz hamle! Tekrar deneyiniz." << endl;
        }
    }
}

int Otomasyon::kazanmaDurumu() {
    // Yatay kontroller
    for (int i = 0; i < 3; ++i) {
        if (dizi[i][0] == currentPlayer && dizi[i][1] == currentPlayer && dizi[i][2] == currentPlayer) {
            return 1;
        }
    }

    // Dikey kontroller
    for (int i = 0; i < 3; ++i) {
        if (dizi[0][i] == currentPlayer && dizi[1][i] == currentPlayer && dizi[2][i] == currentPlayer) {
            return 1;
        }
    }

    // Çapraz kontroller
    if (dizi[0][0] == currentPlayer && dizi[1][1] == currentPlayer && dizi[2][2] == currentPlayer) {
        return 1;
    }
    if (dizi[0][2] == currentPlayer && dizi[1][1] == currentPlayer && dizi[2][0] == currentPlayer) {
        return 1;
    }

    // Beraberlik kontrolü
    bool boardFull = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (dizi[i][j] == "-") {
                boardFull = false;
                break;
            }
        }
    }
    if (boardFull) {
        return -1;
    }

    return 0;
}

int main() {
    Otomasyon obj1;
    obj1.tahtaYazdir();
    obj1.baslangicSecme();
    obj1.hareketKontrol();
    return 0;
}
