#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "build/NanoCmdAPI.pb.h"

int main() {
    uint8_t buffer[128];
    size_t message_length;
    bool status;

    {
        TestMessage message = TestMessage_init_zero;

        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

        message.testNum = 512;

        status = pb_encode(&stream, TestMessage_fields, &message);
        message_length = stream.bytes_written;

        if(!status){
            fprintf(stderr, "Encoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }
    }

    {
        TestMessage message = TestMessage_init_zero;

        pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);

        status = pb_decode(&stream, TestMessage_fields, &message);

        if (!status){
            fprintf(stderr, "Decoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }

        printf("Test num: %d\n", message.testNum);

    }

    return 0;
}
