(**
   Sémantique et interprétation de IMP
*)

type expr =
    | Cst of int
    | Var of string
    | Add of expr * expr
    | Mul of expr * expr
    | Lt of expr * expr
    | Call of string * expr list

type instr =
    | Set of string * expr
    | If of expr * instr list * instr list
    | While of expr * instr list
    | Switch of expr * (int * instr list) list * instr list
    | Break
    | Continue
    | Def of string * string list * string list * instr list
    | Return of expr

type prog = instr list

(* variable *)
type value = int
type env = (string, value) Hashtbl.t

(* Function *)
type fundef = {
    params : string list;
    locals : string list;
    code : instr list;
  }

type funEnv = (string, fundef) Hashtbl.t

type ret =
    | REnd
    | RBreak
    | RCont
    | RRet of value

let rec eval (e : expr) (env : env) (funenv : funEnv) : value =
  match e with
  | Cst n -> n
  | Var x -> Hashtbl.find env x
  | Add (e1, e2) ->
      let v1 = eval e1 env funenv in
      let v2 = eval e2 env funenv in
      v1 + v2
  | Mul (e1, e2) ->
      let v1 = eval e1 env funenv in
      let v2 = eval e2 env funenv in
      v1 * v2
  | Lt (e1, e2) ->
      let v1 = eval e1 env funenv in
      let v2 = eval e2 env funenv in
      if v1 < v2 then
        1
      else
        0
  | Call (name, var) -> (
      let { params; locals; code } = Hashtbl.find funenv name in
      let rec setparams params name =
        match (params, name) with
        | [], [] -> ()
        | p :: l1, n :: l2 -> Hashtbl.add env n (eval p env funenv)
        | _, _ -> assert false
      in
      setparams var params;
      List.iter (fun x -> Hashtbl.add env x 0) locals;
      let ret = execb code env funenv in
      List.iter (Hashtbl.remove env) locals;
      List.iter (Hashtbl.remove env) params;
      match ret with
      | RRet x -> x
      | REnd -> 0
      | _ -> assert false)

and execi (i : instr) (env : env) (funenv : funEnv) : ret =
  match i with
  | Set (x, e) ->
      let v = eval e env funenv in
      Hashtbl.replace env x v;
      REnd
  | If (e, b1, b2) ->
      let v = eval e env funenv in
      if v = 0 then
        execb b1 env funenv
      else
        execb b2 env funenv
  | While (e, b) -> (
      let v = eval e env funenv in
      if v = 0 then
        REnd
      else
        match execb b env funenv with
        | REnd | RCont -> execi i env funenv
        | r -> r)
  | Switch (e, cases, def) ->
      let v = eval e env funenv in
      let rec case = function
        | [] -> execb def env funenv
        | (n, b) :: l ->
            if n = v then
              execb def env funenv
            else
              case l
      in
      case cases
  | Continue -> RCont
  | Break -> RBreak
  | Return e -> RRet (eval e env funenv)
  | Def (nom, param, var, i) ->
      let functiondef = { params = param; locals = var; code = i } in
      Hashtbl.add funenv nom functiondef;
      REnd

and execb (b : instr list) (env : env) (funenv : funEnv) : ret =
  match b with
  | [] -> REnd
  | i :: b' -> (
      match execi i env funenv with
      | REnd -> execb b' env funenv
      | r -> r)

let ifact =
  While
    ( Lt (Cst 0, Var "n"),
      [ Set ("r", Mul (Var "r", Var "n")); Set ("n", Add (Var "n", Cst (-1))) ]
    )

let deffunction = Def ("f", [ "r" ], [], [Set("r", Cst 3); Return (Var "r") ])
let callfunction = Call ("f", [ Cst 3 ])

let bfact6 =
  [
    deffunction;
    Set ("r", callfunction);
    Set ("n", Cst 6);
    Set ("r", Cst 1);
    ifact;
  ]

let () =
  let env = Hashtbl.create 8 in
  let funenv = Hashtbl.create 8 in
  let _ = execb bfact6 env funenv in
  assert (Hashtbl.find env "r" = 720)
;;

print_string "test ok\n"
