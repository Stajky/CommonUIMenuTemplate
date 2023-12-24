#pragma once
#include "LoadingScreenSettings.h"

class FDeferredCleanupSlateBrush;

class STipPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( STipPanel )
		: _Settings(FTipPanelSettings() )
	{}

	/** Settings */
	SLATE_ATTRIBUTE(FTipPanelSettings, Settings)
	
	SLATE_END_ARGS()

	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct( const FArguments& InArgs );
	
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

private:

	void ShuffleTips(TArray<FText>& TipsToShuffle);
	
private:	

	FTipPanelSettings Settings;

	TSharedPtr<FDeferredCleanupSlateBrush> PanelImage;

	TSharedRef<STextBlock> TextBlock = SNew(STextBlock);

	TArray<FText> Tips;

	mutable float TotalDeltaTime = 0.f;

	mutable int32 TooltipIndex = 0;
};
