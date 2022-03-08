#ifndef ULPS_DISTANCE_H__
#define ULPS_DISTANCE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

int32_t ulpsDistanceFloat(const float a, const float b);
int64_t ulpsDistanceDouble(const double a, const double b);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // ULPS_DISTANCE_H__
