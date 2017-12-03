all: clean pdf

clean:
	$(info ====================================[ Cleaning up ]====================================)
	rm -rf verslag.pdf

pdfs:
	$(info ====================================[ Creating pdf ]====================================)
	latexmk -c --shell-escape -pdf verslag.tex
