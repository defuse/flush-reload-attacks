proposal.pdf: proposal.tex proposal.bib distribution.tex
	pdflatex proposal.tex
	bibtex proposal
	pdflatex proposal.tex
	pdflatex proposal.tex
	
.PHONY: clean
clean:
	rm -f *.pdf *.bbl *.blg *.log *.aux *.ent
