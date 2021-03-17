```js
wire ctn_name
{
    meta:
        description = "this is a virtual connection"
        comments = "anything you like"
    
    inputs:
        $in1 = "PSB-001"
        $in2 = "PSB-002"
    outputs:
        $out1 = "LED-001"
    
    condition:
        $in1 && !$in2
}
```

Similar to LARA configuration language.
Declare inputs, declare outputs, define what causes output to fire.
Everything in meta ignored.