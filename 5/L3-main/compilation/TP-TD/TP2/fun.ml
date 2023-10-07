(**
   Sémantique et interprétation de FUN
*)

type expr =
    | Cst of int
    | Var of string
    | Let of string * expr * expr
    | Add of expr * expr
    | Mul of expr * expr
    | Lt of expr * expr
    | If of expr * expr * expr
    | Fun of string * expr
    | App of expr * expr
    | Fix of string * expr
    (* Tuple *)
    | Pair of expr * expr
    | Fst of expr
    | Snd of expr
    (* bool *)
    | True
    | False
    | Not of expr
    | And of expr * expr
    | Eq of expr * expr

type value =
    | VCst of int
    | VClos of string * expr * env
    | VPair of value * value
    | VBool of bool

and env = (string * value) list

let rec eval (e : expr) (env : env) : value =
  match e with
  | Cst n -> VCst n
  | Var x -> List.assoc x env
  | Let (x, e1, e2) ->
      let v1 = eval e1 env in
      eval e2 ((x, v1) :: env)
  | Add (e1, e2) ->
      let v1 = eval e1 env in
      let v2 = eval e2 env in
      let n =
        match (v1, v2) with
        | VCst n1, VCst n2 -> n1 + n2
        | _ -> assert false
      in
      VCst n
  | Mul (e1, e2) ->
      let v1 = eval e1 env in
      let v2 = eval e2 env in
      let n =
        match (v1, v2) with
        | VCst n1, VCst n2 -> n1 * n2
        | _ -> assert false
      in
      VCst n
  | Lt (e1, e2) ->
      let v1 = eval e1 env in
      let v2 = eval e2 env in
      let b =
        match (v1, v2) with
        | VCst n1, VCst n2 ->
            if n1 < n2 then
              true
            else
              false
        | _ -> assert false
      in
      VBool b
  | If (c, e1, e2) -> (
      match eval c env with
      | VBool b ->
          if b then
            eval e1 env
          else
            eval e2 env
      | _ -> assert false)
  | Fun (x, e) -> VClos (x, e, env)
  | App (f, a) -> (
      let vf = eval f env in
      let va = eval a env in
      match vf with
      | VClos (x, b, envclos) -> eval b ((x, va) :: envclos)
      | _ -> assert false)
  | Fix (f, e) -> (
      match eval e env with
      | VClos (x, b, envclos) ->
          let rec vfix = VClos (x, b, (f, vfix) :: envclos) in
          vfix
      | _ -> assert false)
  (* Tuple *)
  | Pair (e1, e2) -> VPair (eval e1 env, eval e2 env)
  | Fst e -> (
      match eval e env with
      | VPair (v1, v2) -> v1
      | _ -> assert false)
  | Snd e -> (
      match eval e env with
      | VPair (v1, v2) -> v2
      | _ -> assert false)
  (* Bool *)
  | True -> VBool true
  | False -> VBool false
  | And (e1, e2) -> (
      match eval e1 env with
      | VBool b ->
          if b then
            eval e2 env
          else
            VBool false
      | _ -> assert false)
  | Not e -> (
      match eval e env with
      | VBool b -> VBool (not b)
      | _ -> assert false)
  | Eq (e1, e2) -> (
      let v1 = eval e1 env in
      let v2 = eval e2 env in
      match (v1, v2) with
      | VCst n1, VCst n2 -> VBool (n1 = n2)
      | VPair (v1, v2), VPair (v3, v4) -> VBool (v1 = v3 && v2 = v4)
      | VClos (_, _, _), VClos (_, _, _) -> VBool (v1 == v2)
      | _ -> assert false)

let efact =
  Fix
    ( "f",
      Fun
        ( "n",
          If
            ( Lt (Var "n", Cst 1),
              Cst 1,
              Mul (Var "n", App (Var "f", Add (Var "n", Cst (-1)))) ) ) )

let efact6 = Let ("fact", efact, App (Var "fact", Cst 6));;

assert (eval efact6 [] = VCst 720);;
print_string "test ok\n"
