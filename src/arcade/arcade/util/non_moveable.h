#pragma once

namespace arcade {
    struct NonMovable {
        NonMovable() = default;
        NonMovable& operator=(NonMovable&&) = delete;
        NonMovable(NonMovable&&) = delete;
    };
} // namespace arcade