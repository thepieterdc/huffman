all: clean pdf

clean:
	$(info ====================================[ Cleaning up ]====================================)
	rm -rf verslag.pdf

pdf:
	$(info ====================================[ Creating pdf ]====================================)
	latexmk --shell-escape -pdf verslag.tex
	latexmk -c
