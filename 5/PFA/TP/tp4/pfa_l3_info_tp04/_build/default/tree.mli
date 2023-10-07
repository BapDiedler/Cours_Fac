module type CompPrint = sig
  type t

  val compare : t -> t -> int
  (** [compare v1 v2] revoie [c] avec :
      - [c = 0] si [v1 = v2]
      - [c < 0] si [v1 < v2]
      - [c > 0] si [v1 > v2]
  *)

  val to_string : t -> string
  (** [to_string v] renvoie la représentation de [v] sous forme
      de chaîne de caractères.
    *)
end

(** Signature des ensembles *)
module type S = sig
  type elt
  (** Le type des éléments *)

  type t
  (** Le type des ensembles *)

  val empty : t
  (** L'ensemble vide *)

  val is_empty : t -> bool
  (** Test du vide *)

  val singleton : elt -> t
  (** [singleton e] crée l'ensemble à un élément *)

  val mem : elt -> t -> bool
  (** apartenance à l'ensemble *)

  val add : elt -> t -> t
  (** [add e t] ajoute un élément à l'ensemble [t] *)

  val remove : elt -> t -> t
  (** [remove e t] retire un élément de l'ensemble [t] *)

  val union : t -> t -> t
  (** [union t1 t2] renvoie l'union de [t1] et [t2] *)

  val inter : t -> t -> t
  (** [inter t1 t2] renvoie l'intersection de [t1] et [t2] *)

  val diff : t -> t -> t
  (** [diff t1 t2] renvoie la différence de [t1] et [t2] *)

  val subset : t -> t -> bool
  (** [subset t1 t2] renvoie [true] si et seulement si [t1] est
        un sous-ensemble de [t2]. *)

  val fold : (elt -> 'a -> 'a) -> t -> 'a -> 'a
  (** [fold f t acc], si [t = { v1; v2; ... ; vn }],
        calcule [ (f vn (... (f v2 (f v1 acc)))) ] *)

  val iter : (elt -> unit) -> t -> unit
  (** [iter f t] applique [f] à tous les éléments de [t] par
        ordre croissant.
    *)

  val to_string : t -> string
  (** Renvoie une chaîne de caractères représentant les éléments de l'ensemble. *)

  (* Q_2.1 suite *)

  (* Q_2.2 suite *)

  (* Q_2.3 suite *)
end

module Make (E : CompPrint) : S with type elt = E.t
