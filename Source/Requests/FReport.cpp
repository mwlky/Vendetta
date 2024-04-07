#include "FReport.h"

FReport::FReport(FString sign, bool isAcceptable, FString text)
{
	Sign = sign;
	Text = text;
	
	bIsAcceptable = isAcceptable;
}
