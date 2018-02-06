let inc x = x + 1

let rec fact n = match n with
             | 0 -> 1
             | k -> k * (fact (k - 1))
