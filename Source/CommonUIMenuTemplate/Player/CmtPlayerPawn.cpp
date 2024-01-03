// 


#include "CmtPlayerPawn.h"

#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "CommonUIMenuTemplate/CmtGameplayTags.h"
#include "InputMappingContext.h"
#include "PlayerMappableInputConfig.h"
#include "CommonUIMenuTemplate/CmtLibrary.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
ACmtPlayerPawn::ACmtPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	bCanAffectNavigationGeneration = false;

	CharacterMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Character Movement Component");
}

// Called when the game starts or when spawned
void ACmtPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACmtPlayerPawn::UnbindInputValueActions()
{
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
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

template <class UserClass, typename ... VarTypes>
void ACmtPlayerPawn::BindInputValueAction(UEnhancedInputComponent* EnhancedInputComponent, FGameplayTag InputTag,
	ETriggerEvent TriggerEvent, UserClass* Object,
	FEnhancedInputActionHandlerValueSignature::TMethodPtr<UserClass, VarTypes...> Func,
	VarTypes... Vars)
{
	// The pawn **MUST** have an InputActionMap configured so we can map input actions to gameplay tags
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

void ACmtPlayerPawn::Input_Look(const FInputActionValue& InputActionValue)
{	
	const FVector2D Value = InputActionValue.Get<FVector2D>();
	
	if (Value.X != 0.0f)
	{
		AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		AddControllerPitchInput(Value.Y);
	}
}

void ACmtPlayerPawn::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		// Quaternion AxisY is the "right" vector
		FVector RightVector = GetControlRotation().Quaternion().GetAxisY();
		AddMovementInput(RightVector, Value.X);
	}

	if (Value.Y != 0.0f)
	{
		// Quaternion AxisX is the "forward" vector
		FVector ForwardVector = GetControlRotation().Quaternion().GetAxisX();
		AddMovementInput(ForwardVector, Value.Y);
	}
}

void ACmtPlayerPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if(const APlayerController* PC = Cast<APlayerController>(NewController))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem  = UCmtLibrary::GetEnhancedInputLocalPlayerSubsystem(PC))
		{
			UE_LOG(LogTemp, Display, TEXT("Clearing all input mappings"));
			Subsystem->ClearAllMappings();
			
			if(PlayerMappableInputConfig)
			{
				for(auto[Imc, Priority] : PlayerMappableInputConfig->GetMappingContexts())
				{
					UE_LOG(LogTemp, Display, TEXT("Adding IMC [%s] with priority %i"), *GetNameSafe(Imc), Priority);

					FModifyContextOptions Options = {};
					Options.bIgnoreAllPressedKeysUntilRelease = false;

					Subsystem->AddMappingContext(Imc, Priority, Options);
				}
			}
			
		}
	}
}

void ACmtPlayerPawn::UnPossessed()
{
	// Remove any EnhancedInput IMCs
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = UCmtLibrary::GetEnhancedInputLocalPlayerSubsystem(GetController<APlayerController>()))
	{
		UE_LOG(LogTemp, Display, TEXT("Clearing input mappings"));
		Subsystem->ClearAllMappings();
	}

	// Unbind from EnhancedInput
	UnbindInputValueActions();

	Super::UnPossessed();
}

// Called to bind functionality to input
void ACmtPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// You **MUST** set InputActionMap or your pawn won't have any inputs!
	if (!ensure(IsValid(InputActionMap)))
	{
		UE_LOG(LogTemp, Error, TEXT("InputActionMap is not configured for player pawn; player pawn will have no inputs"));
		return;
	}

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(!ensure(EnhancedInput))
	{
		UE_LOG(LogTemp, Error, TEXT("EnhancedInput is null; player pawn will have no inputs"));
		return;
	}
	
	// Look and Zoom should update every tick while Triggered
	BindInputValueAction(EnhancedInput, CmtTag::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	BindInputValueAction(EnhancedInput, CmtTag::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	
}

