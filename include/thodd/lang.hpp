#ifndef __THODD_LANG_HPP__
#  define __THODD_LANG_HPP__

#  include <thodd/lang_core.hpp>

#  include <thodd/lang_regex.hpp>
#  include <thodd/lang_word.hpp>

#  include <thodd/lang_alternative.hpp>
#  include <thodd/lang_follow.hpp>
#  include <thodd/lang_some.hpp>





/// |----------|
/// |   CORE   |
/// |__________|
///      ||
/// |----------|
/// | REGEX  |
/// |__________|
///      ||
/// |----------|
/// |   WORD   |
/// |__________|_____________________________
///      ||             ||             ||
/// |----------|   |----------|   |----------|
/// |   SOME   |   |  ALTER   |   |  FOLLOW  |
/// |----------|   |----------|   |----------|


#endif