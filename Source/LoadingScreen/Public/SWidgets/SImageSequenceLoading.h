#pragma once
#include "LoadingScreenSettings.h"

class FDeferredCleanupSlateBrush;

class SImageSequenceLoading : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SImageSequenceLoading )
	: _Settings(FImageSequenceSettings() )
	{}

	/** Settings */
	SLATE_ATTRIBUTE(FImageSequenceSettings, Settings)
	
	SLATE_END_ARGS()

	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct( const FArguments& InArgs );


	//~SWidget override
	/**
	 * The widget should respond by populating the OutDrawElements array with FDrawElements
	 * that represent it and any of its children. Called by the non-virtual OnPaint to enforce pre/post conditions
	 * during OnPaint.
	 *
	 * @param Args              All the arguments necessary to paint this widget (@todo umg: move all params into this struct)
	 * @param AllottedGeometry  The FGeometry that describes an area in which the widget should appear.
	 * @param MyCullingRect     The rectangle representing the bounds currently being used to completely cull widgets.  Unless IsChildWidgetCulled(...) returns true, you should paint the widget. 
	 * @param OutDrawElements   A list of FDrawElements to populate with the output.
	 * @param LayerId           The Layer onto which this widget should be rendered.
	 * @param InColorAndOpacity Color and Opacity to be applied to all the descendants of the widget being painted
	 * @param bParentEnabled	True if the parent of this widget is enabled.
	 * @return The maximum layer ID attained by this widget or any of its children.
	 */
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	//~End of SWidget override
protected:
	// Getter for text visibility
	EVisibility GetVisibility() const;
private:
	void ResetSequence();

	void PopulateSequenceBrushList();

	void InitDisplayedImage();
	
private:	

	FImageSequenceSettings Settings;

	//TODO this isnt the best solution that I hoped for but I yet dont know how to pass TSharedPtr to the ChildSlot so that we get
	//here one unnecessary SNew call instead of just a nullptr, when I am smarter try to look for solution for this
	// Currently displayed image
	TSharedRef<SImage> CurrentImage = SNew(SImage);

	//TODO change this from array list to texture spritesheet
	// Image slate brush list
	TArray<TSharedPtr<FDeferredCleanupSlateBrush>> BrushList;	

	//Mutable is here because onpaint method is const and we need to change these variables hence we use mutable to cancel the constness
	// Current image sequence index
	mutable int32 ImageIndex = 0;

	// Current total delta time
	mutable float TotalDeltaTime = 0.0f;
		
};
