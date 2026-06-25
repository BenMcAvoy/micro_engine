#pragma once

#include <optional>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <iostream>

namespace micro::components
{
    template <typename T>
    class pool;

    // handle to a component in a pool
    template <typename T>
    struct handle
    {
        std::uint32_t index_;
        std::uint32_t generation_;

        T *get(pool<T> &pool)
        {
            return pool.get(*this);
        }
    };

    template <typename T>
    class pool
    {
    public:
        // create a new component in the pool and return a handle to it
        template <typename... Args>
        handle<T> create(Args &&...args)
        {
            std::uint32_t index;
            std::uint32_t generation;

            if (!free_indices_.empty()) // there are free indices available, reuse one
            {
                index = free_indices_.back();
                free_indices_.pop_back(); // remove the index from the free list (we're now using it)
                generation = generations_[index];
            }
            else
            {
                index = static_cast<std::uint32_t>(data_.size());
                data_.emplace_back(std::forward<Args>(args)...);
                generations_.emplace_back(0);
                generation = 0;
            }

            return handle<T>{index, generation};
        }

        // destroy a component in the pool, invalidating its handle
        void destroy(handle<T> handle)
        {
            // retrieve the index and generation from the handle
            std::uint32_t index = handle.index_;
            std::uint32_t generation = handle.generation_;

            // check if the handle is valid
            if (index >= data_.size() || generations_[index] != generation)
            {
                throw std::runtime_error("Invalid handle");
            }

            // increment the generation to invalidate existing handles
            // (it will mismatch with the generation stored in the handle, making it invalid)
            generations_[index]++;

            // add the index to the free list for reuse
            free_indices_.push_back(index);
        }

        // get a reference to the component associated with the handle
        // returns nullptr if the handle is invalid
        T *get(handle<T> handle)
        {
            std::uint32_t index = handle.index_;
            std::uint32_t generation = handle.generation_;

            if (index >= data_.size() || generations_[index] != generation)
            {
                return nullptr; // invalid handle
            }

            return &data_[index].value();
        }

    private:
        // contiguous storage for components (cache friendly)
        std::vector<std::optional<T>> data_;

        // state tracking for pool objects
        std::vector<std::uint32_t> generations_;
        std::vector<std::uint32_t> free_indices_;
    };
}