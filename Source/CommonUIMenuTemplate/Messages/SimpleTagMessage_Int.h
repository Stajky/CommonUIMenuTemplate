#pragma once

#include "CoreMinimal.h"
#include "SimpleTagMessage.h"
#include "SimpleTagMessage_Int.generated.h"

/**
 * Time Message
 */
USTRUCT(BlueprintType)
struct COMMONUIMENUTEMPLATE_API FSimpleTagMessage_Int : public FSimpleTagMessage
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	int32 Value;

};
