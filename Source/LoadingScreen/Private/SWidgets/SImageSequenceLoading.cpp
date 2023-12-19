#include "SWidgets/SImageSequenceLoading.h"

#include "MoviePlayer.h"
#include "Slate/DeferredCleanupSlateBrush.h"
#include "Widgets/Layout/SSpacer.h"

void SImageSequenceLoading::Construct(const FArguments& InArgs)
{
	Settings = InArgs._Settings.Get();

	ResetSequence();
	
	InitDisplayedImage();
	
	ChildSlot
	[
		CurrentImage
	];
	
}

int32 SImageSequenceLoading::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	TotalDeltaTime += Args.GetDeltaTime();

	if (!BrushList.IsEmpty() && TotalDeltaTime >= Settings.Speed)
	{
		ImageIndex++;
		
		//reset back to start
		if (ImageIndex >= BrushList.Num())
		{
			ImageIndex = 0;
		}

		const TSharedPtr<FDeferredCleanupSlateBrush>& NewImageBrush = BrushList[ImageIndex];
		CurrentImage->SetImage(NewImageBrush.IsValid() ? NewImageBrush->GetSlateBrush() : nullptr);
	
		TotalDeltaTime = 0.0f;
	}

	
	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                                bParentEnabled);
}

EVisibility SImageSequenceLoading::GetVisibility() const
{
	return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Hidden : EVisibility::Visible;
}

void SImageSequenceLoading::ResetSequence()
{
	BrushList.Empty();
	ImageIndex = 0;
}

void SImageSequenceLoading::PopulateSequenceBrushList()
{
	const FVector2D& Scale = Settings.Scale;
	for (const auto Image: Settings.Images)
	{
		if (Image)
		{
			BrushList.Add(FDeferredCleanupSlateBrush::CreateBrush(Image, FVector2D(Image->GetSurfaceWidth() * Scale.X, Image->GetSurfaceHeight() * Scale.Y)));					
		}				
	}
}

void SImageSequenceLoading::InitDisplayedImage()
{	
	// Loading Widget is image sequence
	if (!Settings.Images.IsEmpty())
	{
		PopulateSequenceBrushList();
		
		// Create Image slate widget
		CurrentImage = SNew(SImage)
					   .Image(BrushList[ImageIndex]->GetSlateBrush());
		
	}

	if (Settings.bHideLoadingWidgetWhenCompletes)
	{		
		SetVisibility(TAttribute<EVisibility>::Create(TAttribute<EVisibility>::FGetter::CreateRaw(this, &SImageSequenceLoading::GetVisibility)));
	}
}
