#include <QApplication>
#include "gui/mainwindow.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(1200, 800); // Adjusted size to fit content better
    window.setWindowTitle("Data Structure Optimizer");
    window.show();
    return app.exec();
}
