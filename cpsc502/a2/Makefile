relwork.pdf: relwork.tex relwork.bib
	pdflatex relwork.tex
	bibtex relwork
	pdflatex relwork.tex
	pdflatex relwork.tex
	
.PHONY: clean
clean:
	rm -f *.pdf *.bbl *.blg *.log *.aux
