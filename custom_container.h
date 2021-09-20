#pragma once

#include <memory>
#include <iterator>

namespace lib
{

template<class T, class Allocator = std::allocator<T>>
class custom_container
{
public:

    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using pointer = typename std::allocator_traits<Allocator>::pointer;

private:

    template<class V>
    struct Node
    {
        Node() = default;
        ~Node()
        {
            if(next) next->prev = prev;
            if(prev) prev->next = next;
        };

        V* ptr = nullptr;
        Node<V>* prev = nullptr;
        Node<V>* next = nullptr;
    };

public:

    struct Custom_iterator : std::iterator<std::forward_iterator_tag, T>
    {
        explicit Custom_iterator(Node<T>* node = nullptr) : m_node(node) {}
        T& operator*() const
        {
            return *(m_node->ptr);
        }
        T* operator->()
        {
            return m_node ? m_node->ptr : nullptr;
        }
        Custom_iterator& operator++()
        {
            if(m_node)
                m_node = m_node->next;
            return *this;
        }
        Custom_iterator operator++(int)
        {
            Custom_iterator tmp = *this;
            if(m_node)
                m_node = m_node->next;
            return tmp;
        }
        friend bool operator==(const Custom_iterator& a, const Custom_iterator& b)
        {
            return a.m_node == b.m_node;
        }
        friend bool operator!=(const Custom_iterator& a, const Custom_iterator& b)
        {
            return a.m_node != b.m_node;
        }
    private:
        Node<T>* m_node;
    };

    using iterator = Custom_iterator;

    custom_container()
    {
    }

    ~custom_container()
    {
        while(m_first)
        {
            Node<T>* next_node = m_first->next;
            m_allocator.destroy(m_first->ptr);
            m_allocator.deallocate(m_first->ptr, 1);
            delete m_first;
            m_first = next_node;
        }
    }

    void push_back(const T& val)
    {
        pointer ptr = m_allocator.allocate(1);
        m_allocator.construct(ptr, val);

        if(m_first == m_last)
        {
            m_first = new Node<T>();
            m_first->ptr = ptr;
            m_last = new Node<T>();
            m_last->prev = m_first;
            m_first->next = m_last;
        }
        else
        {
            m_last->ptr = ptr;
            m_last->next = new Node<T>();
            m_last->next->prev = m_last;
            m_last = m_last->next;
        }
    }

    iterator begin() const noexcept
    {
        return iterator(m_first);
    }

    iterator end() const noexcept
    {
        return iterator(m_last);
    }

private:
    Node<T>* m_first = nullptr;
    Node<T>* m_last = nullptr;
    allocator_type m_allocator;
};

}