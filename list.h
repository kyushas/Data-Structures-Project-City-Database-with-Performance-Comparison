#ifndef LIST_H
#define LIST_H

template <typename E>
class List {
public:
    virtual void clear() = 0;
    virtual void insert(const E& it) = 0;
    virtual void append(const E& it) = 0;
    virtual E remove() = 0;
    virtual void moveToStart() = 0;
    virtual void moveToEnd() = 0;
    virtual void prev() = 0;
    virtual void next() = 0;
    virtual int length() const = 0;
    virtual int currPos() const = 0;
    virtual void moveToPos(int pos) = 0;
    virtual const E& getValue() const = 0;
    virtual ~List() {}
};

#endif
