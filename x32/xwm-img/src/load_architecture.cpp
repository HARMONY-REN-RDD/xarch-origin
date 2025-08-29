#include <xarch/origin/x32.hpp>
#include <xwm/orchestrator.hpp>

XWM_EXPORT
xwm::BaseArchitecture *load_architecture(xwm::Orchestrator *orchestrator) {
  return new xarch::origin::XarchOrigin_x32();
}
