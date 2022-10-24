#include "PotatoUtilities.h"

#include "UObject/NoExportTypes.h"

DEFINE_LOG_CATEGORY(LogPotatoGame);

static TAutoConsoleVariable<int32> CVarWasteTime(
	TEXT("potato.WasteTime"),
	0,
	TEXT("Determine whether program will purposely waste time"),
	ECVF_Cheat);

static TAutoConsoleVariable<int32> CVarWasteMemory(
	TEXT("potato.WasteMemory"),
	0,
	TEXT("Determine whether program will purposely waste memory"),
	ECVF_Cheat);

void PotatoUtilities::DoSomething(float value)
{
	if(CVarWasteTime.GetValueOnGameThread())
	{
		WasteTime(value);
	}
}

void PotatoUtilities::DoSomethingElse(int32 value)
{
	if (CVarWasteMemory.GetValueOnGameThread())
	{
		WasteMemory(value);
	}
}

void PotatoUtilities::WasteTime(float seconds)
{
	UE_LOG(LogTemp, Log, TEXT("Wasting %.4fs seconds"), seconds);
	const FDateTime start = FDateTime::Now();
	FTimespan span(0);
	while (span.GetTotalSeconds() <= seconds)
	{
		span = FDateTime::Now() - start;
	}
	UE_LOG(LogTemp, Log, TEXT("Wasted %.4fs seconds"), span.GetTotalSeconds());
}

void PotatoUtilities::WasteMemory(int32 bytes)
{
	static TArray<TArray<uint8>> leak;

	UE_LOG(LogTemp, Log, TEXT("Wasting %lld bytes"), bytes);
	TArray<uint8>& wastedMemory = leak.AddDefaulted_GetRef();

	wastedMemory.SetNumUninitialized(bytes);
}