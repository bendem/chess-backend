# CMD=pdflatex # Use this instead if you don't have xelex
CMD=xelatex

OUT=build
FLAGS=-interaction batchmode -output-directory $(OUT) -shell-escape -etex -halt-on-error
PDF=$(CMD) $(FLAGS)

.PHONY: clean docs

documentation.pdf: $(OUT)/documentation.pdf
	cp $< $@

$(OUT):
	mkdir $@

$(OUT)/documentation.pdf: $(OUT) documentation.tex parts/*.tex
	$(PDF) documentation.tex
	$(PDF) documentation.tex

clean:
	rm -rf $(OUT)/* *.aux *.log *.toc *.dvi *.pdf
