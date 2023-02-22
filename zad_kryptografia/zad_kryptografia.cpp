// zad_kryptografia.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

int main()
{
	ifstream plik;
	plik.open("wiadomosc.txt");


	if (plik.good() == true)
	{
		string wiersz, dane, kopia;
		while (getline(plik, wiersz))
			dane = dane + wiersz;

		dane.erase(remove(dane.begin(), dane.end(), ' '), dane.end());

		cout << "Ilosc liter w szyfrogramie = " << dane.length() - 1 << endl << endl;





		//Obliczanie dlugosci klucza metoda Friedmana		

		cout << "METODA FRIEDMANA" << endl << endl;


		vector <int> koincydencje;
		koincydencje.resize(dane.length());


		//Obliczanie koincydencji

		for (int i = 1; i < dane.length(); i++)
		{
			for (int j = 0; j < dane.length(); j++)
			{
				if (dane.at(j) == dane.at((i + j) % dane.length()))
				{
					koincydencje[i]++;
				}
			}
		}

		for (int i = 1; i < 26; i++)
		{
			cout << "Ilosc koincydencji dla przesuniecia " << i << " wynosi : " << koincydencje[i] << endl;
		}



		//Obliczanie sredniej oraz odchylenia standardowego a wynikiem bedzie wartosc wieksza od sumy tych wartosci

		int sred = 0;
		for (int i = 0; i < dane.length(); i++)
		{
			sred += koincydencje[i];
		}
		sred /= dane.length();


		int odchyl = 0;
		for (int i = 0; i < dane.length(); i++)
		{
			odchyl += abs(koincydencje[i] - sred);
		}
		odchyl /= dane.length();


		int wynik;
		for (int i = 0; i < dane.length(); i++)
		{
			if (koincydencje[i] > sred + odchyl)
			{
				wynik = i;
				break;
			}
		}
		cout << endl << "Dlugosc klucza metoda Friedmana = " << wynik << endl << endl;






		//Obliczanie dlugosci klucza metoda Kasiskiego

		cout << endl << "METODA KASISKIEGO" << endl << endl;


		int dystans[100];
		int dist;
		int x = 0;

		//Szukanie slow od 3 do 6 znakow i zapisywanie ich odleglosci od siebie

		for (int i = 0; i < dane.length(); i++)
		{
			for (int k = i + 1; k < dane.length(); k++)
			{
				if (dane[i] == dane[k])
				{
					if (dane[i + 1] == dane[k + 1] && i < dane.length() && k < dane.length())
					{
						if (dane[i + 2] == dane[k + 2] && i < dane.length() && k < dane.length())
						{
							if (dane[i + 3] == dane[k + 3] && i < dane.length() && k < dane.length())
							{
								if (dane[i + 4] == dane[k + 4] && i < dane.length() && k < dane.length())
								{
									if (dane[i + 5] == dane[k + 5] && i < dane.length() && k < dane.length())
									{
										if (dane[i + 6] == dane[k + 6] && i < dane.length() && k < dane.length())
										{
											dystans[x] = k - i;
											x++;
											cout << "Znaleziono slowo: " << dane[i] << dane[i + 1] << dane[i + 2] << dane[i + 3] << dane[i + 4] << dane[i + 5] << dane[i + 6] << " odlegosc do kolejnego takiego slowa = " << k - i << endl;
										}

										dist = k - i;
										if (dist != dystans[x - 1])
										{
											dystans[x] = k - i;
											x++;
											cout << "Znaleziono slowo: " << dane[i] << dane[i + 1] << dane[i + 2] << dane[i + 3] << dane[i + 4] << dane[i + 5] << " odlegosc do kolejnego takiego slowa = " << k - i << endl;
										}
									}
									dist = k - i;
									if (dist != dystans[x - 1])
									{
										dystans[x] = k - i;
										x++;
										cout << "Znaleziono slowo: " << dane[i] << dane[i + 1] << dane[i + 2] << dane[i + 3] << dane[i + 4] << " odlegosc do kolejnego takiego slowa = " << k - i << endl;
									}
								}
								dist = k - i;
								if (dist != dystans[x - 1])
								{
									dystans[x] = k - i;
									x++;
									cout << "Znaleziono slowo: " << dane[i] << dane[i + 1] << dane[i + 2] << dane[i + 3] << " odlegosc do kolejnego takiego slowa = " << k - i << endl;
								}
							}
							dist = k - i;
							if (dist != dystans[x - 1])
							{
								dystans[x] = k - i;
								x++;
								cout << "Znaleziono slowo: " << dane[i] << dane[i + 1] << dane[i + 2] << " odlegosc do kolejnego takiego slowa = " << k - i << endl;
							}
						}
					}
				}
			}
		}

		//Stworzenie vectora przechowywujacego wszystkie dzielniki
		vector <int> tab;
		int max = 0;

		for (int i = 0; i < x; i++)
		{
			for (int j = 3; j <= dystans[i] / 2; j++)
			{
				if (dystans[i] % j == 0)
				{
					tab.push_back(j);

					if (j > max)
					{
						max = j;
					}
				}
			}
		}



		//Zliczanie, ktory dzielnik wystepuje najczesciej	
		vector <int> zlicz;
		zlicz.resize(max);

		for (int i = 0; i < max; i++)
		{
			zlicz[i] = 0;
		}

		for (size_t i = 0; i < tab.size(); i++)
		{
			for (int j = 0; j < max; j++)
			{
				if (tab[i] == j)
				{

					zlicz[j] += 1;
				}
			}
		}

		cout << endl << "Zliczona ilosc dzielnikow:" << endl;
		for (int i = 3; i < 21; i++)
		{
			cout << "Dzielnik : " << i << " wystapil " << zlicz[i] << " razy" << endl;
		}



		//Wybranie najczesciej wystepujacego dzielnika

		int maxx = 1, wynik1;

		for (int i = 0; i < max; i++)
		{
			if (zlicz[i] > maxx)
			{
				maxx = zlicz[i];
				wynik1 = i;
			}
		}
		cout << endl << "Dlugosc klucza metoda Kasiskiego = " << wynik1 << endl;

		int dlugosc_klucza;

		if (wynik == wynik1)
		{
			dlugosc_klucza = wynik;
		}



		// Obliczanie czestosci liter na danej pozycji	

		vector <vector<int>> czestosci;

		czestosci.resize(dlugosc_klucza);

		for (int i = 0; i < dlugosc_klucza; i++)
		{
			czestosci[i].resize(26);
		}




		for (int i = 0; i < dane.length(); i++)
		{
			for (int j = 0; j < dlugosc_klucza; j++)
			{
				czestosci[j][i % 26] = 0;
			}
		}


		//Obliczanie czestosci wystepowania znaku na sprawdzanym miejscu w kluczu

		for (int i = 0; i < dane.length(); i++)
		{
			for (int c = 'a'; c <= 'z'; c++)
			{
				for (int j = 0; j < dlugosc_klucza; j++)
				{

					if (i % dlugosc_klucza == j)
					{
						if (dane[i] == c)
						{
							czestosci[j][c - 'a'] += 1;
						}
					}
				}
			}
		}

		cout << endl << "Tabele czestosci wystepowania znakow na danym miejscu w kluczu:" << endl;

		for (int i = 0; i < dlugosc_klucza; i++)
		{
			cout << endl << "Miejsce w kluczu: " << i + 1 << endl;
			for (int j = 0; j < 26; j++)
			{
				cout << (char)(j + 'a') << " " << czestosci[i][j] << endl;
			}
		}



		// Obliczenie klucza przy uzyciu odchylenia standardowego


		int czestosciPolskie[26] = { 100,15,37,34,90,1,15,12,88,27,35,37,31,55,79,25,0,38,55,39,22,0,46,0,43,65 };
		string klucz = "";

		for (int i = 0; i < dlugosc_klucza; i++)
		{
			int index = 0;
			int min = INT_MAX;

			for (int j = 0; j < 26; j++)
			{
				int suma = 0;

				for (int c = 'a'; c <= 'z'; c++)
				{
					suma += abs(czestosci[i][(c - 'a' + j) % 26] - czestosciPolskie[c - 'a']);
				}
				if (suma < min)
				{
					index = j;
					min = suma;
				}
			}
			klucz += (char)('a' + index);
		}

		cout << endl << "Klucz = " << klucz << endl << endl;


		vector <int> klucz_liczby;
		klucz_liczby.resize(dlugosc_klucza);


		for (int i = 0; i < klucz.length(); i++)
		{
			klucz_liczby[i] = klucz[i] - 'a';
		}




		//Zamiana szyfrogramu na wartosci liczbowe   								
		vector <int> szyfr;
		szyfr.resize(dane.length());


		for (int i = 0; i < dane.length(); i++)
		{
			szyfr[i] = dane[i] - 'a';
		}





		//Obliczenie wartosci liczbowej tekstu jawnego	
		vector <int> tekst;

		tekst.resize(dane.length());
		int pomocnicza = 0;

		for (int i = 0; i < dane.length(); i++)
		{
			for (int j = 0; j < dlugosc_klucza; j++)
			{
				if (i % dlugosc_klucza == j)
				{
					pomocnicza = szyfr[i] - klucz_liczby[i % dlugosc_klucza];
					if (pomocnicza < 0)
					{
						pomocnicza = (26 + pomocnicza) % 26;
					}
					tekst[i] = pomocnicza;
				}
			}
		}



		// Zamiana wartosci liczbowych tekstu jawnego na litery  	

		cout << "Zaszyfrowany tekst:" << endl << endl;
		for (int i = 0; i < dane.length(); i++)
		{
			cout << dane[i];
		}


		cout << endl << endl << "Odszyfrowany tekst :" << endl << endl;
		for (int i = 0; i < dane.length(); i++)
		{
			cout << static_cast<char>(tekst[i] + 97);
		}

		cout << endl << endl << "Odszyfrowanym tekstem jest list Arystotelesa do Aleksandra Wielkiego." << endl;


	}
	else
	{
		cout << "Dostep do pliku zostal zabroniony!" << endl;
	}
	return 0;
}


// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
