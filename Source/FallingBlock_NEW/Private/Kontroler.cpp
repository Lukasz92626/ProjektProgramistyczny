// Fill out your copyright notice in the Description page of Project Settings.


#include "Kontroler.h"
#include "GlownyWidget.h"
#include "TablicaRekordowSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Kamera.h"
#include "Blueprint/UserWidget.h"

/*	Funkcja do zwracania liczb typu int do logow
*	liczba - zwracana liczba do logow
*/

void AKontroler::log_liczba(int liczba) {
	FText tmp = FText::AsNumber(liczba);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *tmp.ToString());
}

/*	Funkcja do zwracania znakow do logow
*	znak - zwracany znak do logow
*/

void AKontroler::log_znak(char znak) {
	FText tmp = FText::FromString(FString(1, &znak));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *tmp.ToString());
}

/*	Funkcja do zwracania liczb do logow
*	liczba - zwracana liczba do logow
*/

void AKontroler::log_float(float liczba) {
	FText tmp = FText::AsNumber(liczba);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *tmp.ToString());
}

/*	Funkcja do obliczania silnii
*	liczba - do jakiej liczby ma byc obliczona silnia
*	return wynik - wynik
*/

int32 AKontroler::silnia(int32 liczba) {
	int32 wynik = 1;
	for (int32 i = 1; i <= liczba; ++i) {
		wynik *= i;
	}
	return wynik;
}

/*	Setup Input Component
*/

void AKontroler::SetupInputComponent() {
	Super::SetupInputComponent();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent dziala"));

		InputComponent->BindKey(EKeys::Right, IE_Pressed, this, &AKontroler::ruch_w_prawo);
		InputComponent->BindKey(EKeys::Left, IE_Pressed, this, &AKontroler::ruch_w_lewo);
		InputComponent->BindKey(EKeys::Up, IE_Pressed, this, &AKontroler::obrot);
		InputComponent->BindKey(EKeys::Down, IE_Pressed, this, &AKontroler::opadanie_test);
		InputComponent->BindKey(EKeys::P, IE_Pressed, this, &AKontroler::pauza);
		InputComponent->BindKey(EKeys::N, IE_Pressed, this, &AKontroler::zamiana_bloku);
		InputComponent->BindKey(EKeys::D, IE_Pressed, this, &AKontroler::interfejs_kasowania_linii);
		InputComponent->BindKey(EKeys::Q, IE_Pressed, this, &AKontroler::podpowiedz);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent nie dziala"));
	}
}

/*	Metoda odpowiedzialna za ruch w prawo
*/

void AKontroler::ruch_w_prawo_test() {
	//UE_LOG(LogTemp, Warning, TEXT("Ruch w prawo"));
	ruch_w_prawo();
}

/*	Metoda odpowiedzialna za ruch w lewo
*/

void AKontroler::ruch_w_lewo_test() {
	//Plan->ruch_w_lewo();
	//UE_LOG(LogTemp, Warning, TEXT("Ruch w lewo"));
	ruch_w_lewo();
}

/*	Metoda odpowiedzialna za obrot
*/

void AKontroler::obrot_test() {
	//UE_LOG(LogTemp, Warning, TEXT("Obrot"));
	obrot();
}

/*	Metoda odpowiedzialna za przyspieszanie opadania
*/

void AKontroler::opadanie_test() {
	if (czyPrzesuwane) {
		return;
	}
	int8 suma_kontrolna = 0; //jesli rowne ilosci szescianow bloku to oznacza, ze kazdy szescian bloku moze sie poruszyc sie w dol
	for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
		if (wsp_akt_bloku[i][1] > 0) { //sprawdza czy nie jest na samym dole
			if (szesciany_na_planszy[wsp_akt_bloku[i][0]][wsp_akt_bloku[i][1] - 2] == nullptr) { //sprawdza czy pole pod szescianem nie jest zajete
				++suma_kontrolna;
			}
		}
	}
	//sprawdzanie czy blok zmiescil sie na planszy
	if (suma_kontrolna != ile_szescianow_bloku)
		return
	//UE_LOG(LogTemp, Warning, TEXT("Ruch w dol"));
	opadanie();
}

/*	Konstruktor domyslny
*/

// Sets default values
AKontroler::AKontroler() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; //odpowiedzialne za wlaczenie tick
	bShowMouseCursor = true; //odpowiedzialne za pokazanie kursora myszy
	/*FInputModeUIOnly InputMode;
	SetInputMode(InputMode);*/
	//SetActorLocation(FVector(0, 0, 0)); // nie posiada wspolrzednych
	Wsp_Startu = FVector(0, 0, 0);
	Rotacja_Standardowa = FRotator(0.0f, 0.0f, 0.0f);
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

	wsp_akt_bloku.SetNum(9);
	for (int32 i = 0; i < 9; ++i) {
		wsp_akt_bloku[i].SetNum(2);
	}

	stadium_gry = 2;

	wsp_srodka_spawn.SetNum(2);
	wsp_srodka_spawn[0] = 5;
	wsp_srodka_spawn[1] = 18;

	wsp_srodka_akt.SetNum(2);
	wsp_srodka_akt[0] = wsp_srodka_spawn[0];
	wsp_srodka_akt[1] = wsp_srodka_spawn[1];

	czyPrzesuwane = false;

	nr_bloku = 0;

	WyczyscInformacja();

	ile_szescianow_bloku = 4;

	wsp_cien.SetNum(9);
	for (int32 i = 0; i < 9; ++i) {
		wsp_cien[i].SetNum(2);
	}

	zestaw_blokow = 0;
	rozmiar_planszy = 0;
	tryb_gry = 0;

	wsp_znacznik = 0;
	czyKasowanie = false;

	limit_blokow = 50;
	oczekiwane_punkty = 2000;

	czy_podpowiedz = false;

	//static ConstructorHelpers::FClassFinder<UGlownyWidget> WidgetClassFinder(TEXT("FallingBlock_NEW/Content/Blueprints/HUD/BP_GlownyWidget.BP_GlownyWidget_C"));
	//static ConstructorHelpers::FClassFinder<UGlownyWidget> WidgetClassFinder(TEXT("/Game/Blueprints/HUD/BP_GlownyWidget.BP_GlownyWidget_C"));
	//Skopiowane: / Script / UMGEditor.WidgetBlueprint'/Game/Blueprints/HUD/BP_GlownyWidget.BP_GlownyWidget'
	// / Script / UMGEditor.WidgetBlueprint'/Game/Blueprints/HUD/BP_GlownyWidget.BP_GlownyWidget'
	/*if (WidgetClassFinder.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("WidgetClassFinder.Succeeded"));
		WidgetClass = WidgetClassFinder.Class;
	}*/


}

//Called when the game starts or when spawned
void AKontroler::BeginPlay() {
	Super::BeginPlay();

	//bShowMouseCursor = true; //odpowiedzialne za kursor myszy
	////usuwanie obracania kamery mysza
	//InputComponent->AxisBindings.RemoveAll(
	//	[&](const FInputAxisBinding& Binding)
	//	{
	//		return Binding.AxisName == "Turn" || Binding.AxisName == "LookUp";
	//	}
	//);

	TSubclassOf < UGlownyWidget > WidgetClass = LoadClass<UGlownyWidget>(nullptr, TEXT("/Game/Blueprints/HUD/BP_GlownyWidget.BP_GlownyWidget_C"));
	//static ConstructorHelpers::FClassFinder<UGlownyWidget> WidgetClassFinder(TEXT("/Game/Blueprints/HUD/BP_GlownyWidget.BP_GlownyWidget_C"));
	if (WidgetClass) {
		MyWidgetInstance = CreateWidget<UGlownyWidget>(this, WidgetClass);
		if (MyWidgetInstance) {
			MyWidgetInstance->AddToViewport();
		}
	}

	//C:/Users/lukasz/Documents/Unreal Projects/FallingBlock_NEW/Content/Blueprints/BP_MenuWidget.uasset
	// / Script / UMGEditor.WidgetBlueprint'/Game/Blueprints/BP_MenuWidget.BP_MenuWidget'
	//static ConstructorHelpers::FClassFinder<UUserWidget> Menu_blueprint(TEXT("/Game/Blueprints/BP_MenuWidget.BP_MenuWidget_C"));
	TSubclassOf < UMenuWidget > MenuClass = LoadClass<UMenuWidget>(nullptr, TEXT("/Game/Blueprints/BP_MenuWidget.BP_MenuWidget_C"));
	if (MenuClass) {
		UE_LOG(LogTemp, Warning, TEXT("Menu"));
		MenuInstance = CreateWidget<UMenuWidget>(this, MenuClass);
		if (MenuInstance) {
			MenuInstance->AddToViewport();
		}
	}

	//Tworzenie kamery
	FVector CameraLocation(1000.0f, 1500.0f, 1000.0f);
	FRotator CameraRotation(90.0f, 0.0f, 90.0f);
	GlownaKamera = GetWorld()->SpawnActor<AKamera>(AKamera::StaticClass(), CameraLocation, CameraRotation);

	if (GlownaKamera) {
		SetViewTargetWithBlend(GlownaKamera);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Nie stworzono kamery."));
	}
}

/*	Metoda odpowiedzialna zaktualizowanie punktow na widget
*/

void AKontroler::UpdatePunkty() {
	if (MyWidgetInstance && MyWidgetInstance->TextBlock_Punkty_liczba) {
		FText tmp = FText::AsNumber(punkty);
		MyWidgetInstance->TextBlock_Punkty_liczba->SetText(tmp);
	}
}

/*	Metoda odpowiedzialna zaktualizowanie numeru bloku na widget
*/

void AKontroler::UpdateNrBloku() {
	if (MyWidgetInstance && MyWidgetInstance->TextBlock_Nr_bloku_liczba) {
		FText tmp = FText::AsNumber(nr_bloku);
		MyWidgetInstance->TextBlock_Nr_bloku_liczba->SetText(tmp);
	}
}

/*	Metoda odpowiedzialna zaktualizowanie pokazywanie na widget czy jest pauza
*/

void AKontroler::UpdatePauza() {
	if (MyWidgetInstance && MyWidgetInstance->TextBlock_Informacja) {
		if (czyPauza) {
			FText tmp = FText::FromString("Pauza");
			MyWidgetInstance->TextBlock_Informacja->SetText(tmp);
		}
		else {
			FText tmp = FText::FromString(""); //Nie ma pauzy
			MyWidgetInstance->TextBlock_Informacja->SetText(tmp);
		}
	}
}

/*	Metoda odpowiedzialna zaktualizowanie pokazywanie na widget, ze jest koniec gry
*/

void AKontroler::UpdateKoniecGry() {
	if (MyWidgetInstance && MyWidgetInstance->TextBlock_Informacja) {
		FText tmp = FText::FromString("Koniec gry.");
		MyWidgetInstance->TextBlock_Informacja->SetText(tmp);
	}
}

/*	Metoda odpowiedzialna wyczyszczenie widget informacja
*/

void AKontroler::WyczyscInformacja() {
	if (MyWidgetInstance && MyWidgetInstance->TextBlock_Informacja) {
		FText tmp = FText::FromString("");
		MyWidgetInstance->TextBlock_Informacja->SetText(tmp);
	}
}

/*	Metoda odpowiedzialna za ustawienie na widget-cie ile punktow nalezy zdobyc
*/

void AKontroler::ustaw_do_zdobycia() {
	if (MyWidgetInstance && MyWidgetInstance->TextBlock_Informacja) {
		FText tmp = FText::FromString("Do zdobycia: 2000");
		MyWidgetInstance->TextBlock_Informacja->SetText(tmp);
	}
}

// Called every frame
void AKontroler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MenuInstance->TablicaInstance->czy_powrot) {
		MenuInstance->TablicaInstance->czy_powrot = false;
		MenuInstance->SetVisibility(ESlateVisibility::Visible);
	}

	if (czyPauza) {
		return;
	}
	else if (stadium_gry == 2) {
		//2 - gra nie zaczeta
		if (MenuInstance->czy_wybrano) {
			//wczytaj_tablice();
			zestaw_blokow = MenuInstance->zestaw_blokow;
			rozmiar_planszy = MenuInstance->rozmiar_planszy;
			tryb_gry = MenuInstance->tryb_gry;
			czyszczenie_planszy();
			gra_rozpoczeta();
		}
	}
	else if (stadium_gry == 0) {
		//0 - blok nie wygenerowany
		if (nr_bloku % 10 == 9) {
			przyspieszanie_opadania();
		}
		UE_LOG(LogTemp, Warning, TEXT("generowanie bloku"));
		tryb_przetrwania();
		generowanie_bloku();
		stadium_gry = 1;
		/*if (MyWidgetInstance && MyWidgetInstance->TextBlock_Punkty_liczba) {
			MyWidgetInstance->TextBlock_Punkty_liczba->SetText(FText::FromString("Podstawowe informacje"));
		}*/

		//stadium_gry = 1;
		//sprawdzanie czy blok zmiescil sie na planszy
		int8 suma_kontrolna = 0;
		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			if (wsp_akt_bloku[i][1] > 0) { //sprawdza czy nie jest na samym dole
				if (szesciany_na_planszy[wsp_akt_bloku[i][0]][wsp_akt_bloku[i][1]] == nullptr) { //sprawdza czy pole pod szescianem nie jest zajete
					suma_kontrolna++;
				}
			}
		}
		if (suma_kontrolna != ile_szescianow_bloku) {
			stadium_gry = 3;
			for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
				szesciany_blok[i]->Destroy(); //usuwanie obiektu dziedziczacego po AActor
				szesciany_blok[i] = nullptr;
			}
			szesciany_blok.Empty();
			usun_cien();
		}
	}
	else if (stadium_gry == 1) {
		//1 - blok wygenerowany i opada
		czyszczenie_linii();
		tryb_ograniczonych_blokow();
		//skasuj_linie(1);
		//stadium_gry = 3;
	}
	if (stadium_gry == 3) {
		//3 - koniec gry
		UE_LOG(LogTemp, Warning, TEXT("KONIEC GRY"));
		UpdateKoniecGry();
		stadium_gry = 2;
		GetWorld()->GetTimerManager().ClearTimer(OpadanieTimer);
		//wyczysc_do_zdobycia();
		//MenuInstance->AddToViewport();
		MenuInstance->pokaz_menu();
		wczytaj_zapisz_tablice();
		//czyszczenie_planszy();
	}

}

void AKontroler::gra_rozpoczeta() {
	UE_LOG(LogTemp, Warning, TEXT("Rozpoczecie rozgrywki"));
	GetWorld()->GetTimerManager().SetTimer(OpadanieTimer, this, &AKontroler::opadanie, opadanie_przerwa, true);

	stadium_gry = 0;
}

/*	Metoda generujaca nowy blok
*/

void AKontroler::generowanie_bloku() {
	switch (zestaw_blokow) {
	case 0:
		generowanie_bloku_standardowego();
		break;
	case 1:
		generowanie_bloku_duzego();
		break;
	case 2:
		generowanie_bloku_losowego();
		break;
	}
}

/*	Metoda odpowiedzialna za opadanie bloku
*/

void AKontroler::opadanie() {
	if (czyPrzesuwane)
		return;
	if (czyPauza)
		return;
	if (stadium_gry == 3 || stadium_gry == 4)
		return;
	czyPrzesuwane = true;
	int8 suma_kontrolna = 0; //jesli rowne ilosci szescianow bloku to oznacza, ze kazdy szescian bloku moze sie poruszyc sie w dol
	for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
		if (wsp_akt_bloku[i][1] > 0) { //sprawdza czy nie jest na samym dole
			if (szesciany_na_planszy[wsp_akt_bloku[i][0]][wsp_akt_bloku[i][1] - 1] == nullptr) { //sprawdza czy pole pod szescianem nie jest zajete
				++suma_kontrolna;
			}
		}
	}
	//sprawdzanie czy blok zmiescil sie na planszy
	if (suma_kontrolna == ile_szescianow_bloku) {
		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(0, 0, -100)); //opadanie
			wsp_akt_bloku[i][1] = wsp_akt_bloku[i][1] - 1;
		}
		wsp_srodka_akt[1] = wsp_srodka_akt[1] - 1;
	}
	else {
		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			szesciany_na_planszy[wsp_akt_bloku[i][0]][wsp_akt_bloku[i][1]] = szesciany_blok[i];
		}
		szesciany_blok.Empty();
		stadium_gry = 0;
		usun_cien();
	}
	czyPrzesuwane = false;
}

/*	Metoda odpowiedzialna za ruch bloku w prawo
*/

void AKontroler::ruch_w_prawo() {
	if (czyPrzesuwane)
		return;
	if (czyPauza)
		return;
	if (stadium_gry == 3 || stadium_gry == 4)
		return;
	czyPrzesuwane = true;
	int8 suma_kontrolna = 0;
	for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
		if (wsp_akt_bloku[i][0] < szerokosc_planszy - 1) { //sprawdza czy nie jest przy prawej krawêdzi
			if (szesciany_na_planszy[wsp_akt_bloku[i][0] + 1][wsp_akt_bloku[i][1]] == nullptr) { //sprawdza czy pole na prawo od szescianu nie jest zajete
				++suma_kontrolna;
			}
		}
	}
	if (suma_kontrolna == ile_szescianow_bloku) {
		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(100, 0, 0)); //ruch w prawo
			wsp_akt_bloku[i][0] = wsp_akt_bloku[i][0] + 1;
		}
		wsp_srodka_akt[0] = wsp_srodka_akt[0] + 1;
	}
	czyPrzesuwane = false;
	miejsce_opadania();
}

/*	Metoda odpowiedzialna za ruch bloku w lewo
*/

void AKontroler::ruch_w_lewo() {
	if (czyPrzesuwane) {
		return;
	}
	if (czyPauza) {
		return;
	}
	if (stadium_gry == 3 || stadium_gry == 4)
		return;
	czyPrzesuwane = true;
	int8 suma_kontrolna = 0;
	for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
		if (wsp_akt_bloku[i][0] > 0) { //sprawdza czy nie jest przy lewej krawedzi
			if (szesciany_na_planszy[wsp_akt_bloku[i][0] - 1][wsp_akt_bloku[i][1]] == nullptr) { //sprawdza czy pole na prawo od szescianu nie jest zajete
				++suma_kontrolna;
			}
		}
	}
	if (suma_kontrolna == ile_szescianow_bloku) {
		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			szesciany_blok[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation() + FVector(-100, 0, 0)); //ruch w lewo
			wsp_akt_bloku[i][0] = wsp_akt_bloku[i][0] - 1;
		}
		wsp_srodka_akt[0] = wsp_srodka_akt[0] - 1;
	}
	czyPrzesuwane = false;
	miejsce_opadania();
}

/*	Metoda odpowiedzialna za obracanie bloku
*/

void AKontroler::obrot() {
	if (czyPrzesuwane)
		return;
	if (czyPauza)
		return;
	if (stadium_gry == 3 || stadium_gry == 4)
		return;
	czyPrzesuwane = true;
	if (blok == 'O') {
		czyPrzesuwane = false;
		miejsce_opadania();
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
			int8 suma_kontrolna = 0;
			for (int i = 0; i < 4; ++i) {
				if (wsp_akt_bloku[i][0] < 10 && wsp_akt_bloku[i][0] >= 0 && wsp_akt_bloku[i][1] >= 0 && wsp_akt_bloku[i][1] < 20) {
					//UE_LOG(LogTemp, Warning, TEXT("Sprawdzone czy sie miesci na planszy"));
					if (szesciany_na_planszy[wsp_akt_bloku[i][0]][wsp_akt_bloku[i][1]] == nullptr)
						suma_kontrolna++;
				}
			}
			if (suma_kontrolna == 4)
				break;

		}
		czyPrzesuwane = false;
		miejsce_opadania();
		return;
	}
	//kazdy inny blok mieszczacy sie w wymiarach 3x3
	for (int8 k = 0; k < 4; ++k) { //cztery rotacje
		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
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
		for (int i = 0; i < ile_szescianow_bloku; ++i) {
			if (wsp_akt_bloku[i][0] < 10 && wsp_akt_bloku[i][0] >= 0 && wsp_akt_bloku[i][1] >= 0 && wsp_akt_bloku[i][1] < 20)
				if (szesciany_na_planszy[wsp_akt_bloku[i][0]][wsp_akt_bloku[i][1]] == nullptr)
					suma_kontrolna++;
		}
		if (suma_kontrolna == ile_szescianow_bloku) {
			UE_LOG(LogTemp, Warning, TEXT("Suma_kontrolna."));
			break;
		}
	}

	czyPrzesuwane = false;
	miejsce_opadania();
}

/*	Metoda odpowiedzialna za czyszczenie linii
*/

void AKontroler::czyszczenie_linii() {
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
		if (suma_kontrolna == szerokosc_planszy) {
			//czyszczenie linii
			for (int8 j = 0; j < szerokosc_planszy; ++j) {
				szesciany_na_planszy[j][i]->Destroy();
				szesciany_na_planszy[j][i] = nullptr;
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
	punkty += ile_linii * silnia(ile_linii) * 100;
	UpdatePunkty();
	miejsce_opadania();
	czyPrzesuwane = false;
}

/*	Metoda odpowiedzialna za sterowanie wlaczeniem pauzy
*/

void AKontroler::pauza() {
	if (stadium_gry == 4)
		return;
	if (czyPauza) {
		if (czy_podpowiedz) {
			czy_podpowiedz = false;
			usun_podpowiedz();
		}
		czyPauza = false;
	}
	else {
		czyPauza = true;
	}
	UpdatePauza();
}

/*	Metoda odpowiedzialna za zamianê bloku na inny
*/

void AKontroler::zamiana_bloku() {
	nr_bloku--;
	if (punkty - 100 < 0) {
		return;
	}
	for (int i = 0; i < ile_szescianow_bloku; ++i) {
		if (szesciany_blok[i] != nullptr) {
			szesciany_blok[i]->Destroy();
		}
	}
	szesciany_blok.Empty();
	stadium_gry = 0;
	//generowanie_bloku();
	punkty -= 100;
	UpdatePunkty();
}

/*	Metoda odpowiedzialna za wyczyszczenie planszy z blokow.
*/

void AKontroler::czyszczenie_planszy() {
	for (int8 i = 0; i < szerokosc_planszy; ++i) {
		for (int8 j = 0; j < wysokosc_planszy; ++j) {
			if (szesciany_na_planszy[i][j] != nullptr) {
				szesciany_na_planszy[i][j]->Destroy();
				szesciany_na_planszy[i][j] = nullptr;
			}
		}
	}
	punkty = 0;
	nr_bloku = 0;
	WyczyscInformacja();
}

void AKontroler::przyspieszanie_opadania() {
	if (opadanie_przerwa > 0.25f) {
		opadanie_przerwa -= 0.05f;
		log_float(opadanie_przerwa);
		GetWorld()->GetTimerManager().ClearTimer(OpadanieTimer);
		GetWorld()->GetTimerManager().SetTimer(OpadanieTimer, this, &AKontroler::opadanie, opadanie_przerwa, true);
	}
}

void AKontroler::miejsce_opadania() {
	if (stadium_gry == 3)
		return;
	przenoszenie_cienia();
	int8 suma_kontrolna = 0; //jesli rowne 4 to oznacza, ze kazdy szescian bloku moze sie poruszyc sie w dol
	do {
		suma_kontrolna = 0;
		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			if (wsp_cien[i][1] > 0) { //sprawdza czy nie jest na samym dole
				if (szesciany_na_planszy[wsp_cien[i][0]][wsp_cien[i][1] - 1] == nullptr) { //sprawdza czy pole pod szescianem nie jest zajete
					++suma_kontrolna;
				}
			}
		}
		if (suma_kontrolna == ile_szescianow_bloku) {
			for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
				szesciany_cien[i]->SetActorLocation(szesciany_cien[i]->GetActorLocation() + FVector(0, 0, -100)); //opadanie
				wsp_cien[i][1] = wsp_cien[i][1] - 1;
			}
		}
	} while (suma_kontrolna == ile_szescianow_bloku);
}

void AKontroler::przenoszenie_cienia() {
	for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
		for (int8 j = 0; j < 2; ++j) {
			wsp_cien[i][j] = wsp_akt_bloku[i][j];
		}
		szesciany_cien[i]->SetActorLocation(szesciany_blok[i]->GetActorLocation());
	}
}

void AKontroler::usun_cien() {
	for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
		szesciany_cien[i]->Destroy();
	}
	szesciany_cien.Empty();
}

void AKontroler::generowanie_bloku_standardowego() {
	if (stadium_gry == 3)
		return;
	nr_bloku++;
	UpdateNrBloku();

	int8 los = FMath::RandRange(0, 6);
	/*UE_LOG(LogTemp, Warning, TEXT("Wylosowano liczbe"));*/
	wsp_srodka_akt[0] = 5;
	wsp_srodka_akt[1] = 18;

	ile_szescianow_bloku = 4;
	for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
		szesciany_cien.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_cien, Wsp_Startu, Rotacja_Standardowa));
	}

	switch (los) {
	case 0:
		//L
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_L, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[0] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[3] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[6] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);

		wsp_akt_bloku[0][0] = 4; wsp_akt_bloku[0][1] = 19;
		wsp_akt_bloku[1][0] = 4; wsp_akt_bloku[1][1] = 18;
		wsp_akt_bloku[2][0] = 4; wsp_akt_bloku[2][1] = 17;
		wsp_akt_bloku[3][0] = 5; wsp_akt_bloku[3][1] = 17;
		blok = 'L';
		break;
	case 1:
		//J
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_J, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[1] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[4] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[6] + wsp_poczatku);

		wsp_akt_bloku[0][0] = 5; wsp_akt_bloku[0][1] = 19;
		wsp_akt_bloku[1][0] = 5; wsp_akt_bloku[1][1] = 18;
		wsp_akt_bloku[2][0] = 5; wsp_akt_bloku[2][1] = 17;
		wsp_akt_bloku[3][0] = 4; wsp_akt_bloku[3][1] = 17;
		blok = 'J';
		break;
	case 2:
		//S
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_S, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[6] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[4] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[5] + wsp_poczatku);

		wsp_akt_bloku[0][0] = 4; wsp_akt_bloku[0][1] = 17;
		wsp_akt_bloku[1][0] = 5; wsp_akt_bloku[1][1] = 17;
		wsp_akt_bloku[2][0] = 5; wsp_akt_bloku[2][1] = 18;
		wsp_akt_bloku[3][0] = 6; wsp_akt_bloku[3][1] = 18;
		blok = 'S';
		break;
	case 3:
		//Z
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_Z, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[3] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[4] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[8] + wsp_poczatku);

		wsp_akt_bloku[0][0] = 4; wsp_akt_bloku[0][1] = 18;
		wsp_akt_bloku[1][0] = 5; wsp_akt_bloku[1][1] = 18;
		wsp_akt_bloku[2][0] = 5; wsp_akt_bloku[2][1] = 17;
		wsp_akt_bloku[3][0] = 6; wsp_akt_bloku[3][1] = 17;
		blok = 'Z';
		break;
	case 4:
		//T
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_T, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[3] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[4] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[5] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);

		wsp_akt_bloku[0][0] = 4; wsp_akt_bloku[0][1] = 18;
		wsp_akt_bloku[1][0] = 5; wsp_akt_bloku[1][1] = 18;
		wsp_akt_bloku[2][0] = 6; wsp_akt_bloku[2][1] = 18;
		wsp_akt_bloku[3][0] = 5; wsp_akt_bloku[3][1] = 17;
		blok = 'T';
		break;
	case 5:
		//O
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_O, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[3] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[4] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[6] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);

		wsp_akt_bloku[0][0] = 4; wsp_akt_bloku[0][1] = 18;
		wsp_akt_bloku[1][0] = 5; wsp_akt_bloku[1][1] = 18;
		wsp_akt_bloku[2][0] = 4; wsp_akt_bloku[2][1] = 17;
		wsp_akt_bloku[3][0] = 5; wsp_akt_bloku[3][1] = 17;
		blok = 'O';
		break;
	case 6:
		//I
		for (int8 i = 0; i < 4; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_I, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[6] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[8] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[10] + wsp_poczatku); // pozycja lezaca

		wsp_akt_bloku[0][0] = 4; wsp_akt_bloku[0][1] = 17;
		wsp_akt_bloku[1][0] = 5; wsp_akt_bloku[1][1] = 17;
		wsp_akt_bloku[2][0] = 6; wsp_akt_bloku[2][1] = 17;
		wsp_akt_bloku[3][0] = 7; wsp_akt_bloku[3][1] = 17;

		blok = 'I';
		break;
	}
	rotacja = 0;
	stadium_gry = 1;
	miejsce_opadania();
}

/*	Metoda generujaca nowy generowany losowo blok
*/

void AKontroler::generowanie_bloku_losowego() {
	if (stadium_gry == 3)
		return;
	nr_bloku++;
	UpdateNrBloku();

	//int8 los = FMath::RandRange(0, 6);
	/*UE_LOG(LogTemp, Warning, TEXT("Wylosowano liczbe"));*/
	wsp_srodka_akt[0] = wsp_srodka_spawn[0];
	wsp_srodka_akt[1] = wsp_srodka_spawn[1];

	ile_szescianow_bloku = 0;
	blok = 'R';

	int8 los_kolor = FMath::RandRange(0, 6);
	do {
		for (int8 i = 0; i < 3; ++i) {
			for (int8 j = 0; j < 3; ++j) {
				int8 los = FMath::RandRange(0, 1);
				// 0, 1 - generuje dla 0 i 1
				if (los == 0) {
					++ile_szescianow_bloku;
					if (los_kolor == 0)
						szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_I, Wsp_Startu, Rotacja_Standardowa));
					else if (los_kolor == 1)
						szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_J, Wsp_Startu, Rotacja_Standardowa));
					else if (los_kolor == 2)
						szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_L, Wsp_Startu, Rotacja_Standardowa));
					else if (los_kolor == 3)
						szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_S, Wsp_Startu, Rotacja_Standardowa));
					else if (los_kolor == 4)
						szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_T, Wsp_Startu, Rotacja_Standardowa));
					else if (los_kolor == 5)
						szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_Z, Wsp_Startu, Rotacja_Standardowa));
					else if (los_kolor == 6)
						szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_O, Wsp_Startu, Rotacja_Standardowa));
					else if (los_kolor == 7)
						szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_blekitny, Wsp_Startu, Rotacja_Standardowa));
					//szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(bloki[los_kolor], Wsp_Startu, Rotacja_Standardowa));
					szesciany_blok[ile_szescianow_bloku - 1]->SetActorLocation(Wsp_Startu + poruszanie[i * 3 + j] + wsp_poczatku);
					wsp_akt_bloku[ile_szescianow_bloku - 1][0] = wsp_srodka_spawn[0] - 1 + j;
					wsp_akt_bloku[ile_szescianow_bloku - 1][1] = wsp_srodka_spawn[1] + 1 - i;

					szesciany_cien.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_cien, Wsp_Startu, Rotacja_Standardowa));
					szesciany_cien[ile_szescianow_bloku - 1]->SetActorLocation(szesciany_blok[ile_szescianow_bloku - 1]->GetActorLocation());
					log_liczba(ile_szescianow_bloku - 1);
					wsp_cien[ile_szescianow_bloku - 1][0] = wsp_akt_bloku[ile_szescianow_bloku - 1][0];
					wsp_cien[ile_szescianow_bloku - 1][1] = wsp_akt_bloku[ile_szescianow_bloku - 1][1];
				}
			}
		}
	} while (ile_szescianow_bloku == 0);
	rotacja = 0;
	stadium_gry = 1;
	miejsce_opadania();
}

/*	Metoda generujaca blok z puli duzych blokow
*/

void AKontroler::generowanie_bloku_duzego() {
	if (stadium_gry == 3)
		return;
	nr_bloku++;
	UpdateNrBloku();

	int8 los = FMath::RandRange(0, 7);
	/*UE_LOG(LogTemp, Warning, TEXT("Wylosowano liczbe"));*/
	wsp_srodka_akt[0] = wsp_srodka_spawn[0];
	wsp_srodka_akt[1] = wsp_srodka_spawn[1];

	switch (los) {
	case 0:
		//o
		//XXX
		//XXX
		//XXX
		ile_szescianow_bloku = 9;

		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_O, Wsp_Startu, Rotacja_Standardowa));
			szesciany_blok[i]->SetActorLocation(Wsp_Startu + poruszanie[i] + wsp_poczatku);
		}

		wsp_akt_bloku[0][0] = wsp_srodka_spawn[0] - 1; wsp_akt_bloku[0][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[1][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[1][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[2][0] = wsp_srodka_spawn[0] + 1; wsp_akt_bloku[2][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[3][0] = wsp_srodka_spawn[0] - 1; wsp_akt_bloku[3][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[4][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[4][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[5][0] = wsp_srodka_spawn[0] + 1; wsp_akt_bloku[5][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[6][0] = wsp_srodka_spawn[0] - 1; wsp_akt_bloku[6][1] = wsp_srodka_spawn[1] - 1;
		wsp_akt_bloku[7][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[7][1] = wsp_srodka_spawn[1] - 1;
		wsp_akt_bloku[8][0] = wsp_srodka_spawn[0] + 1; wsp_akt_bloku[8][1] = wsp_srodka_spawn[1] - 1;

		/*for (int8 i = 0; i < 3; ++i) {
			for (int8 j = 0; j < 3; ++j) {
				wsp_akt_bloku[i * 3 + j][0] = wsp_srodka_spawn[0] - 1 + i;
				wsp_akt_bloku[i * 3 + j][1] = wsp_srodka_spawn[1] - 1 + j;
			}
		}*/
		blok = 'o';
		break;
	case 1:
		//+
		// X
		//XXX
		// X
		ile_szescianow_bloku = 5;

		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_J, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[1] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[3] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[4] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[5] + wsp_poczatku);
		szesciany_blok[4]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);

		wsp_akt_bloku[0][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[0][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[1][0] = wsp_srodka_spawn[0] - 1; wsp_akt_bloku[1][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[2][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[2][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[3][0] = wsp_srodka_spawn[0] + 1; wsp_akt_bloku[3][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[4][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[4][1] = wsp_srodka_spawn[1] - 1;
		blok = 'J';
		break;
	case 2:
		//t
		//XXX
		// X
		// X
		ile_szescianow_bloku = 5;

		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_T, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[0] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[1] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[2] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[4] + wsp_poczatku);
		szesciany_blok[4]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);

		wsp_akt_bloku[0][0] = wsp_srodka_spawn[0] - 1; wsp_akt_bloku[0][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[1][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[1][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[2][0] = wsp_srodka_spawn[0] + 1; wsp_akt_bloku[2][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[3][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[3][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[4][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[4][1] = wsp_srodka_spawn[1] - 1;
		blok = 't';
		break;
	case 3:
		//l
		//X
		//X
		//XXX
		ile_szescianow_bloku = 5;

		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_L, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[0] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[3] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[6] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);
		szesciany_blok[4]->SetActorLocation(Wsp_Startu + poruszanie[8] + wsp_poczatku);

		wsp_akt_bloku[0][0] = wsp_srodka_spawn[0] - 1; wsp_akt_bloku[0][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[1][0] = wsp_srodka_spawn[0] - 1; wsp_akt_bloku[1][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[2][0] = wsp_srodka_spawn[0] - 1; wsp_akt_bloku[2][1] = wsp_srodka_spawn[1] - 1;
		wsp_akt_bloku[3][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[3][1] = wsp_srodka_spawn[1] - 1;
		wsp_akt_bloku[4][0] = wsp_srodka_spawn[0] + 1; wsp_akt_bloku[4][1] = wsp_srodka_spawn[1] - 1;
		blok = 'l';
		break;
	case 4:
		//U
		//
		//X X
		//XXX
		ile_szescianow_bloku = 5;

		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_blekitny, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[3] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[5] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[6] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);
		szesciany_blok[4]->SetActorLocation(Wsp_Startu + poruszanie[8] + wsp_poczatku);

		wsp_akt_bloku[0][0] = wsp_srodka_spawn[0] - 1; wsp_akt_bloku[0][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[1][0] = wsp_srodka_spawn[0] + 1; wsp_akt_bloku[1][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[2][0] = wsp_srodka_spawn[0] - 1; wsp_akt_bloku[2][1] = wsp_srodka_spawn[1] - 1;
		wsp_akt_bloku[3][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[3][1] = wsp_srodka_spawn[1] - 1;
		wsp_akt_bloku[4][0] = wsp_srodka_spawn[0] + 1; wsp_akt_bloku[4][1] = wsp_srodka_spawn[1] - 1;
		blok = 'U';
		break;
	case 5:
		//i
		// X
		// X
		// X
		ile_szescianow_bloku = 3;

		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_I, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[1] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[4] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);

		wsp_akt_bloku[0][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[0][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[1][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[1][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[2][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[2][1] = wsp_srodka_spawn[1] - 1;
		blok = 'i';
		break;
	case 6:
		//z
		//XX
		// X
		// XX
		ile_szescianow_bloku = 5;

		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_Z, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[0] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[1] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[4] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);
		szesciany_blok[4]->SetActorLocation(Wsp_Startu + poruszanie[8] + wsp_poczatku);

		wsp_akt_bloku[0][0] = wsp_srodka_spawn[0] - 1; wsp_akt_bloku[0][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[1][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[1][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[2][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[2][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[3][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[3][1] = wsp_srodka_spawn[1] - 1;
		wsp_akt_bloku[4][0] = wsp_srodka_spawn[0] + 1; wsp_akt_bloku[4][1] = wsp_srodka_spawn[1] - 1;
		blok = 'Z';
		break;
	case 7:
		//s
		// XX
		// X
		//XX
		ile_szescianow_bloku = 5;

		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			szesciany_blok.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_S, Wsp_Startu, Rotacja_Standardowa));
		}
		szesciany_blok[0]->SetActorLocation(Wsp_Startu + poruszanie[1] + wsp_poczatku);
		szesciany_blok[1]->SetActorLocation(Wsp_Startu + poruszanie[2] + wsp_poczatku);
		szesciany_blok[2]->SetActorLocation(Wsp_Startu + poruszanie[4] + wsp_poczatku);
		szesciany_blok[3]->SetActorLocation(Wsp_Startu + poruszanie[6] + wsp_poczatku);
		szesciany_blok[4]->SetActorLocation(Wsp_Startu + poruszanie[7] + wsp_poczatku);

		wsp_akt_bloku[0][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[0][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[1][0] = wsp_srodka_spawn[0] + 1; wsp_akt_bloku[1][1] = wsp_srodka_spawn[1] + 1;
		wsp_akt_bloku[2][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[2][1] = wsp_srodka_spawn[1];
		wsp_akt_bloku[3][0] = wsp_srodka_spawn[0] - 1; wsp_akt_bloku[3][1] = wsp_srodka_spawn[1] - 1;
		wsp_akt_bloku[4][0] = wsp_srodka_spawn[0]; wsp_akt_bloku[4][1] = wsp_srodka_spawn[1] - 1;

		blok = 's';
		break;
	}

	for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
		szesciany_cien.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_cien, Wsp_Startu, Rotacja_Standardowa));
	}

	rotacja = 0;
	stadium_gry = 1;
	miejsce_opadania();
}

void AKontroler::znacznik_w_gore() {
	if (wsp_znacznik + 1 >= wysokosc_planszy)
		return;
	Znacznik[0]->SetActorLocation(Znacznik[0]->GetActorLocation() + FVector(0, 0, 100));
	wsp_znacznik += 1;
}

void AKontroler::znacznik_w_dol() {
	if (wsp_znacznik - 1 < 0)
		return;
	Znacznik[0]->SetActorLocation(Znacznik[0]->GetActorLocation() + FVector(0, 0, -100));
	wsp_znacznik -= 1;
}

void AKontroler::kasowanie_zatwierdzenie() {
	//czyZatwierdzonoKasowanie = true;
	Znacznik[0]->Destroy();
	Znacznik.Empty();

	InputComponent->KeyBindings.RemoveAll([&](const FInputKeyBinding& Binding)
		{
			return Binding.KeyEvent == IE_Pressed && Binding.Chord.Key == EKeys::W;
		});
	InputComponent->KeyBindings.RemoveAll([&](const FInputKeyBinding& Binding)
		{
			return Binding.KeyEvent == IE_Pressed && Binding.Chord.Key == EKeys::S;
		});
	InputComponent->KeyBindings.RemoveAll([&](const FInputKeyBinding& Binding)
		{
			return Binding.KeyEvent == IE_Pressed && Binding.Chord.Key == EKeys::Enter;
		});
	skasuj_linie(wsp_znacznik);
	czyKasowanie = false;
}

void AKontroler::interfejs_kasowania_linii() {
	if (czyKasowanie)
		return;
	if (!czyPauza)
		return;
	if (stadium_gry == 3)
		return;
	czyKasowanie = true;
	Znacznik.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_cien, Wsp_Startu, Rotacja_Standardowa));
	Znacznik[0]->SetActorLocation(Wsp_Startu + FVector(-100, 100, 0));
	wsp_znacznik = 0;
	//czyZatwierdzonoKasowanie = false;
	InputComponent->BindKey(EKeys::W, IE_Pressed, this, &AKontroler::znacznik_w_gore); //poruszenie w gore
	InputComponent->BindKey(EKeys::S, IE_Pressed, this, &AKontroler::znacznik_w_dol); //poruszenie w dol
	InputComponent->BindKey(EKeys::Enter, IE_Pressed, this, &AKontroler::kasowanie_zatwierdzenie); //zatwierdzenie
}

void AKontroler::skasuj_linie(int8 nr) {
	if (punkty - 100 < 0)
		return;
	if (czyPrzesuwane)
		return;
	if (nr > wysokosc_planszy || nr < 0)
		return;
	UE_LOG(LogTemp, Warning, TEXT("Skasuj linie"));
	czyPrzesuwane = true;
	int8 suma_kontrolna = 0; //jesli rowne szerokosc to wtedy znaczy, ze wszystkie pola puste
	for (int8 j = 0; j < szerokosc_planszy; ++j) {
		if (szesciany_na_planszy[j][nr] == nullptr) {
			suma_kontrolna++;
		}
	}
	if (suma_kontrolna < szerokosc_planszy) {
		//czyszczenie linii
		for (int8 j = 0; j < szerokosc_planszy; ++j) {
			if (szesciany_na_planszy[j][nr] != nullptr) {
				szesciany_na_planszy[j][nr]->Destroy();
				szesciany_na_planszy[j][nr] = nullptr;
			}
		}

		//przesuwanie blokow powyzej w dol
		for (int8 j = nr + 1; j < wysokosc_planszy; ++j) {
			for (int8 k = 0; k < szerokosc_planszy; ++k) {
				if (szesciany_na_planszy[k][j] != nullptr) {
					szesciany_na_planszy[k][j - 1] = szesciany_na_planszy[k][j];
					szesciany_na_planszy[k][j] = nullptr;
					szesciany_na_planszy[k][j - 1]->SetActorLocation(szesciany_na_planszy[k][j - 1]->GetActorLocation() + FVector(0, 0, -100));
				}
			}
		}
		miejsce_opadania();
		punkty -= 100;
		UpdatePunkty();
	}
	czyPrzesuwane = false;
}

void AKontroler::tryb_ograniczonych_blokow() {
	if (tryb_gry != 1)
		return;
	if (czyPauza)
		return;
	ustaw_do_zdobycia();
	if (nr_bloku > limit_blokow) {
		stadium_gry = 3;
	}
	else if (punkty > oczekiwane_punkty) {
		stadium_gry = 3;
	}
}

void AKontroler::tryb_przetrwania() {
	if (tryb_gry != 2)
		return;
	if (nr_bloku % 10 != 9)
		return;
	if (czyPrzesuwane)
		return;
	czyPrzesuwane = true;
	//sprawdzanie czy gorna linia nie jest czesciowo zapelniona
	int8 suma_kontrolna = 0;
	for (int8 j = 0; j < szerokosc_planszy; ++j) {
		if (szesciany_na_planszy[j][wysokosc_planszy - 1] != nullptr) {
			stadium_gry = 3;
			return;
		}
	}

	for (int i = wysokosc_planszy - 2; i >= 0; --i) {
		for (int j = 0; j < szerokosc_planszy; ++j) {
			if (szesciany_na_planszy[j][i] != nullptr) {
				szesciany_na_planszy[j][i + 1] = szesciany_na_planszy[j][i];
				szesciany_na_planszy[j][i] = nullptr;
				szesciany_na_planszy[j][i + 1]->SetActorLocation(szesciany_na_planszy[j][i + 1]->GetActorLocation() + FVector(0, 0, 100));
			}
		}
	}

	TArray<ABlokAktor*> szescian_gen;
	suma_kontrolna = 0;
	for (int8 i = 0; i < szerokosc_planszy; ++i) {
		int8 los = FMath::RandRange(0, 4);
		if (los <= 2) {
			los = FMath::RandRange(0, 7);
			if (los == 0)
				szescian_gen.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_I, Wsp_Startu, Rotacja_Standardowa));
			else if (los == 1)
				szescian_gen.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_J, Wsp_Startu, Rotacja_Standardowa));
			else if (los == 2)
				szescian_gen.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_L, Wsp_Startu, Rotacja_Standardowa));
			else if (los == 3)
				szescian_gen.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_S, Wsp_Startu, Rotacja_Standardowa));
			else if (los == 4)
				szescian_gen.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_T, Wsp_Startu, Rotacja_Standardowa));
			else if (los == 5)
				szescian_gen.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_Z, Wsp_Startu, Rotacja_Standardowa));
			else if (los == 6)
				szescian_gen.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_O, Wsp_Startu, Rotacja_Standardowa));
			else if (los == 7)
				szescian_gen.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_blekitny, Wsp_Startu, Rotacja_Standardowa));
			szesciany_na_planszy[i][0] = szescian_gen[0];
			szescian_gen[0] = nullptr;
			szescian_gen.Empty();
			szesciany_na_planszy[i][0]->SetActorLocation(szesciany_na_planszy[i][0]->GetActorLocation() + FVector(100 * i, 0, 0));
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("koniec przesuwania do gory"));
	czyPrzesuwane = false;
}

void AKontroler::usun_podpowiedz() {
	for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
		szesciany_podp[i]->Destroy();
		szesciany_podp[i] = nullptr;
	}
	szesciany_podp.Empty();
}

void AKontroler::podpowiedz() {
	/*if (tryb_gry != 1)
		return;*/
	if (!czyPauza)
		return;

	wsp_podp.SetNum(ile_szescianow_bloku);
	for (int32 i = 0; i < ile_szescianow_bloku; ++i) {
		wsp_podp[i].SetNum(2);
	}
	wsp_srodka_podp.SetNum(2);

	wsp_srodka_podp[0] = wsp_srodka_akt[0];
	wsp_srodka_podp[1] = wsp_srodka_akt[1];
	for (int32 i = 0; i < ile_szescianow_bloku; ++i) {
		wsp_podp[i][0] = wsp_akt_bloku[i][0];
		wsp_podp[i][1] = wsp_akt_bloku[i][1];
	}
	//przesuwanie do lewej krawedzi planszy
	int8 suma_kontrolna = 0;
	do {
		suma_kontrolna = 0;
		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			if (wsp_podp[i][0] - 1 >= 0)
				if (szesciany_na_planszy[wsp_podp[i][0] - 1][wsp_podp[i][1]] == nullptr)
					++suma_kontrolna;
				else
					break;
			else
				break;
		}
		if (suma_kontrolna == ile_szescianow_bloku) {
			for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
				wsp_podp[i][0] -= 1;
			}
			wsp_srodka_podp[0] -= 1;
		}
	} while (suma_kontrolna == ile_szescianow_bloku);

	TArray<TArray<int32>> wsp_najlepsze;
	int8 ile_linii_najlepsze = -1;
	int32 ile_pustych_najlepsze = 100; //maksymalnie 40
	wsp_najlepsze.SetNum(ile_szescianow_bloku);
	for (int32 i = 0; i < ile_szescianow_bloku; ++i)
		wsp_najlepsze[i].SetNum(2);

	TArray<TArray<int32>> wsp_akt;
	wsp_akt.SetNum(ile_szescianow_bloku);
	for (int32 i = 0; i < ile_szescianow_bloku; ++i)
		wsp_akt[i].SetNum(2);

	int8 max_poz = 0;
	int8 min_poz = wysokosc_planszy;

	do {
		max_poz = 0;
		min_poz = wysokosc_planszy;
		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			wsp_akt[i][0] = wsp_podp[i][0];
			wsp_akt[i][1] = wsp_podp[i][1];
		}
		//opuszczanie bloku, obracanie i sprawdzanie oceny umiejscowienia bloku
		do {
			suma_kontrolna = 0;
			for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
				if (wsp_akt[i][1] - 1 >= 0 && szesciany_na_planszy[wsp_akt[i][0]][wsp_akt[i][1] - 1] == nullptr) {
					++suma_kontrolna;
				}
			}
			if (suma_kontrolna == ile_szescianow_bloku) {
				for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
					wsp_akt[i][1] -= 1;
				}
			}
		} while (suma_kontrolna == ile_szescianow_bloku);
		//sprawdzanie przedzialu wsp gdzie nalezy sprawdzac
		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			if (wsp_akt[i][1] > max_poz)
				max_poz = wsp_akt[i][1];
			if (wsp_akt[i][1] < min_poz)
				min_poz = wsp_akt[i][1];
		}

		//sprawdzanie ile linii zbije umiejscowienie
		int8 ile_linii = 0;
		for (int8 i = min_poz; i <= max_poz; ++i) {
			suma_kontrolna = 0;
			for (int8 j = 0; j < szerokosc_planszy; ++j) {
				if (szesciany_na_planszy[j][i] != nullptr)
					++suma_kontrolna;
				else {
					for (int8 k = 0; k < ile_szescianow_bloku; ++k) {
						if (wsp_akt[k][0] == j && wsp_akt[k][0] == i) {
							++suma_kontrolna;
							break;
						}
					}
				}
			}
			if (suma_kontrolna == ile_szescianow_bloku)
				++ile_linii;
		}
		UE_LOG(LogTemp, Warning, TEXT("Min i max poz:"));
		log_liczba(min_poz);
		log_liczba(max_poz);
		int32 ile_pustych = 0; //pola puste i zapelnione od gory
		int8 tmp = min_poz - 1;
		if (tmp < 0)
			tmp = 0;
		for (int8 i = tmp; i <= max_poz; ++i) {
			for (int8 j = 0; j < szerokosc_planszy; ++j) {
				if (szesciany_na_planszy[j][i] == nullptr)
					if (szesciany_na_planszy[j][i + 1] != nullptr)
						++ile_pustych;
					
			}
		}

		if (ile_linii > ile_linii_najlepsze) {
			for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
				wsp_najlepsze[i][0] = wsp_akt[i][0];
				wsp_najlepsze[i][1] = wsp_akt[i][1];
			}
			ile_linii_najlepsze = ile_linii;
		}
		else if (ile_linii == ile_linii_najlepsze && ile_pustych < ile_pustych_najlepsze) {
			for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
				wsp_najlepsze[i][0] = wsp_akt[i][0];
				wsp_najlepsze[i][1] = wsp_akt[i][1];
			}
			ile_linii_najlepsze = ile_linii;
		}

		//przesuwanie sprawdzania w prawo
		suma_kontrolna = 0;
		for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
			if (wsp_podp[i][0] + 1 < szerokosc_planszy)
				if (szesciany_na_planszy[wsp_podp[i][0] + 1][wsp_podp[i][1]] == nullptr)
					++suma_kontrolna;
				else
					break;
			else
				break;
		}
		if (suma_kontrolna == ile_szescianow_bloku) {
			for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
				wsp_podp[i][0] += 1;
			}
			wsp_srodka_podp[0] += 1;
		}

	} while (suma_kontrolna == ile_szescianow_bloku);

	//ustawianie bloku z podpowiedzia na planszy
	for (int8 i = 0; i < ile_szescianow_bloku; ++i) {
		szesciany_podp.Add(GetWorld()->SpawnActor<ABlokAktor>(Blok_Aktor_cien, Wsp_Startu, Rotacja_Standardowa));
		szesciany_podp[i]->SetActorLocation(szesciany_podp[i]->GetActorLocation() + FVector(100 * wsp_najlepsze[i][0], 0, 100 * wsp_najlepsze[i][1]));
		wsp_podp[i][0] = wsp_najlepsze[i][0];
		wsp_podp[i][1] = wsp_najlepsze[i][1];
		UE_LOG(LogTemp, Warning, TEXT("Wsporzedne najlepsze:"));
		log_liczba(wsp_najlepsze[i][0]);
		log_liczba(wsp_najlepsze[i][1]);
	}

	UE_LOG(LogTemp, Warning, TEXT("koniec podpowiedzi"));
	czy_podpowiedz = true;
}

void AKontroler::zapisz_tablice() {
	UTablicaRekordowSaveGame* SaveGameInstance = Cast<UTablicaRekordowSaveGame>(UGameplayStatics::CreateSaveGameObject(UTablicaRekordowSaveGame::StaticClass()));
	
	SaveGameInstance->punkty.Add(punkty);
	SaveGameInstance->tryb.Add(tryb_gry);
	SaveGameInstance->data_godzina.Add(FDateTime::Now());
	//SaveGameInstance->ile_linii += 1;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("TablicaSaveSlot"), 0);
	UE_LOG(LogTemp, Warning, TEXT("Koniec zapis w tablicy."));
}

void AKontroler::wczytaj_zapisz_tablice() {
	UTablicaRekordowSaveGame* LoadGameInstance = Cast<UTablicaRekordowSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("TablicaSaveSlot"), 0));

	if (LoadGameInstance) {
		LoadGameInstance->punkty.Add(punkty);
		LoadGameInstance->tryb.Add(tryb_gry);
		LoadGameInstance->data_godzina.Add(FDateTime::Now());
	}
	else {
		LoadGameInstance = Cast<UTablicaRekordowSaveGame>(UGameplayStatics::CreateSaveGameObject(UTablicaRekordowSaveGame::StaticClass()));
		LoadGameInstance->punkty.Add(punkty);
		LoadGameInstance->tryb.Add(tryb_gry);
		LoadGameInstance->data_godzina.Add(FDateTime::Now());
	}
	LoadGameInstance->wypisz();
	UGameplayStatics::SaveGameToSlot(LoadGameInstance, TEXT("TablicaSaveSlot"), 0);
	UE_LOG(LogTemp, Warning, TEXT("Koniec wczytaj i zapis w tablicy."));
}

void AKontroler::wczytaj_tablice() {
	UTablicaRekordowSaveGame* LoadGameInstance = Cast<UTablicaRekordowSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("TablicaSaveSlot"), 0));

	if (LoadGameInstance) {
		int32 PlayerScore = LoadGameInstance->punkty[0];
		int32 tryb_g = LoadGameInstance->tryb[0];
		FDateTime data = LoadGameInstance->data_godzina[0];
		UE_LOG(LogTemp, Warning, TEXT("Punkty: %d"), punkty);
		UE_LOG(LogTemp, Warning, TEXT("Tryb gry: %d"), tryb_g);
		UE_LOG(LogTemp, Warning, TEXT("Tryb gry: %s"), *data.ToString());
	}
}