all: catalogue
catalogue: catalogue.o
			g++ -o catalogue catalogue.o
clean: 
			rm -f catalogue.o