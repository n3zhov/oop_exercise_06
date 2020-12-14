//
// Created by nikita on 30.11.2020.
//

#ifndef OOP_EXERCISE_06_ALLOCATOR_HPP
#define OOP_EXERCISE_06_ALLOCATOR_HPP
#include <list>
#include <cinttypes>
#include <cstdlib>
#include <queue>

template <typename T, std::size_t BLOCK_SIZE>
struct CustomAllocator {
    static_assert(BLOCK_SIZE != 0, "the block must be above zero");

    using value_type = T;
    using pointer = T *;
    using size_type = std::size_t;
    CustomAllocator(): _used_blocks(nullptr), _free_blocks(){}

    template<typename U>
    struct rebind{
        using other = CustomAllocator<U, BLOCK_SIZE>;
    };

    pointer allocate(size_type count = 1){
        if(_used_blocks == nullptr){
            _used_blocks = (pointer)malloc(BLOCK_SIZE * sizeof(value_type));
            for (size_type i = 0; i < BLOCK_SIZE; ++i)
            {
                _free_blocks.push(_used_blocks + i);
            }
        }
        for (int i = 0; i < count + 1; ++i){
            _free_blocks.pop();
        }
        return _used_blocks;
    }

    void deallocate(pointer ptr, size_type count = 1){
        for (int i = 0; i < count; ++i)
        {
            _free_blocks.push(ptr + i);
        }
    }

    bool empty(){
        return _free_blocks.empty();
    }

    int32_t size(){
        return _free_blocks.size();
    }

    ~CustomAllocator(){
        while(!_free_blocks.empty()){
            _free_blocks.pop();
        }

        free(_used_blocks);
    }

    template <typename U, typename... Args>
    void construct(U *p, Args &&... args)
    {
        new (p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p)
    {
        p->~T();
    }

    pointer _used_blocks = nullptr;
    std::queue<pointer> _free_blocks;
};

#endif //OOP_EXERCISE_06_ALLOCATOR_HPP
