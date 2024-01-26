#pragma once

#include "CoreMinimal.h"
#include "SimpleTagMessage.h"
#include "SimpleTagMessage_Float.generated.h"

/**
 * Time Message
 */
USTRUCT(BlueprintType)
struct COMMONUIMENUTEMPLATE_API FSimpleTagMessage_Float : public FSimpleTagMessage
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	float Value = 0.0f;

};
