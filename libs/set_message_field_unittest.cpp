#include <iostream>

#include "set_message_field.h"

using namespace std;
using namespace google::protobuf;

#include "test.pb.h"

int main() {
    NOVA_UI::UiRequest ui_req;
    ui_req.set_url("empty");
    ui_req.set_type(-1);
    cout<<ui_req.url()<<endl;
    cout<<ui_req.type()<<endl;

    set_message_field(&ui_req, "url", "hello");

    set_message_field(&ui_req, "type", "100");

    cout<<ui_req.url()<<endl;
    cout<<ui_req.type()<<endl;
    return 0;
}
