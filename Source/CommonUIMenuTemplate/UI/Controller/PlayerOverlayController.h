// 

#pragma once

#include "CoreMinimal.h"
#include "CmtWidgetController.h"
#include "CommonUIMenuTemplate/Player/CmtPlayerAttributes.h"
#include "PlayerOverlayController.generated.h"

class ACmtPlayerState;
class ACmtPlayerController;
struct FGameplayTag;
struct FSimpleTagMessage;
struct FSimpleTagMessage_Float;
struct FSimpleTagMessage_Int;
/**
 * 
 */
UCLASS()
class COMMONUIMENUTEMPLATE_API UPlayerOverlayController : public UCmtWidgetController
{
	GENERATED_BODY()

public:

	UPlayerOverlayController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	/** ~UCmtWidgetController functions */
	virtual void BindDataGenerators() override;
	/** ~End of UCmtWidgetController functions */

	void SetDataGeneratorsPointers(ACmtPlayerState* PS);

	UFUNCTION(BlueprintCallable)
	FCmtPlayerAttributes GetPlayerAttributes();
	
protected:
	
	// /** ~Broadcast functions */
	FORCEINLINE void OnLevelChanged(int32 newLevel);
	FORCEINLINE void OnXPChanged(int32 newXP);
	FORCEINLINE void OnHealthChanged(float newHealth);
	FORCEINLINE void OnManaChanged(float newMana);
	FORCEINLINE void OnSpell1Cooldown(float newCooldown);
	FORCEINLINE void OnSpell2Cooldown(float newCooldown);
	FORCEINLINE void OnSpell3Cooldown(float newCooldown);
	FORCEINLINE void OnSpell4Cooldown(float newCooldown);
	// /** ~Broadcast functions */

	FORCEINLINE void SendIntMessage(FGameplayTag Tag, int32 Value) const;
	FORCEINLINE void SendFloatMessage(FGameplayTag Tag, float Value) const;

private:
	TObjectPtr<ACmtPlayerState> PlayerState;
};


