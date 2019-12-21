// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_KEYSTATE_H
#define NOVELRT_KEYSTATE_H
#include <stdint.h>

namespace NovelRT {
  enum class KeyState : uint32_t {
    Idle = 0,
    KeyDown = 1,
    KeyDownHeld = 2,
    KeyUp = 3,
  };
}
#endif // !NOVELRT_KEYSTATE_H

