let affiche_tab a =
  let rec affiche_tab_aux a n = begin
    if n< Array.length a then begin
      Printf.printf "    ";
      Printf.printf "%s\n" a.(n);
      affiche_tab_aux a (n+1)
    end
  end
  in
  affiche_tab_aux a 0

let rec afficher_dir d =
  if Sys.is_directory d then begin
    Printf.printf "%s :\n" d;
    let  contenu = Sys.readdir d in
      affiche_tab contenu;
      Sys.chdir d;
      afficher_dir_iter 0 contenu;
      Sys.chdir "..";
  end
  and afficher_dir_iter i t =
    if i < Array.length t then begin
      afficher_dir t.(i);
      afficher_dir_iter (i+1) t
    end


let () = afficher_dir "."