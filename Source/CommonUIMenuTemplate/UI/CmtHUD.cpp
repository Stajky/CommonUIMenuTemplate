// 


#include "CmtHUD.h"

#include "Components/GameFrameworkComponentManager.h"
#include "Controller/PlayerOverlayController.h"
#include "Kismet/GameplayStatics.h"
#include "CommonUIExtensions.h"
#include "CommonUIMenuTemplate/CmtGameplayTags.h"
#include "ActivatableWidget/Widget/PlayerOverlay.h"
#include "../Player/CmtPlayerState.h"


// Sets default values
ACmtHUD::ACmtHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}


void ACmtHUD::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}


void ACmtHUD::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();
}


void ACmtHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);

	Super::EndPlay(EndPlayReason);
}


UPlayerOverlayController* ACmtHUD::GetPlayerOverlayWidgetController()
{
	if(!PlayerOverlayWidgetController)
	{
		if(APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
		{
			InitPlayerOverlayController(PC);
		}
	}
	return PlayerOverlayWidgetController;
}


void ACmtHUD::ShowPlayerOverlay()
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		if(ULocalPlayer* LocalPlayer = UCommonUIExtensions::GetLocalPlayerFromController(PC))
		{
			//Crate the widget and push it to CommonUI stack
			UCommonActivatableWidget* PlayerOverlay = UCommonUIExtensions::PushContentToLayer_ForPlayer(
				LocalPlayer, CmtTag::UI_Layer_Game, PlayerOverlayWidgetClass);

			//Save the new reference to HUD
			PlayerOverlayWidget = Cast<UPlayerOverlay>(PlayerOverlay);

			//If we succesfully created new widget and Its controller is not yeat inicialized init the controler
			if(PlayerOverlayWidget && !PlayerOverlayWidgetController)
			{
				InitPlayerOverlayController(PC);
			}

			//Set controller pointer to widget
			if(PlayerOverlayWidgetController)
			{
				PlayerOverlayWidget->SetController(PlayerOverlayWidgetController);
			}
		}
	}
}


void ACmtHUD::InitPlayerOverlayController(APlayerController* PC)
{
	ACmtPlayerState* PS = PC->GetPlayerState<ACmtPlayerState>();
	check(PS);
			
	PlayerOverlayWidgetController = NewObject<UPlayerOverlayController>(this, PlayerOverlayWidgetControllerClass);
	PlayerOverlayWidgetController->SetDataGeneratorsPointers(PS);
	PlayerOverlayWidgetController->BindDataGenerators();
}
