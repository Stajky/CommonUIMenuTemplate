//

#include "PlayerOverlayController.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "CommonUIMenuTemplate/CmtGameplayTags.h"
#include "CommonUIMenuTemplate/Messages/SimpleTagMessage_Int.h"
#include "CommonUIMenuTemplate/Messages/SimpleTagMessage.h"
#include "CommonUIMenuTemplate/Messages/SimpleTagMessage_Float.h"
#include "../../Player/CmtPlayerState.h"


UPlayerOverlayController::UPlayerOverlayController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UPlayerOverlayController::BindDataGenerators()
{
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);

	//TODO vymyslet jak to tady bude s generators no, nedává uplně smysl aby to byli zase GMS páč to bych rovnou raši posílal a ne na dvakrat
	// jako dava to smysl hlediska je to vsechno pekne na jednom miste no aale to je tak vsechno
	// asi by se hodilo mit tady pointery k classe kde jsou tyto informace a pak kde jsou klasicky bindy no
	

	/* Bind to Player State Data */
	PlayerState->OnLevelChanged.AddLambda(
		[this](int32 NewLevel)
		{
			SendIntMessage(CmtTag::UI_Message_Level, NewLevel);
		});

	PlayerState->OnXPChanged.AddLambda(
		[this](int32 NewXPPercent)
		{
			SendFloatMessage(CmtTag::UI_Message_XPPercent, NewXPPercent);
		});

	PlayerState->OnHealthChanged.AddLambda(
		[this](float NewHealthPercent)
		{
			SendFloatMessage(CmtTag::UI_Message_HealthPercent, NewHealthPercent);
		});

	PlayerState->OnManaChanged.AddLambda(
		[this](float NewManaPercent)
		{
			SendFloatMessage(CmtTag::UI_Message_ManaPercent, NewManaPercent);
		});
	
	
}

void UPlayerOverlayController::SetDataGeneratorsPointers(ACmtPlayerState* PS)
{
	PlayerState = PS;
}

FPlayerAttributes UPlayerOverlayController::GetPlayerAttributes() const
{
	return PlayerState->GetPlayerAttributes();
}

void UPlayerOverlayController::SendIntMessage(FGameplayTag Tag, int32 Value) const
{
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FSimpleTagMessage_Int OutgoingMessage;
	OutgoingMessage.Tag = Tag;
	OutgoingMessage.Value = Value;
	MessageSubsystem.BroadcastMessage(CmtTag::GMSChannel_UI, OutgoingMessage);
}

void UPlayerOverlayController::SendFloatMessage(FGameplayTag Tag, float Value) const
{
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FSimpleTagMessage_Float OutgoingMessage;
	OutgoingMessage.Tag = Tag;
	OutgoingMessage.Value = Value;
	MessageSubsystem.BroadcastMessage(CmtTag::GMSChannel_UI, OutgoingMessage);
}
