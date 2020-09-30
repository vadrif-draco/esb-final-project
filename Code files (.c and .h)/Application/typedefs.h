#ifndef TYPEDEF_H_
#define TYPEDEF_H_

// Signed typedefs ________________________________________
typedef signed char			int8_t;
typedef signed short		int16_t;		//	predefined?
typedef signed long			int32_t;
typedef signed long long	int64_t;


// Unsigned typedefs ______________________________________
typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;		//	predefined?
typedef unsigned long		uint32_t;
typedef unsigned long long	uint64_t;


// Signed typedefs limits _________________________________
#define INT8_MIN			-0x7f - 1
#define INT8_MAX			0x7f
#define INT16_MIN			-0x7fff - 1
#define INT16_MAX			0x7fff
#define INT32_MIN			-0x7fffffff - 1
#define INT32_MAX			0x7fffffff
#define INT64_MIN			-0x7fffffffffffffff - 1
#define INT64_MAX			0x7fffffffffffffff


// Unsigned typedefs limits _______________________________
#define UINT8_MAX			0xff
#define UINT16_MAX			0xffff
#define UINT32_MAX			0xffffffff
#define UINT64_MAX			0xffffffffffffffff

typedef enum EN_bit
{
    low, // 0
    high // 1
} EN_bit;


// Timers typedefs ________________________________________
typedef enum {NORMAL, CTC, PCPWM, FPWM} EN_TIMERMODE_t;
typedef enum {noclk,
              clk,
              clk_8,
              clk_64,
              clk_256,
              clk_1024,
              clk_ext_rising,
              clk_ext_falling
             } EN_CLOCKSOURCE_t;


typedef enum {DISCONNECTED,
              REVERSED,
              CLR_CMP,
              SET_CMP
             } EN_CMPMODE_t;

// Interrupts typedefs ____________________________________
typedef enum {INT0 = 6, INT1 = 7, INT2 = 5} EN_EXT_INTERRUPT_t;
typedef enum {LEVEL_LOW, ANY_EDGE, FALLING, RISING} EN_INTERRUPT_TRIGGER_t;

// Motor typedefs _________________________________________
typedef enum {running, stopped} EN_MOTOR_STATE_t;
typedef enum {F, B, L, R} EN_MOTOR_DIRECTION_t;

#endif /* TYPEDEF_H_ */