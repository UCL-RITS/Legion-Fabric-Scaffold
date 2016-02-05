// Next line tells CATCH we will use our own main function
#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "Model.h"
#include <cmath>

int main(int argc, char * argv[]) {
    int result = Catch::Session().run(argc, argv);
    return result;
}




TEST_CASE( "Model can be instantiated and configured", "[Model]" ) {

    SECTION( "Model can be constructed" ) {
        Model model(0,1);
    }
}
