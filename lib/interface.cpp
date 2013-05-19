#include "interface.hpp"

extern "C" {

void* ph_engine_init() {
    return new Context();
}

void ph_engine_free(void *ctx) {
    Context *context = (Context*)ctx;
    delete context;
}

}
