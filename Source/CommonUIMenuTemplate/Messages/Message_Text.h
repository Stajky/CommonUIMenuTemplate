#pragma once

#include "CoreMinimal.h"
#include "Message_Text.generated.h"

/**
 * Time Message
 */
USTRUCT(BlueprintType)
struct COMMONUIMENUTEMPLATE_API FMessage_Text
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FText Value = FText::FromString("");

};
