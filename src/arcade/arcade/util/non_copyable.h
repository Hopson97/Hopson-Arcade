#pragma once

namespace arcade {
    struct NonCopyable {
        NonCopyable() = default;
        NonCopyable& operator=(const NonCopyable&) = delete;
        NonCopyable(const NonCopyable&) = delete;
    };
} // namespace arcade