-- EteleOS: tests/lib/libcrypto/free/freenull.lua, time wirte: 2026/08/08
-- This file uses the Apache-2.0 license
-- $OpenBSD: freenull.awk,v 1.4 2023/11/19 13:11:06 tb Exp $
-- Copyright (c) 2018 Theo Buehler <tb@openbsd.org>
-- Permission to use, copy, modify, and distribute this software for any
-- purpose with or without fee is hereby granted.
-- Generate calls to one-argument OpenSSL free functions.  Ported from freenull.awk.
if io.stdout and io.stdout.setvbuf then io.stdout:setvbuf("no") end
local skip = {
    ASN1_item_ex_free=true, ASN1_item_free=true, CONF_modules_free=true,
    EVP_PKEY_asn1_set_free=true, X509V3_section_free=true,
    X509V3_string_free=true, sk_pop_free=true, BIO_CONNECT_free=true,
    CRYPTO_free=true, EC_PRIVATEKEY_free=true, ECPARAMETERS_free=true,
    ECPKPARAMETERS_free=true, X9_62_CHARACTERISTIC_TWO_free=true,
    X9_62_PENTANOMIAL_free=true
}
local input = io.stdin
if (arg or {})[1] then input = assert(io.open(arg[1], "r")) end
for line in input:lines() do
    if line ~= "CRYPTO_dbg_free" and not skip[line] and line:match("_free$") then
        io.write(string.format("\t%s(NULL);\n", line))
    end
end
if input ~= io.stdin then input:close() end
