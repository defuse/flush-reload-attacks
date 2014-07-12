pdf: sidechannels.pdf 
sidechannels.pdf : sidechannels.tex sidechannels.bib
	pdflatex sidechannels.tex
	bibtex sidechannels
	pdflatex sidechannels.tex
	pdflatex sidechannels.tex

clean:
	rm *.aux *.bbl *.log *.blg *.pdf

