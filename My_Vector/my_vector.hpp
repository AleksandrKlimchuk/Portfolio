//
// Created by Александр on 06.01.2021.
//

#ifndef PORTFOLIO_MY_VECTOR_H
#define PORTFOLIO_MY_VECTOR_H

#include <memory>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <iostream>

template<typename T>
class Vector
{
public:
    typedef unsigned int u_int;
    typedef Vector<T>::u_int size_type;
    typedef Vector<T>::u_int capacity_type;
    typedef Vector<T>::u_int index_type;

    Vector();
    explicit Vector(capacity_type cap);

    Vector(const Vector<T>& rhs);
    Vector(Vector<T>&& rhs) noexcept;

    Vector<T>& operator=(const Vector& rhs);
    Vector<T>& operator=(Vector&& rhs) noexcept;

    ~Vector() = default;

    size_type size() const noexcept;
    capacity_type capacity() const noexcept;
    bool is_empty() const;

    T& at(index_type index);
    const T& at(index_type) const;

    void push(T item);
    void insert(index_type index, T item);

    T pop();
    void deleteByIndex(index_type index);
    void removeByKey(T item);

    index_type find(T item);
    void print() const;
private:
    const static u_int stdCapacity = 16;

    std::unique_ptr<std::shared_ptr<T>[]> arr_;
    u_int capacity_;
    u_int size_;
    u_int indexForPushElement_;

    void resize(capacity_type newCapacity);
};

template<typename T>
Vector<T>::Vector() :
    arr_{ std::make_unique<std::shared_ptr<T>[]>(stdCapacity) },
    capacity_{ stdCapacity },
    size_{ 0 },
    indexForPushElement_{ 0 }
{}

template<typename T>
Vector<T>::Vector(capacity_type cap) :
    arr_{ std::make_unique<std::shared_ptr<T>[]>(cap) },
    capacity_{ cap },
    size_{ 0 },
    indexForPushElement_{ 0 }
{}

template<typename T>
Vector<T>::Vector(const Vector<T>& rhs) :
    arr_{ std::make_unique<std::shared_ptr<T>[]>(rhs.capacity_) },
    capacity_{ rhs.capacity_ },
    size_{ rhs.size_ },
    indexForPushElement_{ rhs.indexForPushElement_ }
{
    for (u_int i = 0; i < size_; ++i)
    {
        arr_[i] = rhs.arr_[i];
    }
}

template<typename T>
Vector<T>::Vector(Vector<T>&& rhs) noexcept :
    arr_{ std::move(rhs.arr_) },
    capacity_{ rhs.capacity_ },
    size_{ rhs.size_ },
    indexForPushElement_{ rhs.indexForPushElement_ }
{
    rhs.arr_ = std::make_unique<std::shared_ptr<T>[]>(stdCapacity);
    rhs.capacity_ = stdCapacity;
    rhs.size_ = 0;
    rhs.indexForPushElement_ = 0;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
    if (this != &rhs)
    {
        arr_ = std::make_unique<std::shared_ptr<T>[]>(rhs.capacity_);
        capacity_ = rhs.capacity_;
        size_ = rhs.size_;
        indexForPushElement_ = rhs.indexForPushElement_;

        for (u_int i = 0; i < size_; ++i)
        {
            arr_[i] = rhs.arr_[i];
        }
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& rhs) noexcept
{
    if (this != &rhs)
    {
        arr_ = std::move(rhs.arr_);
        capacity_ = rhs.capacity_;
        size_ = rhs.size_;
        indexForPushElement_ = rhs.indexForPushElement_;
        rhs.arr_ = std::make_unique<std::shared_ptr<T>[]>(stdCapacity);
        rhs.capacity_ = stdCapacity;
        rhs.size_ = 0;
        rhs.indexForPushElement_ = 0;
    }
    return *this;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept
{
    return size_;
}

template<typename T>
typename Vector<T>::capacity_type Vector<T>::capacity() const noexcept
{
    return capacity_;
}

template<typename T>
T& Vector<T>::at(index_type index)
{
    if (index >= capacity_)
    {
        throw std::out_of_range("Invalid index to access.\n");
    }
    if (!arr_[index])
    {
        throw std::runtime_error("Invalid index to access.\n");
    }
    return *arr_[index].get();
}

template<typename T>
const T& Vector<T>::at(index_type index) const
{
    if (index >= capacity_)
    {
        throw std::out_of_range("Invalid index to access.\n");
    }
    if (!arr_[index])
    {
        throw std::runtime_error("Invalid index to access.\n");
    }
    return *arr_[index].get();
}

template<typename T>
bool Vector<T>::is_empty() const
{
    return !size_;
}

template<typename T>
void Vector<T>::resize(capacity_type newCapacity)
{
    std::unique_ptr<std::shared_ptr<T>[]> temp = std::make_unique<std::shared_ptr<T>[]>(newCapacity);
    for (u_int i = 0; i < capacity_; ++i)
    {
        temp[i] = arr_[i];
    }
    arr_ = std::move(temp);
    capacity_ = newCapacity;
}

template<typename T>
void Vector<T>::push(T item)
{
    if (size_ == capacity_ || indexForPushElement_ == capacity_)
    {
        resize(capacity_ * 2);
    }
    std::shared_ptr<T> pItem = std::make_shared<T>(item);
    while (arr_[indexForPushElement_])
    {
        ++indexForPushElement_;
    }
    arr_[indexForPushElement_] = pItem;

    while (arr_[indexForPushElement_].get())
    {
        ++indexForPushElement_;
        if (indexForPushElement_ == capacity_)
        {
            break;
        }
    }
    ++size_;

}

template<typename T>
void Vector<T>::insert(index_type index, T item)
{
    if (size_ == capacity_ || indexForPushElement_ == capacity_)
    {
        resize(capacity_ * 2);
    }
    std::shared_ptr<T> pItem = std::make_shared<T>(item);
    if (index >= capacity_)
    {
        double log2Result = log2(static_cast<double>(index));
        double newCapacityExp = floor(log2Result) + 1;
        u_int  newCapacity = static_cast<u_int>(pow(2, newCapacityExp));
        resize(newCapacity);
    }
    if (index <= indexForPushElement_)
    {
        for (u_int i = indexForPushElement_; i > index; --i)
        {
            arr_[i] = arr_[i - 1];
        }
    }
    else {
        u_int shiftCounter = 0;
        while (arr_[index + shiftCounter])
        {
            ++shiftCounter;
        }
        if (shiftCounter)
        {
            if (index + shiftCounter > capacity_)
            {
                u_int newCapacity = capacity_;
                do
                {
                    newCapacity *= 2;
                } while (newCapacity < index + shiftCounter);
                resize(newCapacity);
            }
            for (u_int i = index + shiftCounter; i > index; --i)
            {
                arr_[i] = arr_[i - 1];
            }
        }
    }
    arr_[index] = pItem;
    ++size_;
    while (arr_[indexForPushElement_].get())
    {
        ++indexForPushElement_;
        if (indexForPushElement_ == capacity_)
        {
            break;
        }
    }
}

template<typename T>
T Vector<T>::pop()
{
    if (size_ == 0 || indexForPushElement_ == 0)
    {
        throw std::out_of_range("Vector's head is empty.\n");
    }
    --indexForPushElement_;
    T result = *arr_[indexForPushElement_].get();
    arr_[indexForPushElement_].reset();
    --size_;
    return result;
}

template<typename T>
void Vector<T>::deleteByIndex(Vector::index_type index)
{
    if (index >= capacity_)
    {
        throw std::out_of_range("Too large index.\n");
    }
    if (!arr_[index])
    {
        throw std::runtime_error("Empty element by index.\n");
    }
    u_int shiftCounter = 1;
    while (arr_[index + shiftCounter])
    {
        shiftCounter++;
    }
    if (shiftCounter == 1)
    {
        arr_[index].reset();
    }
    else
    {
        --shiftCounter;
        for (u_int i = index; i < index + shiftCounter; ++i)
        {
            arr_[i] = arr_[i + 1];
        }
        arr_[index + shiftCounter].reset();
    }
    if (index <= indexForPushElement_)
    {
        --indexForPushElement_;
    }
    --size_;
}

template<typename T>
void Vector<T>::removeByKey(T item)
{
    std::unique_ptr<std::shared_ptr<T>[]> temp = std::make_unique<std::shared_ptr<T>[]>(capacity_);
    for (u_int i = 0; i < capacity_; ++i)
    {
        if (arr_[i])
        {
            if (*arr_[i].get() == item)
            {
                --size_;
                if (i < indexForPushElement_)
                {
                    indexForPushElement_ = i;
                }
            }
            else
            {
                temp[i] = arr_[i];
            }
        }
    }
    arr_ = std::move(temp);
}

template<typename T>
typename Vector<T>::index_type Vector<T>::find(T item)
{
    bool isFind = false;
    u_int i;
    for (i = 0; i < capacity_ && !isFind; ++i)
    {
        if (arr_[i] && (*arr_[i].get() == item))
        {
            isFind = true;
        }
    }
    if (!isFind)
    {
        throw std::runtime_error("Empty element by index.\n");
    }
    return i - 1;
}

template<typename T>
void Vector<T>::print() const
{
    for (u_int i = 0; i < capacity_; ++i)
    {
        if (arr_[i])
        {
            std::cout << *arr_[i].get();
        }
        else
        {
            std::cout << 'e';
        }
        std::cout << ' ';
    }
    std::cout << '\n';
}


#endif //PORTFOLIO_MY_VECTOR_H
