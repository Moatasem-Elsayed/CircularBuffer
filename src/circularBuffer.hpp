#pragma once
#include <array>
#include <cstdint>
#include <iterator>
#include <sstream>
#include <stdexcept>
template <typename T, int size> class CircularBuffer {
public:
  using container = std::array<T, size>;
  CircularBuffer()
      : m_head(0), m_tail(0), m_currentsize(0){

                              };
  void push_back(T value) {
    // update tail
    if (m_tail >= size) {
      m_tail = 0;
    }
    // update container
    m_container.at(m_tail) = value;
    // update head
    if (m_tail == m_head && m_currentsize > 0) {
      m_head++;
      if (m_head >= size) {
        m_head = 0;
      }
    }
    m_tail++;

    // update size
    m_currentsize++;
    if (m_currentsize > size) {
      m_currentsize = size;
    }
  }
  void pop() {
    // update head
    if (m_currentsize == 0) {
      throw std::runtime_error("pop failed due to size");
    }
    m_head++;
    if (m_head >= size) {
      m_head = 0;
    }
    if (m_head == m_tail + 1 && m_currentsize == 1) {
      m_head--;
    }
    m_currentsize--;
  }
  T const &head() { return m_container.at(m_head); }
  T const &tail() { return m_container.at(m_tail); }
  bool empty() const { return (m_currentsize <= 0); }
  int32_t getsize() const { return m_currentsize; }

  template <typename Buffer, typename Iterator> class CircularBufferIterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = typename Buffer::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = typename Buffer::value_type *;
    using reference = typename Buffer::value_type &;

    CircularBufferIterator() : m_done(true) {}

    CircularBufferIterator(Buffer &buf, Iterator begin)
        : m_buf(buf), m_begin(begin), m_cursor(begin), m_done(false) {}

    CircularBufferIterator(Buffer &buf, Iterator begin, bool done)
        : m_buf(buf), m_begin(begin), m_cursor(begin), m_done(done) {}

    reference operator*() const { return *m_cursor; }

    pointer operator->() const { return m_cursor; }

    CircularBufferIterator &operator++() {
      ++m_cursor;
      if (m_cursor == m_buf.end()) {
        m_cursor = m_buf.begin();
      }
      m_done = m_cursor == m_begin;

      return *this;
    }

    CircularBufferIterator operator++(int) = delete;

    bool operator==(const CircularBufferIterator &it) const {
      if (m_done && it.m_done) {
        return true;
      } else if (!m_done && !it.m_done) {
        return (this->m_cursor == it.m_cursor);
      }

      return false;
    }

    bool operator!=(const CircularBufferIterator &it) const {
      return !(*this == it);
    }

  private:
    Buffer &m_buf;
    const Iterator m_begin;
    Iterator m_cursor;
    bool m_done;
  };

  typedef CircularBufferIterator<container, typename container::iterator>
      iterator;

  iterator begin() {
    unsigned int offset = m_head % size;
    return CircularBuffer::iterator(m_container, m_container.begin() + offset);
  }

  iterator end() {
    unsigned int offset = m_tail + 1 % size;
    return CircularBuffer::iterator(m_container, m_container.begin() + offset,
                                    getsize() >= size);
  }

private:
  container m_container{};
  int32_t m_head;
  int32_t m_tail;
  int32_t m_currentsize;
};