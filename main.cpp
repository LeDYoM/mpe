#include "mpeapplication.h"

int main(int argc, char *argv[])
{
    MPEApplication app(argc, argv);

    app.start();
    return app.exec();
}
