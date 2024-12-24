#include "CGameInstance.h"
#include "UI/CMainMenu.h"
#include "UI/CPauseMenu.h"

UCGameInstance::UCGameInstance()
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuClassAsset(TEXT("/Game/UI/WB_MainMenu"));
	if (MainMenuClassAsset.Succeeded())
	{
		MainMenuClass = MainMenuClassAsset.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuClassAsset(TEXT("/Game/UI/WB_PauseMenu"));
	if (PauseMenuClassAsset.Succeeded())
	{
		PauseMenuClass = PauseMenuClassAsset.Class;
	}
}

void UCGameInstance::Init()
{
	Super::Init();

	
}

void UCGameInstance::Host()
{
	if (MainMenu)
	{
		MainMenu->Shutdown();
	}

	UEngine* Engine = GetEngine();
	if (!Engine) return;
	Engine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, "Host");

	UWorld* World = GetWorld();
	if (!World) return;
	World->ServerTravel("/Game/Maps/Coop?listen");
}

void UCGameInstance::Join(const FString& InAddress)
{
	if (MainMenu)
	{
		MainMenu->Shutdown();
	}

	UEngine* Engine = GetEngine();
	if (!Engine) return;
	Engine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Join to %s"), *InAddress));

	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC) return;
	PC->ClientTravel(InAddress, TRAVEL_Absolute);
}

void UCGameInstance::OpenMainMenuLevel()
{
	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC) return;
	PC->ClientTravel("/Game/Maps/MainMenu", TRAVEL_Absolute);
}

void UCGameInstance::LoadMainMenu()
{
	if (!MainMenuClass) return;

	MainMenu = CreateWidget<UCMainMenu>(this, MainMenuClass);
	if (!MainMenu) return;

	MainMenu->SetOwningInstance(this);

	MainMenu->Startup();
}

void UCGameInstance::LoadPauseMenu()
{
	if (!PauseMenuClass) return;

	UCPauseMenu* PauseMenu = CreateWidget<UCPauseMenu>(this, PauseMenuClass);
	if (!PauseMenu) return;

	PauseMenu->SetOwningInstance(this);

	PauseMenu->Startup();
}
