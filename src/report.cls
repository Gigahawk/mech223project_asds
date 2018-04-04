% Load the Base Class
\LoadClass[12pt]{article}
%% Begin dependencies
\usepackage{sectsty}
%% Make sections sansserif
%\allsectionsfont{\normalfont\sffamily\bfseries}
%
\usepackage{titlesec}
\usepackage{float}
\usepackage{graphicx}
\usepackage{caption}
%
%\usepackage[round]{natbib}
%\bibliographystyle{apalike}
%
\usepackage[hidelinks]{hyperref}
\usepackage{titling}

% Enable bibliography with clickable links
\usepackage[backend=biber,style=apa,hyperref=true]{biblatex}
\addbibresource{bibliography.bib}

% Change urls back to monospace typewriter style
% font for bibliography
\urlstyle{tt}

%\usepackage{acro}
% \acsetup{first-style=long}
%
%% Allow acronyms to be a separate file
\usepackage{verbatim}
%
\usepackage{geometry}
% Set the Paper Size and margins
\geometry{margin=1.0in}

% Enable ragged right margin
\raggedright

% Double space text (yea i know its weird)
\linespread{1.3}

% Allow \nameref (gets name of label)
\usepackage{nameref}

% Reset toc to have single space
\usepackage{tocloft}
\renewcommand\cftsecafterpnum{\vskip10pt}

% Show subfigures in list of figures
\setcounter{lofdepth}{2}

% Allow itemlist formatting
\usepackage{enumitem}

% Pack in list items tighter
\setlist[itemize]{noitemsep}
\setlist[enumerate]{noitemsep}

% Allow multiline cells
\usepackage{makecell}

%
%\usepackage{array}
%% Create table columns with specified length
%\newcolumntype{L}[1]{>{\raggedright\let\newline\\\arraybackslash\hspace{0pt}}m{#1}}
%\newcolumntype{C}[1]{>{\centering\let\newline\\\arraybackslash\hspace{0pt}}m{#1}}
%\newcolumntype{R}[1]{>{\raggedleft\let\newline\\\arraybackslash\hspace{0pt}}m{#1}}
%% Make table rows spaced apart
%\renewcommand{\arraystretch}{1.5}

% \setlength{\headheight}{15.2pt}
%
%\usepackage{tikz}
%\usetikzlibrary{arrows,shapes}
%\usetikzlibrary{positioning}
%\usetikzlibrary{arrows.meta}
%\usetikzlibrary{calc}

\usepackage{forarray}

\setlength{\parskip}{10pt}

% Pre-define macro for the running header
\def\therunningheader{}

% Create pagestyles for title and rest of report
\usepackage{fancyhdr}
% Page style used for title
\fancypagestyle{reporttitle}{
	% Explicitly set length of header to make sure content fits
	\setlength{\headheight}{18pt}

	% Remove header line and reset headers/footer
	\renewcommand{\headrulewidth}{0pt}
	\fancyhead{}
	\fancyfoot{}

	\lhead{Running head: \therunningheader}
	\rhead{}
}

% Page style used for rest of report
\fancypagestyle{reportmain}{
	% Explicitly set length of header to make sure content fits properly
	\setlength{\headheight}{18pt}

	% Remove header line and reset headers/footers
	\renewcommand{\headrulewidth}{0pt}
	\fancyhead{}
	\fancyfoot{}

	\lhead{\therunningheader}
	\rhead{\thepage}
}
% Make all the pages the same
\fancypagestyle{empty}{
	% Explicitly set length of header to make sure content fits properly
	\setlength{\headheight}{18pt}

	% Remove header line and reset headers/footers
	\renewcommand{\headrulewidth}{0pt}
	\fancyhead{}
	\fancyfoot{}

	\lhead{\therunningheader}
	\rhead{\thepage}
}
% Make all the pages the same
\fancypagestyle{plain}{
	% Explicitly set length of header to make sure content fits properly
	\setlength{\headheight}{18pt}

	% Remove header line and reset headers/footers
	\renewcommand{\headrulewidth}{0pt}
	\fancyhead{}
	\fancyfoot{}

	\lhead{\therunningheader}
	\rhead{\thepage}
}
\pagestyle{reportmain}

%
%\fancypagestyle{empty}{
% \fancyhf{}
% \fancyhead[L]{\therunningheader}
%}
%
%\renewcommand{\headrulewidth}{0pt}
%\lhead{\therunningheader}
%\rhead{}

% Prevent paragraphs from cutting off
\widowpenalties 1 10000
\raggedbottom

% Disable indentation
\setlength{\parindent}{0mm}

% Make captions centered
\captionsetup{justification=centering,margin=2cm}

% Remove small abstract title
\patchcmd{\abstract}{\small}{\Large}{}{}

% Begin new commands
\newcommand{\runningheader}[1]{
	\def\therunningheader{#1}
}
\newcommand{\for}[1]{
	\def\thefor{#1}
}
\newcommand{\authorformat}{
	by \par
	\ForEachX{,}{
		\thislevelitem \par
	}{\theauthor}
}
\newcommand{\forformat}{
	for \par
	\ForEachX{,}{
		\thislevelitem \par
	}{\thefor}
}
\def\changemargin#1{\list{}{\rightmargin#1\leftmargin#1}\item[]}
\let\endchangemargin=\endlist

\date{\today} % needed for \thedate to work
\renewcommand{\maketitle}{
	\begin{titlepage}
		%\thispagestyle{reporttitle}
		\vspace*{0.5in}
		%\begin{changemargin}{1.5in}
			\centering

			{\huge\bfseries \thetitle \par }
			\vspace{0.5in}
			{\large\bfseries \forformat }
			\vspace{0.5in}
			{\large\bfseries \authorformat }

			\vfill

			% Bottom of the page
			{\large \thedate \par}
		%\end{changemargin}
	\end{titlepage}
}

\renewenvironment{abstract}{
	\begin{center}
		{\Large\bfseries Abstract}
	\end{center}
	\noindent
	\normalfont
	\begin{changemargin}{0.07in}

}{\end{changemargin}}

% Allow footnotes without marker
%\newcommand\blfootnote[1]{%
%  \begingroup
%  \renewcommand\thefootnote{}\footnote{#1}%
%  \addtocounter{footnote}{-1}%
%  \endgroup
%}
