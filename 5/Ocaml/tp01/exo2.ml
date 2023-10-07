let valide =
  (Array.length Sys.argv) = 2

let () =
  if valide then
    let fichier = Sys.argv.(1) in
      if Sys.file_exists fichier then
        if Sys.is_directory fichier then
          Printf.printf "%s est un répertoire\n" fichier
        else
          Printf.printf "%s est un fichier\n" fichier
      else
        Printf.printf "le fichier %s n'existe pas\n" fichier
  else
    Printf.printf "le nombre d'arguments doit être de 1\n"