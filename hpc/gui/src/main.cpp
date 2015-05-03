#include <iostream>

#include <hpc/gui/MainWindow.hpp>

using namespace std;

int main(int ac, char *av[]){
    cout << "Hello, World!" << endl;

    test_network();

    cout << "Goodbye!" << endl;

    //MainWindow app;
    return 0; //app.exec(ac, av);
}
