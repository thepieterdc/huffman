all: clean images pdf

clean:
	$(info ====================================[ Cleaning up ]====================================)
	rm -rf verslag.pdf

images:
	$(info ====================================[ Creating images ]=============================)

pdf:
	$(info ====================================[ Creating pdf ]====================================)
	latexmk --shell-escape -pdf verslag.tex
	latexmk -c
