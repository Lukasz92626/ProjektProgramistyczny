// Fill out your copyright notice in the Description page of Project Settings.


#include "Plansza.h"

/*	Funkcja do zwracania liczb do logow
*	liczba - zwracana liczba do logow
*/

void log_liczba(int liczba) {
	FText tmp = FText::AsNumber(liczba);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *tmp.ToString());
}

/*	Funkcja do zwracania znakow do logow
*	znak - zwracany znak do logow
*/

void log_znak(char znak) {
	FText tmp = FText::FromString(FString(1, &znak));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *tmp.ToString());
}

/*	Funkcja do obliczania silnii
*	liczba - do jakiej liczby ma byc obliczona silnia
*	return wynik - wynik
*/

int8 APlansza::silnia(int8 liczba) {
	int8 wynik = 1;
	for (int8 i = 1; i <= liczba; ++i) {
		wynik *= i;
	}
	return wynik;
}

/*	Konstruktor domyslny
*/

// Sets default values
APlansza::APlansza() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; //odpowiedzialne za wlaczenie tick
	SetActorLocation(FVector(0, 0, 0));
	szerokosc_planszy = 10;
	wysokosc_planszy = 20;
	szer_szescianu = 100;
	punkty = 0;
	rotacja = 0;
	blok = '!';
	czyPauza = false;
	for (int8 i = 0; i < szerokosc_planszy; ++i) {
		TArray<ABlokAktor*> Tmp;
		for (int8 j = 0; j < wysokosc_planszy; ++j) {
			Tmp.Add(nullptr);
		}
		szesciany_na_planszy.Add(Tmp);
	}
	/*if (szesciany_na_planszy[0][0] == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Jest rowne nullptr"));
	}*/
	//Wspolrzedne
	//Prawo, Ty³, Góra
	//012
	//345
	//678[10]
	//9
	poruszanie.Add(FVector(-100, 0, 100)); //0
	poruszanie.Add(FVector(0, 0, 100)); //1
	poruszanie.Add(FVector(100, 0, 100)); //2
	poruszanie.Add(FVector(-100, 0, 0)); //3
	poruszanie.Add(FVector(0, 0, 0)); //4
	poruszanie.Add(FVector(100, 0, 0)); //5
	poruszanie.Add(FVector(-100, 0, -100)); //6
	poruszanie.Add(FVector(0, 0, -100)); //7
	poruszanie.Add(FVector(100, 0, -100)); //8
	//poruszanie.Add(FVector(-100, 0, 200)); //9
	poruszanie.Add(FVector(-100, 0, -200)); //9
	poruszanie.Add(FVector(200, 0, -100)); //10

	//wsp_poczatku = FVector((szerokosc_planszy / 2) * szer_szescianu, 0, (wysokosc_planszy-4) * szer_szescianu);
	wsp_poczatku = FVector(500, 0, 1800);
	//[5][17]

	wsp_akt_bloku.SetNum(4);
	for (int32 i = 0; i < 4; ++i)
	{
		wsp_akt_bloku[i].SetNum(2);
	}

	stadium_gry = 0;

	wsp_srodka_akt.SetNum(2);
	wsp_srodka_akt[0] = 5;
	wsp_srodka_akt[1] = 18;

	czyPrzesuwane = false;
}

// Called when the game starts or when spawned
void APlansza::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Rozpoczecie rozgrywki"));
}

// Called every frame
void APlansza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (czyPauza) {
	//	return;
	//}
	//else if (stadium_gry == 0) {
	//	//0 - blok nie wygenerowany
	//	generowanie_bloku();
	//	
	//	stadium_gry = 1;
	//	//sprawdzanie czy blok zmiescil sie na planszy
	//	int8 suma_kontrolna = 0;
	//	for (int8 i = 0; i < 4; ++i) {
	//		if (wsp_akt_bloku[i][1] > 0) { //sprawdza czy nie jest na samym dole
	//			if (szesciany_na_planszy[wsp_akt_bloku[i][0]][wsp_akt_bloku[i][1]] == nullptr) { //sprawdza czy pole pod szescianem nie jest zajete
	//				suma_kontrolna++;
	//			}
	//		}
	//	}
	//	if (suma_kontrolna != 4) {
	//		stadium_gry = 3;
	//		for (int8 i = 0; i < 4; ++i) {
	//			szesciany_blok[i]->Destroy(); //usuwanie obiektu dziedziczacego po AActor
	//		}
	//	}
	//}
	//else if (stadium_gry == 1) {
	//	//1 - blok wygenerowany i opada
	//	//InputComponent->BindKey(EKeys::Right, IE_Pressed, this, &APlansza::ruch_w_prawo);
	//	//opadanie();
	//	//ruch_w_prawo();
	//	//obrot();
	//	czyszczenie_linii();
	//	//stadium_gry = 3;
	//}
	//else if (stadium_gry == 2) {
	//	//2 - blok opadl

	//}
	//if (stadium_gry == 3) {
	//	//3 - koniec gry
	//	UE_LOG(LogTemp, Warning, TEXT("KONIEC GRY"));
	//	stadium_gry = 4;
	//}
	
}

/*	Metoda generujaca nowy blok
*/

void APlansza::generowanie_bloku() {
	int8 los = FMath::RandRange(0, 6);
	UE_LOG(LogTemp, Warning, TEXT("Wylosowano liczbe"));
	switch (los) {
	case 0:
		//L
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_L, GetActorLocation(), GetActorRotation()));
		}
		szesciany_blok[0]->SetActorLocation(GetActorLocation() + poruszanie[0] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(GetActorLocation() + poruszanie[3] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(GetActorLocation() + poruszanie[6] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(GetActorLocation() + poruszanie[7] + wsp_poczatku);

		wsp_akt_bloku[0][0] = 4; wsp_akt_bloku[0][1] = 19;
		wsp_akt_bloku[1][0] = 4; wsp_akt_bloku[1][1] = 18;
		wsp_akt_bloku[2][0] = 4; wsp_akt_bloku[2][1] = 17;
		wsp_akt_bloku[3][0] = 5; wsp_akt_bloku[3][1] = 17;
		blok = 'L';
		break;
	case 1:
		//J
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_J, GetActorLocation(), GetActorRotation()));
		}
		szesciany_blok[0]->SetActorLocation(GetActorLocation() + poruszanie[1] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(GetActorLocation() + poruszanie[4] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(GetActorLocation() + poruszanie[7] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(GetActorLocation() + poruszanie[6] + wsp_poczatku);

		wsp_akt_bloku[0][0] = 5; wsp_akt_bloku[0][1] = 19;
		wsp_akt_bloku[1][0] = 5; wsp_akt_bloku[1][1] = 18;
		wsp_akt_bloku[2][0] = 5; wsp_akt_bloku[2][1] = 17;
		wsp_akt_bloku[3][0] = 4; wsp_akt_bloku[3][1] = 17;
		blok = 'J';
		break;
	case 2:
		//S
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_S, GetActorLocation(), GetActorRotation()));
		}
		szesciany_blok[0]->SetActorLocation(GetActorLocation() + poruszanie[6] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(GetActorLocation() + poruszanie[7] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(GetActorLocation() + poruszanie[4] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(GetActorLocation() + poruszanie[5] + wsp_poczatku);

		wsp_akt_bloku[0][0] = 4; wsp_akt_bloku[0][1] = 17;
		wsp_akt_bloku[1][0] = 5; wsp_akt_bloku[1][1] = 17;
		wsp_akt_bloku[2][0] = 5; wsp_akt_bloku[2][1] = 18;
		wsp_akt_bloku[3][0] = 6; wsp_akt_bloku[3][1] = 18;
		blok = 'S';
		break;
	case 3:
		//Z
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_Z, GetActorLocation(), GetActorRotation()));
		}
		szesciany_blok[0]->SetActorLocation(GetActorLocation() + poruszanie[3] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(GetActorLocation() + poruszanie[4] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(GetActorLocation() + poruszanie[7] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(GetActorLocation() + poruszanie[8] + wsp_poczatku);

		wsp_akt_bloku[0][0] = 4; wsp_akt_bloku[0][1] = 18;
		wsp_akt_bloku[1][0] = 5; wsp_akt_bloku[1][1] = 18;
		wsp_akt_bloku[2][0] = 5; wsp_akt_bloku[2][1] = 17;
		wsp_akt_bloku[3][0] = 6; wsp_akt_bloku[3][1] = 17;
		blok = 'Z';
		break;
	case 4:
		//T
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_T, GetActorLocation(), GetActorRotation()));
		}
		szesciany_blok[0]->SetActorLocation(GetActorLocation() + poruszanie[3] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(GetActorLocation() + poruszanie[4] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(GetActorLocation() + poruszanie[5] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(GetActorLocation() + poruszanie[7] + wsp_poczatku);

		wsp_akt_bloku[0][0] = 4; wsp_akt_bloku[0][1] = 18;
		wsp_akt_bloku[1][0] = 5; wsp_akt_bloku[1][1] = 18;
		wsp_akt_bloku[2][0] = 6; wsp_akt_bloku[2][1] = 18;
		wsp_akt_bloku[3][0] = 5; wsp_akt_bloku[3][1] = 17;
		blok = 'T';
		break;
	case 5:
		//O
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_O, GetActorLocation(), GetActorRotation()));
		}
		szesciany_blok[0]->SetActorLocation(GetActorLocation() + poruszanie[3] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(GetActorLocation() + poruszanie[4] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(GetActorLocation() + poruszanie[6] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(GetActorLocation() + poruszanie[7] + wsp_poczatku);

		wsp_akt_bloku[0][0] = 4; wsp_akt_bloku[0][1] = 18;
		wsp_akt_bloku[1][0] = 5; wsp_akt_bloku[1][1] = 18;
		wsp_akt_bloku[2][0] = 4; wsp_akt_bloku[2][1] = 17;
		wsp_akt_bloku[3][0] = 5; wsp_akt_bloku[3][1] = 17;
		blok = 'O';
		break;
	case 6:
		//I
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_I, GetActorLocation(), GetActorRotation()));
		}
		szesciany_blok[0]->SetActorLocation(GetActorLocation() + poruszanie[6] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(GetActorLocation() + poruszanie[7] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(GetActorLocation() + poruszanie[8] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(GetActorLocation() + poruszanie[10] + wsp_poczatku); // pozycja lezaca

		wsp_akt_bloku[0][0] = 4; wsp_akt_bloku[0][1] = 17;
		wsp_akt_bloku[1][0] = 5; wsp_akt_bloku[1][1] = 17;
		wsp_akt_bloku[2][0] = 6; wsp_akt_bloku[2][1] = 17;
		wsp_akt_bloku[3][0] = 7; wsp_akt_bloku[3][1] = 17;

		blok = 'I';
		break;
	}
	rotacja = 0;
}

/*	Metoda odpowiedzialna za opadanie bloku
*/

void APlansza::opadanie() {
	if (czyPrzesuwane) {
		return;
	}
	czyPrzesuwane = true;
	int8 suma_kontrolna = 0; //jesli rowne 4 to oznacza, ze kazdy szescian bloku moze sie poruszyc sie w dol
	//FPlatformProcess::Sleep(3);
	for (int8 i = 0; i < 4; ++i) {
		if (wsp_akt_bloku[i][1] > 0) { //sprawdza czy nie jest na samym dole
			if (szesciany_na_planszy[wsp_akt_bloku[i][0]][wsp_akt_bloku[i][1] - 1] == nullptr) { //sprawdza czy pole pod szescianem nie jest zajete
				++suma_kontrolna;
			}
		}
	}
	if (suma_kontrolna == 4) {
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(0, 0, -100)); //opadanie
			wsp_akt_bloku[i][1] = wsp_akt_bloku[i][1] - 1;
			wsp_srodka_akt[1] = wsp_srodka_akt[1] - 1;
		}
	}
	else {
		for (int8 i = 0; i < 4; ++i) {
			szesciany_na_planszy[wsp_akt_bloku[i][0]][wsp_akt_bloku[i][1]] = szesciany_blok[i];
		}
		szesciany_blok.Empty();
		stadium_gry = 0;
	}
	czyPrzesuwane = false;
}

/*	Metoda odpowiedzialna za ruch bloku w prawo
*/

void APlansza::ruch_w_prawo() {
	if (czyPrzesuwane) {
		return;
	}
	czyPrzesuwane = true;
	int8 suma_kontrolna = 0;
	for (int8 i = 0; i < 4; ++i) {
		if (wsp_akt_bloku[i][0] < szerokosc_planszy-1) { //sprawdza czy nie jest przy prawej krawêdzi
			if (szesciany_na_planszy[wsp_akt_bloku[i][0] + 1][wsp_akt_bloku[i][1]] == nullptr) { //sprawdza czy pole na prawo od szescianu nie jest zajete
				++suma_kontrolna;
			}
		}
	}
	if (suma_kontrolna == 4) {
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(100, 0, 0)); //ruch w prawo
			wsp_akt_bloku[i][0] = wsp_akt_bloku[i][0] + 1;
			wsp_srodka_akt[0] = wsp_srodka_akt[0] + 1;
		}
	}
	czyPrzesuwane = false;
}

/*	Metoda odpowiedzialna za ruch bloku w lewo
*/

void APlansza::ruch_w_lewo() {
	if (czyPrzesuwane) {
		return;
	}
	czyPrzesuwane = true;
	int8 suma_kontrolna = 0;
	for (int8 i = 0; i < 4; ++i) {
		if (wsp_akt_bloku[i][0] > 0) { //sprawdza czy nie jest przy lewej krawedzi
			if (szesciany_na_planszy[wsp_akt_bloku[i][0] - 1][wsp_akt_bloku[i][1]] == nullptr) { //sprawdza czy pole na prawo od szescianu nie jest zajete
				++suma_kontrolna;
			}
		}
	}
	if (suma_kontrolna == 4) {
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(-100, 0, 0)); //ruch w lewo
			wsp_akt_bloku[i][0] = wsp_akt_bloku[i][0] - 1;
			wsp_srodka_akt[0] = wsp_srodka_akt[0] - 1;
		}
	}
	czyPrzesuwane = false;
}

/*	Metoda odpowiedzialna za obracanie bloku
*/

void APlansza::obrot() {
	if (czyPrzesuwane) {
		return;
	}
	czyPrzesuwane = true;
	if (blok == 'O') {
		return;
	}
	else if (blok == 'I') {
		for (int k = 0; k < 2; ++k) {
			if (rotacja == 0 || rotacja == 2) { //obrot dla pozycji lezacej
				// nie zmienia sie pozycja dla zerowego

				wsp_akt_bloku[1][0] = wsp_akt_bloku[1][0] - 1;
				wsp_akt_bloku[1][1] = wsp_akt_bloku[1][1] + 1;
				szesciany_blok[1]->SetActorLocation(szesciany_blok[1]->GetActorLocation() + FVector(-100, 0, 100));

				wsp_akt_bloku[2][0] = wsp_akt_bloku[2][0] - 2;
				wsp_akt_bloku[2][1] = wsp_akt_bloku[2][1] + 2;
				szesciany_blok[2]->SetActorLocation(szesciany_blok[2]->GetActorLocation() + FVector(-200, 0, 200));

				wsp_akt_bloku[3][0] = wsp_akt_bloku[3][0] - 3;
				wsp_akt_bloku[3][1] = wsp_akt_bloku[3][1] + 3;
				szesciany_blok[3]->SetActorLocation(szesciany_blok[3]->GetActorLocation() + FVector(-300, 0, 300));
			}
			else { //obrot dla pozycji stojacej
				// nie zmienia sie pozycja dla zerowego

				wsp_akt_bloku[1][0] = wsp_akt_bloku[1][0] + 1;
				wsp_akt_bloku[1][1] = wsp_akt_bloku[1][1] - 1;
				szesciany_blok[1]->SetActorLocation(szesciany_blok[1]->GetActorLocation() + FVector(100, 0, -100));

				wsp_akt_bloku[2][0] = wsp_akt_bloku[2][0] + 2;
				wsp_akt_bloku[2][1] = wsp_akt_bloku[2][1] - 2;
				szesciany_blok[2]->SetActorLocation(szesciany_blok[2]->GetActorLocation() + FVector(200, 0, -200));

				wsp_akt_bloku[3][0] = wsp_akt_bloku[3][0] + 3;
				wsp_akt_bloku[3][1] = wsp_akt_bloku[3][1] - 3;
				szesciany_blok[3]->SetActorLocation(szesciany_blok[3]->GetActorLocation() + FVector(300, 0, -300));
			}
			rotacja++;
			if (rotacja == 4)
				rotacja = 0;
			//log_liczba(rotacja);
			int8 suma_kontrolna = 0;
			for (int i = 0; i < 4; ++i) {
				if(wsp_akt_bloku[i][0] < 10 && wsp_akt_bloku[i][0] >= 0 && wsp_akt_bloku[i][1] >= 0 && wsp_akt_bloku[i][1] < 20)
					if (szesciany_na_planszy[wsp_akt_bloku[i][0]][wsp_akt_bloku[i][1]] == nullptr)
						suma_kontrolna++;
			}
			if (suma_kontrolna == 4)
				break;
		}
		return;
	}
	//log_znak(blok);
	for (int8 k = 0; k < 4; ++k) {
		for (int8 i = 0; i < 4; ++i) {
			//UE_LOG(LogTemp, Warning, TEXT("Petla wewnetrzna."));
			int32 tmp1 = wsp_akt_bloku[i][0] - wsp_srodka_akt[0];
			int32 tmp2 = wsp_akt_bloku[i][1] - wsp_srodka_akt[1];
			if (tmp1 == 0 && tmp2 == 0) { //0 0
				//nic nie robi bo jest na swoim miejscu
			}
			else if (tmp1 == 0 && tmp2 == 1) { //1 0
				wsp_akt_bloku[i][0] = wsp_akt_bloku[i][0] + 1;
				wsp_akt_bloku[i][1] = wsp_akt_bloku[i][1] - 1;
				szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(100, 0, -100));
			}
			else if (tmp1 == 1 && tmp2 == 1) { //1 -1
				wsp_akt_bloku[i][0] = wsp_akt_bloku[i][0] + 0;
				wsp_akt_bloku[i][1] = wsp_akt_bloku[i][1] - 2;
				szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(0, 0, -200));
			}
			else if (tmp1 == 1 && tmp2 == 0) { //0 -1
				wsp_akt_bloku[i][0] = wsp_akt_bloku[i][0] - 1;
				wsp_akt_bloku[i][1] = wsp_akt_bloku[i][1] - 1;
				szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(-100, 0, -100));
			}
			else if (tmp1 == 1 && tmp2 == -1) { //-1 -1
				wsp_akt_bloku[i][0] = wsp_akt_bloku[i][0] - 2;
				wsp_akt_bloku[i][1] = wsp_akt_bloku[i][1] + 0;
				szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(-200, 0, 0));
			}
			else if (tmp1 == 0 && tmp2 == -1) { //-1 0
				wsp_akt_bloku[i][0] = wsp_akt_bloku[i][0] - 1;
				wsp_akt_bloku[i][1] = wsp_akt_bloku[i][1] + 1;
				szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(-100, 0, 100));
			}
			else if (tmp1 == -1 && tmp2 == -1) { //-1 1
				wsp_akt_bloku[i][0] = wsp_akt_bloku[i][0] + 0;
				wsp_akt_bloku[i][1] = wsp_akt_bloku[i][1] + 2;
				szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(0, 0, 200));
			}
			else if (tmp1 == -1 && tmp2 == 0) { //0 1
				wsp_akt_bloku[i][0] = wsp_akt_bloku[i][0] + 1;
				wsp_akt_bloku[i][1] = wsp_akt_bloku[i][1] + 1;
				szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(100, 0, 100));
			}
			else if (tmp1 == -1 && tmp2 == 1) { //1 1
				wsp_akt_bloku[i][0] = wsp_akt_bloku[i][0] + 2;
				wsp_akt_bloku[i][1] = wsp_akt_bloku[i][1] + 0;
				szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(200, 0, 0));
			}
		}
		rotacja++;
		if (rotacja == 4) {
			rotacja = 0;
		}
		int8 suma_kontrolna = 0;
		for (int i = 0; i < 4; ++i) {
			if (wsp_akt_bloku[i][0] < 10 && wsp_akt_bloku[i][0] >= 0 && wsp_akt_bloku[i][1] >= 0 && wsp_akt_bloku[i][1] < 20)
				if (szesciany_na_planszy[wsp_akt_bloku[i][0]][wsp_akt_bloku[i][1]] == nullptr)
					suma_kontrolna++;
			//log_liczba(suma_kontrolna);
		}
		if (suma_kontrolna == 4) {
			//UE_LOG(LogTemp, Warning, TEXT("Suma_kontrolna."));
			break;
		}
	}
	
	czyPrzesuwane = false;
}

/*	Metoda odpowiedzialna za czyszczenie linii
*/

void APlansza::czyszczenie_linii() {
	if (czyPrzesuwane) {
		return;
	}
	czyPrzesuwane = true;
	int8 ile_linii = 0;
	for (int8 i = 0; i < wysokosc_planszy; ++i) {
		int8 suma_kontrolna = 0; //jesli rowne szerokosc to wtedy znaczy, ze nalezy linie wyczyscic
		for (int8 j = 0; j < szerokosc_planszy; ++j) {
			if (szesciany_na_planszy[j][i] == nullptr) {
				break;
			}
			suma_kontrolna++;
		}
		//UE_LOG(LogTemp, Warning, TEXT("Suma kontrolna czyszczenie linii:"));
		//log_liczba(suma_kontrolna);
		if (suma_kontrolna == szerokosc_planszy) {
			//czyszczenie linii
			for (int8 j = 0; j < szerokosc_planszy; ++j) {
				szesciany_na_planszy[j][i]->Destroy();
				szesciany_na_planszy[j][i] = nullptr;
				suma_kontrolna++;
			}

			//przesuwanie blokow powyzej w dol
			for (int8 j = i + 1; j < wysokosc_planszy; ++j) {
				for (int8 k = 0; k < szerokosc_planszy; ++k) {
					if (szesciany_na_planszy[k][j] != nullptr) {
						szesciany_na_planszy[k][j - 1] = szesciany_na_planszy[k][j];
						szesciany_na_planszy[k][j] = nullptr;
						szesciany_na_planszy[k][j - 1]->SetActorLocation(szesciany_na_planszy[k][j - 1]->GetActorLocation() + FVector(0, 0, -100));
					}
				}
			}
			--i; //aby sprawdzic linie ktora byla wczesniej powyzej
			ile_linii++;
		}
	}
	punkty += ile_linii * silnia(ile_linii);
	UE_LOG(LogTemp, Warning, TEXT("Liczba punktow:"));
	log_liczba(punkty);
	czyPrzesuwane = false;
}

/*	Metoda odpowiedzialna za sterowanie wlaczeniem pauzy
*/

void APlansza::pauza() {
	if (czyPauza) {
		czyPauza = false;
	}
	else {
		czyPauza = true;
	}
}