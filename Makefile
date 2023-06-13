ifeq ($(shell uname), Linux)
	CHKFLAGS=-lgtest -lgtest_main -pthread -lrt -lm -lsubunit
else
	CHKFLAGS=-lgtest -lgtest_main
endif

PF=viewer/
DISTDIR=./build
ZIPNAME=C8_3D_Viewer
all: install dvi tests

install:
	@-mkdir $(DISTDIR)
	@-cd $(DISTDIR) && qmake6 $(CURDIR)/viewer/viewer.pro
	@-cd $(DISTDIR) && make
	@-cd $(DISTDIR) && make clean
	@-cd $(DISTDIR) && rm -f Makefile
	@-cd $(DISTDIR) && rm -f *.stash
uninstall:
	@rm -rf $(DISTDIR)
clean:
	@rm -rf tests *.o
dvi:
	@echo "user manual"
	@open CPP4_3D_Viewer_docs.html
dist:
	@mkdir $(ZIPNAME)
	@cp -R viewer $(ZIPNAME)/viewer
	@cp Makefile $(ZIPNAME)/Makefile
	@cp CPP4_3D_Viewer_docs.texi $(ZIPNAME)/CPP4_3D_Viewer_docs.texi
	@tar -cf $(ZIPNAME).tar $(ZIPNAME)
	@gzip $(ZIPNAME).tar
	@rm -rf $(ZIPNAME)
tests:
	cd test/test && qmake6 test.pro
	cd test/test && make
	cd test/test && ./test
	cd test/test && make clean
	cd test/test && rm -rf Makefile test test.pro.user .qmake.stash
style:
	@cp ../materials/linters/.clang-format .
	@clang-format -i $(PF)*.cc 
	@clang-format -i $(PF)*.h
	@clang-format -n $(PF)*.cc 
	@clang-format -n $(PF)*.h
	@rm .clang-format

.PHONY: style tests gcov_report
