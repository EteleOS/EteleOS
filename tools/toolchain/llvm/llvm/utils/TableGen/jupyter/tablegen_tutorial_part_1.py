"""
Converted from tools/toolchain/llvm/llvm/utils/TableGen/jupyter/tablegen_tutorial_part_1.ipynb.
This file preserves the notebook content as plain Python for reference and execution outside Jupyter.
Markdown cells were converted into comments and Jupyter magics were removed.
"""

# Notebook outputs were not embedded in this conversion.

# ## Introduction to TableGen Part 1: Classes, Defs, Basic Types and Let
#
# **Note:** The content in this notebook is adapted from [this document](https://llvm.org/docs/TableGen/index.html). Refer to it if you want more details.
#
# This tutorial will cover:
# * Classes
# * Defs
# * Basic types
# * `let` in various forms
# * Class template arguments
#
# ## What is TableGen?
#
# TableGen is a language used in LLVM to automate the generation of certain types of code. Usually repetitive code that has a common structure. TableGen is used to generate "records" that are then processed by a "backend" into domain specific code.
#
# The compiler for TableGen is the binary `llvm-tblgen`. This contains the logic to convert TableGen source into records that can then be passed to a TableGen backend.
#
# TableGen allows you to define Classes and Defs (which are instances of classes) but it doesn't encode what to do with that structure. That's what the backend does. The backend converts this structure into something useful, for example C++ code.
#
# These backends are included in the `llvm-tblgen` binary and you can choose which one to run using a command line option. If you don't choose a backend you get a dump of the structure, and that is what this notebook will be showing.
#
# This tutorial will focus on the language itself only. The only thing you need to know now is that in addition to `llvm-tblgen` you will see other `*-tblgen` like `clang-tblgen`. The difference between them is the backends they include.
#
# The default output from `llvm-tblgen` looks like this:
#

# --- code cell 5 ---
CELL_5 = """
# Jupyter magic removed: %config cellreset on

// Empty source file
"""

# **Note:** `%config` is not a TableGen command but a "magic" command to the Jupyter kernel for this notebook. By default new cells include the content of previously run cells, but for this notebook we mostly want each to be isolated. On occasion we will use the `%noreset` magic to override this.
#
# No source means no classes and no defs. Let's add a class.
#
# ## Classes
#

# --- code cell 8 ---
CELL_8 = """
class C {}
"""

# Followed by a def (definition).
#

# --- code cell 10 ---
CELL_10 = """
# Jupyter magic removed: %noreset

def X: C;
"""

# `def` creates an instance of a class. Typically, the main loop of a TableGen backend will look for all defs that are instances of a certain class.
#
# For example if I am generating register information I would look for all defs that are instances of `RegisterInfo` in the example below.
#

# --- code cell 12 ---
CELL_12 = """
class RegisterInfo {}
def X0: RegisterInfo {}
def X1: RegisterInfo {}
"""

# ## Inheritance
#
# Like many other languages with classes, a class in TableGen can inherit properties of another class.
#

# --- code cell 15 ---
CELL_15 = """
class C {}
class D : C {}
"""

# Inheritance is done by putting the class you want to inherit from after `:`, before the opening `{`.
#
# You'll know that `D` inherits from `C` by the `// C` comment on the `class D {` line in the output.
#
# Not very interesting though, what are we actually inheriting? The members of the parent class.
#

# --- code cell 17 ---
CELL_17 = """
class C {
    int a;
}
class D : C {}
"""

# Note that `D` now has the `a` member which was defined in the class `C`.
#
# You can inherit from multiple classes. In that case the order that that happens in matches the order you write the class names after the `:`.
#

# --- code cell 19 ---
CELL_19 = """
class C {
    int a = 1;
}
class D {
    int a = 2;
}
class E : C, D {}
"""

# Class `E` first inherits from class `C`. This gives `E` a member `a` with value `1`. Then it inherits from class `D` which also has a member `a` but with a value of `2`. Meaning the final value of `E`'s `a` is `2`.
#
# When a member has the same name this is handled on a "last one in wins" basis. Assuming the types match.
#

# --- code cell 21 ---
CELL_21 = """
class C {
    string a = "";
}
class D {
    int a = 2;
}
class E : C, D {}
"""

# When they don't match, we get an error. Luckily for us, we're about to learn all about types.
#
# ## Types
#
# TableGen is statically typed with error checking to prevent you from assigning things with mismatched types.
#

# --- code cell 25 ---
CELL_25 = """
class C {
    int a;
    bit b = 0;
    string s = "Hello";
}
"""

# Here we've created a class C with integer, bit (1 or 0) and string members. See [here](https://llvm.org/docs/TableGen/ProgRef.html#types) for a full list of types.
#
# Note that you do not have to give a member a default value, it can be left uninitialised.
#

# --- code cell 27 ---
CELL_27 = """
# Jupyter magic removed: %noreset

def X: C {}
"""

# When you make an instance of a class using `def`, that instance gets all the members of the class. Their values will be as set in the class, unless otherwise overridden.
#
# In the case of `a` it also keeps the undefined value. Any backend using that definition would have to check for that case.
#

# --- code cell 29 ---
CELL_29 = """
# Jupyter magic removed: %noreset

def Y {
    int a = "abc"
}
"""

# Here we see the type checking in action. Member `a` has type `int` so we cannot assign a `string` to it.
#
# ## Let
#
# If we want to override those member values we can use `let` ([documented here](https://llvm.org/docs/TableGen/ProgRef.html#let-override-fields-in-classes-or-records)). This can be done in a couple of ways. The first is where you mark the scope of the `let` using `in {}`.
#
# `let <name>=<value> in {`
#
# The code below says that within the `{}` after the `let`, all `a` should have the value 5.
#

# --- code cell 33 ---
CELL_33 = """
class C {
    int a = 9;
}
let a=5 in {
    def X: C {}
}
"""

# For multiple names, separate them with a comma.
#

# --- code cell 35 ---
CELL_35 = """
class C {
    int a;
    int b;
}
let a=5, b=6 in {
    def X: C {}
}
"""

# You can also use `let` within a `def`. This means the scope of the `let` is the same as the scope of the `def` (the def's `{...}`).
#

# --- code cell 37 ---
CELL_37 = """
class C {
    int a = 9;
}
def X: C {
    let a=5;
}
def Y: C {}
"""

# Note that `Y` has `a` as `9` because the `let` was only applied to `X`.
#
# It is an error to try to `let` a name that hasn't been defined or to give it a value of the incorrect type.
#

# --- code cell 39 ---
CELL_39 = """
class C {
    int a = 9;
}
def X: C {
    let a="Hello";
}
"""

# Above, the member `a` was defined but with a type of `int`. We therefore cannot `let` it have a value of type `string`.
#

# --- code cell 41 ---
CELL_41 = """
class C {
    int a = 9;
}
def X: C {
    let b=5;
}
"""

# Above, class `C` only has one member, `a`. Therefore we get an error trying to override the value of `b` which doesn't exist.
#
# If you have multiple let, the outer scope is applied first then on down to the narrowest scope.
#

# --- code cell 43 ---
CELL_43 = """
class Base {
    int var=4;
}
let var=5 in {
    def X: Base {}
    let var=6 in {
        def Y: Base {}
    }
    def Z: Base { let var=7; }
}
"""

# The first `let` is at what we call the "top level". That means the outer most scope in terms of the source code. A bit like a global variable in a C file.
#
# This is applied first and changes `var` from `4` to `5` for all classes within that `let` (`4` came from the definition of `Base`).
#
# def `X` is within the global `let`, therefore `var` is `5` within `X`.
#
# Then we have a `let` inside the global `let`. This one changes `var` from `5` to `6`. The scope of the `let` only contains the def `Y` therefore within `Y`, `var` is `6`.
#
# Finally def `Z` is within the global `let`, so `var` starts as `5`. `Z` has an inner `let` that changes `var` to `7`.
#
# That example is quite complex just to demonstrate the feature. Let's look at something more practical.
#

# --- code cell 45 ---
CELL_45 = """
class Register {
    int size=4;
}
let size=8 in {
    def X0: Register {}
    // Repeats 30 times for X1...X31
}
def W0: Register {}
// Repeats 30 times for W1...W31
"""

# (for anyone curious that's AArch64's register naming)
#
# The use case here is that we are describing registers. Some are 32 bits wide and some are 64 bits wide.
#
# We start by setting a default value of `size` which is 4 (4x8=32 bits) in the class `Register`. Then using a top level `let` we override that value and set it to 8 for all the 64 bit registers at once. So we don't need to do `size=8` over and over again.
#
# ## Classes As Class Members
#
# In addition to the built in types, class members can be user defined classes.
#

# --- code cell 49 ---
CELL_49 = """
class Inner {}
class Outer {
    Inner i;
}
"""

# Of course that raises the question, how do we construct an instance of `Inner` to use as the value?
#
# We simply use a `def` like we have done before.
#

# --- code cell 51 ---
CELL_51 = """
class Inner {}
def AnInner: Inner {}
class Outer {
    Inner i = AnInner;
}
def AnOuter: Outer {}
"""

# ## Class Template Arguments
#
# Class template arguments are used to pass parameters to classes when you `def` them.
#

# --- code cell 54 ---
CELL_54 = """
class C <int a, int b> {
    int c = a;
    int d = b;
}
def X: C<0, 1> {}
"""

# This means that to `def` a `C` we must now provide 2 arguments that have type `int` (type checking applies here as it does elsewhere).
#
# This is going to look familiar if you have written C++. In C++ it might look like:
# ```
# template<int a, int b>
# class C {
#     int c = a;
#     int d = b;
# };
# C<0, 1> X;
# ```
#
# If templates aren't your thing, another way to think of them is as parameters to the constructor of a class. 
#
# For instance Python code might look like this:
# ```
# class C(object):
#     def __init__(self, a, b):
#         self.c = a
#         self.d = b
#
# print(C(0, 1).c)
# # prints "0"
# ```
#

# --- code cell 56 ---
CELL_56 = """
class C <int a, int b> {
    int c = a;
    int d = b;
}
def X: C<0> {}
"""

# When not enough arguments are provided, you get an error.
#
# Below is what happens when one of those arguments is of the wrong type.
#

# --- code cell 58 ---
CELL_58 = """
class C <int a, int b> {
    int c = a;
    int d = b;
}
def X: C<0, "hello"> {}
"""

# You can also provide default values for template arguments.
#

# --- code cell 60 ---
CELL_60 = """
class C <int a=10> {
    int b = a;
}
def X: C<> {}
"""

# Using class template arguments you can enforce a structure on the user of the classes. In our previous register example I could use this to require the the user pass a value for the size.
#
# The code below makes the size argument mandatory but the alias optional.
#

# --- code cell 62 ---
CELL_62 = """
class Register<int _size, string _alias=""> {
    int size = _size;
    string alias = _alias;
}
def X0: Register<8> {}
def X29: Register<8, "frame pointer"> {}
"""

# **Note:** You can't reuse the name between the template argument and the class member.
# Here I have added `_` to the template argument but there's no required style.
#
# For `X0` we don't pass an alias so we get the default of `""`, which would mean there is no alias.
#
# For `X29` we've passed a value for the alias, which overrides the default value.
#
# In C++, the equivalent would be:
# ```
# // Constructor for class Register
# Register(int size, const char* alias=nullptr) :
# ```
#
# Or in Python:
# ```
# def __init__(self, size, alias=""):
# ```
#
