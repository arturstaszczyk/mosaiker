#ifndef HPTINTEGRATION_H
#define HPTINTEGRATION_H

#if defined(_PROFILE)

#include <HPT/PerformanceHelper.h>

#define PROFILE_SCOPE_START(x) MEASURE_SCOPE_START(x)
#define PROFILE_SCOPE_END MEASURE_SCOPE_END
#define PROFILE_END FRAME_END

#else

#define PROFILE_SCOPE_START(x) (void)(x);
#define PROFILE_SCOPE_END()
#define PROFILE_END()

#endif

#endif // HPTINTEGRATION_H
