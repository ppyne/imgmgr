#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>
#include "image.h"
#include "mdisubwindow.h"
#include "dialognew.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->actionToolbarCursor->setChecked(true);
    Tools = new QActionGroup(ui->mainToolBar);
    Tools->addAction(ui->actionToolbarCursor);
    Tools->addAction(ui->actionToolbarZoom);
    Tools->addAction(ui->actionToolbarHand);

    //connect(Tools, SIGNAL(triggered(QAction*)), this, SLOT(onToolsTriggered(QAction*)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::fileOpen(QString path) {
    //qDebug() << "MainWindow::fileOpen(" << path << ")";

    QImageReader reader(path);
    reader.setAutoTransform(true);
    Image img = reader.read();
    if (img.isNull()) {
        QMessageBox::critical(this, QGuiApplication::applicationDisplayName(), tr("Cannot load %1: %2").arg(QDir::toNativeSeparators(path), reader.errorString()));
    } else {
        MdiSubWindow *sw = new MdiSubWindow(Tools);
        ui->mdiArea->addSubWindow(sw);
        sw->loadImage(path, img);
    }
}

void MainWindow::on_actionViewZoomIn_triggered() {
    MdiSubWindow *sw = (MdiSubWindow *)ui->mdiArea->activeSubWindow();
    if (sw) sw->view()->zoomIn();
}

void MainWindow::on_actionViewZoomOut_triggered() {
    MdiSubWindow *sw = (MdiSubWindow *)ui->mdiArea->activeSubWindow();
    if (sw) sw->view()->zoomOut();
}

void MainWindow::on_actionViewFitView_triggered() {
    MdiSubWindow *sw = (MdiSubWindow *)ui->mdiArea->activeSubWindow();
    if (sw) sw->view()->fitView();
}

void MainWindow::on_actionView100_triggered() {
    MdiSubWindow *sw = (MdiSubWindow *)ui->mdiArea->activeSubWindow();
    if (sw) sw->view()->zoom100();
}

void MainWindow::on_actionViewPrintSize_triggered() {
    MdiSubWindow *sw = (MdiSubWindow *)ui->mdiArea->activeSubWindow();
    if (sw) sw->view()->zoomPrint();
}

void MainWindow::on_actionFileNew_triggered() {
    DialogNew dialog;
    if (dialog.exec() == QDialog::Accepted) {
        MdiSubWindow *sw = new MdiSubWindow(Tools);
        ui->mdiArea->addSubWindow(sw);
        sw->newImage(dialog.name(), dialog.documentWidth(), dialog.documentHeight(), dialog.resolution(), dialog.mode(), dialog.backgroundType(), dialog.backgroundColor(), dialog.profileName());
    }
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode) {
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

void MainWindow::on_actionFileOpen_triggered() {
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    if (dialog.exec() == QDialog::Accepted) {
        fileOpen(dialog.selectedFiles().first());
    }

}
