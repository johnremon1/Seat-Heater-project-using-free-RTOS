 /******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: std_types.h
 *
 * Description: types for ARM Cortex M4F
 *
 * Author: Edges Team
 *
 *******************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


#include "Compiler.h"
#include "Common_Macros.h"

/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif



#define LOGIC_HIGH        (1u)
#define LOGIC_LOW         (0u)



#define STD_ON   (1U)
#define STD_OFF  (0U)


typedef unsigned char         uint8;          /*           0 .. 255              */
typedef signed char           sint8;          /*        -128 .. +127             */
typedef unsigned short        uint16;         /*           0 .. 65535            */
typedef signed short          sint16;         /*      -32768 .. +32767           */
typedef unsigned long         uint32;         /*           0 .. 4294967295       */
typedef signed long           sint32;         /* -2147483648 .. +2147483647      */
typedef unsigned long long    uint64;         /*       0 .. 18446744073709551615  */
typedef signed long long      sint64;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float                 float32;
typedef double                float64;

#define Enable_Exceptions()  __asm(" CPSIE I") //this instruction clears the i bit in the primask register so all interrupts are enabled
#define Disable_Exceptions() __asm(" CPSID I") //this instruction sets the i bit in the primask register so all interrupts are disabled
#define Enable_Faults() __asm(" CPSIE F")// this instruction Enables the faults exception
#define Disable_Faults() __asm(" CPSID F")// this instruction disable the faults exceptions so the the program priority becomes -1

/* Boolean Data Type */
typedef uint8 boolean;

#endif /* STD_TYPE_H_ */
