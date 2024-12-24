#include "CPauseMenu.h"
#include "Components/Button.h"

bool UCPauseMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	if (!CancelButton) return false;
	CancelButton->OnClicked.AddDynamic(this, &UCPauseMenu::OnCancelPressed);

	if (!QuitButton) return false;
	QuitButton->OnClicked.AddDynamic(this, &UCPauseMenu::OnQuitPressed);

	return true;
}

void UCPauseMenu::OnCancelPressed()
{
	Shutdown();
}

void UCPauseMenu::OnQuitPressed()
{
	Shutdown();

	if (!OwningInstance) return;
	OwningInstance->OpenMainMenuLevel();
}
