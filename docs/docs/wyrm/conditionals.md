# Conditional statemens

The conditional statement in Wyrm is the if

The if statement lets you execute code if the tested expression is different of the neutral value of the type associated.

```
# For example, in the Boolean type, the neutral value is False.

if True {
    "This will print";
}

if False {
    "This will not print";
}

# Output: This will print
```

If statements can be followed by an **else** statement, that will run code if the tested expression is equal to the neutral value:
```
if 2 == 3 {
    "This will not print";
} else {
    "This will print";
}

# Output: This will print
```

If statements can also be chained with **else if** statements. When executing, if the first if hasn't succeded, then the second if will be tested, if it hasn't succeded, the third, and this until the code reaches an else or an end of the conditional structure.

```
if 2 == 3 {
    "This doesn't work";
} else if (2 == 2){
    "Second if worked";
} else if (2 == 3){
    "Third if worked";
} else if (3 == 3){
    "Fourth if worked";
} else {
    "Nothing happened!";
}

# Output: Second if worked
```