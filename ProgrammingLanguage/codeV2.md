# IZ Language Version 2 #


### Supplemental Info ###
The control panel will have a list of devices currently connected.
They will be classified with an IP, an ID, a type (input/output) and an editable name.
The editable name or the ID can be used in code to represent a module.

Ex. [192.168.0.200 | 0015 | pushButton | output ]

### Sample Code ###
```lua
--this is a comment

--event listener
if
    pushButton == high
    10293 == low
    lightSensor <= 0.1
then
    led = high
    1222 = 0.5
    rgb = "#FFFFFF" --or rgb = "255,255,255"
end

virtual create Timer5
virtual start Timer5 50 
--virtual [command] [name] [value]
if
    Timer5 == "done"
then
    virtual reset Timer5
end

```

### Virtual Device Protocol ###
- Virtual devices can be created however a user likes; however,
they must implement a READ to allow the program
to check if it has reached a value.
- They must also implement a CREATE
- For simplicity, they only output string values to prevent comparison issues


### Comments ###
We will have single and multi-line comments.
Single = "--", Multi-line = "/* */"

### Extra Notes ###
- Spacing doesn't matter, it will be stripped out
- Code is split by lines, not by ending symbols 