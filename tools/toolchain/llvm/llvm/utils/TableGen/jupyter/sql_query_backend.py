"""
Converted from tools/toolchain/llvm/llvm/utils/TableGen/jupyter/sql_query_backend.ipynb.
This file preserves the notebook content as plain Python for reference and execution outside Jupyter.
Markdown cells were converted into comments and Jupyter magics were removed.
"""

# Notebook outputs were not embedded in this conversion.

# # Writing a TableGen Backend in Python
#
# This tutorial is going to walk through creating a TableGen backend using Python.
#
# We are using Python to better fit into a notebook, but backends in LLVM are written in C++. The principles you learn here will still apply and you could port this tutorial to any language that has a JSON parser.
#
# This is the process in LLVM, using a C++ backend:
# ```
# TableGen source -> llvm-tblgen -> backend (within llvm-tblgen) -> results
# ```
# This is what we will be doing:
# ```
# TableGen source -> llvm-tblgen -> JSON -> Python -> results
# ```
#
# The backend here is ported from one of several in "SQLGen" which was written by Min-Yih Hsu.
# * SQLGen C++ sources - https://github.com/mshockwave/SQLGen
# * LLVM dev presentation - https://www.youtube.com/watch?v=UP-LBRbvI_U
#
# I encourage you to use those resources to supplement this notebook.
#
# ## Compiling TableGen
#
# Unlike the other tutorial notebooks we are not using the TableGen kernel. This is an iPython notebook and we're going to run `llvm-tblgen` as a subprocess.
#
# First let's find it, in the same way the TableGen kernel does.
#

# --- code cell 5 ---
import os
import shutil

def find_tblgen():
    path = os.environ.get("LLVM_TBLGEN_EXECUTABLE")
    if path is not None and os.path.isfile(path) and os.access(path, os.X_OK):
        return path
    else:
        path = shutil.which("llvm-tblgen")
        if path is None:
            raise OSError("llvm-tblgen not found")
        return path

_ = find_tblgen()

# If the above cell raises an exception, either put `llvm-tblgen` on your `PATH` or point to it using the `LLVM_TBLGEN_EXECUTABLE` environment variable. Alternatively, edit the code to use whatever path you want.
#
# Then we need to compile some TableGen by passing it to `llvm-tblgen`'s stdin. We will be using the option `--dump-json` and returning the JSON as a Python dictionary if the compilation succeeds. If it fails, we raise an exception.
#

# --- code cell 7 ---
import subprocess
import tempfile
import json

def run_tblgen(src):
    # Passing to stdin requires a file like object.
    with tempfile.TemporaryFile("w+") as f:
        f.write(src)
        f.seek(0)
        got = subprocess.run(
            [find_tblgen(), "--dump-json"],
            stdin=f,
            stderr=subprocess.PIPE,
            stdout=subprocess.PIPE,
            universal_newlines=True,
        )

    if got.stderr:
        raise RuntimeError("llvm-tblgen failed with stderr: " + got.stderr)

    return json.loads(got.stdout)

print(json.dumps(run_tblgen("class Foo {}"), indent=4))

# ## Structure of a SQL Query
#
# This backend is going to generate SQL queries. The general form of a SQL query is:
# ```
# SELECT <some field names> FROM <table name>
#  WHERE <conditions>
#  ORDER BY <field tags>;
# ```
#
# ## SQL Query TableGen
#

# --- code cell 11 ---
query_tblgen = """\
def all;
def fields;
def none;

def eq;
def ne;
def gt;
def ge;
def and;
def or;
"""

# Normally you'd write this to a `.td` file but here we have it in a Python string to fit into this notebook. We will add to this string to produce the final source.
#
# This section defines some constants. First are the fields we want to get back from the query:
# * `all` - Return all fields.
# * `fields` - Means that we will provide a list of fields we are interested in.
#
# The second set are the logical operators for what will become the `WHERE` clause (called `condition` in the TableGen). These are string versions of various symbols. For example `ne` means `!=`, which in SQL is `<>`.
#
# Finally `none` is used to mean there is no condition to the query (no `WHERE`).
#

# --- code cell 13 ---
query_tblgen += """\
class Query <string table, dag query_fields = (all), dag condition = (none)> {
  string TableName = table;
  dag Fields = query_fields;
  dag WhereClause = condition;
  list<string> OrderedBy = [];
}
"""

# Then the Query class. Its arguments are:
# * `table` - The name of the table to query (`FROM <table>`).
# * `query_fields` - The fields you want returned (`SELECT <fields>`).
#     * Defaults to `all` meaning return all fields.
# * `condition` - Logic to select entries (`WHERE <conditions>`).
#     * Defaults to `none` meaning there is no condition, or in other words select all entries in the table.
#
# ## Using The Query Class
#

# --- code cell 16 ---
full_tblgen = query_tblgen + """\
def : Query<"Customer">;

def : Query<"Orders", (fields "Person", "Amount")>;

def : Query<"Customer", (fields "Affiliation"),
            (eq "Name", "Mary Blackburn":$str)>;

def : Query<"Orders", (fields "ProductName"),
            (gt "Amount", 8)>;

def : Query<"Orders", (fields "ProductName":$name, "Person"),
            (and (gt "Amount", 8), (ne "Person", 1))> {
  let OrderedBy = ["$name"];
}
"""

# Now we can define some queries. Let's go go over the last one in detail.
#
# ```
# def : Query<"Orders", (fields "ProductName":$name, "Person"),
#             (and (gt "Amount", 8), (ne "Person", 1))> {
#   let OrderedBy = ["$name"];
# }
# ```
#
# * It will run on a table called `Orders`.
# * We want to see the fields `ProductName` and `Person`.
# * We have tagged `ProductName` with `$name`.
# * The condition is that `Amount` must be greater than `8` and
#   `Person` must not be equal to `1`.
# * The results of this query should be ordered by the field
#   tagged `$name`, which is `ProductName`.
#   
# The condition being of DAG type (Directed Acyclic Graph) allows us to describe nested conditions. You might write this condition in Python as:
# ```
# if (Amount > 8) and (Person != 1):
# ```
# Putting that into a graph form:
# ```
#         |------|and|------|
#         |                 |
# | Amount > 8 |       | Person != 1 |
# ```
# Which is what we're describing with the DAG in TableGen.
#
# ## The JSON format
#

# --- code cell 19 ---
full_json = run_tblgen(full_tblgen)
print(json.dumps(full_json, indent=4))

# The backend is going to walk the JSON we decoded. You can see the full output above in case you want to browse but for now don't read the whole thing. We will highlight the key aspects of it as we go along.
#

# --- code cell 21 ---
print(full_json["!instanceof"])

# Any key beginning with `!` is some sort of metadata about the other keys. Here this is a list of all instances of certain classes. We just have `Query` which lists all the queries we defined.
#

# --- code cell 23 ---
print(full_json["anonymous_0"]["!superclasses"])

# On each def there is also a `!superclasses` that gives you the same information. Meaning you could use `!instanceof` to get a list of keys to lookup, or you could walk all keys and check `!superclasses`.
#

# --- code cell 25 ---
print(full_json["anonymous_0"]["Fields"])

# From a def object you can find its attributes. Here we have the fields we want the query to show, which is all of them.
#
# # The Backend
#
# The core of a backend is looping over all defs of a certain class and outputting some text based on their properties.
#
# Here we're going to loop over all defs of type `Query` and emit SQL queries for them.
#

# --- code cell 29 ---
def find_all_queries(j):
    queries = []
    for key in j:
        # ! means it is some metadata, not a def.
        if not key.startswith("!"):
            value = full_json[key]
            # If we inherit from Query.
            if "Query" in value["!superclasses"]:
                queries.append(value)
    return queries

queries = find_all_queries(full_json)

print([q["!name"] for q in queries])

# Why are the names `anonymous_...`? When we defined them we did `def :` and missed out the name. This is allowed and `llvm-tblgen` just came up with a name for us. For this purpose the names are irrelevant.
#
# Now we have the relevant classes we need to "emit" them. Meaning produce something from them, in this case a SQL query.
#

# --- code cell 31 ---
def emit_operator(operator):
    return {
            'gt': ' > ',
            'ge': ' >= ',
            'lt': ' < ',
            'le': ' <= ',
            'ne': ' <> ',
            'eq': ' = ',
            'or': ' OR ',
            'and': ' AND '
            }[operator]

print(emit_operator('and'))

# The maps our TableGen constants to the equivalent SQL logical operation.
#

# --- code cell 33 ---
def emit_fields(args):
    # Return a comma separated list of arg names.
    return ", ".join([arg[0] for arg in args])

print(emit_fields([["Abc", None], ["Def", None]]))

# This emits the the fields we are selecting. Each field has a name (`arg[0]`) and an optional tag that we will use later.
#

# --- code cell 35 ---
from collections.abc import Mapping

def emit_where_clause(where_clause):
    output = ""
    num_args = len(where_clause["args"])

    for idx, arg in enumerate(where_clause["args"]):
        arg_name, arg_type = arg

        if isinstance(arg_name, Mapping):
            # This is a nested where clause.
            output += emit_where_clause(arg_name)
        else:
            # This is some condition.
            if arg_type == "str":
                # String types must be emitted with "" around them.
                output += '"' + arg_name + '"'
            else:
                output += str(arg_name)

        # If this is not the last arg, emit the condition.
        if idx != (num_args-1):
            output += emit_operator(where_clause["operator"]["def"])

    return output

print(emit_where_clause({
"args": [["Name",None],
        ["Mary Blackburn", "str"]],
"kind": "dag",
"operator": {
    "def": "eq",
    "kind": "def",
    "printable": "eq"
}}))

# This emits the condition that goes with the `WHERE`. The condition is a DAG, which means that we will find a possible mix of conditions and other DAGS. We recurse to handle the latter case.
#
# For each part of the condition we print the name of the thing you're checking, then the condition (`=`, `<>`, etc.). The value to check against is last and that goes on the end.
#

# --- code cell 37 ---
def emit_ordered_by(ordered_by, field_tag_map):
    # No ORDER BY statement to emit.
    if not ordered_by:
        return ""

    output = "\n ORDER BY "
    num_ordered_by = len(ordered_by)

    for idx, field_name in enumerate(ordered_by):
        # If it is a tag
        if field_name.startswith('$'):
            # Find the corresponding field name
            tag_name = field_name[1:]
            field_name = field_tag_map.get(tag_name)
            if field_name is None:
                raise RuntimeError('Unrecognized tag "{}"'.format(
                    tag_name))

        # Separate each tag after the first with ", ".
        if idx != 0:
            output += ", "
        output += field_name

    return output

print(emit_ordered_by(["$abc", "$def"], {'abc':"ABC", 'def':"DEF"}))

# `emit_ordered_by` produces the `ORDER BY` text. If there is no ordering return nothing, otherwise loop over all the fields we want to order by and emit their names.
#
# If the name is a tag, we look that up in a map to get the real field name. Here's how we build that map:
#

# --- code cell 39 ---
def build_tag_map(arguments):
    # Args are [Name, Tag]. Reverse this so we have [Tag, Name].
    # Add each one to a dictionary where Tag is the key and Name is the value.
    return dict([reversed(a) for a in arguments])

print(build_tag_map([["ABC", "abc"], ["DEF", "def"]]))

# --- code cell 40 ---
def emit_query(q):
    fields_init = q["Fields"]
    field_op_name = fields_init["operator"]["def"]
    if not field_op_name in ["all", "fields"]:
        raise RuntimeError("Invalid dag operator " + field_op_name)

    field_tag_map = build_tag_map(fields_init["args"])

    where_clause = q["WhereClause"]
    has_where = where_clause["operator"]["def"] != "none"

    ret = "SELECT "
    if field_op_name == "all":
        ret += "*"
    ret += emit_fields(fields_init["args"])
    ret += " FROM " + q["TableName"]
    if has_where:
        ret += "\n WHERE " + emit_where_clause(where_clause)
    ret += emit_ordered_by(q["OrderedBy"], field_tag_map)
    ret += ";"

    return ret

# Finally the main function. It emits the skeleton of the query and calls the helpers we defined earlier to fill in the gaps.
#
# ## The Result
#

# --- code cell 43 ---
for q in queries:
    print(emit_query(q) + "\n")

# Now we run `emit_query` and print out the results. There you have it, that's a TableGen backend!
#
# You've seen the core concepts. Loop over all the defs of a certain class and then emit some other structure based on the fields of each one. In this case it was SQL queries. In LLVM it's most often C++ code but it can be anything you want.
#
# If you want to see the same thing done with a C++ backend (one written in C++ that is, not producing it), check out the links at the start of this notebook.
#
