#include <pch.hpp>

#include "launcher.hpp"

int main(int argc, char* argv[]) {
    PROFILE_BEGIN_SESSION("Horizon", "Horizon-Main.json");
    int status = launch(argc, argv);
    PROFILE_END_SESSION();
    exit(status);
}