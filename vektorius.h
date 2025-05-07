// Vector.h
#pragma once
#include <algorithm>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    // Konstruktoriai
    Vector() : data_(nullptr), size_(0), capacity_(0) {}
    Vector(size_t count, const T& value = T()) : data_(new T[count]), size_(count), capacity_(count) {
        std::fill(data_, data_ + count, value);
    }
    Vector(const Vector& other) : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }
    Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }
    Vector(std::initializer_list<T> init) : data_(new T[init.size()]), size_(init.size()), capacity_(init.size()) {
        std::copy(init.begin(), init.end(), data_);
    }

    // Destruktorius
    ~Vector() {
        delete[] data_;
    }

    // Priskyrimo operatoriai
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            data_ = new T[other.capacity_];
            size_ = other.size_;
            capacity_ = other.capacity_;
            std::copy(other.data_, other.data_ + other.size_, data_);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

    // Prieiga prie elementų
    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    T& at(size_t index) {
        if (index >= size_)
            throw std::out_of_range("Indeksas už ribų");
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_)
            throw std::out_of_range("Indeksas už ribų");
        return data_[index];
    }

    // Dydžio ir talpos funkcijos
    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_)
            reallocate(new_capacity);
    }

    void resize(size_t new_size, const T& value = T()) {
        if (new_size > capacity_)
            reallocate(new_size);
        if (new_size > size_)
            std::fill(data_ + size_, data_ + new_size, value);
        size_ = new_size;
    }

    void push_back(const T& value) {
        if (size_ == capacity_)
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = value;
    }

    void pop_back() {
        if (size_ > 0)
            --size_;
    }

    void clear() {
        size_ = 0;
    }

    T& front() {
        return data_[0];
    }

    const T& front() const {
        return data_[0];
    }

    T& back() {
        return data_[size_ - 1];
    }

    const T& back() const {
        return data_[size_ - 1];
    }

    T* begin() {
        return data_;
    }

    T* end() {
        return data_ + size_;
    }

    const T* begin() const {
        return data_;
    }

    const T* end() const {
        return data_ + size_;
    }
};
