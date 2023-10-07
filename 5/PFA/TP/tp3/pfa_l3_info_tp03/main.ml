open Tree (* on « importe » les définitions de tree.ml *)

let dump filename t = Draw.draw (fun i -> Printf.sprintf "%d" i) filename t

let test1 () =
  let t1 = add 1 (add 2 (add 3 empty)) (* = Leaf *) in
  let () = dump "img/test_1_1.svg" t1 in
  let t2 = add 42 (add 43 (add 44 t1)) in
  dump "img/test_1_2.svg" t2

let test2 () =
  let t1 = union empty (add 3 empty) in
  let () = dump "img/test_2_1.svg" t1 in
  let t2 = union (add 4 empty) (t1) in
  dump "img/test_2_2.svg" t2

let test3 () =
  let t1 = add 2 (add 3 empty) in
  dump "img/test_3_1.svg" t1;
  Printf.printf "le test3 est %b\n" (is_empty empty && not (is_empty t1))

let test4 () =
  let t1 = add 1 (add 2 (add 3 empty)) in
  let t2 = add 42 (add 43 (add 44 t1)) in
  dump "img/test_4_1.svg" t2;
  dump "img/test_4_2.svg" t1;
  Printf.printf "le test4 est %b\n" (mem 44 t2 && not (mem 44 t1))

let test5() =
  let t1 = add 1 (add 2 (add 3 empty)) in
  dump "img/test_5_1.svg" t1;
  let cpt = ref 0 in
  iter (fun i -> cpt:=!cpt+1) t1;
  Printf.printf "nb éléments %d\n" !cpt;
  iter (fun i -> Printf.printf "%d\n" i) t1

let test6() =
  let t1 = add 1 (add 2 (add 3 empty)) in
  dump "img/test_6_1.svg" t1;
  let size = fold (fun _ acc -> 1 + acc) t1 0 in
  Printf.printf "le test6 est %b\n" (size==3)

let test7() =
  let t1 = add 1 (add 2 (add 3 empty)) in
  iter_fold (fun i -> Printf.printf "%d\n" i) t1

let test8() =
  let t1 = add 1 (add 2 (add 3 empty)) in
  let t2 = add 42 (add 43 (add 44 t1)) in
  dump "img/test_8_1.svg" t2;
  let res = partition (fun i -> i>=43) t2 in
  dump "img/test_8_2.svg" (fst res);
  dump "img/test_8_3.svg" (snd res)

let test9()=
  let t1 = add 1 (add 2 (add 3 empty)) in
  let t2 = add 42 (add 43 (add 44 t1)) in
  Printf.printf "le test9 est %b\n" (not(subset t2 t1) && (subset t1 t2))

let test10()=
  let t1 = add 1 (add 6 (add 3 empty)) in
  List.iter (fun i -> Printf.printf "%d\n" i) (element t1)


let tree_of_height h n b =
  let rec loop f h n =
    match h with
    | 0 -> empty
    | l -> add n (loop f (h-1) (f n))
  in
  if b then
    loop (fun i -> i+1) h (n+1)
  else
    loop (fun i -> i-1) h (n-1)

let test_tree_of_height() =
    dump "img/test_new_1.svg" (tree_of_height 5 3 false)

let test_join()=
  let t1 = tree_of_height 5 3 false in
  let t2 = tree_of_height 2 9 true in
  dump "img/test_join.svg" (join_avl t1  6 t2)

let () = test_join()