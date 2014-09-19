proposal.pdf: proposal.tex
	pdflatex proposal.tex
	bibtex proposal
	pdflatex proposal.tex
	pdflatex proposal.tex

.PHONY: clean
clean:
	rm -f *.pdf *.bbl *.blg *.log *.aux
