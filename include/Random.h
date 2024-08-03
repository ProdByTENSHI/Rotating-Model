#pragma once

#include <random>

namespace engine
{
	class Random
	{
	public:
		static int GetNextInt(int minInclusive, int maxInclusive)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distr(minInclusive, maxInclusive);
			return distr(gen);
		}

		static float GetFloat(float minInclusive, float maxInclusive)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distr(minInclusive, maxInclusive);
			return distr(gen);
		}

		static unsigned int GetRandomSeed()
		{
			std::srand(std::time(nullptr));
			return std::rand();
		}
	};
}