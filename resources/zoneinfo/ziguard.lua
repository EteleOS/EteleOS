-- EteleOS: resources/zoneinfo/ziguard.lua, time wirte: 2026/08/08
-- This file uses the Apache-2.0 license
--
-- Convert tzdata source into vanguard or rearguard form.
-- Contributed by Paul Eggert.  This file is in the public domain.
-- Ported from ziguard.awk.
-- xmake exposes command-line arguments through the standard `arg` table when
-- executing a Lua script; ordinary Lua does the same.
local args = {...}; if #args == 0 then args = arg or {} end
local function option(name) for i = 1, #args - 1 do if args[i] == name then return args[i + 1] end end end
local dataform = option("--dataform") or option("-d") or (os.getenv and os.getenv("DATAFORM")) or "main"
assert(({vanguard=true, main=true, rearguard=true})[dataform], "DATAFORM must be vanguard, main, or rearguard")
local function words(s) local t = {}; for w in s:gmatch("%S+") do t[#t+1] = w end; return t end
local function minutes(v) local h,m = v:match("^([+-]?%d+):?(%d*)"); return tonumber(h)*60 + ((v:sub(1,1)=="-") and -1 or 1)*(tonumber(m) or 0) end
local function abbr(n) local sign=n<0 and "-" or "+"; n=math.abs(n); local h,m=math.floor(n/60),n%60; return m>0 and string.format("%s%02d%02d",sign,h,m) or string.format("%s%02d",sign,h) end
local function rounded(s) local h,m,sec,frac=s:match("^([+-]?%d+):(%d+):(%d+)%.(%d+)$"); if not h then return s end; local n=tonumber(h)*3600+tonumber(m)*60+tonumber(sec); local f=tonumber("0."..frac); if f>.5 or (f==.5 and n%2~=0) then n=n+1 end; return (tonumber(h)<0 and "-" or "")..string.format("%d:%02d:%02d",math.floor(n/3600),math.floor(n/60)%60,n%60) end
local packrat, packratdata, packratlist = {}, option("--packratdata"), option("--packratlist")
if packratlist then local f=io.open(packratlist); if f then for l in f:lines() do local w=words(l); if l:sub(1,1)~="#" then packrat[w[3]]=true end end; f:close() end end
local files={}; for _,a in ipairs(args) do if not a:match("^%-") and a~=dataform and a~=packratdata and a~=packratlist then files[#files+1]=a end end
local lines, linkline, linktarget, zone = {}, {}, {}, nil
local subst_a, subst_b
local function linkreplace(old,target,name,oldtarget,comment)
  local prefix="Link\t"..oldtarget.."\t"; local rest
  if old:sub(1,#prefix)==prefix then rest=old:sub(#prefix+1):gsub("[%t ]*#.*",""); local a,b=math.floor(#oldtarget/8)+1,math.floor(#target/8)+1; while b<a do rest="\t"..rest;b=b+1 end; while a<b and rest:sub(1,1)=="\t" do rest=rest:sub(2);b=b-1 end else rest=name end
  return "Link\t"..target.."\t"..rest..(comment or "")
end
local function convert(line)
  if line:match("^#PACKRATLIST[%t ]+") and packratlist and line:match("^#PACKRATLIST[%t ]+"..packratlist:gsub("([^%w])","%%%1")) then line=line:gsub("^#PACKRATLIST[%t ]+[^%t ]+[%t ]+","") end
  local w=words(line); if line:match("^Zone") then zone=w[2] end
  if dataform~="main" then
    local commented=line:sub(1,1)=="#"; local un,co=false,false; local shift=commented and 1 or 0
    local function field(n) return w[n+shift] or "" end
    if zone=="Europe/Prague" and line:match("^#?[%t ]+[01]:00[	 ]") and line:match("1947 Feb 23") then un=(field(2)~="-")== (dataform~="rearguard");co=not un and not commented end
    local eire=line:match("^#?Rule[%t ]+Eire[%t ]"); local dub=zone=="Europe/Dublin" and line:match("^#?[%t ]+[01]:00[%t ]") and (field(4)=="" or tonumber(field(4))>1968)
    if eire or dub then un=(eire or (dub and field(3)=="IST/GMT"))==(dataform~="rearguard");co=not un and not commented end
    if line:match("^#?[%t ]+-[12]:00[%t ]+((Port|W%-Eur)[%t ]+[%+%%-]|-[%t ]+(%%z|%-01)[%t ]+1982 Mar 28)") then co=(line:find("%%z",1,true)~=nil)==(dataform=="rearguard");un=not co and commented end
    if line:match("^#?(Zone|Link)[%t ]+(Etc/)?GMT[%t ]") then un=((w[2]=="GMT")==(dataform=="vanguard"));co=not un and not commented end
    if un then line=line:gsub("^#","") elseif co then line="#"..line end; w=words(line)
    if dataform=="rearguard" and line:match("^[^#]*%%z") then local c=line:match("^Zone") and 3 or 1; local off,rules=minutes(w[c]),w[c+1]; local dst=rules=="-" and nil or (rules:match("^[+%-%d]") and minutes(rules) or ((rules=="Morocco" and #w==3) and -60 or 60)); line=line:gsub("%%z",dst and (abbr(off).."/"..abbr(off+dst)) or abbr(off),1)
    elseif dataform~="rearguard" then line=line:gsub("^((Zone[%t ]+[^%t ]+)?[%t ]+[^%t ]+[%t ]+[^%t ]+[%t ]+)[%+%-][^%t ]+","%1CHANGE-TO-%%z"):gsub("%-00CHANGE%-TO%-%%z","-00"):gsub("[%+%-][^%t ]+CHANGE%-TO%-","") end
    if w[1]=="#STDOFF" then local r=rounded(w[2]); if dataform=="vanguard" and (os.getenv and os.getenv("VANGUARD_SUBSECONDS")) then subst_a,subst_b=r,w[2] else subst_a,subst_b=w[2],r end elseif subst_a then local c=line:match("^Zone") and 3 or 1; if w[c]==subst_a then line=line:gsub(subst_a,subst_b,1) elseif w[c]~=subst_b then subst_a=nil end end
  end
  return line
end
local function read(f,name) for l in f:lines() do local line=convert(l); local w=words(line); if name==packratdata and packratlist and line:match("^Zone") then packrat._ignore=not packrat[w[2]] end; if packrat._ignore and not line:match("^Rule") then line="#"..line end; if line:match("^Link") then if dataform=="vanguard" and w[4]=="#=" then line=linkreplace(line,w[5],w[3],w[2]) end; if linkline[w[3]] then lines[linkline[w[3]]] = lines[linkline[w[3]]]:gsub("^Link","#Link") end; linkline[w[3]],linktarget[w[3]]=#lines+1,w[2] elseif line:match("^Zone") and linkline[w[2]] then lines[linkline[w[2]]]=lines[linkline[w[2]]]:gsub("^Link","#Link") end; lines[#lines+1]=line end end
if #files==0 then read(io.stdin,nil) else for _,name in ipairs(files) do local f=assert(io.open(name));read(f,name);f:close() end end
if dataform~="vanguard" then for name,target in pairs(linktarget) do local t=linktarget[target];if t then while linktarget[t] do t=linktarget[t] end; local n=linkline[name];lines[n]=linkreplace(lines[n],t,name,target,"\t#= "..target) end end end
for _,l in ipairs(lines) do print(l) end
