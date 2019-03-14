#ifndef VEC_H
#define VEC_H
#pragma once



template <class T>
class Vec
{
    T *data;
    int size;
    int cap;
public:
    Vec(int);
    Vec(void);
    Vec(Vec&);
    Vec operator=(const Vec&);
    bool operator==(const Vec&);
    T get(const int &i);
    void set(const int &i, T val);
    void set(Vec<T> &v);
    int Capacity() const;
    int Size() const;
    T& operator [](int);
    bool operator==(int);
    void push_back(T);
    void clear();
    void create(const int &i);
    void remove(const int &i);
    void resize(const int &n);
    ~Vec(void);

};


template <class  T>
Vec<T>::Vec(void)
{
    size = 0;
    cap = 1;
    data = new T[1];
}

template <class  T>
Vec<T>::Vec(int n)
{
    size = 0;
    cap = n;
    data = new T[n];
}

template <class  T>
Vec<T>::~Vec(void)
{
    delete[] data;
}

template <class  T>
int Vec<T>::Size(void) const
{
    return size;
}

template <class  T>
T& Vec<T>::operator[](int i)
{
    return data[i];
}

template <class T>
Vec<T> Vec<T>::operator=(const Vec&a)
{
    if (this->size)
        delete[] this->data;
    this->size = a.size;
    this->cap = a.cap;
    this->data = new T[this->cap];
    for (int i = 0; i != this->size; ++i) {
        this->data[i] = a.data[i];
    }
    return *this;
}

template <class T>
bool Vec<T>::operator==(const Vec&v)
{
    if (this->size == v.size)
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->data[i] != v.data[i])
                return false;
        }
        return true;
    }
    else {
        return  false;
    }
}

template <class T>
Vec<T>::Vec(Vec&a) {
    this->size = a.Size();
    this->cap = a.Capacity();
    this->data = new T[this->cap];
    for (int i = 0; i != a.size; ++i) {
        this->data[i] = a.data[i];
    }
}

template <class T>
void Vec<T>::push_back(T val) {

    int s = this->size, c = this->cap;
    if (s >= c) {
        T* newdata;
        cap = cap * 2;
        newdata = new T[cap];
        for (int i = 0; i < size; i++)
            newdata[i] = data[i];
        delete[] data;
        data = newdata;
    }
    data[size] = val;
    size++;
}

template <class  T>
int Vec<T>::Capacity() const
{
    return cap;
}

template <class  T>
void Vec<T>::remove(const int &i)
{
    T* newdata = new T[cap];
    bool f = false;

    for (int j = 0; j < this->size; j++)
    {
        if (j == i)
        {
            f = true;
        }
        if (f)
        {
            newdata[j - 1] = this->data[j];
        }
        else {
            newdata[j] = this->data[j];
        }
    }
    this->size -= 1;
    delete[] this->data;
    this->data = newdata;
}

template <class  T>
void Vec<T>::resize(const int &n)
{
    T* newdata = new T[n];
    this->cap = n;
    this->size = n > this->size ? this->size : n;
    for (int i = 0; i < this->size; i++)
    {
        newdata[i] = this->data[i];
    }
    delete[] this->data;
    this->data = newdata;
}

template <class  T>
void Vec<T>::clear()
{
    delete[] this->data;
    this->size = 0;
    this->cap = 1;
    this->data = new T[1];
}

template <class  T>
void Vec<T>::create(const int &i) {
    if (this->data)
        delete[] this->data;
    size = 0;
    cap = i;
    data = new T[i];
}

template <class  T>
T Vec<T>::get(const int &i)
{
    T ret = this->data[i];
    return ret;
}

template <class  T>
void Vec<T>::set(const int &i, T val)
{
    this->data[i] = val;
}


template <class  T>
void Vec<T>::set(Vec<T> &v)
{
    delete[] this->data;
    this->size = v.Size();
    this->cap = v.Capacity();
    this->data = new T[this->cap];
    for (int i = 0; i < this->size; i++)
    {
        this->data[i] = v[i];
    }
}



#endif // VEC_H
