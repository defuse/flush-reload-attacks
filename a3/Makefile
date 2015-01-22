proposal.pdf: proposal.tex proposal.bib
	pdflatex proposal.tex
	bibtex proposal
	pdflatex proposal.tex
	pdflatex proposal.tex
	
.PHONY: clean
clean:
	rm -f *.pdf *.bbl *.blg *.log *.aux
