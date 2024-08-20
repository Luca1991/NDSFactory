#pragma once

#include <QMessageBox>

void notifyExtractionResult(bool result)
{
	if (result)
	{
		QMessageBox::information(Q_NULLPTR, "NDS Factory", "Extraction completed!");
	}
	else
	{
		QMessageBox::critical(Q_NULLPTR, "NDS Factory", "Error during the extraction!");
	}
}