#pragma once
#include <queue>
template <class _Tp, class _Container = std::vector<_Tp>,
        class _Compare = std::less<typename _Container::value_type> >
class my_priority_queue : public std::priority_queue<_Tp, _Container, _Compare> {
public:
    void pop(_Tp &obj) {
        obj = std::move(this->c.front());
        std::priority_queue<_Tp, _Container, _Compare>::pop();
    }
};