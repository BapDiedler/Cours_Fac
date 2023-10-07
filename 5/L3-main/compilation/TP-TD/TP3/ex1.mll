{
    let file = Sys.argv.(1)
    let file_out = open_out (file ^ "_transformed")
    let print s = Printf.fprintf file_out s 
}

let alphabet = ['a'-'z' 'A'-'Z' ' ']
let signeponctu = [',' '!' ';' '\'' '.']

rule transfotext = parse
| alphabet { print " "; transfotext lexbuf}
| signeponctu as s { print "%c" s; transfotext lexbuf }
| eof {}

{
    let () = transfotext (Lexing.from_channel (open_in file)); 
        close_out file_out
}