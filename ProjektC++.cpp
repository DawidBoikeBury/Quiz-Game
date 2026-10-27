#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

struct pytanie
{
	string tresc;
	string o[4];
	string poprawnaOdpowiedz;
};
string indeksDoLitera(string a) {
	if (a=="0")
	{
		return "A";
	}
	else if (a == "1") {
		return "B";
	}
	else if (a=="2")
	{
		return "C";
	}
	else {
		return "D";
	}
}

void dodajPytanie() {
	system("cls");
	bool czyPoprawnaOdpowiedz = false;
	string pytanie, poprawnaOdpowiedz;
	string o[4];
	cin.ignore();
	cout << "Podaj pytanie: ";
	getline(cin, pytanie);
	for (int i = 0; i < 4; i++)
	{
		cout << "Podaj odpowiedz(" << i + 1 << ")[kolejnosc nie ma znaczenia]:";
		getline(cin, o[i]);
	}
	while (czyPoprawnaOdpowiedz == false) {
		system("cls");
		cout << pytanie <<":" << endl;
		for (int i = 0; i < 4; i++)
		{
			cout << i + 1 <<"- " << o[i] << endl;
		}
		cout << "podaj poprawna odpowiedz(1 - 4): ";
		getline(cin, poprawnaOdpowiedz);
		if (poprawnaOdpowiedz.size() == 1 and (stoi(poprawnaOdpowiedz) > 0 and stoi(poprawnaOdpowiedz) < 5)) {
			czyPoprawnaOdpowiedz = true;
		}
		else
		{
			system("cls");
			cout << "Nie poprawna odpowiedz wybierz (1-4)!";
			Sleep(500);
		}
	}
	ofstream plik("pytanie.txt", ios::app);
	if (!plik)
	{
		cout << "blad odczytu pliku!" << endl;
		Sleep(2000);
		return;
	}


	plik << pytanie << "|";
	for (int i = 0; i < 4; i++)
	{
		plik << o[i] << "|";
	}
	plik << poprawnaOdpowiedz << endl;
	plik.close();

	system("cls");
	cout << "DODANO!"<<endl;
	Sleep(300);
}
vector<pytanie>vectorPytan() {
	pytanie pyt;
	vector<pytanie>listaPytan;
	ifstream plik("pytanie.txt");
	if (!plik)
	{
		cout << "blad odczytu pliku!" << endl;
		Sleep(2000);
		return listaPytan;
	}
	while (getline(plik, pyt.tresc, '|') and getline(plik,pyt.o[0],'|')and getline(plik, pyt.o[1], '|')and getline(plik, pyt.o[2], '|')and getline(plik, pyt.o[3], '|')and getline(plik,pyt.poprawnaOdpowiedz)) {
		int pOT = stoi(pyt.poprawnaOdpowiedz) - 1;
		pyt.poprawnaOdpowiedz = to_string(pOT);
		listaPytan.push_back(pyt);
	}
	plik.close();
	return listaPytan;
	

}

void listaPytan() {
	system("cls");
	vector<pytanie>listaPytan = vectorPytan();
	string wyborS;
	int dlugosc = listaPytan.size();

		if (dlugosc ==0)
		{
			cout << "NIE MA PYTAN!"<<endl;
		}
		else {
			for (int i = 0; i < dlugosc; i++)
			{
				cout << i + 1 << ". " << listaPytan[i].tresc << endl;
				cout << "A)" << listaPytan[i].o[0] << endl;
				cout << "B)" << listaPytan[i].o[1] << endl;
				cout << "C)" << listaPytan[i].o[2] << endl;
				cout << "D)" << listaPytan[i].o[3] << endl;
				cout << "Poprawna odpowiedz: " << indeksDoLitera(listaPytan[i].poprawnaOdpowiedz) << endl << endl;
			}
		}
		cout << "Kliknij enter aby przejsc do opcji:";
		cin.ignore();
		getline(cin, wyborS);

	



}
void rankingPlus(string nazwa,string punkty) {
	ofstream plik("ranking.txt", ios::app);
	if (!plik)
	{
		cout << "blad otwarcia pliku";
		Sleep(2000);
		return;
	}
	for (int i = 0; i < nazwa.length(); i++)
	{
		if (nazwa[i]==' ')
		{
			nazwa.at(i) = '-';
		}
	}
	if (nazwa.length()==0)
	{
		nazwa = "-";
	}

	time_t czas = time(0);
	tm czasS;
	localtime_s(&czasS, &czas);
	


	plik <<endl<< punkty<<" " << nazwa<< " " 
		<< (czasS.tm_mday) << "."
		<< (czasS.tm_mon + 1) << "."
		<< (czasS.tm_year + 1900) << " "
		<< (czasS.tm_hour) << ":"
		<< (czasS.tm_min);
	plik.close();
	system("cls");
	cout << "ZAPISANO";
	Sleep(300);
	system("cls");
}

void czyszczeniePliku(string jakiplik) {
	ofstream plik(jakiplik);
	if (!plik)
	{
		cout << "blad otwarcia pliku";
		Sleep(2000);
		return;
	}
	plik.close();

		system("cls");
		cout << "WYCZYSZCZONO";
		Sleep(300);
		system("cls");
	
}

vector<int>kolejnosc1(vector<int>Punkty) {
	vector<int>wynik;
	int osobNaLiscie = Punkty.size(),temp;
	for (int i = 0; i < osobNaLiscie; i++)
	{
		wynik.push_back(int(i));
	}
	for (int i = 1; i < osobNaLiscie; i++)
	{
		for (int j = 1; j < osobNaLiscie; j++)
		{
			if (Punkty[wynik[j-1]]<Punkty[wynik[j]])
			{
				temp = wynik[j];
				wynik[j] = wynik[j - 1];
				wynik[j - 1] = temp;
			}
		}
	}
	return wynik;
}
void ranking() {
	vector<vector<string>>listaRanking(4);
	string nazwa, punkty,czas,godzina,wyborS;
	ifstream plik("ranking.txt");
	system("cls");

		if (!plik)
		{
			cout << "blad otwarcia pliku/nie ma nikogo w rankingu";
			Sleep(2000);
			return;
		}
		while (plik >> punkty >> nazwa >>czas>>godzina)
		{
			listaRanking[0].push_back(punkty);
			listaRanking[1].push_back(nazwa);
			listaRanking[2].push_back(czas);
			listaRanking[3].push_back(godzina);
		}
		plik.close();
		int temp;
		vector<int>Punkty;
		for (int i = 0; i < listaRanking[0].size(); i++)
		{
			temp = stoi(listaRanking[0][i]);
			Punkty.push_back(temp);
		}
		vector<int>kolejnosc=kolejnosc1(Punkty);
			cout << "----RANKING----"<<endl;
			if (listaRanking[0].size() == 0)
			{
				cout << "NIE MA NIKOGO W RANKINGU!" << endl;
				Sleep(2000);
				system("cls");
				return;
			}
			int maxPunkty = (listaRanking[0][kolejnosc[0]]).size();

			for (int i = 0; i < listaRanking[0].size(); i++)
			{
				int obecnaDlugoscPunkty = maxPunkty - listaRanking[0][kolejnosc[i]].size() + 1;
				cout << i + 1 << ". " << listaRanking[0][kolejnosc[i]];
				for (int j = 0; j < obecnaDlugoscPunkty; j++)
				{
					cout << " ";
				}
				cout <<"(" << listaRanking[2][kolejnosc[i]] << " " << listaRanking[3][kolejnosc[i]] << ") " << listaRanking[1][kolejnosc[i]] << endl;
			}

			cout << "Kliknij enter aby przejsc do menu glownego:";
			cin.ignore();
			getline(cin, wyborS);
}
void zasady() {
	string wyborS;
		cout << "+----------------------------------------------- ZASADY GRY ------------------------------------------------+" << endl;
		cout << "|                                                                                                           |" << endl;
		cout << "| Celem gry jest zdobycie jak najwiecej punktow odpowiadajac na pytania.                                    |" << endl;
		cout << "| Ilosc punktow zalezy czasu odpowiedzi trybu gry oraz od zadeklarowanej ilosci odpowiedzi na poczatku      |" << endl;
		cout << "| Istnieja 2 tryby gry jeden z kolami ratunkowymi a drugi bez                                               |" << endl;
		cout << "| W trybie bez kol ratunkowych jest trrudniej ale za to zdobywa sie wiecej punktow za prawidlowa odpowiedz  |" << endl;
		cout << "| Aby zdobyć jakiekolwiek punkty trzeba odpowiedziec na zadeklarowana ilosc pytan                           |" << endl;
		cout << "| Kola ratunkowe 1)50/50-Usuwa 2 odpowiedzi 2)5xPunkty-Mnoży punkty za to pytanie 5 razy 3)Pomin pytanie    |" << endl;
		cout << "| 4)Vabanque-prawidlowa odpowiedz pomija 3 nastepne pytania 5)Sprawdz Odpowiedz-mozesz zobaczyc             |" << endl;
		cout << "| czy odpowiedz jest prawidlowa                                                                             |" << endl;
		cout << "| UWAGA MOZNA WYKORZYSTYWAC MAKSYMALNIE 1 KOLO NA PYTANIE                                                   |" << endl;
		cout << "|                                                                                                           |" << endl;
		cout << "+-----------------------------------------------------------------------------------------------------------+" << endl << endl;
		cout << "Kliknij enter aby porocic do menu:";
		cin.ignore();
		getline(cin, wyborS);
	
}
void koniecGry(int nrPytania,int ilePytanWybralUzytkownik,int punkty,time_t czas) {
	string a;
	cout << "Niestety to nie poprawna odpowiedz" << endl << "Twoj wynik punktowy to: 0" << endl << "Przeszedles juz: " << nrPytania - 1 << " z wybranych " << ilePytanWybralUzytkownik << " pytan" << endl;
	cout << "Ilosc twoich punktow przed zla odpowiedzia wynosila: " << punkty << endl;
	cout << "Granie w ta rozgrywke zajelo ci: " << czas <<" sekund" << endl;
	if (czas >60)
	{
		float czas2 = float(czas) / 60;
		cout << "Czyli inaczej mowiac: " <<fixed<<setprecision(2)<< czas2 << " minut" << endl;
	}
	cout << "Wcisnij enter aby przejsc do menu"<<endl;
	getline(cin, a);
}
void dodaj() {
	pytanie pyt;
	vector<pytanie>listaPytan;
	ifstream plik("podstawa.txt");
	if (!plik)
	{
		cout << "blad odczytu pliku!" << endl;
		Sleep(2000);
		return;
	}
	while (getline(plik, pyt.tresc, '|') and getline(plik, pyt.o[0], '|') and getline(plik, pyt.o[1], '|') and getline(plik, pyt.o[2], '|') and getline(plik, pyt.o[3], '|') and getline(plik, pyt.poprawnaOdpowiedz)) {
		int pOT = stoi(pyt.poprawnaOdpowiedz);
		pyt.poprawnaOdpowiedz = to_string(pOT);
		listaPytan.push_back(pyt);
	}
	plik.close();
	ofstream plik1("pytanie.txt", ios::app);
	if (!plik1)
	{
		cout << "blad odczytu pliku!" << endl;
		Sleep(2000);
		return;
	}

	for (int i = 0; i < listaPytan.size(); i++)
	{

		plik1 << listaPytan[i].tresc << "|";
		for (int j = 0; j < 4; j++)
		{
			plik1 << listaPytan[i].o[j] << "|";
		}
		plik1 << listaPytan[i].poprawnaOdpowiedz << endl;
	}
	plik1.close();

	system("cls");
	cout << "DODANO!" << endl;
	Sleep(300);
	system("cls");
}



void gra() {
	vector<pytanie>listaPytan = vectorPytan();
	time_t start, stop ,czasS,czasK;
	int maxPytan = listaPytan.size(),wybranaIloscPytan,kola,wynik=0,wspolczynnikPunktu=2,mnoznik=1,vabanque=0;
	string wybranaIloscPytanS,kolaS;
	system("cls");
	if (maxPytan == 0) {
		cout << "Brak pytan! Dodaj pytania przed rozpoczeciem gry." << endl;
		Sleep(2000);
		return;
	}
	cout << "Witaj w nowe grze!" << endl;
	cout << "Wybierz ilosc pytan (1-" <<maxPytan<< ") :";
	cin.ignore();
	getline(cin, wybranaIloscPytanS);
	for (int i = 0; i < wybranaIloscPytanS.length(); i++)
	{
		if (wybranaIloscPytanS[i]>='0' and wybranaIloscPytanS[i]<='9')
		{

		}
		else {
			system("cls");
			cout << "Wybrano nie wlasciwa ilosc pytan!";
			Sleep(500);
			return;
		}
	}
	wybranaIloscPytan = stoi(wybranaIloscPytanS);
	if (wybranaIloscPytan<1 or wybranaIloscPytan > maxPytan)
	{
		system("cls");
		cout << "Wybrano nie wlasciwa ilosc pytan!";
		Sleep(500);
		return;
	}
	system("cls");
	bool k = false;
	while (k == false) {
		cout << "Czy grac z kolami ratunkowymi" << endl << "1.Tak" << endl << "2.Nie" << endl << ":";
		getline(cin, kolaS);
		if (kolaS[0] == '1' or kolaS[0] == '2')
		{
			char a = kolaS[0];
			kola = int(a) - '0';
			k = true;
		}
		else {
			system("cls");
			cout << "Nie poprawny wybor!" << endl;
		}
	}
	bool kolaRatunkowe[5] = { true,true,true,true,true};
	if (kola==2)
	{
		for (int i = 0; i < 5; i++)
		{
			kolaRatunkowe[i] = false;
		}
		wspolczynnikPunktu = 6;
	}
	wspolczynnikPunktu = wspolczynnikPunktu * wybranaIloscPytan;
	system("cls");
	srand(time(NULL));
	bool losujDalej =false;
	vector<int>wykorzystanePytania;
	czasS = time(0);
	for (int numerPytania = 1; numerPytania <= wybranaIloscPytan; numerPytania++)
	{
		int losowePytanie;
		do {
			losowePytanie = rand() % maxPytan;
			losujDalej = false;
			for (int i = 0; i < wykorzystanePytania.size(); i++)
			{
				if (losowePytanie == wykorzystanePytania[i])
				{
					losujDalej = true;
				}
			}
		} while (losujDalej==true);
		wykorzystanePytania.push_back(losowePytanie);

		string odpowiedzUzytkownika;
		int poprawnaOdpowiedz = stoi(listaPytan[losowePytanie].poprawnaOdpowiedz);
		cout << numerPytania << ". " << listaPytan[losowePytanie].tresc << endl;
		vector<int>uzyteOdpowiedzi;
		char litery[4] = {'A','B','C','D'};
		string poprawnaLitera;
		for (int odpowiedzi = 0; odpowiedzi < 4; odpowiedzi++)
		{
			bool dobrzeWylosowane;
			int losowaOdpowiedz;
			do {
				losowaOdpowiedz = rand() % 4;
				dobrzeWylosowane = true;
				for (int a = 0; a < uzyteOdpowiedzi.size(); a++)
				{
					if(losowaOdpowiedz==uzyteOdpowiedzi[a]){
						dobrzeWylosowane = false;
					}
				}
			} while (dobrzeWylosowane==false);
			uzyteOdpowiedzi.push_back(losowaOdpowiedz);

			if (losowaOdpowiedz==poprawnaOdpowiedz)
			{
				poprawnaLitera = litery[odpowiedzi];
			}

			cout <<litery[odpowiedzi]<<") " << listaPytan[losowePytanie].o[losowaOdpowiedz] << endl;

		}
		cout << "Obecna ilosc punktow:" << wynik << endl << endl;
		start = time(0);
		cout << "(Pamietaj aby uzywac wielkich liter i tylko 1 np. 'A', aby uzyc jakiegos kola ratunkowego wpisz: '112')"<<endl;
		cout << "Odp:";
		getline(cin, odpowiedzUzytkownika);
		if (odpowiedzUzytkownika == "112") {
			bool skip = false;
			cout << endl << endl;
			string wyborKolaS;
			char wyborKola = '1';
			while (wyborKola != '6') {
				cout << "Kola ratunkowe!" << endl;
				cout << "1. 50/50";
				if (kolaRatunkowe[0] == true)
				{
					cout << " /dostepne";
				}
				else {
					cout << " /niedostepne";
				}
				cout << endl;
				cout << "2. 5x Punkty";
				if (kolaRatunkowe[1] == true)
				{
					cout << " /dostepne";
				}
				else {
					cout << " /niedostepne";
				}
				cout << endl;
				cout << "3. Pomin Pytanie";
				if (kolaRatunkowe[2] == true)
				{
					cout << " /dostepne";
				}
				else {
					cout << " /niedostepne";
				}
				cout << endl;
				cout << "4. Vabanque (mozna pominac 3 pytania)";
				if (kolaRatunkowe[3] == true)
				{
					cout << " /dostepne";
				}
				else {
					cout << " /niedostepne";
				}
				cout << endl;
				cout << "5. Sprawdz odpowiedz";
				if (kolaRatunkowe[4] == true)
				{
					cout << " /dostepne";
				}
				else {
					cout << " /niedostepne";
				}
				cout << endl;
				cout << "6. Powrot" << endl;
				cout << "wybor (liczy sie pierwszy znak jaki wpiszesz):";
				getline(cin, wyborKolaS);
				wyborKola = wyborKolaS[0];
				switch (wyborKola)
				{
				case '1':
					if (kolaRatunkowe[0] == false)
					{
						cout << "Kolo niedostepne!" << endl;
						Sleep(300);
					}
					else {
						kolaRatunkowe[0] = false;
						string a;
						do {
							int x = rand() % 4;
							a = litery[x];
						} while (a == poprawnaLitera);
						int los = rand()%2;
						if (los ==0)
						{
							cout << "Zostaja odpowiedzi: " << poprawnaLitera << " oraz " << a << endl;
						}else{
						cout << "Zostaja odpowiedzi: " << a << " oraz "<<poprawnaLitera<<endl;
						}
					}
					wyborKola = '6';
					break;
				case '2':
					if (kolaRatunkowe[1] == false)
					{
						cout << "Kolo niedostepne!" << endl;
						Sleep(300);
					}
					else {
						kolaRatunkowe[1] = false;
						mnoznik = 5;
					}
					wyborKola = '6';
					break;
				case '3':
					if (kolaRatunkowe[2] == false)
					{
						cout << "Kolo niedostepne!" << endl;
						Sleep(300);
					}
					else {
						kolaRatunkowe[2] = false;
						odpowiedzUzytkownika = poprawnaLitera;
						skip = true;
					}
					wyborKola = '6';

					break;
				case '4':
					if (kolaRatunkowe[3] == false)
					{
						cout << "Kolo niedostepne!" << endl;
						Sleep(300);
					}
					else {
						kolaRatunkowe[3] = false;
						vabanque = 3;
						mnoznik = 10;
					}
					wyborKola = '6';
					break;
				case '5':
					if (kolaRatunkowe[4] == false)

					{
						cout << "Kolo niedostepne!" << endl;
						Sleep(300);
					}
					else {
						kolaRatunkowe[4] = false;
						string odpkolo;
						cout << endl << "Podaj odpowiedz do sprawdzenia przez kolo:";
						getline(cin, odpkolo);
						if (odpkolo == poprawnaLitera)
						{
							cout << "Wydaje mi sie ze to dobra odpowiedz" << endl;
						}
						else {
							cout << "zla odpowiedz!" << endl;
						}

					}
					wyborKola = '6';
					break;
				default:
					if (wyborKola != '6')
					{
						cout << "Nie poprawny wybor!" << endl<<endl;
					}
					Sleep(300);
					break;
				}
			}if (skip != true) {
				cout << "Podaj odpowiedz:";
				getline(cin, odpowiedzUzytkownika);
			}
			else {
				skip = false;
			}
			system("cls");
		}
		if (odpowiedzUzytkownika==poprawnaLitera)
		{
			cout << "DOBRZE!";
			stop = time(0);
			if (mnoznik==10)
			{
				wynik += 3 * wspolczynnikPunktu*10;
				mnoznik = 1;
			}
			wynik += (wspolczynnikPunktu*6 /int(difftime(stop,start)))*mnoznik;
			if (mnoznik==5)
			{
				mnoznik = 1;
			}
			numerPytania += vabanque;
			if (vabanque==3)
			{
				vabanque = 0;
			}
			Sleep(500);
		}
		else
		{
			czasK = time(0);
			time_t czas = difftime(czasK, czasS);
			system("cls");
			koniecGry(numerPytania,wybranaIloscPytan,wynik,czas);
			Sleep(500);
			return;
		}
		system("cls");

	}
	czasK = time(0);
	cout << "Gratulacje udalo ci sie wygrac!!" << endl;
	cout << "Twoj wynik to: " << wynik << endl;
	time_t czas = difftime(czasK, czasS);
	cout << "Przejscie zajelo ci:" << czas << " sekund" << endl;
	if (czas > 60)
	{
		float czas2 = float(czas) / 60;
		cout << "Inaczej mowiac: " <<fixed<< setprecision(2) << czas2 << "minut" << endl;
	}
	string nazwa;
	cout << "Podaj nazwe do zapisu w rankingu:";
	getline(cin, nazwa);
	rankingPlus(nazwa, to_string(wynik));
}





void opcje(){
	system("cls");
	int wyborOpcje = 2;
	while (wyborOpcje !=7)
	{
		cout << "---OPCJE---" << endl;
		cout << "1. Dodaj pytanie" << endl;
		cout << "2. Wypisz wszystkie pytania" << endl;
		cout << "3. Dodaj osobe do rankingu" << endl;
		cout << "4. Wyczysc ranking" << endl;
		cout << "5. Usun wszystkie pytania z puli" << endl;
		cout << "6. Dodaj do pliku pytania z bazy podstawowej" << endl;
		cout << "7. Powrot" << endl;
		cout << "Podaj wybor:";
		cin >> wyborOpcje;
		string nazwa,punkty;
		bool liczba = false;
		switch (wyborOpcje)
		{
		case 1:
			dodajPytanie();
			system("cls");
			break;
		case 2:
			listaPytan();
			system("cls");
			break;
		case 3:
			system("cls");
			cout << "podaj nazwe gracza:";
			cin.ignore();
			getline(cin, nazwa);
			while(liczba == false){
			cout << "ilosc punktow:";
			getline(cin, punkty);
			for (int i = 0; i < punkty.size(); i++)
			{
				if (punkty[i] < '0' or punkty[i] > '9') {
					liczba = false;
					system("cls");
					cout << "Nie poprawna liczba!" << endl;
					break;
				}
				else {
					liczba = true;
				}
			}
			}

			rankingPlus(nazwa,punkty);
			system("cls");
			break;
		case 4:
			system("cls");
			czyszczeniePliku("ranking.txt");
			break;
		case 5:
			system("cls");
			czyszczeniePliku("pytanie.txt");
			break;
		case 6:
			dodaj();
			break;
		default:
			if (wyborOpcje != 7)
			{
				cout << "Nieprawidlowy wybor!" << endl;
				Sleep(1500);
				system("cls");

			}
			else {
				system("cls");
			}
			break;
		}
	}
}

int main() {
	int wyborMenu=2;
	while (wyborMenu != 5)
	{
		cout << "+-\\  |   | ---+---  +--+   \\    |  -+-   +--+" << endl;
		cout << "|  |  \\ /     |    |    |  |\\   |   |   |    |" << endl;
		cout << "+-/    |      |   |------| | \\  |   |  |------|" << endl;
		cout << "|      |      |   |      | |  \\ |   |  |      |" << endl;
		cout << "|      |      |   |      | |   \\|  -+- |      |" << endl<<endl<<endl;
		cout << "1. ZAGRAJ!" << endl;
		cout << "2. Ranking" << endl;
		cout << "3. Opcje" << endl;
		cout << "4. Zasady" << endl;
		cout << "5. Wyjscie" << endl;
		cout << "Podaj wybor:";
		cin >> wyborMenu;
		switch (wyborMenu)
		{
		case 1:
			gra();
			system("cls");
			break;
		case 2:
			ranking();
			system("cls");
			break;
		case 3:
			opcje();
			system("cls");
			break;
		case 4:
			system("cls");
			zasady();
			system("cls");
			break;
		default:
			if (wyborMenu!=5)
			{
				cout << "Nieprawidlowy wybor!"<<endl;
				Sleep(1500);
				system("cls");

			}
			else {
				system("cls");
				cout << "Do nastepnego!" << endl;
			}
			break;
		}
	}
	return 0;
	system("pause");
}
