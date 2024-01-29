#include "CommonUIMenuTemplate/UI/Controller/CheatWidgetController.h"

#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "CommonUIMenuTemplate/CmtLibrary.h"
#include "CommonUIMenuTemplate/Player/CmtPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "CommonUIMenuTemplate/CmtGameplayTags.h"
#include "InputMappingContext.h"

void UCheatWidgetController::BindData()
{
	if(!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot bind inputs in without an Player Controller"));
		return;
	}
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);

	BindInputValueAction(EnhancedInput, CmtTag::InputTag_Cheat_CallAllSpells, ETriggerEvent::Completed, this, &ThisClass::CallAllSpells);
}

void UCheatWidgetController::UnBindData()
{
	if(PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem  = UCmtLibrary::GetEnhancedInputLocalPlayerSubsystem(PlayerController))
		{
			Subsystem->RemoveMappingContext(CheatInputMappingContext);
		}
	}
	
	UnbindInputValueActions();
}

void UCheatWidgetController::CallAllSpells(const FInputActionValue& InputActionValue)
{
	PlayerState->SetSpell1Cooldown(8.0f);
	PlayerState->SetSpell2Cooldown(8.0f);
	PlayerState->SetSpell3Cooldown(8.0f);
	PlayerState->SetSpell4Cooldown(8.0f);
}

void UCheatWidgetController::NativeActivateWidgetController()
{
	//We dont want remove Mapping context that was already removed
	if(!LockGuard())
		return;
	
	//Start Listening for Input
	if(PlayerController)
    {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem  = UCmtLibrary::GetEnhancedInputLocalPlayerSubsystem(PlayerController))
		{
			Subsystem->AddMappingContext(CheatInputMappingContext, IMCPriority);
		}
    }
}

void UCheatWidgetController::NativeDeactivateWidgetController()
{
	//We dont want remove Mapping context that was already removed
	if(!UnlockGuard())
		return;
	
	//Stop Listening for Input
	if(PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem  = UCmtLibrary::GetEnhancedInputLocalPlayerSubsystem(PlayerController))
		{
			Subsystem->RemoveMappingContext(CheatInputMappingContext);
		}
	}
}


void UCheatWidgetController::UnbindInputValueActions()
{
	if(!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Unbind inputs in without an Player Controller"));
		return;
	}
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	if (!ensure(EnhancedInput))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot unbind inputs without an EnhancedInputComponent"));
		return;
	}
	
	for (const int32& Handle : InputEventBindingHandles)
	{
		const bool bRemoved = EnhancedInput->RemoveActionEventBinding(Handle);
		if (!bRemoved)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to remove action event binding %i"), Handle);
		}
	}

	InputEventBindingHandles.Reset();
}

void UCheatWidgetController::Setup(ACmtPlayerState* InPlayerState, APlayerController* InPlayerController)
{
	PlayerState = InPlayerState;
	PlayerController = InPlayerController;
	
	BindData();
}

void UCheatWidgetController::AddToLevel()
{
	PlayerState->SetPlayerLevel(PlayerState->GetPlayerLevel() + AddLevelMagnitude);
}

void UCheatWidgetController::SubFromLevel()
{
	PlayerState->SetPlayerLevel(PlayerState->GetPlayerLevel() - AddLevelMagnitude);
}

void UCheatWidgetController::AddToXP()
{
	PlayerState->SetXP(PlayerState->GetXP() + AddXPMagnitude);
}

void UCheatWidgetController::SubFromXP()
{
	PlayerState->SetXP(PlayerState->GetXP() - AddXPMagnitude);
}

void UCheatWidgetController::AddToMana()
{
	PlayerState->SetMana(PlayerState->GetMana() + AddManaMagnitude);
}

void UCheatWidgetController::SubFromMana()
{
	PlayerState->SetMana(PlayerState->GetMana() - AddManaMagnitude);
}

void UCheatWidgetController::AddToHealth()
{
	PlayerState->SetHealth(PlayerState->GetHealth() + AddHealthMagnitude);
}

void UCheatWidgetController::SubFromHealth()
{
	PlayerState->SetHealth(PlayerState->GetHealth() - AddHealthMagnitude);
}

void UCheatWidgetController::AddToMaxHealth()
{
	PlayerState->SetMaxHealth(PlayerState->GetMaxHealth() + AddMaxHealthMagnitude);
}

void UCheatWidgetController::SubFromMaxHealth()
{
	PlayerState->SetMaxHealth(PlayerState->GetMaxHealth() - AddMaxHealthMagnitude);
}

void UCheatWidgetController::AddToMaxMana()
{
	PlayerState->SetMaxMana(PlayerState->GetMaxMana() + AddMaxManaMagnitude);
}

void UCheatWidgetController::SubFromMaxMana()
{
	PlayerState->SetMaxMana(PlayerState->GetMaxMana() - AddMaxManaMagnitude);
}


template <class UserClass, typename ... VarTypes>
void UCheatWidgetController::BindInputValueAction(UEnhancedInputComponent* EnhancedInputComponent,
	FGameplayTag InputTag, ETriggerEvent TriggerEvent, UserClass* Object,
	FEnhancedInputActionHandlerValueSignature::TMethodPtr<UserClass, VarTypes...> Func, VarTypes... Vars)
{
	//TODO figure out how to move this function into Function librarary I tried but to na awail so here we use duplicit code
	if (ensure(InputActionMap))
	{
		if (const UInputAction* Action = InputActionMap->FindNativeInputActionForTag(InputTag))
		{
			const FEnhancedInputActionEventBinding& Binding = EnhancedInputComponent->BindAction(Action, TriggerEvent, Object, Func, Vars...);
			InputEventBindingHandles.Add(Binding.GetHandle());

			UE_LOG(LogTemp, Display, TEXT("Bound InputAction [%s] to [%s] handle=%i"), *GetNameSafe(Action), *InputTag.ToString(), Binding.GetHandle());
		}
	}
}
