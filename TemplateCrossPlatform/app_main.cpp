#include "App.h"

int main(int argc, char** argv) {
    GlutApp* app = new App(argc, argv, 1280, 800, "Galactic Attack");

    app->run();
}
