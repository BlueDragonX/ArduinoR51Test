#ifndef _R51_TEST_YIELD_H_
#define _R51_TEST_YIELD_H_

#include <Arduino.h>
#include <Caster.h>
#include <R51Core.h>
#include "Array.h"

namespace R51 {

// A deep copy of a message.
class MessageCopy {
    public:
        MessageCopy() : type_(Message::EMPTY) {}

        MessageCopy(const Message& msg) : type_(msg.type()) {
            switch (msg.type()) {
                case Message::EMPTY:
                    break;
                case Message::SYSTEM_EVENT:
                    system_event_ = msg.system_event();
                    break;
                case Message::CAN_FRAME:
                    can_frame_ = msg.can_frame();
                    break;
            }
        }

        enum Message::Type type() const { return type_; };

        const SystemEvent& system_event() const { return system_event_; }

        const Canny::Frame& can_frame() const { return can_frame_; }

    private:
        Message::Type type_;
        SystemEvent system_event_;
        Canny::Frame can_frame_;
};

// A fake Yield implementation that collects copies of the yielded messages.
class FakeYield : public Caster::Yield<Message> {
    public:
        FakeYield() : messages_(new Array<MessageCopy>()) {}
        virtual ~FakeYield() { delete messages_; }

        // Return the number of messages stored in the object.
        size_t size() const { return messages_->size(); } 

        // Return a reference to the array of collected messages.
        const MessageCopy* messages() const { return messages_->data(); }

        // Clear the yielded messages from the object.
        void clear() { messages_->clear(); }

        // Collect a yielded message.
        void operator()(const Message& msg) const override { messages_->push(msg); }

    private:
        Array<MessageCopy>* messages_;
};

}  // namespace R51

#endif  // _R51_TEST_YIELD_H_
