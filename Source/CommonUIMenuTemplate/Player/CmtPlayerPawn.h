// 

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "CommonUIMenuTemplate/Core/CmtPawn.h"
#include "CmtPlayerPawn.generated.h"

class UFloatingPawnMovement;
class UPlayerMappableInputConfig;
class UInputMappingContext;
class UInputActionToTagMap;
struct FGameplayTag;
struct FInputActionValue;

UCLASS()
class COMMONUIMENUTEMPLATE_API ACmtPlayerPawn : public ACmtPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACmtPlayerPawn();

protected:
	//~Actor interface
	virtual void BeginPlay() override;
	//~ End of Actor

	template<class UserClass, typename... VarTypes>
	void BindInputValueAction(UEnhancedInputComponent* EnhancedInputComponent, FGameplayTag InputTag, ETriggerEvent TriggerEvent, UserClass* Object, typename FEnhancedInputActionHandlerValueSignature::template TMethodPtr< UserClass, VarTypes... > Func, VarTypes... Vars);
	void UnbindInputValueActions();
	
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Move(const FInputActionValue& InputActionValue);
	
public:

	//~APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//~End of APawn Interface

	
	
protected:

	/** Config of IMC with priority */
	UPROPERTY(EditDefaultsOnly)
	UPlayerMappableInputConfig* PlayerMappableInputConfig;
	
	/** Map of InputActions to C++ GameplayTags */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<const UInputActionToTagMap> InputActionMap;
	
private:
	UPROPERTY(Transient, VisibleInstanceOnly)
	TSet<int32> InputEventBindingHandles;
	
	/** Movement component used for movement logic in various movement modes (walking, falling, etc), containing relevant settings and functions to control movement. */
	UPROPERTY(Category=Movement, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> CharacterMovement;
};


