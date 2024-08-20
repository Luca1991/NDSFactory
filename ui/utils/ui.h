#pragma once

#include <QMessageBox>

void notifyExtractionResult(bool result)
{
	if (result)
	{
		QMessageBox::information(Q_NULLPTR, "NDSFactory", "Extraction completed!");
	}
	else
	{
		QMessageBox::critical(Q_NULLPTR, "NDSFactory", "Error during the extraction!");
	}
}