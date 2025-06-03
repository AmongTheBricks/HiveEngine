#pragma once

namespace hive {

	class HIVE_API RateController {
	public:

		RateController(int targetRate)
			: frameDuration(1000/targetRate),
			lastUpdateTime(std::chrono::high_resolution_clock::now())
		{}

		void waitForNextTick();

	private:
		std::chrono::high_resolution_clock::time_point lastUpdateTime; // Time of the last frame update
		std::chrono::milliseconds frameDuration; // Duration of each frame in milliseconds
	};

} // hive