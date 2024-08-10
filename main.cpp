#include "ui/mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include "ui/utils/theme.h"

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication app(argc, argv);
    app.setApplicationName("NDSFactory");
    app.setOrganizationName("NDSFactory");

    QString theme = getCurrentTheme();
    if(theme == "dark")
		setDarkTheme(app);
	else if(theme == "light")
        setLightTheme(app);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
