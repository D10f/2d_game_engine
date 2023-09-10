#ifndef _POOL_H
#define _POOL_H

#include <cstddef>
#include <cstdint>
#include <vector>

/**
 * Acts as an abstract class that can ge referenced as a type.
 */
class IPool
{
  public:
    virtual ~IPool() = default;

    IPool &operator=(const IPool &other) = default;
};

/**
 * Simple wrapper class a around std::vector
 */
template <typename T> class Pool : public IPool
{
  private:
    std::vector<T> m_data;

  public:
    Pool(size_t size = 100)
    {
        m_data.resize(size);
    }

    ~Pool() override = default;

    [[nodiscard]] bool isEmpty() const
    {
        return m_data.empty();
    }

    [[nodiscard]] uint32_t size() const
    {
        return m_data.size();
    }

    void resize(uint32_t newSize)
    {
        m_data.resize(newSize);
    }

    void clear()
    {
        m_data.clear();
    }

    void add(const T &obj)
    {
        m_data.push_back(obj);
    }

    void set(uint32_t idx, const T &obj)
    {
        m_data[idx] = obj;
    }

    T &get(uint32_t idx)
    {
        return m_data.at(idx);
    }

    T &operator[](uint32_t idx)
    {
        return get(idx);
    }
};

#endif
