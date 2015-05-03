/**
    PURE C++ CODE
*/

#include <cstdlib>  // rand
#include <ctime>    // time

#include <iostream>
#include <iomanip>

using namespace std;

#include "hpc/component_name/Timer.hpp"
#include "hpc/component_name/Main.hpp"

#include "hpc/component_name/ComponentNameUtilCppFunctions.hpp"

int main(int ac, char * av[]) {
    srand(time(NULL));

    Timer timer;
    timer.reset();

    int x = do_all();

    double t1 = timer.elapsed();

    cout << setw(4) << x << endl;
    cout << "----" << endl;
    cout << "T1 = " << t1 << endl;

    cout << "The Answer to the Ultimate Question of Life, The Universe, and Everything is" << setw(3) << 42 << endl;

    return 0;
}
