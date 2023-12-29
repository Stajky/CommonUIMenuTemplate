
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataTables.generated.h"

USTRUCT(Blueprintable)
struct FCreditsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Category;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Text_01;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Text_02;

	FCreditsData()
	: Category(TEXT("No Type")),
	  Text_01(TEXT("Empty Text")),
	  Text_02(TEXT("Empty Text"))
	{
	}
};















