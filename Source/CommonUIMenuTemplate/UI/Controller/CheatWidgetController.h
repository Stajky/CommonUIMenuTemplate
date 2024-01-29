

#pragma once

#include "CoreMinimal.h"
#include "CmtWidgetController.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "CheatWidgetController.generated.h"

class UInputMappingContext;
class UInputActionToTagMap;
class APlayerController;
class ACmtPlayerState;
/**
 * 
 */
UCLASS()
class UCheatWidgetController : public UCmtWidgetController
{
	GENERATED_BODY()
public:

	/* ~UCmtWidgetController */
	virtual void BindData() override;
	virtual void UnBindData() override;
	virtual void NativeActivateWidgetController() override;
	virtual void NativeDeactivateWidgetController() override;
	/* ~End of UCmtWidgetController */
	
	void Setup(ACmtPlayerState* InPlayerState, APlayerController*  InPlayerController);

	UFUNCTION(BlueprintCallable)
	void AddToLevel();
	
	UFUNCTION(BlueprintCallable)
	void SubFromLevel();
	
	UFUNCTION(BlueprintCallable)
	void AddToXP();
	UFUNCTION(BlueprintCallable)
	void SubFromXP();
	
	UFUNCTION(BlueprintCallable)
	void AddToMana();
	UFUNCTION(BlueprintCallable)
	void SubFromMana();
	
	UFUNCTION(BlueprintCallable)
	void AddToHealth();
	UFUNCTION(BlueprintCallable)
	void SubFromHealth();

	UFUNCTION(BlueprintCallable)
	void AddToMaxHealth();
	UFUNCTION(BlueprintCallable)
	void SubFromMaxHealth();

	UFUNCTION(BlueprintCallable)
	void AddToMaxMana();
	UFUNCTION(BlueprintCallable)
	void SubFromMaxMana();
	
	void CallAllSpells(const FInputActionValue& InputActionValue);
protected:

	UPROPERTY(EditDefaultsOnly)
	int32 IMCPriority = 100;
	
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* CheatInputMappingContext;
	
	/** Map of InputActions to C++ GameplayTags */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<const UInputActionToTagMap> InputActionMap;
	
private:
	template<class UserClass, typename... VarTypes>
	void BindInputValueAction(UEnhancedInputComponent* EnhancedInputComponent, FGameplayTag InputTag, ETriggerEvent TriggerEvent, UserClass* Object, typename FEnhancedInputActionHandlerValueSignature::template TMethodPtr< UserClass, VarTypes... > Func, VarTypes... Vars);
	void UnbindInputValueActions();
	
	void SetupEnhancedInputDataForCpp() const;
public:
	int32 AddLevelMagnitude = 1;
	float AddXPMagnitude = 100;
	float AddHealthMagnitude = 10;
	float AddManaMagnitude = 10;
	float AddMaxHealthMagnitude = 10;
	float AddMaxManaMagnitude = 10;
private:
	UPROPERTY(Transient, VisibleInstanceOnly)
	TSet<int32> InputEventBindingHandles;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<ACmtPlayerState> PlayerState;
};


