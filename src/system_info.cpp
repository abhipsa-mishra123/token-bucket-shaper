#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <cstdlib>

using namespace std;

void showSystemInfo()
{
    char currentDirectory[PATH_MAX];

    cout << endl;
    cout << "========== LINUX SYSTEM INFO ==========" << endl;

    cout << "Process ID: " << getpid() << endl;
    cout << "User ID: " << getuid() << endl;
    cout << "Operating System: Linux" << endl;

    if (getcwd(currentDirectory, sizeof(currentDirectory)) != nullptr)
    {
        cout << "Current Working Directory: "
             << currentDirectory << endl;
    }
    else
    {
        cout << "Current Working Directory: Not available" << endl;
    }

    cout << "=======================================" << endl;
}