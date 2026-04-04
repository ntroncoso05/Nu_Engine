#include <Nu.h>

using namespace Nu;

struct Editor : AppInterface
{    
    NU_INLINE void OnUpdate() {}
    NU_INLINE void OnStart() {}    
};

int32_t main(int32_t argc, char** argv)
{
    auto app = new Application();
    app->AttachLayer<Editor>();
    app->RunContext();
    return 0;
}