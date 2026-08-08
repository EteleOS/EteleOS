-- EteleOS: resources/zoneinfo/zishrink.lua, time wirte: 2026/08/08
-- This file uses the Apache-2.0 license
-- Convert tzdata source into a smaller version of itself.
-- Contributed by Paul Eggert.  This file is in the public domain.  Ported from zishrink.awk.
local args=arg or {};local dataform="main";local version="";local redo="posix_right";local deps="";local files={}
for i,a in ipairs(args) do if a=="--dataform" then dataform=args[i+1] elseif a=="--version" then version=args[i+1] elseif a=="--redo" then redo=args[i+1] elseif a=="--deps" then deps=args[i+1] elseif not a:match("^%-%-") then files[#files+1]=a end end
local fixed={Arg="A",Brazil="B",Canada="C",Denmark="D",EU="E",France="F",["GB-Eire"]="G",Halifax="H",Italy="I",Jordan="J",Egypt="K",Libya="L",Morocco="M",Neth="N",Poland="O",Palestine="P",Cuba="Q",Russia="R",Syria="S",Turkey="T",Uruguay="U",Vincennes="V",Winn="W",Mongol="X",NT_YK="Y",Zion="Z",Austria="a",Belgium="b",["C-Eur"]="c",Algeria="d",["E-Eur"]="e",Taiwan="f",Greece="g",Hungary="h",Iran="i",StJohns="j",Chatham="k",Lebanon="l",Mexico="m",Tunisia="n",Moncton="o",Port="p",Albania="q",Regina="r",Spain="s",Toronto="t",US="u",Louisville="v",Iceland="w",Chile="x",Para="y",Romania="z",Macau="_",Detroit="Dt"}
local used, rules, ruleused, rlines, zones, links = {},{}, {},{}, {},{}
for n,v in pairs(fixed) do used[v]=n end
local function fields(s) local t={};for x in s:gmatch("%S+")do t[#t+1]=x end;return t end
local function short(n) if rules[n] then return rules[n] end;local v=n:sub(1,2);if used[v] and used[v]~=n then error("# ! collision: "..used[v].." "..n) end;used[v]=n;rules[n]=v;return v end
local function process(line)
  line=line:gsub("#.*",""):gsub("[%t ]+"," "):gsub("^ ",""):gsub(" $","");if line==""then return end
  local typ=line:match("^(%a+)");local isrule=typ=="Rule";if line:find("[^ ]Asia ") then if isrule then return else line=line:gsub("Asia ","",1) end end
  line=line:gsub("([: ])0+(%d)","%1%2");line=line:gsub(":0([^:])",":%1");line=line:gsub("last(Mon|Wed|Fri)",function(x)return "last"..x:sub(1,1)end):gsub("last(Sun|Tue|Thu|Sat)",function(x)return "last"..x:sub(1,1)end)
  local repl={max=dataform=="vanguard" and"m"or"ma",min=dataform=="vanguard"and"m"or"mi",only="o",Jan="Ja",Feb="F",Apr="Ap",Aug="Au",Sep="S",Oct="O",Nov="N",Dec="D"};for a,b in pairs(repl)do line=line:gsub(" "..a.." "," "..b.." ")end;line=line:gsub(" 0+$",""):gsub(" ([A-Za-z]+) 1$"," %1"):gsub(" Ja$","")
  if isrule then local f=fields(line);rlines[#rlines+1]=f;return end
  if typ=="Link" then local f=fields(line);ruleused[f[2]]=true;links[#links+1]=f;return end
  local f=fields(line);if typ=="Zone"then ruleused[f[4]]=true;zones[f[2]]={f}else local last=next(zones);if last then zones[last][#zones[last]+1]=f end end
end
if #files==0 then for l in io.stdin:lines()do process(l)end else for _,n in ipairs(files)do local f=assert(io.open(n));for l in f:lines()do process(l)end;f:close()end end
print("# version "..version);if dataform~="main"then print("# dataform "..dataform)end;if redo~="posix_right"then print("# redo "..redo)end;print("# This zic input file is in the public domain.")
for _,f in ipairs(rlines)do if ruleused[f[2]]then f[2]=fixed[f[2]]or short(f[2]);print(table.concat(f," "))end end
local names={};for n in pairs(zones)do names[#names+1]=n end;table.sort(names);for _,n in ipairs(names)do for i,f in ipairs(zones[n])do local p=i==1 and 4 or 2;if f[p]then f[p]=fixed[f[p]]or rules[f[p]]or f[p]end;print(table.concat(f," "))end end
for _,f in ipairs(links)do print("L "..f[2].." "..f[3])end
