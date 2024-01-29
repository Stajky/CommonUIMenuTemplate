// 


#include "PlayerOverlay.h"

#include "CommonUIMenuTemplate/UI/CmtHUD.h"
#include "CommonUIMenuTemplate/UI/Controller/PlayerOverlayController.h"
#include "Kismet/GameplayStatics.h"


void UPlayerOverlay::SetupWidgetController()
{
	//Here we setup the widget controller automatically OnActivated
	if(!bIsWidgetControllerSet)
	{
		if(const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if(ACmtHUD* HUD = Cast<ACmtHUD>(PC->GetHUD()))
			{
				WidgetController = HUD->GetPlayerOverlayWidgetController();
				bIsWidgetControllerSet = true;
			}
		}
	}
}
