#pragma once

#include <memory>
#include <iterator>

namespace lib
{

namespace detail
{

template<typename T>
struct Node
{
    Node() = default;
    ~Node()
    {
        if(next) next->prev = prev;
        if(prev) prev->next = next;
    };
    T* ptr = nullptr;
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;
};

template<typename T, typename N>
class Custom_iterator : std::iterator<std::forward_iterator_tag, T>
{
public:
    explicit Custom_iterator(N node) : m_node(node) {}
    explicit Custom_iterator() {}
    T& operator*() const
    {
        return *(m_node->ptr);
    }
    T* operator->()
    {
        return m_node ? m_node->ptr : nullptr;
    }
    Custom_iterator<T, N>& operator++()
    {
        if(m_node)
            m_node = m_node->next;
        return *this;
    }
    Custom_iterator<T, N> operator++(int)
    {
        Custom_iterator<T, N> tmp = *this;
        if(m_node)
            m_node = m_node->next;
        return tmp;
    }
    friend bool operator==(const Custom_iterator<T, N>& a, const Custom_iterator<T, N>& b)
    {
        return a.m_node == b.m_node;
    }
    friend bool operator!=(const Custom_iterator<T, N>& a, const Custom_iterator<T, N>& b)
    {
        return a.m_node != b.m_node;
    }
private:
    N m_node = nullptr;
};

}

template<typename T, typename Allocator = std::allocator<T>>
class custom_container
{
    using node_allocator_traits = typename std::allocator_traits<Allocator>::template rebind_traits<detail::Node<T>>;
    using node_allocator_type = typename node_allocator_traits::allocator_type;
    using node_pointer = typename node_allocator_traits::pointer;

public:

    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using iterator = typename detail::Custom_iterator<T, node_pointer>;

    custom_container()
    {
    }

    ~custom_container()
    {
        while(m_first)
        {
            node_pointer next_node = m_first->next;

            m_allocator.destroy(m_first->ptr);
            m_allocator.deallocate(m_first->ptr, 1);

            m_node_allocator.destroy(m_first);
            m_node_allocator.deallocate(m_first, 1);

            m_first = next_node;
        }
    }

    void push_back(const T& val)
    {
        pointer ptr = m_allocator.allocate(1);
        m_allocator.construct(ptr, val);

        node_pointer node_ptr = m_node_allocator.allocate(1);
        m_node_allocator.construct(node_ptr);

        node_ptr->ptr = ptr;

        if(!m_first)
        {
            m_first = node_ptr;
            return;
        }

        if(!m_last)
        {
            m_last = node_ptr;
            m_first->next = m_last;
            return;
        }

        m_last->next = node_ptr;
        node_ptr->prev = m_last;
        m_last = m_last->next;
    }

    iterator begin() const noexcept
    {
        return iterator(m_first);
    }

    iterator end() const noexcept
    {
        return iterator(nullptr);
    }

private:
    node_pointer m_first = nullptr;
    node_pointer m_last = nullptr;
    allocator_type m_allocator;
    node_allocator_type m_node_allocator;
};

}