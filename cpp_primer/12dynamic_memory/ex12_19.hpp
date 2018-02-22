#ifndef EX_12_18_HPP_
#define EX_12_18_HPP_

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <stdexcept>

using std::vector;
using std::string;

class StrBlobPtr;

class StrBlob {
public:
    using size_type = vector<string>::size_type;
    friend class StrBlobPtr;

    StrBlobPtr Begin();
    StrBlobPtr End();

    StrBlob() : data_(std::make_shared<vector<string>>()) { }
    StrBlob(std::initializer_list<string> il)
        : data_(std::make_shared<vector<string>>(il)) { }

    size_type Size() const { return data_->size(); }
    bool Empty() const { return data_->empty(); }

    void PushBack(const string &t) { data_->push_back(t); }
    void PopBack() {
        Check(0, "pop_back on empty StrBlob");
        data_->pop_back();
    }

    string &Front() {
        Check(0, "front on tempy StrBlob");
        return data_->front();
    }

    string &Back() {
        Check(0, "back on empty StrBlob");
        return data_->back();
    }

    string &Front() const {
        Check(0, "front on tempy StrBlob");
        return data_->front();
    }

    string &Back() const {
        Check(0, "back on empty StrBlob");
        return data_->back();
    }

private:
    void Check(size_type i, const string &msg) const {
        if (i >= data_->size()) throw std::out_of_range(msg);
    }

    std::shared_ptr<vector<string>> data_;
};

class StrBlobPtr {
public:
    StrBlobPtr() : curr_(0) { }
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr_(a.data_), curr_(sz) { }

    bool operator!=(const StrBlobPtr &p) { return p.curr_ != curr_; }
    string &Deref() const {
        auto p = Check(curr_, "dereference past end");
        return (*p)[curr_];
    }
    StrBlobPtr &Incr() {
        Check(curr_, "increment past end of StrBlobPtr");
        ++curr_;
        return *this;
    }

private:
    std::shared_ptr<vector<string>> Check(size_t i, const string &msg) const {
        auto ret = wptr_.lock();
        if (!ret) throw std::runtime_error("unbound StrBlobPtr");
        if (i >= ret->size()) throw std::out_of_range(msg);

        return ret;
    }

    std::weak_ptr<vector<string>> wptr_;
    size_t curr_;
};


#endif  // EX_12_18_HPP_
