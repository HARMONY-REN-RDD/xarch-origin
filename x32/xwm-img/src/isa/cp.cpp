#include <xarch/origin/x32/isa.hpp>

namespace xarch::origin::x32 {

ORIGIN_X32_FUNC(cpb) {
  auto des_offsets = arch->get_des_offsets();
  auto gpr = &arch->get_gprs().at(des_offsets.at(0));

  
}

ORIGIN_X32_FUNC(cpw) {}
ORIGIN_X32_FUNC(cpl) {}

} // namespace xarch::origin::x32