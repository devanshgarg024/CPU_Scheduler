#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <queue>
#include <vector>
#include "../processService.hpp"
#include <memory>
#include "queueService.hpp"

namespace rr{

    class QueueService {
    private:
        std::queue<Process*> q;
    
    public:
        QueueService();
        void push_element(Process* p);
        void pop_element();
        bool is_empty();
        Process* top_element();
    };
}

#endif // QUEUE_HPP
