
#include "Application.h"

#include <QFileInfo>

#include "cg-sandbox-version.h"


Application::Application(int & argc, char ** argv)
: QApplication(argc, argv)
{
    const QFileInfo fi(QCoreApplication::applicationFilePath());

    QApplication::setApplicationDisplayName(fi.baseName());

    QApplication::setApplicationName(CG_SANDBOX_PROJECT_NAME);
    QApplication::setApplicationVersion(CG_SANDBOX_VERSION);

    QApplication::setOrganizationName(CG_SANDBOX_AUTHOR_ORGANIZATION);
    QApplication::setOrganizationDomain(CG_SANDBOX_AUTHOR_DOMAIN);
}

Application::~Application()
{
}
