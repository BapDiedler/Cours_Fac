let rec double_s n =
  if n<0 then
    failwith "fonction_non_valide"
  else if n = 0 then
    0
  else
    2 + (double_s(n-1))

let double_s_terminal n =
  let rec double_aux n acc =
    if n<0 then
      failwith "fonction_non_valide"
    else if n = 0 then
      acc
    else
      double_aux (n-1) (acc+2)
  in
  double_aux n 0 

let somme_n_premiers_entiers n =
  let rec loop n acc =
    if n<0 then
      failwith "argument_non_valide"
    else if n=0 then
      acc
    else
      loop (n-1) (acc+n)
  in loop n 0

let somme_n_premiers_entiers_pairs n =
  let rec loop n acc =
    if n<0 then
      failwith "argument_non_valide"
    else if n=0 then
      acc
    else
      loop (n-2) (acc+n)
  in
  if n mod 2 = 0 then
    loop n 0
  else
    loop (n-1) 0

let somme_entiers_p_a_q p q =
  let rec loop p q acc =
    if p > q then
      acc
    else if p = q then
      acc + p
    else
      loop (p+1) (q-1) (acc + p + q)
  in
  loop p q 0


let dernier_chiffre_2_n n =
  if n<0 then
    failwith "argument_non_valide"
  else if n = 0 then
    1
  else
    match (n mod 4) with
    | 1 -> 2
    | 0 -> 6
    | 2 -> 4
    | 3 -> 8
    | _ -> failwith "argument_non_valide"

let rec y_a_t_il_un_0 n =
  if n < 0 then
    failwith "argument_non_valide"
  else if n = 1 then
    false
  else if n mod 2 = 0 then
    true
  else
    y_a_t_il_un_0 (n/2)





let () =
    Printf.printf "%b\n" (y_a_t_il_un_0 3)