#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

bool set_message_field(
        google::protobuf::Message* message, 
        const char* field, 
        const char* value);

