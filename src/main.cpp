#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowOpacity(0.3);
    window.setStyleSheet("background-color: rgb(0, 0, 0);");
    window.resize(1338, 752);
    window.show();
    return app.exec();
}
