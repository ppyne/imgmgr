#include "application.h"
#include <QStyleFactory>
#include <QStyle>

int main(int argc, char *argv[]) {
    CApplication a(argc, argv);
    QCoreApplication::setOrganizationName("ImgMgr");
    QCoreApplication::setOrganizationDomain("imgmgr");
    QCoreApplication::setApplicationName("ImgMgr");
    a.setStyle(QStyleFactory::create("cleanlooks"));
    a.setPalette(a.style()->standardPalette());
    return a.exec();
}
