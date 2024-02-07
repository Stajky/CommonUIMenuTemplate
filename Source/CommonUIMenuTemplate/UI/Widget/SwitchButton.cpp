
#include "SwitchButton.h"
#include "CommonTextBlock.h"


USwitchButton::USwitchButton(const FObjectInitializer& ObjectInitializer)
{
	SetIsFocusable(true);
}

bool USwitchButton::Initialize()
{
	if (Super::Initialize())
	{
		OnNavigation.BindUObject(this, &USwitchButton::HandleNavigation);

		return true;
	}

	return false;
}

FNavigationReply USwitchButton::NativeOnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent, const FNavigationReply& InDefaultReply)
{
	switch (InNavigationEvent.GetNavigationType())
	{
	case EUINavigation::Left:
	case EUINavigation::Right:
		return FNavigationReply::Custom(OnNavigation);
	default:
		return InDefaultReply;
	}
}

TSharedPtr<SWidget> USwitchButton::HandleNavigation(EUINavigation UINavigation)
{
	if (UINavigation == EUINavigation::Left)
	{
		ShiftTextLeftInternal(true);
	}
	else if (UINavigation == EUINavigation::Right)
	{
		ShiftTextRightInternal(true);
	}

	return nullptr;
}

void USwitchButton::PopulateTextLabels(TArray<FText> Labels)
{
	TextLabels = Labels;
	SelectedIndex = 0;

	BP_OnOptionsPopulated(TextLabels.Num());
}

FText USwitchButton::GetSelectedText() const
{
	return LabelText->GetText();
}

void USwitchButton::SetSelectedItem(int32 InIndex)
{
	if (TextLabels.IsValidIndex(InIndex))
	{
		SelectedIndex = InIndex;
		LabelText->SetText(TextLabels[SelectedIndex]);

		BP_OnOptionSelected(SelectedIndex);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to set CommonRotator to an out of bounds index: %i"), InIndex);
	}
}

void USwitchButton::ShiftTextLeft()
{
	ShiftTextLeftInternal(false);
}

void USwitchButton::ShiftTextLeftInternal(bool bFromNavigation)
{
	if (IsInteractionEnabled())
	{
		if (SelectedIndex <= 0)
		{
			SelectedIndex = TextLabels.Num() - 1;
		}
		else
		{
			SelectedIndex--;
		}

		if (TextLabels.IsValidIndex(SelectedIndex))
		{
			SetSelectedItem(SelectedIndex);

			if (OnSwitched.IsBound())
			{
				OnSwitched.Broadcast(SelectedIndex);
			}

			OnSwitchedEvent.Broadcast(SelectedIndex, bFromNavigation);
		}
	}
}

void USwitchButton::ShiftTextRight()
{
	ShiftTextRightInternal(false);
}

void USwitchButton::ShiftTextRightInternal(bool bFromNavigation)
{
	if (IsInteractionEnabled())
	{
		if (SelectedIndex >= TextLabels.Num() - 1)
		{
			SelectedIndex = 0;
		}
		else
		{
			SelectedIndex++;
		}

		if (TextLabels.IsValidIndex(SelectedIndex))
		{
			SetSelectedItem(SelectedIndex);

			if (OnSwitched.IsBound())
			{
				OnSwitched.Broadcast(SelectedIndex);
			}

			OnSwitchedEvent.Broadcast(SelectedIndex, bFromNavigation);
		}
	}
}


