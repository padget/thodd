#ifndef __THODD_LANG_HPP__
#  define __THODD_LANG_HPP__

#  include <thodd/lang_core.hpp>

#  include <thodd/lang_matcher.hpp>
#  include <thodd/lang_rule.hpp>

#  include <thodd/lang_alternative.hpp>
#  include <thodd/lang_follow.hpp>
#  include <thodd/lang_some.hpp>

#  include <thodd/lang_operator.hpp>





/// |----------|
/// |   CORE   |
/// |__________|
///      ||
/// |----------|
/// | MATCHER  |
/// |__________|
///      ||
/// |----------|
/// |   RULE   |
/// |__________|_____________________________
///      ||             ||             ||
/// |----------|   |----------|   |----------|
/// |   SOME   |   |  ALTER   |   |  FOLLOW  |
/// |----------|   |----------|   |----------|


#endif