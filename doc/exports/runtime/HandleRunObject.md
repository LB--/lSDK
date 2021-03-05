This required function is called once at the start of the frame, and then possibly every tick after that.
```cpp
#ifdef FUSION_ON_TICK
auto FUSION_API HandleRunObject(RunData *const run_data) noexcept
-> std::int16_t
```
If you want Fusion to stop calling this function every tick (until you later ask for it again), return `FUSION_ON_TICK_STOP_CALLING`.
If you want Fusion to redraw the object after this, return `FUSION_ON_TICK_CALL_DRAW`.
Otherwise return `FUSION_ON_TICK_DONT_DRAW`.

This function is a good place to check and see if any triggered events need to be triggered, e.g. after another thread has finished.

If you want Fusion to call this function again after having previously asked Fusion to stop calling, use the `RFUNCTION_REHANDLE` runtime function (see the lSDK fusion utilities doc for more information).
