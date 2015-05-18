function set_baidutop_template(ws2ui_req)
    print("--Lua: set_baidutop_template")

    ws2ui_req.req_tpl = "hello back from Lua"

    --print(ws2ui_req.req_tpl)
    --print(ws2ui_req.xuanfu_style.main_type)
end

--set_baidutop_template({req_tpl="hello", xuanfu_style={main_type=1}})

