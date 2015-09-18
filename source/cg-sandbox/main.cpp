
// [TODO] This belongs into the cmake platform files!!
#if defined(WIN32) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /entry:mainCRTStartup")
#endif

#include <QScopedPointer>

#include "ui/Application.h"
#include "ui/Viewer.h"

#include "DemoPainter21.h"
#include "DemoPainter32.h"

int main(int argc, char * argv[])
{
    Application app(argc, argv);

    QScopedPointer<Viewer> viewer(new Viewer);
    QScopedPointer<AbstractPainter> demoPainter(new DemoPainter21);
    QScopedPointer<AbstractPainter> demoPainter2(new DemoPainter32);

    viewer->addPainter("Demo", demoPainter.data());
    viewer->addPainter("Demo 2", demoPainter2.data());
    viewer->show();

    return app.exec();
}
