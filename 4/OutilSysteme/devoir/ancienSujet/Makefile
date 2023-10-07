all: Codes

Filtre:
	mkdir -p DOS/TEX
	mkdir -p DOS/PDF
	mkdir -p DOS/C
	mkdir -p DOS/JAVA
	mv DOS/*.tex DOS/TEX 2>/dev/null || true
	mv DOS/*.java DOS/JAVA 2>/dev/null || true
	mv DOS/*.c DOS/C 2>/dev/null || true
	mv DOS/*.pdf DOS/PDF 2>/dev/null || true
	mv DOS/TEX ../ 2>/dev/null || true
	mv DOS/JAVA ../ 2>/dev/null || true
	mv DOS/C ../ 2>/dev/null || true
	mv DOS/PDF ../ 2>/dev/null || true
	rm -rf DOS
	mkdir -p DOS
	mv TEX DOS 2>/dev/null || true
	mv JAVA DOS 2>/dev/null || true
	mv C DOS 2>/dev/null || true
	mv PDF DOS 2>/dev/null || true

Codes:
	mkdir -p Codes
	mv DOS/*.java Codes
	mv DOS/*.c Codes
	mv DOS/*.tex Codes

clean:	Filtre
	mv DOS/TEX/* DOS 2>/dev/null || true
	mv DOS/JAVA/* DOS 2>/dev/null || true
	mv DOS/C/* DOS 2>/dev/null || true
	mv DOS/PDF/* DOS 2>/dev/null || true
	rm -rf TEX
	rm -rf PDF
	rm -rf C
	rm -rf JAVA

.PHONY: clean Codes Filtre
