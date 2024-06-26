#include "Headers/QB_FrontEnd.hpp"


int main() {
    QB_FrontEnd q;
    while (q.isRunning()) // Main Windows Loop.
    {
        q.mainMenu();
        q.subMenu();
    }
    return 0; // Will Not Be Executed Because The Exiting Has Been Handled Already.
}
