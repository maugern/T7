# pdflatex from package 'texlive-base' is requied to build PDF  documents
# htlatex  from package 'tex4ht'       is requied to build HTML documents

OUT=*.log *.aux *.out *.css *.svg *.toc *.4ct *.4tc *.bbl *.blg *.lg *.tmp *.xref *.idv *.pdf *.html *.dvi

all: pdfdocs htmldocs

bib:
	latex  $(basename $(wildcard *.tex))
	bibtex $(basename $(wildcard *.tex))
	latex  $(basename $(wildcard *.tex))

%.pdf: %.tex
	pdflatex $<

%.html: %.tex
	make4ht -u -c $(wildcard *.cfg) $<

clean:
	$(RM) $(OUT)

png: $(patsubst %.svg, %.png, $(wildcard *.svg))
pdfdocs:  png bib $(patsubst %.tex, %.pdf,  $(wildcard *.tex))
htmldocs: png bib $(patsubst %.tex, %.html, $(wildcard *.tex))
