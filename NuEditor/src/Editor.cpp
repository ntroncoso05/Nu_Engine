#include <Nu.h>

using namespace Nu;

struct MyLayer : AppInterface
{
    NU_INLINE void OnStart()
    {
        AttachCallback<MouseMotionEvent>([this](auto e)
        {
            NU_TRACE("Mouse x:{} y:{}", e.TargetX, e.TargetY);
        });
    }
    
    NU_INLINE void OnUpdate()
    {
    }
};

int32_t main(int32_t argc, char** argv)
{
    auto app = new Application();
    app->AttachCallback<KeyPressEvent>([](auto e) {
        NU_TRACE("Key: {}", e.Key);
    });
    app->AttachLayer<MyLayer>();
    app->RunContext();
    return 0;
}