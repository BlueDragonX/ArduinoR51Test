#ifndef _R51_TEST_YIELD_H_
#define _R51_TEST_YIELD_H_

#include <Arduino.h>
#include <Caster.h>
#include <R51Core.h>
#include "Array.h"

namespace R51 {

// A fake Yield implementation that collects copies of the yielded messages.
class FakeYield : public Caster::Yield<Message> {
    public:
        FakeYield() : messages_(new Array<Message>()) {}
        virtual ~FakeYield() { delete messages_; }

        // Return the number of messages stored in the object.
        size_t size() const { return messages_->size(); } 

        // Return a reference to the array of collected messages.
        const Message* messages() const { return messages_->data(); }

        // Collect a yielded message.
        void operator()(const Message& msg) const override { messages_->push(msg); }

    private:
        Array<Message>* messages_;
};

}  // namespace R51

#endif  // _R51_TEST_YIELD_H_
