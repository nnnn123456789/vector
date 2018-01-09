#pragma once
#include <cstdlib>
#include <cstdarg>
#include <string>

template<typename _Elem, int n>
class vector;

enum class _iterflag
{
    l = 1,
    cl = 1,
    r = 3,
    cr = 3
};

template<typename _Elem, int n>
class iterator
{
protected:
    typedef vector<_Elem, n> _BaseType;
    _iterflag flag;
    typedef _Elem* _pElem;
    const _Elem* current;
    iterator();
public:
    iterator(_iterflag, const _Elem*);
    ~iterator();
    int operator++();
    operator _Elem*();
};

template<typename _Elem, int n>
class vector
{
protected:
    _iterflag iterflag = _iterflag::cl;
    const static int length = n;
    const static int _sizeofElem = sizeof(_Elem);
    typedef vector<_Elem, n> _Myt;
    _Elem* head;

public:
    vector();
    ~vector();
    vector(int l, ...);
    vector(const vector&);
    vector(vector&&);
    const vector& operator=(const vector&);
    vector&& operator=(vector&&);
    iterator<_Elem, n> begin()const;
    iterator<_Elem, n> end()const;
    _Elem& operator[](int r);
    int Setiterflag(const char*);
    vector& operator()(const char*);
};

template<typename _Elem, int n>
vector<_Elem, n>::vector()
{
    head = reinterpret_cast<_Elem*>(calloc(length, _sizeofElem));
}

template<typename _Elem, int n>
vector<_Elem, n>::~vector()
{
    if (nullptr != head)
        free(head);
}

template<typename _Elem, int n>
vector<_Elem, n>::vector(int l, ...)
{
    va_list vp;

    head = reinterpret_cast<_Elem*>(calloc(length, _sizeofElem));
    if (nullptr == head)
    {
        return;
    }
    va_start(vp, l);
    for (int i = 0; i < l && i < length; i++)
    {
         head[i] = va_arg(vp, _Elem);
    }
    va_end(vp);
}

template<typename _Elem, int n>
inline vector<_Elem, n>::vector(const vector & r)
{
    head = reinterpret_cast<_Elem*>(calloc(length, _sizeofElem));
    if (nullptr != head)
    {
        memcpy(head, r.head, length * _sizeofElem);
    }
    return *this;
}

template<typename _Elem, int n>
inline vector<_Elem, n>::vector(vector && r)
{
    this->head = r.head;
    r.head = nullptr;
    return *this;
}

template<typename _Elem, int n>
inline const vector<_Elem, n> & vector<_Elem, n>::operator=(const vector &)
{
    if(nullptr == this->head)
        this->head = reinterpret_cast<_Elem*>(calloc(length, _sizeofElem));
    if (nullptr != head)
    {
        memcpy(head, r.head, length * _sizeofElem);
    }
    return *this;
}

template<typename _Elem, int n>
inline vector<_Elem, n> && vector<_Elem, n>::operator=(vector &&)
{
    if (nullptr != this->head)
    {
        free(this->head);
    }
    this->head = r.head;
    r.head = nullptr;
    return *this;
}

template<typename _Elem, int n>
inline iterator<_Elem, n> vector<_Elem, n>::begin() const
{
    if (_iterflag::l == iterflag) 
    {
        return iterator<_Elem, n>(_iterflag::l, head);
    }
    else if (_iterflag::r == iterflag)
    {
        return iterator<_Elem, n>(_iterflag::r, head + length - 1);
    }
    else
    {
        return iterator<_Elem, n>(_iterflag::r, nullptr);
    }
}

template<typename _Elem, int n>
inline iterator<_Elem, n> vector<_Elem, n>::end() const
{
    if (_iterflag::l == iterflag)
    {
        return iterator<_Elem, n>(_iterflag::l, head + length);
    }
    else if (_iterflag::r == iterflag)
    {
        return iterator<_Elem, n>(_iterflag::r, head - 1);
    }
    else
    {
        return iterator<_Elem, n>(_iterflag::r, nullptr);
    }
}

template<typename _Elem, int n>
inline _Elem & vector<_Elem, n>::operator[](int r)
{
    return head[r % length];
}

template<typename _Elem, int n>
int vector<_Elem, n>::Setiterflag(const char * _Mode)
{
    std::string flag = _Mode;
    if ("l" == flag)
    {
        this->iterflag = _iterflag::l;
        return 0;
    }
    else if ("cl" == flag)
    {
        this->iterflag = _iterflag::cl;
        return 0;
    }
    else if ("r" == flag)
    {
        this->iterflag = _iterflag::r;
        return 0;
    }
    else if ("cr" == flag)
    {
        this->iterflag = _iterflag::cr;
        return 0;
    }
    return 1;
}

template<typename _Elem, int n>
inline vector<_Elem, n>& vector<_Elem, n>::operator()(const char * _Mode)
{
    this->Setiterflag(_Mode);
    return *this;
}

template<typename _Elem, int n>
iterator<_Elem, n>::iterator()
{
    this->flag = _BaseType::_iterflag::l;
    this->current = nullptr;
}

template<typename _Elem, int n>
iterator<_Elem, n>::iterator(_iterflag _flag, const _Elem* p)
{
    this->flag = _flag;
    this->current = p;
}

template<typename _Elem, int n>
inline iterator<_Elem, n>::~iterator()
{
};

template<typename _Elem, int n>
int iterator<_Elem, n>::operator++()
{
    if (_iterflag::l == this->flag)
    {
        this->current++;
    }
    else if (_iterflag::r == this->flag)
    {
        this->current--;
    }
    return 0;
}

template<typename _Elem, int n>
inline iterator<_Elem, n>::operator _Elem*()
{
    return const_cast<_Elem*>(this->current);
}




