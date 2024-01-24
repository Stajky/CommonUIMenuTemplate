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
	

}

void UPlayerOverlayController::SetDataGeneratorsPointers(ACmtPlayerState* PS)
{
	PlayerState = PS;
}

FCmtPlayerAttributes UPlayerOverlayController::GetPlayerAttributes()
{
	return PlayerState->PlayerAttributes;
}


void UPlayerOverlayController::OnLevelChanged(int32 newLevel)
{
	SendIntMessage(CmtTag::UI_Message_Level, newLevel);
}

void UPlayerOverlayController::OnXPChanged(int32 newXP)
{
	SendIntMessage(CmtTag::UI_Message_XP, newXP);
}

void UPlayerOverlayController::OnHealthChanged(float newHealth)
{
	SendFloatMessage(CmtTag::UI_Message_Health, newHealth);
}

void UPlayerOverlayController::OnManaChanged(float newMana)
{
	SendFloatMessage(CmtTag::UI_Message_Mana, newMana);
}

void UPlayerOverlayController::OnSpell1Cooldown(float newCooldown)
{
	SendFloatMessage(CmtTag::UI_Message_Spell1, newCooldown);
}

void UPlayerOverlayController::OnSpell2Cooldown(float newCooldown)
{
	SendFloatMessage(CmtTag::UI_Message_Spell2, newCooldown);
}

void UPlayerOverlayController::OnSpell3Cooldown(float newCooldown)
{
	SendFloatMessage(CmtTag::UI_Message_Spell3, newCooldown);
}

void UPlayerOverlayController::OnSpell4Cooldown(float newCooldown)
{
	SendFloatMessage(CmtTag::UI_Message_Spell4, newCooldown);
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
