// 


#include "CmtPlayerState.h"

ACmtPlayerState::ACmtPlayerState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACmtPlayerState::SetLevel(int32 NewLevel)
{
	PlayerAttributes.Level = NewLevel;
	OnLevelChanged.Broadcast(NewLevel);
}

void ACmtPlayerState::SetXP(int32 NewXP)
{
	//When XP changed send Broadcast new percentage
	OnXPChanged.Broadcast(CalculateXPPercent(NewXP));
	PlayerAttributes.XP = NewXP;
}

void ACmtPlayerState::SetHealth(float NewHealth)
{
	OnHealthChanged.Broadcast(NewHealth);
	PlayerAttributes.Health = NewHealth;
}

void ACmtPlayerState::SetMaxHealth(float NewMaxHealth)
{
	const float NewPercent = CalculateHealthPercentageOnMaxValueChange(PlayerAttributes.Health, PlayerAttributes.MaxHealth, NewMaxHealth);
	OnHealthChanged.Broadcast(NewPercent);
	PlayerAttributes.MaxHealth = NewMaxHealth;
}

void ACmtPlayerState::SetMana(float NewMana)
{
	OnHealthChanged.Broadcast(NewMana);
	PlayerAttributes.Mana = NewMana;
}

void ACmtPlayerState::SetMaxMana(float NewMaxMana)
{
	const float NewPercent = CalculateHealthPercentageOnMaxValueChange(PlayerAttributes.Mana, PlayerAttributes.MaxMana, NewMaxMana);
	OnHealthChanged.Broadcast(NewPercent);
	PlayerAttributes.MaxHealth = NewMaxMana;
}

void ACmtPlayerState::SetSpell1Cooldown(float NewCooldown)
{
	//TODO here we should create a better logic for saving cooldown data and broadcasting when to start UI timer even
	//but for the sake of simplicity I will just leave it like this, same for the other SetSpeelCDs methods
	OnSpell1CooldownChanged.Broadcast(NewCooldown);
	PlayerSpellData.Spell1Cooldown = NewCooldown;
}

void ACmtPlayerState::SetSpell2Cooldown(float NewCooldown)
{
	OnSpell2CooldownChanged.Broadcast(NewCooldown);
	PlayerSpellData.Spell2Cooldown = NewCooldown;
}

void ACmtPlayerState::SetSpell3Cooldown(float NewCooldown)
{
	OnSpell3CooldownChanged.Broadcast(NewCooldown);
	PlayerSpellData.Spell3Cooldown = NewCooldown;
}

void ACmtPlayerState::SetSpell4Cooldown(float NewCooldown)
{
	OnSpell3CooldownChanged.Broadcast(NewCooldown);
	PlayerSpellData.Spell4Cooldown = NewCooldown;
}

FPlayerAttributes ACmtPlayerState::GetPlayerAttributes() const
{
	return PlayerAttributes;
}

FPlayerSpellData ACmtPlayerState::GetPlayerSpellData() const
{
	return PlayerSpellData;
}

float ACmtPlayerState::CalculateXPPercent(int32 NewXP) const
{
	//These are hardcoded here one would generally create a whole system that handles XP component of some kind
	//but for our purposes this is fine
	constexpr int MaxLevel = 40;
	constexpr float XPForFirstLevel = 100;
	constexpr float XPForLastLevel = 10000;

	const float B = log(XPForLastLevel / XPForFirstLevel) / (MaxLevel - 1);
	const float A = XPForFirstLevel / (exp(B) - 1.0);

	const float LastLevelXP = round(A * exp(B * (PlayerAttributes.Level - 1)));
	const float CurrLevelXP = round(A * exp(B * PlayerAttributes.Level));
	const float XPNeeded = CurrLevelXP - LastLevelXP;

	return NewXP / XPNeeded;
}

float ACmtPlayerState::CalculateHealthPercentageOnMaxValueChange(float CurrValue, float OldMaxValue, float NewMaxValue) const
{
	const float HealthDifference = NewMaxValue - OldMaxValue;
	return (CurrValue + HealthDifference) / NewMaxValue;
}
