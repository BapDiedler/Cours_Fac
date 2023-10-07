let rec somme_entiers n =
  if n <= 0 then
    0
  else
    n + somme_entiers (n-1)

let rec somme_carres n =
  if n<=0 then
    0
  else
    (n*n) + somme_carres (n-1)

let rec leibniz n =
  if n<=0 then
    1.
  else
    let puis = if n mod 2 = 0 then 1. else -1. in
      puis /. (float((2* n)+1)) +. leibniz (n-1)


    let () = Printf.printf "4. *. leibniz 10 = %f\n"  (4. *. leibniz 10)
    let () = Printf.printf "4. *. leibniz 50 = %f\n"  (4. *. leibniz 50)
    let () = Printf.printf "4. *. leibniz 100 = %f\n"  (4. *. leibniz 100)
    let () = Printf.printf "4. *. leibniz 500 = %f\n"  (4. *. leibniz 500)