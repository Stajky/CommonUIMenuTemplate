// 


#include "CmtPlayerState.h"

ACmtPlayerState::ACmtPlayerState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACmtPlayerState::SetPlayerLevel(int32 NewLevel)
{
	PlayerAttributes.Level = NewLevel;
	OnLevelChanged.Broadcast(NewLevel);
}

int32 ACmtPlayerState::GetPlayerLevel() const
{
	return PlayerAttributes.Level;
}

void ACmtPlayerState::SetXP(int32 NewXP)
{
	//When XP changed send Broadcast new percentage
	OnXPChanged.Broadcast(CalculateXPPercent(NewXP));
	PlayerAttributes.XP = NewXP;
}

float ACmtPlayerState::GetXP() const
{
	return PlayerAttributes.XP;
}

void ACmtPlayerState::SetHealth(float NewHealth)
{
	NewHealth = FMath::Clamp(NewHealth,0.0f,GetMaxHealth());
	
	OnHealthChanged.Broadcast(NewHealth / GetMaxHealth());
	PlayerAttributes.Health = NewHealth;
}

float ACmtPlayerState::GetHealth() const
{
	return PlayerAttributes.Health;
}

float ACmtPlayerState::GetMaxHealth() const
{
	return PlayerAttributes.MaxHealth;
}

float ACmtPlayerState::GetMana() const
{
	return PlayerAttributes.Mana;
}

float ACmtPlayerState::GetMaxMana() const
{
	return PlayerAttributes.MaxMana;
}

void ACmtPlayerState::SetMaxHealth(float NewMaxHealth)
{
	//Get the difference between old and new value
	const float Difference = NewMaxHealth - PlayerAttributes.MaxHealth;
	PlayerAttributes.MaxHealth = NewMaxHealth;
	//Here adding to MAX value will add it to base value as well, It will also broadcast the change
	SetHealth(GetHealth() + Difference);
}

void ACmtPlayerState::SetMana(float NewMana)
{
	NewMana = FMath::Clamp(NewMana,0.0f, GetMaxMana());
	OnManaChanged.Broadcast(NewMana / GetMaxMana());
	PlayerAttributes.Mana = NewMana;
}

void ACmtPlayerState::SetMaxMana(float NewMaxMana)
{
	//Get the difference between old and new value
	const float Difference = NewMaxMana - PlayerAttributes.MaxMana;
	PlayerAttributes.MaxMana = NewMaxMana;
	//Here adding to MAX value will add it to base value as well, It will also broadcast the change
	SetMana(GetMana() + Difference);
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
	OnSpell4CooldownChanged.Broadcast(NewCooldown);
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
	constexpr float XPForFirstLevel = 1000;
	constexpr float XPForLastLevel = 10000;

	const float B = log(XPForLastLevel / XPForFirstLevel) / (MaxLevel - 1);
	const float A = XPForFirstLevel / (exp(B) - 1.0);

	const float LastLevelXP = round(A * exp(B * (PlayerAttributes.Level - 1)));
	const float CurrLevelXP = round(A * exp(B * PlayerAttributes.Level));
	const float XPNeeded = CurrLevelXP - LastLevelXP;

	return NewXP / XPNeeded;
}
