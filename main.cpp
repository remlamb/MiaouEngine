#include "SampleManager.h"

static SampleManager sampleManager;

int main(int argc, char* argv[])
{
    if (sampleManager.InitSDL() != ErrorCode::Success)
    {
        return EXIT_FAILURE;
    }
    sampleManager.Run();
    sampleManager.DeInit();
    return 0;
}
