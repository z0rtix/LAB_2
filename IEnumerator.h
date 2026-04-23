#ifndef IENUMERATOR_H
#define IENUMERATOR_H


template <typename T>
class IEnumerator {
    public:
        virtual ~IEnumerator() = default;
        
        virtual bool moveNext() = 0;
        virtual T current() = 0;
};


#endif