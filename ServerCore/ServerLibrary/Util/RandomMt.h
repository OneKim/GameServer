#pragma once
#include "stdafx.h"

#define RAND(type, maxVal)			(type) RandomMT::getInstance().rand(maxVal)

class RandomMT : public Singleton<RandomMT>
{
public:
	uint64_t rand(int maxVal)
	{
		//MT19937 난수 엔진
		static uint32_t seed = 0;
		std::mt19937 engine((uint32_t)time(nullptr) + seed++);

		std::uniform_int_distribution<uint64_t> distribution(0, UINT64_MAX);
		//rand 생성 함수포인터 bind
		auto generator = bind(distribution, engine);

		return (uint64_t)(generator() % maxVal);
	}
};