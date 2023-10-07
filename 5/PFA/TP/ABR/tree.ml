type 'a tree = Leaf | Node of ('a tree * 'a * 'a tree)

let is_empty t =
  match t with
  | Leaf -> true
  | _ -> false

let exist v t =
  match t with
  | Leaf -> false
  | Node(l, i, r) ->