#ifndef UTILS_REPOSITION_CURSOR_H_
#define UTILS_REPOSITION_CURSOR_H_

#include <string>
#include "gesture/gesture-type.h"

// Bitmask representing options for when cursor should be repositioned.
enum RepositionCursorOpt {
  NEVER				= 0b00,	// 0
  GESTURE_END			= 0b01,	// 1
  GESTURE_UPDATE		= 0b10,	// 2
  GESTURE_UPDATE_AND_END	= 0b11	// 3
};

inline bool gestureTypeSupportsCursorReposition(GestureType gestureType) {
  switch (gestureType) {
    case GestureType::SWIPE:
    case GestureType::TAP:
      return true;
    default:
      return false;
  }
};

inline std::string repositionCursorOptToStr(RepositionCursorOpt repositionCursorOpt) {
  switch (repositionCursorOpt) {
    case RepositionCursorOpt::NEVER:
      return "NEVER";
    case RepositionCursorOpt::GESTURE_END:
      return "GESTURE_END";
    case RepositionCursorOpt::GESTURE_UPDATE:
      return "GESTURE_UPDATE";
    case RepositionCursorOpt::GESTURE_UPDATE_AND_END:
      return "GESTURE_UPDATE_AND_END";
    default:
      return "NEVER";
  }
}

inline RepositionCursorOpt repositionCursorOptFromStr(const std::string &str) {
  constexpr auto prefixLength = sizeof("GESTURE_")-1;	// -1 for terminating null.
  if (!str.compare(prefixLength, std::string::npos, "END")) {
    return RepositionCursorOpt::GESTURE_END;
  }
  if (!str.compare(prefixLength, std::string::npos, "UPDATE")) {
    return RepositionCursorOpt::GESTURE_UPDATE;
  }
  if (!str.compare(prefixLength, std::string::npos, "UPDATE_AND_END")) {
    return RepositionCursorOpt::GESTURE_UPDATE_AND_END;
  }
  // Consider warning user if (str != "NEVER") ...
  return RepositionCursorOpt::NEVER;
}

#endif  // UTILS_REPOSITION_CURSOR_H_
