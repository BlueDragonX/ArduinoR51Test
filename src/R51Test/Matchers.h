#ifndef _R51_TEST_MATCHERS_H_
#define _R51_TEST_MATCHERS_H_

#define assertPrintableEqual(left, right) do { \
    if (left != right) { \
        SERIAL_PORT_MONITOR.print(left); \
        SERIAL_PORT_MONITOR.print(" != "); \
        SERIAL_PORT_MONITOR.println(right); \
        assertTrue(false); \
    } \
} while (false)

#define assertSize(container, value) \
    assertEqual((int)container.size(), (int)value)

#define assertIsSystemEvent(message, event) \
    assertEqual(message.type(), R51::Message::SYSTEM_EVENT); \
    assertPrintableEqual(message.system_event(), event);

#define assertIsCANFrame(message, frame) \
    assertEqual(message.type(), R51::Message::CAN_FRAME);\
    assertPrintableEqual(message.can_frame(), frame);

#endif  // _R51_TEST_MATCHERS_H_
