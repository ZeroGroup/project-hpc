#include <hpc/gui/MainWindow.hpp>

#include <hpc/sensors/SensorNetwork.hpp>

int main(int ac, char *av[]){
    MainWindow * app = new MainWindow();
    delete app;

    SensorNetwork net(4);
    net.push();

    return 0;
}
