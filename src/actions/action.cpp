#include "actions/action.h"

int Action::readThreshold(const Config &config) {
  int threshold = 0;
  try {
    threshold =
      std::stoi(config.getGlobalSetting("action_execute_threshold"));
  } catch (std::exception& e) {
    std::cout << "Bad action_execute_threshold value: "
              << e.what() << std::endl;
    // leave default 0 if numeric conversion failed
  }
  // discard negative percentage
  return std::max(threshold, 0);
}
