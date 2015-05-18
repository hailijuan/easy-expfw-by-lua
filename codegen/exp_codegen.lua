function file_exists(path)
    local file = io.open(path, "rb")
    if file then file:close() end
    return file ~= nil
end


local flag_count = 0
local flag_sign = {}

function get_temp_flag(exp_id)
    if flag_sign[exp_id] ~= nil then
        return flag_sign[exp_id]
    end
    flag_sign[exp_id] = "FLAG_RESERVED_" .. flag_count
    flag_count = flag_count + 1
    return flag_sign[exp_id]
end


function gen_exp_conf(all_exps)
    local file = io.open("output/autogen.exp", "w")

    for k,v in pairs(all_exps) do
        file:write("##" .. k)
        file:write("\n")
        file:write("[@EXP]")
        file:write("\n")
        file:write("NAME:" .. v.NAME)   
        file:write("\n")
        file:write("OWNER:" .. v.OWNER)   
        file:write("\n")
        file:write("DESC:" .. v.DESC)   
        file:write("\n")
        file:write("FLOW:" .. v.FLOW)   
        file:write("\n")
        file:write("TYPE:" .. v.TYPE)   
        file:write("\n")
        file:write("LAYER:" .. v.LAYER)   
        file:write("\n")
        file:write("[.@DIVERSION]")
        file:write("\n")
        file:write("DIVNAME:" .. v.DIVERSION)
        file:write("\n")

        if v.CONDITION ~= nil then
            file:write("CONDITION:" .. v.CONDITION)
            file:write("\n")
            file:write("ARG:" .. v.ARG)
            file:write("\n")
        end

        file:write("[..@OVERRIDE]")
        file:write("\n")
        file:write("FLAG_NAME:" .. get_temp_flag(v.NAME))
        file:write("\n")
        file:write("VALUE:true")
        file:write("\n")
    end

    file:close()
end


function gen_diversion_lua(all_exps)
    local exp_main_lines = ""

    for k,v in pairs(all_exps) do
        if file_exists(v.ACTION .. ".lua") == true then
            action_line = "dofile(\"" .. v.ACTION .. ".lua\")\n" .. v.ACTION .. "(msg)"
        else
            action_line = v.ACTION
        end

        local temp_flag = get_temp_flag(v.NAME)
        exp_main_lines = 
            exp_main_lines .. temp_flag .. " = expflag.get_flag_value(\"" .. temp_flag .. "\")\n"
        exp_main_lines = 
            exp_main_lines .. "if " .. temp_flag .. " == \"true\" then\n" .. action_line .. "\nend\n\n"
 
    end

    local file = io.open("output/div_page_build.lua", "w")
    local header = [[
package.cpath = 'autogen/?.so;'
local expflag = require("expflag");
local pb = require("luapb");
pb.import("ws2ui_req.proto");
local msg = pb.new("lm.ws2ui_req_t");
function div_page_build(msg_str)
pb.parseFromString(msg, msg_str)

]]

    local tail = [[
msg_str = pb.serializeToString(msg)
return msg_str
end
]]

    file:write(header)
    file:write(exp_main_lines)
    file:write(tail)
    file:close()
end

function make_dir(dir)
    if file_exists(dir) == false then
        os.execute("mkdir " .. dir)
    end    
end

function exp_codegen()
    dofile("exp_conf.lua")

    --TODO:对于全流量的EXP，不再生成conf，在lua里always调用对应的ACTION即可

    --TODO:exp_conf.lua规则校验

    make_dir("output/")

    gen_exp_conf(all_exps)

    gen_diversion_lua(all_exps)

end


exp_codegen()

