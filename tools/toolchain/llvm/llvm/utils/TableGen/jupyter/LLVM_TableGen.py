"""
Converted from tools/toolchain/llvm/llvm/utils/TableGen/jupyter/LLVM_TableGen.ipynb.
This file preserves the notebook content as plain Python for reference and execution outside Jupyter.
Markdown cells were converted into comments and Jupyter magics were removed.
"""

# Notebook outputs were not embedded in this conversion.

# # LLVM TableGen Kernel
#
# This notebook is running `llvm-tblgen`.
#

# --- code cell 3 ---
CELL_3 = """
# Jupyter magic removed: %reset
// This is some tablegen
class Foo {}
"""

# Errors printed to stderr are shown.
#

# --- code cell 5 ---
CELL_5 = """
# Jupyter magic removed: %reset
This is not tablegen.
"""

# Add some classes to get some output.
#

# --- code cell 7 ---
CELL_7 = """
# Jupyter magic removed: %reset
class Stuff {}
def thing : Stuff {}
"""

# By default cells are connected. Meaning that we cache the code and magic directives from the previously run cells.
#
# This means that the next cell still sees the `Stuff` class.
#

# --- code cell 9 ---
CELL_9 = """
def other_thing : Stuff {}
"""

# You can use the magic `%reset` to clear this cache and start fresh.
#

# --- code cell 11 ---
CELL_11 = """
# Jupyter magic removed: %reset
def other_thing : Stuff {}
"""

# You can also configure the default reset behaviour using the `%config` magic.
#

# --- code cell 13 ---
CELL_13 = """
# Jupyter magic removed: %config cellreset on
class Thing {}
"""

# --- code cell 14 ---
CELL_14 = """
// The cache is reset here so this is an error.
def AThing: Thing {}
"""

# The default value is `off`, meaning cells are connected. If you want to override the default for one cell only, use the `%reset` or `%noreset` magic. These always override the default.
#

# --- code cell 16 ---
CELL_16 = """
class Thing {}
"""

# --- code cell 17 ---
CELL_17 = """
# Jupyter magic removed: %noreset
// This works because of the noreset above.
def AThing: Thing {}
"""

# --- code cell 18 ---
CELL_18 = """
// This does not because we're not changing the default.
def AnotherThing: Thing {}
"""

# --- code cell 19 ---
CELL_19 = """
# Jupyter magic removed: %config cellreset off
# Jupyter magic removed: %reset
// Here we have an empty cache and default reset behaviour.
"""

# It is not valid to have `%reset` and `%noreset` in the same cell.
#

# --- code cell 21 ---
# Jupyter magic removed: %reset
# Jupyter magic removed: %noreset

# Consider setting `cellreset` to the majority usecase for your notebook. For example a tutorial building a large example across many cells will likely want it `off`. One with many standalone examples, `on`.
#
# There is a "magic" directive `%args` that you can use to send command line arguments to `llvm-tblgen`.
#
# For example, here we have some code that shows a warning.
#

# --- code cell 23 ---
CELL_23 = """
# Jupyter magic removed: %reset
class Thing <int A, int B> {
    int num = A;
}
"""

# We can pass an argument to ignore that warning.
#

# --- code cell 25 ---
# Jupyter magic removed: %args --no-warn-on-unused-template-args

# If you have a run of cells without a `%reset`, the most recent `%args` is used.
#

# --- code cell 27 ---
CELL_27 = """
// This passes --no-warn-on-unused-template-args
"""

# --- code cell 28 ---
CELL_28 = """
# Jupyter magic removed: %args
// Now we're not passing the argument so the warning comes back.
"""

# If there are many `%args` in a cell, the last one is used.
#

# --- code cell 30 ---
CELL_30 = """
# Jupyter magic removed: %reset
# Jupyter magic removed: %args --no-warn-on-unused-template-args
# Jupyter magic removed: %args
class Thing <int A, int B> {}
"""

