(* Exercice1 *)

(* 1 *)

let fac n =
  let rec aux n acc =
    if n = 0 then
      acc
    else
      aux (n - 1) (n * acc)
  in
  aux n 1

let _ =
  assert (fac 2 = 2);
  assert (fac 3 = 6);
  assert (fac 4 = 24)

(* 2 *)
let nb_bit_pos n =
  let rec aux n acc =
    if n == 0 then
      acc
    else
      aux (n / 2) (acc + (n mod 2))
  in
  aux n 0

let _ =
  assert (nb_bit_pos 0b0 = 0);
  assert (nb_bit_pos 0b1 = 1);
  assert (nb_bit_pos 0b10 = 1);
  assert (nb_bit_pos 0b11 = 2)

(* Exercice 2 *)

(* 1 *)
let rec fibo n =
  let rec aux n acc1 acc2 =
    if n = 0 then
      acc1
    else if n = 1 then
      acc2
    else
      aux (n - 1) acc2 (acc2 + acc1)
  in
  aux n 0 1

let _ =
  assert (fibo 0 = 0);
  assert (fibo 1 = 1);
  assert (fibo 2 = 1);
  assert (fibo 3 = 2);
  assert (fibo 4 = 3);
  assert (fibo 5 = 5);
  assert (fibo 6 = 8)

(* Exercice 3 *)

(* 1 *)
let palindrome s =
  let mid_string = String.length s / 2 in
  let rec aux d f = d >= mid_string || (s.[d] = s.[f] && aux (d + 1) (f - 1)) in
  aux 0 (String.length s - 1)

let _ =
  assert (palindrome "aba");
  assert (not (palindrome "abac"))

(* 2 *)
let compare m1 m2 =
  let l1 = String.length m1 in
  let l2 = String.length m2 in
  let rec aux i =
    i >= l1 || (i < l2 && m1.[i] < m2.[i]) || (m1.[i] = m2.[i] && aux (i + 1))
  in
  aux 0

let _ =
  assert (compare "a" "b");
  assert (compare "aa" "ab");
  assert (not (compare "b" "a"));
  assert (compare "ac" "acd")

let compare m1 m2 =
  let l1 = String.length m1 in
  let l2 = String.length m2 in
  let rec aux i =
    i >= l1 || (i < l2 && m1.[i] < m2.[i]) || (m1.[i] = m2.[i] && aux (i + 1))
  in
  aux 0

let _ =
  assert (compare "a" "b");
  assert (compare "aa" "ab");
  assert (not (compare "b" "a"));
  assert (compare "ac" "acd")

(* 3 *)
let facteur m1 m2 =
  let l1 = String.length m1 in
  let l2 = String.length m2 in
  let rec facteur_index i =
    let rec sub_facteur p =
      p >= l1 || (i + p < l2 && m1.[p] = m2.[i + p] && sub_facteur (p + 1))
    in
    i < l2 && ((m1.[0] = m2.[i] && sub_facteur 1) || facteur_index (i + 1))
  in
  facteur_index 0

let _ =
  assert (facteur "bc" "abcde");
  assert (not (facteur "be" "abcde"))

(* Exercice 4 *)

(* 1 *)
let split l =
  let rec split_rec l1 l2 = function
    | [] -> (l1, l2)
    | x :: l -> split_rec l2 (x :: l1) l
  in
  split_rec [] [] l

(* 2 *)
let rec merge l1 l2 =
  match (l1, l2) with
  | [], l | l, [] -> l
  | x :: t1, y :: t2 ->
      if x < y then
        x :: merge t1 l2
      else
        y :: merge l1 t2

let rec tri l =
  match l with
  | [] | [ _ ] -> l
  | _ ->
      let l1, l2 = split l in
      merge (tri l1) (tri l2)

let _ =
  let l = [ 8; 1; 6; 5; 2; 9; 10; 7; 3; 4 ] in
  let lt = tri l in
  let rec verif prec = function
    | [] -> ()
    | x :: l ->
        if x < prec then
          assert false
        else
          verif x l
  in
  verif 0 lt

(* Exercice 5 *)

(* 1 *)
let rec somme_carre1 = function
  | [] -> 0
  | x :: l -> (x * x) + somme_carre1 l

let somme_carre2 l = List.fold_left (fun acc x -> acc + (x * x)) 0 l

let _ =
  let l = [ 1; 2; 3 ] in
  assert (somme_carre1 l = 14);
  assert (somme_carre2 l = 14)

(* 2. *)

let find_opt1 x l =
  let rec find_index i = function
    | [] -> None
    | h :: t ->
        if h = x then
          Some i
        else
          find_index (i + 1) t
  in
  find_index 0 l

let find_opt2 x l =
  snd
    (List.fold_left
       (fun (i, opt) h ->
         match opt with
         | Some i -> (0, Some i)
         | None ->
             if h = x then
               (0, Some i)
             else
               (i + 1, None))
       (0, None) l)

(* Exercie 6 *)

let l = List.init 1_000_001 (fun i -> i)

let rev =
  let rec rev_rec acc = function
    | [] -> acc
    | x :: l -> rev_rec (x :: acc) l
  in
  rev_rec []

let rec map f = function
  | [] -> []
  | a :: l ->
      let r = f a in
      r :: map f l

(* Exercice 7 *)

let rec concat l1 l2 =
  match l1 with
  | [] -> l2
  | x :: s -> x :: concat s l2

type 'a seq =
    | Elt of 'a
    | Seq of 'a seq * 'a seq

let ( @@ ) x y = Seq (x, y)
let a1 = Seq (Elt 1, Seq (Elt 2, Elt 3))
let a2 = Seq (Seq (Elt 1, Elt 2), Elt 3)
(* 1 *)

let rec hd = function
  | Seq (x, _) -> hd x
  | Elt x -> x

let rec tl = function
  | Seq (Elt x, y) -> y
  | Seq (x, y) -> Seq (tl x, y)
  | Elt x -> Elt x

let rec mem elt = function
  | Seq (x, y) -> mem elt x || mem elt y
  | Elt x -> x = elt

let rec fold_left f acc = function
  | Elt x -> f acc x
  | Seq (x, y) ->
      let acc' = fold_left f acc x in
      fold_left f acc' y

let rec fold_right f acc = function
  | Elt x -> f acc x
  | Seq (x, y) ->
      let acc' = fold_right f acc y in
      fold_right f acc' x

(* 2 *)
let seq2list s =
  let rec seq_rec s acc =
    match s with
    | Seq (x, y) ->
        let acc' = seq_rec x acc in
        seq_rec y acc'
    | Elt x -> x :: acc
  in
  seq_rec s []

let seq2listBis s =
  let rec seq2listBisAux acc = function
    | [] -> acc
    | Elt x :: l -> seq2listBisAux (x :: acc) l
    | Seq (s1, s2) :: l -> seq2listBisAux acc (s1 :: s2 :: l)
  in
  seq2listBisAux [] [ s ]

(* 3 *)

type find =
    | Found of int
    | Indice of int

let find_opt x' s =
  let rec find_rec i = function
    | Elt x when x = x' -> Found i
    | Elt x -> Indice (i + 1)
    | Seq (s1, s2) -> (
        match find_rec i s1 with
        | Found i -> Found i
        | Indice i -> find_rec i s2)
  in
  match find_rec 0 s with
  | Indice _ -> None
  | Found i -> Some i

(* 4 *)
let nth s n =
  let rec nth_rec i = function
    | Elt x when i = n -> Found x
    | Elt x -> Indice (i + 1)
    | Seq (l, r) -> (
        match nth_rec i l with
        | Found x -> Found x
        | Indice i -> nth_rec i r)
  in
  match nth_rec 0 s with
  | Found x -> x
  | Indice _ -> raise (Invalid_argument "index is out of bounds")

let ( ++ ) x y = Seq (x, y)
let a = Elt "a" ++ Elt "a" ++ Elt "b" ++ Elt "c" ++ Elt "a" ++ Elt "a"
