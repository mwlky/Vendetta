#include "FReport.h"

FReport::FReport(FString sign, bool isFake, FString text)
{
	Sign = sign;
	Text = text;
	
	bIsFake = isFake;
}
