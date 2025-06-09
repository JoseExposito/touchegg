#ifndef UTILS_REPOSITION_CURSOR_H_
#define UTILS_REPOSITION_CURSOR_H_

// Bitmask representing options for when cursor should be repositioned.
enum RepositionCursorOpt {
  NEVER				= 0b00,	// 0
  GESTURE_END			= 0b01,	// 1
  GESTURE_UPDATE		= 0b10	// 2
  //GESTURE_UPDATE_AND_END	= 0b11	// 3
};

//bool operator!(RepositionCursorOpt e) {
//  return e == static_cast<RepositionCursorOpt>(0);
//}
//bool operator!(RepositionCursorOpt e) {
//  return e == static_cast<RepositionCursorOpt>(0);
//}
//inline RepositionCursorOpt operator|(RepositionCursorOpt a, RepositionCursorOpt b) {
//    return static_cast<RepositionCursorOpt>(static_cast<int>(a) | static_cast<int>(b));
//}
//inline RepositionCursorOpt operator&(RepositionCursorOpt a, RepositionCursorOpt b) {
//    return static_cast<RepositionCursorOpt>(static_cast<int>(a) & static_cast<int>(b));
//}
//inline RepositionCursorOpt operator+(RepositionCursorOpt a, RepositionCursorOpt b) {
//    return static_cast<RepositionCursorOpt>(static_cast<int>(a) + static_cast<int>(b));
//}

/*class CursorPosition {
  public:
    // Absolute position on display in millimeters.
    double x;
    double y;

    bool isDefined();
};*/

#endif  // UTILS_REPOSITION_CURSOR_H_
