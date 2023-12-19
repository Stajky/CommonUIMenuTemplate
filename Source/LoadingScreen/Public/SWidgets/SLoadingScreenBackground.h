#pragma once
#include "LoadingScreenSettings.h"


class FDeferredCleanupSlateBrush;

class LOADINGSCREEN_API SLoadingScreenBackground : public SCompoundWidget
{
	
public:
	SLATE_BEGIN_ARGS( SLoadingScreenBackground )
	: _Settings(FBackgroundSettings() )
	{}

	/** Settings */
	SLATE_ATTRIBUTE(FBackgroundSettings, Settings)
	
	SLATE_END_ARGS()

	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct( const FArguments& InArgs );

private:	

	FBackgroundSettings Settings;

	TSharedPtr<FDeferredCleanupSlateBrush> ImageBrush;
};
