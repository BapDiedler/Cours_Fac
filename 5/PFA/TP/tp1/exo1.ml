(*module signature*)
module type Frac =
sig
  type frac
  val sign : int -> int
  val simp : frac -> frac
  val frac : int -> int -> frac
  val string_of_frac : frac -> string
  val float_of_frac : frac -> float
  val add_frac : frac -> frac -> frac
  val neg_frac : frac -> frac
  val sub_frac : frac -> frac -> frac
  val mul_frac : frac -> frac -> frac
  val inv_frac : frac -> frac
  val div_frac : frac -> frac -> frac
end

(*module de la fraction qui hérite de sa signature*)
module Frac : Frac =
struct

  type frac = {num : int; denom : int}(*représentatiion d'une fraction*)
  

  (*pgcd d'Euclide récursif*)
  let rec pgcd a b =
    if b = 0 then
      a
    else
      pgcd b (a mod b)


  (*sign i renvoie 1, -1 ou 0 selon que i est positif, négatif ou nul*)
  let sign i =
    if i < 0 then
      -1
    else if i > 0 then
      1
    else
      0


  (*simp f qui simplifie la fraction f et s’assure que b est positif*)
  let simp f =
    let num = f.num in
    let denom = f.denom in
    if sign denom = 1 then
      let tmp = pgcd num denom in
      {num = num/tmp ; denom = denom/tmp}
    else if sign denom = 0 then
      f
    else
      let tmp = pgcd num (abs denom) in
      {num = num/tmp ; denom = denom/tmp}
  

  (*frac a b : renvoie la fraction ayant pour numérateur a et pour dénominateur b*)
  let frac a b = {num = a ; denom = b}


  (*string_of_frac f : convertit la fraction f en chaîne de caractères*)
  let string_of_frac f =
    string_of_int f.num ^ "/" ^ string_of_int f.denom


  (*add_frac f1 f2 : additionne les deux fractions*)
  let add_frac f1 f2 =
    let num = (f1.num * f2.denom + f2.num * f1.denom) in
    let denom = (f2.denom * f1.denom) in
    let f_aux = frac num denom in
    simp f_aux


  (*neg_frac f : renvoie l’opposé de f*)
  let neg_frac f =
    frac (-f.num) f.denom


  (*sub_frac f1 f2 : soustrait les deux fractions*)
  let sub_frac f1 f2 =
    let num = (f1.num * f2.denom - f2.num * f1.denom) in
    let denom = (f2.denom * f1.denom) in
    let f_aux = frac num denom in
    simp f_aux


  (*mul_frac f1 f2 : multiplie les deux fractions*)
  let mul_frac f1 f2 =
    let num = f1.num * f2.num in
    let denom = f1.denom * f2.denom in
    let f_aux = frac num denom in
    simp f_aux


  (*inv_frac f : renvoie l’inverse de f*)
  let inv_frac f =
    frac f.denom f.num


  (*div_frac f1 f2 : divise les deux fractions*)
  let div_frac f1 f2 =
    mul_frac f1 (inv_frac f2)


  (*float_of_frac f : convertit la fraction en nombre flottan*)
  let float_of_frac f =
    (float f.num) /. (float f.denom)
end







(*ESPACE DE CODE TESTE*)

let pr_frac a b =
  Printf.printf "%d / %d : %s\n" a b (Frac.string_of_frac (Frac.frac a b))

let print_frac f =
  Printf.printf "%s\n" (Frac.string_of_frac f)

let test_0 () =
  pr_frac 2 4;
  pr_frac 2 8;
  pr_frac 1 10

let test_1 () =
  pr_frac (-1) 2;
  pr_frac (-2) (-10);
  pr_frac 1 (-6)

let test_2 () =
  print_frac (Frac.(simp (frac 2 4)));
  print_frac (Frac.(simp (frac 2 (-4))))

let () =
  test_0 ();
  test_1 ();
  test_2 ()








(*fonctions de la question 8*)
let rec fof_aux f =
  let r, i = modf f in
  let fi = (Frac.frac (int_of_float i) 1) in
  if r < 0.001 then
    fi
  else
    Frac.(add_frac fi
    (inv_frac (fof_aux (1.0 /. r))))

let frac_of_float f =
  let s = if f < 0.0 then -1 else 1 in
  Frac.(mul_frac (frac s 1) (fof_aux (abs_float f)))


let test_0 () =
  print_frac(frac_of_float 0.5);
  print_frac(frac_of_float 1.5);
  print_frac(frac_of_float 2.);
  print_frac(frac_of_float 0.0)

let () =
  test_0 ()



(*1.2 nombres*)

(*type représentant un nombre*)
type num = Int of int | Float of float | Frac of Frac.frac


(*passage de num à string*)
let string_of_num n =
  match n with
  | Int(n) -> string_of_int n
  | Float(n) -> string_of_float n
  | Frac(n) -> Frac.string_of_frac n


(*fonction qui permet de faire des opération sur le type num*)
let exec_op n1 n2 op_i op_fr op_fl =
  match n1, n2 with
  | Float fl1, Float fl2 -> Float (op_fl fl1 fl2)
  | Frac fl1, Frac fl2 -> Frac (op_fr fl1 fl2)
  | Int fl1, Int fl2 -> Int (op_i fl1 fl2)
  | Float fl1, Frac fl2 -> Float (op_fl fl1 (Frac.float_of_frac fl2))
  | Float fl1, Int fl2 -> Float (op_fl fl1 (float_of_int fl2))
  | Frac fl1, Float fl2 -> Float (op_fl (Frac.float_of_frac fl1) fl2)
  | Int fl1, Float fl2 -> Float (op_fl (float_of_int fl1) fl2)
  | Frac fl1, Int fl2 -> Frac (op_fr fl1 (frac_of_float (float fl2)))
  | Int fl1, Frac fl2 -> Frac (op_fr (frac_of_float (float fl1)) fl2)


(*add_num n1 n2 : additionne les deux nombres*)
let add_num n1 n2 =
  exec_op n1 n2 (+) Frac.add_frac (+.)


(*sub_num n1 n2 : soustrait les deux nombres*)
let sub_num n1 n2 =
  exec_op n1 n2 (-) Frac.sub_frac (-.)


(*mul_num n1 n2 : multiple les deux nombres*)
let mul_num n1 n2 =
  exec_op n1 n2 ( * ) Frac.mul_frac ( *.)


(*div_num n1 n2 : divise les deux nombres*)
let div_num n1 n2 =
  exec_op n1 n2 (/) Frac.div_frac (/.)


(*all_of_num n qui étant donné une valeur n de type num, renvoie le triplet d’un
entier, une fraction et un flottant le représentant*)
let all_of_num n =
  match n with
  | Float n -> ((int_of_float n), n, frac_of_float n)
  | Int n -> (n, float_of_int n, frac_of_float (float_of_int n))
  | Frac n -> (int_of_float (Frac.float_of_frac n),Frac.float_of_frac n,n)


(*num_of_string s convertit une chaîne de caractère en num*)
let num_of_string s =
  if String.index_opt s '.' <> None then
    Float(float_of_string s)
  else
    match String.index_opt s '/' with
    | None -> Int (int_of_string s)
    | Some i -> let s1 = String.sub s 0 i in
        let s2 = String.sub s (i+1) (String.length(s)-i+1) in
        Frac(Frac.frac (int_of_string s1) (int_of_string s2))


let num_of_string_opt s =
  try Some ( num_of_string s) with _ -> None


let op_of_string_opt s =
  match s with
  | "+" -> Some(add_num)
  | "-" -> Some(sub_num)
  | "*" -> Some(mul_num)
  | "/" -> Some(div_num)
  | _ -> None


let rec read_until f =
  let s = read_line() in
  match f s with
  | Some v -> v
  | None -> read_until f


let rec calcul () =
  Printf.printf "entrez un opérateur :\n"
  