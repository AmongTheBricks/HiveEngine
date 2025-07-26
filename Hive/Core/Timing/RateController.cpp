#include "RateController.h"
#include <thread>

namespace hive {
	void RateController::waitForNextTick() {
		auto now = std::chrono::high_resolution_clock::now();
		auto elapsed = now - lastUpdateTime;

		if (elapsed < frameDuration) {
			std::this_thread::sleep_for(frameDuration - elapsed);
		}

		lastUpdateTime = std::chrono::high_resolution_clock::now();
	}
} // hive