#include <xarch/origin/x32/isa.hpp>

namespace xarch::origin::x32 {

ORIGIN_X32_FUNC(setb) {
  auto des_offsets = arch->get_des_offsets();
  auto gpr = &arch->get_gprs().at(des_offsets.at(0));

  size_t le_index =
      (des_offsets.at(0) << 2) | (des_offsets.at(1) << 1) | des_offsets.at(2);

  size_t be_index = 3 - le_index;

  gpr->b[be_index] = arch->get_a_value();
}

ORIGIN_X32_FUNC(setw) {
  auto des_offsets = arch->get_des_offsets();
  auto gpr = &arch->get_gprs().at(des_offsets.at(0));

  size_t be_word_index = 1 - des_offsets.at(1);

  gpr->w[be_word_index] = static_cast<uint16_t>(arch->get_a_value() & 0xFFFF);
}

ORIGIN_X32_FUNC(setl) {
  auto des_offsets = arch->get_des_offsets();

  auto gpr = &arch->get_gprs().at(des_offsets.at(0));

  gpr->l = arch->get_a_value();
}

} // namespace xarch::origin::x32