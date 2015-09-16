
// [TODO] This belongs into the cmake platform files!!
#if defined(WIN32) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /entry:mainCRTStartup")
#endif

#include "Application.h"

int main(int argc, char * argv[])
{
    Application app(argc, argv);

    return app.exec();
}
