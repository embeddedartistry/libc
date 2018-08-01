#ifndef __ARM_MACHINE_ENDIAN_H_
#define __ARM_MACHINE_ENDIAN_H_

#ifdef __ARMEB__
#define __BYTE_ORDER _BIG_ENDIAN
#else
#define __BYTE_ORDER _LITTLE_ENDIAN
#endif //__ARMEB__

#endif //__ARM_MACHINE_ENDIAN_H_
