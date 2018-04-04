SOURCEDIR = src
BUILDDIR = bin
RESDIR = res
APPENDDIR = appendices
SECTIONDIR = sections
TEMPDIR = temp

all:
	latexmk -f -pdf -output-directory=../../$(BUILDDIR) -cd $(SOURCEDIR)/$(RESDIR)/*.tex
#	latexmk -f -pdf -output-directory=../../$(BUILDDIR) -cd $(SOURCEDIR)/$(SECTIONDIR)/*.tex
#	latexmk -f -pdf -output-directory=../../$(BUILDDIR) -cd $(SOURCEDIR)/$(SECTIONDIR)/$(APPENDDIR)/*.tex
	latexmk -f -pdf -output-directory=../$(BUILDDIR) -cd $(SOURCEDIR)/*.tex
#	latexmk -f -c -output-directory=../../$(BUILDDIR) -cd $(SOURCEDIR)/$(RESDIR)/*.tex
#	latexmk -f -c -output-directory=../../$(BUILDDIR) -cd $(SOURCEDIR)/$(SECTIONDIR)/*.tex
#	latexmk -f -c -output-directory=../$(BUILDDIR) -cd $(SOURCEDIR)/*.tex
#	latexmk -f -c -output-directory=../../$(BUILDDIR) -cd $(SOURCEDIR)/$(SECTIONDIR)/$(APPENDDIR)/*.tex

report:
	latexmk -f -pdf -output-directory=../$(BUILDDIR) -cd $(SOURCEDIR)/report.tex

clean:
	rm -rf $(BUILDDIR)/*

clear:
	rm -rf $(TEMPDIR)/*

tidy:
	latexmk -f -c -output-directory=../../$(BUILDDIR) -cd $(SOURCEDIR)/$(RESDIR)/*.tex
	latexmk -f -c -output-directory=../../$(BUILDDIR) -cd $(SOURCEDIR)/$(SECTIONDIR)/*.tex
	latexmk -f -c -output-directory=../$(BUILDDIR) -cd $(SOURCEDIR)/*.tex
	latexmk -f -c -output-directory=../../$(BUILDDIR) -cd $(SOURCEDIR)/$(SECTIONDIR)/$(APPENDDIR)/*.tex
	find $(BUILDDIR)/ -type f ! -name '*.pdf' -delete


