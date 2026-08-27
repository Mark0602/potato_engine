#ifndef PRANDOM_H
#define PRANDOM_H

#include <random>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <initializer_list>
#include <type_traits>
#include "debug.h"

namespace prandom {
    using rd = std::random_device;
    using mt = std::mt19937;

    inline rd& device() {
        static rd rd_instance;
        return rd_instance;
    }

    inline mt& engine() {
        static mt eng(device()());
        return eng;
    }

    inline std::size_t random_weighted_index(const std::vector<float>& weights, Logger* logger = nullptr) {
        if (weights.empty()) {
            if (logger) {
                logger->log(Log_Level::ERROR, "prandom", "Cannot choose from an empty weight list");
            }
            throw std::runtime_error("Cannot choose from an empty weight list");
        }

        bool has_positive_weight = false;
        for (const float weight : weights) {
            if (!std::isfinite(weight) || weight < 0.0f) {
                if (logger) {
                    logger->log(Log_Level::ERROR, "prandom", "Weights must be finite and non-negative");
                }
                throw std::runtime_error("Weights must be finite and non-negative");
            }
            has_positive_weight = has_positive_weight || weight > 0.0f;
        }
        if (!has_positive_weight) {
            throw std::runtime_error("At least one weight must be positive");
        }

        std::discrete_distribution<std::size_t> distribution(
            weights.begin(), weights.end()
        );
        return distribution(engine());
    }

    template<typename T>
    inline T random_range(T min, T max) {
        static_assert(std::is_integral_v<T>, "random_range requires an integral type");
        if (min > max) throw std::runtime_error("Random range minimum exceeds maximum");
        std::uniform_int_distribution<T> dist(min, max);
        return dist(engine());
    }

    template<typename T>
    inline T random_range_weighted(T min, T max, const std::vector<float>& weight) {
        static_assert(
            std::is_integral_v<T>,
            "random_range_weighted requires an integral type"
        );
        if (min > max) throw std::runtime_error("Random range minimum exceeds maximum");

        const std::size_t choice_count =
            static_cast<std::size_t>(max - min) + 1;
        if (weight.size() != choice_count) {
            throw std::runtime_error(
                "The number of weights must match the weighted random range"
            );
        }

        return static_cast<T>(
            min + static_cast<T>(random_weighted_index(weight))
        );
    }

    template<typename T>
    inline T random_choice(const std::vector<T>& choices) {
        if (choices.empty()) throw std::runtime_error("Cannot choose from an empty vector");
        std::uniform_int_distribution<std::size_t> dist(0, choices.size() - 1);
        return choices[dist(engine())];
    }

    template<typename T>
    inline T random_choice_weighted(const std::vector<T>& choices, const std::vector<float>& weight) {
        if (choices.empty()) throw std::runtime_error("Cannot choose from an empty vector");
        if (choices.size() != weight.size()) throw std::runtime_error("Choices and weights must be the same size");
        return choices[random_weighted_index(weight)];
    }

    template<typename T>
    inline T random_choice_weighted(std::initializer_list<T> choices,
                                    std::initializer_list<float> weights) {
        return random_choice_weighted(
            std::vector<T>(choices),
            std::vector<float>(weights)
        );
    }
}

#endif
