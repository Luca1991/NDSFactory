#ifndef FATSTRUCT_H
#define FATSTRUCT_H

#include <cstdint>

struct FatRange {
  uint32_t startAddr;
  uint32_t endAddr;
};

#endif // FATSTRUCT_H
