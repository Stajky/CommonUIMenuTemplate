// 


#include "ActionButton.h"
#include "CommonUITypes.h"
#include "Input/CommonUIInputTypes.h"

void UActionButton::SetListeningForInput(bool bShouldListen)
{
	if (GetUISubsystem() == nullptr)
	{
		return;
	}

	if (bShouldListen != bIsListeningForInput)
	{
		bIsListeningForInput = bShouldListen;
		UpdateBindings();
	}
}

void UActionButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (bAutoListenForInput)
	{
		SetListeningForInput(true);
	}
}

void UActionButton::NativeDestruct()
{
	SetListeningForInput(false);
	Super::NativeDestruct();
}

void UActionButton::UpdateBindings()

{	
	if (bIsListeningForInput)
	{
		const bool bIsEnhancedInputSupportEnabled = CommonUI::IsEnhancedInputSupportEnabled();
		if (bIsEnhancedInputSupportEnabled && EnhancedInputAction)
		{
			FBindUIActionArgs args = FBindUIActionArgs(EnhancedInputAction, false,
			                                           FSimpleDelegate::CreateUObject(this, &UActionButton::NativeButtonPressed));
			args.KeyEvent = IE_Pressed;
			InputActionHandlePressed = RegisterUIActionBinding(args);
		}
		else
		{
			FBindUIActionArgs args = FBindUIActionArgs(InputAction, false,
			                                           FSimpleDelegate::CreateUObject(this, &UActionButton::NativeButtonPressed));
			args.KeyEvent = IE_Pressed;
			InputActionHandlePressed = RegisterUIActionBinding(args);
		}
	}
	else
	{
		InputActionHandlePressed.Unregister();
	}
}

void UActionButton::NativeButtonPressed() const
{
	OnActionPressed.Broadcast();
}
