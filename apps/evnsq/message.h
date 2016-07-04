#pragma once

#include "evnsq_export.h"
#include <evpp/exp.h>
#include <evpp/buffer.h>

namespace evnsq {

    enum { kMessageIDLen = 16 };
    enum { kFrameTypeResponse = 0, kFrameTypeError = 1, kFrameTypeMessage = 2, };

    struct Message {
        int64_t timestamp;
        uint16_t attempts;
        std::string id; // with length equal to kMessageIDLen
        const char* body;
        size_t body_len;

        void Decode(size_t message_len, evpp::Buffer* buf) {
            assert(buf->size() >= message_len);
            timestamp = buf->ReadInt64();
            attempts = buf->ReadInt16();
            id = buf->NextString(kMessageIDLen);
            body_len = message_len - sizeof(timestamp) - sizeof(attempts) - kMessageIDLen;
            body = buf->data(); // No copy
            buf->Retrieve(body_len);
        }
    };


    // MessageCallback is the message processing interface for Consumer
    //
    // Implement this interface for handlers that return whether or not message
    // processing completed successfully.
    //
    // When the return value is 0 Consumer will automatically handle FINishing.
    //
    // When the returned value is non-zero Consumer will automatically handle REQueing.
    typedef std::function<int(const Message*)> MessageCallback;
}