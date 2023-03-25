# Variables

Variables are a reference to some information in a Wyrm program that have a fixed name. Variables in Wyrm can be of *dynamic type* or of *fixed type*

### Assignation

You can assignate something to a variable using the reserved `=` opperand. For example, the following code will create a variable with the identifier `a` and it will have the integer value `2` stored inside
```
a = 2;
```

## Declaration of variables

### Dynamic type variables

Dynamic type variables are variables that can change their type at runtime.

```
a = 3;
b = 6;
c = "Hello World!";
c = 2;
```

Note that in this case `c` changed type in the last line, because it changed from being an *string* type to an *integer* type.

Dynamic variable types are typically slower because they don't have a fixed type.

It is advised to use instead fixed type variables if performance is a key code in your code.

### Fixed type variables

Fixed type variables are variables that cannot change their type at runtime, therefore their type must be specified at compilation time.

You can declare fixed type variables by specifying their type when the variable is created. You must specify the type before the identifier of the variable.

```
int a; # This variable will be fixed
a = 2;
a = 5;
a = "Hello"; # This will trigger an error
```