/**
 * SOURCE: https://discord.com/channels/515453022097244160/686661689894240277/1057762589205086248
 * Jeremiah on 3dgep.com Discord server
 */

#pragma once

#include <chrono>

namespace Tmpl8
{
    class Timer
    {
    public:
        Timer() noexcept;

        void tick() noexcept;
        void reset() noexcept;

        double elapsedSeconds() const noexcept;
        double elapsedMilliseconds() const noexcept;
        double elapsedMicroseconds() const noexcept;

        double totalSeconds() const noexcept;
        double totalMilliseconds() const noexcept;
        double totalMicroseconds() const noexcept;

        void limitFPS(int fps) const noexcept;
        void limitFPS(double seconds) const noexcept;
        void limitFPS(const std::chrono::high_resolution_clock::duration& duration) const noexcept;

        template<class Rep, class Period>
        constexpr void limitFPS(const std::chrono::duration<Rep, Period>& duration) const noexcept
        {
            limitFPS(std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(duration));
        }

    private:
        std::chrono::high_resolution_clock::time_point t0, t1;
        mutable std::chrono::high_resolution_clock::time_point beginFrame;

        double elapsedTime;
        double totalTime;
    };
}