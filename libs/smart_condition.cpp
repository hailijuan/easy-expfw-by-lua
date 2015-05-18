#include "smart_condition.h"

using namespace google::protobuf;

bool SmartCondition::satisfied(const Message* message, const char* arg) const {
    return true;
}
