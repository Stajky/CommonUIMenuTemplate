﻿
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
		ShiftTextLeftInternal();
	}
	else if (UINavigation == EUINavigation::Right)
	{
		ShiftTextRightInternal();
	}

	return nullptr;
}

void USwitchButton::PopulateTextLabels(TArray<FText> Labels)
{
	TextLabels = Labels;
	SelectedIndex = 0;
	DefaultIndex = SelectedIndex;

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
	ShiftTextLeftInternal();
}

void USwitchButton::ShiftTextLeftInternal()
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
		}
	}
}

void USwitchButton::ShiftTextRight()
{
	ShiftTextRightInternal();
}

int32 USwitchButton::GetCurrentOptionIndex()
{
	return SelectedIndex;
}

int32 USwitchButton::GetDefaultOptionIndex()
{
	return  DefaultIndex;
}

void USwitchButton::SetDefaultOption(int32 DefaultOptionIndex)
{
	DefaultIndex = DefaultOptionIndex;
	SetSelectedItem(DefaultOptionIndex);
	BP_OnDefaultOptionSpecified(DefaultOptionIndex);
}

void USwitchButton::ShiftTextRightInternal()
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
		}
	}
}



