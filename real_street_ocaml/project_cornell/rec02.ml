let inc x = x + 1

let rec fact n = match n with
             | 0 -> 1
             | k -> k * (fact (k - 1))

let id x = x

let divide ?test:(arg=false) ~num:(x:float) ~denum:(y:float) = if arg then 0.0 else (x /. y)

let ($$) x y = (x +. y) /. 2.0