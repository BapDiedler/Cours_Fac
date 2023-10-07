let guess n =
  let rec guess_aux n cpt =
    Printf.printf "choisissez une valeur : \n";
    let choix = read_int () in
      if n = choix then begin
        Printf.printf "Bravo, la valeur était %d\n" n;
        cpt
      end
      else begin
        if n < choix then
          Printf.printf "Plus bas, la valeur %d est trop haute\n" choix
        else
          Printf.printf "Plus haut, la valeur %d est trop basse\n" choix;
        guess_aux n (cpt+1)
      end;
  in
    guess_aux n 1

let () = 
  Random.self_init();
  let res = Random.int 20; in
    let cpt = guess res in
    Printf.printf "Le nombre de coup est de %d\n" cpt