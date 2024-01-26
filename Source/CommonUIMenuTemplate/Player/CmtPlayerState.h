// 

#pragma once

#include "CoreMinimal.h"
#include "../Data/PlayerAttributes.h"
#include "ModularPlayerState.h"
#include "CommonUIMenuTemplate/Data/PlayerSpellData.h"
#include "CmtPlayerState.generated.h"




DECLARE_MULTICAST_DELEGATE_OneParam(FOnIntegerChangedSignature, int32 /* NewValue */)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFloatChangedSignature, float /* NewValue */)

/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API ACmtPlayerState : public AModularPlayerState
{
	GENERATED_BODY()
public:
	ACmtPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetLevel(int32 NewLevel);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetXP(int32 NewXP);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetHealth(float NewHealth);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetMaxHealth(float NewMaxHealth);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetMana(float NewMana);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetMaxMana(float NewMaxMana);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetSpell1Cooldown(float NewCooldown);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetSpell2Cooldown(float NewCooldown);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetSpell3Cooldown(float NewCooldown);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetSpell4Cooldown(float NewCooldown);
	
	FORCEINLINE FPlayerAttributes GetPlayerAttributes() const;
	FORCEINLINE FPlayerSpellData GetPlayerSpellData() const;
private:

	FORCEINLINE float CalculateXPPercent(int32 NewXP) const;
	FORCEINLINE float CalculateHealthPercentageOnMaxValueChange(float CurrValue, float OldMaxValue, float NewMaxValue) const;
	
public:
	FOnIntegerChangedSignature OnLevelChanged;
	FOnIntegerChangedSignature OnXPChanged;
	FOnFloatChangedSignature OnHealthChanged;
	FOnFloatChangedSignature OnMaxHealthChanged;
	FOnFloatChangedSignature OnManaChanged;
	FOnFloatChangedSignature OnMaxManaChanged;

	FOnFloatChangedSignature OnSpell1CooldownChanged;
	FOnFloatChangedSignature OnSpell2CooldownChanged;
	FOnFloatChangedSignature OnSpell3CooldownChanged;
	FOnFloatChangedSignature OnSpell4CooldownChanged;
	
	
protected:

	//TODO try removing SaveGame to see what it does with save system
	UPROPERTY(VisibleAnywhere, SaveGame)
	FPlayerAttributes PlayerAttributes;
	
	UPROPERTY(VisibleAnywhere, SaveGame)
	FPlayerSpellData PlayerSpellData;
	
};

