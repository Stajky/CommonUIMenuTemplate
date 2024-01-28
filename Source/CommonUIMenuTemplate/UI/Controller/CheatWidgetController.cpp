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

	BindInputValueAction(EnhancedInput, CmtTag::InputTag_Cheat_F1, ETriggerEvent::Completed, this, &ThisClass::AddToLevel);
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

void UCheatWidgetController::AddToLevel(const FInputActionValue& InputActionValue)
{
	//TODO remove hardcoded value
	PlayerState->SetLevel(PlayerState->GetPlayerLevel() + 1);
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


void UCheatWidgetController::SetupEnhancedInputDataForCpp() const
{
	//setup our C++ links to BP definitions, YOU NEED TO SET THE MAPPINGS IN BLUEPRINT VERSION OF THIS Controller
	if(PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem  = UCmtLibrary::GetEnhancedInputLocalPlayerSubsystem(PlayerController))
		{
			UE_LOG(LogTemp, Display, TEXT("Remove previous Mapping context if any"));
			Subsystem->RemoveMappingContext(CheatInputMappingContext);
			
			if(CheatInputMappingContext)
			{
				UE_LOG(LogTemp, Display, TEXT("Adding IMC [%s] with priority %i"), *GetNameSafe(CheatInputMappingContext), IMCPriority);

				FModifyContextOptions Options = {};
				Options.bIgnoreAllPressedKeysUntilRelease = false;

				Subsystem->AddMappingContext(CheatInputMappingContext, IMCPriority, Options);
			}
		}
	}
}


void UCheatWidgetController::Setup(ACmtPlayerState* InPlayerState, APlayerController* InPlayerController)
{
	PlayerState = InPlayerState;
	PlayerController = InPlayerController;
	
	SetupEnhancedInputDataForCpp();
	BindData();
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
