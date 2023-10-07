type 'a ab =
    | F
    | N of 'a ab * 'a * 'a ab

let rec infix = function
  | F -> []
  | N (t1, n, t2) -> infix t1 @ (n :: infix t2)

let rec appartient x = function
  | F -> false
  | N (t1, n, t2) -> x = n || appartient x t1 || appartient x t2

let rec appartient_abr x = function
  | F -> false
  | N (t1, n, t2) ->
      n = x || (n > x && appartient_abr x t1) || (n < x && appartient_abr x t2)

let rec verifie min max = function
  | F -> true
  | N (t1, n, t2) ->
      n >= min && n <= max && verifie min n t1 && verifie n max t2
