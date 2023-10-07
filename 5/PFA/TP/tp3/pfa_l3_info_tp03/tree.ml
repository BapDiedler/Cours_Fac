(** Le type générique des Arbres binaires de recherche *)

type ('a, 'info) tree =
  | Leaf
  | Node of ('info * ('a, 'info) tree * 'a * ('a, 'info) tree)

(* Ci-dessous les opérations génériques telles que vues en cours *)

(* Attention, dans les commentaires, les [crochets] indiquent
   que le code entre crochet est une expression OCaml. 
   Cela permet d'afficher joliement la documentation lorsqu'on survole
   un identifiant (par exempl placer la souris au dessus de [split]
   à la ligne 30 ci-dessous.
*)

(** [split join t v] renvoie un triplet [(l, b, r)] où:
  - [l] est l'ensemble des valeurs plus petites que [v] dans [t],
    sous forme d'un arbre
  - [r] est l'ensemble des valeurs plus grandes que [v] dans [t],
    sous forme d'un arbre
  - [b] est un booléen qui indique si [v] était dans l'arbre ou non.
*)
let rec split join t v =
  match t with
  | Leaf -> (Leaf, false, Leaf)
  | Node (_, l, w, r) ->
      let c = compare v w in
      if c = 0 then (l, true, r)
      else if c < 0 then
        let ll, b, lr = split join l v in
        (ll, b, join lr w r)
      else
        let rl, b, rr = split join r v in
        (join l w rl, b, rr)

(** [remove_max_elt join t] renvoie un couple [t',v] où
    - [t'] est l'arbre [t] privé de sa valeur maximale
    - [v] est la valeur maximale retirée de [t]
    La fonction lève une exception si [t] est vide *)
let rec remove_max_elt join t =
  match t with
  | Leaf -> failwith "arbre vide"
  | Node (_, l, v, Leaf) -> (l, v)
  | Node (_, l, v, r) ->
      let t2, v2 = remove_max_elt join r in
      (join l v t2, v2)

(** [merge join l r] fusionne les deux arbres [l] et [r].
    La fonction suppose que toutes les valeurs de [l] sont inférieures
    aux valeurs de [r]*)
let rec merge join l r =
  match (l, r) with
  | Leaf, _ -> r
  | _ ->
      let ll, v = remove_max_elt join l in
      join ll v r

(** [add_gen join v t] ajoute la valeur [v] à [t] *)
let add_gen join v t =
  let l, b, r = split join t v in
  if b then t else join l v r

(** [remove_gen join v t] retire la valeur [v] de [t] *)
let remove_gen join v t =
  let l, b, r = split join t v in
  if b then merge join l r else t

(** [union_gen join t1 t2] renvoie l'union de [t1] et [t2] *)
let rec union_gen join t1 t2 =
  match (t1, t2) with
  | Leaf, _ -> t2
  | _, Leaf -> t1
  | _, Node (_, l2, v2, r2) ->
      let l1, _, r1 = split join t1 v2 in
      let ll = union_gen join l1 l2 in
      let rr = union_gen join r1 r2 in
      join ll v2 rr

(** [inter_gen join t1 t2] renvoie l'intersection de [t1] et [t2] *)
let rec inter_gen join t1 t2 =
  match (t1, t2) with
  | Leaf, _ | _, Leaf -> Leaf
  | _, Node (_, l2, v2, r2) ->
      let l1, b, r1 = split join t1 v2 in
      let ll = inter_gen join l1 l2 in
      (* inter des plus petits que v2 *)
      let rr = inter_gen join r1 r2 in
      (* inter des plus grands que v2 *)
      if b then (* v2 était aussi dans t1 *)
        join ll v2 rr
      else
        (* v2 pas dans t1, il n'est pas dans l'intersection *)
        merge join ll rr

(** [diff_gen join t1 t2] renvoie la différence de [t1] et [t2] *)
let rec diff_gen join t1 t2 =
  match (t1, t2) with
  | Leaf, _ -> Leaf
  | _, Leaf -> t1
  | _, Node (_, l2, v2, r2) ->
      let l1, _, r1 = split join t1 v2 in
      let ll = diff_gen join l1 l2 in
      (* on retire de l1 les plus petits que v2 *)
      let rr = diff_gen join r1 r2 in
      (* on retire de r1 le plus grand que v2*)
      merge join ll rr (* on fusionne, sasn remettre v2 *)


(** le type des AVLs et ses opérations spécifiques *)
type 'a avl = ('a, int) tree

(** [height t] renvoie la hauteur de l'AVL [t]. *)
let height t = match t with Leaf -> 0 | Node (h, _, _, _) -> h

(** Les opérations de constructions spécifiques aux AVL *)
let empty = Leaf

let node l v r = Node (1 + max (height l) (height r), l, v, r)

let rotate_left t =
  match t with
  | Node (_, l, v, Node (_, lr, vr, rr)) -> node (node l v lr) vr rr
  | _ -> failwith "rotate_left"

let rotate_right t =
  match t with
  | Node (_, Node (_, ll, vl, rl), v, r) -> node ll vl (node rl v r)
  | _ -> failwith "rotate_right"

let rec join_avl_right l v r =
  match l with
  | Leaf -> failwith "impossible"
  | Node (_, ll, vl, rl) ->
      if height rl <= height r + 1 then
        let new_r = node rl v r in
        if height new_r <= height ll + 1 then node ll vl new_r
        else rotate_left (node ll vl (rotate_right new_r))
      else
        let new_r = join_avl_right rl v r in
        let new_t = node ll vl new_r in
        if height new_r <= height ll + 1 then new_t else rotate_left new_t


let rec join_avl_left l v r =
  match r with
  | Leaf -> failwith "impossible"
  | Node (_, lr, vr, rr) ->
      if height lr <= height l + 1 then
        let new_l = node l v lr in
        if height new_l <= height rr + 1 then node new_l vr rr
        else rotate_right (node (rotate_left new_l) vr rr)
      else
        let new_l = join_avl_left l v lr in
        let new_t = node new_l vr rr in
        if height new_l <= height rr + 1 then new_t else rotate_right new_t

let join_avl l v r =
  if height l > height r + 1 then join_avl_right l v r
  else if height r > height l + 1 then join_avl_left l v r
  else node l v r


(* On spécialise les opérations génériques par la bonne 
   fonction join *)
let add v t = add_gen join_avl v t
let remove v t = remove_gen join_avl v t
let union t1 t2 = union_gen join_avl t1 t2
let inter t1 t2 = inter_gen join_avl t1 t2
let diff t1 t2 = diff_gen join_avl t1 t2

let is_empty t =
  match t with
  | Leaf -> true
  | _ -> false

let rec mem v t =
  match t with
  | Leaf -> false
  | Node(_,l,tete,r) ->
      if tete==v then
        true
      else if tete<v then
        mem v r
      else
        mem v l

let rec iter f t =
  match t with
  | Leaf -> ()
  | Node(_,l,tete,r) ->
      iter f l;
      f tete;
      iter f r


let rec fold f t acc =
  match t with
  | Leaf -> acc
  | Node(_,l,tete,r)->
      let acc_l = fold f l acc in
      let acc_v = f tete acc_l in
      fold f r acc_v

let iter_fold f t = fold (fun i _ -> f i) t ()


let rec partition f t=
  let res = (empty,empty) in
  match t with
  | Leaf -> res
  | Node(_,l,tete,r) ->
      let resL = partition f l in
      let resR = partition f r in
      let resLR = (union (fst resL) (fst resR), union (snd resL) (snd resR)) in
      if f tete then
        (add tete (fst resLR), snd resLR)
      else
        (fst resLR, add tete (snd resLR))


let rec subset t1 t2 =
  let t3 = inter t1 t2 in
  let size1 = fold (fun _ acc -> 1 + acc) t1 0 in
  let size3 = fold (fun _ acc -> 1 + acc) t3 0 in
  size1 == size3

let element t =
  let rec loop t acc =
    match t with
    | Leaf -> acc
    | Node(_,l,tete,r) ->
        let resL = loop l acc in
        let new_acc = tete::resL in
        loop r new_acc
  in
  loop t []

let rec next l =
  let size t = fold (fun _ i -> 1+i) t 0 in
  List.sort 

let same_fringe t1 t2 =
  failwith "coucou"