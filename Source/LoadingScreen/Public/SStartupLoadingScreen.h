#pragma once

#include "MoviePlayer.h"
#include "Widgets/Images/SThrobber.h"
#include "Widgets/SCompoundWidget.h"


class SStartupLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStartupLoadingScreen) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		FSlateBrush *BGBrush = new FSlateBrush();
		BGBrush->TintColor = FLinearColor(0.034f, 0.034f, 0.034f, 0.0f);

		ChildSlot
			[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)	
				.BorderImage(BGBrush)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(FMargin(10.0f))
				[
					SNew(SThrobber)
					.Visibility(this, &SStartupLoadingScreen::GetLoadIndicatorVisibility)
				]
			]
		];
	}

private:
	/** Rather to show the ... indicator */
	EVisibility GetLoadIndicatorVisibility() const
	{
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}

};