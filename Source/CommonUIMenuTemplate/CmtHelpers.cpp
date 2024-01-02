// 


#include "CmtHelpers.h"
#include "EnhancedInputSubsystems.h"

UEnhancedInputLocalPlayerSubsystem* UCmtHelpers::GetEnhancedInputLocalPlayerSubsystem(
	const APlayerController* PlayerController)
{
	if(const APlayerController* PC = Cast<APlayerController>(PlayerController))
	{
		if (const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			return LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		}
	}

	return nullptr;
}
