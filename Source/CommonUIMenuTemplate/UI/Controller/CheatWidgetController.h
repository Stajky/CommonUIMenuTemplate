

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
	
	void AddToLevel(const FInputActionValue& InputActionValue);
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

private:
	UPROPERTY(Transient, VisibleInstanceOnly)
	TSet<int32> InputEventBindingHandles;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<ACmtPlayerState> PlayerState;
};


