#ifndef PX_CORE_FORMAT_OPTION_H
#define PX_CORE_FORMAT_OPTION_H

#include "import.h"

typedef enum PxFormatOption
{
    PX_FORMAT_OPTION_NONE         = 0x0,
    PX_FORMAT_OPTION_LEADING_ZERO = 0x1,
    PX_FORMAT_OPTION_LEADING_PLUS = 0x2,
    PX_FORMAT_OPTION_UPPER_CASE   = 0x4,
}
PxFormatOption;

#endif // PX_CORE_FORMAT_OPTION_H
