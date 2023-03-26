# Functions

## Functions without return type

You can quickly create a function like this:

```
hello {
    "Hello world!";
}
```

Now the variable `hello` has a function in it. Note that we didn't use the `=` operand. If we have to call a function we simple use pharentesis:

```
hello(); # Hello world!
```

If we want to pass some arguments to our function, we can specify these after the `:`, as the following example:

```py
append: a, b {
    a + b;
}

append(2,3); # 5
append("Hello", "World"); # HelloWorld
append("Number: ", 7); # Number: 7
```

You can also pass fixed variables:

```py
add: int a, int b {
    a + b;
}

add(3,4); # 7
add(-45, 89); # 54
add(3, "h"); # Error
```

## Functions with return type
Functions can also return values. If we want a function that can return a dynamic variable (whose type is dynamic), we don't need to write anything at the declaration:

```py
add: a, b {
    return a + b;
}

add(5,4); # 9
add(add(1,2), add(3,4)); # 10
add(add(add(add("Hel", "lo"), " "), "World"), "!"); # Hello World!
```

```py
multiply: a, int b {
    return a * b;
}

multiply(3,5); # 15
multiply("Hi!", 4); # Hi!Hi!Hi!Hi!
```

If you want to specify a certain return type, you need to write `=>` followed by the return type after the parameters:

```py
multiply: int a, int b => int {
    return a * b;
}

multiply(3,4); # 12
multiply(3,5) + 3; # 18
```