/**
 * @file Vector.h
 * @brief Dinaminis konteineris, imituojantis std::vector elgseną.
 */
#pragma once
#include <algorithm>
#include <stdexcept>
#include <initializer_list>

/**
 * @brief Šabloninis konteineris Vector.
 * 
 * Teikia dinaminio masyvo funkcionalumą: 
 * auganďios talpos valdymą, 
 * elementų prieigą, iteravimą, trynimą ir kt.
 * 
 * @tparam T Elementų tipas
 */

template <typename T>
class Vector {
private:
    T* data_;       ///< Rodo į saugomų elementų masyvą
    size_t size_;   ///< Dabartinis elementų skaičius
    size_t capacity_;   ///< Dabartinė rezervuota talpa


    /**
     * @brief Padidina talpą ir perkelia esamus elementus.
     * @param new_capacity Nauja talpa
     */
    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
        /** @brief Numatytoji konstruktorius, sukuria tuščią kolekciją */
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

     /**
     * @brief Konstruktorius su pradiniu dydžiu ir reikšme
     * @param count Pradinis elementų skaičius
     * @param value Reikšmė, kuria užpildyti
     */

    Vector(size_t count, const T& value = T()) : data_(new T[count]), size_(count), capacity_(count) {
        std::fill(data_, data_ + count, value);
    }

    /** @brief Kopijavimo konstruktorius */
    Vector(const Vector& other) : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }
    /** @brief Perkėlimo konstruktorius */
    Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }
     /**
     * @brief Inicijuoja vektorių naudojant sąrašą
     * @param init Inicializavimo sąrašas
     */
    Vector(std::initializer_list<T> init) : data_(new T[init.size()]), size_(init.size()), capacity_(init.size()) {
        std::copy(init.begin(), init.end(), data_);
    }

    /** @brief Destruktorius atlaisvina atmintį */
    ~Vector() {
        delete[] data_;
    }

    /** @brief Kopijavimo priskyrimo operatorius */
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
    /** @brief Perkėlimo priskyrimo operatorius */
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

    /**
     * @brief Prieiga prie elemento pagal indeksą
     * @param index Indeksas
     * @return Nuoroda į elementą
     */
    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    /**
     * @brief Saugus prieigos metodas su patikrinimu
     * @param index Indeksas
     * @return Nuoroda į elementą
     * @throws std::out_of_range Jei indeksas netinkamas
     */
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

    /** @brief Grąžina elementų skaičių */
    size_t size() const {
        return size_;
    }
    /** @brief Grąžina rezervuotą talpą */
    size_t capacity() const {
        return capacity_;
    }
    /** @brief Tikrina ar konteineris tuščias */
    bool empty() const {
        return size_ == 0;
    }
    /**
     * @brief Rezervuoja nurodytą talpą
     * @param new_capacity Nauja talpa
     */
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_)
            reallocate(new_capacity);
    }
    /**
     * @brief Keičia konteinerio dydį
     * @param new_size Naujas dydis
     * @param value Reikšmė, kuria pildyti naujus elementus
     */
    void resize(size_t new_size, const T& value = T()) {
        if (new_size > capacity_)
            reallocate(new_size);
        if (new_size > size_)
            std::fill(data_ + size_, data_ + new_size, value);
        size_ = new_size;
    }
    /**
     * @brief Prideda elementą į pabaigą
     * @param value Pridedamas elementas
     */
    void push_back(const T& value) {
        if (size_ == capacity_)
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = value;
    }
    /**
     * @brief Pašalina vieną elementą pagal iteratoriaus poziciją
     * @param pos Rodyklė į trinamą elementą
     * @return Rodyklė į kitą elementą
     */
    T* erase(T* pos) {
        if (pos < data_ || pos >= data_ + size_)
            throw std::out_of_range("Iteratorius už ribų");

        size_t index = pos - data_;
        for (size_t i = index; i < size_ - 1; ++i)
            data_[i] = std::move(data_[i + 1]);

        --size_;
        return data_ + index;
    }

    /**
     * @brief Pašalina elementų intervalą
     * @param first Pradžia
     * @param last Pabaiga
     */
    void erase(T* first, T* last) {
        if (first >= data_ && last <= data_ + size_ && first <= last) {
            std::move(last, data_ + size_, first);
            size_ -= (last - first);
        }
    }
    /** @brief Pašalina paskutinį elementą */
    void pop_back() {
        if (size_ > 0)
            --size_;
    }
    /** @brief Išvalo visus elementus */
    void clear() {
        size_ = 0;
    }
    /** @brief Grąžina pirmą elementą */
    T& front() {
        return data_[0];
    }

    const T& front() const {
        return data_[0];
    }
     /** @brief Grąžina paskutinį elementą */
    T& back() {
        return data_[size_ - 1];
    }

    const T& back() const {
        return data_[size_ - 1];
    }
    /** @brief Grąžina iteratorių į pirmą elementą */
    T* begin() {
        return data_;
    }

    T* end() {
        return data_ + size_;
    }

    const T* begin() const {
        return data_;
    }
    /** @brief Grąžina iteratorių į po paskutinio elemento vietą */
    const T* end() const {
        return data_ + size_;
    }
};
