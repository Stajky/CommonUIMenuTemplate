// 


#include "CheatWindow.h"

#include "CommonUIMenuTemplate/UI/CmtHUD.h"
#include "Kismet/GameplayStatics.h"
#include "CommonUIMenuTemplate/UI/Controller/CheatWidgetController.h"

void UCheatWindow::SetupWidgetController()
{
	//Here we setup the widget controller automatically OnActivated
	if(!bIsWidgetControllerSet)
	{
		if(const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if(ACmtHUD* HUD = Cast<ACmtHUD>(PC->GetHUD()))
			{
				WidgetController = HUD->GetCheatWidgetController();
				bIsWidgetControllerSet = true;
			}
		}
	}
}
