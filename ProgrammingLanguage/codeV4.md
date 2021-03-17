```js
wire TurnLightOn
{
    meta:
        author = "John Doe"
        description = "this is stuff"
    inputs:
        PSB-001 == "high"
        LTS-001 >= "50"
    outputs:
        LED-001 = "high"
}
```