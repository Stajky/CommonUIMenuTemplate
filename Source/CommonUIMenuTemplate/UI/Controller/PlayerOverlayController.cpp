//

#include "PlayerOverlayController.h"
#include "CommonUIMenuTemplate/CmtGameplayTags.h"
#include "../../Player/CmtPlayerState.h"
#include "CommonUIMenuTemplate/CmtLibrary.h"


UPlayerOverlayController::UPlayerOverlayController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UPlayerOverlayController::BindData()
{
	if(!LockGuard())
		return;
	
	if(!PlayerState)
	{
		UE_LOG(LogTemp, Error, TEXT("Could Not Bind Data in Player Overlay Controller. PlayerState Pointer is Null"))
		return;
	}
	
	/* Bind to Player State Data */
	OnLevelChangedHandle = PlayerState->OnLevelChanged.AddLambda(
		[this](int32 NewLevel)
		{
			UCmtLibrary::SendIntMessage(this, CmtTag::UI_Message_Level, NewLevel);
		});

	OnXPChangedHandle = PlayerState->OnXPChanged.AddLambda(
		[this](int32 NewXPPercent)
		{
			UCmtLibrary::SendFloatMessage(this,CmtTag::UI_Message_XPPercent, NewXPPercent);
		});

	OnHealthChangedHandle = PlayerState->OnHealthChanged.AddLambda(
		[this](float NewHealthPercent)
		{
			UCmtLibrary::SendFloatMessage(this,CmtTag::UI_Message_HealthPercent, NewHealthPercent);
		});

	OnManaChangedHandle = PlayerState->OnManaChanged.AddLambda(
		[this](float NewManaPercent)
		{
			UCmtLibrary::SendFloatMessage(this,CmtTag::UI_Message_ManaPercent, NewManaPercent);
		});

}


void UPlayerOverlayController::UnBindData()
{
	//We dont want to unbind data if we already did
	if(!UnlockGuard())
		return;
	
	if (OnLevelChangedHandle.IsValid())
	{
		PlayerState->OnLevelChanged.Remove(OnLevelChangedHandle);
	}
	if (OnXPChangedHandle.IsValid())
	{
		PlayerState->OnXPChanged.Remove(OnXPChangedHandle);
	}
	if (OnHealthChangedHandle.IsValid())
	{
		PlayerState->OnHealthChanged.Remove(OnHealthChangedHandle);
	}
	if (OnManaChangedHandle.IsValid())
	{
		PlayerState->OnManaChanged.Remove(OnManaChangedHandle);
	}
}


void UPlayerOverlayController::NativeActivateWidgetController()
{
	BindData();
}

void UPlayerOverlayController::NativeDeactivateWidgetController()
{
	UnBindData();
}


void UPlayerOverlayController::Setup(ACmtPlayerState* PS)
{
	PlayerState = PS;
}


FPlayerAttributes UPlayerOverlayController::GetPlayerAttributes() const
{
	return PlayerState->GetPlayerAttributes();
}