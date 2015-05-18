#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

class SmartCondition {
public:
    bool satisfied(const google::protobuf::Message* message, const char* arg) const;
};

