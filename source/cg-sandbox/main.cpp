
// [TODO] This belongs into the cmake platform files!!
#if defined(WIN32) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /entry:mainCRTStartup")
#endif

#include <QScopedPointer>

#include "ui/Application.h"
#include "ui/Viewer.h"

#include "DemoPainter.h"

int main(int argc, char * argv[])
{
    Application app(argc, argv);

    QScopedPointer<Viewer> viewer(new Viewer);
    QScopedPointer<AbstractPainter> demoPainter(new DemoPainter);
    QScopedPointer<AbstractPainter> demoPainter2(new DemoPainter);

    viewer->addPainter("Demo", demoPainter.data());
    viewer->addPainter("Demo 2", demoPainter2.data());
    viewer->show();

    return app.exec();
}
