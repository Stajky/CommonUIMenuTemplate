#include "SWidgets/STipPanel.h"

#include <random>

#include "Slate/DeferredCleanupSlateBrush.h"

void STipPanel::Construct(const FArguments& InArgs)
{
	Settings = InArgs._Settings.Get();
	
	if(!Settings.Image)
		return;
	PanelImage = FDeferredCleanupSlateBrush::CreateBrush(Settings.Image, FVector2D(1024,150));
	
	Tips = Settings.Tips;
	//Shuffle the tips if we want to
	if(Settings.bShuffleTips)
		ShuffleTips(Tips);
	
	//create textblock as an variable so that we can set it in OnPaint
	FText text = Settings.Tips.IsEmpty() ? FText::FromString(TEXT("Default Text")) : Tips[0];
	TextBlock = SNew(STextBlock)
				.Text(text)
				.Font(Settings.Font);
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(Settings.Size.X)
		.HeightOverride(Settings.Size.Y)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)
				.BorderImage(PanelImage->GetSlateBrush())
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(Settings.TextPadding)
			[
				TextBlock
			]
		]
	];
}

int32 STipPanel::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const
{
	//After some delta time change the tooltip
	TotalDeltaTime += Args.GetDeltaTime();
	if (!Tips.IsEmpty() && TotalDeltaTime >= Settings.TooltipChangeSpeed)
	{
		TotalDeltaTime = 0;
		TooltipIndex++;
		
		//reset back to start
		if (TooltipIndex >= Tips.Num())
		{
			TooltipIndex = 0;
		}
		
		TextBlock->SetText(Tips[TooltipIndex]);
	}
	
	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                                bParentEnabled);
}


void STipPanel::ShuffleTips(TArray<FText>& TipsToShuffle)
{
	int32 LastIndex = TipsToShuffle.Num() - 1;

	// //get random generator
	// std::random_device rd;
	// std::mt19937 gen(rd());
	// std::uniform_int_distribution<> distrib(0, LastIndex); 
	
	for (int32 i = 0; i < LastIndex; ++i)
	{
		int32 Index = FMath::RandRange(0, LastIndex);
		if (i != Index)
		{
			TipsToShuffle.Swap(i, Index);
		}
	}
	
}


