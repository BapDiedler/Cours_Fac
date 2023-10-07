% Documentclass DEUG
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{DEUG}
\LoadClass[a4paper,11pt]{article}

\DeclareOption{correction}{\@correctiontrue}
\newif\if@correction
\@correctionfalse
\ProcessOptions

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Packages
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\RequirePackage[T1]{fontenc}
\RequirePackage[utf8]{inputenc}
\RequirePackage[francais]{babel}
\RequirePackage{verbatim}
\RequirePackage{multicol}

\RequirePackage{amsmath}
\RequirePackage{amsthm}
\RequirePackage{amsfonts}

\RequirePackage{subfiles}
\RequirePackage{xstring}
%\RequirePackage{multido}
%\RequirePackage{pst-node}
%\RequirePackage{french}
\RequirePackage[noend]{algpseudocode}
\RequirePackage{todonotes}
\RequirePackage{subcaption}

\RequirePackage{hyperref}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% French keywords for algorithms
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\algrenewcommand\algorithmicend{\textbf{fin}}
\algrenewcommand\algorithmicdo{\textbf{faire}}
\algrenewcommand\algorithmicwhile{\textbf{tant que}}
\algrenewcommand\algorithmicfor{\textbf{pour}}
\algrenewcommand\algorithmicforall{\textbf{pour tout}}
\algrenewcommand\algorithmicloop{\textbf{boucle}}
\algrenewcommand\algorithmicrepeat{\textbf{répéter}}
\algrenewcommand\algorithmicuntil{\textbf{jusqu'à}}
\algrenewcommand\algorithmicprocedure{\textbf{procédure}}
\algrenewcommand\algorithmicfunction{\textbf{fonction}}
\algrenewcommand\algorithmicif{\textbf{si}}
\algrenewcommand\algorithmicthen{\textbf{alors}}
\algrenewcommand\algorithmicelse{\textbf{sinon}}
\algrenewcommand\algorithmicrequire{\textbf{Entrée~:}}
\algrenewcommand\algorithmicensure{\textbf{Sortie~:}}
\algrenewcommand\algorithmicreturn{\textbf{retourne}}
\algrenewcommand\textproc{\textsc}

% variable in a program
\newcommand*{\var}[1]{\mathsf{#1}}
\newcommand*{\algo}[1]{\mathsf{#1}}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Correction
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\if@correction
        \newenvironment{correction}%
                {\par\noindent\begin{small}\textbf{Correction~:}}%
                {\end{small}\par\medskip}
\else
        \let\correction\comment
        \let\endcorrection\endcomment
\fi

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% PAGE LAYOUT
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\setlength{\textwidth}{16cm}
\setlength{\textheight}{23cm}
\setlength{\topmargin}{0cm}
\setlength{\evensidemargin}{0cm}
\setlength{\oddsidemargin}{0cm}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Entete
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


\newcommand{\entete}[3]{\begin{center}
        Universit\'e Paris Diderot - L1 informatique \hfill Ann\'ee  #3\\
\vspace{0.5cm}
       {\Large Initiation à la programmation \\#1 n$^\circ$ #2}\\
\if@correction (Correction)\else\relax\fi
\end{center}
\bigskip}


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Sections
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\renewcommand{\thesection}{\Roman{section})}
\renewcommand{\thesubsection}{\alph{subsection})}


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Environnement exercice
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Used internally in environment exercice
% Can be used to add difficulty to an exercice
\newcommand*{\difficulty}[1]{%
  \reversemarginpar%
  \IfEqCase{#1}{%
    {0}{}%
    {1}{\leavevmode\marginpar[\hfill\raisebox{0.2ex}{$\star$}]{}}%
    {2}{\leavevmode\marginpar[\hfill\raisebox{0.2ex}{$\star\star$}]{}}%
  }[\PackageError{DEUG}{Undefined option to difficulty: #1}{}]%
  \reversemarginpar%
}

\newcounter{exercice}
% \begin{exercice}[difficulty]{title}, difficulty = 0,1,2
\newenvironment{exercice}[2][0]{
\noindent\textbf{Exercice \refstepcounter{exercice}\theexercice.} \textit{#2.} \difficulty{#1}
\par
}
{
\medskip
}

% Specify the difficulty of an exercice (0 -> nothing, 1 -> *, 2 -> *)
% Shoud be used in the title of an exercice or for a question (item of an enumerate)


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Details...
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\newcommand{\sujet}[1]
{\begin{center}{\LARGE{\bf #1}}\end{center}\bigskip}

\AtBeginDocument{%
\renewcommand{\labelitemi}{$\bullet$}
\sloppy
\hbadness=5000
}

