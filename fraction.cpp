#include<bits/stdc++.h>
using namespace std;

template<typename T>
T gcd(const T& n,const T& d)  // Returns the GCD of "n" and "d"...
{
    if(n%d==0)
        return d;
    return gcd(d,n%d);
}

// Class Definition starts...
template<typename T> class fraction;

// Routines without any attempt to prevent overflow...
template<typename T> fraction<T> operator +(const fraction<T>& one,const fraction<T>& two);
template<typename T> fraction<T> operator -(const fraction<T>& one,const fraction<T>& two);
template<typename T> fraction<T> operator *(const fraction<T>& one,const fraction<T>& two);
template<typename T> fraction<T> operator /(const fraction<T>& one,const fraction<T>& two);

// Routines with an attempt to prevent overflow...  [ Assuming "one" and "two" are already in their reduced form ]
template<typename T> fraction<T> add  (fraction<T> one,fraction<T> two);
template<typename T> fraction<T> subtract  (fraction<T> one,fraction<T> two);
template<typename T> fraction<T> multiply  (fraction<T> one,fraction<T> two);
template<typename T> fraction<T> divide  (fraction<T> one,fraction<T> two);

// Routines of a fraction with an integer...
template<typename T> fraction<T> operator +(const fraction<T>& one,const T& two);
template<typename T> fraction<T> operator -(const fraction<T>& one,const T& two);
template<typename T> fraction<T> operator *(const fraction<T>& one,const T& two);
template<typename T> fraction<T> operator /(const fraction<T>& one,const T& two);

// I/O operators for fraction class..
template<typename T> ostream& operator <<(ostream& out,const fraction<T>& a);
template<typename T> istream& operator >>(istream& in,fraction<T>& a);

// Class Definition
template<typename T>
class fraction
{
    T num,den;
public:

    fraction(const T& n=0,const T& d=0)  // Constructor...
    {
        this->num=n;
        this->den=d;
    }

    fraction<T>& reduce()  // Reduce the fraction to the lowest terms...
    {
        if(den==0)
            throw domain_error("");
        T temp=gcd(num,den);
        num/=temp;
        den/=temp;
        return *this;
    }

    T getNum() const  // Returns the numerator of the fraction...
    {
        return num;
    }

    T getDen() const  //  Returns the denominator of the fraction...
    {
        return den;
    }

    double value() const  // Returns the numerical value of the fraction as a double...
    {
        if(den==0)
            throw domain_error("");
        return num/(double)den;
    }

    // Friend Functions necessary for successful compilation...
    friend fraction operator + <>(const fraction& one,const T& two);
    friend fraction operator - <>(const fraction& one,const T& two);
    friend fraction operator * <>(const fraction& one,const T& two);
    friend fraction operator / <>(const fraction& one,const T& two);

    friend fraction add   <>(fraction one,fraction two);
    friend fraction subtract   <>(fraction one,fraction two);
    friend fraction multiply   <>(fraction one,fraction two);
    friend fraction divide   <>(fraction one,fraction two);

    friend fraction operator + <>(const fraction& one,const fraction& two);
    friend fraction operator - <>(const fraction& one,const fraction& two);
    friend fraction operator * <>(const fraction& one,const fraction& two);
    friend fraction operator / <>(const fraction& one,const fraction& two);

    friend ostream& operator << <>(ostream& out,const fraction& a);
    friend istream& operator >> <>(istream& in,fraction& a);
};

// Class Definition ends...

template<typename T>
fraction<T> operator +(const fraction<T>& one,const fraction<T>& two)
{
    fraction<T> a;
    a.num=one.num*two.den+two.num*one.num;
    a.den=one.den*two.den;
    return a;
}
template<typename T>
fraction<T> operator -(const fraction<T>& one,const fraction<T>& two)
{
    fraction<T> a;
    a.num=one.num*two.den-two.num*one.num;
    a.den=one.den*two.den;
    return a;
}
template<typename T>
fraction<T> operator *(const fraction<T>& one,const fraction<T>& two)
{
    fraction<T> a;
    a.num=one.num*two.num;
    a.den=one.den*two.den;
    return a;
}

template<typename T>
fraction<T> operator /(const fraction<T>& one,const fraction<T>& two)
{
    fraction<T> a;
    a.num=one.num*two.den;
    a.den=one.den*two.num;
    return a;
}


template<typename T>
fraction<T> add(fraction<T> one,fraction<T> two)
{
    fraction<T> a;
    T lcm=(one.den*two.den)/gcd(one.den,two.den);
    a.den=lcm;
    one.num*=lcm/one.den;
    two.num*=lcm/two.den;
    a.num=one.num+two.num;
    return a;
}
template<typename T>
fraction<T> subtract(fraction<T> one,fraction<T> two)
{
    fraction<T> a;
    T lcm=(one.den*two.den)/gcd(one.den,two.den);
    a.den=lcm;
    one.num*=lcm/one.den;
    two.num*=lcm/two.den;
    a.num=one.num-two.num;
    return a;
}
template<typename T>
fraction<T> multiply(fraction<T> one,fraction<T> two)
{
    fraction<T> a;
    T temp=gcd(two.num,one.den);
    two.num/=temp;
    one.den/=temp;
    temp=gcd(one.num,two.den);
    one.num/=temp;
    two.den/=temp;
    a.num=one.num*two.num;
    a.den=one.den*two.den;
    return a;
}
template<typename T>
fraction<T> divide(fraction<T> one,fraction<T> two)
{
    std::swap(two.num,two.den);
    fraction<T> a;
    T temp=gcd(two.num,one.den);
    two.num/=temp;
    one.den/=temp;
    temp=gcd(one.num,two.den);
    one.num/=temp;
    two.den/=temp;
    a.num=one.num*two.num;
    a.den=one.den*two.den;
    return a;
}


template<typename T>
fraction<T> operator +(const fraction<T>& one,const T& two)
{
    return one+fraction<T>(two,1);
}
template<typename T>
fraction<T> operator -(const fraction<T>& one,const T& two)
{
    return one-fraction<T>(two,1);
}
template<typename T>
fraction<T> operator *(const fraction<T>& one,const T& two)
{
    return fraction<T>(one.getNum()*two,one.getDen());
}
template<typename T>
fraction<T> operator /(const fraction<T>& one,const T& two)
{
    return fraction<T>(one.getNum(),one.getDen()*two);
}


template<typename T>
ostream& operator <<(ostream& out,const fraction<T>& a)
{
    out<<a.num<<"/"<<a.den;
    return out;
}
template<typename T>
istream& operator >>(istream& in,fraction<T>& a)
{
    in>>a.num>>a.den;
    return in;
}


int main()
{
     // Will update on usage...
}