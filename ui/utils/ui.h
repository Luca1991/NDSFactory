#pragma once

#include <QMessageBox>
#include "../../ndsfactory/nfresult.h"

void notifyExtractionResult(NFResult nfResult)
{
	if (nfResult.result)
	{
		QMessageBox::information(Q_NULLPTR, "NDSFactory", "Extraction completed!");
	}
	else
	{
		QMessageBox::critical(Q_NULLPTR, "NDSFactory", nfResult.message.c_str());
	}
}