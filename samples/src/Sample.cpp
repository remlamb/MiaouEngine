#include "Sample.h"

void Sample::SetUp() noexcept
{
    _timer.OnStart();
    _sampleWorld.Init();
    SampleSetUp();
}

void Sample::SetUpdate() noexcept
{
    SampleUpdate();
    _sampleWorld.Update(_timer.DeltaTime());
}

void Sample::TearDown() noexcept
{
    SampleTearDown();
    _bodyRefs.clear();
    _colRefs.clear();
    _sampleWorld.Clear();
}