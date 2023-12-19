#include "SWidgets\SLoadingScreenBackground.h"
#include "Slate/DeferredCleanupSlateBrush.h"
#include "Widgets/Images/SImage.h"
#include "Engine/Texture2D.h"


void SLoadingScreenBackground::Construct(const FArguments& InArgs)
{
	Settings = InArgs._Settings.Get();

	UTexture2D* ImageTextureRaw = Cast<UTexture2D>(Settings.ImagePath.TryLoad());
	if(!ImageTextureRaw)
		return;

	const FLinearColor Tint = Settings.Tint.GetSpecifiedColor();
	ImageBrush = FDeferredCleanupSlateBrush::CreateBrush(ImageTextureRaw, Tint);
	
	ChildSlot
	[
		SNew(SScaleBox)
		.Stretch(Settings.ImageStretch)
		[
			SNew(SImage)						
			.Image(ImageBrush->GetSlateBrush())
		]
	];
}


