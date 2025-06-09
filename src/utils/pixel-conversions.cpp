double mmToDpi(double mm) {
  constexpr double mmInOneInch = 25.4;  // 1 inch == 25.4 mm
  double inches = mm / mmInOneInch;
  double dpi = (inches * 1000);
  return dpi;
}
