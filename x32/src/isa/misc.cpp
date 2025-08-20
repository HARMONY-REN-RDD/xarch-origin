#include <xarch/origin/x32/isa.hpp>

#include <iostream>

namespace xarch::origin::x32 {

ORIGIN_X32_FUNC(stop) {
  arch->stop_execution();
}

}