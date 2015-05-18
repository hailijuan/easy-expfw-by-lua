extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <iostream>
#include <vector>
#include <iterator>

#include <google/protobuf/message.h>

#include <string.h>
#include "ws2ui_req.pb.h"

using namespace std;
using namespace google::protobuf;
//using namespace google::protobuf::MessageLite;

vector<string> lua_functions{"div_page_build"};

void lua_execute(lua_State* L, lm::ws2ui_req_t* ui_req) {
    for (vector<string>::iterator it = lua_functions.begin();
        it != lua_functions.end(); ++it) {
        string lua_function = *it;
        string lua_file = lua_function + ".lua";

        cout<<"C -> Lua: " <<lua_file<<endl;

        //load lua file
        luaL_dofile(L, lua_file.c_str());

        //push lua function on top of stack
        lua_getglobal(L, lua_function.c_str());

        //push argument value on top of stack
        string ui_req_str;
        ui_req->SerializeToString(&ui_req_str);
        lua_pushstring(L, ui_req_str.c_str());

        cout<<ui_req_str.c_str()<<endl;

        //call lua function
        lua_call(L, 1, 1);

        cout<<"welcome back"<<endl;

        //pull lua-modified-value in ui_req
        ui_req_str = (string) lua_tostring(L, -1);
        ui_req->ParseFromString(ui_req_str);

        lua_pop(L, 1);
    }
}

int main() {
    lm::ws2ui_req_t ui_req;
    ui_req.set_req_tpl("hello");
    ui_req.set_wuliao_bitmap(22);
    cout<<"before:"<<endl;
    cout<<"req_tpl: "<<ui_req.req_tpl()<<endl<<"wuliao_bitmap: "<<ui_req.wuliao_bitmap()<<endl;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    lua_execute(L, &ui_req);
    lua_close(L);

    cout<<"after:"<<endl;
    cout<<"req_tpl: "<<ui_req.req_tpl()<<endl<<"wuliao_bitmap: "<<ui_req.wuliao_bitmap()<<endl;
    return 0;
}

