#pragma once

#include <cstdint>

struct FatRange {
  uint32_t startAddr;
  uint32_t endAddr;
};

struct FatFileID {
	uint16_t id;
	std::string path;
};