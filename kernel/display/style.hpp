
#include "display.hpp"

namespace VgaDisplay {

/*
  Style helper for VGA display driver
*/
class Style {
private:
  StyleAttribute m_plain;
  StyleAttribute m_attention;

public:
  constexpr Style(
    StyleAttribute plain = init_style<Color::White, Color::Black>(),
    StyleAttribute attention = init_style<Color::Red, Color::LightGray>())
      : m_plain (plain)
      , m_attention (attention)
  {
  }

  inline StyleAttribute plain() const {
    return m_plain;
  }

  inline StyleAttribute attention() const {
    return m_attention;
  }

};

}
