#include "set_message_field.h"

using namespace google::protobuf;

bool set_message_field(
        Message* message, 
        const char* field, 
        const char* value) { 
    const Descriptor* descriptor = message->GetDescriptor();
    const Reflection* reflection = message->GetReflection();
    const FieldDescriptor* field_des = descriptor->FindFieldByName(field);
    switch (field_des->cpp_type()) {
        case FieldDescriptor::CPPTYPE_STRING:
            reflection->SetString(message, 
            field_des, 
            value);
            break;
        case FieldDescriptor::CPPTYPE_INT32:
            reflection->SetInt32(message, 
            field_des, 
            atoi(value));
            break;
        default:
            break;
    }
    return true;
}

