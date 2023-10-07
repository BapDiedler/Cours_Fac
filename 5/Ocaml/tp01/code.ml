let rec f n =
  if n >= 0 then begin
  Printf.printf "%d\n" n;
  f (n-1)
  end
let () = f 10