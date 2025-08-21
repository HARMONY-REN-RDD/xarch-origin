#pragma once

#include <xarch/origin/x32/xarch_origin_x32.hpp>

#define ORIGIN_X32_FUNC(name) void name(XarchOrigin_x32 *arch)

namespace xarch::origin::x32 {

ORIGIN_X32_FUNC(setb);
ORIGIN_X32_FUNC(setw);
ORIGIN_X32_FUNC(setl);

ORIGIN_X32_FUNC(cpb);
ORIGIN_X32_FUNC(cpw);
ORIGIN_X32_FUNC(cpl);



ORIGIN_X32_FUNC(stop);

} // namespace xarch::origin::x32