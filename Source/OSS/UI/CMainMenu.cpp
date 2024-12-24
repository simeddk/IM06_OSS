#include "CMainMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UCMainMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	//Main Menu
	if (!HostButton) return false;
	HostButton->OnClicked.AddDynamic(this, &UCMainMenu::HostServer);

	if (!JoinButton) return false;
	JoinButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenJoinMenu);

	if (!QuitButton) return false;
	QuitButton->OnClicked.AddDynamic(this, &UCMainMenu::QuitGame);

	//Join Menu
	if (!CancelJoinButton) return false;
	CancelJoinButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenMainMenu);

	if (!ConfirmJoinButton) return false;
	ConfirmJoinButton->OnClicked.AddDynamic(this, &UCMainMenu::JoinServer);

	return true;
}

void UCMainMenu::HostServer()
{
	if (!OwningInstance) return;

	OwningInstance->Host();
}

void UCMainMenu::JoinServer()
{
	if (!OwningInstance) return;

	if (OwningInstance && IPAddressField)
	{
		const FString&  IPAddress = IPAddressField->GetText().IsEmpty() 
			? FString("127.0.0.1") 
			: IPAddressField->GetText().ToString();

		OwningInstance->Join(IPAddress);
	}
}

void UCMainMenu::OpenMainMenu()
{
	if (!MenuSwitcher) return;
	if (!MainMenu) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UCMainMenu::OpenJoinMenu()
{
	if (!MenuSwitcher) return;
	if (!JoinMenu) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UCMainMenu::QuitGame()
{
	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PC =  World->GetFirstPlayerController();
	if (!PC) return;

	UKismetSystemLibrary::QuitGame(World, PC, EQuitPreference::Quit, false);
}
