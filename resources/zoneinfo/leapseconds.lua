-- EteleOS: resources/zoneinfo/leapseconds.lua, time wirte: 2026/08/08
-- This file uses the Apache-2.0 license
-- Generate zic format 'leapseconds' from NIST/IERS format 'leap-seconds.list'.
-- This file is in the public domain.  Ported from leapseconds.awk.
local argv = {...}; if #argv == 0 then argv = arg or {} end
local input = argv[1] and assert(io.open(argv[1], "r")) or io.stdin
local months={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"}
local function date(s)
  local day=109513+math.floor(s/86400); local q=math.floor(day/146097);day=day-q*146097
  local century=math.floor(day/36524);if century==4 then century=3 end;day=day-century*36524
  local quad=math.floor(day/1461);day=day-quad*1461;local year=math.floor(day/365);if year==4 then year=3 end;day=day-year*365
  local md={31,30,31,30,31,31,30,31,30,31,31};local month=0;while month<11 and day>=md[month+1] do day=day-md[month+1];month=month+1 end
  if month<=9 then month=month+3 else month=month-9;year=year+1 end
  return 1600+q*400+century*100+quad*4+year,month,day+1,math.floor(s/3600)%24,math.floor(s/60)%60,s%60
end
local header=[[# Allowance for leap seconds added to each time zone file.

# This file is in the public domain.

# This file is generated automatically from the data in the public-domain
# NIST/IERS format leap-seconds.list file, which can be copied from
# <https://hpiers.obspm.fr/iers/bul/bulc/ntp/leap-seconds.list>.
# For more about leap-seconds.list, please see The NTP Timescale and Leap Seconds.

# There were no leap seconds before 1972, as no official mechanism
# accounted for the discrepancy between atomic time (TAI) and the earth's rotation.
# All leap-seconds are Stationary (S) at the given UTC time.
# Typical lines look like this:
# Leap	YEAR	MON	DAY	23:59:60	+	S
]]
io.write(header)
local old, updated, expires, lastlines = nil, nil, nil, ""
for line in input:lines() do
  line=line:gsub("\r$","")
  if line:match("^#[ \t]*[Uu]pdated through") or line:match("^#[ \t]*[Ff]ile expires on") then lastlines=lastlines..line.."\n" end
  local tag,n=line:match("^#([@$])[ \t]+(%d+)");if tag=="$" then updated=tonumber(n) elseif tag=="@" then expires=tonumber(n) end
  if not line:match("^[ \t]*#") and line:match("%S") then local stamp,tai=line:match("^(%d+)%s+(%d+)");stamp,tai=tonumber(stamp),tonumber(tai);if old then local y,m,d=date(stamp-1);io.write(string.format("Leap\t%d\t%s\t%d\t%s\tS\n",y,months[m],d,old<tai and "23:59:60\t+" or "23:59:59\t-")) end;old=tai end
end
if input~=io.stdin then input:close() end
print("")
local function metadata(kind,s)
  local y,m,d,h,mi,se=date(s);return string.format("#%s %d (%.4d-%.2d-%.2d %.2d:%.2d:%.2d UTC)\n",kind,s-2208988800,y,m,d,h,mi,se)
end
if expires then local y,m,d,h,mi,se=date(expires);print("# UTC timestamp when this leap second list expires.");print("# Any additional leap seconds will come after this.");print(string.format("#Expires %.4d\t%s\t%.2d\t%.2d:%.2d:%.2d",y,months[m],d,h,mi,se)) else print("# (No Expires line, since the expires time is unknown.)") end
print("\n# Here are POSIX timestamps for the data in this file.")
io.write(updated and metadata("updated",updated) or "#(updated time unknown)\n");io.write(expires and metadata("expires",expires) or "#(expires time unknown)\n");io.write("\n"..lastlines)
