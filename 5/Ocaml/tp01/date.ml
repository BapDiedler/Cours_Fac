let bissextile a =
  a mod 4 = 0 && (a mod 100 <> 0 || a mod 400 = 0)

let jour_moi m a =
  if m < 1 then 0 else
  if m = 2 then
    if bissextile a then
      29
    else
      28
  else
    let x = if m<= 8 then m else m-7 in
      if x mod 2 = 0 then
        30
      else
        31

let rec jour_date j m a =
  if m = 0 then
    0
  else
    let nb_jours = jour_moi (m-1) a in
      let nb_jours_restant = jour_date nb_jours (m-1) a in
        j + nb_jours_restant

let () = 
  let x = jour_date 12 4 2021 in
    Printf.printf "%d\n" x;