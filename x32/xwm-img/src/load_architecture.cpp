#include <xarch/origin/x32/isa.hpp>
#include <xarch/origin/x32/xarch_origin_x32.hpp>

#include <xuci/log.hpp>
#include <xuci/orchestrator.hpp>

namespace xarch::origin::x32 {

XarchOrigin_x32::XarchOrigin_x32() {
  this->IP = 0;
  this->SR = 0;

  this->current_instruction = 0;

  xuci::log_info(1, "Starting xarch-origin-x32");

  this->instruction_set[0x0001] = setb;
  this->instruction_set[0x0002] = setw;
  this->instruction_set[0x0003] = setl;
  this->instruction_set[0xFFFF] = stop;
}

XarchOrigin_x32::~XarchOrigin_x32() {
  xuci::log_info(1, "Closing xarch-origin-x32");
}

void XarchOrigin_x32::write_instruction(std::uint32_t &offset,
                                        std::uint16_t inst, std::uint32_t des,
                                        std::uint32_t a, std::uint32_t b) {
  auto write_uint32 = [this, &offset](std::uint32_t value) {
    this->vmu.write(offset++, (value >> 24) & 0xFF);
    this->vmu.write(offset++, (value >> 16) & 0xFF);
    this->vmu.write(offset++, (value >> 8) & 0xFF);
    this->vmu.write(offset++, value & 0xFF);
  };

  this->vmu.write(offset++, inst >> 8);
  this->vmu.write(offset++, inst & 0xFF);

  write_uint32(des);
  write_uint32(a);
  write_uint32(b);
}

} // namespace xarch::origin::x32

XUCI_EXPORT
xuci::BaseArchitecture *load_architecture(xuci::Orchestrator *orchestrator) {
  return new xarch::origin::x32::XarchOrigin_x32();
}
