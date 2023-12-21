#include "SWidgets/STipPanel.h"

#include "Slate/DeferredCleanupSlateBrush.h"

void STipPanel::Construct(const FArguments& InArgs)
{
	Settings = InArgs._Settings.Get();

	//TODO shuffle the tips list so that we get random sequence of tips
	
	if(!Settings.Image)
		return;
	PanelImage = FDeferredCleanupSlateBrush::CreateBrush(Settings.Image, FVector2D(1024,150));

	//create textblock as an variable so that we can set it in OnPaint

	FText text = Settings.Tips.IsEmpty() ? FText::FromString(TEXT("Default Text")) : Settings.Tips[0];
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
	if (!Settings.Tips.IsEmpty() && TotalDeltaTime >= Settings.TooltipChangeSpeed)
	{
		TotalDeltaTime = 0;
		TooltipIndex++;
		
		//reset back to start
		if (TooltipIndex >= Settings.Tips.Num())
		{
			TooltipIndex = 0;
		}
		
		TextBlock->SetText(Settings.Tips[TooltipIndex]);
	}
	
	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                                bParentEnabled);
}
