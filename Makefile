all:
	pdflatex tp2.tex
	pdflatex tp2.tex
	pdflatex tp2.tex


clean:
	rm -f tp2.pdf
	rm -f tp2.aux
	rm -f tp2.toc
	rm -f tp2.log
	rm -f tp2.out
