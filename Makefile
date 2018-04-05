all: Hauptdokument

Hauptdokument:
	pdflatex Hauptdokument.tex

clean:
	rm *.aux *.pdf *.idx *.log *.out *.toc
