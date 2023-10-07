(** Q_1.2 : Créer un module IntSet et une variable globale iset contenant
   un exemple de tel ensemble, non vide *)
module IntSet = Tree.Make(Int)

let iset = IntSet.(
    add 4 (
        add 3 (
            empty
        )
    )
)
let () = Printf.printf "%s\n" (IntSet.to_string iset)

(* Q_1.4 : Tester IntSet.to_string sur l'ensemble iset et afficher la chaîne
    dans la console *)

(* Q1.5: écrire la fonction ci-dessous comme demandée dans l'énoncé
    puis écrire un test pour cette fonction  *)
let subset_without_duplicates l =
    let rec loop l seen arb_aux arb =
        match l with
        []-> arb
        | "--"::ll -> loop ll false IntSet.empty (IntSet.union arb_aux arb)
        | v::ll->
            if seen || IntSet.mem (int_of_string v) arb_aux then
                loop ll true IntSet.empty arb
            else
                let acc_aux = IntSet.add (int_of_string v) arb_aux in
                loop ll false acc_aux arb
            in
    loop l false IntSet.empty IntSet.empty
    
    

(* Q_1.6 : Créer un module Chr puis un module ChrSet *)
module Char : Tree.CompPrint with type t = char =
struct    
    type t = char
    let compare a b = Char.compare a b
    let to_string a = Char.escaped a
end

module CharSet = Tree.Make(Char)

(* Q_1.7 : écrire la fonction charset *)
let charset s =
    String.fold_left (fun set a -> CharSet.add a set) CharSet.empty s

(* Q_1.8 : écrire la fonction only one row ainsi qu'un test *)
let only_one_row l = failwith "todo Q 1.8"

(* Q_2.3 : tests pour remove_min et remove_max *)

(* Q_2.4 : implémenter smallest_such_than en utilisant un iterateur 
          ainsi qu'un test *)
let smallest_such_than p s = failwith "todo Q 2.4"
