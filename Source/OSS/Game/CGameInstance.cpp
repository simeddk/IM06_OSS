#include "CGameInstance.h"
#include "Blueprint/UserWidget.h"

UCGameInstance::UCGameInstance()
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuClassAsset(TEXT("/Game/UI/WB_MainMenu"));
	if (MainMenuClassAsset.Succeeded())
	{
		MainMenuClass = MainMenuClassAsset.Class;
	}
}

void UCGameInstance::Init()
{
	Super::Init();

	
}

void UCGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!Engine) return;
	Engine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, "Host");

	UWorld* World = GetWorld();
	if (!World) return;
	World->ServerTravel("/Game/Maps/Coop?listen");
}

void UCGameInstance::Join(const FString& InAddress)
{
	UEngine* Engine = GetEngine();
	if (!Engine) return;
	Engine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Join to %s"), *InAddress));

	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC) return;
	PC->ClientTravel(InAddress, TRAVEL_Absolute);
}

void UCGameInstance::LoadMainMenu()
{
	if (!MainMenuClass) return;

	UUserWidget* MainMenu = CreateWidget<UUserWidget>(this, MainMenuClass);
	if (!MainMenu) return;

	MainMenu->AddToViewport();

	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC) return;

	MainMenu->bIsFocusable = true;

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(MainMenu->TakeWidget());
	PC->SetInputMode(InputMode);
	PC->bShowMouseCursor = true;
}
