let hanoi n =
  let rec hanoi_aux dep mil arr n =
    if n > 0 then begin
      hanoi_aux dep arr mil (n-1);
      Printf.printf "%s -> %s\n" dep arr;
      hanoi_aux mil dep arr (n-1);
    end
  in
  hanoi_aux "A" "B" "C" n

let () = hanoi 4